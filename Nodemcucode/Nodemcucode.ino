#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
char auth[] = "1fa6fe7a6ea5495c8ee9db797900fa18";
char ssid[] = "TRUONG DEP TRAI";
char pass[] = "123444444";
int t=100;
int j=1;
const byte numChars = 64;
char receivedChars[numChars];   // an array to store the received data
char tempChars[numChars]; 
boolean newData = false;
int valuePos[numChars];
float value[numChars];
int numPos=0;
String target[10];
char targetstring[numChars];
BlynkTimer timer;
int pinValue;
long mili=millis();
long kp=250,ki=100,kd=200;
double setpoint=180,offset=10,movepoint = 180;
int tempoo, tempo,tempi;
int increoffset=0, decreoffset=0, itemp=0;
int updateoffset=0;
float x=5,y=5;
float k= 0.5;
int start = 0;
BLYNK_WRITE(V10)
{
  kp = param.asInt(); // assigning incoming value from pin V1 to a variable
  Blynk.virtualWrite(V0,kp );
}
BLYNK_WRITE(V11)
{
  ki = param.asInt(); // assigning incoming value from pin V1 to a variable
  Blynk.virtualWrite(V1,ki );
}
BLYNK_WRITE(V12)
{
  kd = param.asInt(); // assigning incoming value from pin V1 to a variable
  Blynk.virtualWrite(V2,kd );
}
BLYNK_WRITE(V6)
{
    int temp = param.asInt(); // assigning incoming value from pin V1 to a variable
  if(temp>tempoo) setpoint=setpoint+ 0.5;
  else if ( temp<tempoo) setpoint=setpoint-0.5;
  tempoo=temp;
   movepoint= setpoint;
}
BLYNK_WRITE(V7)
{
  int temp = param.asInt(); // assigning incoming value from pin V1 to a variable
  if(temp>tempo) setpoint=setpoint+ 0.1;
  else if ( temp<tempo) setpoint=setpoint-0.1;
  tempo=temp;
   movepoint= setpoint;
}
BLYNK_WRITE(V8)
{
  int temp = param.asInt(); // assigning incoming value from pin V1 to a variable
  setpoint=target[0].toFloat();
  movepoint= setpoint;
}
BLYNK_WRITE(V9)
{
  start = param.asInt(); // assigning incoming value from pin V1 to a variable
}
BLYNK_WRITE(V18)
{
   updateoffset = param.asInt(); // assigning incoming value from pin V1 to a variable
}
BLYNK_WRITE(V16)
{
  x = param[0].asInt(); 
   y = param[1].asInt();
   setpoint = movepoint + (y-500)/100*k;
}
BLYNK_WRITE(V20)
{
  k = (float)param.asInt()/5; // assigning incoming value from pin V1 to a variable
   Blynk.virtualWrite(V21, k); 
}
void setup()
{  
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  pinMode(LED_BUILTIN, OUTPUT); 
  Blynk.run();
  Blynk.virtualWrite(V10,100);Blynk.virtualWrite(V11,100);Blynk.virtualWrite(V12,100);
}
void loop()
{ 
  Blynk.run();//  timer.run();
  if((millis()-mili)>=150)//send get data marker to pic's utMart interrupt
  {
    Serial.print('#');
    Serial.print(start);
    Serial.print("2345");
    Serial.print(kp);
    Serial.print(ki);
    Serial.print(kd);
    Serial.print(long ((setpoint*100)) );
    Serial.print("xy");//pppiiiddd
    Serial.print('@');
    mili=millis();
  }
  recvWithStartEndMarkers();//move data from uart to buffer, receivedChars
  if(valuePos[0]!=0&&newData==true)//decrypt data function 
  {
    int i=0;
    for(int k=0;k<numPos/2;k++)
    {
      target[k]="";
      for(int j=0;j<(valuePos[k*2+1]-valuePos[k*2]-1);j++)
      {// targetstring[j]=receivedChars[valuePos[0]+j];
       target[k]+=receivedChars[valuePos[k*2]+j];   //valuepos
      }  //Serial.println(target[k]);
    }
    valuePos[0]=0;
    numPos=0;
  }
  showNewData();// send data from nodemcu to blynk
}
void recvWithStartEndMarkers() {
    static boolean recvInProgress = false;
    static byte ndx = 0;
    char startMarker = '<';
    char endMarker = '>';
    char rc;
    while (Serial.available() > 0 && newData == false) {
        rc = Serial.read();
        if (recvInProgress == true) {
            if (rc != endMarker) {
             if(rc=='$') 
               {
                valuePos[numPos]=ndx+1;
                numPos++;
               }
                receivedChars[ndx] = rc;
                ndx++;
                if (ndx >= numChars) {
                    ndx = numChars - 1;
                }
            }
            else {
                receivedChars[ndx] = '\0'; // terminate the string
                recvInProgress = false;
                ndx = 0;
                newData = true;
            }
        }
        else if (rc == startMarker) {
            recvInProgress = true;
        }
    }
}
void showNewData() {
    if (newData == true) {
        newData = false;
        Blynk.virtualWrite(V3, target[0]);
        if(updateoffset==1)
        {
          Blynk.virtualWrite(V4, target[1]);// 
          Blynk.virtualWrite(V5, target[2]); 
        }
    }
}
