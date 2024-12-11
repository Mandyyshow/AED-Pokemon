#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#define MAX 100

// Nova estrutura de itens
typedef struct
{
    char nome[30], desc[MAX];
    int money;
} itens;

// Estrutura do nó da lista encadeada
typedef struct tp_no
{
    itens info;         // Informação armazenada no nó
    struct tp_no *prox; // Ponteiro para o próximo nó
} loja;

// Função para inicializar a lista (retorna NULL)
loja *inicializa_listase()
{
    return NULL;
}

// Função para verificar se a lista está vazia
int listase_vazia(loja *lista)
{
    return lista == NULL; // Retorna 1 se vazia, 0 caso contrário
}

// Função para alocar um novo nó na lista
loja *aloca_listase()
{
    loja *novo_no = (loja *)malloc(sizeof(loja)); // Alocando memória
    return novo_no;                               // Retorna o novo nó alocado
}

// Função para inserir um item no final da lista
int insere_lista_no_fim(loja **l, itens e)
{
    loja *novo_no = aloca_listase(); // Aloca um novo nó
    if (novo_no == NULL)
        return 0; // Retorna 0 se falhar na alocação

    novo_no->info = e;    // Armazena o item no novo nó
    novo_no->prox = NULL; // O novo nó será o último, então o próximo é NULL

    // Se a lista estiver vazia, o novo nó se torna o primeiro
    if (listase_vazia(*l))
    {
        *l = novo_no;
    }
    else
    {
        loja *atu = *l;
        // Navega até o último nó
        while (atu->prox != NULL)
        {
            atu = atu->prox;
        }
        atu->prox = novo_no; // Link o novo nó ao final da lista
    }
    return 1; // Retorna 1 em caso de sucesso
}

// Função para imprimir os itens da lista
void imprime_listase(loja *lista)
{
    loja *atu = lista;
    int i = 1;
    while (atu != NULL)
    {
        // Imprime os dados do item
        printf("-------------------------------------\n");
        printf("Item : %d\nNome: %s, Descricao: %s\n Preco: %d\n", i, atu->info.nome, atu->info.desc, atu->info.money);
        atu = atu->prox; // Avança para o próximo nó
        i++;
    }
    printf("-------------------------------------\n");
    printf("\n"); // Nova linha ao final
}

// Função para remover um item da lista (comparando por nome)
int remove_listase(loja **lista, char *nome)
{
    loja *ant = NULL;   // Ponteiro para o nó anterior
    loja *atu = *lista; // Ponteiro para o nó atual

    // Navega pela lista procurando o item com o nome fornecido
    while (atu != NULL && strcmp(atu->info.nome, nome) != 0)
    {
        ant = atu;       // Atualiza o nó anterior
        atu = atu->prox; // Avança para o próximo nó
    }

    if (atu == NULL)
        return 0; // Retorna 0 se o item não for encontrado

    // Se o item a ser removido é o primeiro nó
    if (ant == NULL)
    {
        *lista = atu->prox; // O próximo nó se torna o novo primeiro
    }
    else
    {
        ant->prox = atu->prox; // Bypass o nó a ser removido
    }

    free(atu); // Libera a memória do nó removido
    return 1;  // Retorna 1 em caso de sucesso
}

// Função para buscar um item na lista (buscando por nome)
loja *busca_listase(loja *lista, char *nome)
{
    loja *atu = lista;
    // Navega pela lista procurando o item com o nome fornecido
    while (atu != NULL && strcmp(atu->info.nome, nome) != 0)
    {
        atu = atu->prox; // Avança para o próximo nó
    }
    return atu; // Retorna o nó encontrado ou NULL se não for encontrado
}

// Função para contar o número de itens na lista
int tamanho_listase(loja *lista)
{
    int cont = 0; // Contador de itens
    loja *atu = lista;
    // Conta os nós da lista
    while (atu != NULL)
    {
        cont++;
        atu = atu->prox; // Avança para o próximo nó
    }
    return cont; // Retorna o número total de nós
}

// Função para destruir a lista e liberar a memória
void destroi_listase(loja **l)
{
    loja *atu = *l; // Ponteiro para o nó atual
    // Enquanto houver nós na lista
    while (atu != NULL)
    {
        *l = atu->prox; // Avança para o próximo nó
        free(atu);      // Libera a memória do nó atual
        atu = *l;       // Atualiza o ponteiro para o próximo nó
    }
    *l = NULL; // Garante que o ponteiro da lista seja NULL
}

// Funcao para definir 3 itens aleatorios e adiciona-los a lista
int defineItensRandom(loja **l, char *buffer, int *pmoney)
{
    int x;
    itens opcoes[5] = {
        {"Pocao Base de Vida", "Restaura uma pequena quantidade de vida.", 50},
        {"Pocao Forte de Vida", "Restaura uma quantidade maior de vida.", 100},
        {"Pokebola", "Usada para capturar Pokemon selvagens.", 150},
        {"Aumentar Ataque", "Aumenta temporariamente o ataque do Pokemon.", 120},
        {"Aumentar Defesa", "Aumenta temporariamente a defesa do Pokemon.", 120}};

    int indices[3];         // Para armazenar sorteados
    int sorteados[5] = {0}; // para evitar repetição

    // Seleciona 3 índices aleatórios únicos
    for (int i = 0; i < 3; i++)
    {
        int indice;
        do
        {
            indice = rand() % 5; // Gera um índice entre 0 e 4
        } while (sorteados[indice] == 1); // Repete até achar um índice ainda não sorteado
        sorteados[indice] = 1; // Marca o índice como sorteado
        indices[i] = indice;
    }

    // Adiciona os itens sorteados na lista
    for (int i = 0; i < 3; i++)
    {
        insere_lista_no_fim(l, opcoes[indices[i]]);
    }

    imprime_listase(*l);

    int saidai = 0;
    loja *atu = *l;
    // Loop para perguntar sobre a compra dos itens
    do
    {
        printf("Dinhiro atual: %d\n", *pmoney);
        printf("Escolha o item de 0 a 3 (0 para cancelar): ");
        scanf("%d", &x);
        printf("--------------------------------------------------------\n");

        // Valida a escolha do usuário (entre 0 e 3)
        while (x < 0 || x > 3)
        {
            printf("Numero Invalido! Tente novamente (0 a 3): ");
            scanf("%d", &x);
        }
        switch (x)
        {
        case 0:
            printf("Operacao cancelada.\n");
            saidai = 1;
            break;

        case 1:
            if(*pmoney < atu->info.money) {
                printf("Dinheiro insuficiente!\n");
                x=2;
                break;
            }
            printf("Deseja comprar o item %s? Se sim, digite 1; caso contrario, digite 2: ", atu->info.nome);
            scanf("%d", &x);
            
            break;

        case 2:
            atu = atu->prox;
            if(*pmoney < atu->info.money) {
                printf("Dinheiro insuficiente!\n");
                x=2;
                break;
            }
            printf("Deseja comprar o item %s? Se sim, digite 1; caso contrario, digite 2: ", atu->info.nome);
            scanf("%d", &x);
            break;

        case 3:
            atu = atu->prox->prox;
            if(*pmoney < atu->info.money) {
                printf("Dinheiro insuficiente!\n");
                x=2;
                break;
            }
            printf("Deseja comprar o item %s? Se sim, digite 1; caso contrario, digite 2: ", atu->info.nome);
            scanf("%d", &x);
            break;

        default:
            printf("Opcao invalida.\n");
            saidai = 0;
            break;
        }

        if (x == 1)
        {
            *pmoney -= atu->info.money;
            printf("Item %s comprado!\n", atu->info.nome);
            strcpy(buffer, atu->info.nome);                 //passa para a main o item comprado


            saidai = 1;
        }

        else if (x == 2)
        {
            strcpy(buffer, "Nenhum");
            printf("Compra cancelada.\n");
            saidai = 0;
        }

        // Sai do loop apos a compra ou cancelamento
    } while (!saidai);
  destroi_listase(l);
    return 1;
}


  
