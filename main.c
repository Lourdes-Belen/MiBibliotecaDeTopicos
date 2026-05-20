#include <stdio.h>
#include "mi_biblioteca.h"

/*EJEMPLO DE CMP PARA QSORT*/
/*int compararEnteros(const void* a, const void* b) {
    int x = *(int*)a;
    int y = *(int*)b;
    return x - y; // Si querés orden descendente: return y - x;
}*/

int main()
{
    puts("*=== Biblioteca de Lu de la materia Topicos de Programacion ===*\n");

///========= LOTE DE ARCHIVO BIN ========= ///
//    const char* lotebin = "lote.bin";
//    if(mi_crear_lote_arch_bin(lotebin))
//        mi_mostrar_arch_bin(lotebin);
//    else
//        printf("No se pudo crear el lote binario.\n");

///========= LOTE ARCHIVO TXT ========= ///
//    const char* lotetxt = "lote.txt";
//    if(mi_crear_lote_arch_txt(lotetxt))
//        mi_mostrar_arch_txt(lotetxt);

///========= EJEMPLO DE RENAME ========= ///
/*    if (rename("archivo.txt", "nuevo_nombre.txt") == 0)
        printf("Archivo renombrado correctamente.\n");
    else
        printf("Error al renombrar el archivo.\n");
*/

///========= EJEMPLO DE REMOVE ========= ///
/*    if (remove("archivo.txt") == 0)
        printf("Archivo eliminado correctamente.\n");
    else
        printf("Error al eliminar el archivo.\n");
 */

///========= EJEMPLO DE REWIND ========= ///
//POSICIONA EL PUNTERO AL INICIO DEL ARCHIVO
        ///rewind(pf);

///========= EJEMPLO DE QSORT ========= ///
//    int v[] = {5, 1, 9, 3, 2};
//    int n = sizeof(v) / sizeof(v[0]);
//    mi_ordenar_qsort(v, n, compararEnteros);
//
//    for (int i = 0; i < n; i++)
//    {
//        printf("%d ", v[i]);
//    }

///========= ARGUMENTOS A MAIN EJEMPLO ========= ///
 ///argv: es un vector de cadenas que contiene los argumentos
 /// que le pasás al programa desde la línea de comandos.
/*int main(int argc, char *argv[])
{
    printf("Hola esta es mi biblioteca c:!\n");

    if (argc != 2)  // se espera 1 argumento además del nombre del programa
    {
        printf("Uso: %s <nombre_archivo>\n", argv[0]);
        return 1; // termina con error
    }

    return 0;
}*/



   return 0;
}
