#include <unistd.h>
#include <sys/stat.h>
#include "sig.h"
#include "sig.h"
#include "byte.h"
#include "exit.h"
#include "open.h"
#include "buffer.h"
#include "strerr.h"
#include "error.h"
#include "fmt.h"
#include "env.h"
#include "str.h"
#include "fork.h"
#include "wait.h"
#include "seek.h"
#include "now.h"
#include "env.h"
#include "pathexec.h"

#define FATAL "condtomaildir: fatal: "

char buf[BUFFER_INSIZE];
char outbuf[BUFFER_OUTSIZE];
char fntmptph[80 + FMT_ULONG * 2];
char fnnewtph[80 + FMT_ULONG * 2];
void tryunlinktmp() { unlink(fntmptph); }
void sigalrm ()
{
  tryunlinktmp();
  strerr_die1x(111,"Timeout on maildir delivery. (#4.3.0)");
}

int doit (dir)
char *dir;
{
  unsigned long pid;
  unsigned long thyme;
  char host[64];
  char *s;
  int loop;
  struct stat st;
  int fd;
  buffer ss;
  buffer ssout;
  char *rpline;
  char *dtline;

  sig_catch(sig_alarm,sigalrm);
  if (chdir(dir) == -1) { if (error_temp(errno)) return(1); return(2); }
  pid = getpid();
  host[0] = '\0';
  gethostname(host,sizeof(host));
  for (loop = 0;;++loop) {
    thyme = now();
    s = fntmptph;
    s += fmt_str(s,"tmp/");
    s += fmt_ulong(s,thyme); *s++ = '.';
    s += fmt_ulong(s,pid); *s++ = '.';
    s += fmt_strn(s,host,sizeof(host)); *s++ = 0;
    if (stat(fntmptph, &st) == -1) if (errno == error_noent) break;
    if (loop == 2) return(1);
    sleep(2);
  }
  str_copy(fnnewtph,fntmptph);
  byte_copy(fnnewtph,3,"new");

  alarm(86400);
  fd = open_excl(fntmptph);
  if (fd == -1) return(1);

  rpline = env_get("RPLINE");
  if (!rpline) strerr_die2x(100,FATAL,"RPLINE not set");
  dtline = env_get("DTLINE");
  if (!dtline) strerr_die2x(100,FATAL,"DTLINE not set");

  buffer_init(&ss,buffer_unixread,0,buf,sizeof(buf));
  buffer_init(&ssout,buffer_unixwrite,fd,outbuf,sizeof(outbuf));
  if (buffer_puts(&ssout,rpline) == -1) goto fail;
  if (buffer_puts(&ssout,dtline) == -1) goto fail;

  switch (buffer_copy(&ssout,&ss)) {
    case -2: tryunlinktmp(); return(4);
    case -3: goto fail;
  }

  if (buffer_flush(&ssout) == -1) goto fail;
  if (fsync(fd) == -1) goto fail;
  if (close(fd) == -1) goto fail;

  if (link(fntmptph,fnnewtph) == -1) goto fail;
  tryunlinktmp(); return(0);

 fail: tryunlinktmp(); return(1);
}

int main(int argc,char * const *argv,char * const *envp)
{
  const char *dir;
  int pid;
  int wstat;
  int r;

  if (!argv[1] || !argv[2]) 
    strerr_die1x(100,"condtomaildir: usage: condtomaildir dir program [ arg ... ]");

  pid = fork();
  if (pid == -1)
    strerr_die2sys(111,FATAL,"unable to fork: ");
  if (pid == 0) {
    pathexec_run(argv[2],argv + 2,envp);
    if (error_temp(errno)) _exit(111);
    _exit(100);
  }
  if (wait_pid(&wstat,pid) == -1)
    strerr_die2x(111,FATAL,"wait failed");
  if (wait_crashed(wstat))
    strerr_die2x(111,FATAL,"child crashed");
  switch(wait_exitcode(wstat)) {
    case 0: break;
    case 111: strerr_die2x(111,FATAL,"temporary child error");
    default: _exit(0);
  }

  if (seek_begin(0) == -1)
    strerr_die2sys(111,FATAL,"unable to rewind: ");
  umask(077);
  sig_ignore(sig_pipe);

  dir = argv[1];

  r = doit(dir);
  switch(r) {
    case 0: break;
    case 2: strerr_die1x(111,"Unable to chdir to maildir. (#4.2.1)");
    case 3: strerr_die1x(111,"Timeout on maildir delivery. (#4.3.0)");
    case 4: strerr_die1x(111,"Unable to read message. (#4.3.0)");
    default: strerr_die1x(111,"Temporary error on maildir delivery. (#4.3.0)");
  }
  strerr_die1x(99,"condtomaildir");
}
