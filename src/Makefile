# Don't edit Makefile!  Use conf-* for configuration.

SHELL=/bin/sh

default: it

clean:
	rm -f 822addr 822addr.o 822body 822body.o 822bodyfilter 822bodyfilter.o \
	822fields 822fields.o 822headerfilter 822headerfilter.o 822headerok \
	822headerok.o 822headers 822headers.o alloc.o alloc_re.o auto-str \
	auto-str.o auto_qmail.c auto_qmail.o buffer.o buffer_0.o buffer_1.o \
	buffer_2.o buffer_copy.o buffer_get.o buffer_put.o buffer_read.o \
	buffer_write.o byte_chr.o byte_copy.o byte_cr.o byte_diff.o case_diffb.o \
	case_diffs.o case_startb.o checkaddr checkaddr.o checkdomain \
	checkdomain.o choose compile condtomaildir condtomaildir.o constmap.o \
	env.o error.o error_str.o error_temp.o fd_copy.o fd_move.o fmt_str.o \
	fmt_strn.o fmt_ulong.o fork.h getconf.o getln.o getln2.o hassgact.h \
	haswaitp.h ifaddr ifaddr.o iftoccfrom iftoccfrom.o it load makelib \
	mess822_addr.o mess822_line.o mess822_ok.o mess822_token.o \
	mess822_when.o now.o open_excl.o open_read.o openreadclose.o \
	pathexec_env.o pathexec_run.o qmail.o readclose.o replier replier.o \
	scan_long.o scan_sign.o scan_ulong.o seek_cur.o seek_set.o sgetopt.o \
	sig.o sig_catch.o str_chr.o str_cpy.o str_diff.o str_len.o str_rchr.o \
	str_start.o stralloc_cat.o stralloc_catb.o stralloc_cats.o \
	stralloc_copy.o stralloc_eady.o stralloc_opyb.o stralloc_opys.o \
	stralloc_pend.o strerr_die.o strerr_sys.o subgetopt.o sysdeps systype \
	tomaildir tomaildir.o unix.a wait_pid.o

822addr: load 822addr.o unix.a
	./load 822addr unix.a 

822addr.o: compile 822addr.c buffer.h strerr.h getln.h mess822.h case.h \
stralloc.h exit.h alloc.h sgetopt.h str.h buffer.h stralloc.h stralloc.h \
caltime.h gen_alloc.h subgetopt.h gen_alloc.h gen_alloc.h caldate.h
	./compile 822addr.c

822body: load 822body.o unix.a
	./load 822body unix.a 

822body.o: compile 822body.c buffer.h strerr.h error.h fd.h getln.h \
mess822.h exit.h buffer.h stralloc.h stralloc.h caltime.h gen_alloc.h \
gen_alloc.h caldate.h
	./compile 822body.c

822bodyfilter: load 822bodyfilter.o unix.a
	./load 822bodyfilter unix.a 

822bodyfilter.o: compile 822bodyfilter.c exit.h error.h strerr.h buffer.h \
getln.h mess822.h fd.h seek.h pathexec.h buffer.h stralloc.h stralloc.h \
caltime.h gen_alloc.h gen_alloc.h caldate.h
	./compile 822bodyfilter.c

822fields: load 822fields.o unix.a
	./load 822fields unix.a 

822fields.o: compile 822fields.c buffer.h strerr.h getln.h mess822.h \
case.h stralloc.h exit.h alloc.h buffer.h stralloc.h stralloc.h caltime.h \
gen_alloc.h gen_alloc.h gen_alloc.h caldate.h
	./compile 822fields.c

822headerfilter: load 822headerfilter.o unix.a
	./load 822headerfilter unix.a 

822headerfilter.o: compile 822headerfilter.c exit.h error.h fork.h wait.h \
strerr.h buffer.h getln.h mess822.h fd.h pathexec.h sig.h buffer.h \
stralloc.h stralloc.h caltime.h gen_alloc.h gen_alloc.h caldate.h
	./compile 822headerfilter.c

822headerok: load 822headerok.o unix.a
	./load 822headerok unix.a 

822headerok.o: compile 822headerok.c buffer.h error.h getln.h mess822.h \
exit.h buffer.h stralloc.h stralloc.h caltime.h gen_alloc.h gen_alloc.h \
caldate.h
	./compile 822headerok.c

822headers: load 822headers.o unix.a
	./load 822headers unix.a 

822headers.o: compile 822headers.c buffer.h strerr.h getln.h mess822.h \
case.h stralloc.h exit.h alloc.h buffer.h stralloc.h stralloc.h caltime.h \
gen_alloc.h gen_alloc.h gen_alloc.h caldate.h
	./compile 822headers.c

alloc.o: compile alloc.c alloc.h error.h
	./compile alloc.c

alloc_re.o: compile alloc_re.c alloc.h byte.h
	./compile alloc_re.c

auto-str: load auto-str.o unix.a
	./load auto-str unix.a 

auto-str.o: compile auto-str.c buffer.h exit.h
	./compile auto-str.c

auto_qmail.c: auto-str conf-qmail
	./auto-str auto_qmail "`head -1 conf-qmail`" > auto_qmail.c

auto_qmail.o: compile auto_qmail.c
	./compile auto_qmail.c

buffer.o: compile buffer.c buffer.h
	./compile buffer.c

buffer_0.o: compile buffer_0.c buffer.h
	./compile buffer_0.c

buffer_1.o: compile buffer_1.c buffer.h
	./compile buffer_1.c

buffer_2.o: compile buffer_2.c buffer.h
	./compile buffer_2.c

buffer_copy.o: compile buffer_copy.c buffer.h
	./compile buffer_copy.c

buffer_get.o: compile buffer_get.c buffer.h byte.h error.h
	./compile buffer_get.c

buffer_put.o: compile buffer_put.c buffer.h str.h byte.h error.h
	./compile buffer_put.c

buffer_read.o: compile buffer_read.c buffer.h
	./compile buffer_read.c

buffer_write.o: compile buffer_write.c buffer.h
	./compile buffer_write.c

byte_chr.o: compile byte_chr.c byte.h
	./compile byte_chr.c

byte_copy.o: compile byte_copy.c byte.h
	./compile byte_copy.c

byte_cr.o: compile byte_cr.c byte.h
	./compile byte_cr.c

byte_diff.o: compile byte_diff.c byte.h
	./compile byte_diff.c

case_diffb.o: compile case_diffb.c case.h
	./compile case_diffb.c

case_diffs.o: compile case_diffs.c case.h
	./compile case_diffs.c

case_startb.o: compile case_startb.c case.h
	./compile case_startb.c

checkaddr: load checkaddr.o unix.a
	./load checkaddr unix.a 

checkaddr.o: compile checkaddr.c buffer.h strerr.h getln.h mess822.h \
case.h env.h exit.h buffer.h stralloc.h stralloc.h caltime.h gen_alloc.h \
gen_alloc.h caldate.h
	./compile checkaddr.c

checkdomain: load checkdomain.o unix.a
	./load checkdomain unix.a 

checkdomain.o: compile checkdomain.c buffer.h strerr.h getln.h mess822.h \
case.h env.h exit.h str.h buffer.h stralloc.h stralloc.h caltime.h \
gen_alloc.h gen_alloc.h caldate.h
	./compile checkdomain.c

choose: home warn-auto.sh choose.sh
	rm -f choose
	cat warn-auto.sh choose.sh \
	| sed s}HOME}"`head -1 home`"}g \
	> choose
	chmod 755 choose

compile: conf-cc print-cc.sh systype warn-auto.sh
	rm -f compile
	sh print-cc.sh > compile
	chmod 755 compile

condtomaildir: load condtomaildir.o unix.a
	./load condtomaildir unix.a 

condtomaildir.o: compile condtomaildir.c sig.h sig.h byte.h exit.h open.h \
buffer.h strerr.h error.h fmt.h env.h str.h fork.h wait.h seek.h now.h \
env.h pathexec.h datetime.h
	./compile condtomaildir.c

constmap.o: compile constmap.c constmap.h alloc.h case.h
	./compile constmap.c

env.o: compile env.c str.h env.h
	./compile env.c

error.o: compile error.c error.h
	./compile error.c

error_str.o: compile error_str.c error.h
	./compile error_str.c

error_temp.o: compile error_temp.c error.h
	./compile error_temp.c

fd_copy.o: compile fd_copy.c fd.h
	./compile fd_copy.c

fd_move.o: compile fd_move.c fd.h
	./compile fd_move.c

fmt_str.o: compile fmt_str.c fmt.h
	./compile fmt_str.c

fmt_strn.o: compile fmt_strn.c fmt.h
	./compile fmt_strn.c

fmt_ulong.o: compile fmt_ulong.c fmt.h
	./compile fmt_ulong.c

fork.h: choose compile load tryvfork.c fork.h1 fork.h2
	./choose cl tryvfork fork.h1 fork.h2 >fork.h

getconf.o: compile getconf.c stralloc.h openreadclose.h strerr.h byte.h \
getconf.h gen_alloc.h stralloc.h gen_alloc.h
	./compile getconf.c

getln.o: compile getln.c byte.h getln.h buffer.h stralloc.h gen_alloc.h
	./compile getln.c

getln2.o: compile getln2.c byte.h getln.h buffer.h stralloc.h gen_alloc.h
	./compile getln2.c

hassgact.h: choose compile trysgact.c hassgact.h1 hassgact.h2
	./choose cl trysgact hassgact.h1 hassgact.h2 > hassgact.h

haswaitp.h: choose compile load trywaitp.c haswaitp.h1 haswaitp.h2
	./choose cl trywaitp haswaitp.h1 haswaitp.h2 >haswaitp.h

ifaddr: load ifaddr.o unix.a
	./load ifaddr unix.a 

ifaddr.o: compile ifaddr.c buffer.h strerr.h getln.h mess822.h case.h \
env.h exit.h stralloc.h alloc.h str.h buffer.h stralloc.h stralloc.h \
caltime.h gen_alloc.h gen_alloc.h gen_alloc.h caldate.h
	./compile ifaddr.c

iftoccfrom: load iftoccfrom.o unix.a
	./load iftoccfrom unix.a 

iftoccfrom.o: compile iftoccfrom.c buffer.h strerr.h getln.h mess822.h \
case.h env.h exit.h buffer.h stralloc.h stralloc.h caltime.h gen_alloc.h \
gen_alloc.h caldate.h
	./compile iftoccfrom.c

it: 822addr 822body 822bodyfilter 822fields 822headerfilter 822headerok \
822headers checkaddr checkdomain condtomaildir ifaddr iftoccfrom replier \
tomaildir sysdeps

load: conf-ld print-ld.sh systype warn-auto.sh
	rm -f load
	sh print-ld.sh > load
	chmod 755 load

makelib: print-ar.sh systype warn-auto.sh
	rm -f makelib
	sh print-ar.sh > makelib
	chmod 755 makelib

mess822_addr.o: compile mess822_addr.c mess822.h str.h stralloc.h \
caltime.h gen_alloc.h caldate.h
	./compile mess822_addr.c

mess822_line.o: compile mess822_line.c mess822.h stralloc.h str.h case.h \
stralloc.h caltime.h gen_alloc.h gen_alloc.h caldate.h
	./compile mess822_line.c

mess822_ok.o: compile mess822_ok.c mess822.h byte.h stralloc.h caltime.h \
gen_alloc.h caldate.h
	./compile mess822_ok.c

mess822_token.o: compile mess822_token.c mess822.h stralloc.h caltime.h \
gen_alloc.h caldate.h
	./compile mess822_token.c

mess822_when.o: compile mess822_when.c mess822.h scan.h stralloc.h case.h \
str.h stralloc.h caltime.h gen_alloc.h gen_alloc.h caldate.h
	./compile mess822_when.c

now.o: compile now.c datetime.h now.h datetime.h
	./compile now.c

open_excl.o: compile open_excl.c open.h
	./compile open_excl.c

open_read.o: compile open_read.c open.h
	./compile open_read.c

openreadclose.o: compile openreadclose.c error.h open.h readclose.h \
openreadclose.h stralloc.h stralloc.h gen_alloc.h gen_alloc.h
	./compile openreadclose.c

pathexec_env.o: compile pathexec_env.c stralloc.h alloc.h str.h byte.h \
env.h pathexec.h gen_alloc.h
	./compile pathexec_env.c

pathexec_run.o: compile pathexec_run.c error.h stralloc.h str.h env.h \
pathexec.h gen_alloc.h
	./compile pathexec_run.c

qmail.o: compile qmail.c buffer.h wait.h exit.h fork.h fd.h qmail.h \
auto_qmail.h pathexec.h buffer.h
	./compile qmail.c

readclose.o: compile readclose.c error.h readclose.h stralloc.h \
gen_alloc.h
	./compile readclose.c

replier: load replier.o unix.a auto_qmail.o
	./load replier unix.a auto_qmail.o 

replier.o: compile replier.c stralloc.h strerr.h error.h qmail.h env.h \
sig.h open.h getln.h case.h scan.h str.h fmt.h exit.h buffer.h getconf.h \
constmap.h fd.h wait.h pathexec.h byte.h gen_alloc.h buffer.h buffer.h \
stralloc.h gen_alloc.h
	./compile replier.c

scan_long.o: compile scan_long.c scan.h
	./compile scan_long.c

scan_sign.o: compile scan_sign.c scan.h
	./compile scan_sign.c

scan_ulong.o: compile scan_ulong.c scan.h
	./compile scan_ulong.c

seek_cur.o: compile seek_cur.c seek.h
	./compile seek_cur.c

seek_set.o: compile seek_set.c seek.h
	./compile seek_set.c

sgetopt.o: compile sgetopt.c buffer.h sgetopt.h subgetopt.h subgetopt.h
	./compile sgetopt.c

sig.o: compile sig.c sig.h
	./compile sig.c

sig_catch.o: compile sig_catch.c sig.h hassgact.h
	./compile sig_catch.c

str_chr.o: compile str_chr.c str.h
	./compile str_chr.c

str_cpy.o: compile str_cpy.c str.h
	./compile str_cpy.c

str_diff.o: compile str_diff.c str.h
	./compile str_diff.c

str_len.o: compile str_len.c str.h
	./compile str_len.c

str_rchr.o: compile str_rchr.c str.h
	./compile str_rchr.c

str_start.o: compile str_start.c str.h
	./compile str_start.c

stralloc_cat.o: compile stralloc_cat.c byte.h stralloc.h gen_alloc.h
	./compile stralloc_cat.c

stralloc_catb.o: compile stralloc_catb.c stralloc.h byte.h gen_alloc.h
	./compile stralloc_catb.c

stralloc_cats.o: compile stralloc_cats.c byte.h str.h stralloc.h \
gen_alloc.h
	./compile stralloc_cats.c

stralloc_copy.o: compile stralloc_copy.c byte.h stralloc.h gen_alloc.h
	./compile stralloc_copy.c

stralloc_eady.o: compile stralloc_eady.c alloc.h stralloc.h \
gen_allocdefs.h gen_alloc.h
	./compile stralloc_eady.c

stralloc_opyb.o: compile stralloc_opyb.c stralloc.h byte.h gen_alloc.h
	./compile stralloc_opyb.c

stralloc_opys.o: compile stralloc_opys.c byte.h str.h stralloc.h \
gen_alloc.h
	./compile stralloc_opys.c

stralloc_pend.o: compile stralloc_pend.c alloc.h stralloc.h \
gen_allocdefs.h gen_alloc.h
	./compile stralloc_pend.c

strerr_die.o: compile strerr_die.c buffer.h strerr.h
	./compile strerr_die.c

strerr_sys.o: compile strerr_sys.c error.h strerr.h
	./compile strerr_sys.c

subgetopt.o: compile subgetopt.c subgetopt.h
	./compile subgetopt.c

sysdeps: systype compile load fork.h hassgact.h haswaitp.h
	rm -f sysdeps
	cat systype compile load >> sysdeps
	grep sysdep fork.h >> sysdeps
	grep sysdep hassgact.h >> sysdeps
	grep sysdep haswaitp.h >> sysdeps

systype: find-systype.sh trycpp.c x86cpuid.c
	sh find-systype.sh > systype

tomaildir: load tomaildir.o unix.a
	./load tomaildir unix.a 

tomaildir.o: compile tomaildir.c sig.h byte.h exit.h open.h buffer.h \
strerr.h error.h fmt.h str.h now.h env.h sgetopt.h datetime.h subgetopt.h
	./compile tomaildir.c

unix.a: makelib openreadclose.o getconf.o qmail.o alloc.o alloc_re.o \
buffer.o buffer_0.o buffer_1.o buffer_2.o buffer_get.o buffer_put.o \
buffer_read.o buffer_write.o buffer_copy.o fd_move.o fd_copy.o wait_pid.o \
seek_cur.o seek_set.o pathexec_env.o pathexec_run.o byte_chr.o \
byte_copy.o byte_cr.o error.o error_str.o error_temp.o getln.o getln2.o \
sgetopt.o sig.o readclose.o constmap.o open_read.o open_excl.o \
fmt_ulong.o str_rchr.o str_chr.o str_len.o str_cpy.o sig_catch.o \
fmt_str.o now.o str_diff.o fmt_strn.o byte_diff.o case_startb.o \
case_diffb.o case_diffs.o env.o str_start.o stralloc_cat.o \
stralloc_cats.o stralloc_catb.o stralloc_eady.o stralloc_opyb.o \
stralloc_opys.o stralloc_pend.o stralloc_copy.o scan_ulong.o scan_long.o \
scan_sign.o strerr_die.o strerr_sys.o subgetopt.o mess822_ok.o \
mess822_line.o mess822_addr.o mess822_token.o mess822_when.o
	./makelib unix.a openreadclose.o getconf.o qmail.o alloc.o alloc_re.o \
	buffer.o buffer_0.o buffer_1.o buffer_2.o buffer_get.o buffer_put.o \
	buffer_read.o buffer_write.o buffer_copy.o fd_move.o fd_copy.o \
	wait_pid.o seek_cur.o seek_set.o pathexec_env.o pathexec_run.o \
	byte_chr.o byte_copy.o byte_cr.o error.o error_str.o error_temp.o \
	getln.o getln2.o sgetopt.o sig.o readclose.o constmap.o open_read.o \
	open_excl.o fmt_ulong.o str_rchr.o str_chr.o str_len.o str_cpy.o \
	sig_catch.o fmt_str.o now.o str_diff.o fmt_strn.o byte_diff.o \
	case_startb.o case_diffb.o case_diffs.o env.o str_start.o stralloc_cat.o \
	stralloc_cats.o stralloc_catb.o stralloc_eady.o stralloc_opyb.o \
	stralloc_opys.o stralloc_pend.o stralloc_copy.o scan_ulong.o scan_long.o \
	scan_sign.o strerr_die.o strerr_sys.o subgetopt.o mess822_ok.o \
	mess822_line.o mess822_addr.o mess822_token.o mess822_when.o

wait_pid.o: compile wait_pid.c error.h haswaitp.h
	./compile wait_pid.c
