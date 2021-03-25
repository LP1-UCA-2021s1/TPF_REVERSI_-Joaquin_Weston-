/*
 * inteligencia_cpu.c
 *
 *  Created on: 12 feb. 2021
 *      Author: JOAQUIN WESTON
 *
 *      ->AQUI DEBE ESTAR TODA LA INTELIGENCIA DEL JUEGO
 *
 */

#include "Declaraciones_R.h"

void turno_cpu(int c, int jug){			//Se encarga de realizar el movimiento de juego de la IA

	terminador_cpu = SIGUE;
	while (terminador_cpu == SIGUE){
	/*Las esquinas son las mas importantes, ya que se tiene un mayor control*/
		if(verif_esquinas(c, jug) == SIGUE){
			/*Luego se encuentra el borde, ayuda a sumar puntos*/
			terminador_cpu = accion_cpu(c, jug);
		}
	}
}

int verif_esquinas(int c, int jug){			//verifica si hay posibilidad de ocuparlas esquinas del tablero
	//*-->*/printf("verif_esquinas \n");
	mayor = 0;

	contador = 0;
	if (tablero[0][0] == POS_VAL){
		accion_juego(0,0,c,jug);
		return numero = FIN;
	}else if (tablero[0][7] == POS_VAL){
		accion_juego(0,7,c,jug);
		return numero = FIN;
	}else if (tablero[7][0] == POS_VAL){
		accion_juego(7,0,c,jug);
		return numero = FIN;
	}else if (tablero[7][7] == POS_VAL){
		accion_juego(7,7,c,jug);
		return numero = FIN;
	}else return SIGUE;
}

int accion_cpu(int jug, int c){ //lo que debe hacer esta funcion es: analizar el tablero
								//elegir la mejor opcion para la cpu

	valor = 0;
	for(x = 0; x < MAX_NUM; x++){
		for(y = 0; y < MAX_NUM; y++){
			if(tablero[x][y] == POS_VAL){
				mayor = 0; //contador que ayuda a determinar el movimiento

				/*ARRIBA*/

				aux_x = x;
				contador = 0;
				for (i = aux_x-1; i > VACIO; i--){
					if (tablero[i][y] == c){
						contador++;
					}else if (tablero[i][y] == jug){
						i = VACIO;
					}else if (tablero[i][y] == VACIO || tablero[i][y] == POS_VAL){
						contador = 0;
						i = VACIO;
					}
				}
				mayor = mayor + contador;

				/*ABAJO*/

				contador = 0;
				aux_x = x;
				for (i = aux_x+1; i < MAX_NUM; ++i){
					if (tablero[i][y] == c ){
						contador++;
					}else if (tablero[i][y] == jug){
						i = MAX_NUM;
					}else if (tablero[i][y] == VACIO || tablero[i][y] == POS_VAL){
						contador = 0;
						i = MAX_NUM;
					}
				}
				mayor = mayor + contador;

				/*DERECHA*/

				aux_y = y;
				contador = 0;
				for (j = aux_y+1; j < MAX_NUM; ++j){
						if (tablero[x][j] == c ){
							contador++;
						}else if (tablero[i][y] == jug){
							j = MAX_NUM;
						}else if (tablero[x][j] == VACIO || tablero[i][y] == POS_VAL){
							contador = 0;
							j = MAX_NUM;
						}
					}
				mayor = mayor + contador;

				/*IZQUIERDA*/

				contador = 0;
				aux_y = y;
				for (j = aux_y-1; j > VACIO; j--){
						if (tablero[x][j] == c){
							contador++;
						}else if (tablero[x][j] == jug){
							j = VACIO;
						}else if (tablero[x][j] == VACIO || tablero[i][y] == POS_VAL){
							contador = 0;
							j = VACIO;
						}
					}
				mayor = mayor + contador;

				/*DIAGONAL SUPERIOR DERECHA*/

				contador = 0;
				aux_x = x;
				aux_y = y;
				while(c_flag == SIGUE){
					--aux_x;
					++aux_y;
					if (tablero[aux_x][aux_y] == c){
						contador++;
					}else if(tablero[aux_x][aux_y] == jug){
						c_flag = FIN;
					}else if (tablero[aux_x][aux_y] == VACIO || tablero[aux_x][aux_y] == POS_VAL){
						contador = 0;
						c_flag = FIN;
					}
				}
				mayor = mayor + contador;

				/*DIAGONAL INFERIOR DERECHA*/

				contador = 0;
				aux_x = x;
				aux_y = y;
				while(c_flag == SIGUE){
						++aux_x;
						++aux_y;
						if (tablero[aux_x][aux_y] == c){
							contador++;
						}else if(tablero[aux_x][aux_y] == jug){
							c_flag = FIN;
						}else if (tablero[aux_x][aux_y] == VACIO || tablero[aux_x][aux_y] == POS_VAL){
							contador = 0;
							c_flag = FIN;
						}
					}
				mayor = mayor + contador;

				/*DIAGONAL INFERIOR IZQUIERDA*/

				contador = 0;
				aux_x = x;
				aux_y = y;
				while(c_flag == SIGUE){
					++aux_x;
					--aux_y;
					if (tablero[aux_x][aux_y] == c){
						contador++;
					}else if(tablero[aux_x][aux_y] == jug){
						c_flag = FIN;
					}else if (tablero[aux_x][aux_y] == VACIO || tablero[aux_x][aux_y] == POS_VAL){
						contador = 0;
						c_flag = FIN;
					}
				}
				mayor = mayor + contador;

				/*DIAGONAL SUPERIOR IZQUIERDA*/

				contador = 0;
				aux_x = x;
				aux_y = y;
				while(c_flag == SIGUE){
						--aux_x;
						--aux_y;
						if (tablero[aux_x][aux_y] == c){
							contador++;
						}else if(tablero[aux_x][aux_y] == jug){
							c_flag = FIN;
						}else if (tablero[aux_x][aux_y] == VACIO || tablero[aux_x][aux_y] == POS_VAL){
							contador = 0;
							c_flag = FIN;
						}
				}
				mayor = mayor + contador;

				if(mayor > valor){
					valor = mayor;
					direccion_x = x;
					direccion_y = y;
				}
			}
		}
	}
	tablero[direccion_x][direccion_y] = jug;
	accion_juego(direccion_x,direccion_y,jug,c);
	borrar_pv();
	printf("%d - %d-%d\n", valor,direccion_x,direccion_y);
	return FIN;
}

