#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//Pre = Pre condiciones
//Post = Post condiciones

#define JOHNNY 'J'
#define CORAJE 'C'
#define POLLITO 'P'
#define PURO 'H'
#define BELLOTA 'S'
#define BLUE 'B'

const char AZUL = 'A';
const char AMARILLO = 'Y';
const char VERDE = 'V';
const char NEGRO = 'N';
const char BLANCO = 'B';
const char ROSA = 'R';

const char DULCE = 'D';
const char AMARGO = 'A';
const char SALADO = 'S';

const int PUNTAJE_MINIMO = 5;
const int PUNTAJE_MEDIO = 15;
const int PUNTAJE_MAXIMO = 20;

const int TALLE_MIN_X2 = 33;
const int TALLE_MAX_X2 = 37;
const int TALLE_MIN_X3 = 38;
const int TALLE_MAX_X3 = 42;
const int TALLE_MIN_X4 = 43;
const int TALLE_MAX_X4 = 47;
const int TALLE_X1 = 0;

const int ALTURA_JOHNNY = 180;
const int ALTURA_BELLOTA = 120;
const int ALTURA_POLLITO = 50;
const int ALTURA_BLUE = 140;
const int ALTURA_PUROHUESO = 200;
const int ALTURA_CORAJE = 30;

const int PUNTAJE_MIN_JOHNNY_CORAJE = 1;
const int PUNTAJE_MAX_JOHNNY_CORAJE = 80;
const int PUNTAJE_MIN_PUROHUESO_POLLITO = 81;
const int PUNTAJE_MAX_PUROHUESO_POLLITO = 160;
const int PUNTAJE_MIN_BLUE_BELLOTA = 161;
const int PUNTAJE_MAX_BLUE_BELLOTA = 240;

const int ALTURA_MINIMA = 10;
const int ALTURA_MAXIMA = 250;

const int FECHA_MINIMA = 1988;
const int FECHA_MAXIMA = 2008;
/*
const char JOHNNY = 'J';
const char CORAJE = 'C';
const char POLLITO = 'P';
const char PURO = 'H';
const char BELLOTA = 'S';
const char BLUE = 'B';
*/
const char SI = 'S';
const char NO = 'N';

/*
Pre: -
Post: Verifica que fecha se encuentre entre FECHA_MINIMA y FECHA_MAXIMA (inclusive)
*/
bool es_fecha_valida(int fecha){
	if ((fecha >= FECHA_MINIMA) && (fecha <= FECHA_MAXIMA)){
		return true;
	}
	else{
		return false;
	}
}


/*
Pre: El entero fecha tiene que ser un numero entre FECHA_MINIMA y FECHA_MAXIMA (inclusive)
Post: Devuelve el puntaje de la fecha  
*/
int puntaje_segun_fecha(int fecha){
	if (es_fecha_valida(fecha) == true){
		return (fecha %20 +1);

	}else{
		int fecha_nueva;
		printf("No es un valor válido! Tiene que estar entre 1988 y 2008.\n");
		scanf(" %i", &fecha_nueva);

		return puntaje_segun_fecha(fecha_nueva);
	}
	return 0;
}


/*
Pre: -
Post: Verifica que el caracter gusto es igual a AMARGO, DULCE o SALADO
*/
bool es_sabor_valido(char gusto){
	if (gusto == AMARGO) {
		return true;
	}
	else if (gusto == SALADO){
		return true;
	}
	else if (gusto == DULCE){
		return true;
	}
	else{
		return false;
	}
}


/*
Pre: gusto tiene que ser un caracter igual a AMARGO, SALADO o DULCE
Post: PUNTAJE_MINIMO - si es igual a SALADO
	  PUNTAJE_MEDIO - si es igual a DULCE
	  PUNTAJE_MAXIMO - si es igual a AMARGO 
*/
int puntaje_segun_sabor(char gusto){
	if(es_sabor_valido(gusto) == true){
		if (gusto == AMARGO) {
			return PUNTAJE_MAXIMO;
		}
		else if (gusto == SALADO){
			return PUNTAJE_MINIMO;
		}
		else if (gusto == DULCE){
			return PUNTAJE_MEDIO;
		}
	}else{
		char sabor_nuevo;
		printf("No ingresaste 'S,D o A'! Acordate: (Dulce: 'D', Salado: 'S', Amargo: 'A')\n");
		scanf(" %c", &sabor_nuevo);

		return puntaje_segun_sabor(sabor_nuevo);
	}
	return 0;
}


/*
Pre: -
Post: Verifica que el talle_zapato este entre TALLE_MIN_X2 y TALLE_MAX_X4 (inclusive) o sea TALLE_X1
*/
bool es_talle_valido(int talle_zapato){
	if ((talle_zapato >= TALLE_MIN_X2 && talle_zapato <= TALLE_MAX_X4) || (talle_zapato == TALLE_X1)){
		return true;
	}else{
		return false;
	}
}


/*
Pre: talle_zapato tiene que ser un numero entre TALLE_MIN_X2 y TALLE_MAX_X4 (inclusive) o TALLE_X1
Post: 1 - si es TALLE_X1
	  2 - si esta entre TALLE_MIN_X2 y TALLE_MAX_X2 (inclusive)
	  3 - si esta entre TALLE_MIN_X3 y TALLE_MAX_X3 (inclusive)
	  4 - si esta entre TALLE_MIN_X4 y TALLE_MAX_X4 (inclusive)
*/
int puntaje_segun_talle(int talle_zapato){
	if (es_talle_valido(talle_zapato) == true){
		if (talle_zapato >= TALLE_MIN_X2 && talle_zapato <= TALLE_MAX_X2){
			return 2;
		}
			else if (talle_zapato >= TALLE_MIN_X3 && talle_zapato <= TALLE_MAX_X3){
				return 3;
			}
			else if (talle_zapato >= TALLE_MIN_X4 && talle_zapato <= TALLE_MAX_X4){
				return 4;
			}
			else if (talle_zapato == TALLE_X1){
				return 1;
			}
	}
		else{
			int talle_nuevo;
			printf("El valor ingresado no es válido! Acordate: Tiene que ser un numero entre 33 y 47 inclusive, si no usa zapatos escribir 0\n");
			scanf(" %i", &talle_nuevo);

			return puntaje_segun_talle(talle_nuevo);
		}
	return 0;
}


/*
Pre: -
Post: Verifica que colores es igual a ROSA, AMARILLO, NEGRO, BLANCO, AZUL o VERDE
*/
bool es_color_valido(char colores){
	if (colores == ROSA || colores == AMARILLO || colores == NEGRO || colores == BLANCO || colores == AZUL || colores == VERDE){
		return true;
	}else{
		return false;
	}
}

/*
Pre: colores tiene que ser igual a ROSA, AMARILLO, NEGRO, BLANCO, AZUL o VERDE
Post: 5 - si es igual a ROSA o AMARILLO
	  15 - si es igual a NEGRO o BLANCO
	  20 - si es igual a AZUL o VERDE
*/
int puntaje_segun_color(char colores){
	if (es_color_valido(colores) == true){
		if (colores == ROSA || colores == AMARILLO){
		return PUNTAJE_MINIMO;
	}
		else if (colores == NEGRO || colores == BLANCO){
			return PUNTAJE_MEDIO;
		}
		else if (colores == AZUL || colores == VERDE){
			return PUNTAJE_MAXIMO;
		}
	}
	else{
			char color_nuevo;
			printf("No ingresaste un color válido! Acordate: Rosa: 'R', Amarillo: 'Y', Negro: 'N'; Blanco: 'B', Azul: 'A', Verde: 'V'\n");
			scanf(" %c", &color_nuevo);

			return puntaje_segun_color(color_nuevo);
		}
	return 0;
}


/*
Pre: alturas debe ser un numero entre ALTURA_MAXIMA y ALTURA_MINIMA
Post: es igual a CORAJE si diferencia1 > diferencia2
	  es igual a JOHNNY si no es la situación anterior
	  es igual a POLLITO si diferencia3 > diferencia4
	  es igual a PURO si no es la situación anterior
	  es igual a BELLOTA si diferencia5 > diferencia6
	  es igual a BLUE si no es la situación anterior
*/
char diferencia_altura(int alturas, int p_total){
	char personaje;
	if (p_total >= PUNTAJE_MIN_JOHNNY_CORAJE && p_total <= PUNTAJE_MAX_JOHNNY_CORAJE){
		int diferencia_johnny = abs(ALTURA_JOHNNY - alturas);
		int diferencia_coraje = abs(ALTURA_CORAJE - alturas);
		
		if (diferencia_johnny > diferencia_coraje){
			personaje = CORAJE;
		}else{
			personaje = JOHNNY;
		}
	}
		else if (p_total >= PUNTAJE_MIN_PUROHUESO_POLLITO && p_total <= PUNTAJE_MAX_PUROHUESO_POLLITO){
			int diferencia_purohueso = abs(ALTURA_PUROHUESO - alturas);
			int diferencia_pollito = abs(ALTURA_POLLITO - alturas);
		
			if (diferencia_purohueso > diferencia_pollito){
				personaje = POLLITO;
			}else{
				personaje = PURO;
			}
		}
		else if (p_total >= PUNTAJE_MIN_BLUE_BELLOTA && p_total <= PUNTAJE_MAX_BLUE_BELLOTA){
			int diferencia_blue = abs(ALTURA_BLUE - alturas);
			int diferencia_bellota = abs(ALTURA_BELLOTA - alturas);
		
			if (diferencia_blue > diferencia_bellota){
				personaje = BELLOTA;
			}else{
				personaje = BLUE;
			}
		}
	return personaje;
}


/*
Pre: -
Post: Verifica que altura es un numero entre ALTURA_MINIMA y ALTURA_MAXIMA
*/
bool es_altura_valida(int altura){
	if (altura >= ALTURA_MINIMA && altura <= ALTURA_MAXIMA){
		return true;
	}else{
	return false;	
	}
}


/*
Pre:
Post:
*/
void preguntar_empezar_juego(char *respuesta){

		printf("Desea empezar el juego? (S: si / N: no)\n");
		scanf(" %c", respuesta);
		if(*respuesta == SI){
			system("clear");
		}
		else{
			preguntar_empezar_juego(respuesta);
		}

	}


/*
Pre: Tienen que estar calculados los puntajes de fecha_nacimiento_dada, sabor_dado, talle_dado y color_dado
Post: si la altura es más cercana a ALTURA_JOHNNY: imprime Johnny Bravo y su puntaje
	  si la altura es más cercana a ALTURA_CORAJE: imprime Coraje y su puntaje
	  si la altura es más cercana a ALTURA_POLLITO: imprime Pollito y su puntaje
	  si la altura es más cercana a ALTURA_PUROHUESO: imprime Puro Hueso y su puntaje
	  si la altura es más cercana a ALTURA_BLUE: imprime Blue y su puntaje
	  si la altura es más cercana a ALTURA_BELLOTA: imprime Bellota y su puntaje
*/
void resultado(int comida, int color, int anio, int talle, char* personaje_detectado){
	int puntaje_total = (comida + color + anio) * talle;

	//char respuesta;

	int altura_dada;
	printf("Cuál es su altura en cm? (Tiene que ser un numero entre 10 y 250 inclusive)\n");
	scanf(" %i", &altura_dada);

	while (es_altura_valida(altura_dada) == false){
		printf("El valor ingresado no es válido! Acordate: Tiene que estar entre 10 y 250 cm inclusive\n");
		scanf(" %i", &altura_dada);
		es_altura_valida(altura_dada);

	}

	if (es_altura_valida(altura_dada) == true){

		char valor_diferencia = diferencia_altura(altura_dada, puntaje_total);

		if (valor_diferencia ==	JOHNNY ){
			printf("Luego de obterner %i puntos la súper máquina detectora arrojó el resultado: - Johnny Bravo -.\n", puntaje_total);
			*personaje_detectado = JOHNNY;
			//preguntar_empezar_juego(&respuesta);
		}
		else if (valor_diferencia == CORAJE){
			printf("Luego de obterner %i puntos la súper máquina detectora arrojó el resultado: - Coraje -.\n", puntaje_total);
			*personaje_detectado = CORAJE;
			//preguntar_empezar_juego(&respuesta);
		}
		else if (valor_diferencia == PURO){
			printf("Luego de obterner %i puntos la súper máquina detectora arrojó el resultado: - Puro Hueso -.\n", puntaje_total);
			*personaje_detectado = PURO;
			//preguntar_empezar_juego(&respuesta);
		}
		else if (valor_diferencia == POLLITO){
			printf("Luego de obterner %i puntos la súper máquina detectora arrojó el resultado: - Pollito -.\n", puntaje_total);
			*personaje_detectado = POLLITO;
			//preguntar_empezar_juego(&respuesta);
		}

		if (valor_diferencia == BLUE){
			printf("Luego de obterner %i puntos la súper máquina detectora arrojó el resultado: - Blue -.\n", puntaje_total);
			*personaje_detectado = BLUE;
			//preguntar_empezar_juego(&respuesta);
		}
		else if (valor_diferencia == BELLOTA){
			printf("Luego de obterner %i puntos la súper máquina detectora arrojó el resultado: - Bellota -.\n", puntaje_total);
			*personaje_detectado = BELLOTA;
			//preguntar_empezar_juego(&respuesta);
		}
	}
}


/*
Pre: -
Post: Devuelve el dato ingresado por el usuario
*/
void preguntar_fecha_nacimiento(int *fecha_dada){
	printf("Cuál es la fecha de nacimiento del personaje? (Usar un numero entre 1988 y 2008)\n");
	scanf(" %i", fecha_dada);
}


/*
Pre: -
Post: Devuelve el dato ingresado por el usuario
*/
void preguntar_sabor(char *sabor_dado){
	printf("Qué sabor prefiere? (Dulce: 'D', Salado: 'S', Amargo: 'A')\n");
	scanf(" %c", sabor_dado);
}


/*
Pre: -
Post: Devuelve el dato ingresado por el usuario
*/
void preguntar_talle(int *talle_dado){
	printf("Ingresar su talla de zapatos (Tiene que ser un numero entre 33 y 47 inclusive, si no usa zapatos escribir 0)\n");
	scanf(" %i", talle_dado);
}


/*
Pre: -
Post: Devuelve el dato ingresado por el usuario
*/
void preguntar_color(char *color_dado){
	printf("De qué color es el personaje? (Rosa: 'R', Amarillo: 'Y', Negro: 'N'; Blanco: 'B', Azul: 'A', Verde: 'V')\n");
	scanf(" %c", color_dado);
}


void detectar_personaje(char* personaje_detectado){

	int fecha_nacimiento_dada;
	char sabor_dado;
	int talle_dado;
	char color_dado;

	preguntar_fecha_nacimiento(&fecha_nacimiento_dada);
	int fecha_final = puntaje_segun_fecha(fecha_nacimiento_dada);

	preguntar_sabor(&sabor_dado);
	int sabor_final = puntaje_segun_sabor(sabor_dado);

	preguntar_talle(&talle_dado);
	int talle_final = puntaje_segun_talle(talle_dado);

	preguntar_color(&color_dado);
	int color_final = puntaje_segun_color(color_dado);
	

	resultado(sabor_final, color_final, fecha_final, talle_final, personaje_detectado);
}