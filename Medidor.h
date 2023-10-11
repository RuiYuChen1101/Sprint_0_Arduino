// ------------------------------------------------------
// Autor: Ruiyu Chen 
// Descripción: Este fichero es para formar el valor de co2
// y de temperatura a lo real y lo usa para publicar beacon
// ------------------------------------------------------

#ifndef MEDIDOR_H_INCLUIDO
#define MEDIDOR_H_INCLUIDO

class Medidor {

private:

public:

  // Constructor
  // ------------------------------------------------------
  Medidor(  ) {
  } 

  // ------------------------------------------------------
  void iniciarMedidor() {
	
  } 

  // En esta version se devuelve un valor constante
  // ------------------------------------------------------
  int medirCO2() {
	return 2000;
  } 

  // En esta version se devuelve un valor constante
  // ------------------------------------------------------
  int medirTemperatura() {
	return 1101; 
  } 
	
};
#endif
