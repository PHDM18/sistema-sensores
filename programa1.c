#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 128
#define MAX_SENSORES 100

typedef struct {
    char id[20];
    char tipo[10];
    FILE *arquivo;
    char nome_arquivo[30];
} Sensor;

int comparar_timestamp(const void *a, const void *b) {
    long ta = atol(*(char **)a);
    long tb = atol(*(char **)b);
    return (ta > tb) - (ta < tb);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Uso: %s <arquivo_entrada>
", argv[0]);
        return 1;
    }

    FILE *entrada = fopen(argv[1], "r");
    if (!entrada) {
        perror("Erro ao abrir arquivo de entrada");
        return 1;
    }

    Sensor sensores[MAX_SENSORES];
    int total_sensores = 0;
    char linha[MAX_LINE];

    while (fgets(linha, sizeof(linha), entrada)) {
        char *timestamp = strtok(linha, " ");
        char *id = strtok(NULL, " ");
        char *valor = strtok(NULL, "
");

        int encontrado = 0;
        for (int i = 0; i < total_sensores; i++) {
            if (strcmp(sensores[i].id, id) == 0) {
                encontrado = 1;
                fprintf(sensores[i].arquivo, "%s %s %s
", timestamp, id, valor);
                break;
            }
        }

        if (!encontrado) {
            strcpy(sensores[total_sensores].id, id);
            sprintf(sensores[total_sensores].nome_arquivo, "%s.txt", id);
            sensores[total_sensores].arquivo = fopen(sensores[total_sensores].nome_arquivo, "w");
            fprintf(sensores[total_sensores].arquivo, "%s %s %s
", timestamp, id, valor);
            total_sensores++;
        }
    }

    for (int i = 0; i < total_sensores; i++) {
        fclose(sensores[i].arquivo);
    }

    fclose(entrada);
    printf("Organização concluída. Arquivos gerados por sensor.
");
    return 0;
}
