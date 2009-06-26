#include <unistd.h>
#include "exit.h"
#include "error.h"
#include "fork.h"
#include "wait.h"
#include "strerr.h"
#include "buffer.h"
#include "getln.h"
#include "mess822.h"
#include "fd.h"
#include "pathexec.h"
#include "sig.h"

#define FATAL "822headerfilter: fatal: "

stralloc line = {0};
int match;

char pipbuf[1024];
buffer sspip;

int main(int argc,char * const *argv,char * const *envp) {
  int pfi[2];
  int pid;
  int wstat;

  if (!argv[1])
    strerr_die1x(100,"822headerfilter: usage: 822headerfilter prog");

  if (pipe(pfi) == -1) strerr_die2sys(111,FATAL,"unable to create pipe: ");
  pid = fork();
  if (pid == -1) strerr_die2sys(111,FATAL,"unable to fork: ");
  if (pid == 0) {
    close(pfi[1]);
    if (fd_move(0,pfi[0]) == -1)
      strerr_die2sys(111,FATAL,"unable to arrange file descriptors: ");
    pathexec_run(argv[1],argv + 1,envp);
    if (error_temp(errno)) strerr_die2sys(111,FATAL,"exec failed: ");
    strerr_die2sys(100,FATAL,"exec failed: ");
  }
  close(pfi[0]);

  sig_ignore(sig_pipe);
  buffer_init(&sspip,buffer_unixwrite,pfi[1],pipbuf,sizeof pipbuf);
  for (;;) {
    if (getln(buffer_0,&line,&match,'\n') == -1)
      strerr_die2sys(111,FATAL,"unable to read input: ");
    if (!mess822_ok(&line)) break;
    if (buffer_put(&sspip,line.s,line.len) == -1)
      strerr_die2sys(111,FATAL,"unable to write output: ");
    if (!match) { line.len = 0; break; }
  }
  if (buffer_flush(&sspip) == -1)
    strerr_die2x(111,FATAL,"unable to write output: ");
  close(pfi[1]);

  if (wait_pid(&wstat,pid) == -1) strerr_die2x(111,FATAL,"wait failed");
  if (wait_crashed(wstat)) strerr_die2x(111,FATAL,"child crashed");
  if (wait_exitcode(wstat)) _exit(wait_exitcode(wstat));

  if (buffer_put(buffer_1,line.s,line.len) == -1)
    strerr_die2sys(111,FATAL,"unable to write output: ");
  if (buffer_copy(buffer_1,buffer_0) != 0)
    strerr_die2sys(111,FATAL,"unable to read input: ");
  if (buffer_flush(buffer_1) == -1)
    strerr_die2x(111,FATAL,"unable to write output: ");

  _exit(0);
}
