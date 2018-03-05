#include <ESP8266WiFi.h>
#include <WiFiUDP.h>
 


WiFiUDP UDP;                              //
char buff[32];                            //
const char ssid[]="ESP8266";              // wifi ssid
const char pass[]="12345678";             // wifi password
const char iPhoneIP[]   = "192.168.4.2";  // iPhone/Ipad iP
const int  iPhoneTxPort = 7000;           // UDP Tx port
const int  iPhoneRxPort = 9000;           // UDP Rx port
String all;                               //
  

 
void setup() {
 
  Serial.begin(115200);Serial.println();      
  pinMode(D0, OUTPUT); digitalWrite(D0, LOW); 
  pinMode(D1, OUTPUT); digitalWrite(D1, LOW);  
  pinMode(D2, OUTPUT); digitalWrite(D2, LOW);  
  pinMode(D3, OUTPUT); digitalWrite(D3, LOW);  
 
  WiFi.softAP(ssid, pass);                      // WiFi connect
  UDP.begin(iPhoneTxPort);                      // iPhoneTxPort
}
 
void loop() {
 
  ESP.wdtDisable();                             //
  int rx = UDP.parsePacket();                   // packet size
  if (rx){                                      // recive
    int len = UDP.read(buff, rx);               // rx lengs
    if (len > 0){                               // rx action
      buff[len] = '\0';                         // Termination char
      int c = buff[0];                          // head haracter
      if ( c == '0' ){ all_clear();}            // 0, all off
      if ( c == '1' ){ sw(D0, 1);}              // 1, LED 1 on/off
      if ( c == '2' ){ sw(D1, 2);}              // 2, LED 2 on/off
      if ( c == '3' ){ sw(D2, 3); }             // 3, LED 3 on/off
      if ( c == '4' ){ sw(D3, 4);}              // 4, LED 4 on/off
      if ( c == '5' ){ allread();}              // 7, all read
      c = '9';                                  //
    }                                           //
  }                                             //
} 

void sw(int pin, int n){                       // gpio feed back
  if ( digitalRead(pin) == 0 ){                // gpio ck = LOW
       digitalWrite(pin, HIGH);                // SET LED ON 
       UDP.beginPacket(iPhoneIP, iPhoneRxPort); // UDP
       UDP.print( String(n) + "H");             // return LED ON 
       UDP.endPacket();                         // UDP
  } else {                                      // gpio ck = HI
       digitalWrite(pin, LOW );                // SET LED OFF
       UDP.beginPacket(iPhoneIP, iPhoneRxPort); // UDP
       UDP.print( String(n) + "L");             // return LED OFF 
       UDP.endPacket();                         // UDP
  }                                             //
}                                               //
 
void all_clear(){                               // 
  ESP.wdtDisable();                             //
  all = "";                                     //
  digitalWrite(D0, LOW); io(D0, 1);  
  digitalWrite(D1, LOW); io(D1, 2); 
  digitalWrite(D2, LOW); io(D2, 3);           
  digitalWrite(D3, LOW); io(D3, 4);
  UDP.beginPacket(iPhoneIP, iPhoneRxPort);      // UDP feed back
  UDP.print( all );                             // 1L2L3L4L5L6L
  UDP.endPacket();                              // UDP
}
 
void allread(){                                 //
  ESP.wdtDisable();                             //
  all = "";                                     //
  io(D0, 1);
  io(D1, 2);
  io(D2, 3);
  io(D3, 4);
  UDP.beginPacket(iPhoneIP, iPhoneRxPort);      //
  UDP.print( all );                             // 1x2x3x4x5x6x
  UDP.endPacket();                              //
}    

void io(int pin, int n){
  if ( digitalRead(pin) == 0 ){                  
    all = all + String(n) + "L";
  } else {                                      
    all = all + String(n) + "H";
  }       
  
}
 
