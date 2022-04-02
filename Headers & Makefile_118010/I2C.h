
/****************************************************************************
HEADER:I2C.h

*****************************************************************************

COPYRIGHT(c): Technophilia embedded systems
AUTHOR:Technophilia
Date: 26th July 2012

DESCRIPTION: 

    This header file gives two wire interface between an avr microcontroller & a TWI(I2C) device. 
	Include this header file in your C code. 
	
	write();------Call this function specifying the address/location & data to write in the device 
					 
	read();-------This function is used to read the data from a memory location of the device.
		
*****************************************************************************/

#ifndef _I2C_H_
#define _I2C_H_

unsigned char write(unsigned char add,unsigned char data)
{
	TWBR=0XFF;							//lowest possible scl frequency
	TWSR=0X00;							//precscalar set to 1
	
	TWCR=0XA4;							//start bit
	while(!(TWCR&0x80));				//checking if TWINT is set
	while(TWSR!=0x08);					//checking if  status code is correct
	
	
	
	TWDR=0x98;							//Selecting the slave in write mode (10011000), [From MSB first 7 bits are the unique device id of Acceleration Sensor & the 8th bit is for read(1)/write(0)]
	TWCR=0x84;							//enabling TWI and set TWINT
	while(!(TWCR&0x80));				//checking if TWINT is set
	while(TWSR!=0x18);					//checking if  status code is correct
	
	
	
	TWDR=add;							//choosing the memory address  
	TWCR=0x84;							//enabling TWI and set TWINT
	while(!(TWCR&0x80));				//checking if TWINT is set
	while(TWSR!=0x28);					//checking if  status code is correct
	
	
	
	TWDR=data;							//sending data byte
	TWCR=0x84;							//enabling TWI and set TWINT
	while(!(TWCR&0x80));				//checking if TWINT is set
	while(TWSR!=0x28);					//checking if  status code is correct
	
	
	
	TWCR=0x94;							//sending stop bit 
	delay_i2c(20);
	
	
}

unsigned char read(unsigned char add)	//random address read
{	
	unsigned char a;
	
	TWBR=0X48;							//lowest possible scl frequency
	TWSR=0X00;							//precscalar set to 1
	
	TWCR=0XA4;							//start bit
	while(!(TWCR&0x80));				//checking if TWINT is set
	while(TWSR!=0x08);					//checking if  status code is correct
	

	
	TWDR=0x98;							//Selecting the slave in write mode (10011000), [From MSB first 7 bits are the unique device id of Acceleration Sensor & the 8th bit is for read(1)/write(0)]
	TWCR=0x84;							//enabling TWI and set TWINT
	while(!(TWCR&0x80));				//checking if TWINT is set
	while(TWSR!=0x18);					//checking if  status code is correct

	
	TWDR=add;							//choosing the address   0X08 ON 24c02 
	TWCR=0x84;							//enabling TWI and set TWINT
	while(!(TWCR&0x80));				//checking if TWINT is set
	while(TWSR!=0x28);					//checking if  status code is correct

	
	TWCR=0XA4;							//ReStart bit
	while(!(TWCR&0x80));				//checking if TWINT is set
	while(TWSR!=0x10);					//checking if  status code is correct
	
	TWDR=0x99;							//Selecting the slave in read mode (10011001), [From MSB first 7 bits are the unique device id of Acceleration Sensor & the 8th bit is for read(1)/write(0)]
	TWCR=0x84;							//enabling TWI and set TWINT
	while(!(TWCR&0x80));				//checking if TWINT is set
	while(TWSR!=0x40);					//checking if  status code is correct
	
	TWCR=0x84;							//enabling TWI and set TWINT
	
	while(!(TWCR&0x80));				//checking if TWINT is set
	while(TWSR!=0x58);					//checking if  status code is correct
	a=TWDR;
	TWCR=0x94;							//stop bit
	
	delay_i2c(2);
	return a;
}

void delay_i2c(unsigned int time_ms)
{
	unsigned int count_i2c;
	for(count_i2c=0;count_i2c<=time_ms;count_i2c++)
	{
		asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
		asm("nop");asm("nop");asm("nop");asm("nop");
	}
}

#endif