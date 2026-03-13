#include<lpc214x.h>
#define rs 1<<24
#define en 1<<25
int i;
char k[]={"kesavan"};

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

void display_command(char c)
{
    IOCLR1=0X0FFF<<16;
    IOSET1=(c<<16);
    IOCLR1=rs;
    IOSET1=en;
    delay();
    IOCLR1=en;
}

void display_data(char d)
{
    IOCLR1=0X0FFF<<16;
    IOSET1=(d<<16);
    IOSET1=rs;
    IOSET1=en;
    delay();
    IOCLR1=en;
}

void i2c_init()
{
    PINSEL0=0X50;                  //select the i2c pin
    I2C0CONCLR=0X6C;               //i2c control clear register
    I2C0SCLH=0X96;                 //i2c scl high duty cycle
    I2C0SCLL=0X96;                 //i2c scl low duty cycle
    I2C0CONSET=0X40;               //i2c enable bit
}

void i2c_start()
{
    I2C0CONSET=0X20;               //i2c start bit
    I2C0CONCLR=0X08;               //i2c intrrupt clear bit
    while((I2C0STAT==0X08)==0);    //check interflag
}

void i2c_stop()
{
    I2C0CONSET=0X10;                //i2c stop bit
    I2C0CONCLR=0X08;                //i2c intrrupt clear bit
}

void i2c_write_address()              
{

    I2C0DAT=0XA0;                   //i2c write bit
    I2C0CONCLR=0X08;                //i2c intrrupt clear bit
    while((I2C0CONSET & 0X08)==0);  //check interflag

    I2C0DAT=0X00;                   //i2c high address bit
    I2C0CONCLR=0X08;                //i2c intrrupt clear bit
    while((I2C0CONSET & 0X08)==0);  //check interflag

    I2C0DAT=0X00;                   //i2c low address bit
    I2C0CONCLR=0X08;                //i2c intrrupt clear bit
    while((I2C0CONSET & 0X08)==0);  //check interflag

}

int i2c_write(char w)
{ 
    I2C0DAT=w;                      //i2c set value
    I2C0CONCLR=0X08;                //i2c intrrupt clear bit
    while((I2C0CONSET & 0X08)==0);  //check interflag
	return I2C0DAT;
 }
int main()
{
    char S;
    IODIR1=0X0FFF<<16;
    pll();
    i2c_init();
	display_command(0x0e);

    while(1)
    {
	    i2c_start();
		i2c_write_address();
     	for(i=0; k[i]!='\0'; i++)
        {  
	       S=i2c_write(k[i]);
		   display_command(0x80+i);
           display_data(S);
		}
        i2c_stop();  
    }
}