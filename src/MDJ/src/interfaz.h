#ifndef INTERFAZ_H
#define INTERFAZ_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h> 
#include <sys/mman.h>
#include <sys/stat.h> 
#include <fcntl.h>
#include "../../sample-socket/socket.h"
#include <commons/config.h>
#include <commons/bitarray.h>
#include <commons/collections/list.h>
#include <sys/file.h>

//uso enum para ser mas claro en el codigo
// noExiste = 0, existe =1
// yaCreado = 0,recienCreado = 1, noCreado = 2
//el caso que sea 2 es para casos de error
 
typedef enum{noExiste,existe };
typedef enum{yaCreado,recienCreado,noCreado};
typedef enum{noBorrado,recienBorrado};

//estructura por si hay que usar hilos
typedef struct {
socket_connection * connection;
char ** args;
}argumentos;

//estructura para manejar los directorios del fs
typedef struct {
t_list *  directorios;
}t_directorios;

//estructura para guardar la informacion del archivo
typedef struct{
int fd;
char * mem_ptro;
char * path;
size_t * size;
t_dictionary * bloque; // diccionario de los bloques que posee ese archivo
int estado;
}t_archivo;

//estructura que define al bloque
//con un vector que acumulas los bytes, el cual es dinamico
//un ptro a la direccion  proximo  bloque
typedef struct {
char * contBloque;
int * ptroProxBloque;
}bloque;

//estructura del metadata 
typedef struct {
size_t tamanio_bloques;
int cantidad_bloques;
char * magic_number;
}t_metadata_filesystem;

typedef struct{
t_bitarray estado_bloques;//  1 ocupado , 0 libre
int * ptroBloque;  
}t_metadata_bitmap;

typedef struct{
int fd;
size_t  tamanio_archivo_enBytes;
int  * bloques;
}t_metadata_filemetadata;


char * directorioMontaje;

// devuelve un true(1) si el archivo existe, u falso(0)  si no existe
void  validarArchivo(socket_connection * ,char**);
//crear el archivo, cada elemento del vector sera una linea del archivo
void crearArchivo(socket_connection *,char **);
//devuelvo la cant de bytes del path(archivo)
size_t   obtenerDatos(socket_connection *,char **);
void guardarDatos(socket_connection *,char * ,off_t  *,size_t * ,char *);
void borrarArchivo(socket_connection *,char *);
int verificarSiExisteArchivo(char * path);
#endif