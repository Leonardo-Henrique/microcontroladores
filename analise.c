// analise_picos.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_AMOSTRAS 1000
#define TAMANHO_JANELA 10

float mediaMovel(float buffer[], int tamanho) {
    float soma = 0.0;
    for (int i = 0; i < tamanho; i++) {
        soma += buffer[i];
    }
    return soma / tamanho;
}

int main() {
    char linha[64];
    float corrente, tensao;
    float bufferCorrente[TAMANHO_JANELA] = {0};
    int idx = 0;
    int count = 0;
    
    printf("Detectando picos em leitura serial de corrente...
");
    while (fgets(linha, sizeof(linha), stdin) != NULL && count < MAX_AMOSTRAS) {
        sscanf(linha, "%f,%f", &corrente, &tensao);
        bufferCorrente[idx % TAMANHO_JANELA] = corrente;
        idx++;
        count++;

        if (count >= TAMANHO_JANELA) {
            float media = mediaMovel(bufferCorrente, TAMANHO_JANELA);
            float limiar = media * 1.5; // 50% acima da média
            if (corrente > limiar) {
                printf("Pico detectado: Corrente = %.2f A, Limiar = %.2f A (amostra %d)
", corrente, limiar, count);
            }
        }
    }
    return 0;
}