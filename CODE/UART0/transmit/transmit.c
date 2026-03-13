#include<lpc214x.h>
#define rs 1<<8
#define en 1<<9
void delay()
{
    int i,j;
    for(i=0; i<100; i++)
    {
        for(j=0; j<100; j++);
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
    VPBDIV=0X01;
}
void INIT_UART()
{
    PINSEL0 |=0X00000005;
    U0LCR=0X83;
	U0DLL=0X87;
	U0DLM=0X01;
    U0LCR=0X03;  
}

int write(char k)
{
    while(!(U0LSR&(1<<5)));
    U0THR=k;
}
int main()
{
    pll();
	INIT_UART();
	write('k');
	delay();
}