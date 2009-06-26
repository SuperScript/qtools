#include "buffer.h"
#include "strerr.h"
#include "getln.h"
#include "mess822.h"
#include "case.h"
#include "env.h"
#include "exit.h"

#define FATAL "checkaddr: fatal: "

void nomem()
{
  strerr_die2x(111,FATAL,"out of memory");
}

stralloc addrlist = {0};

int match;

const char *recipient;
char * const *recips;

void check(addr)
char *addr;
{
  int i;

  if (recipient)
    if (case_equals(addr,recipient)) _exit(0);

  if (!recipient)
    for (i = 0;recips[i];++i)
      if (case_equals(addr,recips[i])) _exit(0);
}

int main(int argc,char * const *argv) {
  recipient = env_get("RECIPIENT");
  recips = argv + 1;
  if (*recips) recipient = 0;

	for (;;) {
		if (getln(buffer_0,&addrlist,&match,'\0') == -1)
			strerr_die2sys(111,FATAL,"unable to read input: ");
		if (!match) break;
		if (addrlist.s[0] == '+')
			check(addrlist.s + 1);
	}

	_exit(100);
}
