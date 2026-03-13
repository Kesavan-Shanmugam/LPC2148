#include<LPC214x.h>
void delay();
int main()
{
    IODIR0=0X0FF;
    IOCLR0=0X0FF;
    while(1)
    {
        IOSET0=0X00000055;
        delay();
        IOCLR0=0X00000055;
        IOSET0=0X000000AA;
        delay();
        IOCLR0=0X000000AA;
    }
}
void delay()
{
    int i,j;
    for(i=0;i<1000;i++)
    {
        for(j=0;j<1000;j++);
    }
}