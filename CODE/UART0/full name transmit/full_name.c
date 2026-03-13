#include<lpc214x.h>
#define rs 1<<12
#define en 1<<13
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
    while(!(PLL0STAT&(1<<10)));
    PLL0CON=0X03;
    PLL0FEED=0XAA;
    PLL0FEED=0X55;
    VPBDIV=0X01;
}
void display_command(char c)
{
    IOCLR0=0X0FFF0;
    IOSET0=c<<4;
    IOCLR0=rs;
    IOSET0=en;
    delay();
    IOCLR0=en;
}
void display_data(char d)
{
    IOCLR0=0X0FFF0;
    IOSET0=d<<4;
    IOSET0=rs;
    IOSET0=en;
    delay();
    IOCLR0=en;
}
void INIT_UART()
{
    PINSEL0 |=0X00000005;
    U0LCR=0X83;
	U0DLL=0X87;
	U0DLM=0X01;
    U0LCR=0X03;  
}
int write(char w)
{   int data;
    while(!(U0LSR&(1<<5)));
    U0THR=w;
    return data;
}
int main()
{	int i;
	char name;
    char k[]={"kesavan"};
    IODIR0=0x0FFF<<4;
    pll();
	INIT_UART();
	while(1)
	{
        for(i=0; k[i]!='\0'; i++)
        {
          display_command(0X0E);
	      display_command(0X80+i);
          name=write(k[i]);
	      display_data(name);
	      delay();

        }
	}

}
