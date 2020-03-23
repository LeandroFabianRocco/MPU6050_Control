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
#include "MPU6050.h"
#include "Delays.h"

bool isThereAccelFX = false;
bool isThereAccelMPU = false;

float x_prev = 0, y_prev = 0;
float x_new, y_new;

void PIT_0_IRQHANDLER(void)
{
	/*if (isThereAccelMPU)
	{
		MPU6050_ComplementaryFilterAngles(x_prev, y_prev, 0.02, &x_new, &y_new);
		PRINTF("X = %2.2f , Y = %2.2f, PID_output = %2.3f \r\n", x_new, y_new);
	}*/
	uint8_t status0_value = 0;
	int16_t m_xyz[3];

	status0_value = 0;
	status0_value = FXOS8700CQ_Read_Magnet_Data(I2C0, FXOS8700CQ_DEVICE_ADDRESS, m_xyz);
	PRINTF("mx = %5d , my = %5d , mz = %5d \r\n", m_xyz[0], m_xyz[1], m_xyz[2]);


	PIT_ClearStatusFlags(PIT_PERIPHERAL, kPIT_Chnl_0, kPIT_TimerFlag);
	__DSB();
}


int main(void) {
  	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    SysTick_init();
    BOARD_InitBootPeripherals();
  	/* Init FSL debug console. */
    BOARD_InitDebugConsole();



    // Inicializo el acelerómetro de la placa
    PRINTF("Inicializando acelerómetro...");
    FXOS8700CQ_Init();
    MPU6050_Init();
    PRINTF("Hecho.\n");

    FXOS8700CQ_Configure_Device();
    MPU6050_Configure_Device();

    isThereAccelFX = FXOS8700CQ_ReadSensorWhoAmI();
    isThereAccelMPU = MPU6050_ReadSensorWhoAmI();


    PIT_StartTimer(PIT_PERIPHERAL, PIT_0);



    /*float ref = 0.0;
    float pError = 0.0;
    float iError = 0.0;
    float dError = 0.0;
    float dt = 0.02;
    float prevError = 0.0;
    float pid = 0.0;*/

    while(1)
    {
    	if ((isThereAccelFX) & (isThereAccelMPU))
		{
			//uint8_t status0_value = 0;
			//int16_t m_xyz[3];
			//int16_t a_xyz[3];
			//int16_t g_xyz[3];

			/*status0_value = 0;
			while (status0_value != 0xff)
			{
				FXOS8700CQ_ReadAccelRegs(I2C0, FXOS8700CQ_DEVICE_ADDRESS, FXOS8700CQ_STATUS, &status0_value, 1);
			}*/

			//status0_value = FXOS8700CQ_Read_Magnet_Data(I2C0, FXOS8700CQ_DEVICE_ADDRESS, m_xyz);
    		//MPU6050_Read_Accel_Data(I2C1, MPU6050_DEVICE_ADDRESS_0, a_xyz);
    		//MPU6050_Read_Gyro_Data(I2C1, MPU6050_DEVICE_ADDRESS_0, g_xyz);
    		//PRINTF("ax = %5d , ay = %5d , az = %5d, gx = %5d , gy = %5d , gz = %5d, mx = %5d , my = %5d , mz = %5d \r\n", a_xyz[0], a_xyz[1], a_xyz[2], g_xyz[0], g_xyz[1], g_xyz[2], m_xyz[0], m_xyz[1], m_xyz[2]);
			//PRINTF("mx = %5d , my = %5d , mz = %5d \r\n", m_xyz[0], m_xyz[1], m_xyz[2]);

    		/*float omega[3];
    		float accel[3];
    		MPU6050_GetAngularVelocity(omega);
    		MPU6050_GetgAcceleration(accel);*/

    		//PRINTF("wx = %2.2f , wy = %2.2f , wz = %2.2f, gx = %2.2f , gy = %2.2f , gz = %2.2f \r\n", omega[0], omega[1], omega[2], accel[0], accel[1], accel[2]);
    		/*float roll, pitch;
    		roll = MPU6050_GetXAngle();
    		pitch = MPU6050_GetYAngle();
    		PRINTF("Roll = %2.2f , Pitch = %2.2f \r\n", roll, pitch);*/

    		//SysTick_DelayTicks(20U);
    		//MPU6050_ComplementaryFilterAngles(x_prev, y_prev, 0.02, &x_new, &y_new);
    		/*x_prev = x_new;
    		y_prev = y_new;



    		pError = ref - x_new;
    		iError = iError + pError * dt;
    		dError = pError - prevError;

    		prevError = pError;
    		pid = 1.0*pError + 0.5*iError + 0.3*dError;

    		PRINTF("X = %2.2f , Y = %2.2f, PID_output = %2.3f \r\n", x_new, y_new, pid);*/
    	}
    }




    return 0 ;
}
