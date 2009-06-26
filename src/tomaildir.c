#include <unistd.h>
#include <sys/stat.h>
#include "sig.h"
#include "byte.h"
#include "exit.h"
#include "open.h"
#include "buffer.h"
#include "strerr.h"
#include "error.h"
#include "fmt.h"
#include "str.h"
#include "now.h"
#include "env.h"
#include "sgetopt.h"

#define FATAL "tomaildir: fatal: "

void usage() { strerr_die1x(100,"tomaildir: usage: tomaildir [ -l ] dir"); }

char buf[1024];
char outbuf[1024];

int flagterm = 0;
char fntmptph[80 + FMT_ULONG * 2];
char fnnewtph[80 + FMT_ULONG * 2];
void tryunlinktmp() { unlink(fntmptph); }
void sigalrm (void) {
  tryunlinktmp();
  strerr_die1x(111,"Timeout on maildir delivery. (#4.3.0)");
}

int doit (char *dir) {
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

  switch (buffer_copy(&ssout, &ss)) {
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

int main(int argc,char * const *argv) {
  char *dir;
  int r;
  int opt;

  while ((opt = getopt(argc,argv,"l")) != opteof)
    switch(opt) {
      case 'l': flagterm = 1; break;
      default: usage();
    }
  argc -= optind;
  argv += optind;

  umask(077);
  sig_ignore(sig_pipe);

  dir = *argv;
  if (!dir) usage();

  r = doit(dir);
  switch(r) {
    case 0: break;
    case 2: strerr_die1x(111,"Unable to chdir to maildir. (#4.2.1)");
    case 3: strerr_die1x(111,"Timeout on maildir delivery. (#4.3.0)");
    case 4: strerr_die1x(111,"Unable to read message. (#4.3.0)");
    default: strerr_die1x(111,"Temporary error on maildir delivery. (#4.3.0)");
  }
  strerr_die1x(flagterm ? 99 : 0,"tomaildir");
}
