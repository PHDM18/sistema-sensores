#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

long gerar_timestamp_aleatorio(time_t inicio, time_t fim) {
    return inicio + rand() % (fim - inicio + 1);
}

int main() {
    srand(time(NULL));

    FILE *arquivo = fopen("leituras.txt", "w");

    char *sensores[] = {"temp", "pressao", "luz", "estado"};
    char *tipos[] = {"int", "float", "bool", "str"};
    int num_sensores = 4;

    struct tm inicio = {0}, fim = {0};
    inicio.tm_year = 2023 - 1900;
    inicio.tm_mon = 0;
    inicio.tm_mday = 1;
    fim.tm_year = 2023 - 1900;
    fim.tm_mon = 11;
    fim.tm_mday = 31;

    time_t t_inicio = mktime(&inicio);
    time_t t_fim = mktime(&fim);

    for (int i = 0; i < num_sensores; i++) {
        for (int j = 0; j < 2000; j++) {
            long ts = gerar_timestamp_aleatorio(t_inicio, t_fim);
            if (strcmp(tipos[i], "int") == 0)
                fprintf(arquivo, "%ld %s %d
", ts, sensores[i], rand() % 100);
            else if (strcmp(tipos[i], "float") == 0)
                fprintf(arquivo, "%ld %s %.2f
", ts, sensores[i], (float)(rand() % 1000) / 10);
            else if (strcmp(tipos[i], "bool") == 0)
                fprintf(arquivo, "%ld %s %s
", ts, sensores[i], rand() % 2 ? "true" : "false");
            else
                fprintf(arquivo, "%ld %s codigo%04d
", ts, sensores[i], rand() % 10000);
        }
    }

    fclose(arquivo);
    printf("Arquivo de teste 'leituras.txt' gerado com sucesso!
");
    return 0;
}
