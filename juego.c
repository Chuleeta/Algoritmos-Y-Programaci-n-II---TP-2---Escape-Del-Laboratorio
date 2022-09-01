#include <stdio.h>
#include "detector_personajes.h"
#include "escape_laboratorio.h"
#include "utiles.h"
#include <stdlib.h> 
#include <time.h>

#define NORMAL "\e[0m"
#define AZUL "\e[44m"

#define DIMENSION_GRANDE 17
#define DIMENSION_CHICA 12

#define JUGANDO 0
#define PERDIO -1
#define GANO 1

#define MOVIMIENTOS_NUEVOS 10

#define ESPACIO_VACIO ' '

#define GUARDIA 'G'

#define PRIMER_NIVEL 1
#define SEGUNDO_NIVEL 2
#define TERCER_NIVEL 3
#define CUARTO_NIVEL 4


/*Pre condiciones: Recibe nivel (0 a 3), la posicion del obstaculo en su array (de 0 hasta el tope_obstaculos).
*Post condiciones: Devuelve si existe una herramienta u otro obstaculo en la misma coordenada que el obstaculo dado.
*/
bool hay_obstaculo_herramienta(nivel_t* nivel, int posicion_obstaculo){
	for (int i = 0; i < (*nivel).tope_herramientas; i++){
		if((((*nivel).obstaculos[posicion_obstaculo].posicion.fil == (*nivel).herramientas[i].posicion.fil)) &&
		(((*nivel).obstaculos[posicion_obstaculo].posicion.col) == ((*nivel).herramientas[i].posicion.col))){
			return true;
		}
	}

	for (int i = 0; i < (*nivel).tope_obstaculos; i++){
		if((((*nivel).obstaculos[posicion_obstaculo].posicion.fil == (*nivel).obstaculos[i].posicion.fil)) &&
		(((*nivel).obstaculos[posicion_obstaculo].posicion.col) == ((*nivel).obstaculos[i].posicion.col)) 
		&& (posicion_obstaculo != i)){
			return true;
		}
	}
return false;
}


/*Pre condiciones: Recibe nivel (0 a 3), la posicion del obstaculo en su array (de 0 hasta el tope_obstaculos).
*Post condiciones: Devuelve si existe una pared en la misma coordenada que el obstaculo.
*/
bool hay_pared(nivel_t* nivel, int posicion_obstaculo){
	for(int i = 0; i < (*nivel).tope_paredes; i++){
		if( (((*nivel).obstaculos[posicion_obstaculo].posicion.fil == (*nivel).paredes[i].fil)) &&
		(((*nivel).obstaculos[posicion_obstaculo].posicion.col) == ((*nivel).paredes[i].col)) ){
			return true;
		}
	}
return false;
}


/*Pre condiciones: Recibe juego, la dimension del nivel actual (17 o 12).
*Post condiciones: Mueve a los guardias a una nueva posicion mientras que no haya algo alli.
*/
void mover_guardias(juego_t* juego, int dimension){
	for (int i = 0; i < (*juego).niveles[(*juego).nivel_actual - 1].tope_obstaculos ; i++){
		if((*juego).niveles[(*juego).nivel_actual - 1].obstaculos[i].tipo == GUARDIA){
			(*juego).niveles[(*juego).nivel_actual - 1].obstaculos[i].posicion.fil = rand () % (dimension - 2) + 1;
			(*juego).niveles[(*juego).nivel_actual - 1].obstaculos[i].posicion.col = rand () % (dimension - 2) + 1;
			while((hay_pared( &((*juego).niveles[(*juego).nivel_actual - 1]), i) == true) || 
				(hay_obstaculo_herramienta( &((*juego).niveles[(*juego).nivel_actual - 1]), i) == true)){
				(*juego).niveles[(*juego).nivel_actual - 1].obstaculos[i].posicion.fil = rand () % (dimension - 2) + 1;
				(*juego).niveles[(*juego).nivel_actual - 1].obstaculos[i].posicion.col = rand () % (dimension - 2) + 1;
			}
		}
	}
}


/*Pre condiciones: Recibe juego.
*Post condiciones: Devuelve si es necesario presionar el interruptor o no.
*/
void definir_interruptor_llave(juego_t* juego){
	if ((*juego).nivel_actual == PRIMER_NIVEL){
		(*juego).personaje.presiono_interruptor = true;
		(*juego).personaje.tiene_llave = false;
	}else if ((*juego).nivel_actual == SEGUNDO_NIVEL){
		(*juego).personaje.presiono_interruptor = true;
		(*juego).personaje.tiene_llave = false;
	}else if ((*juego).nivel_actual == TERCER_NIVEL){
		(*juego).personaje.presiono_interruptor = false;
		(*juego).personaje.tiene_llave = false;
	}else{
		(*juego).personaje.presiono_interruptor = false;
		(*juego).personaje.tiene_llave = false;
	}
}


/*Pre condiciones: Recibe juego, sel nivel actual (1 a 4), estado_actual_nivel (0 o 1), estado_actual_juego (0, 1 o -1), 
si perdio la primera vida, y la dimension (17 o 12).
*Post condiciones: Corre el nivel, deja que el usuario juegue. En base a eso devuelvo los cambios al esta_actual_nivel y 
estado_actual_juego (diciendo si paso de nivel, gano o perdio)
*/
void jugar_nivel(juego_t* juego, int nivel, int* estado_actual_nivel, int* estado_actual_juego, int dimension_para_guardias){

	(*estado_actual_nivel) = JUGANDO;
	(*estado_actual_juego) = JUGANDO;

	(*juego).nivel_actual = nivel;
	(*juego).personaje.movimientos += MOVIMIENTOS_NUEVOS;
	

	(*juego).personaje.posicion.fil = (*juego).niveles[(*juego).nivel_actual - 1].entrada.fil;
	(*juego).personaje.posicion.col = (*juego).niveles[(*juego).nivel_actual - 1].entrada.col;
	
	definir_interruptor_llave(juego);
	mostrar_juego((*juego));
	
	char movimiento;
	(*estado_actual_nivel) = estado_nivel(juego->personaje, juego->niveles[juego->nivel_actual - 1].salida);
	(*estado_actual_juego) = estado_juego(*juego);
	
	while(((*estado_actual_nivel) != GANO) && ((*estado_actual_juego) != PERDIO)){
		system("clear");
		mostrar_juego((*juego));
		//printf("\t");
		printf(AZUL);
		printf("Ingrese el siguente movimiento (w,a,s,d):  ");
		printf(NORMAL);
		scanf(" %c", &movimiento);
		mover_personaje(&(*juego), movimiento);
		system("clear");
		mover_guardias(juego, dimension_para_guardias);
		printf(NORMAL);
		mostrar_juego((*juego));
		(*estado_actual_nivel) = estado_nivel((*juego).personaje, (*juego).niveles[(*juego).nivel_actual - 1].salida);
		(*estado_actual_juego) = estado_juego((*juego));
	}
}


int main(){
	srand (( unsigned)time(NULL));
	juego_t juego;
	juego.personaje.tipo = ESPACIO_VACIO;
	juego.personaje.murio = false;

	detectar_personaje(&juego.personaje.tipo);

	inicializar_juego(&juego, juego.personaje.tipo);

	int dimension_para_guardias;
	int nivel = PRIMER_NIVEL;

	int estado_actual_juego;
	int estado_actual_nivel;


	while(estado_actual_juego == JUGANDO){
		if((nivel % 2) == 0){
			dimension_para_guardias = DIMENSION_GRANDE;
		}else dimension_para_guardias = DIMENSION_CHICA;

		if(estado_actual_juego == JUGANDO){
			system("clear");
			jugar_nivel(&juego, nivel, &estado_actual_nivel, &estado_actual_juego, dimension_para_guardias);
		}

		if((estado_actual_nivel == GANO) && (estado_juego(juego) == GANO)){ 
			estado_actual_juego = GANO;
			//printf(NORMAL);
			printf("Ganaste!\n");
		}else if (estado_actual_juego == PERDIO){
			//printf(NORMAL);
			printf("Perdiste! :c\n");
		}
		else nivel++;
	}
	return 0;
}