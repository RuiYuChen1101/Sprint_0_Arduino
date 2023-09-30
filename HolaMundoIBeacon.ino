// -*-c++-*-

// --------------------------------------------------------------
// Autor: Ruiyu Chen 
// Descripción: Este fichero inicialmente configura la placa y 
// la inicializa, recibe los valores de CO2 y temperatura desde
// varios sensores, y emite un beacon, tal como se puede enviar
// mensaje que quiera
// --------------------------------------------------------------

// https://learn.sparkfun.com/tutorials/nrf52840-development-with-arduino-and-circuitpython

// https://stackoverflow.com/questions/29246805/can-an-ibeacon-have-a-data-payload

// --------------------------------------------------------------
// --------------------------------------------------------------
#include <bluefruit.h>

#undef min //Indefinir el valor maximo y minimo  
#undef max 

// --------------------------------------------------------------
// --------------------------------------------------------------
#include "LED.h"
#include "PuertoSerie.h"

// --------------------------------------------------------------
// --------------------------------------------------------------
namespace Globales {
  
  LED elLED ( /* NUMERO DEL PIN LED = */ 7 );

  PuertoSerie elPuerto ( /* velocidad = */ 115200 ); // 115200 o 9600 o ...

};

// --------------------------------------------------------------
// --------------------------------------------------------------
#include "EmisoraBLE.h"
#include "Publicador.h"
#include "Medidor.h"


// --------------------------------------------------------------
// --------------------------------------------------------------
namespace Globales {

  Publicador elPublicador;

  Medidor elMedidor;

}; // namespace

// --------------------------------------------------------------
// --------------------------------------------------------------
void inicializarPlaquita () {

  // de momento nada

} // ()

// --------------------------------------------------------------
// setup()
// --------------------------------------------------------------
void setup() {

  Globales::elPuerto.esperarDisponible();

  // 
  // 
  // 
  inicializarPlaquita();

  // Suspend Loop() to save power
  // suspendLoop();

  // 
  // 
  // 
  Globales::elPublicador.encenderEmisora();

  // Globales::elPublicador.laEmisora.pruebaEmision();
  
  // 
  // 
  // 
  Globales::elMedidor.iniciarMedidor();

  // 
  // 
  // 
  esperar( 1000 );

  Globales::elPuerto.escribir( "---- setup(): fin ---- \n " );

} // setup ()

// --------------------------------------------------------------
// Encender y apagar la lucecita cada cierto tiempo
// --------------------------------------------------------------
inline void lucecitas() {
  using namespace Globales;

  elLED.brillar( 100 ); 
  esperar ( 400 ); 
  elLED.brillar( 100 ); 
  esperar ( 400 );  
  Globales::elLED.brillar( 100 ); 
  esperar ( 400 ); 
  Globales::elLED.brillar( 1000 ); 
  esperar ( 1000 ); 
} // ()

// --------------------------------------------------------------
// loop ()
// --------------------------------------------------------------
namespace Loop {
  uint8_t cont = 0;
};

// ..............................................................
// ..............................................................
void loop () {

  using namespace Loop;
  using namespace Globales;

  cont++;

  elPuerto.escribir( "\n---- loop(): empieza " );
  elPuerto.escribir( cont );
  elPuerto.escribir( "\n" );


  lucecitas();

  // 
  // mido y publico
  // 
  int valorCO2 = elMedidor.medirCO2();
  
  elPublicador.publicarCO2( valorCO2,
							cont,
							1000 // intervalo de emisión
							);
  
  // 
  // mido y publico
  // 
  int valorTemperatura = elMedidor.medirTemperatura();
  
  elPublicador.publicarTemperatura( valorTemperatura, 
									cont,
									1000 // intervalo de emisión
									);

  // 
  // prueba para emitir un iBeacon y poner
  // en la carga (21 bytes = uuid 16 major 2 minor 2 txPower 1 )
  // lo que queramos (sin seguir dicho formato)
  // 
  // Al terminar la prueba hay que hacer Publicador::laEmisora privado
  // 
  char datos[21] = {
	'H', 'o', 'l', 'a',
	'H', 'o', 'l', 'a',
	'H', 'o', 'l', 'a',
	'H', 'o', 'l', 'a',
	'H', 'o', 'l', 'a',
	'H'
  };

  // elPublicador.laEmisora.emitirAnuncioIBeaconLibre ( &datos[0], 21 );
  elPublicador.laEmisora.emitirAnuncioIBeaconLibre ( "MolaMolaMolaMolaMolaM", 21 );

  esperar( 2000 );

  elPublicador.laEmisora.detenerAnuncio();
  
  // 
  // 
  // 
  elPuerto.escribir( "---- loop(): acaba **** " );
  elPuerto.escribir( cont );
  elPuerto.escribir( "\n" );
  
} // loop ()
// --------------------------------------------------------------
// --------------------------------------------------------------
// --------------------------------------------------------------
// --------------------------------------------------------------
