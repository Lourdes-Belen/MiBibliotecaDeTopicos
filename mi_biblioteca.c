#include "mi_biblioteca.h"

/* ========================= VECTORES ========================= */
int mi_crear_vector(tVector* vec, size_t tam)
{
    vec->maximo = CAPACIDAD;
    vec->vec = malloc(vec->maximo * tam);
    if(!vec->vec)
    {
        printf("Error al reservar memoria");
       return -1;
    }

    vec->cantElem = 0;
    vec->tamElem = tam;
    return 0;
}
void mi_destruir_vector(tVector* vec)
{
    free(vec->vec);
    vec->cantElem = 0;
}
//MI INSERTAR AL FINAL EL VECTOR
int mi_insertar_al_final(tVector* vec, void* info, size_t tam)
{

    if(vec->cantElem == vec->maximo){
        printf("El vector esta lleno\n.");
        //USAR REALLOC AGREGAR!!
        return -1;
    }
    //Posicionarse al final
    void* fin = vec->vec + (vec->cantElem * tam);
    //Inserto al final
    memcpy(fin, info, tam);

    vec->cantElem++;

    return 0;
}
/* ========================= ORDENAMIENTO ========================= */
void* mi_buscar_menor(void* inicio, void* fin, size_t tamElem, Cmp cmp)
{
    void* p = inicio + tamElem;
    void* menor = inicio;
    for(; p < fin; p+=tamElem)
    {
            if(cmp(menor,p)>0){
                menor = p;
            }
    }
    return menor;
}
void mi_ordenar_vector(void* vec, int ce, size_t tamElem, Cmp cmp)
{
  void* inicio = vec;
  void* fin = vec + (ce * tamElem);

  void* menor;
  void* m;

    for(; inicio < fin; inicio+=tamElem)
    {
        menor = inicio;
        m = mi_buscar_menor(inicio,fin,tamElem, cmp);

        if(cmp(m,menor)<0){

        mi_intercambiar(menor, m, tamElem);

        }
    }
}
void mi_intercambiar(void* elem1, void* elem2, size_t tamElem)
{
    void* aux = malloc(tamElem);
        if(!aux)
        {
            printf("Error al reservar memoria");
            return;
        }
    memcpy(aux,elem1,tamElem);
    memcpy(elem1,elem2,tamElem);
    memcpy(elem2,aux,tamElem);

    free(aux);
}
void mi_ordenar_qsort(int* vec, int ce, Cmp cmp)
{
    qsort(vec, ce, sizeof(int), cmp);
}
/* ========================= MATRICES ========================= */
//Saber cuantas filas y columnas tiene el archivo para crear la matriz de tam perfecto
//Se usa antes de crear matriz.
void mi_contar_filas_columnas(const char* arch, int* filas, int* cols)
{
    if(!arch || !filas || !cols) return;
    FILE* pf = fopen(arch,"rt");
    if(pf == NULL){
        printf("Error al abrir el archivo.\n");
        return;
    }

    char linea[MAX_LINEA];
    char *p;

    if(fgets(linea,MAX_LINEA,pf)!= NULL){
        int cantPipes = 0;

        for(p = linea; *p != '\0'; p++)
        {
            if( *p == '|' )
            {
                cantPipes++;
            }
        }
    *cols = cantPipes + 1;

    }
    *filas = 1;

    while(fgets(linea,MAX_LINEA,pf)!= NULL) /* Lee hasta MAX_LINEA + '\0' */
    {
        (*filas)++;
    }

    fclose(pf);
}
void** mi_crear_matriz_dinamica(int filas, int cols, size_t tamElem)
{
    void** matriz;
    int i;
    matriz = malloc(filas * sizeof(void*));
    if(!matriz){
        return NULL;
    }

    //Reservar cada fila
    for(i = 0; i < filas; i++)
    {
        matriz[i] = malloc(cols * tamElem);
        if(!matriz[i]){
            mi_liberar_matriz(matriz,i);
            return NULL;
        }
    }

    return matriz;
}
void mi_liberar_matriz(void** matriz, int filas)
{
    if(!matriz)
    {
        return;
    }

    for(int i = 0; i< filas; i++)
    {
        free(matriz[i]);
    }

    free(matriz);
}
int mi_cargar_matriz(const char* arch, float** matriz, int filas, int cols)
{
    FILE* pf = fopen(arch,"rt");
    char linea[MAX_LINEA];
    int i;
        if(!pf)
        {
            printf("No se pudo abrir el archivo.");
            return -1;
        }

    for(i = 0; i < filas; i++){
        if(fgets(linea, MAX_LINEA,pf)== NULL){
            fclose(pf);
            return -1;
        }

    //Trozar y cargar en matriz
    mi_trozar_linea_matriz(linea,matriz[i],cols);

    }
    fclose(pf);
    return 0;
}
void mi_trozar_linea_matriz(const char* linea, float* fila, int cols)
{
    const char* p = linea;
    int j;
    char buffer[50];
    int k;

        for(j = 0;j < cols; j++)
        {
            k = 0;
                while((*p != '|')&&(*p != '\n')&&(*p != '\0'))
                {
                    buffer[k++]= *p++;
                }
            buffer[k] = '\0';       //terminar buffer
            fila[j] = atof(buffer);// convertir y guardar

            if(*p == '|')
            {
                p++;
            }
        }

}
int mi_guardar_matriz(const char* archDes, float** matriz, int filas, int cols)
{
    FILE* pf = fopen(archDes,"wt");
    if(!pf)
    {
        printf("Error al abrir escribir el archivo.");
        return -1;
    }

    int i,j;

    for(i = 0;i < filas; i++)
    {
        for(j=0; j< cols; j++)
        {
            fprintf(pf,"%g",matriz[i][j]); //escribir valor

            if(j< cols-1){ //Si no es la ultima columna
                fprintf(pf,"|");
            }

        }
    fprintf(pf, "\n");
    }


    fclose(pf);
    return 0;
}
/* ========================= FECHAS ========================= */
int mi_cmp_fechas(const tFecha* f1, const tFecha* f2)
{
    if(f1->anio != f2->anio)
    {
        return f1->anio - f2->anio;
    }

    if(f1->mes != f2->mes)
    {
        return f1->mes - f2->mes;
    }

    return f1->dia - f2->dia;
}
bool mi_es_fecha_valida(const tFecha* f)
{
    if(!f) return false;
    if((f->anio >= 1601) && (f->mes >= 1 && f->mes <= 12) &&
       (f->dia >= 1 && f->dia <= mi_cant_dias_mes(f->mes, f->anio))) {
        return true;
    }
    return false;
}
int mi_cant_dias_mes(int mes, int anio)
{
    int diasMes[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
    if(mes == 2 && ES_BISIESTO(anio))
    {
    return 29;

    }
    if(mes >=1 && mes <=12)
    {
        return diasMes[mes];
    }
    return 0;
}
tFecha mi_sumar_dias_a_fecha(const tFecha* f, unsigned dias)
{
    tFecha resultado = *f;
    while(dias> mi_cant_dias_mes(resultado.mes,resultado.anio))
    {
        dias -= mi_cant_dias_mes(resultado.mes,resultado.anio);
        resultado.mes++;

        if( resultado.mes > 12 )
        {
            resultado.mes = 1;
            resultado.anio++;
        }
    }
    resultado.dia += dias;


    return resultado;
}
/* ========================= ARCHIVOS BINARIOS ========================= */
int mi_crear_lote_arch_bin(const char* nombreArchivo)
{
    if(!nombreArchivo) return 0;
    FILE* pf = fopen(nombreArchivo,"wb");
    if(!pf){
        printf("Error al crear archivo.\n");
        return 0;
    }

    tEstructura vecEstructura[] =
    {
        {1,"Karen",1500.00f},
        {2,"Agustin",2500.00f},
        {3,"Christian",5500.00f},
        {4,"Lourdes",3000.00f}
    };
    size_t cant = sizeof(vecEstructura)/sizeof(vecEstructura[0]);

    if(fwrite(vecEstructura, sizeof(tEstructura), cant, pf) != cant)
    {
        printf("Error al escribir en el archivo.\n");
        fclose(pf);
        return 0;
    }

    fclose(pf);
    return 1;
}
void mi_mostrar_arch_bin(const char* nombreArchivo)
{
    if(!nombreArchivo) return;
    FILE* f = fopen(nombreArchivo, "rb");
    if(!f) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    tEstructura estructura;
    printf("Contenido del archivo '%s':\n", nombreArchivo);
    printf("------------------------------------------\n");

    while(fread(&estructura, sizeof(tEstructura), 1, f) == 1) {
        printf("Codigo: %d\n", estructura.codigo);
        printf("Descripcion: %s\n", estructura.descripcion);
        printf("Precio: %.2f\n", estructura.precio);
        printf("------------------------------------------\n");
    }

    fclose(f);
}
/* ========================= ARCHIVOS TXT ========================= */
int mi_crear_lote_arch_txt(const char* nombreArchivo)
{
    FILE* f = fopen(nombreArchivo, "wt");
    if(!f)
    {
        printf("Error al crear el archivo de texto.\n");
        return 0;
    }

    fprintf(f, "1;Mouse;1500.50\n");
    fprintf(f, "2;Teclado;2500.00\n");
    fprintf(f, "3;Monitor;55000.99\n");
    fprintf(f, "4;Pendrive;3000.75\n");
    fprintf(f, "5;Auriculares;7200.00\n");

    fclose(f);
    printf("Archivo de texto '%s' creado correctamente.\n", nombreArchivo);
    return 1;
}

void mi_mostrar_arch_txt(const char* nombreArchivo)
{
    FILE* f = fopen(nombreArchivo, "rt");
    if(!f)
    {
        printf("Error al abrir el archivo para lectura.\n");
        return;
    }

    char linea[100];
    printf("\nContenido del archivo '%s':\n", nombreArchivo);
    printf("----------------------------------------\n");

    while(fgets(linea, sizeof(linea), f))
        printf("%s", linea);

    fclose(f);
    printf("----------------------------------------\n");

}
/* ========================= CADENAS ORDENAR Y DESOFUSCAR ========================= */
char* mi_desofuscar_linea(char* linea){

    ///1- Ordenar letras de cada palabra.
    mi_ordenar_letras(linea);
        //2- Convertir cada letra en su correspondiente letra
        //3- Retornar linea ordenada y convertida

    return linea;
}
char* mi_ordenar_letras(char* linea)
{
    char* p = linea;
    char* fin;
    char* inicio;

    while(*p != '\0')
    {
        ///1-Buscar inicio de palabra
        inicio = mi_buscar_inicio_palabra(p);

        ///2-Buscar final de palabra
        fin = mi_buscar_final_palabra(inicio);

        ///3-Intercambiar
        mi_ordenar_palabra(inicio,fin);
        p = fin + 1;
    }

    return linea;
}
char* mi_buscar_inicio_palabra(char* p)
{
    //while(*p == ' ')
   while(!mi_es_letra(*p) && (*p != '\0'))
   {
        p++;
    }

    return p;
}
char* mi_buscar_final_palabra(char* q)
{
    while(mi_es_letra(*q)&&(*q != '\0'))
    {
        mi_conversion_letras(q);
        q++;
    }
    return q - 1;
}
void mi_intercambiar_letras(char* ini, char* fin)
{
    char aux = *ini;
         *ini = *fin;
         *fin = aux;
}
void mi_ordenar_palabra(char* ini,char* fin)
{
    while(ini < fin)
    {
        mi_intercambiar_letras(ini,fin);
        ini++;
        fin--;
    }
}
//Ejemplo de ejercicio de clase
char* mi_conversion_letras(char* letra)
{
    switch(*letra)
    {
    case 'a': *letra = 'f'; break;

    case 'b': *letra = 'e'; break;

    case 'c': *letra = 'd'; break;

    case 'd': *letra = 'c'; break;

    case 'e': *letra = 'b'; break;

    case 'f': *letra = 'a'; break;

    }

    return letra;
}
/* ========================= STRING.H ========================= */
String* mi_string_create(const char* str)
{
    const char* plectura = str;
    const char* pEscritura = str;
    int contarCaracter = 0;

    // Contar caracteres
    while (*plectura != '\0')
    {
        contarCaracter++;
        plectura++;
    }

    // Reservar memoria para la estructura
    String* estructura = malloc(sizeof(String));
    if (!estructura)
    {
        printf("Error al reservar memoria para la estructura.\n");
        return NULL;
    }

    // Reservar memoria para la cadena
    estructura->cadena = malloc(contarCaracter + 1);
    if (!estructura->cadena)
    {
        printf("Error al reservar memoria para la cadena.\n");
        free(estructura);
        return NULL;
    }

    // Copiar caracteres manualmente
    char* strDestino = estructura->cadena;
    while (*pEscritura != '\0')
    {
        *strDestino = *pEscritura;
        pEscritura++;
        strDestino++;
    }
    *strDestino = '\0';

    // Asigno valores
    estructura->longitud = contarCaracter;
    estructura->cmax = contarCaracter + (contarCaracter / 2);

    return estructura;
}

void mi_string_destroy(String* s)
{
    free(s->cadena);
    free(s);
}

const char* mi_string_c_str(const String* s)
{
    const char* puntero = s->cadena;
    return puntero;
}

String* mi_string_cconcat(String* self, const char* other)
{
    // 1- Calcular longitud de la palabra 2 (other)
    int longPal2 = 0;
    const char* plecturaPal2 = other;
    while (*plecturaPal2 != '\0')
    {
        plecturaPal2++;
        longPal2++;
    }

    // 2- Calcular longitud total de ambas
    size_t total = self->longitud + longPal2;

    // 3- Redimensionar la cadena recibida
    char* nueva = realloc(self->cadena, total + 1);
    if (!nueva)
    {
        printf("Error al reservar memoria.\n");
        return NULL;
    }
    self->cadena = nueva;

    // 4- Copiar la segunda cadena al final
    char* dest = self->cadena + self->longitud; // se posiciona al final de la palabra1
    const char* pePal2 = other;

    while (*pePal2 != '\0')
    {
        *dest = *pePal2;
        dest++;
        pePal2++;
    }
    *dest = '\0';

    self->longitud = total;
    self->cmax = total + (total * 0.5);

    return self;
}

String* mi_string_toupper(String* self)
{
    char* p = self->cadena;

    while (*p != '\0')
    {
        if (*p >= 'a' && *p <= 'z')
        {
            *p = *p - 32;
        }
        p++;
    }

    return self;
}

int mi_string_ccmp(const String* s1, const char* other)
{
    char* p1 = s1->cadena;
    const char* p2 = other;

    while (*p1 && *p2 && *p1 == *p2)
    {
        p1++;
        p2++;
    }
    return *p1 - *p2;
}

int mi_string_tofile(String* self, FILE* pf)
{
    pf = fopen("archivo.txt", "wt");

    if(!pf)
    {
        printf("Error al escribir el archivo.\n");
        return -1;
    }

    fprintf(pf, "%s\n", self->cadena);

    fclose(pf);

    return 0;
}
