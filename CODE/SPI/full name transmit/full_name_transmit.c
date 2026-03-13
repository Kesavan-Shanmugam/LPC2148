#include<lpc214x.h>
#define rs 1<<24
#define en 1<<25
#define CS 1<<7

void delay()
{
    int i,j;
    for(i=0; i<300; i++)
    {
        for(j=0; j<300; j++);
    }
}

void pll()
{
    PLL0CON=0X01;
    PLL0CFG=0X24;
    PLL0FEED=0XAA;
    PLL0FEED=0X55;
    while(PLL0STAT==(1<<10));
    PLL0CON=0X03;
    PLL0FEED=0XAA;
    PLL0FEED=0X55;
    VPBDIV=0X02;
}
  

int main()
{
    int i;
    char k[]={"kesavan"};
    IODIR1=0X0FFF<<16;
	pll();

	IODIR0=CS;                    //GPIO OUTPUT FOR CS
    PINSEL0=0X00001500;           //SPI PIN SELECT 
	pll();
    S0SPCR=0X0020;                  //ENABLE MOSTER MODE
    S0SPCCR=0X3C;                 //SPL CLOCK(60/60=1, 60 HEX VALUE 0X3C)

	while(1)
	{
    IOSET0=CS;                    //CS HIGH
    delay();
    IOCLR0=CS;                    //CS LOW

    S0SPDR=0X06;                  //WRITE ENABLE FOR EEPROM(25AA640)
    while((S0SPSR & 0X80)==0);    //SPI IF

    IOSET0=CS;                    //CS HIGH
    delay();
    IOCLR0=CS;                    //CS LOW

    S0SPDR=0X02;                  //WRITE COMMAND
    while((S0SPSR & 0X80)==0);    //SPI IF

    S0SPDR=0X00;                  //LOW BYTE ADDRESS
    while((S0SPSR & 0X80)==0);    //SPI IF

    S0SPDR=0X00;                  //HIGH BYTE ADDRESS
    while((S0SPSR & 0X80)==0);    //SPI IF

	for(i=0; k[i]!='\0'; i++)
	{
    S0SPDR=k[i];                     //SET DATA
    while((S0SPSR & 0X80)==0);    //SPI IF
	}

    IOSET0=CS;
	while(1);
	}
 }

