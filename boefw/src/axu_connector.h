// Copyright 2018 The go-hpb Authors
// This file is part of the go-hpb.
//
// The go-hpb is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// The go-hpb is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with the go-hpb. If not, see <http://www.gnu.org/licenses/>.

#ifndef AXU_CONNECTOR_H
#define AXU_CONNECTOR_H
#include <xil_types.h>


#define PACKAGE_MAX_SIZE 	(2048)   // 2KB
#define PACKAGE_MIN_SIZE 	(100)

#define AXU_MAGIC_START (0xaacc)
#define AXU_MAGIC_END   (0xccaa)

typedef struct A_PACKAGE_HEADER {
    uint16_t magic_aacc;
    uint16_t package_id;
    uint16_t body_length;
    uint8_t  acmd;
    uint8_t  reserved;
    uint16_t magic_ccaa;
}A_Package_Header;

typedef struct A_PACKAGE{
    A_Package_Header header;
    uint32_t    checksum;
    uint8_t     data[];
}A_Package;

typedef enum A_Error{
    A_ERROR_START,
	A_UNKNOWN_CMD,
    A_MAGIC_ERROR,
    A_CHECKSUM_ERROR,
	A_ENV_UPDATE_ERROR,
    A_STA_USAGE_ERROR,
    A_MID_UID_NOT_FOUND,
    A_FIN_CHECKSUM_ERROR,
    A_STA_LEN_ERROR,
    A_MID_LEN_ERROR, // datalen + offset > totallen
    A_UPGRADE_IS_ABORT,
	A_UPGRADE_STATE_ERROR, // when get upgrade start command, current flag is not recv_finish.
    A_UPGRADE_FLASH_ERASE_ERROR,
    A_UPGRADE_FLASH_WRITE_ERROR,
    A_UPGRADE_ABORT_ERROR,
	A_VERSION_ERROR,
    A_ERROR_END,
}A_Error;
const char *gAErrorMsg[A_ERROR_END];


typedef enum A_CMD {
    ACMD_START = 0x0,
    ACMD_PB_GET_VERSION_INFO    = 0x01,
    ACMD_PB_TRANSPORT_START     = 0x02,
    ACMD_PB_TRANSPORT_MIDDLE    = 0x03,
    ACMD_PB_TRANSPORT_FINISH    = 0x04,
    ACMD_PB_UPGRADE_START       = 0x05,
    ACMD_PB_UPGRADE_ABORT       = 0x06,
    ACMD_PB_RESET               = 0x07,
    ACMD_PB_GET_RANDOM          = 0x08,
    ACMD_PB_GET_BOEID           = 0x09,
    ACMD_PB_GET_HW_VER          = 0x0A,
    ACMD_PB_GET_FW_VER          = 0x0B,
    ACMD_PB_GET_AXU_VER         = 0x0C,
    ACMD_PB_SET_BOEID           = 0x0D,

	ACMD_PB_CHECK_BIND			= 0x0E,
	ACMD_PB_BIND_ID				= 0x0F,
	ACMD_PB_BIND_ACCOUNT		= 0x10,
	ACMD_PB_HW_SIGN				= 0x11,


    ACMD_BP_RES_ACK             = 0x51,
    ACMD_BP_RES_ERR             = 0x52,
    ACMD_BP_RES_UPGRADE_PROGRESS= 0x53,

    ACMD_END                    = 0xff,
}ACmd;

A_Package* axu_package_new(int len);
int axu_package_free(A_Package* pack);

void axu_package_init(A_Package *pack, A_Package* req, ACmd cmd);

int axu_set_data(A_Package *pack, int offset, u8 *data, int len);

void axu_finish_package(A_Package *pack);

char *axu_get_error_msg(A_Error ecode);





#endif  /*AXU_CONNECTOR_H*/