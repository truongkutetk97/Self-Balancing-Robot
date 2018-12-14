#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
char auth[] = "1fa6fe7a6ea5495c8ee9db797900fa18";
char ssid[] = "linhtran_electronics";
char pass[] = "Khongbiet113";
int t=100;
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



void setup()
{  
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  //inputString.reserve(200);
  pinMode(LED_BUILTIN, OUTPUT); 
//  int t=0;timer.setInterval(200L, myTimerEvent);
  Blynk.run();
  
}

void loop()
{  
  Blynk.run();//  timer.run();
  if((millis()-mili)>=250)//send get data marker to pic's uart interrupt
  {
    Serial.print('c');
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
      //Serial.println("Processing.......");
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
       // Serial.print("This just in ... ");
       // Serial.println(receivedChars);//Serial.println(valuePos[0]);
        newData = false;
         Blynk.virtualWrite(V0, target[0]);
         Blynk.virtualWrite(V1, target[1]);
         Blynk.virtualWrite(V2, target[2]);
         Blynk.virtualWrite(V3, target[3]);
         Blynk.virtualWrite(V4, target[4]);
         Blynk.virtualWrite(V5, target[5]);
       
    }
}