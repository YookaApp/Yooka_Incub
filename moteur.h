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

//ce fichier contient les fonction permettant le retournement des oeufs grace au moteur
boolean valider = false, etat_bts = true;
bool memorie_btG = false, memorie_btD = false;
char heure_actuelle;

void initial_retournement(){

  if (digitalRead(PIN_FIN_de_COURSE_G)){
    etat_bts = 1; //dans l'autre cas on change de sens
  }

  if (digitalRead(PIN_FIN_de_COURSE_D)) {
    etat_bts = 0; //dans l'autre cas on change de sens
  }
}


void control_hour() {
    if(dateTime.hours != heure_actuelle){

    }
}

void control_Fin_de_course() {
  bool data1 = digitalRead(PIN_FIN_de_COURSE_G);
  bool data2 = digitalRead(PIN_FIN_de_COURSE_D);

  if ( (data1 != memorie_btG) && (data1 == true) ) {
    valider = false ;  //arret moteurs
    etat_bts = 1; //dans l'autre cas on change de sens
  }

  if ((data2 != memorie_btD) && (data2 == true)) {
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
  }
  
  else if(digitalRead(PIN_RETOURNEMENT_AVANC) && !digitalRead(PIN_FIN_de_COURSE_D)){
    etat_bts = 0;
    valider = true;
  }

  else {
    valider = false; //on stop le moteur
  }

// initialisation du sens des boutons si on a atteint les contacts de fin de course

  initial_retournement();

}

void retournement() {
  
  lecture_buttons(); // action des boutons 
  control_hour(); //check time, if deadline 's reach we action the motor
  
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
