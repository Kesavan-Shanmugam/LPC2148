#include<lpc214x.h>
void delay();
int main()
{
    int k;
    for(k=0; k<0xffffffff; k++)
    {
        DACR=k;
    }
    DACR=0X00000000;
    delay();
}
void delay()
{
    int i,j;
    for(i=0; i<200; i++)
    {
        for(j=0; j<200; j++);
    }
}