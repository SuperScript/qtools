#include "buffer.h"
#include "strerr.h"
#include "getln.h"
#include "mess822.h"
#include "case.h"
#include "stralloc.h"
#include "alloc.h"
#include "sgetopt.h"
#include "str.h"
#include <unistd.h>

#define FATAL "822addr: fatal: "

void die_usage(void) {
  strerr_die1x(100,"822addr: usage: 822addr [-dcan] [ field ... ]");
}

void nomem() {
  strerr_die2x(111,FATAL,"out of memory");
}

int prefix = 0;
int flagnewline = 0;
int flag;
stralloc addr = {0};

mess822_header h = MESS822_HEADER;
mess822_action *a;
mess822_action a0[] = {
  { "to", &flag, 0, 0, &addr, 0 }
, { "cc", &flag, 0, 0, &addr, 0 }
, { 0, 0, 0, 0, 0, 0 }
};

stralloc line = {0};
int match;

mess822_action *init(int n,char * const *s)
{
  int i;
  mess822_action *a1;

  if (!n) return a0;

  a1 = (mess822_action *)alloc((n + 1) * sizeof(mess822_action));
  if (!a1) nomem();

  for (i = 0;i < n;i++) {
    a1[i].name = *s;
    a1[i].flag = &flag;
    a1[i].copy = 0;
    a1[i].value = 0;
    a1[i].addr = &addr;
    a1[i].when = 0;
    ++s;
  }
  a1[n].name = 0;
  a1[n].flag = 0;
  a1[n].copy = 0;
  a1[n].value = 0;
  a1[n].addr = 0;
  a1[n].when = 0;

  return a1;
}

int main(int argc,char * const *argv) {
  int opt;
  unsigned int u;
  const char *x;

  while ((opt = getopt(argc,argv,"dcna")) != opteof)
    switch(opt) {
      case 'a': prefix = 0; break;
      case 'd': prefix = '+'; break;
      case 'c': prefix = '('; break;
      case 'n': flagnewline = 1; break;
      default: die_usage();
    }
  argc -= optind;
  argv += optind;

  a = init(argc, argv);
  if (!mess822_begin(&h,a)) nomem();

  for (;;) {
    if (getln(buffer_0,&line,&match,'\n') == -1)
      strerr_die2sys(111,FATAL,"unable to read input: ");

    if (!mess822_ok(&line)) break;
    if (!mess822_line(&h,&line)) nomem();
    if (!match) break;
  }

  if (!mess822_end(&h)) nomem();

  if (prefix || flagnewline) {
    x = addr.s;
    u = 0;
    
    while (u < addr.len) {
      u = str_chr(x,0);
      if (prefix) {
	if (*x == prefix) {
	  buffer_put(buffer_1,x + 1,u - 1);
	  buffer_put(buffer_1,flagnewline ? "\n" : "\0",1);
	}
      }
      else {
	buffer_put(buffer_1,x,u);
	buffer_put(buffer_1,flagnewline ? "\n" : "\0",1);
      }
      x += u + 1;
      u = x - addr.s;
    }
    buffer_flush(buffer_1);
  }
  else
    buffer_putflush(buffer_1,addr.s,addr.len);

  _exit(flag ? 0 : 100);
}
