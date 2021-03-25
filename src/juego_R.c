/*
 * juego_R.c
 *
 *  Created on: 11 feb. 2021
 *      Author: JOAQUIN WESTON
 */

#include "Declaraciones_R.h"

int terminador = SIGUE;
void juego(){

	cargar_tablero();

	/*MENU DONDE SE DAN LAS 3 OPCIONES DE JUEGO*/

	modo_opc = modo();

	if(modo_opc == JUG_VS_CPU){
		turno = quien_juega();
		color = color_fichas();

		if (color == 1){
			jugador_1 = BLANCO;
			cpu = NEGRO;
		}else if(color == 2){
			jugador_1 = NEGRO;
			cpu = BLANCO;
		}

		if (turno == FIN || color == FIN){
			terminador = FIN;
		}
	}else if(modo_opc == JUG_VS_JUG){
		turno = quien_juega();
		color = color_fichas();

		if (color == 1){
			jugador_1 = BLANCO;
			jugador_2 = NEGRO;
		}else if(color == 2){
			jugador_1 = NEGRO;
			jugador_2 = BLANCO;
		}

		if (turno == FIN || color == FIN){
			terminador = FIN;
		}
	}else if(modo_opc == CPU_VS_CPU){
		cpu = BLANCO;
		eva = NEGRO;
	}



	/*-->*/while(terminador != FIN){		//LOOP DEL JUEGO -->

		if (modo_opc == JUG_VS_CPU){
			if(turno == JUGADOR){		// primero juega jugador 1 y luego la CPU
				printf("TURNO DE JUGADOR_1 \n");

				/*turno del jugador 1*/

				posicion_valida(jugador_1, cpu);	//la funcion debe verificar si es posible poner alguna ficha

				imprimir_tablero();

				if (pierde_turno(jugador_1) == FALSE){
					printf("JUEGA JUGADOR_1 \n");
					P_TURNO_JUG = FALSE;
					turno_jugador(jugador_1, cpu);
				}else {
					printf("No hay posicion valida para jugar\n");
					printf("Pierde el turno\n");
					P_TURNO_JUG = TRUE;
				}
				imprimir_tablero();

				/*turno de la CPU*/

				printf("TURNO DE LA CPU \n");
				posicion_valida(cpu, jugador_1);
				if (pierde_turno(cpu) == FALSE){
					turno_cpu(cpu, jugador_1);
					P_TURNO_CPU = FALSE;
				}else {
					printf("No hay posicion valida para jugar\n");
					printf("Pierde el turno\n");
					P_TURNO_CPU = TRUE;
				}
				imprimir_tablero();

				terminador = fin_del_juego(P_TURNO_JUG,P_TURNO_CPU,jugador_1,cpu);

			}else if(turno == CPU){		// primero juega la CPU y luego el jugador_1

				/*turno de la CPU*/
				printf("TURNO DE LA CPU \n");

				posicion_valida(cpu, jugador_1);
				if (pierde_turno(cpu) == FALSE){
					turno_cpu(cpu, jugador_1);
					P_TURNO_CPU = FALSE;
				}else {
					printf("No hay posicion valida para jugar\n");
					printf("Pierde el turno\n");
					P_TURNO_CPU = TRUE;
				}
				imprimir_tablero();

				/*turno del jugador 1*/
				printf("TURNO DE JUGADOR_1 \n");

				posicion_valida(jugador_1, cpu);
				imprimir_tablero();
				if (pierde_turno(jugador_1) == FALSE){
					turno_jugador(jugador_1, cpu);
					P_TURNO_JUG = FALSE;
				}else {
					printf("No hay posicion valida para jugar\n");
					printf("Pierde el turno\n");
					P_TURNO_JUG = TRUE;
				}

				imprimir_tablero();
				terminador = fin_del_juego(P_TURNO_JUG,P_TURNO_CPU,jugador_1,cpu);
			}
		}else if(modo_opc == JUG_VS_JUG){

			if(turno == JUGADOR){		// primero juega jugador 1 y luego el jugador 2
				printf("TURNO DE JUGADOR_1 \n");

				/*turno del jugador 1*/

				posicion_valida(jugador_1, jugador_2);	//la funcion debe verificar si es posible poner alguna ficha

				imprimir_tablero();

				if (pierde_turno(jugador_1) == FALSE){
					printf("JUEGA JUGADOR_1 \n");
					P_TURNO_JUG = FALSE;
					turno_jugador(jugador_1, jugador_2);
				}else {
					printf("No hay posicion valida para jugar\n");
					printf("Pierde el turno\n");
					P_TURNO_JUG = TRUE;
				}
				imprimir_tablero();

				/*turno del jugador 2*/

				printf("TURNO DEL JUGADOR 2 \n");
				posicion_valida(jugador_2, jugador_1);	//la funcion debe verificar si es posible poner alguna ficha

				imprimir_tablero();

				if (pierde_turno(jugador_2) == FALSE){
					printf("JUEGA JUGADOR_2 \n");
					P_TURNO_JUG = FALSE;
					turno_jugador(jugador_2, jugador_1);
				}else {
					printf("No hay posicion valida para jugar\n");
					printf("Pierde el turno\n");
					P_TURNO_JUG = TRUE;
				}
				imprimir_tablero();
				terminador = fin_del_juego(P_TURNO_JUG,P_TURNO_CPU,jugador_1,jugador_2);

			}else if(turno == CPU){		// primero juega EL JUGADOR 2 y luego EL JUGADOR 1

				/*turno deL JUGADOR 2*/
				printf("TURNO DL JUGADOR 2 \n");

				posicion_valida(jugador_2, jugador_1);	//la funcion debe verificar si es posible poner alguna ficha

				imprimir_tablero();

				if (pierde_turno(jugador_2) == FALSE){
					printf("JUEGA JUGADOR_2 \n");
					P_TURNO_JUG = FALSE;
					turno_jugador(jugador_2, jugador_1);
				}else {
					printf("No hay posicion valida para jugar\n");
					printf("Pierde el turno\n");
					P_TURNO_JUG = TRUE;
				}
				imprimir_tablero();

				/*turno del jugador 1*/
				printf("TURNO DE JUGADOR_1 \n");

				posicion_valida(jugador_1, jugador_2);
				imprimir_tablero();
				if (pierde_turno(jugador_1) == FALSE){
					turno_jugador(jugador_1, jugador_2);
					P_TURNO_JUG = FALSE;
				}else {
					printf("No hay posicion valida para jugar\n");
					printf("Pierde el turno\n");
					P_TURNO_JUG = TRUE;
				}

				imprimir_tablero();
				terminador = fin_del_juego(P_TURNO_JUG,P_TURNO_CPU,jugador_1,jugador_2);
			}
		}else if(modo_opc == CPU_VS_CPU){
			imprimir_tablero();

			/*turno de la CPU*/

			printf("TURNO DE LA CPU \n");
			posicion_valida(cpu, eva);
			if (pierde_turno(cpu) == FALSE){
				turno_cpu(cpu, eva);
				P_TURNO_CPU = FALSE;
			}else {
				printf("No hay posicion valida para jugar\n");
				printf("Pierde el turno\n");
				P_TURNO_CPU = TRUE;
			}
			imprimir_tablero();

			/*turno de EVA*/

			printf("TURNO DE EVA \n");
			posicion_valida(eva, cpu);
			if (pierde_turno(eva) == FALSE){
				turno_cpu(eva, cpu);
				P_TURNO_JUG = FALSE;
			}else {
				printf("No hay posicion valida para jugar\n");
				printf("Pierde el turno\n");
				P_TURNO_JUG = TRUE;
			}
			imprimir_tablero();
			terminador = fin_del_juego(P_TURNO_CPU,P_TURNO_JUG,cpu,eva);
		}
	}
	terminador = FIN;
}
