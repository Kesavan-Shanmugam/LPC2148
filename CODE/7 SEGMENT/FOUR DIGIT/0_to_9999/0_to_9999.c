#include<LPC214x.h>
void delay();
int main()
{
    IODIR0=0X00000FFF;
    IOCLR0=0X00000FFF;

    while(1)
    {
        int a[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
        int first,second,third,fourth,k;
        for(k=0; k<10000; k++)
        {
            first=((k/1000)%10);
            second=((k/100)%10);
            third=((k/10)%10);
            fourth=((k/1)%10);

            
                IOSET0=0X00000700;
                IOSET0=a[fourth];
                delay();
                IOCLR0=0X00000FFF;

                IOSET0=0X00000B00;
                IOSET0=a[third];
                delay();
                IOCLR0=0X00000FFF;

                IOSET0=0X00000D00;
                IOSET0=a[second];
                delay();
                IOCLR0=0X00000FFF;

                IOSET0=0X00000E00;
                IOSET0=a[first];
                delay();
                IOCLR0=0X00000FFF;
            
        }
    }
}
void delay()
{
    int i,j;
    for(i=0;i<100;i++)
    {
        for(j=0;j<100;j++);
    }
}