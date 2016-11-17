/*
 * stu_string.h
 *
 *  Created on: 2016-9-8
 *      Author: Tony Lau
 */

#ifndef STU_STRING_H_
#define STU_STRING_H_

#include <stdio.h>
#include <string.h>


typedef struct {
	size_t      len;
	u_char     *data;
} stu_str_t;

#define stu_string(str)     { sizeof(str) - 1, (u_char *) str }
#define stu_null_string     { 0, NULL }
#define stu_str_set(str, text) \
    (str)->len = sizeof(text) - 1; (str)->data = (u_char *) text
#define stu_str_null(str)   (str)->len = 0; (str)->data = NULL

#define stu_tolower(c)      (u_char) ((c >= 'A' && c <= 'Z') ? (c | 0x20) : c)
#define stu_toupper(c)      (u_char) ((c >= 'a' && c <= 'z') ? (c & ~0x20) : c)

#define stu_strlen(s)       strlen((const char *) s)

void stu_strlow(u_char *dst, u_char *src, size_t n);
u_char *stu_strlchr(u_char *p, u_char *last, u_char c);
void *stu_memzero(void *block, size_t n);

#define stu_memcpy(dst, src, n) (((u_char *) memcpy(dst, src, n)) + (n))

u_char *stu_strncpy(u_char *dst, u_char *src, size_t n);

stu_int_t stu_printf(const char *fmt, ...);
u_char *stu_sprintf(u_char *s, const char *fmt, ...);

stu_int_t stu_vprintf(const char *fmt, va_list args);
u_char *stu_vsprintf(u_char *s, const char *fmt, va_list args);

#endif /* STU_STRING_H_ */
