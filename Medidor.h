// ------------------------------------------------------
// Autor: Ruiyu Chen 
// Descripción: Formamos el valor de co2 y de temperatura
// a lo real y lo usamos para publicar beacon.
// En esta version no es necesario los valores reales, por lo
// tanto todos los codigos de calculo y conversión estarán 
// comentados.
// ------------------------------------------------------

#ifndef MEDIDOR_H_INCLUIDO
#define MEDIDOR_H_INCLUIDO

class Medidor {

private:
  int pinGas = 5;
  int pinRef = 28;
  int pinTemperatura = 29;

public:
  float rawGas;
  float rawRef;
  float rawTemperatura;

  float vGas;
  float vRef;
  float vTemperatura;

  float vMedida;
  float concentracion;
  float incrementoTemperatura;
  float temperatura;


  // Constructor
  // ------------------------------------------------------
  Medidor(  ) {
    
  }   

  // ------------------------------------------------------
  void iniciarMedidor() {
    /*
    pinMode(pinGas,INPUT);
    pinMode(pinRef,INPUT);
    pinMode(pinTemperatura,INPUT);
    */
  } 

  // En esta version se devuelve un valor constante
  // ------------------------------------------------------
  int medirCO2() {

    /*
    rawGas =analogRead(pinGas);
    rawRef =analogRead(pinRef);
    rawTemperatura =analogRead(pinTemperatura);

    vGas = rawGas*3.3;
    vRef = rawRef*3.3;
    vTemperatura = rawTemperatura*3.3;

    vMedida= vGas - vRef;
    */

	  return 2000;
  } 

  // En esta version se devuelve un valor constante
  // ------------------------------------------------------
  int medirTemperatura() {
    /*
    temperatura=87*vTemperatura-18;
    return temperatura;
    */

	  return 1101; 
  } 
	
};
#endif
