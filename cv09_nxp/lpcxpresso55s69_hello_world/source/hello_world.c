/*
 * Copyright (c) 2013 - 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"

#include "fsl_power.h"
#include "string.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/


/*******************************************************************************
 * Prototypes
 ******************************************************************************/
uint32_t DWT1, DWT2;
uint32_t result, x=8, y=5;

char password_stored[20] = "7410";
char input[20];
uint8_t status;

uint32_t strcmp_safe(const char*s1, const char*s2, const uint32_t length)
{
	uint32_t valid = 0;
	uint32_t invalid = 0;
	uint32_t i;

	for (i = 0; i < length ;i++){
		if (s1[i] == s2[i]) {
			valid = valid + 1;
		}
		else {
			invalid = invalid + 1;
		}
	}
	return invalid;

//	if (valid == length){
//		return 0;
//	} else {
//		return 1;
//	}

}
/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * @brief Main function
 */
int main(void)
{
    char ch;

    /* Init board hardware. */
    /* set BOD VBAT level to 1.65V */
POWER_SetBodVbatLevel(kPOWER_BodVbatLevel1650mv, kPOWER_BodHystLevel50mv, false);
    /* attach main clock divide to FLEXCOMM0 (debug console) */
    CLOCK_AttachClk(BOARD_DEBUG_UART_CLK_ATTACH);

    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitDebugConsole();
#if !defined(DONT_ENABLE_FLASH_PREFETCH)
    /* enable flash prefetch for better performance */
    SYSCON->FMCCR |= SYSCON_FMCCR_PREFEN_MASK;
#endif

	//PRINTF("\r\nhello world.\r\n");


	//DWT1 = DWT -> CYCCNT;
	//result = x + y;
	//DWT2 = DWT -> CYCCNT;
	//PRINTF("Cycles in function: %d", DWT2-DWT1);


    /*
	while(1) {
		PRINTF("\r\nEnter password: ");

			SCANF ("%s", input);

			DWT1 = DWT -> CYCCNT;

			result = strcmp(input, password_stored);

			DWT2 = DWT -> CYCCNT;

			PRINTF("\r\nInput: %s", input);

			if(result == 0) {
				PRINTF("\r\nInput correct");
			}
			else {
				PRINTF("\r\nInput invalid");
			}

			PRINTF("\r\nCycles in function: %d", DWT2-DWT1);

	}
	*/

    while(1) {
    	PRINTF("\r\nEnter password: ");
    	SCANF ("%s", input);

    	DWT1 = DWT -> CYCCNT;						//zaciatok merania cycles
    	status = strcmp_safe(input, password_stored, strlen(password_stored));
    	DWT2 = DWT -> CYCCNT;						//koniec merania cycles

		if (status == 0) {
			PRINTF("\r\nInput correct");
		}
		else {
			PRINTF("\r\nInput incorrect");
		}
		PRINTF("\r\nCycles in function: %d", DWT2-DWT1);
    }

}
