#ifndef data_h
#define data_h

static uint8_t data_macBuffer;
static char data_vendorBuffer;
static String data_vendorStrBuffer = "";

static char data_websiteBuffer[6500];

/*
I used the program memory (https://www.arduino.cc/en/Reference/PROGMEM) so I don't need an external SD card reader to hold the HTML files and the very ling vendor list.
Alternatively you could use the SPIFFS memory on the ESP8266: https://github.com/esp8266/Arduino/blob/master/doc/filesystem.md#file-system-object-spiffs

The HTML files are minified and converted into bytes. Use the minifier.html in the htmlfiles folder to do the same.
For files larger then 6000 bytes change the size of data_websiteBuffer.
The vendor list contains 11 bytes per row. The first 3 bytes are the beginning mac adress and the other 8 are the vendorname.
*/

const static char data_error404[] PROGMEM = "<html><head><meta charset='utf-8'></head><body><h1>ERROR 404</h1><p>¯\\_(ツ)_/¯ </p></body></html>";
const static uint8_t data_styleCSS[] PROGMEM = {02};
const static uint8_t data_functionsJS[] PROGMEM = {0xx7d};
const static uint8_t data_manifest[] PROGMEM = {0x77d};

const static uint8_t data_indexHTML[] PROGMEM = {0x3c,
const static uint8_t data_clientsHTML[] PROGMEM = {0x3c,
const static uint8_t data_attackHTML[] PROGMEM = {0x3c,
const static uint8_t data_settingsHTML[] PROGMEM = {0x3c,
/*
Based on Wireshark manufacturer database
source: https://www.wireshark.org/tools/oui-lookup.html
Wireshark is released under the GNU General Public License version 2
*/

const static uint8_t data_vendors[] PROGMEM = {
0x00,0x00,0x01,0x53,0x75,0x70,0x65,0x72,0x6C,0x61,0x6E,
/**/
0xFC,0xFF,0xAA,0x49,0x65,0x65,0x65,0x52,0x65,0x67,0x69
};

String data_getVendor(uint8_t first,uint8_t second,uint8_t third){
  data_vendorStrBuffer = "";
  
  for(int i=0;i<sizeof(data_vendors)/11;i++){

    data_macBuffer = pgm_read_byte_near(data_vendors + i*11 + 0);
    if(data_macBuffer == first){
      data_macBuffer = pgm_read_byte_near(data_vendors + i*11 + 1);
      if(data_macBuffer == second){
        data_macBuffer = pgm_read_byte_near(data_vendors + i*11 + 2);
        if(data_macBuffer == third){

          for(int h=0;h<8;h++){
            data_vendorBuffer = (char)pgm_read_byte_near(data_vendors + i*11 + 3 + h);
            if(data_vendorBuffer != 0x00) data_vendorStrBuffer += data_vendorBuffer;
          }
          return data_vendorStrBuffer;
        }

      }
    }

  }

  return data_vendorStrBuffer;
}

char* data_getIndexHTML(){
  int _size = sizeof(data_indexHTML);
  for(int i=0;i<sizeof(data_websiteBuffer);i++){
    if(i<_size) data_websiteBuffer[i] = pgm_read_byte_near(data_indexHTML + i);
    else data_websiteBuffer[i] = 0x00;
  }
  return data_websiteBuffer;
}

char* data_getManifest(){
  int _size = sizeof(data_manifest);
  for(int i=0;i<sizeof(data_websiteBuffer);i++){
    if(i<_size) data_websiteBuffer[i] = pgm_read_byte_near(data_manifest + i);
    else data_websiteBuffer[i] = 0x00;
  }
  return data_websiteBuffer;
}

char* data_get404(){
  int _size = sizeof(data_error404);
  for(int i=0;i<sizeof(data_websiteBuffer);i++){
    if(i<_size) data_websiteBuffer[i] = pgm_read_byte_near(data_error404 + i);
    else data_websiteBuffer[i] = 0x00;
  }
  return data_websiteBuffer;
}

char* data_getStyle(){ /*   get style  ヽ(ヅ)ノ   */
  int _size = sizeof(data_styleCSS);
  for(int i=0;i<sizeof(data_websiteBuffer);i++){
    if(i<_size) data_websiteBuffer[i] = pgm_read_byte_near(data_styleCSS + i);
    else data_websiteBuffer[i] = 0x00;
  }
  return data_websiteBuffer;
}

char* data_getFunctionsJS(){
  int _size = sizeof(data_functionsJS);
  for(int i=0;i<sizeof(data_websiteBuffer);i++){
    if(i<_size) data_websiteBuffer[i] = pgm_read_byte_near(data_functionsJS + i);
    else data_websiteBuffer[i] = 0x00;
  }
  return data_websiteBuffer;
}

char* data_getClientsHTML(){
  int _size = sizeof(data_clientsHTML);
  for(int i=0;i<sizeof(data_websiteBuffer);i++){
    if(i<_size) data_websiteBuffer[i] = pgm_read_byte_near(data_clientsHTML + i);
    else data_websiteBuffer[i] = 0x00;
  }
  return data_websiteBuffer;
}

char* data_getAttackHTML(){
  int _size = sizeof(data_attackHTML);
  for(int i=0;i<sizeof(data_websiteBuffer);i++){
    if(i<_size) data_websiteBuffer[i] = pgm_read_byte_near(data_attackHTML + i);
    else data_websiteBuffer[i] = 0x00;
  }
  return data_websiteBuffer;
}

char* data_getSettingsHTML(){
  int _size = sizeof(data_settingsHTML);
  for(int i=0;i<sizeof(data_websiteBuffer);i++){
    if(i<_size) data_websiteBuffer[i] = pgm_read_byte_near(data_settingsHTML + i);
    else data_websiteBuffer[i] = 0x00;
  }
  return data_websiteBuffer;
}

//source: https://forum.arduino.cc/index.php?topic=38107.0
void PrintHex8(uint8_t *data, uint8_t length){
  Serial.print("0x");
  for (int i=0; i<length; i++) {
    if (data[i]<0x10) {Serial.print("0");}
    Serial.print(data[i],HEX);
    Serial.print(" ");
  }
}

//source: http://shelvin.de/eine-integer-zahl-in-das-arduiono-eeprom-schreiben/
void eepromWriteInt(int adr, int val) {
  byte low, high;
  low = val & 0xFF;
  high = (val >> 8) & 0xFF;
  EEPROM.write(adr, low);
  EEPROM.write(adr+1, high);
  return;
}

int eepromReadInt(int adr) {
  byte low, high;
  low = EEPROM.read(adr);
  high = EEPROM.read(adr+1);
  return low + ((high << 8) & 0xFF00);
}

void getRandomVendorMac(uint8_t *buf){
  int _macRandom = random(sizeof(data_vendors)/11);
  for(int h=0;h<3;h++) buf[h] = pgm_read_byte_near(data_vendors + _macRandom*11 + h);
  for(int h=0;h<3;h++) buf[h+3] = random(255);
}

bool intInArray(int num, int _array[]){
  for(int i=0;i<sizeof(_array);i++){
    if(_array[i] == num) return true;
  }
  return false;
}

#endif
