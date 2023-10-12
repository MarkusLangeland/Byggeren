#pragma once 

void SPI_init(void); 
uint8_t SPI_write(uint8_t cData);
uint8_t SPI_read(void);
void SS_on(void);
void SS_off(void);
