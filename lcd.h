
// FICHIER POUR AFFICHAGE DES DONNEES.
#ifndef lcd
#define lcd
#include "prototypes.h"

char tableau[2];
LiquidCrystal_I2C lcd_tempe(0x27, 20, 4);

void affichage(){
  
  sprintf(tableau,"%cC ", char(0b11011111));
  lcd_tempe.print("");
  lcd_tempe.setCursor(4, 0);
  lcd_tempe.print("T");
  lcd_tempe.print(char(0b11011111));
  lcd_tempe.setCursor(15, 0);
  lcd_tempe.print("H");
    
  lcd_tempe.setCursor(2, 1);
  lcd_tempe.print(tempe, 1);
  lcd_tempe.print(tableau);
  
  lcd_tempe.setCursor(13, 1);
  lcd_tempe.print(humidy, 1);
  lcd_tempe.print('%');

//affichage du temps et de la date   
  
  lcd_tempe.setCursor(5, 2);
  if (dateTime.hours < 10)
  lcd_tempe.print("0");
  
  lcd_tempe.print(dateTime.hours);
  lcd_tempe.print(":");
 
  if (dateTime.mins < 10){
  lcd_tempe.print("0");
  }
  lcd_tempe.print(dateTime.mins);  
  lcd_tempe.print("'");
  lcd_tempe.print(":");

  if (dateTime.sec < 10){
  lcd_tempe.print("0");
  }
  lcd_tempe.print(dateTime.sec);
  lcd_tempe.print('"');
    
  lcd_tempe.setCursor(2, 3);
  lcd_tempe.print(decode_dow(dateTime.dow));
  lcd_tempe.print(" ");
  if (dateTime.dom < 10)
  lcd_tempe.print("0");
  
  lcd_tempe.print(dateTime.dom);
  lcd_tempe.print(" ");
  lcd_tempe.print(decode_month(dateTime.month));
  lcd_tempe.print(" ");
  lcd_tempe.print(dateTime.year + 2000);
}


void initialisation()
{
  int j,i;
  
 for(i =0; i<2; i++){
  lcd_tempe.clear();
  lcd_tempe.setCursor(3, 2);
  lcd_tempe.print("chargement");
      
      delay(250);    
      for(j=0; j<=2; j++){
        lcd_tempe.print(".");
        delay(250);    
      }
    }   
        lcd_tempe.clear();
}


#endif //lcd
