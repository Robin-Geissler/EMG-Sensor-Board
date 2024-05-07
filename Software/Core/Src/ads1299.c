// ADS1299.c
#include "ads1299.h"
  
SPI_HandleTypeDef hspi_ads1299;
uint8_t sendDataBuff[3];
uint8_t readDataBuff[3];
 
void ADS1299_Init(SPI_HandleTypeDef hspi, GPIO_TypeDef *CLKSEL_GPIOx, uint16_t CLKSEL_GPIO_Pin, bool extCLK, 
	GPIO_TypeDef *NPWDN_GPIOx, uint16_t NPWDN_GPIO_Pin,GPIO_TypeDef *NRESET_GPIOx, uint16_t NRESET_GPIO_Pin) {
		hspi_ads1299 = hspi;
	
		/* set ext CLK Pin */
		if(extCLK){
			HAL_GPIO_WritePin(CLKSEL_GPIOx, CLKSEL_GPIO_Pin, GPIO_PIN_RESET);
		}else{
			HAL_GPIO_WritePin(CLKSEL_GPIOx, CLKSEL_GPIO_Pin, GPIO_PIN_SET);
		}
		
		/* Wait for at least 2^18 cycles = 2^18 * 666ns * 10^-9 = 0.175s*/
		HAL_Delay(200);
		
		/* set ext NPWDN Pin */
		HAL_GPIO_WritePin(NPWDN_GPIOx, NPWDN_GPIO_Pin, GPIO_PIN_SET);
		
		/* set ext NRESET Pin */
		HAL_GPIO_WritePin(NRESET_GPIOx, NRESET_GPIO_Pin, GPIO_PIN_SET);
		
		sendDataBuff[0] = RESET;
		HAL_SPI_Transmit_DMA(&hspi_ads1299, sendDataBuff, 1);
		
		
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
    HAL_SPI_Transmit_DMA(&hspi_ads1299, sendDataBuff, sizeof(sendDataBuff));
}
 
uint8_t ADS1299_ReadRegister(uint8_t reg) {
		/* send Read Command */
		sendDataBuff[0] = RREG | reg;
		sendDataBuff[1] = 0x00;
		sendDataBuff[2] = 0x00;
    
		HAL_SPI_TransmitReceive_DMA(&hspi_ads1299, sendDataBuff, readDataBuff, sizeof(sendDataBuff));
    
		return readDataBuff[2];
}

uint8_t* ReadNRegisters(uint8_t n, uint8_t reg){
		sendDataBuff[0] = RREG | reg;
		sendDataBuff[1] = n;
		sendDataBuff[2] = 0x00;
	
    HAL_SPI_TransmitReceive_DMA(&hspi_ads1299, sendDataBuff, readDataBuff, sizeof(sendDataBuff));
    return readDataBuff;
}