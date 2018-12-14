/*******************************************************************************
  * File      :        MPU6050.h
  * Author    :        Ngo Tran Khanh Dang BK
  * Version   :        1.0
  * Date      :        26-03-2014
  * Summary   :        Thu vien MPU6050 dung chuyen cho trinh bien dich CCS
                       Co su dung kem theo mot so ham cua thu vien LCD16x2
//*****************************************************************************/
/******************************************************************************/
//Luu y: gia tri doc ve tu MPU6050 thuong la 16bit

//=================== Khai bao cac thanh ghi cho MPU6050 =====================//
// Tra data sheet de co cac thong so nay
#define   SMPLRT_DIV      0x19   //0x07(125Hz)
#define   CONFIG          0x1A   //0x06(5Hz)
#define   GYRO_CONFIG     0x1B   //0x18(不自检，2000deg/s)
#define   ACCEL_CONFIG    0x1C   //0x01(不自检，2G，5Hz)
#define   ACCEL_XOUT_H    0x3B
#define   ACCEL_XOUT_L    0x3C
#define   ACCEL_YOUT_H    0x3D
#define   ACCEL_YOUT_L    0x3E
#define   ACCEL_ZOUT_H    0x3F
#define   ACCEL_ZOUT_L    0x40
#define   TEMP_OUT_H      0x41
#define   TEMP_OUT_L      0x42
#define   GYRO_XOUT_H     0x43
#define   GYRO_XOUT_L     0x44   
#define   GYRO_YOUT_H     0x45
#define   GYRO_YOUT_L     0x46
#define   GYRO_ZOUT_H     0x47
#define   GYRO_ZOUT_L     0x48
#define   USER_CTRL       0x6A
#define   PWR_MGMT_1      0x6B
#define   WHO_AM_I        0x75

#define mpu6050 0xD0  //Dia chi cua cam bien mpu6050 co 7 bit doi sang trai 1 bit de set read or write
#use i2c(Master,Fast,sda=PIN_C4,scl=PIN_C3)
#use DELAY(clock=22118400)
//=============================================================================//
//Ham Display_Value ===========================================================//
//    Ham nay phai dung chung voi thu vien LCD 16x2 or tuong duong
//    value gia tri muon xuat hien tren LCD
//    Hien thi gia tri value tren LCD tai vi tri dong x va cot thu y
void Display_Value(float value, unsigned char x, unsigned char y)
{
   ///LCD_Gotoxy(x,y);
   //LCD_Puts(dis);
}


//Ham Mpu6050_Read =============================================================//
// Ham nay dung de doc gia tu cam bien MPU6050
// Luu y la dia chi cua MPU6050 duoc gan truoc boi bien hang: "mpu6050"
// Du lieu dau vao cua ham la dia chi thanh ghi MPU6050 "address"
// Ham se tra ve gia tri 8bit
unsigned char Mpu6050_Read(unsigned char address)
   {
//Doan code duoi day viet cho dong Atem
/*   bit AckTemp=1;          // Bit kiem tra Ack trong giao tiep I2C
   unsigned char Data;     // Khai bao bien Data
   I2C_Start();            // Khoi dong truyen I2C
   I2C_Write(mpu6050);     // Truyen/ghi dia chi den MPU6050
   AckTemp=I2C_CheckAck(); // Slave bao da nhan duoc du lieu
   I2C_Write(address);     // Truyen/ghi dia chi den MPU6050  
   AckTemp=I2C_CheckAck(); // Slave bao da nhan duoc du lieu
   I2C_Start();            // Khoi dong lai I2C
   I2C_Write(mpu6050+1);   // Set MPU6050 truyen du lieu ve Master
   AckTemp=I2C_CheckAck(); // Slave bao da nhan duoc du lieu
   Data=I2C_Read();        // Doc du lieu tu MPU6050 ve Master
   AckTemp=I2C_CheckAck(); // Bao da nhan du lieu xong
   I2C_Stop();             // Ket thuc qua trinh truyen nhan I2C
   return Data; //*/       // Tra ve gia tri doc duoc cho bien Data
   
//Doan code viet cho PIC, dung CCS
   int8 Data;     // Khai bao bien Data
   i2c_start();            // start condition
   i2c_write(mpu6050);     // Truyen/ghi dia chi den MPU6050
   i2c_write(address);     // Chon dia chi thanh ghi address cua MPU6050
   i2C_start();            // Khoi dong lai I2C
   i2C_write(mpu6050|1);   // Set MPU6050 truyen du lieu ve Master
   Data=i2C_read(0);       // Doc du lieu tu MPU6050 ve Master
   i2c_stop();             // Ngung truyen nhan I2C
   return Data; //*/       // Tra ve gia tri doc duoc cho bien Data
   }


//Ham GetData =============================================================//
// Day la ham doc du lieu ve tu MPU6050. Ham nay dung chung voi ham Mpu6050_Read
// Ham nay khong co doi so. Ham nay co gia tri tra ve la gia tri doc duoc tu
//    cam bien MPU6050
// Gia tri nhap vao ham la dia chi thanh ghi cua MPU6050
// Du lieu nhan ve thuong la 16bit
int16 GetData(unsigned char address)
{
   int16 H=0,L=0;
//================================//
   i2c_start();            // start condition
   i2c_write(mpu6050);     // Truyen/ghi dia chi den MPU6050
   i2c_write(address);     // Chon dia chi thanh ghi address cua MPU6050
   i2C_start();            // Khoi dong lai I2C
   i2C_write(mpu6050|1);   // Set MPU6050 truyen du lieu ve Master
   H=i2C_read();           // Doc du lieu tu MPU6050 ve Master (8 bit cao)
   L=i2C_read(0);          // Doc du lieu tu MPU6050 ve Master (8 bit cao)
   i2c_stop();             // Ngung truyen nhan I2C
//==================================================//
//!   H=Mpu6050_Read(address);
//!   L=Mpu6050_Read(address+1);
   return (H<<8)|L;
}
   

//Ham Mpu6050_Write ==========================================================//
// Ham nay dung de set dia chi thanh ghi cho MPU6050
// Luu y la dia chi cua MPU6050 duoc gan truoc boi bien hang: "mpu6050"
// Du lieu dau vao cua ham la dia chi thanh ghi MPU6050 "address"
// kem theo chuoi "data" muon truyen di
void Mpu6050_Write(unsigned char address,unsigned char Data)
   {
//Doan code duoi day viet cho dong Atem
/*   bit AckTemp=1;          // Bit kiem tra Ack trong giao tiep I2C
   I2C_Start();            // Khoi dong truyen I2C
   I2C_Write(mpu6050);     // Truyen/ghi dia chi den MPU6050
   AckTemp=I2C_CheckAck(); // Slave bao da nhan duoc du lieu
   I2C_Write(address);     // Chon dia chi thanh ghi address cua MPU6050
   AckTemp=I2C_CheckAck(); // Slave bao da nhan duoc du lieu
   I2C_Write(Data);        // Ghi du lieu Data vao vi tri thanh ghi
   AckTemp=I2C_CheckAck(); // Slave bao da nhan duoc du lieu
   I2C_Stop();  //*/       // Ngung truyen nhan I2C

//Doan code viet cho PIC, dung CCS
   i2c_start();            // start condition
   i2c_write(mpu6050);     // Truyen/ghi dia chi den MPU6050
   i2c_write(address);     // Chon dia chi thanh ghi address cua MPU6050
   i2c_write(Data);        // Ghi du lieu Data vao vi tri thanh ghi
   i2c_stop();  //*/       // Ngung truyen nhan I2C
   }


//Ham Mpu6050_Init ============================================================//
// Ham nay de set che do lam viec cho MPU6050
// Ham nay khong co doi so. Va khong co gia tri tra ve.
// Day la ham duoc viet dua tren ham Mpu6050_Write
void Mpu6050_Init()
   {
//Tat ca thong so trong cac ham duoi day deu duoc khai bao dia chi truoc
//  hoac tra data sheet cua MPU6050
   Mpu6050_Write(PWR_MGMT_1,0X80); // Moi nhet vo nen chua tra lai
   delay_ms(5);
   Mpu6050_Write(PWR_MGMT_1, 0x00);   // Thanh ghi thu 107 cua MPU6050 duoc set
                                      //      Dung xung noi,bat sensor nhiet do,...
   Mpu6050_Write(SMPLRT_DIV, 0x07);   // Thanh ghi thu 25 cua MPU6050 duoc set
                                      //      sao cho du lieu xuat ra o tan so 1kHz // Set the sample rate to 1000Hz - 8kHz/(7+1) = 1000Hz
   Mpu6050_Write(CONFIG, 0x00);       // Thanh ghi thu 26 cua MPU6050 duoc set
                                      // Disable FSYNC and set 260 Hz Acc filtering, 256 Hz Gyro filtering, 8 KHz sampling
   Mpu6050_Write(GYRO_CONFIG, 0x00);  // Thanh ghi thu 27 cua MPU6050 duoc set
                                      //      Detect goc xoay +_ 250degree/s
   Mpu6050_Write(ACCEL_CONFIG, 0x00); // Thanh ghi thu 28 cua MPU6050 duoc set
                                      //      Detect gia toc +_ 2.g
   Mpu6050_Write(USER_CTRL, 0x00);    // 0X6A disable FIFO, disable master mode
   Mpu6050_Write(PWR_MGMT_1, 0x01);   // PLL with X axis gyroscope reference and disable sleep mode
   delay_ms(10);
   }

//============================== END OF FILE ===================================//
