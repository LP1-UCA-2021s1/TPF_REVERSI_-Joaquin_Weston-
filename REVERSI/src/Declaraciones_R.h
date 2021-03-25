/*
 * Declaraciones_R.h
 *
 *  Created on: 10 feb. 2021
 *      Author: JOAQUIN WESTON
 *      TODO revisar la funcion modo(void), porque no sale de dicha funcion
 */

#ifndef DECLARACIONES_R_H_
#define DECLARACIONES_R_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_NUM 8
#define TRUE 0
#define FALSE 1
#define JUGADOR 0
#define CPU 1
#define JUG_VS_CPU 2
#define JUG_VS_JUG 3
#define CPU_VS_CPU 4
#define BLANCO 1
#define NEGRO 2
#define FIN -1
#define SIGUE 0
#define VACIO 0
#define POS_VAL 5		//valor de posicion valida, el programa lee esto e imprime * en señal de posicion valida
#define LIMITE 9

//Declaracion de tipos de datos, de variables
int opcion, i, j, k, aux_i, aux_j, aux_x, aux_y; 	//iteradores
int numero, turno, color, t, c, x, y, n, contador, mayor, valor, modo_val, modo_opc;
int direccion, direccion_x, direccion_y;
int jugador_1, jugador_2, cpu, eva; //cpu y eva son IA
int terminador, terminador_cpu, c_flag, P_TURNO_JUG, P_TURNO_CPU;			// BANDERA QUE INDICA SI EL JUEGO CONTINUA O TERMINA
int contador_blancas, contador_negras;	//contador de fichas para determinar un ganador
int tablero[MAX_NUM][MAX_NUM];
char columna, buffer;




//Declaracion de funciones

void juego(void);				// Funcion que desarrolla el juego
int modo(void);
void imprimir_tablero(void);
void cargar_tablero(void);
int quien_juega(void);
int color_fichas(void);
void posicion_valida(int jug, int c);
int pierde_turno(int c);
void turno_jugador(int jug, int c);
void turno_cpu(int c, int jug);
void accion_juego(int x, int y, int jug, int c);
void borrar_pv(void);
int convertir_letras(char letra);
int verif_esquinas(int c, int jug);
int accion_cpu(int c, int jug);
int fin_del_juego (int x, int y, int jug, int c);


#endif /* DECLARACIONES_R_H_ */
