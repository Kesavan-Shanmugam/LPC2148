#include <lpc214x.h>
#define RS (1<<24)
#define EN (1<<25)
#define cs (1<<7)

void delay();
void pll();
void lcd_command(int command);
void lcd_data(char data);

int main()
{
    int i;
	char data[10];
	pll();

    PINSEL0 = 0x00001500;
    IODIR0  = cs;
	S0SPCCR = 0x3C;
    S0SPCR  = 0x20;   

	IODIR1 |= (0x0FFF << 16);

	while (1) 
	{
    	IOSET0 |= cs;    		         //cs high
	    delay();						 //delay
	    IOCLR0 = cs;     				 //cs low

	    S0SPDR = 0x03;					 //read command
		 while (!(S0SPSR & 0x80));		 //spi if

	    S0SPDR = 0x00;					 //high byte memory address
		 while (!(S0SPSR & 0x80));		 //spi if

	    S0SPDR = 0x00;					 //low byte memory address
		 while (!(S0SPSR & 0x80));		 //spi if
		          
	    for(i=0; i<7; i++)
		{
		
        S0SPDR = 0xFF;               	 //dummy byte to receive data
         while (!(S0SPSR & 0x80));    	 //spi if
         data[i] = S0SPDR;  		     //store the receice data
	
	    lcd_command(0x0E);
        lcd_command(0x80+i);      
        lcd_data(data[i]);           
        delay();
		}
    
	    IOSET0 = cs;     

		while(1);  
    }
}

void pll()
{
    PLL0CON = 0x01;
    PLL0CFG = 0x24;
    PLL0FEED = 0xAA;
    PLL0FEED = 0x55;
    while(!(PLL0STAT & (1<<10)));
    PLL0CON = 0x03;
    PLL0FEED = 0xAA;
    PLL0FEED = 0x55;
    VPBDIV = 0x01;
}

void delay()
{
    int i,j;
	for(i=0;i<50;i++)
	{
		for(j=0;j<50;j++);
	 }
} 

void lcd_command(int c)
{
    IOCLR1 = 0x0FFF << 16;               
    IOSET1 = (c << 16);   
    IOCLR1 = RS;                    
    IOSET1 = EN;                   
    delay();
    IOCLR1 = EN;                    
    delay();
}

void lcd_data(char d)
{
    IOCLR1 = 0x0FFF << 16;
    IOSET1 = (d << 16);
    IOSET1 = RS;                    
    IOSET1 = EN;
    delay();
    IOCLR1 = EN;
    delay();
}