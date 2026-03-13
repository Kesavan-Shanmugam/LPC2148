#include<lpc214x.h>
#include<stdio.h>
#define a 1<<8
#define b 1<<9

void pll()
{
    PLL0CON=0X01;               //pll enable
    PLL0CFG=0X24;               // pll configuration multiplier and divider
    PLL0FEED=0XAA; 
    PLL0FEED=0X55;
    while(PLL0STAT ==(1<<10));
    PLL0CON=0X03;               //pll enable and connect
    PLL0FEED=0XAA;
    PLL0FEED=0X55;
    VPBDIV=0X01;                //divider pclk=cclk
}
void adc_init()
{
    PINSEL1 |=(1<<24);                 //set bit 24=1
    PINSEL1 &=~(1<<25);                //set bit 25=0
    AD0CR =(1<<2)|(13<<8)|(1<<21);     //configure adc
}
int adc_read()
{	int val;
    AD0CR |=(1<<24);                   //start adc
    while(!(AD0GDR &(1<<31)));         //wait unit conversion done
    //val=AD0GDR;                      //store value
    val=(AD0GDR>>6) & 0x03FF;          //sotre value in 10 bit
    return val;
}
void delay()
{
    int i,j;
    for(i=0; i<300; i++)
    {
        for(j=0; j<300; j++);
    }
}
void display_command(char C)
{
    IOCLR0=0X0FFF;            //clear the bit
    IOSET0=C;                 //command
    IOCLR0=a;
    IOSET0=b;
    delay();
    IOCLR0=b;
}
void display_data(int D)
{
    IOCLR0=0X0FFF;            //clear the bit
    IOSET0=D;                 //data
    IOSET0=a;
    IOSET0=b;
    delay();
    IOCLR0=b;
}

int main()
{	int k,value;
     char v[10];
    IODIR0=0X00000FFF;                //input and output diraction bit 
	pll();
	 adc_init();                      //call function in adc intial
    //while(1)
    {
        value=adc_read();             //store the adc read function
		 display_command(0x0E);       //call command function
         display_command(0x80);       //call command function
        sprintf(v, "%d", value);      //int convert to string
        for(k=0; v[k]!='\0'; k++)
        {
            display_data(v[k]);        //call data function
        }
    }
}