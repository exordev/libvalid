PREFIX?=	${DESTDIR}/usr/local
INCDIR=		${PREFIX}/include
LIBDIR=		${PREFIX}/lib

CFLAGS=		-O2 -g -W -Wall -Wextra -Werror -pedantic -ansi

all: libvalid.so libvalid.a

.SUFFIXES: .c .o
.c.o:
	${CC} ${CFLAGS} -o $@ -c $<

libvalid.so: valid.o pred.o
	${CC} ${CFLAGS} -fPIC -shared -o $@ valid.o pred.o

libvalid.a: valid.o pred.o
	ar rcs libvalid.a valid.o pred.o

example: example.o libvalid.a
	${CC} ${CFLAGS} -I. -o $@ example.o -static -pie -L. -lvalid

install: all
	mkdir -p ${INCDIR} ${LIBDIR}
	cp -p valid.h ${INCDIR}
	cp -p libvalid.{so,a} ${LIBDIR}

uninstall:
	rm -f ${INCDIR}/valid.h ${LIBDIR}/libvalid.{so,a}

clean:
	rm -f *.{o,a,so,gch,core,out} example

.PHONY: all install uninstall clean
