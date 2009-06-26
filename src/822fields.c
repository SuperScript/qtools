#include "buffer.h"
#include "strerr.h"
#include "getln.h"
#include "mess822.h"
#include "case.h"
#include "stralloc.h"
#include "exit.h"
#include "alloc.h"

#define FATAL "822fields: fatal: "

void nomem()
{
  strerr_die2x(111,FATAL,"out of memory");
}

int flag;
stralloc value = {0};

mess822_header h = MESS822_HEADER;
mess822_action *a;
mess822_action a0[] = {
  { "subject", &flag, 0, &value, 0, 0 }
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
		a1[i].value = &value;
		a1[i].addr = 0;
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
	a = init(argc - 1, ++argv);

  if (!mess822_begin(&h,a)) nomem();

  for (;;) {
    if (getln(buffer_0,&line,&match,'\n') == -1)
      strerr_die2sys(111,FATAL,"unable to read input: ");

    if (!mess822_ok(&line)) break;
    if (!mess822_line(&h,&line)) nomem();
    if (!match) break;
  }

  if (!mess822_end(&h)) nomem();

  buffer_putflush(buffer_1,value.s,value.len);

  _exit(flag ? 0 : 100);
}
