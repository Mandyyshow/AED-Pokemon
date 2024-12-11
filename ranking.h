#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_PLAYERS 100
#define MAX 100

typedef struct {
    char nome[MAX];
    int pontuacao;
} jogador;


void salvar_ranking(const char *nome, int pontuacao) {
    FILE *arquivo = fopen("ranking.txt", "a");
    if(arquivo == NULL) {
        printf("Erro ao abrir arquivo de ranking.\n");
        return;
    }
    fprintf(arquivo, "%s %d\n", nome, pontuacao);
    fclose(arquivo);
}


void exibir_ranking() {
    FILE *arquivo = fopen("ranking.txt", "r");
    if(arquivo==NULL) {
        printf("Erro ao abrir arquivo de ranking.\n");
        return;
    }

    jogador jogadores[MAX_PLAYERS];
    int count = 0;


    while(fscanf(arquivo, "%s %d", jogadores[count].nome, &jogadores[count].pontuacao) == 2) {
        
        count ++;
    }
    fclose(arquivo);

    //Ordena o ranking em ordem decrescente de pontuação
    for(int i=0;i<count-1;i++){
        for(int j=i+1;j<count;j++){
            if(jogadores[i].pontuacao < jogadores[j].pontuacao) {
                jogador temp = jogadores[i];
                jogadores[i] = jogadores[j];
                jogadores[j] = temp;
            }
        }
    }

    //Exibe o ranking
    printf("\n--- Ranking --- \n");
    for(int i=0;i<count;i++) {
        printf("%d. %s - %d pontos\n", i+1, jogadores[i].nome, jogadores[i].pontuacao);
        if(count>=9){
            break;
        }
    }
    printf("--------------------\n");
}
