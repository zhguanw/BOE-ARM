/*
 * golden.c: jump boot image.
 *
 * This application configures UART 16550 to baud rate 9600.
 * PS7 UART (Zynq) is not initialized by this application, since
 * bootrom/bsp configures it to baud rate 115200
 *
 * ------------------------------------------------
 * | UART TYPE   BAUD RATE                        |
 * ------------------------------------------------
 *   uartns550   9600
 *   uartlite    Configurable only in HW design
 *   ps7_uart    115200 (configured by bootrom/bsp)
 */

#include <stdio.h>
#include "platform.h"
#include "xplatform_info.h"
#include "xil_printf.h"
#include "xil_io.h"
#include "xparameters.h"
#include "xil_types.h"
#include "xstatus.h"
#include "xqspipsu.h"
#include "multiboot.h"
#include "sleep.h"
#include "flash_map.h"
#include "env.h"

static void doMultiBoot()
{
    int status = 0;
    status = env_init();
    if(status != XST_SUCCESS){
        printf("env_init failed.\n");
        return -1;
    }
    EnvContent env;
    status = env_get(&env);
    if(status != XST_SUCCESS) {
        printf("env_get failed.\n");
        return -1;
    }
    FPartation fp1, fp2;
    FM_GetPartation(FM_IMAGE1_PNAME, &fp1);
    FM_GetPartation(FM_IMAGE2_PNAME, &fp2);
    if(env.bootaddr != fp1.pAddr && env.bootaddr != fp2.pAddr){
    	env.bootaddr = fp1.pAddr;
        env_update(&env);
        GoMultiBoot(fp1.pAddr/0x8000);
    }
    GoMultiBoot(env.bootaddr/0x8000);
}

int main()
{

    init_platform();
    //doMultiBoot();
    xil_printf("This is Golden.\r\n");

    extern void runtest();
    runtest();


    cleanup_platform();
    return 0;
}
