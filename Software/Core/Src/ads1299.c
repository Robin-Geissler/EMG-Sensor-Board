// ADS1299.c
#include "ads1299.h"
  
SPI_HandleTypeDef *hspi_ads1299;
GPIO_TypeDef *spi_ncs_port_ads1299;
uint16_t spi_ncs_pin_ads1299;

uint8_t sendDataBuff[32];
uint8_t readDataBuff[32];
int32_t debugData[200];
int32_t debugData2[200];
uint32_t debugData3[200];
uint32_t debugData4[200];
int iDebug = 0;
 
 
 
void ADS1299_WriteRegister(uint8_t reg, uint8_t value) {
    sendDataBuff[0] = WREG | reg;
		sendDataBuff[1] = 0x00;
		sendDataBuff[2] = value;
    HAL_GPIO_WritePin(spi_ncs_port_ads1299, spi_ncs_pin_ads1299, GPIO_PIN_RESET);
		HAL_SPI_Transmit_DMA(hspi_ads1299, sendDataBuff, 3);
		HAL_Delay(100);
		
}
 
uint8_t ADS1299_ReadRegister(uint8_t reg) {
		/* send Read Command */
		sendDataBuff[0] = RREG | reg;
		sendDataBuff[1] = 0x00;
		sendDataBuff[2] = 0x00;
		sendDataBuff[3] = 0x00;
    
		HAL_GPIO_WritePin(spi_ncs_port_ads1299, spi_ncs_pin_ads1299, GPIO_PIN_RESET);
		HAL_SPI_TransmitReceive_DMA(hspi_ads1299, sendDataBuff, readDataBuff, 4);
		HAL_Delay(100);

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
 
 
void ADS1299_Init(SPI_HandleTypeDef *hspi, GPIO_TypeDef *spi_ncs_port, uint16_t spi_ncs_pin,
	GPIO_TypeDef *CLKSEL_GPIOx, uint16_t CLKSEL_GPIO_Pin, bool extCLK, 
	GPIO_TypeDef *NPWDN_GPIOx, uint16_t NPWDN_GPIO_Pin,GPIO_TypeDef *NRESET_GPIOx, uint16_t NRESET_GPIO_Pin) {
		hspi_ads1299 = hspi;
		spi_ncs_port_ads1299 = spi_ncs_port;
		spi_ncs_pin_ads1299 = spi_ncs_pin;
		
		
		
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
		
		/* Set device into SDATAC Mode so that registers can be read and written */
		sendDataBuff[0] = SDATAC;
    HAL_GPIO_WritePin(spi_ncs_port_ads1299, spi_ncs_pin_ads1299, GPIO_PIN_RESET);
		HAL_SPI_Transmit_DMA(hspi_ads1299, sendDataBuff, 1);
		
		/* Activate internal reference and wait to settle */
		//ADS1299_WriteRegister(CONFIG3, 0xE0);
		ADS1299_WriteRegister(CONFIG3, 0xFC);
		

		HAL_Delay(100);
		
		/* Single-shot-mode*/
		//ADS1299_WriteRegister(CONFIG4, 0x08);
		
		/* Configure for test */
		/*
		ADS1299_WriteRegister(CONFIG1, 0xF4);
		ADS1299_WriteRegister(CONFIG2, 0xD0);
		HAL_Delay(100);
		ADS1299_WriteRegister(CH1SET, 0x05);
		ADS1299_WriteRegister(CH2SET, 0x15);
		ADS1299_WriteRegister(CH3SET, 0x25);
		ADS1299_WriteRegister(CH4SET, 0x35);
		ADS1299_WriteRegister(CH5SET, 0x45);
		ADS1299_WriteRegister(CH6SET, 0x55);
		ADS1299_WriteRegister(CH7SET, 0x65);
		ADS1299_WriteRegister(CH8SET, 0x05);
		*/
		
		ADS1299_WriteRegister(CONFIG2, 0xD0);
		
		/* Configure for measurement */
		ADS1299_WriteRegister(CONFIG1, 0xF4);
		//ADS1299_WriteRegister(CONFIG2, 0xC4);
		HAL_Delay(100);
		ADS1299_WriteRegister(CH1SET, 0x60);
		ADS1299_WriteRegister(CH2SET, 0x60);
		ADS1299_WriteRegister(CH3SET, 0x60);
		ADS1299_WriteRegister(CH4SET, 0x60);
		ADS1299_WriteRegister(CH5SET, 0x60);
		ADS1299_WriteRegister(CH6SET, 0x60);
		ADS1299_WriteRegister(CH7SET, 0x60);
		ADS1299_WriteRegister(CH8SET, 0x60);
		
		ADS1299_WriteRegister(BIAS_SENSP, 0x01);
		ADS1299_WriteRegister(BIAS_SENSN, 0x01);
		
		
		HAL_Delay(200);
		debugData[0] = ADS1299_ReadRegister(CH1SET);
		debugData[1] = ADS1299_ReadRegister(CH2SET);
		debugData[2] = ADS1299_ReadRegister(CH3SET);
		debugData[3] = ADS1299_ReadRegister(CH4SET);
		debugData[4] = ADS1299_ReadRegister(CH5SET);
		debugData[5] = ADS1299_ReadRegister(CH6SET);
		debugData[6] = ADS1299_ReadRegister(CH7SET);
		debugData[7] = ADS1299_ReadRegister(CH8SET);
		debugData[8] = ADS1299_ReadRegister(CONFIG1);
		debugData[9] = ADS1299_ReadRegister(MISC1);
		debugData[10] = ADS1299_ReadRegister(MISC1);
}
	

 
void ADS1299_RDATAC() {
  sendDataBuff[0] = RDATAC;
  HAL_GPIO_WritePin(spi_ncs_port_ads1299, spi_ncs_pin_ads1299, GPIO_PIN_RESET);  
	HAL_SPI_Transmit_DMA(hspi_ads1299, sendDataBuff, 1);
}

uint8_t *ADS1299_RDATA(){
	sendDataBuff[0] = RDATA;
	sendDataBuff[1] = 0;
	sendDataBuff[2] = 0;
  HAL_GPIO_WritePin(spi_ncs_port_ads1299, spi_ncs_pin_ads1299, GPIO_PIN_RESET);  
	HAL_SPI_TransmitReceive_DMA(hspi_ads1299, sendDataBuff, readDataBuff, 29);
	return readDataBuff;
}
 
void ADS1299_Convert_Data(uint8_t *input, int32_t *output){

	for(int i = 0; i < 8; i++){
		/* data starts at 4 because first byte is send byte, byte 1,2,3 are status bytes*/
		/* first bit is ingored due to Two´s compliment format*/
		output[i] = ((input[4 + i*3] & 0x7F) << 16) | (input[4+ i*3 + 1] << 8) | (input[4 + i * 3 + 2]);
		/* if first bit was set, substract Val Max to get the right 2´s compliment value*/
		if(input[4 + i*3] >= 0x80){
			output[i] = output[i] - 0x800000;
			}
	}
}




