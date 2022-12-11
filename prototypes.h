#ifndef proto
#define proto
 
//Structure pour permettant de bien gerer le temps creation d'une variable personalisee
struct dateTime_t{

   byte sec;
   byte mins;
   byte hours;
   byte dow;   //dayOfWeek(1-7)
   byte dom;  //dayOfMonth(1-30/31)
   byte month;
   byte year;
   
}dateTime;

//QUELQUES VARIABLES GLOBALES DU PROGRAMME 
//variable pour la temperature et l'humidity
float tempe, humidy;
bool etat_buz= 0;

//FONCTIONS POUR LA LECTURE DU CAPTEUR DHT22
byte readDHT(byte pin, float* temperature, float* humidity);

 //FONCTIONS POUR LE CONTROL DE tempe,humid,leds, etc...
void control_temperature();
void control_humidity();
void control_leds_T();
void control_leds_D();
void control_buzzer();
void lcd_clear(bool); // verifie si l'ecran doit etre mis a jour

//pour l'affichage
void affichage();
void appel_fonction();
void retournement();
void result_bt(char, bool);

void lecture_bt2();
void lecture_bt18();
void lecture_bt19();

    //Fonctions pour le module RTC et le retournement
bool Clock(int);//controle de l'horloge du module 

// fonction pour le decodage du jour de la semaine et celui du moi 
String decode_dow(byte);
String decode_month(byte);


//fonction de mise ajour du temp
void update_time(byte, byte, byte, byte, byte, byte, byte);
void update_time_reglage(byte, byte); 
void download_time(dateTime_t *); 

//convertisseur des donnees
byte decimal_hexa(byte);
byte hexa_decimal(byte);

// fonction pour le decodage du jour de la semaine et celui du moi 
String decode_dow(byte);
String decode_month(byte);

// fonction d'initialisation de l'incubateur
void initialisation();
#endif //prototype
