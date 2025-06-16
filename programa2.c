#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    long timestamp;
    char id[20];
    char valor[32];
} Leitura;

long converter_data_para_timestamp(int ano, int mes, int dia, int hora, int min, int seg) {
    struct tm t;
    t.tm_year = ano - 1900;
    t.tm_mon = mes - 1;
    t.tm_mday = dia;
    t.tm_hour = hora;
    t.tm_min = min;
    t.tm_sec = seg;
    return mktime(&t);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Uso: %s <id_sensor> <timestamp>
", argv[0]);
        return 1;
    }

    char nome_arquivo[32];
    sprintf(nome_arquivo, "%s.txt", argv[1]);

    long alvo = atol(argv[2]);

    FILE *arquivo = fopen(nome_arquivo, "r");
    if (!arquivo) {
        perror("Erro ao abrir arquivo do sensor");
        return 1;
    }

    Leitura leituras[2000];
    int total = 0;
    while (fscanf(arquivo, "%ld %s %s", &leituras[total].timestamp, leituras[total].id, leituras[total].valor) == 3) {
        total++;
    }

    int esq = 0, dir = total - 1, melhor = -1;
    while (esq <= dir) {
        int meio = (esq + dir) / 2;
        if (leituras[meio].timestamp == alvo) {
            melhor = meio;
            break;
        } else if (leituras[meio].timestamp < alvo) {
            esq = meio + 1;
        } else {
            dir = meio - 1;
        }
    }

    if (melhor == -1) {
        melhor = (esq < total && (dir < 0 || abs(leituras[esq].timestamp - alvo) < abs(leituras[dir].timestamp - alvo)))
                 ? esq : dir;
    }

    printf("Leitura mais próxima: %ld %s %s
", leituras[melhor].timestamp, leituras[melhor].id, leituras[melhor].valor);
    fclose(arquivo);
    return 0;
}
