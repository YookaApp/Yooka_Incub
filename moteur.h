  //Ce fichier contient les fonction permettant le retournement des oeufs grace au moteur
#ifndef moteur
#define moteur

#define PIN_MOTEUR_a 36
#define PIN_MOTEUR_d 38

#define PIN_FIN_de_COURSE_G 3  // fin de course au fond de l'incubateur
#define PIN_FIN_de_COURSE_D 19  //fin de course pres de la porte

// BOUTON DE DIRECTION DU MOTEUR

#define PIN_RETOURNEMENT_RECUL 2
#define PIN_RETOURNEMENT_AVANC 18
#define DEADLINE 4

//ce fichier contient les fonction permettant le retournement des oeufs grace au moteur
boolean valider = false, etat_bts = true, flag_manuelRetour = false;
int HourNow = 0; // variable content a Hour now
bool memorie_btG = true, memorie_btD = true; // booleans content a state of course-ends buttons
                                                // setup to true value
void initial_retournement(){

  if (digitalRead(PIN_FIN_de_COURSE_G)){
    etat_bts = 0; //dans l'autre cas on change de sens
  }

  if (digitalRead(PIN_FIN_de_COURSE_D)) {
    etat_bts = 1; //dans l'autre cas on change de sens
  }
}


void control_hour() {
  int deadlineNow = dateTime.incremente_hours;
   
   if(HourNow != dateTime.hours){
      HourNow = dateTime.hours;
      deadlineNow = deadlineNow + 1;

        if(deadlineNow >= DEADLINE){
                 deadlineNow = 0;
                 valider = true;
                 
                 }    
      update_deadline_Hours(deadlineNow); // save incremente hour
    Serial.print("Incremente OK ");
   }
}

void control_Fin_de_course() {
  bool data1 = digitalRead(PIN_FIN_de_COURSE_D);
  bool data2 = digitalRead(PIN_FIN_de_COURSE_G);

  if((data1 != memorie_btG) && (data1 == true) && !data2) {
    valider = false ;  //arret moteurs
    etat_bts = 1; //dans l'autre cas on change de sens
  }

  else if((data2 != memorie_btD) && (data2 == true) && !data1) {
    valider = false ;  //arret moteurs
    etat_bts = 0; //dans l'autre cas on change de sens
      }
  
  memorie_btG = data1;
  memorie_btD = data2; // Enregistrement d'etats
}


void lecture_buttons(){
  
  if(digitalRead(PIN_RETOURNEMENT_RECUL) && !digitalRead(PIN_FIN_de_COURSE_G)){
    etat_bts = 1; 
    valider = true;
    flag_manuelRetour = true;
  }
  
  else if(digitalRead(PIN_RETOURNEMENT_AVANC) && !digitalRead(PIN_FIN_de_COURSE_D)){
    etat_bts = 0;
    valider = true;
    flag_manuelRetour = true;
  }

  else {
    //on stop le moteur
    if(flag_manuelRetour){
          valider = false; 
          flag_manuelRetour = false;
    }
  }
}

void retournement() {
  control_hour();
  lecture_buttons();
  
  if(valider) {
    control_Fin_de_course(); // on verifie nos boutons de fin de course

    if (etat_bts) { // de Droite vers le Gauche
      digitalWrite(PIN_MOTEUR_a, HIGH);
      digitalWrite(PIN_MOTEUR_d, LOW);
    }

    if (!etat_bts) { // de Gauche vers la Droite
      digitalWrite(PIN_MOTEUR_a, LOW);
      digitalWrite(PIN_MOTEUR_d, HIGH);
    }
    
  }
 

  if(valider == false){
    digitalWrite(PIN_MOTEUR_a, LOW);
    digitalWrite(PIN_MOTEUR_d, LOW);
  }
 }
#endif //moteur
