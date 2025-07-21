/********************************************************************
 * ʵ�����ƣ� Wk2XXXд�Ĵ�����ʽ��һ��һ�ֽڣ��շ���������
 * ѡ���鼮��	�ϲ�-������ǳ��STC8��ǿ��51��Ƭ�����׹��ԡ��Ѿ�����
							�²�-������ǳ��STC8��ǿ��51��Ƭ��ʵս���ԡ�����д��
 * �鼮���ߣ�	��˳����� �廪��ѧ���������
 * �Ա����̣�	https://520mcu.taobao.com/
 * ʵ��ƽ̨��	˼�޵���STC8��ս����ϵ��С���ӿ�����
 * оƬ�ͺţ�	STC8H8K64U-LQFP64������΢�������ֲ��STC����ϵ�е�Ƭ����
 * ʱ��˵����	Ƭ��IRC����24MHzʱ�ӣ�ʹ��STC-ISP���س���ʱ����
 * �������ʣ� STC8H8K64U��Ƭ����115200bps��ģ���Ӵ��ڣ�14400bps
 * ����˵���� SX-UART-A V3.6ģ���RX=P3.1��TX=P3.0��RS=P3.6
********************************************************************/
#include <reg52.h>
#include "wk2xxx.h"
/*************************�˿����Ŷ���******************************/
sbit WK2XXX_RST = P3^6;//WK2XXX��λ�˿�
/********************************************************************
WK2XXX��ʼ������WK2XXX_Init(void)�����β��ޣ�����ֵ
********************************************************************/
void WK2XXX_Init(void)
{
  UART_init();		//��ʼ������1��������Ϊ115200
  WK2XXX_RST=0;  	//��λwk2xxx
  delay_ms(100);  //��ʱ100ms
  WK2XXX_RST=1; 
  delay_ms(100);  //��ʱ100ms
  UART_SendByte(0x55);//��wk2xxx���������ź�
  delay_ms(10);  	//��ʱ10ms
}
/********************************************************************
WK2XXX��ȫ�ּĴ�����WK2XXX_Read_GlobalREG��u8 reg��
�β�regΪ�Ĵ�����ַ������ֵΪ�üĴ�����ֵ
********************************************************************/
u8 WK2XXX_Read_GlobalREG(u8 reg)
{
  u8 reg_buff;
  UART_num=1;//����Ҫ���յ����ݸ���
  UART_Rflag=0;//���������ɱ�־
  UART_SendByte(reg|0x40);//���ͼĴ�������Ĵ�����ַָ��
  while(!UART_Rflag);//�ȴ����ݽ������
  UART_Rflag=0;//��ս������λ
  reg_buff = UART_buff[0];//�������ļĴ�����ֵ���ظ���reg_buff
  return  reg_buff;
}
/********************************************************************
WK2XXXдȫ�ּĴ�����WK2XXX_Write_GlobalREG��u8 reg,u8 dat��
�β�regΪ�Ĵ�����ַ��datΪҪд������ݣ��޷���ֵ
********************************************************************/
void WK2XXX_Write_GlobalREG(u8 reg,u8 dat)
{
  UART_SendByte(reg|0x00);//���ͼĴ���д��Ĵ�����ַָ��
  UART_SendByte(dat);//��������
}
/********************************************************************
WK2XXX���Ӵ��ڼĴ�����WK2XXX_Read_REG(u8 num,u8 reg)
�β�numΪ�Ӵ��ںţ�regΪ�Ĵ�����ַ������ֵreg_buffΪ�üĴ�����ֵ
********************************************************************/
u8 WK2XXX_Read_REG(u8 num,u8 reg)
{
  u8 reg_buff;
  switch(num)//ѡ��Ĵ�������Ĵ�����ַָ��
  {
	  case 1 : reg|=0x00;break;
	  case 2 : reg|=0x10;break;
	  case 3 : reg|=0x20;break;
	  case 4 : reg|=0x30;break;
	  default : return 0; 
  }
  UART_num=1;//����Ҫ���յ����ݸ���
  UART_Rflag=0;//���������ɱ�־          
  UART_SendByte(reg|0x40);//���ͼĴ�������Ĵ�����ַָ��
  while(!UART_Rflag);//�ȴ��������
  UART_Rflag=0;//���������ɱ�־   
  reg_buff=UART_buff[0];//�������ļĴ�����ֵ���ظ���reg_buff
  return  reg_buff;
}
/********************************************************************
WK2XXXд�Ĵ�����WK2XXX_Write_GlobalREG��u8 reg,u8 dat��
�β�numΪ�Ӵ��ںţ�regΪ�Ĵ�����ַ��datΪҪд������ݣ��޷���ֵ
********************************************************************/
void WK2XXX_Write_REG(u8 num,u8 reg,u8 dat)
{
  switch(num)//ѡ��Ĵ���д��Ĵ�����ַָ��
  {
  case 1 : reg|=0x00;break;
  case 2 : reg|=0x10;break;
  case 3 : reg|=0x20;break;
  case 4 : reg|=0x30;break;
  default : return; 
  }
  UART_SendByte(reg|0x00);//���ͼĴ���д��Ĵ�����ַָ��
  UART_SendByte(dat);     //����Ҫд���ֵ
}
/********************************************************************
WK2XXX�Ӵ��ڳ�ʼ������WK2XXX_UTx_Init(u8 num,u16 baud)
�β�numΪ�Ӵ��ںţ�baudΪ�����ʣ��޷���ֵ
********************************************************************/
void WK2XXX_UTx_Init(u8 num,u16 baud)
{
  u8 GENA_dat;
  
  GENA_dat=WK2XXX_Read_GlobalREG(WK2XXX_GENA); //��ȫ�ֿ��ƼĴ�����ֵ
  switch(num)
  {
  case 1 : WK2XXX_Write_GlobalREG(WK2XXX_GENA,GENA_dat|WK2XXX_UT1EN);
  break;//ʹ���Ӵ���1��ʱ��
  case 2 : WK2XXX_Write_GlobalREG(WK2XXX_GENA,GENA_dat|WK2XXX_UT2EN);
  break;//ʹ���Ӵ���2��ʱ��
  case 3 : WK2XXX_Write_GlobalREG(WK2XXX_GENA,GENA_dat|WK2XXX_UT3EN);
  break;//ʹ���Ӵ���3��ʱ��
  case 4 : WK2XXX_Write_GlobalREG(WK2XXX_GENA,GENA_dat|WK2XXX_UT4EN);
  break;//ʹ���Ӵ���4��ʱ��
  default : return; 
  }
  //�����Ӵ��ڿ������Ĵ���
  WK2XXX_Write_REG(num,WK2XXX_SPAGE,WK2XXX_SPAGE0);//ѡ���Ӵ���ҳ������0
  WK2XXX_Write_REG(num,WK2XXX_SCR,WK2XXX_TXEN|WK2XXX_RXEN);//ʹ���Ӵ����շ�
  WK2XXX_Write_REG(num,WK2XXX_LCR,0x00);//�Ӵ�����У��
  WK2XXX_Write_REG(num,WK2XXX_FCR,0x0C);//�Ӵ���FIFO�շ�ʹ��
  WK2XXX_Write_REG(num,WK2XXX_SPAGE,WK2XXX_SPAGE1);//ѡ���Ӵ���ҳ������1
  //�����Ӵ��ڲ�����
  WK2XXX_Write_REG(num,WK2XXX_BAUD1,baud<<8);//�Ӵ��ڲ����ʸ�λ
  WK2XXX_Write_REG(num,WK2XXX_BAUD0,baud);   //�Ӵ��ڲ����ʵ�λ
  WK2XXX_Write_REG(num,WK2XXX_SPAGE,WK2XXX_SPAGE0);//ѡ���Ӵ���ҳ������0
}

/********************************************************************
WK2XXXд�Ĵ�����ʽ�������ݺ���WK2XXX_Write_REG_ReceiveByte(u8 num)
�β�numΪ�Ӵ��ںţ��з���ֵDataΪ�Ӵ���FIFO���ݼĴ�����ֵ
********************************************************************/
u8 WK2XXX_Write_REG_ReceiveByte(u8 num)
{
  u8 Data;
  while(!((WK2XXX_Read_REG(num,WK2XXX_FSR))&0x08));
  Data =WK2XXX_Read_REG(num,WK2XXX_FDAT);//�����Ӵ���FIFO���ݼĴ�����ֵ
  return Data;
}
/********************************************************************
WK2XXXд�Ĵ�����ʽ�������ݺ���WK2XXX_Write_REG_SendByte(u8 num,u8 dat)
�β�numΪ�Ӵ��ںţ�datΪҪ���͵����ݣ��޷���ֵ
********************************************************************/
void WK2XXX_Write_REG_SendByte(u8 num,u8 dat)
{
  WK2XXX_Write_REG(num,WK2XXX_FDAT,dat);
}
/********************************************************************
WK2XXX�����ַ�������WK2XXX_Write_REG_SendString(u8 num,u8 *buff)
�β�numΪ�Ӵ��ںţ�buffΪҪд������ݵ�ָ�룬�޷���ֵ
********************************************************************/
void WK2XXX_Write_REG_SendString(u8 num,u8 *buff)
{
  while(*buff!='\0')// '\0 '��ʾ�ַ���������־��
  {
    WK2XXX_Write_REG(num,WK2XXX_FDAT,*buff);
    buff++;
  }
}

#if 0
/********************************************************************
WK2XXX��FIFO����WK2XXX_Read_FIFO(u8 num,u8 count,u8 *fifo_buff)
�β�numΪ�Ӵ��ںţ�countΪҪ���յĸ�����fifo_buffΪ�����ݴ�ָ�룬�޷���ֵ
********************************************************************/
void WK2XXX_Read_FIFO(u8 num,u8 count,u8 *fifo_buff)
{
  u8 cmd;
  if(count>16)//һ��������16���ַ�
    count=16;
  UART_num=count;//����Ҫ���յ����ݸ���
  UART_Rflag=0;
  count--; //���ö�ȡFIFO����ʱ��Ҫ��һ������Ϊ0000ʱ���������1�������ֽڣ�
  switch(num)
  {
  case 1 : cmd=0xC0|count;//���Ӵ���1FIFOָ��
  break;
  case 2 : cmd=0xD0|count;//���Ӵ���2FIFOָ��
  break;
  case 3 : cmd=0xE0|count;//���Ӵ���3FIFOָ��
  break;
  case 4 : cmd=0xF0|count;//���Ӵ���4FIFOָ��
  break;
  default : return; 
  }
  UART_SendByte(cmd); //����д�Ӵ���FIFOָ��
  while(!UART_Rflag);//�ȴ����ݽ������
  UART_Rflag=0;    //����ձ�־λ
  
  strncpy((char *)fifo_buff,(char *)UART_buff,count+1);
                      //��UART_buff�е����ݸ��Ƶ�fifo_buff
  fifo_buff[count+1]='\0';//������־
}
/********************************************************************
WK2XXXдFIFO����WK2XXX_Write_FIFO(u8 num,u8 count,u8 *fifo_buff)
�β�numΪ�Ӵ��ںţ�countΪ���͵ĸ�����fifo_buffΪ����ָ�룬�޷���ֵ
********************************************************************/
void WK2XXX_Write_FIFO(u8 num,u8 count,u8 *fifo_buff)
{
  u8 cmd;
  if(count>16)//һ�����д��16���ַ�
  count=16;
  fifo_buff[count]  = '\0';
  count--; //���ö�ȡFIFO����ʱ��Ҫ��һ������Ϊ0000ʱ���������1�������ֽڣ�
  cmd=0x80+count;
  switch(num)
  {
    case 1 : cmd=0x80|count;//д�Ӵ���1FIFOָ��
    break;
    case 2 : cmd=0x90|count;//д�Ӵ���2FIFOָ��
    break;
    case 3 : cmd=0xA0|count;//д�Ӵ���3FIFOָ��
    break;
    case 4 : cmd=0xB0|count;//д�Ӵ���4FIFOָ��
    break;
    default : return; 
  }
  UART_SendByte(cmd);//����д�Ӵ���FIFOָ��
  UART_SendStr(fifo_buff);//��������
}
/********************************************************************
WK2XXXдFIFO��ʽ�������ݺ���WK2XXX_Write_FIFO_SendData(u8 num,u8 *fifo_buff)
�β�numΪ�Ӵ��ںţ�fifo_buffΪ��������ָ�룬�޷���ֵ
********************************************************************/
void WK2XXX_Write_FIFO_SendData(u8 num,u8 *fifo_buff)
{
  WK2XXX_Write_FIFO(num,strlen((char *)fifo_buff),fifo_buff);//��������
}
/********************************************************************
WK2XXXдFIFO��ʽ�������ݺ���WK2XXX_Write_FIFO_ReceiveData(u8 num,u8 *fifo_buff)
�β�numΪ�Ӵ��ںţ�fifo_buffΪ��������ָ�룬�޷���ֵ
********************************************************************/
void WK2XXX_Write_FIFO_ReceiveData(u8 num,u8 *fifo_buff)
{
  while(!((WK2XXX_Read_REG(num,WK2XXX_FSR))&0x08));//�ȴ�����
  WK2XXX_Read_FIFO(num,WK2XXX_Read_REG(num,WK2XXX_RFCNT),fifo_buff);//����
}
/********************************************************************
WK2XXX�շ�һ�庯��WK2XXX_Receive_And_Send(u8 num)���β�numΪ�Ӵ��ںţ�
//�޷���ֵ
********************************************************************/
void WK2XXX_REG_Receive_And_Send(u8 num)
{
  if(WK2XXX_Read_REG(num,WK2XXX_FSR)&0x08)//�����ռĴ����ǿ�
  {
    WK2XXX_Write_REG_SendByte(num,WK2XXX_Read_REG(num,WK2XXX_FDAT));
		//�����յ������ݷ���
  }
}
#endif