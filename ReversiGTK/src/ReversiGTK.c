/*
 ============================================================================
 Name        : GTKpractica.c
 Author      : Joaquin Weston
 Version     :
 Copyright   : Your copyright notice
 Description : REVERSI in GTK+
 ============================================================================
 */

#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>
#include <time.h>


//Declaracion de funciones
void imprimir_tablero();
void ActualizarTablero();
void borrar_pv();
void posicion_valida(int jug, int c);
void imprimir_tablero(void);
void cargar_tablero(void);
void accion_juego(int x, int y, int jug, int c);

//Constantes importantes
#define MAX_NUM 8
#define N 8										//Fila y Columna de la matriz
#define NAME 25
#define SONIC 1
#define EGGMAN 2
#define VACIO 0
#define POS_VAL 5		//valor de posicion valida, el programa lee esto e imprime * en señal de posicion valida
#define FIN -1
#define SIGUE 0

GtkImage *imagenes[MAX_NUM][MAX_NUM];

//Vector de strings que sirve para almacenar las imagenes del tablero

char *imagenesVacio[] = {"./IMG/coin.png","IMG/sonic.png","IMG/eggman.png", "IMG/indice.png"};

//Variables Globales para logica en C

int opcion_modo; 			//si coloca jVSj, jVScpu, cpuVScpu
int quepieza;  				//que color de pieza
int turno; 					//quien inicia
int modoseleccion = 0; 		//indica si al hacer click se esta seleccionando que pieza mover o a donde mover
int tablero[N][N];

//Declaracion de tipos de datos, de variables

int opcion, k, aux_i, aux_j, aux_x, aux_y, x, y; 	//iteradores
int numero, turno, color, t, c, n, contador, mayor, valor, modo_val, modo_opc, mod;
int direccion, direccion_x, direccion_y;
int jugador_1, jugador_2, cpu, eva; //cpu y eva son IA
int terminador, terminador_cpu, c_flag, P_TURNO_JUG, P_TURNO_CPU;			// BANDERA QUE INDICA SI EL JUEGO CONTINUA O TERMINA
int contador_blancas, contador_negras;	//contador de fichas para determinar un ganador
char columna, buffer;

//General
    GtkBuilder *builder;

//Ventana de inicio
	GtkWidget *window1;
    GtkWidget *fixedinicio;
    GtkWidget *botonadelante;
    GtkWidget *botoninfo;
    GtkWidget *imagenprincipal;

//Ventana Acerca De
    GtkWidget *windowacercade;
    GtkWidget *fixedacercade;
    GtkWidget *labelacercade;
    GtkWidget *labelinfo;
    GtkWidget *imagenacercade;
    GtkWidget *botonFininfo;

//Ventana Configuracion de la partida
    GtkWidget *windowconfig;//
    GtkWidget *fixedconfig;//
    GtkWidget *fondoconfig;
    GtkWidget *labeltituloconfig;
    GtkWidget *botonterminarconfig;//
    GtkWidget *toogle_sonic;
    GtkWidget *toogle_aleatoriocolor;;
    GtkWidget *toogle_jugvscpu;
    GtkWidget *toogle_jugvsjug;
    GtkWidget *toogle_empiezajugador;
    GtkWidget *entrynombrejugador;
    GtkEntry *entrynombrejugador1;
    gchar *nombre_1;
    gchar *nombre_2;

//Ventana de Ayuda
    GtkWidget *windowayuda;
    GtkWidget *botonabrirayuda;
    GtkWidget *botoncerrarayuda;

//Ventana Colocar piezas en tablero
    GtkWidget *fixedtablero;
    GtkWidget *windowtablero;
    GtkWidget *box_tablero;
    GtkWidget *label_turno;
    GtkWidget *label_jugada;

void botonadelante_clicked_cb(GtkWidget *widget, gpointer data) {
	gtk_widget_show_all(windowconfig);
}

void botonFininfo_clicked_cb(GtkWidget *widget, gpointer data) {
	gtk_widget_hide(windowacercade);
}

void botoninfo_clicked_cb(GtkWidget *widget, gpointer data) {
	gtk_widget_show_all(windowacercade);
}

void botonterminarconfig_clicked_cb(GtkWidget *widget, gpointer data) {
	//if(opcion_modo){
		gtk_widget_show_all(windowtablero);
	//}
}

void on_toogle_jugvsjug(GtkRadioButton *toogle_jugvsjug,gpointer data){
	gboolean T = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(toogle_jugvsjug));
	gboolean X = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(toogle_jugvscpu));
	if (T){
		printf("J VS J\n");
		opcion_modo = 1;
	}
	else if(X){
		printf("J VS CPU\n");
		opcion_modo = 0;
	}else {
		printf("CPU VS CPU\n");
		opcion_modo = 2;
	}
}

void on_toogle_sonic(GtkRadioButton *toogle_sonic, gpointer data){
	gboolean T = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(toogle_sonic));
	gboolean X = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(toogle_aleatoriocolor));

	if (T){
		printf("Entro al color sonic\n");
		jugador_1 = SONIC;
		jugador_2 = EGGMAN;
		quepieza = 1;
	}else if(X) {
		quepieza = rand()%2;
		printf("Se va a elegir aleatoriamente el color: %d\n", quepieza);
	}
	else {
		quepieza = 0;
		jugador_1 = EGGMAN;
		jugador_2 = SONIC;
		printf("Entro al color eggman\n");
	}
}

void on_toogle_empiezajugador(GtkRadioButton *toogle_empiezajugador,gpointer data){
	gboolean T= gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(toogle_empiezajugador));
	if (T){
		turno = 1;
		printf("Comienza jugador 1\n");
		gchar *temp = g_strdup_printf("TURNO DEL JUGADOR 1");
		gtk_label_set_text(GTK_LABEL(label_turno), temp);
		g_free(temp);
	}
	else{
		turno = 0;
		printf("comienza jugador 2 / pc\n");
		gchar *temp = g_strdup_printf("TURNO DEL JUGADOR 2");
		gtk_label_set_text(GTK_LABEL(label_turno), temp);
		g_free(temp);
	}
}

void entry_jug(GtkWidget *widget, gpointer data){
	nombre_1 = gtk_entry_get_text(entrynombrejugador);
}

void entry_jug1(GtkWidget *widget1, gpointer data){
	nombre_2 = gtk_entry_get_text(entrynombrejugador1);
}

botoncerrarayuda_clicked_cb(GtkWidget *widget, gpointer data){
	gtk_widget_hide(windowayuda);
}

botonabrirayuda_clicked_cb(GtkWidget *widget, gpointer data){
	gtk_widget_show_all(windowayuda);
}

int filamov, columnamov, filamov2, columnamov2; //

void tablero_cb(GtkWidget *event_box, GdkEventButton *event, gpointer data){
	guint i,j;
	guint m,n;

	printf("turnoo %d - %d\n", opcion_modo, turno);

	if(opcion_modo == 1){		//jug vs jug
		printf("J VS J\n");
		if(turno == 1){		// primero jug1 y luego jug2

			gchar *temp = g_strdup_printf("TURNO DEL JUGADOR 1");
			gtk_label_set_text(GTK_LABEL(label_turno), nombre_1);
			g_free(temp);
			posicion_valida(jugador_1,jugador_2);

			i = (GUINT_FROM_LE(event -> y) / 50); 	//las imagenes son de 50x50pixeles
			j = (GUINT_FROM_LE(event -> x) / 50);
			printf("ha seleccionado %d - %d valor del tablero %d\n", i, j, tablero[i][j]);

			if(tablero[i][j] != POS_VAL){

				gchar *tempo = g_strdup_printf("LUGAR NO VALIDO");
				gtk_label_set_text(GTK_LABEL(label_jugada), tempo);
				g_free(tempo);
				gchar *temp = g_strdup_printf("TURNO DEL JUGADOR 1");
				gtk_label_set_text(GTK_LABEL(label_turno), temp);
				g_free(temp);
				turno = 1;

			}else if(tablero[i][j] == POS_VAL){

				gchar *tempor = g_strdup_printf("LUGAR VALIDO");
				gtk_label_set_text(GTK_LABEL(label_jugada), tempor);
				g_free(tempor);
				gchar *temp = g_strdup_printf("TURNO DEL JUGADOR 2");
				gtk_label_set_text(GTK_LABEL(label_turno), temp);
				g_free(temp);
				accion_juego(i,j,jugador_1,jugador_2);
				turno = 2;
				imprimir_tablero();
				ActualizarTablero();
				gtk_widget_show_all(windowtablero);

			}
			borrar_pv();
		}else{// primero jug2 y luego jug1

			gchar *temp = g_strdup_printf("TURNO DEL JUGADOR 2");
			gtk_label_set_text(GTK_LABEL(label_turno), temp);
			g_free(temp);
			posicion_valida(jugador_2,jugador_1);

			i = (GUINT_FROM_LE(event -> y) / 50); 	//las imagenes son de 50x50pixeles
			j = (GUINT_FROM_LE(event -> x) / 50);
			printf("ha seleccionado %d - %d valor del tablero %d\n", i, j, tablero[i][j]);

			if(tablero[i][j] != POS_VAL){

				gchar *tempo = g_strdup_printf("LUGAR NO VALIDO");
				gtk_label_set_text(GTK_LABEL(label_jugada), tempo);
				g_free(tempo);
				gchar *temp = g_strdup_printf("TURNO DEL JUGADOR 2");
				gtk_label_set_text(GTK_LABEL(label_turno), temp);
				g_free(temp);
				turno = 2;

			}else if(tablero[i][j] == POS_VAL){

				gchar *tempor = g_strdup_printf("LUGAR VALIDO");
				gtk_label_set_text(GTK_LABEL(label_jugada), tempor);
				g_free(tempor);
				gchar *temp = g_strdup_printf("TURNO DEL JUGADOR 1");
				gtk_label_set_text(GTK_LABEL(label_turno), temp);
				g_free(temp);
				accion_juego(i,j,jugador_2,jugador_1);
				turno = 1;
				imprimir_tablero();
				ActualizarTablero();
				gtk_widget_show_all(windowtablero);

			}
			borrar_pv();
		}

	}

	if(opcion_modo == 0){//jug vs cpu
		if(turno == 1){//turno del jug

			gchar *temp = g_strdup_printf("TURNO DEL JUGADOR 1");
			gtk_label_set_text(GTK_LABEL(label_turno), temp);
			g_free(temp);
			posicion_valida(jugador_1,jugador_2);

			i = (GUINT_FROM_LE(event -> y) / 50); 	//las imagenes son de 50x50pixeles
			j = (GUINT_FROM_LE(event -> x) / 50);
			printf("ha seleccionado %d - %d valor del tablero %d\n", i, j, tablero[i][j]);

			if(tablero[i][j] != POS_VAL){

				gchar *tempo = g_strdup_printf("LUGAR NO VALIDO");
				gtk_label_set_text(GTK_LABEL(label_jugada), tempo);
				g_free(tempo);
				gchar *temp = g_strdup_printf("TURNO DEL JUGADOR 1");
				gtk_label_set_text(GTK_LABEL(label_turno), temp);
				g_free(temp);
				turno = 1;

			}else if(tablero[i][j] == POS_VAL){

				gchar *tempor = g_strdup_printf("LUGAR VALIDO");
				gtk_label_set_text(GTK_LABEL(label_jugada), tempor);
				g_free(tempor);
				gchar *temp = g_strdup_printf("TURNO DE LA CPU");
				gtk_label_set_text(GTK_LABEL(label_turno), temp);
				g_free(temp);
				accion_juego(i,j,jugador_1,jugador_2);
				turno = 2;
				imprimir_tablero();
				ActualizarTablero();

			}
			borrar_pv();

		}else if(turno ==2){//turno de la pc
			posicion_valida(jugador_2,jugador_1);
			turno_cpu(jugador_2, jugador_1);
			turno = 1;
			gchar *temp = g_strdup_printf("TURNO DE LA CPU");
			gtk_label_set_text(GTK_LABEL(label_turno), temp);
			g_free(temp);
			imprimir_tablero();
			ActualizarTablero();
			gtk_widget_show_all(windowtablero);
			gtk_widget_show_all(windowtablero);
			gchar *tempo = g_strdup_printf("TURNO DEL JUGADOR 1");
			gtk_label_set_text(GTK_LABEL(label_turno), tempo);
			g_free(tempo);
		}
	}



}

GtkWidget *crear_tablero(){

	GtkWidget *eventbox;
	GtkWidget *tablerogtk;
	int i, j;

	cargar_tablero();

	eventbox = gtk_event_box_new();
	tablerogtk = gtk_grid_new();

	for (i = 0; i < MAX_NUM; i++) {
		for (j = 0; j < MAX_NUM; j++) {
			if((i == 3 && j == 3) || (i == 4 && j == 4)){
				imagenes[i][j] = gtk_image_new_from_file(imagenesVacio[1]);
			}else if((i == 3 && j == 4) || (i == 4 && j == 3)){
				imagenes[i][j] = gtk_image_new_from_file(imagenesVacio[2]);
			}else {
				imagenes[i][j] = gtk_image_new_from_file(imagenesVacio[0]);
			}
			gtk_grid_attach(GTK_GRID(tablerogtk), GTK_WIDGET(imagenes[i][j]), j, i, 1, 1);
		}
	}

	gtk_container_add(GTK_CONTAINER(eventbox), tablerogtk);
	g_signal_connect(eventbox, "button-press-event", G_CALLBACK(tablero_cb), tablerogtk);

	for(i = 0; i < N; i++){
		for(j = 0; j < N; j++){
			tablero[i][j] = VACIO;
		}
	}

	tablero[3][3] = SONIC;
	tablero[4][4] = SONIC;
	tablero[3][4] = EGGMAN;
	tablero[4][3] = EGGMAN;

	return eventbox;
}

 int main (int argc, char *argv[]){

	srand(time(NULL));

	gtk_init (&argc, &argv);

	builder = gtk_builder_new_from_file("REVERSI.glade");

	window1 = GTK_WIDGET(gtk_builder_get_object(builder, "ventanainicio")); //ventanaprincipal
    g_signal_connect (window1, "destroy", G_CALLBACK (gtk_main_quit), NULL);

    label_turno = GTK_WIDGET(gtk_builder_get_object(builder, "label_turno"));
	label_jugada = GTK_WIDGET(gtk_builder_get_object(builder, "label_jugada"));

	windowacercade = GTK_WIDGET(gtk_builder_get_object(builder, "ventanainfo"));//ventana acerca de
	windowconfig = GTK_WIDGET(gtk_builder_get_object(builder, "ventanaconfig"));//ventana de configuracion pre partida
	windowtablero = GTK_WIDGET(gtk_builder_get_object(builder, "ventanatablero"));//ventana de configuracion pre partida
    g_signal_connect (windowtablero, "destroy", G_CALLBACK (gtk_main_quit), NULL);
    windowayuda = GTK_WIDGET(gtk_builder_get_object(builder, "ventanaayuda"));//ventana de configuracion pre partida

    entrynombrejugador = GTK_WIDGET(gtk_builder_get_object(builder, "entrynombrejugador"));

    entrynombrejugador = gtk_builder_get_object(builder,"entrynombrejugador");
	g_signal_connect(entrynombrejugador, "changed", G_CALLBACK (entry_jug), NULL);
    entrynombrejugador1 = gtk_builder_get_object(builder,"entrynombrejugador1");
	g_signal_connect(entrynombrejugador1, "changed", G_CALLBACK (entry_jug1), NULL);

    fixedinicio = GTK_WIDGET(gtk_builder_get_object(builder, "fixedinicio"));//fixed de la ventana principal
    fixedacercade = GTK_WIDGET(gtk_builder_get_object(builder, "fixedinfo"));//fixed de la ventana acerca del juego
    fixedconfig = GTK_WIDGET(gtk_builder_get_object(builder, "fixedconfig"));//fixed de la ventana de configuraciones
    fixedtablero = GTK_WIDGET(gtk_builder_get_object(builder, "fixedtablero"));

	botonadelante = GTK_WIDGET(gtk_builder_get_object(builder, "botonadelante")); //boton para abrir ventana de config
	g_signal_connect(botonadelante, "clicked", G_CALLBACK (botonadelante_clicked_cb), NULL);

	botoninfo = GTK_WIDGET(gtk_builder_get_object(builder, "botonacercade")); //boton para abrir ventana de informacion
	g_signal_connect(botoninfo, "clicked", G_CALLBACK (botoninfo_clicked_cb), NULL);

	botonFininfo = GTK_WIDGET(gtk_builder_get_object(builder, "botonfininfo")); //boton para abrir ventana de informacion
	g_signal_connect(botonFininfo, "clicked", G_CALLBACK (botonFininfo_clicked_cb), NULL);

	botoncerrarayuda = GTK_WIDGET(gtk_builder_get_object(builder, "botoncerrarayuda")); //boton para abrir ventana de informacion
	g_signal_connect(botoncerrarayuda, "clicked", G_CALLBACK (botoncerrarayuda_clicked_cb), NULL);

	botonabrirayuda = GTK_WIDGET(gtk_builder_get_object(builder, "botonayuda")); //boton para abrir ventana de informacion
	g_signal_connect(botonabrirayuda, "clicked", G_CALLBACK (botonabrirayuda_clicked_cb), NULL);

	botonterminarconfig = GTK_WIDGET(gtk_builder_get_object(builder, "botonfinconfig")); //boton para abrir ventana de informacion
	g_signal_connect(botonterminarconfig, "clicked", G_CALLBACK (botonterminarconfig_clicked_cb), NULL);

	toogle_aleatoriocolor = GTK_WIDGET(gtk_builder_get_object(builder, "toogle_aleatoriocolor"));

	toogle_jugvscpu = GTK_WIDGET(gtk_builder_get_object(builder, "toogle_jugvscpu"));

	toogle_jugvsjug = GTK_WIDGET(gtk_builder_get_object(builder, "toogle_jugvsjug"));
	g_signal_connect(toogle_jugvsjug, "toggled", G_CALLBACK (on_toogle_jugvsjug), NULL);

	toogle_sonic= GTK_WIDGET(gtk_builder_get_object(builder, "toogle_sonic"));
	g_signal_connect(toogle_sonic, "toggled", G_CALLBACK (on_toogle_sonic), NULL);

	toogle_empiezajugador= GTK_WIDGET(gtk_builder_get_object(builder, "toogle_empiezajugador"));
	g_signal_connect(toogle_empiezajugador, "toggled", G_CALLBACK (on_toogle_empiezajugador), NULL);

	box_tablero = GTK_WIDGET(gtk_builder_get_object(builder, "box_tablero"));
	gtk_box_pack_start(GTK_BOX(box_tablero), crear_tablero(), TRUE, FALSE, 20);

    gtk_widget_show_all (window1);

    /* start the main loop, and let it rest there until the application is closed */
    gtk_main ();

 }

void ActualizarTablero(){

	int m,n;

	for(m = 0; m < N; m++){
		for(n = 0; n < N; n++){
			if(tablero[m][n] == VACIO || tablero[m][n] == POS_VAL){
				gtk_image_clear(imagenes[m][n]);
				gtk_image_set_from_file(imagenes[m][n], imagenesVacio[0]);
			}
			if(tablero[m][n] == SONIC){
				gtk_image_clear(imagenes[m][n]);
				gtk_image_set_from_file(imagenes[m][n], imagenesVacio[1]);
			}
			if(tablero[m][n] == EGGMAN){
				gtk_image_clear(imagenes[m][n]);
				gtk_image_set_from_file(imagenes[m][n], imagenesVacio[2]);
			}
		}
	}


}

void cargar_tablero(void){	// carga e inicializa el tablero con '0'
	printf("cargar_tablero\n");
 	int i, j;

 	for (i = 0; i < MAX_NUM; i++){
 		for (j = 0; j < MAX_NUM; j++){
 			if ((i == 3 && j == 3) || (i == 4 && j == 4)){
 				tablero[i][j] = SONIC;
 			}else if((i == 4 && j == 3) || (i == 3 && j == 4)){
 				tablero[i][j] = EGGMAN;

 			}else {
 				tablero[i][j] = 0;
 				}

 		}
 	}

 }

void imprimir_tablero(void){				// imprime el tablero
	printf("imprimir_tablero\n");
 	int i, j;

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

void posicion_valida(int jug, int c){		//recibe el "color" de la ficha y revisa en el tablero si se puede jugar
	printf("posicion_valida\n");
	int i, j;
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
 							//gtk_image_clear(imagenes[aux_i][j]);
 							//gtk_image_set_from_file(imagenes[aux_i][j], imagenesVacio[3]);
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
 							//gtk_image_clear(imagenes[aux_i][j]);
 							//gtk_image_set_from_file(imagenes[aux_i][j], imagenesVacio[3]);
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
 							//gtk_image_clear(imagenes[i][aux_j]);
 							//gtk_image_set_from_file(imagenes[i][aux_j], imagenesVacio[3]);
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
							//gtk_image_clear(imagenes[i][aux_j]);
 							//gtk_image_set_from_file(imagenes[i][aux_j], imagenesVacio[3]);
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
							//gtk_image_clear(imagenes[aux_i][aux_j]);
 							//gtk_image_set_from_file(imagenes[aux_i][aux_j], imagenesVacio[3]);
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
							//gtk_image_clear(imagenes[aux_i][aux_j]);
 							//gtk_image_set_from_file(imagenes[aux_i][aux_j], imagenesVacio[3]);
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
							//gtk_image_clear(imagenes[aux_i][aux_j]);
 							//gtk_image_set_from_file(imagenes[aux_i][aux_j], imagenesVacio[3]);
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
							//gtk_image_clear(imagenes[aux_i][aux_j]);
 							//gtk_image_set_from_file(imagenes[aux_i][aux_j], imagenesVacio[3]);
 							break;
 						}
 					}
 				}
 			}
 		}
 }

void borrar_pv(){									//borra las posiciones validas no utilizadas
	printf("borrar_pv\n");
 	int i, j;

 	for(i = 0; i < MAX_NUM; i++){
 		for(j = 0; j < MAX_NUM; j++){
 			if(tablero[i][j] == POS_VAL){
 				tablero[i][j] = VACIO;
 			}
 		}
 	}
 }

void accion_juego(int x, int y, int jug, int c){ 	//con las coordenadas, recorre las 8 direcciones para
													//realizar los cambios de color en las fichas
	int i, j;

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
	while(contador >= 0 && ((aux_x > 0))){

		tablero[aux_x][y] = jug;
		aux_x--;
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
	while(contador >= 0 && ((aux_x < MAX_NUM))){

		tablero[aux_x][y] = jug;
		aux_x++;
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
	while(contador >= 0 && ((aux_y < MAX_NUM))){

		tablero[x][aux_y] = jug;
		aux_y++;
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
	while(contador >= 0 && ((aux_y > 0))){

		tablero[x][aux_y] = jug;
		aux_y--;
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
	while(contador >= 0 && ((aux_x > 0) && (aux_y < MAX_NUM))){

		tablero[aux_x][aux_y] = jug;
		aux_x--;
		aux_y++;
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
	while(contador >= 0 && ((aux_x < MAX_NUM) && (aux_y < MAX_NUM))){

		tablero[aux_x][aux_y] = jug;
		aux_x++;
		aux_y++;
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
	while(contador >= 0 && ((aux_x < MAX_NUM) && (aux_y > 0))){

		tablero[aux_x][aux_y] = jug;
		aux_x++;
		aux_y--;
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
	while(contador >= 0 && ((aux_x > 0) && (aux_y > 0))){

		tablero[aux_x][aux_y] = jug;
		aux_x--;
		aux_y--;
		contador--;
	}


}

/*SECCION DE LA INTELIGENCIA ARTIFICIAL*/

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
	int i, j;

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

