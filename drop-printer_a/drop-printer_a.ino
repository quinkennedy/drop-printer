#include "SoftwareSerial.h"
#include "Adafruit_Thermal.h"
#include "drop1.h"
#include <avr/pgmspace.h>

int printer_RX_Pin = 5; // green
int printer_TX_Pin = 6; // yellow
const int maxWidth = 384;

Adafruit_Thermal printer(printer_RX_Pin, printer_TX_Pin);

void setup(){
  Serial.begin(9600);
  printer.begin();
}

void loop(){
  // printer.printBitmap(drop1_width, drop1_height, drop1_data);
  /*
  int arrSize = ((drop1_width+7)/8)*drop1_height;
uint8_t drop[arrSize];
for(int i = 0 ; i < arrSize; i++){
  drop[i] = pgm_read_byte(drop1_data+i);
}
printer.printBitmap(drop1_width, drop1_height, drop, false);/**/
  if (random(10) < 8){
    printer.println("");
  } else {
    uint8_t padding = random((maxWidth - drop1_width)/8);
    uint8_t byteWidth = (uint8_t)((drop1_width+7)/8);
    uint8_t drop[((int)padding+byteWidth)*drop1_height];
    for(uint8_t j = 0; j < drop1_height; j++){
      for(uint8_t i = 0; i < (padding + byteWidth); i++){
        if (i < padding){
          drop[j*((int)padding+byteWidth)+i] = 0x00;
        } else {
          drop[j*((int)padding+byteWidth)+i] = pgm_read_byte(drop1_data+((int)j)*byteWidth+i-padding);
        }
      }
    }
    printer.printBitmap(((int)padding)*8 + drop1_width, drop1_height, drop, false);
  }
  printer.timeoutWait();
  /**/
}
