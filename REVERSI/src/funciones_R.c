/*
 * funciones_R.c
 *
 *  Created on: 10 feb. 2021
 *      Author: JOAQUIN WESTON
 */

#include "Declaraciones_R.h"

int modo(void){								// funcion que determina el modo de juego
	printf("MODO DE JUEGO \n");				// devuelve el modo de juego
	printf("1- JUGADOR VS CPU \n");
	printf("2- JUGADOR VS JUGADOR \n");
	printf("3- CPU VS CPU \n");
	modo_val = FIN;
	while(modo_val < 0 || modo_val > 4){
		scanf("%d", &modo_val);
		while((buffer = getchar()) != '\n' && buffer != EOF);
	}

	if(modo_val == 1){
		n = JUG_VS_CPU;
	}else if(modo_val == 2){
		n = JUG_VS_JUG;
	}else if (modo_val == 3){
		n = CPU_VS_CPU;
	}
	return n;
}

int quien_juega(void){						//funcion que determina quien comienza a jugar,
											//si t = 1, comienza jugador 1, si t = 2 comienza jugador 2

	//*-->*/printf("quien_juega \n");

	printf("Ingrese el jugador que comienza: \n");
	printf("1- Jugador 1\n");
	printf("2- Jugador 2\n");
	printf("3- ALEATORIO\n");
	scanf("%d", &c);

	while((buffer = getchar()) != '\n' && buffer != EOF);

	switch(c){
		case 1 : t = JUGADOR; printf("Comienza Jugador 1\n"); break;
		case 2 : t = CPU; printf("Comienza CPU\n"); break;
		case 3 : t = rand() % 2;
				if(t == JUGADOR){
					printf("Comienza Jugador 1\n");
					break;
				}else printf("Comienza CPU\n");
				break;
		default : printf("Ha ingresado un valor incorrecto"); quien_juega();
		}

	return t;
}

int color_fichas(void){						//funcion que determina el color de los jugadores

	//*-->*/printf("color_fichas \n");

	printf("Escoja el color de las fichas:\n");
	printf("1- Blancas -> Jugador 1\n");
	printf("2- Blancas -> CPU\n");
	printf("3- ALEATORIO\n");
	scanf("%d", &c);

	while((buffer = getchar()) != '\n' && buffer != EOF);

	switch(c){
		case 1 : c = 1;printf("El Jugador tiene las blancas y la CPU las negras\n"); break;
		case 2 : c = 2; printf("La CPU tiene las blancas y el Jugador las negras\n"); break;
		case 3 : c = rand() % 2 + 1;
		if(t == JUGADOR){
			printf("El Jugador tiene las blancas y la CPU las negras\n");
		}else printf("La CPU tiene las blancas y el Jugador las negras\n");
		break;
		default : printf("Ha ingresado un valor incorrecto"); c = FIN ;
	}

	return c;
}

void cargar_tablero(void){					// carga e inicializa el tablero con '0'

	//*-->*/printf("cargar_tablero \n");

	for (i = 0; i < MAX_NUM; i++){
		for (j = 0; j < MAX_NUM; j++){
			if ((i == 3 && j == 3) || (i == 4 && j == 4)){
				tablero[i][j] = BLANCO;
			}else if((i == 4 && j == 3) || (i == 3 && j == 4)){
				tablero[i][j] = NEGRO;

			}else {
				tablero[i][j] = 0;
				}

		}
	}

}

void imprimir_tablero(void){				// imprime el tablero

	//*-->*/printf("imprimir_tablero \n");

	printf("\n");
	numero = 0;

	printf("\n.x. A  B  C  D  E  F  G  H .x.\n");

	while (numero < MAX_NUM){
		for (i = 0; i < MAX_NUM; i++){
			printf("%d.-", numero++);
			for (j = 0; j < MAX_NUM; j++){
				printf(" %d ", tablero[i][j]);
			}
			printf("-.%d", numero);
			printf("\n");
		}
	}
	printf(".x. A  B  C  D  E  F  G  H .x.\n");
}

											// el primer color indica la ficha que juega y el segundo la ficha del contrario
void posicion_valida(int jug, int c){		//recibe el "color" de la ficha y revisa en el tablero si se puede jugar
	//*-->*/printf("entre a posicion valida\n");
	borrar_pv();
	for(i = 0; i < MAX_NUM; i++){
			for(j = 0; j < MAX_NUM; j++){
				if(tablero[i][j] == c){		//si en el tablero se encuentra una ficha del jugador
					/*ARRIBA*///*-->*/printf("arriba\n");
					aux_i = i - 1;
					while(aux_i >= VACIO && tablero[aux_i][j] != jug && tablero[aux_i][j] != POS_VAL){
						if (tablero[i+1][j] != jug){	// Si la ficha de abajo es una ficha del jugador, continua, hay sandwich
							break;   //Si no, no se puede determinar si hay alguna posicion valida
						}

						if(tablero[aux_i][j] == c){		//si la ficha de arriba es del otro color sigue subiendo
							aux_i--;
						}else if(tablero[aux_i][j] == VACIO){
							tablero[aux_i][j] = POS_VAL;
							break;
						}
					}

					/*ABAJO*///*-->*/printf("abajo\n");
					aux_i = i + 1;
					while(aux_i <= MAX_NUM && tablero[aux_i][j] != jug && tablero[aux_i][j] != POS_VAL){

						if(tablero[i-1][j] != jug){
							break;
						}

						if(tablero[aux_i][j] == c){		//si la ficha de abajo es del otro color sigue bajando
							aux_i++;
						}else if(tablero[aux_i][j] == VACIO){
							tablero[aux_i][j] = POS_VAL;
							break;
						}
					}

					/*DERECHA*///*-->*/printf("derecha\n");
					aux_j = j + 1;
					while(aux_j <= MAX_NUM && tablero[i][aux_j] != jug && tablero[i][aux_j] != POS_VAL){

						if(tablero[i][j-1] != jug){
							break;
						}

						if(tablero[i][aux_j] == c){		//si la ficha de la derecha es del otro color sigue a la derecha
							aux_j++;
						}else if(tablero[i][aux_j] == VACIO){
							tablero[i][aux_j] = POS_VAL;
							break;
						}
					}

					/*IZQUIERDA*///*-->*/printf("izquierda\n");
					aux_j = j - 1;
					while(aux_j >= VACIO && tablero[i][aux_j] != jug && tablero[i][aux_j] != POS_VAL){

						if(tablero[i][j+1] != jug){
							break;
						}

						if(tablero[i][aux_j] == c){		//si la ficha de la izquierda es del otro color sigue a la izquierda
							aux_j--;
						}else if(tablero[i][aux_j] == VACIO){
							tablero[i][aux_j] = POS_VAL;
							break;
						}
					}

					/*DIAGONAL SUPERIOR DERECHA*///*-->*/printf("d-sup-der\n");
					aux_i = i - 1;
					aux_j = j + 1;
					while(aux_i >= VACIO && aux_j <= MAX_NUM && tablero[aux_i][aux_j] != jug && tablero[aux_i][aux_j] != POS_VAL){

						if(tablero[i+1][j-1] != jug){
							break;
						}

						if(tablero[aux_i][aux_j] == c){		//si la ficha de la diagonal superior derecha es una ficha contraria, sigue
							aux_i--;
							aux_j++;
						}else if(tablero[aux_i][aux_j] == VACIO){
							tablero[aux_i][aux_j] = POS_VAL;
							break;
						}
					}

					/*DIAGONAL INFERIOR DERECHA*///*-->*/printf("d-inf-der\n");
					aux_i = i + 1;
					aux_j = j + 1;
					while(aux_i <= MAX_NUM && aux_j <= MAX_NUM && tablero[aux_i][aux_j] != jug && tablero[aux_i][aux_j] != POS_VAL){

						if(tablero[i-1][j-1] != jug){
							break;
						}

						if(tablero[aux_i][aux_j] == c){		//si la ficha de la diagonal inferior derecha es una ficha contraria, sigue
							aux_i++;
							aux_j++;
						}else if(tablero[aux_i][aux_j] == VACIO){
							tablero[aux_i][aux_j] = POS_VAL;
							break;
						}
					}


					/*DIAGONAL INFERIOR IZQUIERDA*///*-->*/printf("d-inf-izq\n");
					aux_i = i + 1;
					aux_j = j - 1;
					while(aux_i <= MAX_NUM && aux_j >= VACIO && tablero[aux_i][aux_j] != jug && tablero[aux_i][aux_j] != POS_VAL){

						if(tablero[i-1][j+1] != jug){
							break;
						}

						if(tablero[aux_i][aux_j] == c){		//si la ficha de la diagonal inferior izquierda es una ficha contraria, sigue
							aux_i++;
							aux_j--;
						}else if(tablero[aux_i][aux_j] == VACIO){
							tablero[aux_i][aux_j] = POS_VAL;
							break;
						}
					}


					/*DIAGONAL SUPERIOR IZQUIERDA*///*-->*/printf("d-sup-izq\n");
					aux_i = i - 1;
					aux_j = j - 1;
					while(aux_i >= VACIO && aux_j >= VACIO && tablero[aux_i][aux_j] != jug && tablero[aux_i][aux_j] != POS_VAL){

						if(tablero[i+1][j+1] != jug){
							aux_i = FIN;
							aux_j = FIN;
						}

						if(tablero[aux_i][aux_j] == c){		//si la ficha de la diagonal superior izquierda es una ficha contraria, sigue
							aux_i--;
							aux_j--;

						}else if(tablero[aux_i][aux_j] == VACIO){

							tablero[aux_i][aux_j] = POS_VAL;
							break;
						}
					}
				}
			}
		}
}

int pierde_turno(int c){					//debe contar la cantidad de posiciones validas, si es cero pierde el turno por no poder jugar
											//devuelve TRUE si es que no encuentra alguna posicion y FALSE si encuentra
	//*-->*/printf("entre a pierde turno\n");
	for(i = 0; i < MAX_NUM; i++){
		for(j = 0; j < MAX_NUM; j++){
			if (tablero[i][j] == POS_VAL){
				printf("Existen movimientos validos\n");
				return FALSE;
			}
		}
	}
	printf("No existen movimientos validos, pierde el turno\n");
	return TRUE;
}

void turno_jugador(int jug, int c){			//efectua los movimientos, los cambios de ficha y
											//limpia el tablero de las posiciones validas.
											//recibe las coordenadas y el color de la ficha
	//*-->*/printf("entre a turno_jugador\n");
	opcion = SIGUE;
	while(opcion == SIGUE){
		printf("INGRESE FILA: \n");
		scanf("%d", &x);

		while((buffer = getchar()) != '\n' && buffer != EOF);

		printf("INGRESE columna: \n");
		scanf("%c", &columna);

		while((buffer = getchar()) != '\n' && buffer != EOF);

		y = convertir_letras(columna);
		if(tablero[x][y] == POS_VAL){
			opcion = FIN;
		}else {
			printf("POSICION INCORRECTA\n");
			opcion = SIGUE;
		}
	}
	tablero[x][y] = jug;
	accion_juego(x,y,jug,c);
	borrar_pv();
}

void accion_juego(int x, int y, int jug, int c){ 	//con las coordenadas, recorre las 8 direcciones para
													//realizar los cambios de color en las fichas
	//*-->*/printf("entre accion del juego\n");
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
	while(contador > 0){
		aux_x--;
		tablero[aux_x][y] = jug;
		contador--;
	}

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
	while(contador > 0){
		aux_x++;
		tablero[aux_x][y] = jug;
		contador--;
	}

	/*DERECHA*/

	aux_y = y;
	contador = 0;
	for (j = aux_y+1; j < MAX_NUM; ++j){
			if (tablero[x][j] == c ){
				contador++;
			}else if (tablero[x][j] == jug){
				j = MAX_NUM;
			}else if (tablero[x][j] == VACIO || tablero[x][j] == POS_VAL){
				contador = 0;
				j = MAX_NUM;
			}
	}
	while(contador > 0){
		aux_y++;
		tablero[x][aux_y] = jug;
		contador--;
	}

	/*IZQUIERDA*/

	contador = 0;
	aux_y = y;
	for (j = aux_y-1; j > VACIO; j--){
			if (tablero[x][j] == c){
				contador++;
			}else if (tablero[x][j] == jug){
				j = VACIO;
			}else if (tablero[x][j] == VACIO || tablero[x][j] == POS_VAL){
				contador = 0;
				j = VACIO;
			}
	}
	while(contador > 0){
		aux_y--;
		tablero[x][aux_y] = jug;
		contador--;
	}

	/*DIAGONAL SUPERIOR DERECHA*/

	c_flag = SIGUE;
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
	aux_x = x;
	aux_y = y;
	while(contador > 0){
		aux_x--;
		aux_y++;
		tablero[aux_x][aux_y] = jug;
		contador--;
	}

	/*DIAGONAL INFERIOR DERECHA*/

	c_flag = SIGUE;
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
	aux_x = x;
	aux_y = y;
	while(contador > 0){
		aux_x++;
		aux_y++;
		tablero[aux_x][aux_y] = jug;
		contador--;
	}

	/*DIAGONAL INFERIOR IZQUIERDA*/

	c_flag = SIGUE;
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
	aux_x = x;
	aux_y = y;
	while(contador > 0){
		aux_x++;
		aux_y--;
		tablero[aux_x][aux_y] = jug;
		contador--;
	}

	/*DIAGONAL SUPERIOR IZQUIERDA*/

	c_flag = SIGUE;
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
	aux_x = x;
	aux_y = y;
	while(contador > 0){
		aux_x--;
		aux_y--;
		tablero[aux_x][aux_y] = jug;
		contador--;
	}


}

void borrar_pv(){									//borra las posiciones validas no utilizadas

	//*-->*/printf("borrar_pv \n");

	for(i = 0; i < MAX_NUM; i++){
		for(j = 0; j < MAX_NUM; j++){
			if(tablero[i][j] == POS_VAL){
				tablero[i][j] = VACIO;
			}
		}
	}
}

int convertir_letras(char letra){					// convierte la columna recibida en caracter a entero

	//*-->*/printf("convertir_letras \n");

	switch(letra){
	/*MAYUSCULAS*/
	case 'A': numero = 0; break;
	case 'B': numero = 1; break;
	case 'C': numero = 2; break;
	case 'D': numero = 3; break;
	case 'E': numero = 4; break;
	case 'F': numero = 5; break;
	case 'G': numero = 6; break;
	case 'H': numero = 7; break;
	/*minusculas*/
	case 'a': numero = 0; break;
	case 'b': numero = 1; break;
	case 'c': numero = 2; break;
	case 'd': numero = 3; break;
	case 'e': numero = 4; break;
	case 'f': numero = 5; break;
	case 'g': numero = 6; break;
	case 'h': numero = 7; break;
	default : numero = FIN;
	}
	return numero;
}


int fin_del_juego (int x, int y, int jug, int c){	//funcion que determina el fin del juego y da un ganador

	//*-->*/printf("fin_del_juego \n");

	contador_blancas = 0;
	contador_negras = 0;
	if (x == TRUE && y == TRUE){// ninguno de los dos pueden hacer movimientos, el juego termina
		printf("JUEGO TERMINADO\n");
		for(i = 0; i < MAX_NUM; i++){
			for(j = 0; j < MAX_NUM; j++){
				if(tablero[i][j] == jug){
					contador_blancas++;
				}else if(tablero[i][j] == c){
					contador_negras++;
				}
			}
		}
		if (contador_blancas > contador_negras){
			printf("GANA EL JUGADOR\n");
		}else if(contador_blancas < contador_negras){
			printf("GANA LA CPU\n");
		}else if(contador_blancas == contador_negras){
			printf("EMPATE\n");
		}
		return FIN;
	}else {
		return SIGUE;
	}
}

