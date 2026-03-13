#include<LPC214x.h>
void delay();
int main()
{
    IODIR0=0X0FF;
    IOCLR0=0X0FF;
    while(1)
    {
        IOSET0=0X00000033;
        delay();
        IOCLR0=0X00000033;
        IOSET0=0X000000cc;
        delay();
        IOCLR0=0X000000cc;
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