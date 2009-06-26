#include "buffer.h"
#include "strerr.h"
#include "error.h"
#include "fd.h"
#include "getln.h"
#include "mess822.h"
#include "exit.h"

#define FATAL "822body: fatal: "

stralloc line = {0};
int match;

int main(int argc,char * const *argv) {
  int r;

  for (;;) {
    if (getln(buffer_0,&line,&match,'\n') == -1)
      strerr_die2sys(111,FATAL,"unable to read input: ");
    if (!mess822_ok(&line)) break;
    if (!match) { line.len = 0; break; }
  }
  if (match) {
    r = 0;
    --line.len; ++r;
    if (line.len && (line.s[line.len - 1] == '\r')) { --line.len; ++r; }
    if (line.len) line.len += r;
  }
  buffer_put(buffer_1,line.s,line.len);
  buffer_copy(buffer_1,buffer_0);
  buffer_flush(buffer_1);
  _exit(0);
}
