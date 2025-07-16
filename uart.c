#include <reg52.h>
#include <string.h>
#include "intrins.h"
typedef unsigned char uchar;



sbit newTXD = P1^1;//ģ�⴮�ڵķ��Ͷ���ΪP2.1


void print_init()
{

	SCON  = 0x50;     // SCON: serail mode 1, 8-bit UART
	TMOD |= 0x21;     // T0�����ڷ�ʽ1��ʮ��λ��ʱ
	PCON |= 0x80;     // SMOD=1;
	// ��ʱ��0��ʼֵ����ʱ417us��Ŀ������ģ�⴮�ڵĲ�����Ϊ4800bps fosc=11.0592MHz
	// ��ʱ��0��ʼֵ����ʱ417us��Ŀ������ģ�⴮�ڵĲ�����Ϊ4800bps fosc=11.0592MHz
	TH0 = (65536 - 192) / 256;
	TL0 = (65536 - 192) % 256;
}

void WaitTF0(void)
{
	while(!TF0);
	TF0=0;
	// ��ʱ��0��ʼֵ����ʱ417us��Ŀ������ģ�⴮�ڵĲ�����Ϊ4800bps fosc=11.0592MHz
	// ��ʱ��0��ʼֵ����ʱ417us��Ŀ������ģ�⴮�ڵĲ�����Ϊ4800bps fosc=11.0592MHz
   	TH0 = (65536 - 192) / 256;
	TL0 = (65536 - 192) % 256;
}

void write_byte(uchar input)
{

	//������ʼλ
	uchar j=8;

	newTXD=(bit)0;
	WaitTF0();
	
	//����8λ����λ
	while(j--)
	{
	   newTXD=(bit)(input&0x01);      //�ȴ���λ
	   WaitTF0();
	   input=input>>1;
	}
	
	//����У��λ(��)
	//���ͽ���λ
	newTXD=(bit)1;
	WaitTF0();
	TR0=0;
}

void print_str(const char *str)
{
	int i, len = strlen(str);

	for (i = 0; i <len; i++)
		   write_byte(str[i]);
}

void print_l2c(long n)
{
	int i = 0, j;	
	char c[20] = {'0'};
	while(n)
	{
		c[i++] = ((n % 10) +'0');
		n /= 10;
	}
	for(j = i - 1; j >= 0; j--)
		WByte(c[j]);
}