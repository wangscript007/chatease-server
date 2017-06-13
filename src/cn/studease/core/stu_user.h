/*
 * stu_user.h
 *
 *  Created on: 2016-9-28
 *      Author: Tony Lau
 */

#ifndef STU_USER_H_
#define STU_USER_H_

#include "stu_config.h"
#include "stu_core.h"

#define STU_USER_ID_MAX_LEN     16

#define STU_USER_ROLE_VISITOR   0x00
#define STU_USER_ROLE_NORMAL    0x01
#define STU_USER_ROLE_VIP       0x0E
#define STU_USER_ROLE_ASSISTANT 0x10
#define STU_USER_ROLE_SECRETARY 0x20
#define STU_USER_ROLE_ANCHOR    0x30
#define STU_USER_ROLE_ADMIN     0x40
#define STU_USER_ROLE_SU_ADMIN  0x80
#define STU_USER_ROLE_SYSTEM    0xC0

typedef struct {
	uint8_t     code;
	stu_uint_t  time;
} stu_punishment_t;

typedef struct {
	stu_str_t         id;
	stu_str_t         name;
	uint8_t           role;

	stu_short_t       interval;
	stu_uint_t        active;
	stu_punishment_t  punishment;

	stu_channel_t    *channel;
} stu_user_t;

stu_int_t stu_user_init(stu_user_t *usr, stu_str_t *id, stu_str_t *name, stu_base_pool_t *pool);

#endif /* STU_USER_H_ */
