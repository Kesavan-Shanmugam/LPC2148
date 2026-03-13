#include<LPC214x.h>
void delay();
int main()
{
    IODIR0=0X00000FFF;
    IOCLR0=0X00000FFF;

    while(1)
    {
        int a[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};

		IOSET0=0X00000200;
        IOSET0=a[3];
        delay();
        IOCLR0=0X00000FFF;

        IOSET0=0X00000100;
        IOSET0=a[3];
        delay();
		IOCLR0=0X00000FFF;
    }
}
void delay()
{
    int i,j;
    for(i=0;i<200;i++)
    {
        for(j=0;j<200;j++);
    }
}