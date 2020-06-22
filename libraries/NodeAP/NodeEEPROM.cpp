#include "NodeAP.h"

void WriteEepromString(char addr,String data)
{
  int _size = data.length();
  int i;

  for(i=0;i<_size;i++) {
    EEPROM.write(addr+i,data[i]);
  }
  EEPROM.write(addr+_size,'\0');   //Add termination null character for String Data
  EEPROM.commit();
}

String ReadEepromString(char addr)
{
  int i;
  char data[100]; //Max 100 Bytes
  int len=0;
  unsigned char k;
  k=EEPROM.read(addr);
  while(k != '\0' && len<500) {
    k=EEPROM.read(addr+len);
    data[len]=k;
    len++;
  }
  data[len]='\0';
  return String(data);
}
