#pragma once 

void SPI_init(void); 
void SPI_write(char cData);
char SPI_read(void);
void SS_on(void);
void SS_off(void);
