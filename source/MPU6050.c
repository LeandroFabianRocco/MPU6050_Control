/*
 * MPU6050.c
 *
 *  Created on: 1 feb. 2020
 *      Author: leandro
 */



#include "MPU6050.h"

volatile bool MPU6050_nakFlag        = false;
volatile bool MPU6050_completionFlag = false;
i2c_master_handle_t mpu_g_m_handle;

void MPU6050_Init(void)
{
	I2C_MasterTransferCreateHandle(I2C1, &mpu_g_m_handle, MPU6050_i2c_master_callback, NULL);
}


void MPU6050_i2c_master_callback(I2C_Type *base, i2c_master_handle_t *handle, status_t status, void *userData)
{
    /* Signal transfer success when received success status. */
    if (status == kStatus_Success)
    {
        MPU6050_completionFlag = true;
    }
    /* Signal transfer success when received success status. */
    if ((status == kStatus_I2C_Nak) || (status == kStatus_I2C_Addr_Nak))
    {
        MPU6050_nakFlag = true;
    }
}



bool MPU6050_ReadSensorWhoAmI(void)
{
	// Definición de variables
	uint8_t who_am_i_reg          = MPU6050_WHO_AM_I;	// Dirección del registro
	uint8_t who_am_i_value        = 0x00;					// Valor devuelto
	bool find_device              = false;					// Flag de dispositivo encontrado
	i2c_master_transfer_t masterXfer;
	memset(&masterXfer, 0, sizeof(masterXfer));

	// START + Slave_address (write_bit); Reg_address
	masterXfer.slaveAddress   = FXOS8700CQ_DEVICE_ADDRESS;	// Envío la dirección del dispositivo
	masterXfer.direction      = kI2C_Write;					// Operación de escritura
	masterXfer.subaddress     = 0;
	masterXfer.subaddressSize = 0;
	masterXfer.data           = &who_am_i_reg;				// Dirección del registro WHO_AM_I
	masterXfer.dataSize       = 1;
	masterXfer.flags          = kI2C_TransferNoStopFlag;
	I2C_MasterTransferNonBlocking(I2C0, &g_m_handle, &masterXfer);

	// Espero a que la transmisión se complete
	while ((!nakFlag) && (!completionFlag)){}
	nakFlag = false;

	if (completionFlag == true)
	{
		completionFlag     = false;
		find_device        = true;
	}
	/*else
	{
		PRINTF("No se pudo conectar con el dispositivo.");
	}*/

	if (find_device == true)
	{
		// START + Slave_address (read_bit); recibo dato
		masterXfer.direction      = kI2C_Read;
		masterXfer.subaddress     = 0;
		masterXfer.subaddressSize = 0;
		masterXfer.data           = &who_am_i_value;
		masterXfer.dataSize       = 1;
		masterXfer.flags          = kI2C_TransferRepeatedStartFlag;
		I2C_MasterTransferNonBlocking(I2C0, &g_m_handle, &masterXfer);

		// Espero a que la transmisión se complete
		while ((!nakFlag) && (!completionFlag)){}
		nakFlag = false;
	}

	completionFlag = false;
	if (who_am_i_value == FXOS8700_WHOAMI_VALUE)
	{
		//PRINTF("Conexión con FXOS8700CQ establecida, la dirección del dispositivo es 0x%x . \r\n", masterXfer.slaveAddress);
		return true;
	}
	else
	{
		return false;
	}
}


