/*
 * Copyright 2016-2020 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
 
/**
 * @file    MPU6050_Control.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MK64F12.h"
#include "fsl_debug_console.h"

#include "FXOS8700CQ.h"

/*
 * @brief   Application entry point.
 *
 * uint8_t g_accel_addr_found = 0x00;
 */

uint8_t g_accel_addr_found = 0x00;
int main(void) {

	bool isThereAccelFX = false;
	bool isThereAccelMPU = false;

  	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
  	/* Init FSL debug console. */
    BOARD_InitDebugConsole();

    // Inicializo el acelerómetro de la placa
    PRINTF("Inicializando acelerómetro...");
    FXOS8700CQ_Init();
    MPU6050_Init();
    PRINTF("Hecho.\n");

    isThereAccelFX = FXOS8700CQ_ReadSensorWhoAmI();
    FXOS8700CQ_Configure_Device();

    isThereAccelMPU = MPU6050_ReadSensorWhoAmI();


    if (isThereAccelFX)
    {
    	uint8_t status0_value = 0;
		uint8_t readBuff[7];
		int16_t x, y, z;
		int16_t a_xyz[3];
		int16_t m_xyz[3];

		while(1)
		{
			status0_value = 0;
			while (status0_value != 0xff)
			{
				I2C_ReadAccelRegs(I2C0, FXOS8700CQ_DEVICE_ADDRESS, FXOS8700CQ_STATUS, &status0_value, 1);
			}

			status0_value = FXOS8700CQ_Read_Accel(I2C0, FXOS8700CQ_DEVICE_ADDRESS, a_xyz);

			status0_value = FXOS8700CQ_Read_Magnet(I2C0, FXOS8700CQ_DEVICE_ADDRESS, m_xyz);


			PRINTF("status_reg = 0x%x , x = %5d , y = %5d , z = %5d \r\n", status0_value, x, y, z);
		}
    }

    return 0 ;
}
