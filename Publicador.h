// --------------------------------------------------------------
// Autor: Ruiyu Chen 
// Descripción: Configura los parametros del publicador para 
// la publicación del ibeacon
// --------------------------------------------------------------

#ifndef PUBLICADOR_H_INCLUIDO
#define PUBLICADOR_H_INCLUIDO

// Constructor
// --------------------------------------------------------------
class Publicador {

private:

  uint8_t beaconUUID[16] = { 
	'E', 'P', 'S', 'G', '-', 'G', 'T', 'I', 
	'-', 'P', 'R', 'O', 'Y', '-', '3', 'A'
	};

  
public:
  EmisoraBLE laEmisora {
	"GTI-3A_CHEN", 
	  0x004c, 
	  4 
	};

  const int RSSI = -53; 

// --------------------------------------------------------------
public:

  enum MedicionesID  {
	CO2 = 11,
	TEMPERATURA = 12,
	RUIDO = 13
  };

  Publicador( ) {
  } 

  // --------------------------------------------------------------
  // Diseño: encenderEmisora()
  // Descripción: Llama la función encenderEmisora() de la clase EmisoraBLE
  // --------------------------------------------------------------
  void encenderEmisora() {
	(*this).laEmisora.encenderEmisora();
  } 

  // --------------------------------------------------------------
  // Diseño: R,N,N ---> publicarCO2() 
  // Descripción: Recibe parametros para publicar el valor de co2
  // --------------------------------------------------------------
  void publicarCO2( int16_t valorCO2, uint8_t contador, long tiempoEspera ) {

	uint16_t major = (MedicionesID::CO2 << 8) + contador;

	(*this).laEmisora.emitirAnuncioIBeacon( (*this).beaconUUID, major, valorCO2, (*this).RSSI);

	esperar( tiempoEspera );

	(*this).laEmisora.detenerAnuncio();
  } 

  // --------------------------------------------------------------
  // Diseño: R,N,N ---> publicarTemperatura() 
  // Descripción: Recibe parametros para publicar el valor de temperatura
  // --------------------------------------------------------------
  void publicarTemperatura( int16_t valorTemperatura,	uint8_t contador, long tiempoEspera ) {

	uint16_t major = (MedicionesID::TEMPERATURA << 8) + contador;

	(*this).laEmisora.emitirAnuncioIBeacon( (*this).beaconUUID, major, valorTemperatura,	(*this).RSSI);

	esperar( tiempoEspera );

	(*this).laEmisora.detenerAnuncio();
  } 
	
}; 
#endif
