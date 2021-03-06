/*
 ============================================================================
 Name        : chatease-server.c
 Author      : Tony Lau
 Version     : 1.x.xx
 Copyright   : studease.cn
 Description : Websocket chat server.
 ============================================================================
 */

#include "cn/studease/core/stu_config.h"
#include "cn/studease/core/stu_core.h"
#include <stdio.h>
#include <stdlib.h>

extern stu_cycle_t *stu_cycle;
extern stu_str_t    STU_CONF_FILE_DEFAULT_PATH;


int main(int argc, char **argv) {
	int           arg;
	char          val;
	stu_config_t  cf;

	stu_time_init();
	stu_config_default(&cf);

	while ((arg = getopt(argc, argv, ":m:p:w:t:c:")) != -1) {
		switch (arg) {
		case 'e':
			cf.edition = stu_utils_get_edition((u_char *) optarg, strlen(optarg));
			stu_log_debug(0, "Edition: %s", optarg);
			break;
		case 'p':
			cf.port = atoi(optarg);
			stu_log_debug(0, "Port: %s", optarg);
			break;
		case 'w':
			cf.worker_processes = atoi(optarg);
			stu_log_debug(0, "Worker_processes: %s", optarg);
			break;
		case 't':
			cf.worker_threads = atoi(optarg);
			stu_log_debug(0, "Worker_threads: %s", optarg);
			break;
		case '?':
			val = optopt;
			stu_log_error(0, "Illegal argument \"%d\", ignored.", val);
			break;
		case ':':
			stu_log_error(0, "Required parameter not found!");
			break;
		}
	}

	if (stu_strerror_init() == STU_ERROR) {
		stu_log_error(0, "Failed to init error strings.");
		return EXIT_FAILURE;
	}

	if (stu_log_init(&cf.log) == STU_ERROR) {
		stu_log_error(0, "Failed to init log file.");
		return EXIT_FAILURE;
	}

	stu_log("GCC " __VERSION__);
	stu_log(__NAME "/" __VERSION " (" __DATE__ " " __TIME__ ")");

	stu_cycle = stu_cycle_create(&cf);
	if (stu_cycle == NULL) {
		stu_log_error(0, "Failed to init cycle.");
		return EXIT_FAILURE;
	}

	if (stu_conf_file_parse(&stu_cycle->config, STU_CONF_FILE_DEFAULT_PATH.data) == STU_ERROR) {
		stu_log_error(0, "Failed to parse configure file.");
		return EXIT_FAILURE;
	}

	if (stu_pidfile_create(&stu_cycle->config.pid) == STU_ERROR) {
		stu_log_error(0, "Failed to create pid file: %s.", stu_cycle->config.pid.name.data);
		return EXIT_FAILURE;
	}

	if (stu_flash_add_listen(&stu_cycle->config) == STU_ERROR) {
		stu_log_error(0, "Failed to add flash listen.");
	}

	if (stu_http_add_listen(&stu_cycle->config) == STU_ERROR) {
		stu_log_error(0, "Failed to add http listen.");
		return EXIT_FAILURE;
	}

	stu_process_start_worker_processes(stu_cycle);
	stu_process_master_cycle(stu_cycle);

	return EXIT_SUCCESS;
}
