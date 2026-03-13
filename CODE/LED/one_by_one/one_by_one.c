#include<LPC214x.h>
void delay();
int main()
{
    IODIR0=0X0FF;
    IOCLR0=0X0FF;
    while(1)
    {
        IOSET0=0X00000001;
        delay();
        IOCLR0=0X00000001;
        IOSET0=0X00000002;
        delay();
        IOCLR0=0X00000002;
        IOSET0=0X00000004;
        delay();
        IOCLR0=0X00000004;
        IOSET0=0X00000008;
        delay();
        IOCLR0=0X00000008;
        IOSET0=0X00000010;
        delay();
        IOCLR0=0X00000010;
        IOSET0=0X00000020;
        delay();
        IOCLR0=0X00000020;
        IOSET0=0X00000040;
        delay();
        IOCLR0=0X00000040;
        IOSET0=0X00000080;
        delay();
        IOCLR0=0X00000080;
    }
}
void delay()
{
    int i,j;
    for(i=0;i<300;i++)
    {
        for(j=0;j<300;j++);
    }
}