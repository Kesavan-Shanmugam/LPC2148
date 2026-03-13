#include<lpc214x.h>
int delay();
int main()
{
    IODIR0=0X0F;
    IOCLR0=0X0F;
    while(1)
    {
        IOSET0=0X01;
        delay();
        IOCLR0=0X01;
        delay();
    }
}
int delay()
{
    int i,j;
    for(i=0;i<300;i++)
    {
        for(j=0;j<300;j++);
    }
}