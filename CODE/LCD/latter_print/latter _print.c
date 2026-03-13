#include<lpc214x.h>
#define a 1<<8;
#define b 1<<9;
void delay()
{
    int i,j;
    for(i=0; i<200; i++)
    {
        for(j=0; j<200; j++);
    }
}

void command(char c)
{
    IOCLR0=0x0FF;
    IOSET0=c;
    IOCLR0=a;
    IOSET0=b;
    delay();
    IOCLR0=b;
    delay();
}
void data(int d)
{
    IOCLR0=0x0FF;
    IOSET0=d;
    IOSET0=a;
    IOSET0=b;
    delay();
    IOCLR0=b;
    delay();
}

int main()
{
    IODIR0=0X0FFF; //it,s means 0x00000fff. it's use which pin are output(1) and intput(0).
    //IOCLR0=0X0FFF; //clear or low the all pins
    while(1)
    {
 
            command(0x0e);
            command(0x80);
            data('k');
    }
}

