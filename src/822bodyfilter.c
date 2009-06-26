#include "exit.h"
#include "error.h"
#include "strerr.h"
#include "buffer.h"
#include "getln.h"
#include "mess822.h"
#include "fd.h"
#include "seek.h"
#include "pathexec.h"

#define FATAL "822bodyfilter: fatal: "

stralloc line = {0};
int match;

int main(int argc,char * const *argv,char * const *envp)
{
  seek_pos pos;
  int r;

  if (!argv[1])
    strerr_die1x(100,"822bodyfilter: usage: 822bodyfilter program [ arg ... ]");

  for (;;) {
    if (getln(buffer_0,&line,&match,'\n') == -1)
      strerr_die2sys(111,FATAL,"unable to read input: ");
    if (!mess822_ok(&line)) break;
    if (buffer_put(buffer_1,line.s,line.len) == -1)
      strerr_die2sys(111,FATAL,"unable to write output: ");
    if (!match) { line.len = 0; break; }
  }
  r = 0;
  if (match) {
    --line.len;  ++r;
    if (line.len && (line.s[line.len - 1] == '\r')) { --line.len; ++r; }
    if (!line.len) {
      if (buffer_put(buffer_1,line.s,r) == -1)
	strerr_die2sys(111,FATAL,"unable to write output: ");
      r = 0;
    }
  }
  if (buffer_flush(buffer_1) == -1)
    strerr_die2x(111,FATAL,"unable to write output: ");
  pos = seek_cur(0);
  if (pos == -1)
    strerr_die2sys(111,FATAL,"unable to seek: ");
  if (seek_set(0,pos - buffer_0->p - line.len - r) == -1)
    strerr_die2sys(111,FATAL,"unable to seek: ");

  pathexec_run(argv[1],argv + 1,envp);
  if (error_temp(errno)) strerr_die2sys(111,FATAL,"exec failed: ");
  strerr_die2sys(100,FATAL,"exec failed: ");
}
