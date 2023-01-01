#ifndef rtc
#define rtc
#include "lcd.h"

   //Constantes pour le module RTC 
#define ADRESS_RTC 0x68 // qui vaut 104 en decimal
#define ADRESS_EEPROM 8

void download_time(dateTime_t *now){  //now est une variable de type structure qui stoquerant l'heure et la date actuel
  Wire.beginTransmission(ADRESS_RTC);
  Wire.write(0);         //on remet a zero le curseur
  Wire.endTransmission();

  Wire.requestFrom(ADRESS_RTC, 9);
  now->sec   = decimal_hexa(Wire.read());
  now->mins  = decimal_hexa(Wire.read());
  now->hours = decimal_hexa(Wire.read() & 63);
  now->dow   = decimal_hexa(Wire.read());
  now->dom   = decimal_hexa(Wire.read());
  now->month = decimal_hexa(Wire.read());
  now->year  = decimal_hexa(Wire.read());
  Wire.read(); //lecture du  8ieme octet
  now->incremente_hours = decimal_hexa(Wire.read());

  Clock( now->sec & 128); //verification de l'horloge
}

void update_time(byte secondes, byte minutes, byte heures, byte dows, byte doms, byte moi, byte an){ //mise a jours de l'heure et de la date

  Wire.beginTransmission(ADRESS_RTC);
  Wire.write(0);                      // remise a zero du curseur
  Wire.write( hexa_decimal(secondes) & 127); // CH=0
  Wire.write( hexa_decimal(minutes));
  Wire.write( hexa_decimal(heures) & 63);    //mode 24
  Wire.write( hexa_decimal(dows));
  Wire.write( hexa_decimal(doms));
  Wire.write( hexa_decimal(moi));
  Wire.write( hexa_decimal(an));
  Wire.endTransmission();
  
}

void update_time_reglage(byte sec_R, byte min_R){
  Wire.beginTransmission(ADRESS_RTC);
  Wire.write(0);                      // remise a zero du curseur
  Wire.write( hexa_decimal(sec_R) & 127); // CH=0
  Wire.write( hexa_decimal(min_R));
  Wire.endTransmission();
}


void update_deadline_Hours(int data){
  
  Wire.beginTransmission(ADRESS_RTC);
  Wire.write(ADRESS_EEPROM);                      // pointage vers l'octet
  Wire.write(hexa_decimal(data));
  Wire.endTransmission();  
}


String decode_dow(byte day){
  String data;
  switch(day){
    
    case 1:
    data = "lun";
    break;

    case 2:
    data = "mar";
    break;

    case 3:
    data = "mer";
    break;

    case 4:
    data = "jeu";
    break;

    case 5:
    data = "ven";
    break;

    case 6:
    data = "sam";
    break;

    case 7:
    data = "dim";
    break;
  }
  return data;
}

String decode_month(byte moi){
  String data;

  switch(moi){

    case 1:
    data = "Jan";
    break;

    case 2:
    data = "Fev";
    break;

    case 3:
    data = "Mar";
    break;

    case 4:
    data = "Avr";
    break;

    case 5:
    data = "Mai";
    break;

    case 6:
    data = "Juin";
    break;

    case 7:
    data = "July";
    break;

    case 8:
    data = "Aout";
    break;

    case 9:
    data = "Sept";
    break;

    case 10:
    data = "Oct";
    break;

    case 11:
    data = "Nov";
    break;

    case 12:
    data = "Dec";
    break;
    
  }

  return data;
}

byte decimal_hexa(byte decimal){ // fonction convertissant 
                                  // un nombre decimal en hexa
      
  char dizaine = (decimal / 16) * 10;
  char unite = decimal % 16;

  return dizaine + unite;
}

byte hexa_decimal(byte hexa){
  char dizaine = (hexa / 10) * 16;
  char unite = hexa % 10;
  return dizaine + unite;
}


bool Clock(int data){
 
  if(data){
    Serial.println("l'horloge est en Arret");
    update_time_reglage(0, 0); 
    }

  else{
    //Serial.println("ok_");
  }
}
#endif //rtc
