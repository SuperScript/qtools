#include "buffer.h"
#include "strerr.h"
#include "getln.h"
#include "mess822.h"
#include "case.h"
#include "env.h"
#include "exit.h"
#include "str.h"

#define FATAL "checkdomain: fatal: "

void nomem()
{
  strerr_die2x(111,FATAL,"out of memory");
}

stralloc addrlist = {0};

int match;

const char *recipient;
const char * const *recips;

void check(addr)
const char *addr;
{
  int i;


  if (recipient)
    if (case_equals(addr,recipient)) _exit(0);

  if (!recipient)
    for (i = 0;recips[i];++i)
      if (case_equals(addr,recips[i])) _exit(0);
}

int main(argc,argv)
int argc;
const char * const *argv;
{
  int i;

  recipient = env_get("RECIPIENT");
  recips = argv + 1;
  if (*recips)
		recipient = 0;
	else {
		recipient += str_rchr(recipient, '@');
		if (recipient) ++recipient;
	}

	for (;;) {
		if (getln(buffer_0,&addrlist,&match,'\0') == -1)
			strerr_die2sys(111,FATAL,"unable to read input: ");
		if (!match) break;
		if (addrlist.s[0] == '+') {
			i = str_rchr(addrlist.s,'@');
			if (addrlist.s[i])
				check(addrlist.s + i + 1);
		}
	}

	_exit(100);
}
