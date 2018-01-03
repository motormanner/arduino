/*
  AnalogReadSerial
 Reads an analog input on pin 0, prints the result to the serial monitor 
 
 This example code is in the public domain.
 */
int dataCollectionRep=0;
int s1=0;
int s2=0;
int s3=0;
int s4=0;
int summ1=0;
int summ2=2;
int summ3=3;
int summ4=0;
boolean printFlag = 0;
boolean pairFlag = 0;
int setTemp = 200;

void setup() {
  Serial.begin(9600); // msp430g2231 must use 4800
  pinMode(A0, INPUT);
pinMode(A3, INPUT);
pinMode(A4, INPUT);
pinMode(A5, INPUT);
pinMode(9, OUTPUT);
pinMode(11, OUTPUT);
pinMode(12, OUTPUT);
pinMode(13, OUTPUT);
pinMode(14, OUTPUT);

}

void loop() {
dataCollector();
dataDigester();
dataCollectionRep++;

if (printFlag){
actuator();
printOut();
printFlag=0;
}

  delay (100);
}

void dataCollector(){
 s1 = analogRead(A0);
 s2 = analogRead(A3);
 s3 = analogRead(A4);
 s4 = analogRead(A5);

}

void printOut(){
  Serial.print(s1);
  Serial.print(" | ");
  Serial.print(s2);
  Serial.print(" | ");
  Serial.print(s3);
  Serial.print(" | ");
  Serial.println(s4);
  if (pairFlag)  Serial.println("pair");
  else Serial.println("unpair");
}

void dataDigester(){
  if (!printFlag){
summ1=summ1+s1;
summ2=summ2+s2;
summ3=summ3+s3;
summ4=summ4+s4;
  }
if (dataCollectionRep>=10){
s1=summ1 / 11;
s2=summ2 / 11;
s3=summ3 / 11;
s4=summ4 / 11;
summ1=0;
summ2=0;
summ3=0;
summ4=0;
printFlag=1;
dataCollectionRep=0;
}
}

void actuator(){
if (pairFlag){
  digitalWrite(11, 0);
  digitalWrite(12, 0);
  digitalWrite(13, 0);
  digitalWrite(14, 0);
pinMode(11, OUTPUT);
pinMode(12, OUTPUT);
pinMode(13, INPUT);
pinMode(14, INPUT);
  if (setTemp >= s1)digitalWrite(11, 1);
  if (setTemp >= s2)digitalWrite(12, 1);
  
}
else {
  digitalWrite(11, 0);
  digitalWrite(12, 0);
  digitalWrite(13, 0);
  digitalWrite(14, 0);
pinMode(11, INPUT);
pinMode(12, INPUT);
pinMode(13, OUTPUT);
pinMode(14, OUTPUT);
  if (setTemp >= s3)digitalWrite(13, 1);
  if (setTemp >= s4)digitalWrite(14, 1);
}
if (pairFlag == 0)pairFlag=1;
else pairFlag=0;

}
