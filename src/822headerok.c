#include "buffer.h"
#include "error.h"
#include "getln.h"
#include "mess822.h"
#include "exit.h"

stralloc line = {0};
int match;

int main(int argc,char * const *argv) {
  for (;;) {
    if (getln(buffer_0,&line,&match,'\n') == -1) _exit(111);
    if (!mess822_ok(&line)) break;
    if (!match) _exit(0);
  }
  if (match) {
    --line.len;
    if (line.len && (line.s[line.len - 1] == '\r')) --line.len;
  }
  if (!line.len) _exit(0);
  _exit(100);
}
