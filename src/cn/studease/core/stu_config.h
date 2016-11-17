/*
 * stu_config.h
 *
 *  Created on: 2016-9-8
 *      Author: Tony Lau
 */

#ifndef STU_CONFIG_H_
#define STU_CONFIG_H_

#include <errno.h>
#include <stddef.h>
#include <math.h>
#include <stdint.h>
#include <sys/types.h>
#include <time.h>

typedef signed long         stu_int_t;
typedef unsigned long       stu_uint_t;
typedef unsigned char       stu_bool_t;

#define TRUE                1
#define FALSE               0

#define STU_ALIGNMENT       sizeof(unsigned long)

#define stu_align(d, a)     (((d) + (a - 1)) & ~(a - 1))
#define stu_align_ptr(p, a) \
	(u_char *) (((uintptr_t) (p) + ((uintptr_t) a - 1)) & ~((uintptr_t) a - 1))

#define stu_inline          inline

#endif /* STU_CONFIG_H_ */
