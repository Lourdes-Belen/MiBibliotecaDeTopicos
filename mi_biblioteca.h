#ifndef MI_BIBLIOTECA_H_INCLUDED
#define MI_BIBLIOTECA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define ES_BISIESTO(anio) ((anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0))
#define mi_es_letra(c) (((c) >= 'A' && (c) <= 'Z') || ((c) >= 'a' && (c) <= 'z'))
#define MAX_LINEA 1024
#define MAXLINE 1024
#define CAPACIDAD 20

///IMPLEMENTACIONES DE LA CURSADA DE TOPICOS

/* VECTORES - GENERICOS - MEMORIA DINAMICA */
typedef struct
{
    void* vec;
    unsigned cantElem;
    size_t tamElem;
    size_t maximo;

}tVector;

int mi_crear_vector(tVector* vec, size_t tam);
void mi_destruir_vector(tVector* vec);
int mi_insertar_al_final(tVector* vec, void* info, size_t tam);
//agregar un mostrar generico.

/* ORDENAMIENTO - GENERICO */
typedef int (*Cmp)(const void*, const void*); //Para todos los CMP luego declaro los cmp para cada tipo
void* mi_buscar_menor(void* inicio, void* fin, size_t tamElem, Cmp cmp);
void mi_ordenar_vector(void* vec, int ce, size_t tamElem, Cmp cmp);
void mi_intercambiar(void* elem1, void* elem2, size_t tamElem);
/*ORDENAR CON QSORT*/
typedef int (*Cmp)(const void*, const void*); //Se pasa para ordenar por campo
void mi_ordenar_qsort(int* vec, int ce, Cmp cmp);
//FALTA AGREGAR COMO SE USA QSORT

/* MATRICES - GENERICOS - MEMORIA DINAMICA */
void** mi_crear_matriz_dinamica(int filas, int cols, size_t tamElem);
void mi_liberar_matriz(void** matriz, int filas);
void mi_contar_filas_columnas(const char* arch, int* filas, int* cols);
int mi_cargar_matriz(const char* arch, float** matriz, int filas, int cols);
void mi_trozar_linea_matriz(const char* linea, float* fila, int cols);
int mi_guardar_matriz(const char* archDes, float** matriz, int filas, int cols);
//Agregar un mostrar generico

/* TDA - FECHA */
typedef struct
{
	int dia;
	int mes;
	int anio;
}tFecha;

int mi_cant_dias_mes(int mes, int anio);
bool mi_es_fecha_valida(const tFecha* f);
tFecha mi_sumar_dias_a_fecha(const tFecha* f, unsigned dias);
int mi_cmp_fechas(const tFecha* f1, const tFecha* f2);

///ARCHIVOS BINARIOS - LEER - ESCRIBIR - ACTUALIZAR REMOVE RENAME MEMMOVE MEMCPY
///ARCHIVOS DE TEXTO
//CREAR LOTE BINARIO
/* EJEMPLO ESTRUCTURA PARA ARCHIVOS BINARIOS */
typedef struct{
    int codigo;
    char descripcion[30];
    float precio;
} tEstructura;

int mi_crear_lote_arch_bin(const char* nombreArchivo);
void mi_mostrar_arch_bin(const char* nombreArchivo);

//CREAR LOTE TXT
/* EJEMPLO ESTRUCTURA PARA ARCHIVOS TXT */
int mi_crear_lote_arch_txt(const char* nombreArchivo);
void mi_mostrar_arch_txt(const char* nombreArchivo);
//Tener en cuenta el trozado.

/* MANEJO DE CADENAS */
char* mi_desofuscar_linea(char* linea);
char* mi_ordenar_letras(char* linea);
char* mi_buscar_inicio_palabra(char* p);
char* mi_buscar_final_palabra(char* q);
void mi_intercambiar_letras(char* ini, char* fin);
void mi_ordenar_palabra(char* ini,char* fin);
char* mi_conversion_letras(char* letra);

/* MANEJO DE STRING.H */
typedef struct sstring {
    char* cadena;
    size_t longitud;
    size_t cmax;
} String;

String* mi_string_create(const char* str);
const char* mi_string_c_str(const String* s);
String* mi_string_cconcat(String* self, const char* other);
String* mi_string_toupper(String* self);
void mi_string_destroy(String* s);
int mi_string_ccmp(const String* s1, const char* other);
int mi_string_tofile(String* self, FILE* ostream);


#endif // MI_BIBLIOTECA_H_INCLUDED
