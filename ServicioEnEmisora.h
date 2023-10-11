// ----------------------------------------------------------
// Autor: Ruiyu Chen 
// Descripción: Aqui estan los servicios para configurar el 
// emisor BLT
// ----------------------------------------------------------

#ifndef SERVICIO_EMISORA_H_INCLUIDO
#define SERVICIO_EMISORA_H_INCLUIDO

// ----------------------------------------------------------
#include <vector>

// ----------------------------------------------------------
template< typename T >
T *  alReves( T * p, int n ) {
  T aux;

  for( int i=0; i < n/2; i++ ) {
	aux = p[i];
	p[i] = p[n-i-1];
	p[n-i-1] = aux;
  }
  return p;
} 

// ----------------------------------------------------------
uint8_t * stringAUint8AlReves( const char * pString, uint8_t * pUint, int tamMax ) {

	int longitudString =  strlen( pString );
	int longitudCopiar = ( longitudString > tamMax ? tamMax : longitudString );
	// copio nombreServicio -> uuidServicio pero al revés
	for( int i=0; i<=longitudCopiar-1; i++ ) {
	  pUint[ tamMax-i-1 ] = pString[ i ];
	} // for

	return pUint;
} 

// ----------------------------------------------------------
class ServicioEnEmisora {

public:

  // Cosntructor
  // ----------------------------------------------------------
  using CallbackCaracteristicaEscrita = void ( uint16_t conn_handle,
											   BLECharacteristic * chr,
											   uint8_t * data, uint16_t len); 

  // ----------------------------------------------------------
  class Caracteristica {
  private:
	uint8_t uuidCaracteristica[16] = { 
	  '0', '1', '2', '3', 
	  '4', '5', '6', '7', 
	  '8', '9', 'A', 'B', 
	  'C', 'D', 'E', 'F'
	};

  // ----------------------------------------------------------
	BLECharacteristic laCaracteristica;

  public:
	Caracteristica( const char * nombreCaracteristica_ )
	  :laCaracteristica( stringAUint8AlReves( nombreCaracteristica_, &uuidCaracteristica[0], 16 ) )
	{
	  
	} 

	// ----------------------------------------------------------
	Caracteristica( const char * nombreCaracteristica_ ,
					uint8_t props,
					SecureMode_t permisoRead,
					SecureMode_t permisoWrite, 
					uint8_t tam ) 
	  :
	  Caracteristica( nombreCaracteristica_ ) // llamada al otro constructor
	{
	  (*this).asignarPropiedadesPermisosYTamanyoDatos( props, permisoRead, permisoWrite, tam );
	} 

  // ----------------------------------------------------------
  private:
	void asignarPropiedades ( uint8_t props ) {
	  (*this).laCaracteristica.setProperties( props );
	}

	// ----------------------------------------------------------
	void asignarPermisos( SecureMode_t permisoRead, SecureMode_t permisoWrite ) {
	  (*this).laCaracteristica.setPermission( permisoRead, permisoWrite );
	} 

	// ----------------------------------------------------------
	void asignarTamanyoDatos( uint8_t tam ) {
	  (*this).laCaracteristica.setMaxLen( tam );
	} 
  public:
	// ----------------------------------------------------------
	void asignarPropiedadesPermisosYTamanyoDatos( uint8_t props,
												 SecureMode_t permisoRead,
												 SecureMode_t permisoWrite, 
												 uint8_t tam ) {
	  asignarPropiedades( props );
	  asignarPermisos( permisoRead, permisoWrite );
	  asignarTamanyoDatos( tam );
	} 
												 

	// ----------------------------------------------------------
	uint16_t escribirDatos( const char * str ) {
	 
	  uint16_t r = (*this).laCaracteristica.write( str );

	  return r;
	} 

  // ----------------------------------------------------------
	uint16_t notificarDatos( const char * str ) {
	  
	  uint16_t r = laCaracteristica.notify( &str[0] );

	  return r;
	} 

	// ----------------------------------------------------------
	void instalarCallbackCaracteristicaEscrita( CallbackCaracteristicaEscrita cb ) {
	  (*this).laCaracteristica.setWriteCallback( cb );
	} 

	// ----------------------------------------------------------
	void activar() {
	  err_t error = (*this).laCaracteristica.begin();
	  Globales::elPuerto.escribir(  " (*this).laCaracteristica.begin(); error = " );
	  Globales::elPuerto.escribir(  error );
	} 

  }; 
  
  // ----------------------------------------------------------
private:
  
  uint8_t uuidServicio[16] = { 
	'0', '1', '2', '3', 
	'4', '5', '6', '7', 
	'8', '9', 'A', 'B', 
	'C', 'D', 'E', 'F'
  };

  BLEService elServicio;

  std::vector< Caracteristica * > lasCaracteristicas;

public:
  
  // ----------------------------------------------------------
  ServicioEnEmisora( const char * nombreServicio_ )
	:
	elServicio( stringAUint8AlReves( nombreServicio_, &uuidServicio[0], 16 ) )
  {
	
  } 
  
  // ----------------------------------------------------------
  void escribeUUID() {
	Serial.println ( "**********" );
	for (int i=0; i<= 15; i++) {
	  Serial.print( (char) uuidServicio[i] );
	}
	Serial.println ( "\n**********" );
  } 

  // ----------------------------------------------------------
  void anyadirCaracteristica( Caracteristica & car ) {
	(*this).lasCaracteristicas.push_back( & car );
  } 

  // ----------------------------------------------------------
  void activarServicio( ) {

    err_t error = (*this).elServicio.begin();
    Serial.print( " (*this).elServicio.begin(); error = " );
    Serial.println( error );

    for( auto pCar : (*this).lasCaracteristicas ) {
      (*pCar).activar();
    } 
  } 

  // ----------------------------------------------------------
  operator BLEService&() {
	return elServicio;
  }
	
};
#endif

