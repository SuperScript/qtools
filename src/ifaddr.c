#include "buffer.h"
#include "strerr.h"
#include "getln.h"
#include "mess822.h"
#include "case.h"
#include "env.h"
#include "exit.h"
#include "stralloc.h"
#include "alloc.h"
#include "str.h"

#define FATAL "ifaddr: fatal: "

void nomem()
{
  strerr_die2x(111,FATAL,"out of memory");
}

stralloc addrlist = {0};

mess822_header h = MESS822_HEADER;
mess822_action *a;
mess822_action a0[] = {
  { "to", 0, 0, 0, &addrlist, 0 }
, { "cc", 0, 0, 0, &addrlist, 0 }
, { 0, 0, 0, 0, 0, 0 }
} ;

stralloc line = {0};
int match;

const char *recipient = 0;
char * const *addrs;

mess822_action *init(int n,char * const *s)
{
  int i;
  mess822_action *a1;

  if (!n) return a0;

  a1 = (mess822_action *)alloc((n + 1) * sizeof(mess822_action));
  if (!a1) nomem();

  for (i = 0;i < n;i++) {
    a1[i].name = *s;
    a1[i].flag = 0;
    a1[i].copy = 0;
    a1[i].value = 0;
    a1[i].addr = &addrlist;
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

void check(const char *addr)
{
  int i;

  if (recipient) {
    if (recipient[0] == '@') {
      if (case_equals(addr + str_rchr(addr,'@'),recipient)) _exit(0);
    }
    else
      if (case_equals(addr,recipient)) _exit(0);
  }
  else
    for (i = 0;addrs[i];++i)
      if (addrs[i][0] == '@') {
	if (case_equals(addr + str_rchr(addr,'@'),addrs[i])) _exit(0);
      }
      else 
	if (case_equals(addr,addrs[i])) _exit(0);
}

int main(int argc,char * const *argv)
{
  int i;
  int j;

  i = 0;
  addrs = ++argv;

  while (*addrs && str_diff(*addrs,":")) {
    ++i; ++addrs;
  }

  if (*addrs) {
    a = init(i,argv);
    ++addrs;
  }
  else {
    a = init(0,0);
    addrs = argv;
  }

  if (!mess822_begin(&h,a)) nomem();

  if (!*addrs)
    recipient = env_get("RECIPIENT");

  if (!mess822_begin(&h,a)) nomem();

  for (;;) {
    if (getln(buffer_0,&line,&match,'\n') == -1)
      strerr_die2sys(111,FATAL,"unable to read input: ");

    if (!mess822_ok(&line)) break;
    if (!mess822_line(&h,&line)) nomem();
    if (!match) break;
  }

  if (!mess822_end(&h)) nomem();

  for (j = i = 0;j < addrlist.len;++j)
    if (!addrlist.s[j]) {
      if (addrlist.s[i] == '+')
	check(addrlist.s + i + 1);
      i = j + 1;
    }

  _exit(100);
}
