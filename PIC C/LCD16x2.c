/*******************************************************************************
  * File      :        LCD16x2.c
  * Author    :        Ngo Tran Khanh Dang BK
  * Version   :        1.0
  * Date      :        26-03-2014
  * Summary   :        Dinh nghia cac ham dieu khien LCD 16x2.
********************************************************************************/

//Chu y: Phai chinh lai phan khai bao cac chan cua LCD
#ifndef LCD_RS
#define LCD_RS PIN_E0                        
#endif

#ifndef LCD_RW
#define LCD_RW PIN_E1
#endif

#ifndef LCD_EN
#define LCD_EN PIN_E2
#endif

#ifndef LCD_D4
#define LCD_D4 PIN_D4
#endif

#ifndef LCD_D5
#define LCD_D5 PIN_D5
#endif

#ifndef LCD_D6
#define LCD_D6 PIN_D6
#endif

#ifndef LCD_D7
#define LCD_D7 PIN_D7
#endif



//Tao Xung
 void LCD_Enable(void)
{
 output_high(LCD_EN);
 delay_us(3);
 output_low(LCD_EN);
 delay_us(50); 
}
//Ham Gui 4 Bit Du Lieu Ra LCD
 void LCD_Send4Bit( unsigned char Data )
{
 output_bit(LCD_D4,Data&0x01);
 output_bit(LCD_D5,(Data>>1)&1);
 output_bit(LCD_D6,(Data>>2)&1);
 output_bit(LCD_D7,(Data>>3)&1);
}
// Ham Gui 1 Lenh Cho LCD
 void LCD_SendCommand (unsigned char command )
{
LCD_Send4Bit  ( command >>4 );   /* Gui 4 bit cao */
LCD_Enable () ;
LCD_Send4Bit  ( command  );      /* Gui 4 bit thap*/
LCD_Enable () ;
}
// Ham Khoi Tao LCD
 void LCD_Init ( void )
{
output_drive(LCD_D4);
output_drive(LCD_D5);
output_drive(LCD_D6);
output_drive(LCD_D7);
output_drive(LCD_EN);
output_drive(LCD_RS);
output_drive(LCD_RW);
LCD_Send4Bit(0x00);
delay_ms(20);
output_low(LCD_RS);
output_low(LCD_RW);
LCD_Send4Bit(0x03);
LCD_Enable();
delay_ms(5);
LCD_Enable();
delay_us(100);
LCD_Enable();
LCD_Send4Bit(0x02);
LCD_Enable();
LCD_SendCommand( 0x28 );      // giao thuc 4 bit, hien thi 2 hang, ki tu 5x8
LCD_SendCommand( 0x0c);       // cho phep hien thi man hinh
LCD_SendCommand( 0x06 );      // tang ID, khong dich khung hinh
LCD_SendCommand( 0x01 );      // xoa toan bo khung hinh
delay_ms(10);
}
void LCD_Gotoxy(unsigned char x, unsigned char y) //Toa do goc x=0, y=0
{
  unsigned char address;
  switch(y){
     case 0 : address=0x80+x ;break; 
     case 1 : address=0xc0+x ;break; 
     case 2 : address=0x94+x ;break; 
     case 3 : address=0xd4+x ;break; 
  }
  delay_us(300);
  LCD_SendCommand(address);
  delay_us(50);
}

// Ham Xoa Man Hinh LCD
void LCD_Clear()
{
  LCD_SendCommand(0x01);  
  delay_ms(10);
}
// Ham Gui 1 Ki Tu Len LCD
 void LCD_Put ( unsigned char Data )
{
 output_high(LCD_RS);
 LCD_SendCommand( Data );
 output_low(LCD_RS);
}
void LCD_Puts (char *s)
{
   while (*s)
   {
      LCD_Put(*s);
      s++;
   }
}





