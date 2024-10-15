#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nombre[30];
    int edad;
    char sexo;
    float altura;
    double peso;
} PACIENTE;

// Función para leer los datos del paciente desde el usuario
void leerDatosPaciente(void *datos) {
    PACIENTE *paciente = (PACIENTE *)datos;
    printf("Escriba datos del paciente:\n");
    printf("Nombre: ");
    scanf("%s", paciente->nombre);
    printf("Edad: ");
    scanf("%d", &paciente->edad);
    printf("Sexo (M/F): ");
    scanf(" %c", &paciente->sexo);
    printf("Altura (en metros): ");
    scanf("%f", &paciente->altura);
    printf("Peso (en kg): ");
    scanf("%lf", &paciente->peso);
}

// Función para guardar los datos del paciente en un archivo de texto
void guardarPacienteEnArchivo(const char *nombreArchivo, void *datos, long tamBloque) {
    FILE *archivo = fopen(nombreArchivo, "a");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    fwrite(datos, tamBloque, 1, archivo);
    fclose(archivo);
}

// Función para imprimir los datos de un paciente
void imprimirPaciente(void *datos) {
    PACIENTE *paciente = (PACIENTE *)datos;
    printf("Nombre: %s\n", paciente->nombre);
    printf("Edad: %d\n", paciente->edad);
    printf("Sexo: %c\n", paciente->sexo);
    printf("Altura: %.2f\n", paciente->altura);
    printf("Peso: %.2f\n", paciente->peso);
}

// Función para imprimir todos los pacientes desde el archivo
void imprimirTodosPacientes(const char *nombreArchivo, long tamBloque) {
    FILE *archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo para lectura.\n");
        return;
    }

    void *datos = malloc(tamBloque);  // Reservar memoria para leer cada paciente
    if (datos == NULL) {
        printf("Error al asignar memoria.\n");
        fclose(archivo);
        return;
    }

    printf("\n--- Lista de Pacientes ---\n");
    while (fread(datos, tamBloque, 1, archivo)) {
        imprimirPaciente(datos);
        printf("\n");
    }

    free(datos);
    fclose(archivo);
}

// Función para imprimir un paciente específico usando fseek
void imprimirPacientePorIndice(const char *nombreArchivo, int indice, long tamBloque) {
    FILE *archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo para lectura.\n");
        return;
    }

    void *datos = malloc(tamBloque);  // Reservar memoria para leer los datos
    if (datos == NULL) {
        printf("Error al asignar memoria.\n");
        fclose(archivo);
        return;
    }

    long desplazamiento = indice * tamBloque;  // Calculamos el desplazamiento
    if (fseek(archivo, desplazamiento, SEEK_SET) == 0) {
        if (fread(datos, tamBloque, 1, archivo) == 1) {
            imprimirPaciente(datos);  // Imprimir los datos del paciente
        } else {
            printf("No se pudo leer el paciente en la posición %d.\n", indice);
        }
    } else {
        printf("Error al buscar la posición en el archivo.\n");
    }

    free(datos);
    fclose(archivo);
}

int main() {
    const long tamBloque = sizeof(char) * 30 + sizeof(int) + sizeof(char) + sizeof(float) + sizeof(double);  // Tamaño total del bloque
    void *datos = malloc(tamBloque);  // Puntero genérico para los datos del paciente
    int opcion, indice;
    const char *nombreArchivo = "pacientes.txt";

    if (datos == NULL) {
        printf("Error al asignar memoria para los datos del paciente.\n");
        return 1;
    }

    do {
        printf("\nMenú:\n");
        printf("1. Agregar paciente\n");
        printf("2. Imprimir todos los pacientes (desde archivo)\n");
        printf("3. Imprimir paciente por índice (usando fseek)\n");
        printf("4. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                leerDatosPaciente(datos);  // Leer los datos del nuevo paciente
                guardarPacienteEnArchivo(nombreArchivo, datos, tamBloque);  // Guardar en el archivo
                printf("Paciente agregado y guardado en archivo.\n");
                break;

            case 2:
                imprimirTodosPacientes(nombreArchivo, tamBloque);  // Imprimir todos los pacientes
                break;

            case 3:
                printf("Ingrese el índice del paciente que desea imprimir: ");
                scanf("%d", &indice);
                imprimirPacientePorIndice(nombreArchivo, indice, tamBloque);  // Imprimir el paciente en el índice dado
                break;

            case 4:
                printf("Saliendo...\n");
                break;

            default:
                printf("Opción no válida. Intente de nuevo.\n");
        }

    } while (opcion != 4);

    free(datos);  // Liberar la memoria
    return 0;
}
