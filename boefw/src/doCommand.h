/*
 * doCommand.h
 *
 *  Created on: Jun 13, 2018
 *      Author: luxq
 */

#ifndef SRC_DOCOMMAND_H_
#define SRC_DOCOMMAND_H_
#include "axu_connector.h"

typedef int (*Func)(A_Package *req, A_Package *send);

typedef struct Processor{
	ACmd acmd;
	Func pre_check;
	Func do_func;
}Processor;

Processor* processor_get(ACmd acmd);
int make_package_progress(ACmd cmd, u8 progress, A_Package *p);
int make_response_ack(A_Package *req, ACmd cmd, u8 ack, A_Package *p);
int make_response_error(A_Package *req, ACmd cmd, u8 err_code, char*err_info, int len, A_Package *p);
#endif /* SRC_DOCOMMAND_H_ */
