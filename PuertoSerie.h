
// -*- mode: c++ -*-

// ----------------------------------------------------------
// Autor: Ruiyu Chen 
// Descripción: Configurar la velocida del puerto serie y la 
// inicializa
// ----------------------------------------------------------

#ifndef PUERTO_SERIE_H_INCLUIDO
#define PUERTO_SERIE_H_INCLUIDO

// ----------------------------------------------------------
// ----------------------------------------------------------
class PuertoSerie  {

public:
  // .........................................................
  // Diseño: N ---> PuertoSerie
  // Descripción: Inicializar el puerto serie con tal velocidad
  // .........................................................
  PuertoSerie (long baudios) {
	Serial.begin( baudios );
	// mejor no poner esto aquí: while ( !Serial ) delay(10);   
  } // ()

  // .........................................................
  // Diseño: esperarDisponible()
  // Descripción: Cuando el puerto serie no esta disponible, 
  // pausa la ejecución del programa para 10 ms
  // .........................................................
  void esperarDisponible() {

	while ( !Serial ) {
	  delay(10);   
	}

  } // ()

  // .........................................................
  // Diseño: String ---> escribir()
  // Descripción: Recibe todo el tipo de mensaje y los imprime 
  // en el puerto serie
  // .........................................................
  template<typename T>
  void escribir (T mensaje) {
	Serial.print( mensaje );
  } // ()
  
}; // class PuertoSerie

// ----------------------------------------------------------
// ----------------------------------------------------------
// ----------------------------------------------------------
// ----------------------------------------------------------
#endif
