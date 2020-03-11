/*
SD card datalogger, SPI communication 

 The circuit:
 * analog sensors on analog ins 0, 1, and 2
 * SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4


RTC(Real time clock),I2C communication 
SCL - A5
SDA - A4

All copyright reserved by MamunTech
Data:12-9-2017
*/

#include <SPI.h>
#include <SD.h>

#include <Wire.h>
#include "RTClib.h"
RTC_DS1307 RTC;

const int chipSelect = 4;

String data;

char a;
int w=0;
int x=0;
int y=0;

int a5mA = A0; //0.5ma                       // add the pin number that you want to control.
int b5mA = A1; //0.5ma
int c5mA = A2; //0.5ma
int d5mA = 10; //0.5ma
int e1mA = 9;  //0.1ma
int f1mA = 8;  //0.1ma
int g1mA = 7;  //0.1ma
int h1mA = 6;  //0.1ma
int i1mA = 5;  //0.1ma

void setup(){

Serial.begin(9600);


//RTC Initializing
    Wire.begin();
    
    RTC.begin();
 /* if (! RTC.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    RTC.adjust(DateTime(__DATE__, __TIME__));
  }
  */
  Serial.println("RTC is running!");

//SD card Initializing
   Serial.print("Initializing SD card...");

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("card initialized.");
  

//current output pin Initializing 
pinMode(a5mA,OUTPUT);
pinMode(b5mA,OUTPUT);
pinMode(c5mA,OUTPUT);
pinMode(d5mA,OUTPUT);
pinMode(e1mA,OUTPUT);
pinMode(f1mA,OUTPUT);
pinMode(g1mA,OUTPUT);
pinMode(h1mA,OUTPUT);
pinMode(i1mA,OUTPUT);
}

void loop() {

  while(Serial.available()&&(x==0 && y==0)){

                       a=Serial.read();
                    Serial.println(a); //for the debagging
                   

                            if(a=='O'){ 
                              dataStor();  //stor data to the memoray 
                              //Send current rating data to the app
                              delay(100);
                              Serial.println(w);
                              delay(100);
                              Serial.println(w);
                              }
                            if(a=='F'){   //stop the system and stor the time and current 
                              dataStor();  //stor data to the memoray 

                            digitalWrite(a5mA,LOW);
                            digitalWrite(b5mA,LOW);
                            digitalWrite(c5mA,LOW);
                            digitalWrite(d5mA,LOW);
                            digitalWrite(e1mA,LOW);
                            digitalWrite(f1mA,LOW);
                            digitalWrite(g1mA,LOW);
                            digitalWrite(h1mA,LOW);
                            digitalWrite(i1mA,LOW);
                              }
                      
                            if(a=='a'){                // 0.1ma
                            w=1;
                            output();
                            }
                            
                            if(a=='b'){               //0.2ma  
                            w=2;
                            output();
                            }
                            
                            if(a=='c'){                  //0.3ma
                            w=3;
                            output();
                            }
                            
                            if(a=='d'){                 //0.5ma
                            w=5;
                            output();
                            }
                            
                            if(a=='e'){                     //0.5ma
                            w=5;
                            output();
                            }
                            
                            if(a=='f'){                    //1ma
                            w=10;
                            output();
                            }
                            
                            if(a=='p'){   // adding sign (+)
                            x=1;
                            }
                            
                            if(a=='m'){  //subtractracting sign (-)
                            y=1;  
                            }
                            

                               while(x==1){

                                  a=Serial.read();
                                    
                                    if(a=='a'){                // 0.1ma
                                        w+=1;
                                        output();
                                        x=0;
                                         break;
                                       }
                            
                                    if(a=='b'){               //0.2ma  
                                     w+=2;
                                     output();
                                        x=0;
                                         break;
                                    }
                                    
                                    if(a=='c'){                  //0.3ma
                                      w+=3;
                                      output();
                                        x=0;
                                        break;
                                    }
                                    
                                    if(a=='d'){                 //0.5ma
                                      w+=5;
                                      output();
                                        x=0;
                                        break;
                                    }
                                    
                                    if(a=='e'){                     //0.5ma
                                      w+=5;
                                      output();
                                        x=0;
                                        break;
                                    }
                                    
                                    if(a=='f'){                    //1ma
                                      w+=10;
                                      output();
                                        x=0;
                                        break;
                                    }
                                    
                                    
                               }

                                    
                              while(y==1){

                                a=Serial.read();
                                    
                                    if(a=='a'){                // 0.1ma
                                        w-=1;
                                        output();
                                        y=0;
                                        break;
                                       }
                            
                                    if(a=='b'){               //0.2ma  
                                     w-=2;
                                     output();
                                        y=0;
                                        break;
                                    }
                                    
                                    if(a=='c'){                  //0.3ma
                                      w-=3;
                                      output();
                                        y=0;
                                        break;
                                    }
                                    
                                    if(a=='d'){                 //0.5ma
                                      w-=5;
                                      output();
                                        y=0;
                                        break;
                                    }
                                    
                                    if(a=='e'){                     //0.5ma
                                      w-=5;
                                      output();
                                        y=0;
                                        break;
                                    }
                                    
                                    if(a=='f'){                    //1ma
                                      w-=10;
                                      output();
                                        y=0;
                                        break;
                                    }   
                          }
                    }

}

void output(){
  if(w==1){        //0.1ma
    digitalWrite(a5mA,LOW); //0.5ma                    
    digitalWrite(b5mA,LOW);  //0.5ma
    digitalWrite(c5mA,LOW);  //0.5ma
    digitalWrite(d5mA,LOW);  //0.5ma
    digitalWrite(e1mA,LOW);  //0.1ma
    digitalWrite(f1mA,LOW);  //0.1ma
    digitalWrite(g1mA,LOW);  //0.1ma
    digitalWrite(h1mA,LOW);  //0.1ma
    
    digitalWrite(i1mA,HIGH);  //0.1ma
    }
    
  if(w==2){          //0.2ma
    digitalWrite(a5mA,LOW); //0.5ma  
    digitalWrite(b5mA,LOW);  //0.5ma
    digitalWrite(c5mA,LOW);  //0.5ma
    digitalWrite(d5mA,LOW);  //0.5ma
    digitalWrite(e1mA,LOW);  //0.1ma
    digitalWrite(f1mA,LOW);  //0.1ma
    digitalWrite(g1mA,LOW);  //0.1ma
    
    digitalWrite(h1mA,HIGH);  //0.1ma
    digitalWrite(i1mA,HIGH);  //0.1ma
    }
    
  if(w==3){             //0.3ma
    digitalWrite(a5mA,LOW); //0.5ma                    
    digitalWrite(b5mA,LOW);  //0.5ma
    digitalWrite(c5mA,LOW);  //0.5ma
    digitalWrite(d5mA,LOW);  //0.5ma
    digitalWrite(e1mA,LOW);  //0.1ma
    digitalWrite(f1mA,LOW);  //0.1ma
    
    digitalWrite(g1mA,HIGH);  //0.1ma
    digitalWrite(h1mA,HIGH);  //0.1ma
    digitalWrite(i1mA,HIGH);  //0.1ma
    }
    
  if(w==4){          //0.4ma
    digitalWrite(a5mA,LOW); //0.5ma                    
    digitalWrite(b5mA,LOW);  //0.5ma
    digitalWrite(c5mA,LOW);  //0.5ma
    digitalWrite(d5mA,LOW);  //0.5ma
    digitalWrite(e1mA,LOW);  //0.1ma
    
    digitalWrite(f1mA,HIGH);  //0.1ma
    digitalWrite(g1mA,HIGH);  //0.1ma
    digitalWrite(h1mA,HIGH);  //0.1ma
    digitalWrite(i1mA,HIGH);  //0.1ma
    }
    
  if(w==5){       //0.5ma
    digitalWrite(a5mA,LOW); //0.5ma                    
    digitalWrite(b5mA,LOW);  //0.5ma
    digitalWrite(c5mA,LOW);  //0.5ma
    digitalWrite(d5mA,LOW);  //0.5ma
    
    digitalWrite(e1mA,HIGH);  //0.1ma
    digitalWrite(f1mA,HIGH);  //0.1ma
    digitalWrite(g1mA,HIGH);  //0.1ma
    digitalWrite(h1mA,HIGH);  //0.1ma
    digitalWrite(i1mA,HIGH);  //0.1ma
    }
    
  if(w==6){      //0.6ma
    digitalWrite(a5mA,HIGH); //0.5ma  
                     
    digitalWrite(b5mA,LOW);  //0.5ma
    digitalWrite(c5mA,LOW);  //0.5ma
    digitalWrite(d5mA,LOW);  //0.5ma
    digitalWrite(e1mA,LOW);  //0.1ma
    digitalWrite(f1mA,LOW);  //0.1ma
    digitalWrite(g1mA,LOW);  //0.1ma
    digitalWrite(h1mA,LOW);  //0.1ma
    
    digitalWrite(i1mA,HIGH);  //0.1ma
    }
    
  if(w==7){          //0.7ma
    digitalWrite(a5mA,HIGH); //0.5ma  
                       
    digitalWrite(b5mA,LOW);  //0.5ma
    digitalWrite(c5mA,LOW);  //0.5ma
    digitalWrite(d5mA,LOW);  //0.5ma
    digitalWrite(e1mA,LOW);  //0.1ma
    digitalWrite(f1mA,LOW);  //0.1ma
    digitalWrite(g1mA,LOW);  //0.1ma
    
    digitalWrite(h1mA,HIGH);  //0.1ma
    digitalWrite(i1mA,HIGH);  //0.1ma
    }
    
  if(w==8){        //0.8ma
    digitalWrite(a5mA,HIGH); //0.5ma  
                       
    digitalWrite(b5mA,LOW);  //0.5ma
    digitalWrite(c5mA,LOW);  //0.5ma
    digitalWrite(d5mA,LOW);  //0.5ma
    digitalWrite(e1mA,LOW);  //0.1ma
    digitalWrite(f1mA,LOW);  //0.1ma
    
    digitalWrite(g1mA,HIGH);  //0.1ma
    digitalWrite(h1mA,HIGH);  //0.1ma
    digitalWrite(i1mA,HIGH);  //0.1ma
    }
    
  if(w==9){       //0.9ma
    digitalWrite(a5mA,HIGH); //0.5ma  
                       
    digitalWrite(b5mA,LOW);  //0.5ma
    digitalWrite(c5mA,LOW);  //0.5ma
    digitalWrite(d5mA,LOW);  //0.5ma
    digitalWrite(e1mA,LOW);  //0.1ma
    
    digitalWrite(f1mA,HIGH);  //0.1ma
    digitalWrite(g1mA,HIGH);  //0.1ma
    digitalWrite(h1mA,HIGH);  //0.1ma
    digitalWrite(i1mA,HIGH);  //0.1ma
    }
    
  if(w==10){      //1ma
    digitalWrite(a5mA,HIGH); //0.5ma  
                       
    digitalWrite(b5mA,LOW);  //0.5ma
    digitalWrite(c5mA,LOW);  //0.5ma
    digitalWrite(d5mA,LOW);  //0.5ma
    
    digitalWrite(e1mA,HIGH);  //0.1ma
    digitalWrite(f1mA,HIGH);  //0.1ma
    digitalWrite(g1mA,HIGH);  //0.1ma
    digitalWrite(h1mA,HIGH);  //0.1ma
    digitalWrite(i1mA,HIGH);  //0.1ma
    }
    
  if(w==11){       //1.1ma
    digitalWrite(a5mA,HIGH); //0.5ma                   
    digitalWrite(b5mA,HIGH);  //0.5ma
    
    digitalWrite(c5mA,LOW);  //0.5ma
    digitalWrite(d5mA,LOW);  //0.5ma
    digitalWrite(e1mA,LOW);  //0.1ma
    digitalWrite(f1mA,LOW);  //0.1ma
    digitalWrite(g1mA,LOW);  //0.1ma
    digitalWrite(h1mA,LOW);  //0.1ma
    
    digitalWrite(i1mA,HIGH);  //0.1ma
    }
    
  if(w==12){          //1.2ma
    digitalWrite(a5mA,HIGH); //0.5ma                     
    digitalWrite(b5mA,HIGH);  //0.5ma
    
    digitalWrite(c5mA,LOW);  //0.5ma
    digitalWrite(d5mA,LOW);  //0.5ma
    digitalWrite(e1mA,LOW);  //0.1ma
    digitalWrite(f1mA,LOW);  //0.1ma
    digitalWrite(g1mA,LOW);  //0.1ma
    
    digitalWrite(h1mA,HIGH);  //0.1ma
    digitalWrite(i1mA,HIGH);  //0.1ma
    }
    
  if(w==13){        //1.3ma
    digitalWrite(a5mA,HIGH); //0.5ma                   
    digitalWrite(b5mA,HIGH);  //0.5ma
    
    digitalWrite(c5mA,LOW);  //0.5ma
    digitalWrite(d5mA,LOW);  //0.5ma
    digitalWrite(e1mA,LOW);  //0.1ma
    digitalWrite(f1mA,LOW);  //0.1ma
    
    digitalWrite(g1mA,HIGH);  //0.1ma
    digitalWrite(h1mA,HIGH);  //0.1ma
    digitalWrite(i1mA,HIGH);  //0.1ma
    }
    
  if(w==14){       //1.4ma
    digitalWrite(a5mA,HIGH); //0.5ma                    
    digitalWrite(b5mA,HIGH);  //0.5ma
    
    digitalWrite(c5mA,LOW);  //0.5ma
    digitalWrite(d5mA,LOW);  //0.5ma
    digitalWrite(e1mA,LOW);  //0.1ma
    
    digitalWrite(f1mA,HIGH);  //0.1ma
    digitalWrite(g1mA,HIGH);  //0.1ma
    digitalWrite(h1mA,HIGH);  //0.1ma
    digitalWrite(i1mA,HIGH);  //0.1ma
    }
    
  if(w==15){    //1.5ma
    digitalWrite(a5mA,HIGH); //0.5ma                   
    digitalWrite(b5mA,HIGH);  //0.5ma
    
    digitalWrite(c5mA,LOW);  //0.5ma
    digitalWrite(d5mA,LOW);  //0.5ma
    
    digitalWrite(e1mA,HIGH);  //0.1ma
    digitalWrite(f1mA,HIGH);  //0.1ma
    digitalWrite(g1mA,HIGH);  //0.1ma
    digitalWrite(h1mA,HIGH);  //0.1ma
    digitalWrite(i1mA,HIGH);  //0.1ma
    }
    
  if(w==16){      //1.6ma
    digitalWrite(a5mA,HIGH); //0.5ma                
    digitalWrite(b5mA,HIGH);  //0.5ma
    digitalWrite(c5mA,HIGH);  //0.5ma
    
    digitalWrite(d5mA,LOW);  //0.5ma
    digitalWrite(e1mA,LOW);  //0.1ma
    digitalWrite(f1mA,LOW);  //0.1ma
    digitalWrite(g1mA,LOW);  //0.1ma
    digitalWrite(h1mA,LOW);  //0.1ma
    
    digitalWrite(i1mA,HIGH);  //0.1ma
    
    }
    
  if(w==17){      //1.7ma
    digitalWrite(a5mA,HIGH); //0.5ma                   
    digitalWrite(b5mA,HIGH);  //0.5ma
    digitalWrite(c5mA,HIGH);  //0.5ma
    
    digitalWrite(d5mA,LOW);  //0.5ma
    digitalWrite(e1mA,LOW);  //0.1ma
    digitalWrite(f1mA,LOW);  //0.1ma
    digitalWrite(g1mA,LOW);  //0.1ma
    
    digitalWrite(h1mA,HIGH);  //0.1ma
    digitalWrite(i1mA,HIGH);  //0.1ma
    }
    
  if(w==18){         //1.8ma
    digitalWrite(a5mA,HIGH); //0.5ma                   
    digitalWrite(b5mA,HIGH);  //0.5ma
    digitalWrite(c5mA,HIGH);  //0.5ma
    
    digitalWrite(d5mA,LOW);  //0.5ma
    digitalWrite(e1mA,LOW);  //0.1ma
    digitalWrite(f1mA,LOW);  //0.1ma
    
    digitalWrite(g1mA,HIGH);  //0.1ma
    digitalWrite(h1mA,HIGH);  //0.1ma
    digitalWrite(i1mA,HIGH);  //0.1ma
    }
    
  if(w==19){       //1.9ma
    digitalWrite(a5mA,HIGH); //0.5ma                
    digitalWrite(b5mA,HIGH);  //0.5ma
    digitalWrite(c5mA,HIGH);  //0.5ma
    
    digitalWrite(d5mA,LOW);  //0.5ma
    digitalWrite(e1mA,LOW);  //0.1ma
    
    digitalWrite(f1mA,HIGH);  //0.1ma
    digitalWrite(g1mA,HIGH);  //0.1ma
    digitalWrite(h1mA,HIGH);  //0.1ma
    digitalWrite(i1mA,HIGH);  //0.1ma
    }
    
  if(w==20){          //2ma
    digitalWrite(a5mA,HIGH); //0.5ma                   
    digitalWrite(b5mA,HIGH);  //0.5ma
    digitalWrite(c5mA,HIGH);  //0.5ma
    
    digitalWrite(d5mA,LOW);  //0.5ma
    
    digitalWrite(e1mA,HIGH);  //0.1ma
    digitalWrite(f1mA,HIGH);  //0.1ma
    digitalWrite(g1mA,HIGH);  //0.1ma
    digitalWrite(h1mA,HIGH);  //0.1ma
    digitalWrite(i1mA,HIGH);  //0.1ma
    }
    
  if(w==21){         //2.1ma
    digitalWrite(a5mA,HIGH); //0.5ma              
    digitalWrite(b5mA,HIGH);  //0.5ma
    digitalWrite(c5mA,HIGH);  //0.5ma
    digitalWrite(d5mA,HIGH);  //0.5ma
    
    digitalWrite(e1mA,LOW);  //0.1ma
    digitalWrite(f1mA,LOW);  //0.1ma
    digitalWrite(g1mA,LOW);  //0.1ma
    digitalWrite(h1mA,LOW);  //0.1ma
    
    digitalWrite(i1mA,HIGH);  //0.1ma
    }
    
  if(w==22){       //2.2ma
    digitalWrite(a5mA,HIGH); //0.5ma                 
    digitalWrite(b5mA,HIGH);  //0.5ma
    digitalWrite(c5mA,HIGH);  //0.5ma
    digitalWrite(d5mA,HIGH);  //0.5ma
    
    digitalWrite(e1mA,LOW);  //0.1ma
    digitalWrite(f1mA,LOW);  //0.1ma
    digitalWrite(g1mA,LOW);  //0.1ma
    
    digitalWrite(h1mA,HIGH);  //0.1ma
    digitalWrite(i1mA,HIGH);  //0.1ma
    }
    
  if(w==23){  //2.3ma
    digitalWrite(a5mA,HIGH); //0.5ma                   
    digitalWrite(b5mA,HIGH);  //0.5ma
    digitalWrite(c5mA,HIGH);  //0.5ma
    digitalWrite(d5mA,HIGH);  //0.5ma
    
    digitalWrite(e1mA,LOW);  //0.1ma
    digitalWrite(f1mA,LOW);  //0.1ma
    
    digitalWrite(g1mA,HIGH);  //0.1ma
    digitalWrite(h1mA,HIGH);  //0.1ma
    digitalWrite(i1mA,HIGH);  //0.1ma
    }
    
  if(w==24){   //2.4ma
    digitalWrite(a5mA,HIGH); //0.5ma                    
    digitalWrite(b5mA,HIGH);  //0.5ma
    digitalWrite(c5mA,HIGH);  //0.5ma
    digitalWrite(d5mA,HIGH);  //0.5ma
    
    digitalWrite(e1mA,LOW);  //0.1ma
    
    digitalWrite(f1mA,HIGH);  //0.1ma
    digitalWrite(g1mA,HIGH);  //0.1ma
    digitalWrite(h1mA,HIGH);  //0.1ma
    digitalWrite(i1mA,HIGH);  //0.1ma
    }
    
  if(w==25){   //2.5ma
    digitalWrite(a5mA,HIGH); //0.5ma           
    digitalWrite(b5mA,HIGH);  //0.5ma
    digitalWrite(c5mA,HIGH);  //0.5ma
    digitalWrite(d5mA,HIGH);  //0.5ma
    digitalWrite(e1mA,HIGH);  //0.1ma
    digitalWrite(f1mA,HIGH);  //0.1ma
    digitalWrite(g1mA,HIGH);  //0.1ma
    digitalWrite(h1mA,HIGH);  //0.1ma
    digitalWrite(i1mA,HIGH);  //0.1ma
    }
}

void dataStor() {

  //time and current 
    DateTime now = RTC.now();
    data="Date:";
    data+= String(now.year(), DEC);
    data+="/";
    data+=String(now.month(), DEC);
    data+="/";
    data+=String(now.day(), DEC);
    

    data+=", Time:";
    
    data+=String(now.hour(), DEC);
    data+="-";
    data+=String(now.minute(), DEC);
    data+="-";
    data+=String(now.second(), DEC);

    data+=", Current:";
    data+=String(w);
    data+=",";
    
    Serial.print(data);
    Serial.println(); 
    delay(1000);



  //stor time and data
    File dataFile = SD.open("datalog.txt", FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile) {
    dataFile.println(data);
    dataFile.close();
    // print to the serial port too:
    Serial.println(data);
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
  }
}
