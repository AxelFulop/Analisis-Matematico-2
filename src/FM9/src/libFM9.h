#include <stdio.h>
#include <stdlib.h>
#include <commons/log.h>
#include <commons/config.h>
#include <commons/string.h>
#include <commons/collections/dictionary.h>
#include <commons/collections/list.h>
#include <pthread.h>
#include "socket.h"

//ESTRUCTURAS
typedef struct {
	int puerto;
	char* modo;
	int tamanio;
	int maximoLinea;
	int tamanioPagina;
} t_config_FM9;

typedef struct {
	int pid;
	//char* nombreArchivo;
	int base;
	int limite;
} t_tabla_segmentos;

typedef struct {
	int pagina;
	int PID; //id del GDT 
	int marco;
	bool libre;
	int tamanioOcupado;
} t_PaginasInvertidas;

typedef struct{
	int idGDT;
	char* nombre;
	int pagina;
	int desplazamiento;
	int segmento;
} archivo;

typedef struct{
	int pagina;
	int desplazamiento;
	bool cargaOK;
}retornoCargaTPI;

//VARIABLES
t_log* logger;
t_config_FM9* datosConfigFM9;
t_dictionary * callableRemoteFunctions;
pthread_mutex_t mx_main;
int socketDAM;

char* memoria;//void* memoria;

t_list* lista_tabla_segmentos;
t_list* tabla_paginasInvertidas;

t_list* lista_archivos;

//FUNCIONES

//CallableRemoteFunctions
void solicitudCargaArchivo(socket_connection*, char**);
void actualizarDatosDTB(socket_connection*, char**);
void cerrarArchivoDelDTB(socket_connection*, char**);
void obtenerDatos(socket_connection* connection, char** args);
//LOGS
void configure_logger();
void close_logger();

//SOCKETS
void identificarProceso(socket_connection * connection ,char** args);
void disconnect(socket_connection*);

//SEGMENTACION PURA
void inicializarMemoriaConSegmentacion();
int devolverPosicionNuevoSegmento(int);

//TABLA DE PAGINAS INVERTIDAS
void inicializarMemoriaConPaginacionInvertida();
void setearNumerosMarcos(int );
retornoCargaTPI cargarArchivoTPI( char*arch, int idGDT);

//CONFIG
t_config_FM9* read_and_log_config(char*);

bool ordenarTablaSegmentosDeMenorBaseAMayorBase(t_tabla_segmentos*, t_tabla_segmentos*);
bool buscarSegmento(t_tabla_segmentos*, int*, int*);

int cantidadDeLineas(char* datos);
void guardarDatosPorLinea(char* datos, int pos);

