#include<LPC214x.h>
void delay();
int main()
{
    IODIR0=0X0FF;
    IOCLR0=0X0FF;
    while(1)
    {
        IOSET0=0X0000000f;
        delay();
        IOCLR0=0X0000000f;
        IOSET0=0X000000f0;
        delay();
        IOCLR0=0X000000f0;
    }
}
void delay()
{
    int i,j;
    for(i=0;i<2000;i++)
    {
        for(j=0;j<2000;j++);
    }
}