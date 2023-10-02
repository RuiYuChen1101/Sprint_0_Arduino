// -*- mode: c++ -*-

#ifndef LED_H_INCLUIDO
#define LED_H_INCLUIDO

// ----------------------------------------------------------
// Autor: Ruiyu Chen 
// Descripción: Configurar el numero del puerto LED y contiene
// funciones para encender, apagar o hacer que parpadea
// ----------------------------------------------------------

  // ----------------------------------------------------------
  // Diseño: N ---> esperar()
  // Descripción: El tiempo de retardo en ms
  // ----------------------------------------------------------
  void esperar (long tiempo) {
    delay (tiempo);
  }

  // ----------------------------------------------------------
  // Diseño: N, Bool ---> LED
  // Descripción: Clase LED que recibe un numero como el pin
  // de salida y un booleano para controlarla
  // ----------------------------------------------------------
class LED {
  private:
    int numeroLED;
    bool encendido;
public:

  LED (int numero)
	: numeroLED (numero), encendido(false)

  {
	pinMode(numeroLED, OUTPUT);
	apagar ();
  }

  // .........................................................
  // Diseño: encender()
  // Descripción: Encender la luz, poner el numero de pin en HIGH
  // .........................................................
  void encender () {
	digitalWrite(numeroLED, HIGH); 
	encendido = true;
  }

  // .........................................................
  // Diseño: apagar()
  // Descripción: Apagar la luz, poner el numero de pin en LOW
  // .........................................................
  void apagar () {
	  digitalWrite(numeroLED, LOW);
	  encendido = false;
  }

  // .........................................................
  // Diseño: alternar()
  // Descripción: llamar la funcion encender() y apagar() 
  // alternativamente sin pararse
  // .........................................................
  void alternar () {
	if (encendido) {
	  apagar();
	} else {
	  encender ();
	}
  } // ()

  // .........................................................
  // Diseño: N ---> brillar()
  // Descripción: Encender la luz por un cierto tiempo y despues
  // apagarla
  // .........................................................
  void brillar (long tiempo) {
	encender ();
	esperar(tiempo); 
	apagar ();
  }
}; // class

// ----------------------------------------------------------
// ----------------------------------------------------------
// ----------------------------------------------------------
// ----------------------------------------------------------
#endif
