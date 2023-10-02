// -*- mode: c++ -*-

// --------------------------------------------------------------
// Autor: Ruiyu Chen 
// Descripción: Configura los parametros para el envío de Beacon
// así como la carga del sí mismo
// --------------------------------------------------------------

#ifndef PUBLICADOR_H_INCLUIDO
#define PUBLICADOR_H_INCLUIDO

// --------------------------------------------------------------
// --------------------------------------------------------------
class Publicador {

private:

  uint8_t beaconUUID[16] = { 
	'E', 'P', 'S', 'G', '-', 'G', 'T', 'I', 
	'-', 'P', 'R', 'O', 'Y', '-', '3', 'A'
	};

  
public:
  EmisoraBLE laEmisora {
	"GTI-3A", //  nombre emisora
	  0x004c, // fabricanteID (Apple)
	  4 // txPower
	  };

  const int RSSI = -53; 

 
public:

  enum MedicionesID  {
	CO2 = 11,
	TEMPERATURA = 12,
	RUIDO = 13
  };

  Publicador( ) {
  } 

  // ............................................................
  // Diseño: encenderEmisora()
  // Descripción: Llama la función encenderEmisora() de la clase EmisoraBLE
  // ............................................................
  void encenderEmisora() {
	(*this).laEmisora.encenderEmisora();
  } 

  // ............................................................
  // Diseño: R,N,N ---> publicarCO2() 
  // Descripción: Recibe parametros que constituye la carga de ibeacon,
  // uuid y rssi son constantes, major es el numero combinado de la
  // constante CO2 con contador, y minor es el valor de CO2 del sensor
  // ............................................................
  void publicarCO2( int16_t valorCO2, uint8_t contador, long tiempoEspera ) {

	uint16_t major = (MedicionesID::CO2 << 8) + contador;
	(*this).laEmisora.emitirAnuncioIBeacon( (*this).beaconUUID, major, valorCO2, (*this).RSSI);

	/*
	Globales::elPuerto.escribir( "   publicarCO2(): valor=" );
	Globales::elPuerto.escribir( valorCO2 );
	Globales::elPuerto.escribir( "   contador=" );
	Globales::elPuerto.escribir( contador );
	Globales::elPuerto.escribir( "   todo="  );
	Globales::elPuerto.escribir( major );
	Globales::elPuerto.escribir( "\n" );
	*/

	esperar( tiempoEspera );

	(*this).laEmisora.detenerAnuncio();
  } // ()

  // ............................................................
  // Diseño: R,N,N ---> publicarTemperatura() 
  // Descripción: Recibe parametros que constituye la carga de ibeacon,
  // uuid y rssi son constantes, major es el numero combinado de la
  // constante TEMPERATURA con contador, y minor es el valor de temperatura del sensor
  // ............................................................
  void publicarTemperatura( int16_t valorTemperatura,	uint8_t contador, long tiempoEspera ) {

	uint16_t major = (MedicionesID::TEMPERATURA << 8) + contador;
	(*this).laEmisora.emitirAnuncioIBeacon( (*this).beaconUUID, major, valorTemperatura,	(*this).RSSI);

	esperar( tiempoEspera );

	(*this).laEmisora.detenerAnuncio();
  } // ()
	
}; // class

// --------------------------------------------------------------
// --------------------------------------------------------------
// --------------------------------------------------------------
// --------------------------------------------------------------
#endif
