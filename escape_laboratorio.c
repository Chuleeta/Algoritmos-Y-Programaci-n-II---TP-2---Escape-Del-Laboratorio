#include <stdio.h>
#include "escape_laboratorio.h"
#include "utiles.h"
#include <stdbool.h>

#define FROJO "\e[41m"
#define MORADO "\e[45m"
#define NORMAL "\e[0m"


#define DIMENSION_GRANDE 17
#define DIMENSION_CHICA 12
#define MAX_OBJETO 25

#define JUGANDO 0
#define PERDIO -1
#define GANO 1

#define MOVIMIENTOS_NUEVOS 10

#define ENTRADA 'E'
#define SALIDA 'S'

#define MOVER_ARRIBA 'w'
#define MOVER_ABAJO 's'
#define MOVER_DERECHA 'd'
#define MOVER_IZQUIERDA 'a'

#define ESPACIO_VACIO ' '
#define PARED '.'
#define JUGADOR '&'

#define LLAVE 'L'
#define MONEDA 'M'
#define TELETRANSPORTADOR 'T'
#define INTERRUPTOR 'I'

#define BOMBA 'B'
#define GUARDIA 'G'
#define PINCHE 'P'

#define PINCHES_PRIMER_NIVEL 4
#define PINCHES_SEGUNDO_NIVEL 6
#define PINCHES_TERCER_NIVEL 6
#define PINCHES_CUARTO_NIVEL 10

#define GUARDIAS_PRIMER_NIVEL 2
#define GUARDIAS_SEGUNDO_NIVEL 3
#define GUARDIAS_TERCER_NIVEL 3
#define GUARDIAS_CUARTO_NIVEL 4

#define PRIMER_NIVEL 1
#define SEGUNDO_NIVEL 2
#define TERCER_NIVEL 3
#define CUARTO_NIVEL 4

#define JOHNNY 'J'
#define CORAJE 'C'
#define POLLITO 'P'
#define PURO 'H'
#define BELLOTA 'S'
#define BLUE 'B'

/*Pre condiciones:  Recibe juego, la posicion de la herramienta en su array (de 0 hasta el tope_herramientas).
*Post condiciones:  Elimina la herramienta del array herramientas.
*/
void eliminar_herramienta(juego_t* juego, int posicion_herramienta){
	if (posicion_herramienta != ((*juego).niveles[(*juego).nivel_actual - 1].tope_herramientas)){
		for (int i = posicion_herramienta; i < ((*juego).niveles[(*juego).nivel_actual - 1].tope_herramientas); i++){
			(*juego).niveles[(*juego).nivel_actual - 1].herramientas[i].tipo = (*juego).niveles[(*juego).nivel_actual - 1].herramientas[i + 1].tipo;
			(*juego).niveles[(*juego).nivel_actual - 1].herramientas[i].posicion.fil = (*juego).niveles[(*juego).nivel_actual - 1].herramientas[i + 1].posicion.fil;
			(*juego).niveles[(*juego).nivel_actual - 1].herramientas[i].posicion.col = (*juego).niveles[(*juego).nivel_actual - 1].herramientas[i + 1].posicion.col;
		}
		(*juego).niveles[(*juego).nivel_actual - 1].tope_herramientas--;
	}else{
		(*juego).niveles[(*juego).nivel_actual - 1].tope_herramientas--;
	}
}


/*Pre condiciones: Recibe juego, la posicion del obstaculo en su array (de 0 hasta el tope_obstaculos).
*Post condiciones: Elimina el obstaculo del array obstaculos.
*/
void eliminar_obstaculo(juego_t* juego, int posicion_obstaculo){
	if (posicion_obstaculo != ((*juego).niveles[(*juego).nivel_actual - 1].tope_obstaculos)){
		for (int i = posicion_obstaculo; i < ((*juego).niveles[(*juego).nivel_actual - 1].tope_obstaculos); i++){
			(*juego).niveles[(*juego).nivel_actual - 1].obstaculos[i].tipo = (*juego).niveles[(*juego).nivel_actual - 1].obstaculos[i + 1].tipo;
			(*juego).niveles[(*juego).nivel_actual - 1].obstaculos[i].posicion.fil = (*juego).niveles[(*juego).nivel_actual - 1].obstaculos[i + 1].posicion.fil;
			(*juego).niveles[(*juego).nivel_actual - 1].obstaculos[i].posicion.col = (*juego).niveles[(*juego).nivel_actual - 1].obstaculos[i + 1].posicion.col;
		}
		(*juego).niveles[(*juego).nivel_actual - 1].tope_obstaculos--;
	}else{
		(*juego).niveles[(*juego).nivel_actual - 1].tope_obstaculos--;
	}
}


/*Pre condiciones: Recibe nivel (0 a 3) y la posicion del obstaculo en su array.
*Post condiciones: Verifica si hay una pared en la misma coordenada que el obstaculo.
*/
bool hay_pared_obstaculo(nivel_t* nivel, int posicion_obstaculo){
	for(int i = 0; i < (*nivel).tope_paredes; i++){
		if( (((*nivel).obstaculos[posicion_obstaculo].posicion.fil == (*nivel).paredes[i].fil)) &&
		(((*nivel).obstaculos[posicion_obstaculo].posicion.col) == ((*nivel).paredes[i].col)) ){
			return true;
		}
	}
return false;
}


/*Pre condiciones:Recibe nivel (0 a 3) y la posicion de la herramienta en el array herramientas.
*Post condiciones:Verifica si hay otra herramienta, pared o obstaculo en la misma coordenada que la herramienta dada.
*/
bool se_puede_colocar_herramienta(nivel_t* nivel, int posicion_herramienta){
	for(int i = 0; i < (*nivel).tope_paredes; i++){
		if( (((*nivel).herramientas[posicion_herramienta].posicion.fil == (*nivel).paredes[i].fil)) &&
		(((*nivel).herramientas[posicion_herramienta].posicion.col) == ((*nivel).paredes[i].col)) ){
			return false;
		}
	}

	for (int i = 0; i < (*nivel).tope_herramientas; i++){
		if((((*nivel).herramientas[posicion_herramienta].posicion.fil == (*nivel).obstaculos[i].posicion.fil)) &&
		(((*nivel).herramientas[posicion_herramienta].posicion.col) == ((*nivel).obstaculos[i].posicion.col))){
			return false;
		}
	}

	for (int i = 0; i < (*nivel).tope_herramientas; i++){
		if((((*nivel).herramientas[posicion_herramienta].posicion.fil == (*nivel).herramientas[i].posicion.fil)) &&
		(((*nivel).herramientas[posicion_herramienta].posicion.col) == ((*nivel).herramientas[i].posicion.col)) 
		&& (posicion_herramienta != i)){
			return false;
		}
	}
return true;
}


/*Pre condiciones:Recibe nivel (0 a 3) y la posicion del obstaculo en el array obstaculos.
*Post condiciones: Verifica si hay otro obstaculo o herramienta en la misma coordenada que el obstaculo dado.
*/
bool se_puede_colocar_obstaculo(nivel_t* nivel, int posicion_obstaculo){
	for (int i = 0; i < (*nivel).tope_herramientas; i++){
		if((((*nivel).obstaculos[posicion_obstaculo].posicion.fil == (*nivel).herramientas[i].posicion.fil)) &&
		(((*nivel).obstaculos[posicion_obstaculo].posicion.col) == ((*nivel).herramientas[i].posicion.col))){
			return false;
		}
	}

	for (int i = 0; i < (*nivel).tope_obstaculos; i++){
		if((((*nivel).obstaculos[posicion_obstaculo].posicion.fil == (*nivel).obstaculos[i].posicion.fil)) &&
		(((*nivel).obstaculos[posicion_obstaculo].posicion.col) == ((*nivel).obstaculos[i].posicion.col)) 
		&& (posicion_obstaculo != i)){
			return false;
		}
	}
return true;
}


/*Pre condiciones: Recibe nivel (0 a 3) y la cantidad de obstaculos.
*Post condiciones: Verifica si es contigua con un pinche.
*/
bool es_contigua_con_pinche(nivel_t* nivel, int cantidad_obstaculos){
	for (int i = 1; i <= ((*nivel).tope_obstaculos - cantidad_obstaculos); i++){
		if ((((*nivel).obstaculos[((*nivel).tope_obstaculos) - cantidad_obstaculos].posicion.fil + 1) == (*nivel).obstaculos[((*nivel).tope_obstaculos) - cantidad_obstaculos - i].posicion.fil) &&
			((*nivel).obstaculos[((*nivel).tope_obstaculos) - cantidad_obstaculos].posicion.col) == (*nivel).obstaculos[((*nivel).tope_obstaculos) - cantidad_obstaculos - i].posicion.col){
			return true;
		}else if ((((*nivel).obstaculos[((*nivel).tope_obstaculos) - cantidad_obstaculos].posicion.fil - 1) == (*nivel).obstaculos[((*nivel).tope_obstaculos) - cantidad_obstaculos - i].posicion.fil) &&
			(((*nivel).obstaculos[((*nivel).tope_obstaculos) - cantidad_obstaculos].posicion.col) == (*nivel).obstaculos[((*nivel).tope_obstaculos) - cantidad_obstaculos - i].posicion.col)){
			return true;
		}else if ((((*nivel).obstaculos[((*nivel).tope_obstaculos) - cantidad_obstaculos].posicion.col - 1) == (*nivel).obstaculos[((*nivel).tope_obstaculos) - cantidad_obstaculos - i].posicion.col) &&
			(((*nivel).obstaculos[((*nivel).tope_obstaculos) - cantidad_obstaculos].posicion.fil ) == (*nivel).obstaculos[((*nivel).tope_obstaculos) - cantidad_obstaculos - i].posicion.fil)){
			return true;
		}else if ((((*nivel).obstaculos[((*nivel).tope_obstaculos) - cantidad_obstaculos].posicion.col + 1) == (*nivel).obstaculos[((*nivel).tope_obstaculos) - cantidad_obstaculos - i].posicion.col) &&
			(((*nivel).obstaculos[((*nivel).tope_obstaculos) - cantidad_obstaculos].posicion.fil ) == (*nivel).obstaculos[((*nivel).tope_obstaculos) - cantidad_obstaculos - i].posicion.fil)){
			return true;
		}
	}
return false;
}


/*Pre condiciones:Recibe nivel (0 a 3), la diension del nivel actual (17 o 12), la cantidad de obstaculos, el tope de paredes 
*y si es el primer pinche colocado.
*Post condiciones: Da una coordenada a el obstaculo dado. Si es un pinche verifica que tenga una posicion contigua con otro pinche.
*/
void ubicar_obstaculos(int dimension, char tipo, nivel_t* nivel, int cantidad_obstaculos, int tope_paredes, bool es_primer_pinche){
	(*nivel).obstaculos[((*nivel).tope_obstaculos) - cantidad_obstaculos].posicion.fil = rand () % (dimension - 2) + 1;
	(*nivel).obstaculos[((*nivel).tope_obstaculos) - cantidad_obstaculos].posicion.col = rand () % (dimension - 2) + 1;
	if ((*nivel).obstaculos[((*nivel).tope_obstaculos) - cantidad_obstaculos].tipo != PINCHE){
		while(hay_pared_obstaculo(nivel, ((*nivel).tope_obstaculos - cantidad_obstaculos)) == true){
			(*nivel).obstaculos[((*nivel).tope_obstaculos) - cantidad_obstaculos].posicion.fil = rand () % (dimension - 2) + 1;
			(*nivel).obstaculos[((*nivel).tope_obstaculos) - cantidad_obstaculos].posicion.col = rand () % (dimension - 2) + 1;	
		}
	}else if(es_primer_pinche == true){
		while(hay_pared_obstaculo(nivel, ((*nivel).tope_obstaculos - cantidad_obstaculos)) == true){
			(*nivel).obstaculos[((*nivel).tope_obstaculos) - cantidad_obstaculos].posicion.fil = rand () % (dimension - 2) + 1;
			(*nivel).obstaculos[((*nivel).tope_obstaculos) - cantidad_obstaculos].posicion.col = rand () % (dimension - 2) + 1;	
		}
	}else{
		while((hay_pared_obstaculo(nivel, ((*nivel).tope_obstaculos - cantidad_obstaculos)) == true) ||
				(es_contigua_con_pinche(nivel, cantidad_obstaculos) != true) || 
				(se_puede_colocar_obstaculo(nivel, ((*nivel).tope_obstaculos - cantidad_obstaculos)) == false)){
			(*nivel).obstaculos[((*nivel).tope_obstaculos) - cantidad_obstaculos].posicion.fil = rand () % (dimension - 2) + 1;
			(*nivel).obstaculos[((*nivel).tope_obstaculos) - cantidad_obstaculos].posicion.col = rand () % (dimension - 2) + 1;	
		}
	}
}


/*Pre condiciones: Recibe nivel (0 a 3), la cantidad de pinches, guardias, si hay bomba y la dimension (17 o 12).
*Post condiciones: Define la cantidad de obstaculos necesarias para ese nivel y les asigna una coordenada. 
*/
void definir_obstaculos(int cantidad_baldosas_pinches, int cantidad_guardia,bool hay_bomba, nivel_t* nivel, int dimension){
	(*nivel).tope_obstaculos = cantidad_baldosas_pinches;
	bool es_primer_pinche = true;
	while(cantidad_baldosas_pinches > 0){
		(*nivel).obstaculos[(*nivel).tope_obstaculos - cantidad_baldosas_pinches].tipo = PINCHE;
		ubicar_obstaculos(dimension, (*nivel).obstaculos[((*nivel).tope_obstaculos) - cantidad_baldosas_pinches].tipo,
		 &(*nivel), cantidad_baldosas_pinches, (*nivel).tope_paredes, es_primer_pinche);
		cantidad_baldosas_pinches--;
		es_primer_pinche = false;
	}

	(*nivel).tope_obstaculos += cantidad_guardia;

	while(cantidad_guardia > 0){
		(*nivel).obstaculos[((*nivel).tope_obstaculos) - cantidad_guardia].tipo = GUARDIA;
		ubicar_obstaculos(dimension, (*nivel).obstaculos[((*nivel).tope_obstaculos) - cantidad_guardia].tipo,
		 &(*nivel), cantidad_guardia, (*nivel).tope_paredes, es_primer_pinche);
		cantidad_guardia--;
	}

	if(hay_bomba == true){
		int cantidad_bombas = 1;
		(*nivel).tope_obstaculos += cantidad_bombas;
		(*nivel).obstaculos[((*nivel).tope_obstaculos) - cantidad_bombas].tipo = BOMBA;
		ubicar_obstaculos(dimension, (*nivel).obstaculos[((*nivel).tope_obstaculos) - 1].tipo,
		 &(*nivel), cantidad_bombas, (*nivel).tope_paredes, es_primer_pinche);
	}
}


/*Pre condiciones: Recibe nivel (0 a 3), la dimension del nivel (17 o 12), la cantidad de herramientas y el tope de paredes.
*Post condiciones: Devuelve una posicion random para la herramienta en la cual hay nada.
*/
void ubicar_herramientas(int dimension, char tipo, nivel_t* nivel, int cantidad_herramientas, int tope_paredes,
 int tope_herramientas){
	(*nivel).herramientas[((*nivel).tope_herramientas) - cantidad_herramientas].posicion.fil = rand () % (dimension - 2) + 1;
	(*nivel).herramientas[((*nivel).tope_herramientas) - cantidad_herramientas].posicion.col = rand () % (dimension - 2) + 1;

	while(se_puede_colocar_herramienta(nivel, ((*nivel).tope_herramientas - cantidad_herramientas)) == false){
		(*nivel).herramientas[((*nivel).tope_herramientas) - cantidad_herramientas].posicion.fil = rand () % (dimension - 2) + 1;
		(*nivel).herramientas[((*nivel).tope_herramientas) - cantidad_herramientas].posicion.col = rand () % (dimension - 2) + 1;	
	}
}


/*Pre condiciones: Recibe la cantidad de pinches, guardias, si hay bomba, el nivel actual (va de 1 a 4) y la dimension de este.
*Post condiciones: Define la cantidad de herramientas necesarias para ese nivel y les asigna una coordenada.
*/
void definir_herramientas(int cantidad_baldosas_pinches, int cantidad_guardia,bool hay_bomba, nivel_t* nivel, int dimension){
	
	int cantidad_monedas;
	int cantidad_tps;
	bool hay_interruptor;

	cantidad_monedas = (cantidad_baldosas_pinches / 2);
	cantidad_tps = cantidad_guardia;
	hay_interruptor = hay_bomba;

	(*nivel).tope_herramientas = cantidad_monedas;
	
	while(cantidad_monedas > 0){
		(*nivel).herramientas[(*nivel).tope_herramientas - cantidad_monedas].tipo = MONEDA;
		ubicar_herramientas(dimension, (*nivel).herramientas[((*nivel).tope_herramientas) - cantidad_monedas].tipo,
		 &(*nivel), cantidad_monedas, (*nivel).tope_paredes, (*nivel).tope_herramientas);
		cantidad_monedas--;
	}

	(*nivel).tope_herramientas += cantidad_tps;

	while(cantidad_tps > 0){
		(*nivel).herramientas[((*nivel).tope_herramientas) - cantidad_tps].tipo = TELETRANSPORTADOR;
		ubicar_herramientas(dimension, (*nivel).herramientas[((*nivel).tope_herramientas) - cantidad_tps].tipo,
		 &(*nivel), cantidad_tps, (*nivel).tope_paredes, (*nivel).tope_herramientas);
		cantidad_tps--;
	}

	if(hay_interruptor == true){
		int cantidad_interruptor = 1;
		(*nivel).tope_herramientas += cantidad_interruptor;
		(*nivel).herramientas[((*nivel).tope_herramientas) - cantidad_interruptor].tipo = INTERRUPTOR;
		ubicar_herramientas(dimension, (*nivel).herramientas[((*nivel).tope_herramientas) - 1].tipo,
		 &(*nivel), cantidad_interruptor, (*nivel).tope_paredes, (*nivel).tope_herramientas);
	}

	(*nivel).tope_herramientas = (*nivel).tope_herramientas + 1;
	(*nivel).herramientas[((*nivel).tope_herramientas) - 1].tipo = LLAVE;
	ubicar_herramientas(dimension, (*nivel).herramientas[(*nivel).tope_herramientas - 1].tipo, &(*nivel), 1,
	 (*nivel).tope_paredes, (*nivel).tope_herramientas);

}


/*Pre condiciones:Recibe nivel (0 a 3), la cantidad de pinches, guardias, si hay bomba y el numero de nivel actual .
*Post condiciones: Define la cantidad de pinches, guardias, si hay bomba segun el nivel.
*/
void rellenar_info_nivel(nivel_t* nivel, int* cantidad_baldosas_pinches, int* cantidad_guardia, bool* hay_bomba, int numero_nivel){

	if(numero_nivel == PRIMER_NIVEL){
		*cantidad_baldosas_pinches = PINCHES_PRIMER_NIVEL;
		*cantidad_guardia = GUARDIAS_PRIMER_NIVEL;
		*hay_bomba = false;
	}
	else if(numero_nivel == SEGUNDO_NIVEL){
		*cantidad_baldosas_pinches = PINCHES_SEGUNDO_NIVEL;
		*cantidad_guardia = GUARDIAS_SEGUNDO_NIVEL;
		*hay_bomba = false;
	}
	else if(numero_nivel == TERCER_NIVEL){
		*cantidad_baldosas_pinches = PINCHES_TERCER_NIVEL;
		*cantidad_guardia = GUARDIAS_TERCER_NIVEL;
		*hay_bomba = true;
	}
	else{
		*cantidad_baldosas_pinches = PINCHES_CUARTO_NIVEL;
		*cantidad_guardia = GUARDIAS_CUARTO_NIVEL;
		*hay_bomba = true;
	}
}


/*Pre condiciones: Recibe la dimension (17 o 12) y el numero de nivel.
*Post condiciones: Define el tamaño de la dimension necesario para ese nivel.
*/
void definir_dimension(int *dimension, int numero_nivel){
	*dimension = DIMENSION_CHICA;

	if((numero_nivel % 2) == 0){
		*dimension = DIMENSION_GRANDE;
	}
}


/*Pre condiciones: Recibe el mapa y su dimension (17 o 12).
*Post condiciones: Rellena de espacios el mapa.
*/
void rellenar_mapa(int dimension, char mapa[dimension][dimension]){
	for(int i = 0; i < dimension; i++){
		for(int j = 0; j < dimension; j++)
			mapa[i][j] = ESPACIO_VACIO;
	}
}


/*Pre condiciones: Recibe nivel (0 a 3).
*Post condiciones: Devuelve si hay algo en las coordenadas donde se quiere colocar la entrada.
*/
bool hay_algo_entrada_salida(nivel_t* nivel, coordenada_t* coordenada, char entrada_salida){
	
	for(int i = 0; i < (*nivel).tope_obstaculos; i++){
		if(((*coordenada).fil == (*nivel).obstaculos[i].posicion.fil) && 
			((*coordenada).col == (*nivel).obstaculos[i].posicion.col)){
			return true;
		}
	}
	for (int i = 0; i < (*nivel).tope_herramientas; ++i){
		if(((*coordenada).fil == (*nivel).herramientas[i].posicion.fil) && 
			((*coordenada).col == (*nivel).herramientas[i].posicion.col)){
			return true;
		}
	}
	for (int i = 0; i < (*nivel).tope_paredes; ++i){
		if(((*coordenada).fil == (*nivel).paredes[i].fil) && 
			((*coordenada).col == (*nivel).paredes[i].col)){
			return true;
		}
	}
	if(((*coordenada).fil == (*nivel).entrada.fil) && 
		((*coordenada).col == (*nivel).entrada.col) && (entrada_salida == SALIDA)){
		return true;
	}
return false;
}

/*Pre condiciones:Recibe nivel (0 a 3).
*Post condiciones:Devuelve donde hay que colocar la entrada y la salida.
*/
void definir_entrada_salida(int dimension, nivel_t* nivel){
	(*nivel).entrada.fil = rand () % (dimension - 2) + 1;
	(*nivel).entrada.col = rand () % (dimension - 2) + 1;

	while(hay_algo_entrada_salida(nivel, &(*nivel).entrada, ENTRADA) == true){
		(*nivel).entrada.fil = rand () % (dimension - 2) + 1;
		(*nivel).entrada.col = rand () % (dimension - 2) + 1;
	}

	(*nivel).salida.fil = rand () % (dimension - 2) + 1;
	(*nivel).salida.col = rand () % (dimension - 2) + 1;

	while(hay_algo_entrada_salida(nivel, &(*nivel).salida, SALIDA) == true){
		(*nivel).salida.fil = rand () % (dimension - 2) + 1;
		(*nivel).salida.col = rand () % (dimension - 2) + 1;
	}
}


/*Pre condiciones: Recibe el un array, su tope y el mapa.
*Post condiciones: Coloca los elementos del array dado en el mapa.
*/
void colocar_elemento_en_mapa(elemento_t objeto[MAX_OBJETO] , int dimension, char mapa[dimension][dimension], int tope){
	for(int i = 0; i < tope; i++){
		mapa[objeto[i].posicion.fil][objeto[i].posicion.col] = objeto[i].tipo;
	}
}


/*Pre condiciones:Recibe la dimension (17 o 12), el mapa y nivel (0 a 3).
*Post condiciones: Coloca todas las paredes en el mapa segun sus coordenadas.
*/
void construir_paredes(int dimension, char mapa[dimension][dimension], nivel_t nivel){
	for(int i = 0; i < nivel.tope_paredes; i++){
		mapa[nivel.paredes[i].fil][nivel.paredes[i].col] = PARED;
	}
}


/*Pre condiciones: Recibe juego y la direccion que el usuario quiera ir (w,a,s,d).
*Post condiciones: Devuelve si es posible moverse en la direccion solicitada.
*/
bool se_puede_mover(juego_t juego, char movimiento, int posicion_parcial_fil, int posicion_parcial_col){
	if(movimiento== MOVER_ARRIBA){
		for(int i = 0; i < juego.niveles[juego.nivel_actual - 1].tope_paredes; i++){
			if( (((posicion_parcial_fil - 1) == juego.niveles[juego.nivel_actual - 1].paredes[i].fil)) &&
			((posicion_parcial_col) == (juego.niveles[juego.nivel_actual - 1].paredes[i].col)) ){
				return false;
			}
		}
		return true;
	}else if (movimiento == MOVER_ABAJO){
		for(int i = 0; i < juego.niveles[juego.nivel_actual - 1].tope_paredes; i++){
			if( (((posicion_parcial_fil + 1) == juego.niveles[juego.nivel_actual - 1].paredes[i].fil)) &&
			((posicion_parcial_col) == (juego.niveles[juego.nivel_actual - 1].paredes[i].col)) ){
				return false;
			}
		}
		return true;
	}else if (movimiento == MOVER_DERECHA){
		for(int i = 0; i < juego.niveles[juego.nivel_actual - 1].tope_paredes; i++){
			if( (((posicion_parcial_fil) == juego.niveles[juego.nivel_actual - 1].paredes[i].fil)) &&
			((posicion_parcial_col + 1) == (juego.niveles[juego.nivel_actual - 1].paredes[i].col)) ){
				return false;
			}
		}
		return true;
	}else if (movimiento == MOVER_IZQUIERDA){
		for(int i = 0; i < juego.niveles[juego.nivel_actual - 1].tope_paredes; i++){
			if( (((posicion_parcial_fil) == juego.niveles[juego.nivel_actual - 1].paredes[i].fil)) &&
			((posicion_parcial_col - 1) == (juego.niveles[juego.nivel_actual - 1].paredes[i].col)) ){
				return false;
			}
		}
		return true;
	}
return false;
}


/*Pre condiciones: Recibe juego y toca_algo.
Post condiciones: Primero encuentra con cual obstaculo interactua y aplica los determinados efectos de ese obstaculo.
      Pinche: -2 movimientos.
      Bomba: le saca todos los movimientos al jugador.
      Guardia: le saca todos los movimientos al jugador (al menos que sea Johnny o Coraje).
*/
void interactuar_obstaculo(juego_t* juego, bool* toca_algo, int posicion_parcial_fil, int posicion_parcial_col){
	for (int i = 0; i < (*juego).niveles[(*juego).nivel_actual - 1].tope_obstaculos; i++){
		if((posicion_parcial_fil == (*juego).niveles[(*juego).nivel_actual - 1].obstaculos[i].posicion.fil) &&
			(posicion_parcial_col == (*juego).niveles[(*juego).nivel_actual - 1].obstaculos[i].posicion.col)){
			(*toca_algo) = true;
			if ((*juego).niveles[(*juego).nivel_actual - 1].obstaculos[i].tipo == PINCHE){
				if (((*juego).personaje.tipo != POLLITO) && ((*juego).personaje.tipo != PURO)){
					(*toca_algo) = false;
					(*juego).personaje.movimientos = (*juego).personaje.movimientos - 2;
				}
				(*toca_algo) = false;
			}else if ((*juego).niveles[(*juego).nivel_actual - 1].obstaculos[i].tipo == BOMBA){
				(*juego).personaje.movimientos = 0;
				
				eliminar_obstaculo(juego, i);
				(*toca_algo) = false;//esto cambie ultimo
			}else if ((*juego).niveles[(*juego).nivel_actual - 1].obstaculos[i].tipo == GUARDIA){
				(*toca_algo) = false;
				if(((*juego).personaje.tipo != JOHNNY) && ((*juego).personaje.tipo != CORAJE)){
					(*juego).personaje.movimientos = 0;
					//(*juego).personaje.murio = true;
				}
			}
		}
	}
}


/*Pre condiciones: Recibe juego, toca_algo, interactua_con_teletransportador y se_metio_una_vez.
Post condiciones: Primero encuentra con cual herramienta interactua y aplica los determinados efectos de esa herramienta.
      Moneda: +3 movimientos (-1 de movimiento)
      Teletransportador: mueve el jugador al proximo teletransportador.
      Interruptor: hace aparecer la llave.
      Llave: hace aparecer la salida.
*/
//void interactuar_herramienta(juego_t* juego, bool* toca_algo, bool* interactua_con_teletransportador, bool se_metio_una_vez,
void interactuar_herramienta(juego_t* juego, bool* toca_algo, bool se_metio_una_vez,
 int* posicion_parcial_fil, int* posicion_parcial_col){
	for (int i = 0; i < (*juego).niveles[(*juego).nivel_actual - 1].tope_herramientas; i++){
		if(((*posicion_parcial_fil) == (*juego).niveles[(*juego).nivel_actual - 1].herramientas[i].posicion.fil) &&
			((*posicion_parcial_col) == (*juego).niveles[(*juego).nivel_actual - 1].herramientas[i].posicion.col)){
			//(*toca_algo) = true;ESTO CAMBIEEEEEE
			if ((*juego).niveles[(*juego).nivel_actual - 1].herramientas[i].tipo == MONEDA){
				(*juego).personaje.movimientos += 1; 
				eliminar_herramienta(juego, i);
				(*toca_algo) = false;//	ESTO CAMBIEEEEEE
			}else if (((*juego).niveles[(*juego).nivel_actual - 1].herramientas[i].tipo == TELETRANSPORTADOR) && (se_metio_una_vez == false)){
				for (int j = i + 1; j < (*juego).niveles[(*juego).nivel_actual - 1].tope_herramientas; j++){
					if ((((*juego).personaje.posicion.fil != (*juego).niveles[(*juego).nivel_actual - 1].herramientas[j].posicion.fil) 
					|| ((*juego).personaje.posicion.col != (*juego).niveles[(*juego).nivel_actual - 1].herramientas[j].posicion.col)) 
					&& ((*juego).niveles[(*juego).nivel_actual - 1].herramientas[j].tipo == TELETRANSPORTADOR) 
					&& (se_metio_una_vez == false)){
						(*posicion_parcial_fil) = (*juego).niveles[(*juego).nivel_actual - 1].herramientas[j].posicion.fil;
						(*posicion_parcial_col) = (*juego).niveles[(*juego).nivel_actual - 1].herramientas[j].posicion.col;
						se_metio_una_vez = true;
						(*toca_algo) = true;
					}
				}
				if(!se_metio_una_vez){
					for (int j = 0; j < i; j++){
						if (((*juego).personaje.posicion.fil != (*juego).niveles[(*juego).nivel_actual - 1].herramientas[j].posicion.fil) 
						&& ((*juego).personaje.posicion.col != (*juego).niveles[(*juego).nivel_actual - 1].herramientas[j].posicion.col) 
						&& ((*juego).niveles[(*juego).nivel_actual - 1].herramientas[j].tipo == TELETRANSPORTADOR)){
							(*posicion_parcial_fil) = (*juego).niveles[(*juego).nivel_actual - 1].herramientas[j].posicion.fil;
							(*posicion_parcial_col) = (*juego).niveles[(*juego).nivel_actual - 1].herramientas[j].posicion.col;
							se_metio_una_vez = true;
							(*toca_algo) = true;
						}
					}
				}
				//se_metio_una_vez = true;
			}else if ((*juego).niveles[(*juego).nivel_actual - 1].herramientas[i].tipo == INTERRUPTOR){
					(*juego).personaje.presiono_interruptor = true;
					(*toca_algo) = false;//	ESTO CAMBIEEEEEE
			}else if ((*juego).niveles[(*juego).nivel_actual - 1].herramientas[i].tipo == LLAVE){
				if(((*juego).personaje.presiono_interruptor == true) || ((*juego).nivel_actual == PRIMER_NIVEL) || 
					((*juego).nivel_actual == SEGUNDO_NIVEL)){
					(*juego).personaje.tiene_llave = true;
					eliminar_herramienta(juego, i);
					(*toca_algo) = false;//esto fue lo ultimo
				}
			}
		}
	}
}
			//}else if ((*juego).niveles[(*juego).nivel_actual - 1].herramientas[i].tipo == TELETRANSPORTADOR){
				/*
				for (int j = 0; j < (*juego).niveles[(*juego).nivel_actual - 1].tope_herramientas; j++){
					if(((*juego).personaje.posicion.fil != (*juego).niveles[(*juego).nivel_actual - 1].herramientas[j].posicion.fil) 
					&& ((*juego).personaje.posicion.col != (*juego).niveles[(*juego).nivel_actual - 1].herramientas[j].posicion.col)){
						if (((*juego).niveles[(*juego).nivel_actual - 1].herramientas[j].tipo == TELETRANSPORTADOR) && (j != i)){
						 //&& ((*interactua_con_teletransportador) == false)){
						 	//printf("ENTRO EN TP VIEJAAA\n");
							(*posicion_parcial_fil) = (*juego).niveles[(*juego).nivel_actual - 1].herramientas[j].posicion.fil;
							(*posicion_parcial_col) = (*juego).niveles[(*juego).nivel_actual - 1].herramientas[j].posicion.col;
							//(*interactua_con_teletransportador) = true;
						}
					}
				}*/
				/*
				bool encontro_tp = false;
				int j = i + 1;
				while(!encontro_tp){
					if(((*juego).niveles[(*juego).nivel_actual - 1].herramientas[j].tipo != TELETRANSPORTADOR) &&
					 (j <= (*juego).niveles[(*juego).nivel_actual - 1].tope_herramientas)){
						j++;
					}else if(((*juego).niveles[(*juego).nivel_actual - 1].herramientas[j].tipo != TELETRANSPORTADOR) &&
					 (j > (*juego).niveles[(*juego).nivel_actual - 1].tope_herramientas)){
						j = 0;
					}else if (((*juego).personaje.posicion.fil != (*juego).niveles[(*juego).nivel_actual - 1].herramientas[j].posicion.fil) 
					&& ((*juego).personaje.posicion.col != (*juego).niveles[(*juego).nivel_actual - 1].herramientas[j].posicion.col)){
						(*posicion_parcial_fil) = (*juego).niveles[(*juego).nivel_actual - 1].herramientas[j].posicion.fil;
						(*posicion_parcial_col) = (*juego).niveles[(*juego).nivel_actual - 1].herramientas[j].posicion.col;
						encontro_tp = true;
						se_metio_una_vez = true;
					}
				}
				*/

/*Pre condiciones: Recibe juego y toca_algo.
Post condiciones: Verifica si el jugador esta en la posicion de salida.
*/
void interactuar_salida(juego_t* juego, bool* toca_algo, int posicion_parcial_fil, int posicion_parcial_col){
	if((*juego).personaje.tiene_llave == true){
		if((posicion_parcial_fil == (*juego).niveles[(*juego).nivel_actual - 1].salida.fil) &&
				(posicion_parcial_col == (*juego).niveles[(*juego).nivel_actual - 1].salida.col)){
			(*toca_algo) = true;
		}
	}
}


/*Pre condiciones: Recide juego, toca_algo y el movimiento del jugador (w,a,s,d).
Post condiciones: Devuelve si el jugador se puede mover el la direccion indicada.
*/
void interactuar_pared(juego_t* juego, bool* toca_algo, char movimiento, int posicion_parcial_fil, int posicion_parcial_col){
	if(movimiento == MOVER_ARRIBA){
		for (int i = 0; i < (*juego).niveles[(*juego).nivel_actual - 1].tope_paredes; i++){
			if(((posicion_parcial_fil - 1) == (*juego).niveles[(*juego).nivel_actual - 1].paredes[i].fil) &&
				(posicion_parcial_col == (*juego).niveles[(*juego).nivel_actual - 1].paredes[i].col)){
				(*toca_algo) = true;
			}
		}		
	}else if(movimiento == MOVER_ABAJO){
		for (int i = 0; i < (*juego).niveles[(*juego).nivel_actual - 1].tope_paredes; i++){
			if(((posicion_parcial_fil + 1) == (*juego).niveles[(*juego).nivel_actual - 1].paredes[i].fil) &&
				(posicion_parcial_col == (*juego).niveles[(*juego).nivel_actual - 1].paredes[i].col)){
				(*toca_algo) = true;
			}
		}
	}else if(movimiento == MOVER_DERECHA){
		for (int i = 0; i < (*juego).niveles[(*juego).nivel_actual - 1].tope_paredes; i++){
			if((posicion_parcial_fil == (*juego).niveles[(*juego).nivel_actual - 1].paredes[i].fil) &&
				((posicion_parcial_col + 1) == (*juego).niveles[(*juego).nivel_actual - 1].paredes[i].col)){
				(*toca_algo) = true;
			}
		}
	}else if(movimiento == MOVER_IZQUIERDA){
		for (int i = 0; i < (*juego).niveles[(*juego).nivel_actual - 1].tope_paredes; i++){
			if((posicion_parcial_fil == (*juego).niveles[(*juego).nivel_actual - 1].paredes[i].fil) &&
				((posicion_parcial_col - 1) == (*juego).niveles[(*juego).nivel_actual - 1].paredes[i].col)){
				(*toca_algo) = true;
			}
		}
	}
}


/*Pre condiciones: Recibe juego.
Post condiciones: Chequea si el jugador se quedo sin movimientos. Y si es asi, en el caso de que murio 
sea false, le asigna nuevos movimientos al jugador. 
*/
void agregar_vida_extra(juego_t* juego){
	if((*juego).personaje.movimientos <= 0){
		if ((((*juego).personaje.tipo == BLUE) || ((*juego).personaje.tipo == BELLOTA)) && (((*juego).personaje.murio) == false)){
			(*juego).personaje.movimientos = MOVIMIENTOS_NUEVOS;
			((*juego).personaje.murio) = true;
		}
	}
}


/*Pre condiciones: Recibe juego.
Post condiciones: Chequea si el jugador se quedo sin movimientos. Y si es asi, cambia el estado de murio a true. 
*/
void verificar_muerte(juego_t* juego){
	if((*juego).personaje.movimientos <= 0){
		((*juego).personaje.murio) = true;
	}
}


/*Pre condiciones: Recibe juego, toca_algo, la direccion que se movio y la posicion parcial del personaje.
*Post condiciones: Realiza los cambios necesarios a la cantidad de movimientos que le quedan al usuario, si pierde la primer vida
en el caso de Blue y Bellota, y por ultimo devuelve si toca_algo es verdadero o falso frenando al personaje cuando entre en contacto con
algo en especifico
*/
bool pasa_arriba_de_algo(juego_t* juego, bool* toca_algo, char movimiento, int* posicion_parcial_fil, int* posicion_parcial_col){
	interactuar_obstaculo(juego, toca_algo, (*posicion_parcial_fil), (*posicion_parcial_col));

	//bool interactua_con_teletransportador = false;
	bool se_metio_una_vez = false;
	
	//interactuar_herramienta(juego, toca_algo, &interactua_con_teletransportador, se_metio_una_vez, posicion_parcial_fil, posicion_parcial_col);
	interactuar_herramienta(juego, toca_algo, se_metio_una_vez, posicion_parcial_fil, posicion_parcial_col);

	interactuar_salida(juego, toca_algo, (*posicion_parcial_fil), (*posicion_parcial_col));

	interactuar_pared(juego, toca_algo, movimiento, (*posicion_parcial_fil), (*posicion_parcial_col));

	agregar_vida_extra(juego);
	verificar_muerte(juego);
return (*toca_algo);
}


/*Pre condiciones: Recibe juego y la direccion a donde quiera ir el usuario (w,a,s,d).
*Post condiciones: Actualiza la posicion del personaje hasta encontrarse con una pared. 
Ademas verifica si pasa arriba de algun objeto o herramienta.
*/
void mover_personaje(juego_t* juego, char movimiento){
	int posicion_parcial_fil = (*juego).personaje.posicion.fil;
	int posicion_parcial_col = (*juego).personaje.posicion.col;
	(*juego).personaje.movimientos--;
	bool toca_algo;
	bool pasar_arriba = false; 
	while( pasar_arriba != true){
		if(movimiento == MOVER_ARRIBA){
			if(se_puede_mover(*juego, movimiento, posicion_parcial_fil, posicion_parcial_col) == true){
				posicion_parcial_fil--;
			}
		}else if (movimiento == MOVER_ABAJO){
			if(se_puede_mover(*juego, movimiento, posicion_parcial_fil, posicion_parcial_col) == true){
				posicion_parcial_fil++;
			}
		}else if (movimiento == MOVER_DERECHA){
			if(se_puede_mover(*juego, movimiento, posicion_parcial_fil, posicion_parcial_col) == true){
				posicion_parcial_col++;
			}
		}else if (movimiento == MOVER_IZQUIERDA){
			if(se_puede_mover(*juego, movimiento, posicion_parcial_fil, posicion_parcial_col) == true){
				posicion_parcial_col--;
			}
		}
		pasar_arriba = pasa_arriba_de_algo(juego, &toca_algo, movimiento, &posicion_parcial_fil, &posicion_parcial_col);
	}
	(*juego).personaje.posicion.fil = posicion_parcial_fil;
	(*juego).personaje.posicion.col = posicion_parcial_col;
}


/*Pre condiciones: Recibe la dimension del nivel (17 o 12), el mapa y juego.
*Post condiciones: Decide si se tiene que mostrar la llave dependiendo si el usuario le haya dado al interruptor.
*/
void aparecer_llave(int dimension, char mapa[dimension][dimension], juego_t juego){
	if (juego.personaje.presiono_interruptor == false){
		for (int i = 0; i < juego.niveles[juego.nivel_actual - 1].tope_herramientas ; ++i){
			if ((juego.niveles[juego.nivel_actual - 1].herramientas[i].tipo == LLAVE)){
				mapa[juego.niveles[juego.nivel_actual - 1].herramientas[i].posicion.fil][juego.niveles[juego.nivel_actual - 1].herramientas[i].posicion.col] = ESPACIO_VACIO;
			}
		}
	}
}


/*Pre condiciones: Recibe la dimension del nivel (17 o 12), el mapa y juego.
*Post condiciones: Imprime todo aquello que tenga una coordenada en el mapa, generando asi lo que ve el usuario.
*/
void imprimir_nivel(int dimension, char mapa[dimension][dimension], juego_t juego){
	printf("\t");
	printf(MORADO);
	printf("Movimientos restantes: %i\n", juego.personaje.movimientos);
	printf("\t");
	printf("Personaje seleccionado: %c\n", juego.personaje.tipo);
	printf(NORMAL);
	rellenar_mapa(dimension, mapa);
	construir_paredes(dimension, mapa, juego.niveles[juego.nivel_actual - 1]);

	colocar_elemento_en_mapa((juego).niveles[(juego.nivel_actual) - 1].herramientas , dimension, mapa, (juego).niveles[(juego.nivel_actual) - 1].tope_herramientas);
	colocar_elemento_en_mapa((juego).niveles[(juego.nivel_actual) - 1].obstaculos , dimension, mapa, (juego).niveles[(juego.nivel_actual) - 1].tope_obstaculos);

	mapa[juego.niveles[(juego.nivel_actual) - 1].entrada.fil][juego.niveles[(juego.nivel_actual) - 1].entrada.col] = ENTRADA;
	
	if(juego.personaje.tiene_llave == true){
		mapa[juego.niveles[(juego.nivel_actual) - 1].salida.fil][juego.niveles[(juego.nivel_actual) - 1].salida.col] = SALIDA;
	}

	aparecer_llave(dimension, mapa, juego);

	mapa[juego.niveles[(juego.nivel_actual) - 1].entrada.fil][juego.niveles[(juego.nivel_actual) - 1].entrada.col] = ENTRADA;
	mapa[juego.personaje.posicion.fil][juego.personaje.posicion.col] = JUGADOR;
	for(int i = 0; i < dimension; i++){
		//printf("\t");
		for(int j = 0; j < dimension; j++){
			printf(FROJO);
			printf( " %c " , mapa[i][j]);
			//printf(NORMAL);
		}
		printf(NORMAL);
		printf("\n");
	}
}


int estado_nivel(personaje_t personaje, coordenada_t salida){
	if(personaje.tiene_llave == true){
		if((personaje.posicion.fil == salida.fil) && (personaje.posicion.col == salida.col) &&
				(personaje.movimientos >= 0))//el =
			return GANO;
		}
return JUGANDO;
}


int estado_juego(juego_t juego){
	if ((juego.nivel_actual == CUARTO_NIVEL) && ((juego.personaje.posicion.fil == juego.niveles[juego.nivel_actual - 1].salida.fil) && 
		(juego.personaje.posicion.col == juego.niveles[juego.nivel_actual - 1].salida.col)) && (juego.personaje.movimientos > 0)){
		return GANO;
	}else if(juego.personaje.movimientos < 1) return PERDIO;
return JUGANDO;
}


void inicializar_nivel(nivel_t* nivel, int numero_nivel, int cantidad_baldosas_pinches, int cantidad_guardia, bool hay_bomba){
	int dimension;
	definir_dimension(&dimension, numero_nivel);

	(*nivel).tope_paredes = 0;
	(*nivel).tope_herramientas = 0;
	(*nivel).tope_obstaculos = 0;

	obtener_paredes(numero_nivel, (*nivel).paredes, &(*nivel).tope_paredes);
	
	definir_obstaculos(cantidad_baldosas_pinches, cantidad_guardia, hay_bomba, nivel, dimension);
	definir_herramientas(cantidad_baldosas_pinches, cantidad_guardia, hay_bomba, nivel, dimension);
	definir_entrada_salida(dimension, nivel);
}


void mostrar_juego(juego_t juego){
	int dimension;
	definir_dimension(&dimension, juego.nivel_actual);

	char mapa[dimension][dimension];

	imprimir_nivel(dimension, mapa, juego);
}


void inicializar_juego(juego_t* juego, char tipo_personaje){
	int cantidad_baldosas_pinches;
	int cantidad_guardia;
	bool hay_bomba;
	(*juego).personaje.tipo = tipo_personaje;
	(*juego).personaje.movimientos = 0;
	(*juego).nivel_actual = PRIMER_NIVEL;

	rellenar_info_nivel(&(*juego).niveles[0], &cantidad_baldosas_pinches, &cantidad_guardia, &hay_bomba, PRIMER_NIVEL);
	inicializar_nivel( &(juego->niveles[0]) , PRIMER_NIVEL, cantidad_baldosas_pinches, cantidad_guardia, hay_bomba);

	rellenar_info_nivel(&(*juego).niveles[1], &cantidad_baldosas_pinches, &cantidad_guardia, &hay_bomba, SEGUNDO_NIVEL);
	inicializar_nivel( &(juego->niveles[1]) , SEGUNDO_NIVEL, cantidad_baldosas_pinches, cantidad_guardia, hay_bomba);

	rellenar_info_nivel(&(*juego).niveles[2], &cantidad_baldosas_pinches, &cantidad_guardia, &hay_bomba, TERCER_NIVEL);	
	inicializar_nivel( &(juego->niveles[2]) , TERCER_NIVEL, cantidad_baldosas_pinches, cantidad_guardia, hay_bomba);	

	rellenar_info_nivel(&(*juego).niveles[3], &cantidad_baldosas_pinches, &cantidad_guardia, &hay_bomba, CUARTO_NIVEL);
	inicializar_nivel( &(juego->niveles[3]) , CUARTO_NIVEL, cantidad_baldosas_pinches, cantidad_guardia, hay_bomba);
}