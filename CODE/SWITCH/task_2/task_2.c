#include<lpc214x.h>
int main()
{
    IODIR0=~(1<<0)|(1<<1)|(1<<2)|(1<<3);
    IODIR0=(1<<4)|(1<<5)|(1<<6);
    while(1)
    {
        if(!(IOPIN0 & (1<<0)))
        {
            IOSET0=(1<<4);
            IOCLR0=(1<<5)|(1<<6);
        }
        else if(!(IOPIN0 & (1<<1)))
        {
            IOSET0=(1<<5);
            IOCLR0=(1<<4)|(1<<6);
        }
        else if(!(IOPIN0 & (1<<2)))
        {
            IOSET0=(1<<6);
            IOCLR0=(1<<5)|(1<<4);
        }
        else if(!(IOPIN0 & (1<<3)))
        {
            IOCLR0=(1<<4)|(1<<5)|(1<<6);
        }
    }
}