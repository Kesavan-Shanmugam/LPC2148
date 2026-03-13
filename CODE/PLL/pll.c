#include<lpc214x.h>
void pll();
int main()
{
    pll();
}
void pll()
{
    PLL0CON=0x01;
    PLL0CFG=0X24;
    PLL0FEED=0XAA;
    PLL0FEED=0X55;
    while(PLL0STAT==(1<<10));
    PLL0CON=0X03;
    PLL0FEED=0XAA;
    PLL0FEED=0X55;
    VPBDIV=0X01;
}