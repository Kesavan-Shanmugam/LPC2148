#include<lpc214X.h>
void timer();
void pll();
int main()
{
	pll();
    IODIR0=0X00000001;
    IOCLR0=0X00000001;
    while(1)
    {
        IOSET0=0X01;
        timer();
        IOCLR0=0X01;
		timer();
    }
}
void timer()
{
    T0CTCR=0x00;
    T0TCR=0X00;
    T0PR=59999;
    T0TCR=0X02;
    T0TCR=0X01;
    while(T0TC<10);
    T0TCR=0X00;
    T0TC=0;
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