/********************************************************************
 * 实验名称： Wk2XXX写寄存器方式（一次一字节）收发数据例程
 * 选配书籍：	上册-《深入浅出STC8增强型51单片机进阶攻略》已经出版
							下册-《深入浅出STC8增强型51单片机实战攻略》还在写作
 * 书籍作者：	龙顺宇编著 清华大学出版社出版
 * 淘宝店铺：	https://520mcu.taobao.com/
 * 实验平台：	思修电子STC8“战将”系列小王子开发板
 * 芯片型号：	STC8H8K64U-LQFP64（程序微调后可移植至STC其他系列单片机）
 * 时钟说明：	片内IRC高速24MHz时钟，使用STC-ISP下载程序时配置
 * 串口速率： STC8H8K64U单片机：115200bps；模块子串口：14400bps
 * 接线说明： SX-UART-A V3.6模块的RX=P3.1，TX=P3.0，RS=P3.6
********************************************************************/
#include <reg52.h>
#include "wk2xxx.h"
/*************************端口引脚定义******************************/
sbit WK2XXX_RST = P3^6;//WK2XXX复位端口
/********************************************************************
WK2XXX初始化函数WK2XXX_Init(void)，无形参无，返回值
********************************************************************/
void WK2XXX_Init(void)
{
  UART_init();		//初始化串口1，波特率为115200
  WK2XXX_RST=0;  	//复位wk2xxx
  delay_ms(100);  //延时100ms
  WK2XXX_RST=1; 
  delay_ms(100);  //延时100ms
  UART_SendByte(0x55);//向wk2xxx发送握手信号
  delay_ms(10);  	//延时10ms
}
/********************************************************************
WK2XXX读全局寄存器函WK2XXX_Read_GlobalREG（u8 reg）
形参reg为寄存器地址，返回值为该寄存器的值
********************************************************************/
u8 WK2XXX_Read_GlobalREG(u8 reg)
{
  u8 reg_buff;
  UART_num=1;//设置要接收的数据个数
  UART_Rflag=0;//清零接收完成标志
  UART_SendByte(reg|0x40);//发送寄存器读与寄存器地址指令
  while(!UART_Rflag);//等待数据接收完成
  UART_Rflag=0;//清空接收完成位
  reg_buff = UART_buff[0];//将读到的寄存器的值读回赋给reg_buff
  return  reg_buff;
}
/********************************************************************
WK2XXX写全局寄存器函WK2XXX_Write_GlobalREG（u8 reg,u8 dat）
形参reg为寄存器地址，dat为要写入的数据，无返回值
********************************************************************/
void WK2XXX_Write_GlobalREG(u8 reg,u8 dat)
{
  UART_SendByte(reg|0x00);//发送寄存器写与寄存器地址指令
  UART_SendByte(dat);//发送数据
}
/********************************************************************
WK2XXX读子串口寄存器函WK2XXX_Read_REG(u8 num,u8 reg)
形参num为子串口号，reg为寄存器地址，返回值reg_buff为该寄存器的值
********************************************************************/
u8 WK2XXX_Read_REG(u8 num,u8 reg)
{
  u8 reg_buff;
  switch(num)//选择寄存器读与寄存器地址指令
  {
	  case 1 : reg|=0x00;break;
	  case 2 : reg|=0x10;break;
	  case 3 : reg|=0x20;break;
	  case 4 : reg|=0x30;break;
	  default : return 0; 
  }
  UART_num=1;//设置要接收的数据个数
  UART_Rflag=0;//清零接收完成标志          
  UART_SendByte(reg|0x40);//发送寄存器读与寄存器地址指令
  while(!UART_Rflag);//等待接收完成
  UART_Rflag=0;//清零接收完成标志   
  reg_buff=UART_buff[0];//将读到的寄存器的值读回赋给reg_buff
  return  reg_buff;
}
/********************************************************************
WK2XXX写寄存器函WK2XXX_Write_GlobalREG（u8 reg,u8 dat）
形参num为子串口号，reg为寄存器地址，dat为要写入的数据，无返回值
********************************************************************/
void WK2XXX_Write_REG(u8 num,u8 reg,u8 dat)
{
  switch(num)//选择寄存器写与寄存器地址指令
  {
  case 1 : reg|=0x00;break;
  case 2 : reg|=0x10;break;
  case 3 : reg|=0x20;break;
  case 4 : reg|=0x30;break;
  default : return; 
  }
  UART_SendByte(reg|0x00);//发送寄存器写与寄存器地址指令
  UART_SendByte(dat);     //发送要写入的值
}
/********************************************************************
WK2XXX子串口初始化函数WK2XXX_UTx_Init(u8 num,u16 baud)
形参num为子串口号，baud为波特率，无返回值
********************************************************************/
void WK2XXX_UTx_Init(u8 num,u16 baud)
{
  u8 GENA_dat;
  
  GENA_dat=WK2XXX_Read_GlobalREG(WK2XXX_GENA); //读全局控制寄存器的值
  switch(num)
  {
  case 1 : WK2XXX_Write_GlobalREG(WK2XXX_GENA,GENA_dat|WK2XXX_UT1EN);
  break;//使能子串口1的时钟
  case 2 : WK2XXX_Write_GlobalREG(WK2XXX_GENA,GENA_dat|WK2XXX_UT2EN);
  break;//使能子串口2的时钟
  case 3 : WK2XXX_Write_GlobalREG(WK2XXX_GENA,GENA_dat|WK2XXX_UT3EN);
  break;//使能子串口3的时钟
  case 4 : WK2XXX_Write_GlobalREG(WK2XXX_GENA,GENA_dat|WK2XXX_UT4EN);
  break;//使能子串口4的时钟
  default : return; 
  }
  //配置子串口控制器寄存器
  WK2XXX_Write_REG(num,WK2XXX_SPAGE,WK2XXX_SPAGE0);//选择子串口页控制器0
  WK2XXX_Write_REG(num,WK2XXX_SCR,WK2XXX_TXEN|WK2XXX_RXEN);//使能子串口收发
  WK2XXX_Write_REG(num,WK2XXX_LCR,0x00);//子串口无校验
  WK2XXX_Write_REG(num,WK2XXX_FCR,0x0C);//子串口FIFO收发使能
  WK2XXX_Write_REG(num,WK2XXX_SPAGE,WK2XXX_SPAGE1);//选择子串口页控制器1
  //配置子串口波特率
  WK2XXX_Write_REG(num,WK2XXX_BAUD1,baud<<8);//子串口波特率高位
  WK2XXX_Write_REG(num,WK2XXX_BAUD0,baud);   //子串口波特率低位
  WK2XXX_Write_REG(num,WK2XXX_SPAGE,WK2XXX_SPAGE0);//选择子串口页控制器0
}

/********************************************************************
WK2XXX写寄存器方式接收数据函数WK2XXX_Write_REG_ReceiveByte(u8 num)
形参num为子串口号，有返回值Data为子串口FIFO数据寄存器的值
********************************************************************/
u8 WK2XXX_Write_REG_ReceiveByte(u8 num)
{
  u8 Data;
  while(!((WK2XXX_Read_REG(num,WK2XXX_FSR))&0x08));
  Data =WK2XXX_Read_REG(num,WK2XXX_FDAT);//接收子串口FIFO数据寄存器的值
  return Data;
}
/********************************************************************
WK2XXX写寄存器方式发送数据函数WK2XXX_Write_REG_SendByte(u8 num,u8 dat)
形参num为子串口号，dat为要发送的数据，无返回值
********************************************************************/
void WK2XXX_Write_REG_SendByte(u8 num,u8 dat)
{
  WK2XXX_Write_REG(num,WK2XXX_FDAT,dat);
}
/********************************************************************
WK2XXX发送字符串函数WK2XXX_Write_REG_SendString(u8 num,u8 *buff)
形参num为子串口号，buff为要写入的数据的指针，无返回值
********************************************************************/
void WK2XXX_Write_REG_SendString(u8 num,u8 *buff)
{
  while(*buff!='\0')// '\0 '表示字符串结束标志，
  {
    WK2XXX_Write_REG(num,WK2XXX_FDAT,*buff);
    buff++;
  }
}

#if 0
/********************************************************************
WK2XXX读FIFO函数WK2XXX_Read_FIFO(u8 num,u8 count,u8 *fifo_buff)
形参num为子串口号，count为要接收的个数，fifo_buff为数据暂存指针，无返回值
********************************************************************/
void WK2XXX_Read_FIFO(u8 num,u8 count,u8 *fifo_buff)
{
  u8 cmd;
  if(count>16)//一次最大接收16个字符
    count=16;
  UART_num=count;//设置要接收的数据个数
  UART_Rflag=0;
  count--; //设置读取FIFO个数时需要减一（当其为0000时，表明后接1个数据字节）
  switch(num)
  {
  case 1 : cmd=0xC0|count;//读子串口1FIFO指令
  break;
  case 2 : cmd=0xD0|count;//读子串口2FIFO指令
  break;
  case 3 : cmd=0xE0|count;//读子串口3FIFO指令
  break;
  case 4 : cmd=0xF0|count;//读子串口4FIFO指令
  break;
  default : return; 
  }
  UART_SendByte(cmd); //读送写子串口FIFO指令
  while(!UART_Rflag);//等待数据接收完成
  UART_Rflag=0;    //清接收标志位
  
  strncpy((char *)fifo_buff,(char *)UART_buff,count+1);
                      //将UART_buff中的数据复制到fifo_buff
  fifo_buff[count+1]='\0';//结束标志
}
/********************************************************************
WK2XXX写FIFO函数WK2XXX_Write_FIFO(u8 num,u8 count,u8 *fifo_buff)
形参num为子串口号，count为发送的个数，fifo_buff为数据指针，无返回值
********************************************************************/
void WK2XXX_Write_FIFO(u8 num,u8 count,u8 *fifo_buff)
{
  u8 cmd;
  if(count>16)//一次最大写入16个字符
  count=16;
  fifo_buff[count]  = '\0';
  count--; //设置读取FIFO个数时需要减一（当其为0000时，表明后接1个数据字节）
  cmd=0x80+count;
  switch(num)
  {
    case 1 : cmd=0x80|count;//写子串口1FIFO指令
    break;
    case 2 : cmd=0x90|count;//写子串口2FIFO指令
    break;
    case 3 : cmd=0xA0|count;//写子串口3FIFO指令
    break;
    case 4 : cmd=0xB0|count;//写子串口4FIFO指令
    break;
    default : return; 
  }
  UART_SendByte(cmd);//发送写子串口FIFO指令
  UART_SendStr(fifo_buff);//发送数据
}
/********************************************************************
WK2XXX写FIFO方式发送数据函数WK2XXX_Write_FIFO_SendData(u8 num,u8 *fifo_buff)
形参num为子串口号，fifo_buff为发送数据指针，无返回值
********************************************************************/
void WK2XXX_Write_FIFO_SendData(u8 num,u8 *fifo_buff)
{
  WK2XXX_Write_FIFO(num,strlen((char *)fifo_buff),fifo_buff);//发送数据
}
/********************************************************************
WK2XXX写FIFO方式发送数据函数WK2XXX_Write_FIFO_ReceiveData(u8 num,u8 *fifo_buff)
形参num为子串口号，fifo_buff为接收数据指针，无返回值
********************************************************************/
void WK2XXX_Write_FIFO_ReceiveData(u8 num,u8 *fifo_buff)
{
  while(!((WK2XXX_Read_REG(num,WK2XXX_FSR))&0x08));//等待数据
  WK2XXX_Read_FIFO(num,WK2XXX_Read_REG(num,WK2XXX_RFCNT),fifo_buff);//接收
}
/********************************************************************
WK2XXX收发一体函数WK2XXX_Receive_And_Send(u8 num)有形参num为子串口号，
//无返回值
********************************************************************/
void WK2XXX_REG_Receive_And_Send(u8 num)
{
  if(WK2XXX_Read_REG(num,WK2XXX_FSR)&0x08)//若接收寄存器非空
  {
    WK2XXX_Write_REG_SendByte(num,WK2XXX_Read_REG(num,WK2XXX_FDAT));
		//将接收到的数据返回
  }
}
#endif