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

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "valid.h"

typedef struct {
	char*	fname;
	char*	lname;
} User;

static char*
ismin2len(char *s)
{
	return (isminlen(2, s));
}

static char*
ismax128len(char *s)
{
	return (ismaxlen(128, s));
}

static Field*
isfname(const char *input)
{
	Field *res;

	res = validfield("firstname", input,
	    isrequired, ismin2len, ismax128len, NULL);
	return (res);
}

static Field*
islname(const char *input)
{
	Field *res;

	res = validfield("lastname", input,
	    isrequired, ismin2len, ismax128len, NULL);
	return (res);
}

static int
isuser(Valid *v, User *u)
{
	Field *fname, *lname;
	int res;

	fname = isfname(u->fname);
	lname = islname(u->lname);
	res = validinit(v, fname, lname, NULL);
	return (res);
}

int
main(void)
{
	Valid v;
	User u;

	u.fname = "Jose";
	u.lname = "";
	assert(isuser(&v, &u) == 0);
	validfree(&v);
	return (EXIT_SUCCESS);
}
