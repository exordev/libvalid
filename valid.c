/*
 * Copyright (c) 2024 Jose G Perez Taveras <josegpt27@gmail.com>
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS.  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include "valid.h"

int
validinit(Valid *v, ...)
{
	Field *f;
	va_list ap;

	v->head = NULL;
	v->tail = &v->head;
	v->n    = 0;
	va_start(ap, v);
	while ((f = va_arg(ap, Field *))) {
		*v->tail = f;
		v->tail = &f->next;
		v->n += f->n;
	}
	va_end(ap);
	return (v->n == 0);
}

void
validfree(Valid *v)
{
	Field *f, *t;
	Msg *m, *tm;

	for (f = v->head; f && (t = f->next, 1); f = t) {
		for (m = f->head; m && (tm = m->next, 1); m = tm) {
			free(m->text);
			free(m);
		}
		free(f->name);
		free(f);
	}
}

Field*
validfind(Valid *v, const char *name)
{
	Field *f;

	for (f = v->head; f; f = f->next)
		if (strcmp(name, f->name) == 0)
			return (f);
	return (NULL);
}

Msg*
newmsg(char *s)
{
	Msg *m;

	m = malloc(sizeof(*m));
	m->text = strdup(s);
	m->next = NULL;
	return (m);
}

Field*
validfield(const char *name, const char *input, ...)
{
	Field *f;
	Msg *m;
	Predicate p;
	va_list ap;
	char *s;

	f = malloc(sizeof(*f));
	f->name = strdup(name);
	f->next = NULL;
	f->head = NULL;
	f->tail = &f->head;
	f->n    = 0;
	va_start(ap, input);
	while ((p = va_arg(ap, Predicate))) {
		if ((s = p(input))) {
			m = newmsg(s);
			*f->tail = m;
			f->tail = &m->next;
			++f->n;
		}
	}
	va_end(ap);
	return (f);
}
