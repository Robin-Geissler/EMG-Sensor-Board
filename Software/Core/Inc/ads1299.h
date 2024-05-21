// ADS1299.h
#ifndef ADS1299_H
#define ADS1299_H
 
#include <stdint.h>

#include "stm32wbxx_hal.h"
#include <stdbool.h>




/* TCLK_MAX = 666ns */
/*********************************************************
 *  ADS1299 SPI Commands
 *********************************************************/
#define WAKEUP 0x02 // Wake-up from standby mode
#define STANDBY 0x04 // Enter standby mode
#define RESET 0x06 // Reset the device
#define START 0x08 // Start and restart (synchronize) conversions
#define STOP 0x0A // Stop conversion

// Data Read Commands
#define RDATAC 0x10 // Enable Read Data Continuous mode (this is default)
#define SDATAC 0x11 // Stop Read Data Continuously mode
#define RDATA 0x12 // Read data by command; supports multiple read back

// Register Read Commands
// For RREG and WREG, you will need to calculate the command based on the register address and count
#define RREG 0x20 // Read registers
#define WREG 0x40 // Write registers

/*********************************************************
 *  ADS1299 Registers
 *********************************************************/

#define ID 0x00
#define CONFIG1 0x01
#define CONFIG2 0x02
#define CONFIG3 0x03
#define LOFF 0x04
#define CH1SET 0x05
#define CH2SET 0x06
#define CH3SET 0x07
#define CH4SET 0x08
#define CH5SET 0x09
#define CH6SET 0x0A
#define CH7SET 0x0B
#define CH8SET 0x0C
#define BIAS_SENSP 0x0D
#define BIAS_SENSN 0x0E
#define LOFF_SENSP 0x0F
#define LOFF_SENSN 0x10
#define LOFF_FLIP 0x11
#define LOFF_STATP 0x12
#define LOFF_STATN 0x13
#define GPIO 0x14
#define MISC1 0x15
#define MISC2 0x16
#define CONFIG4 0x17

/* Private */
void ADS1299_WriteRegister(uint8_t reg, uint8_t value);
uint8_t ADS1299_ReadRegister(uint8_t reg);
uint8_t *ADS1299_ReadNRegisters(uint8_t n, uint8_t reg);


/* Public */
void ADS1299_Init(SPI_HandleTypeDef *hspi, GPIO_TypeDef *spi_ncs_port, uint16_t spi_ncs_pin, GPIO_TypeDef *CLKSEL_GPIOx, uint16_t CLKSEL_GPIO_Pin, bool extCLK, 
	GPIO_TypeDef *NPWDN_GPIOx, uint16_t NPWDN_GPIO_Pin,GPIO_TypeDef *NRESET_GPIOx, uint16_t NRESET_GPIO_Pin);
void ADS1299_ReadData(uint8_t* buffer);
void ADS1299_RDATAC();
uint8_t *ADS1299_RDATA();





#endif // ADS1299_H
