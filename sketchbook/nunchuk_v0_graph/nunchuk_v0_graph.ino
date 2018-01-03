#include <Wire.h>

uint8_t cnt;
uint8_t input_raw[6];
uint8_t numi;
uint8_t print_setup=0;
void setup() {
 
  delay(200);
  Serial.begin(9600);
  nbegin();
  nupdate();
//  ncalibrateJoy();
}

void loop() {
  delay(20);
  nupdate(); 
 // delay(500);
 // Serial.println("---------------------");
 // Serial.println(input_raw[0]);
  print_graph();
}


void nbegin() 
        {
            Wire.begin();
            cnt = 0;
            Wire.beginTransmission(0x52);	// device address
            Wire.write(0xF0);
            Wire.write(0x55);
            Wire.endTransmission();
            delay(1);
            Wire.beginTransmission(0x52);
            Wire.write(0xFB);
            Wire.write((uint8_t)0x00);

            Wire.endTransmission();
            nupdate();            
            }


        void nupdate() {

 Wire.requestFrom (0x52, 6);	// request data from nunchuck
            while (Wire.available ()) {
                // receive byte as an integer
                numi=Wire.read();
                //Serial.print(cnt);
                //Serial.print(": ");
                //Serial.println(numi);//status[cnt] = _nunchuk_decode_byte (Wire.read()); //
                input_raw[cnt]=numi;
                cnt++;
            }
            if (cnt > 5) {
                nsend_zero(); // send the request for next bytes

            }
        }

void nsend_zero()
        {
            Wire.beginTransmission (0x52);	// transmit to device 0x52
            Wire.write ((uint8_t)0x00);		// sends one byte
            Wire.endTransmission ();	// stop transmitting
            cnt=0;
        }

void print_graph(){
uint8_t x = input_raw[print_setup];
for (int i=0; i<=(x/3); i++){
  Serial.print(".");
}
Serial.println(" ");

}
