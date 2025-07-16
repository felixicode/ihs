 /**********************************************************************************
 * 描述    ：STC89C52RC, 晶振11.0592MHz, 波特率：9600, 串口读取单路EC电导率模块浓度数据 
 * 硬件连接：        
 * LCD1602：RS -> P2.5; RW -> P2.6; E -> P2.7;
 *          D0~D7 -> P0口
 * 单路EC电导率模块：3.3V -> 3.3V; RX -> 3.1; TX -> P3.0; GND -> GND;  
 * 功能描述：串口外接单路EC电导率模块读取浓度数据，在LCD1602液晶屏显示浓度数据
 * 使用说明：先下载好程序再接线
**********************************************************************************/
#include "reg51.h"
#include "intrins.h"
#include "lcd.h"

typedef unsigned char BYTE;
typedef unsigned int WORD;

#define FOSC 11059200L      //System frequency
#define BAUD 9600           //UART baudrate
#define	BUF_LENTH	128		//定义串口接收缓冲长度

/*Define UART parity mode*/
#define NONE_PARITY     0   //None parity
#define ODD_PARITY      1   //Odd parity
#define EVEN_PARITY     2   //Even parity
#define MARK_PARITY     3   //Mark parity
#define SPACE_PARITY    4   //Space parity

#define PARITYBIT NONE_PARITY   //Testing even parity

sbit bit9 = P2^2;           //P2.2 show UART data bit9

bit busy;
int TDS_1_H,TDS_1_L;
int TM_1_H,TM_1_L;
float TDS1,TM1;

WORD ii;
unsigned int uart0_wr=0;    //写指针
unsigned char uart0_rd;		//读指针
xdata unsigned char RX0_Buffer[20]={'0'};	//接收缓冲

void SendData(BYTE dat);
void SendString(char *s);
void uart0_init();

void command1()     //发送检测指令
{
	SendData(0xA0);
	SendData(0x00);	
	SendData(0x00);
	SendData(0x00);
	SendData(0x00);
	SendData(0xA0);	
	Delay100ms();
}	

//void Display1()
//{
//	BYTE a1,a2,a3,a4;
//	a1 = (int)TDS1/1000 + '0';
//	a2 = (int)TDS1%1000/100 + '0';	
//	a3 = (int)TDS1%100/10 + '0';
//	a4 = (int)TDS1%10 + '0';
//	
//	DisplaySingleChar(0x05,0,a1);
//	DisplaySingleChar(0x06,0,a2);	
//	DisplaySingleChar(0x07,0,a3);	
//	DisplaySingleChar(0x08,0,a4);
//}
//	
//void Display2()
//{
//	BYTE a1,a2,a3,a4,a5;
//	a1 = (int)TM1/1000 + '0';
//	a2 = (int)TM1%1000/100 + '0';	
//	a3 = '.';	
//	a4 = (int)TM1%100/10 + '0';
//	a5 = (int)TM1%10 + '0';
//	
//	DisplaySingleChar(0x07,1,a1);
//	DisplaySingleChar(0x08,1,a2);	
//	DisplaySingleChar(0x09,1,a3);	
//	DisplaySingleChar(0x0A,1,a4);	
//	DisplaySingleChar(0x0B,1,a5);	
//}	

void ec_read(long *ec, long *temp)
{
		command1();		
		for(ii = 0;ii<uart0_wr;ii++)  
		{		
			if (RX0_Buffer[ii] == 0xAA )   //识别指令标志位
			{		
				TDS_1_H = (RX0_Buffer[ii+1]);
				TDS_1_L = (RX0_Buffer[ii+2]);			
				
				TDS1 = TDS_1_H*256 + TDS_1_L;
				if(TDS1<0){TDS1 = 0;}
				if(TDS1>3000){TDS1 = 3000;}	
				*ec = TDS1;		
		
				TM_1_H = (RX0_Buffer[ii+3]);
				TM_1_L = (RX0_Buffer[ii+4]);				
				TM1 = TM_1_H*256 + TM_1_L;
				*temp = TM1;
				Delay500ms();				
		      }
		  }	
}

/*----------------------------
UART interrupt service routine
----------------------------*/
void Uart_Isr() interrupt 4 using 1
{
	if(RI)
	{
		RI = 0;
		RX0_Buffer[uart0_wr] = SBUF;
		if(++uart0_wr >= 12)	uart0_wr = 0;
	}	
    if (TI)
    {
        TI = 0;             //Clear transmit interrupt flag
        busy = 0;           //Clear transmit busy flag
    }
}

void	ec_init(void)
{
	#if (PARITYBIT == NONE_PARITY)
			SCON = 0x50;            //8-bit variable UART
	#elif (PARITYBIT == ODD_PARITY) || (PARITYBIT == EVEN_PARITY) || (PARITYBIT == MARK_PARITY)
			SCON = 0xda;            //9-bit variable UART, parity bit initial to 1
	#elif (PARITYBIT == SPACE_PARITY)
			SCON = 0xd2;            //9-bit variable UART, parity bit initial to 0
	#endif

			TMOD = 0x20;            //Set Timer1 as 8-bit auto reload mode
			TH1 = TL1 = -(FOSC/12/32/BAUD); //Set auto-reload vaule
			TR1 = 1;                //Timer1 start run
			ES = 1;                 //Enable UART interrupt
			EA = 1;                 //Open master interrupt switch
}
/*----------------------------
Send a byte data to UART
Input: dat (data to be sent)
Output:None
----------------------------*/
void SendData(BYTE dat)
{
    while (busy);           //Wait for the completion of the previous data is sent
    ACC = dat;              //Calculate the even parity bit P (PSW.0)
    if (P)                  //Set the parity bit according to P
    {
#if (PARITYBIT == ODD_PARITY)
        TB8 = 0;            //Set parity bit to 0
#elif (PARITYBIT == EVEN_PARITY)
        TB8 = 1;            //Set parity bit to 1
#endif
    }
    else
    {
#if (PARITYBIT == ODD_PARITY)
        TB8 = 1;            //Set parity bit to 1
#elif (PARITYBIT == EVEN_PARITY)
        TB8 = 0;            //Set parity bit to 0
#endif
    }
    busy = 1;
    SBUF = ACC;             //Send data to UART buffer
}

/*----------------------------
Send a string to UART
Input: s (address of string)
Output:None
----------------------------*/
void SendString(char *s)
{
    while (*s)              //Check the end of the string
    {
        SendData(*s++);     //Send current char and increment string ptr
    }
}

