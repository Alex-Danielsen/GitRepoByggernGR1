/*
 * spi.h For atmega 2560
 *
 * Created: 04.10.2016 14:11:44
 *  Author: nikolasn
 */ 


#ifndef SPI_H_
#define SPI_H_

//---FUNCTIONS---
void spi_init();

void spi_transmit(char data);

char spi_read();

#endif /* SPI_H_ */