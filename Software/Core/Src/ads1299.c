// ADS1299.c
#include "ads1299.h"
  
SPI_HandleTypeDef *hspi_ads1299;
GPIO_TypeDef *spi_ncs_port_ads1299;
uint16_t spi_ncs_pin_ads1299;

uint8_t sendDataBuff[3];
uint8_t readDataBuff[3];
 
void ADS1299_Init(SPI_HandleTypeDef *hspi, GPIO_TypeDef *spi_ncs_port, uint16_t spi_ncs_pin,
	GPIO_TypeDef *CLKSEL_GPIOx, uint16_t CLKSEL_GPIO_Pin, bool extCLK, 
	GPIO_TypeDef *NPWDN_GPIOx, uint16_t NPWDN_GPIO_Pin,GPIO_TypeDef *NRESET_GPIOx, uint16_t NRESET_GPIO_Pin) {
		hspi_ads1299 = hspi;
		spi_ncs_port_ads1299 = spi_ncs_port;
		spi_ncs_pin_ads1299 = spi_ncs_pin;
		
	/***********das ist quark*********	
//		/* set NRESET Pin */
//		HAL_GPIO_WritePin(NRESET_GPIOx, NRESET_GPIO_Pin, GPIO_PIN_SET);
//		/* set SPI CLK Pin */
//		//HAL_GPIO_WritePin(CLKSEL_GPIOx, CLKSEL_GPIO_Pin, GPIO_PIN_SET);
//		*************************/
		
		
		/* set ext CLK Pin */
		if(extCLK){
			HAL_GPIO_WritePin(CLKSEL_GPIOx, CLKSEL_GPIO_Pin, GPIO_PIN_RESET);
		}else{
			HAL_GPIO_WritePin(CLKSEL_GPIOx, CLKSEL_GPIO_Pin, GPIO_PIN_SET);
		}
		
		/* Wait for oscilator to wake up min 2 CLK */
		HAL_Delay(20);
		
		
		/* set NPWDN Pin */
		HAL_GPIO_WritePin(NPWDN_GPIOx, NPWDN_GPIO_Pin, GPIO_PIN_SET);
		
		/* set NRESET Pin */
		HAL_GPIO_WritePin(NRESET_GPIOx, NRESET_GPIO_Pin, GPIO_PIN_SET);
		
		/* Wait for at least 2^18 cycles = 2^18 * 666ns * 10^-9 = 0.175s */
		HAL_Delay(200);
		
		/* send a reset pulse */
		HAL_GPIO_WritePin(NRESET_GPIOx, NRESET_GPIO_Pin, GPIO_PIN_RESET);
		HAL_Delay(2);
		HAL_GPIO_WritePin(NRESET_GPIOx, NRESET_GPIO_Pin, GPIO_PIN_SET);
		
		/* Wait for at least 18 cycles = 18 * 666ns = 12us */
		HAL_Delay(2);
		
		
		/* send ads1299 RESET command */
//		sendDataBuff[0] = RESET;
//		HAL_GPIO_WritePin(spi_ncs_port_ads1299, spi_ncs_pin_ads1299, GPIO_PIN_RESET);
//		HAL_SPI_Transmit_DMA(hspi_ads1299, sendDataBuff, 1);
		// GPIO Reset is done in DMA Interrupt
		
    // z.B. ADS1299_WriteRegister(ADS1299_REG_CONFIG1, 0x96);
}
 
void ADS1299_ReadData(uint8_t* buffer) {
    // Lesen Sie hier die Daten vom ADS1299
    // z.B. HAL_SPI_Receive(&ADS1299_SPI_HANDLE, buffer, 1, HAL_MAX_DELAY);
}
 
void ADS1299_WriteRegister(uint8_t reg, uint8_t value) {
    sendDataBuff[0] = WREG | reg;
		sendDataBuff[1] = 0x00;
		sendDataBuff[2] = value;
    HAL_GPIO_WritePin(spi_ncs_port_ads1299, spi_ncs_pin_ads1299, GPIO_PIN_RESET);
		HAL_SPI_Transmit_DMA(hspi_ads1299, sendDataBuff, 3);
}
 
uint8_t ADS1299_ReadRegister(uint8_t reg) {
		/* send Read Command */
		sendDataBuff[0] = RREG | reg;
		sendDataBuff[1] = 0x00;
		sendDataBuff[2] = 0x00;
    
		HAL_GPIO_WritePin(spi_ncs_port_ads1299, spi_ncs_pin_ads1299, GPIO_PIN_RESET);
		HAL_SPI_TransmitReceive_DMA(hspi_ads1299, sendDataBuff, readDataBuff, sizeof(sendDataBuff));
    
		return readDataBuff[2];
}

uint8_t* ReadNRegisters(uint8_t n, uint8_t reg){
		sendDataBuff[0] = RREG | reg;
		sendDataBuff[1] = n;
		sendDataBuff[2] = 0x00;
	
		HAL_GPIO_WritePin(spi_ncs_port_ads1299, spi_ncs_pin_ads1299, GPIO_PIN_RESET);
    HAL_SPI_TransmitReceive_DMA(hspi_ads1299, sendDataBuff, readDataBuff, sizeof(sendDataBuff));
    return readDataBuff;
}

