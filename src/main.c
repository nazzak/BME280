/**
  ******************************************************************************
  * @file    main.c
  * @author  Taha MENEBHI
  * @version V1.0
  * @date    02-November-2017
  * @brief   Read output values from the Weather click using the i2C protocol..
  ******************************************************************************
*/


#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "i2c.h" // Contain
#include "bme280.h" // This header contains all the driver APIs. Available on Bosch Sensortec Github.

void MspInit;
void user_delay_ms;
int8_t user_i2c_read;
int8_t user_i2c_write;

int main(void)
{
	uint32_t period=1000;
	int8_t stream_sensor_data_forced_mode;


/****I2C mode Initialization****/

	struct bme280_dev dev;
	int8_t rslt = BME280_OK;

	dev.dev_id=BME280_I2C_ADDR_PRIM;
	dev.intf=BME280_I2C_ADDR_PRIM;
	dev.read=user_i2c_read; //PB7 RegA=SDA
	dev.write=user_i2c_write; //PB7=SDA
	dev.delay_ms=HAL_delay(1000); //PB8=SCL

	rslt=bme280_init(&dev);


/****Functions Declaration****/

	int8_t stream_sensor_data_forced_mode(struct bme280_dev *dev)
	{
	    int8_t rslt;
	    uint8_t settings_sel;
	    struct bme280_data comp_data;

	    /* Recommended mode of operation: Indoor navigation */
	    dev->settings.osr_h = BME280_OVERSAMPLING_1X;
	    dev->settings.osr_p = BME280_OVERSAMPLING_16X;
	    dev->settings.osr_t = BME280_OVERSAMPLING_2X;
	    dev->settings.filter = BME280_FILTER_COEFF_16;

	    settings_sel = BME280_OSR_PRESS_SEL | BME280_OSR_TEMP_SEL | BME280_OSR_HUM_SEL | BME280_FILTER_SEL;

	    rslt = bme280_set_sensor_settings(settings_sel, dev);

	    printf("Temperature, Pressure, Humidity\r\n");
	    /* Continuously stream sensor data */
	    while (1) {
	        rslt = bme280_set_sensor_mode(BME280_FORCED_MODE, dev);
	        /* Wait for the measurement to complete and print data @25Hz */
	        dev->delay_ms(40);
	        rslt = bme280_get_sensor_data(BME280_ALL, &comp_data, dev);
	        print_sensor_data(&comp_data);
	    }
	    return rslt;
	}

	void print_sensor_data(struct bme280_data *comp_data)
	{
	#ifdef BME280_FLOAT_ENABLE
	        printf("%0.2f, %0.2f, %0.2f\r\n",comp_data->temperature, comp_data->pressure, comp_data->humidity);
	#else
	        printf("%ld, %ld, %ld\r\n",comp_data->temperature, comp_data->pressure, comp_data->humidity);
	#endif
	}
/*	void user_delay_ms(uint32_t period) //Is it the same as a HAL_Delay ?? can't see it purpose...
	{

	     //Return control or wait, for a period amount of milliseconds

	}
*/
	int8_t user_i2c_read(uint8_t dev_id, uint8_t reg_addr, uint8_t *reg_data, uint16_t len)
	{
	    int8_t rslt = 0; /* Return 0 for Success, non-zero for failure */

	    /*
	     * The parameter dev_id can be used as a variable to store the I2C address of the device
	     */

	    /*
	     * Data on the bus should be like
	     * |------------+---------------------|
	     * | I2C action | Data                |
	     * |------------+---------------------|
	     * | Start      | -                   |
	     * | Write      | (reg_addr)          |
	     * | Stop       | -                   |
	     * | Start      | -                   |
	     * | Read       | (reg_data[0])       |
	     * | Read       | (....)              |
	     * | Read       | (reg_data[len - 1]) |
	     * | Stop       | -                   |
	     * |------------+---------------------|
	     */

	    return rslt;
	}

	int8_t user_i2c_write(uint8_t dev_id, uint8_t reg_addr, uint8_t *reg_data, uint16_t len)
	{
	    int8_t rslt = 0; /* Return 0 for Success, non-zero for failure */

	    /*
	     * The parameter dev_id can be used as a variable to store the I2C address of the device
	     */

	    /*
	     * Data on the bus should be like
	     * |------------+---------------------|
	     * | I2C action | Data                |
	     * |------------+---------------------|
	     * | Start      | -                   |
	     * | Write      | (reg_addr)          |
	     * | Write      | (reg_data[0])       |
	     * | Write      | (....)              |
	     * | Write      | (reg_data[len - 1]) |
	     * | Stop       | -                   |
	     * |------------+---------------------|
	     */

	    return rslt;
	}

	void MspInit(void)
	{
		__HAL_RCC_GPIOA_CLK_ENABLE();
		GPIO_InitTypeDef GPIO_InitStruct;
		GPIO_InitStruct.Pin = GPIO_PIN_7;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;  //Pull Hardware??
		GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
		GPIO_InitStruct.Alternate = GPIO_AF4_I2C1; //p408
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct); //PIN 7 of Register n°A
	}
	for(;;);
}
