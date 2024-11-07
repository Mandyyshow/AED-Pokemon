#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "fila.h"
#include "pilhaSTR.h"
#define MAX 100
#define MAXt 5

//struct de uma habilidade
typedef struct{
char nome[MAX];
char tipo[MAX];
int dano;
int precisao;
}tp_habilidade;
// estrutura de um pokemon
typedef struct{
char nome[MAX];
int vida;
int nivel;
tp_habilidade habilidade1;
tp_habilidade habilidade2;
tp_habilidade habilidade3;
tp_habilidade habilidade4;
int defesa;
int ataque;
int velocidade;
int vidamax;
char tipo[MAX];
}pokemon;
// estrutura de pilha quem tem a struct pokemon como parametro
typedef struct {
    pokemon itens[MAX];
    int topo;
} Pilha;

//fila habilidade
typedef tp_habilidade
tp_itemm;

typedef struct {
    tp_habilidade item[MAX];
    int ini, fim;
    int tam;
} tp_filahab;


//chamando as funcoes para nao da erro no compilador
int nomeJogador(char n[MAX]);
void imprimirPokemon(pokemon p);
void inicializaPilhapok(Pilha *p);
int pilhaVaziapok(Pilha *p);
int pilhaCheiapok(Pilha *p);
void pushpok(Pilha *p, pokemon item);
pokemon poppok(Pilha *p);
void printPilhapok(Pilha p);
int alturaPilhapok(Pilha *p);
pokemon topopok(Pilha *p);
int pokemonIgual(pokemon q, pokemon w);
int pokemonNaPilha(Pilha *p, pokemon e);
void embaralhar(pokemon *vetor, int n);
void embaralharparceiro(int *vetor, int n);
pokemon trocaPokemon(Pilha *p);
void printhabilidade(tp_habilidade hab);
//filas habilidade
void iniciaFilahab(tp_filahab *f);
int insereFilahab(tp_filahab *f, tp_itemm e);
int retiraFilahab(tp_filahab *f, tp_itemm *e);
void printFilahab(tp_filahab m);
int filaVaziahab(tp_filahab *f);
int proximohab(int pos);
int filaCheiahab(tp_filahab *f);

void calculadano(pokemon *p1, pokemon *p2, tp_habilidade h);
void combate(pokemon *p1, pokemon *p2, tp_habilidade h1, tp_habilidade h2);

int main(){
    
    // nome do jogador
      char nome[MAX];
    
    //necessario para embaralhar
   srand(time(NULL));
    
  //filas para as habilidades
  tp_filahab fila[3];
  tp_item item[3];

//pilha dos pokemons(parceiros e oq sobrou)
  Pilha pokepilha[2];

  //seus pokemons
  int parceiro[3];
    
    //variavel auxiliar
    int x;

  
  //definindo o nome do jogador
  nomeJogador(nome);
    
    //todas as habilidades possiveis
    tp_habilidade habilidades[47] = {
        {"Thunder Shock", "Electric", 40, 100},
        {"Quick Attack", "Normal", 40, 100},
        {"Iron Tail", "Steel", 100, 75},
        {"Thunder", "Electric", 110, 70},
        {"Flamethrower", "Fire", 90, 100},
        {"Fly", "Flying", 90, 95},
        {"Dragon Claw", "Dragon", 80, 100},
        {"Fire Spin", "Fire", 35, 85},
        {"Vine Whip", "Grass", 45, 100},
        {"Razor Leaf", "Grass", 55, 95},
        {"Solar Beam", "Grass", 120, 100},//10 //2 turnos
        {"Water Gun", "Water", 40, 100},
        {"Tackle", "Normal", 40, 100},
        {"Bite", "Dark", 60, 100},
        {"Hydro Pump", "Water", 110, 80},
        {"Take Down", "Normal", 90, 85},
        {"Swift", "Normal", 60, 100},
        {"Body Slam", "Normal", 85, 100},
        {"Double-Edge", "Normal", 120, 100},
        {"Hyper Voice", "Normal", 90, 100},
        {"Disarming Voice", "Fairy", 40, 100},//20
        {"Hyper Beam", "Normal", 150, 90},    //2 turnos
        {"Giga Impact", "Normal", 150, 90},
        {"Shadow Ball", "Ghost", 80, 100},
        {"Dark Pulse", "Dark", 80, 100},
        {"Acid Spray", "Poison", 40, 100},
        {"Dream Eater", "Psychic", 100, 100},
        {"Sludge Bomb", "Poison", 90, 100},
        {"Karate Chop", "Fighting", 50, 100},
        {"Submission", "Fighting", 80, 80},
        {"Cross Chop", "Fighting", 100, 80},//30
        {"Dynamic Punch", "Fighting", 100, 50},
        {"Psychic", "Psychic", 90, 100},
        {"Psybeam", "Psychic", 65, 100},
        {"Dragon Tail", "Dragon", 60, 90},
        {"Hurricane", "Flying", 110, 70},
        {"Waterfall", "Water", 80, 100},
        {"Crunch", "Dark", 80, 100},
        {"Extreme Speed", "Normal", 80, 100}, //+2prio
        {"Fire Fang", "Fire", 65, 95},
        {"Skull Bash", "Normal", 130, 100},//40 //2 turnos
        {"Surf", "Water", 90, 100},
        {"Earthquake", "Ground", 100, 100},
        {"Frenzy Plant", "Grass", 150, 90},
        {"Calm Mind", "Psychic", 0, 100},  // +30% ataque +30% defesa por 2 turnos
        {"Dragon Dance", "Dragon", 0, 100},//+30% ataque +30% velocidade por 2 turnos
        {"Rest", "Psychic", 0, 100},   //46     //cura 50% do hp
        };
    
  //todos os pokemons presentes
    pokemon pokedex[15] = {
          {"Pikachu", 35, 10, habilidades[0], habilidades[1], habilidades[2], habilidades[3], 40, 55, 90, 35, "Electric"},
          {"Charizard", 78, 36, habilidades[4], habilidades[5], habilidades[6], habilidades[7], 78, 84, 100, 78, "Fire/Flying"},
          {"Bulbasaur", 45, 12, habilidades[8], habilidades[9], habilidades[25], habilidades[10], 49, 49, 45, 45,"Grass/Poison"},
          {"Squirtle", 44, 10, habilidades[11], habilidades[12], habilidades[13], habilidades[14], 65, 48, 43, 44, "Water"},
          {"Eevee", 55, 8, habilidades[1], habilidades[13], habilidades[15], habilidades[16], 50, 55, 55, 55, "Normal"},
          {"Jigglypuff", 115, 7, habilidades[20], habilidades[17], habilidades[18], habilidades[19], 20, 45, 20, 115, "Fairy"},
          {"Snorlax", 160, 30, habilidades[17], habilidades[21], habilidades[46], habilidades[22], 65, 110, 30, 160,  "Normal"},
          {"Gengar", 60, 28, habilidades[23], habilidades[24], habilidades[26], habilidades[26], 60, 65, 110, 60, "Ghost/Poison"},
          {"Machamp", 90, 25, habilidades[28], habilidades[29], habilidades[30], habilidades[31], 85, 130, 55, 90, "Fighting"},
          {"Alakazam", 55, 35, habilidades[32], habilidades[23], habilidades[33], habilidades[44], 45, 50, 120, 55, "Psychic"},
          {"Dragonite", 91, 55, habilidades[34], habilidades[21], habilidades[25], habilidades[45], 95, 134, 80, 91, "Dragon/Flying"},
          {"Gyarados", 95, 40, habilidades[36], habilidades[13], habilidades[14], habilidades[45], 79, 125, 81, 95,  "Water/Flying"},
          {"Arcanine", 90, 32, habilidades[4], habilidades[38], habilidades[37], habilidades[39], 80, 110, 95, 90, "Fire"},
          {"Blastoise", 79, 36, habilidades[14], habilidades[40], habilidades[13], habilidades[41], 100, 83, 78, 79, "Water"},
          {"Venusaur", 80, 35, habilidades[10], habilidades[27], habilidades[42], habilidades[43], 83, 82, 80, 80, "Grass/Poison"}
      };

    
    
  // momento de escolher os pokemons
  printf("\n Agora escolha os seus 3 pokemons.\n");
  for(int i=0;i<15;i++){
    printf("%d: %s\n",i,pokedex[i].nome);
  }
  printf("\n");
  for(int i=0;i<3;i++){
    printf("Pokemon %d : ",i+1);
    scanf("%d", &parceiro[i]);
      if(i==1){
          if(parceiro[0]==parceiro[1]){
              printf("Escolha inválida. Não escolha pokemons iguais.\n");
              i--;
          }
      }if(i==2){
          if(parceiro[0]==parceiro[2] || parceiro[1]==parceiro[2]){
              printf("Escolha inválida. Não escolha pokemons iguais.\n");
              i--;
          }
      }
    if(parceiro[i] < 0 || parceiro[i] >= 15) {
        printf("Escolha inválida! Tente novamente.\n");
        i--; 
    }
  }
      
  //imprimindo os pokemons escolhidos
  printf("\n");
  printf("Esses sao seus pokemons:\n");
   printf("-------------------------------------\n");
  for(int i=0;i<3;i++){
    imprimirPokemon(pokedex[parceiro[i]]);
  }
        
    
    //inicializa as 3 filas
        for(int i=0;i<3;i++){
          iniciaFilahab(&fila[i]);}


         //enfileira todas as habilidades
      for(int i=0;i<3;i++){
          insereFilahab(&fila[i], pokedex[parceiro[i]].habilidade1);
          insereFilahab(&fila[i], pokedex[parceiro[i]].habilidade2);
          insereFilahab(&fila[i], pokedex[parceiro[i]].habilidade3);
          insereFilahab(&fila[i], pokedex[parceiro[i]].habilidade4);
      }
    /*A seleção de ataques funcionará da seguinte forma: Quando o jogador escolher um ataque,
    a fila irá rodar (retirando um ataque e colocando no fim da fila), até o ataque no inicio da fila
    ser o ataque que o jogador escolheu.
    Por exemplo:
    O jogador escolheu o ataque 3, a fila está assim: 2 3 1 4, sendo o ataque '4', o inicio da fila.
    O '4' iria para o fim da fila, bem como o 1, até o 3 ficar no inicio: 2 3 1 4 ->  4 2 3 1 ->  1 4 2 3.
    */
       
// mostra as habilidades na fila
  printf("\n");
    printf("deseja verificar a fila de habilidades? se sim digite 1\n ");
    scanf("%d", &x);
    if(x==1){
        for(int i=0;i<3;i++){
            printf("Fila %d: ",i+1);
            printFilahab(fila[i]);
            printf("\n\n");
            }
        x=0;
    }
    


//inicializas as pilhas de pokemon
    for(int i=0;i<2;i++){
    inicializaPilhapok(&pokepilha[i]);}  
    
//embaralha e empilha os parceiros
embaralharparceiro(parceiro,3);
for(int i=0;i<3;i++){
pushpok(&pokepilha[0],pokedex[parceiro[i]]);
}

//embaralhar e empilha oq sobrou
embaralhar(pokedex,15);
for (int i = 0; i < 15; i++) {
    if (!pokemonNaPilha(&pokepilha[0], pokedex[i])) {
        pushpok(&pokepilha[1], pokedex[i]);
    }
}
    
//verifica o embaralhamento e o empilhamento doq sobrou
     printf("\n");
     printf("-------------------------------------\n");
printf("deseja verificar o embaralhamento? se sim digite 1\n");
scanf("%d", &x);
     printf("\n");

if(x==1){
printf("Todos os Pokémon na pilha:\n");
     printf("-------------------------------------\n");
    printPilhapok(pokepilha[1]);
  x=0;  
}
//verifica o embaralhamento e o empilhamento dos parceiros
    printf("\n");
printf("deseja verificar o embaralhamento dos parceiros? se sim digite 1 \n");

scanf("%d", &x);
     printf("\n");
if(x==1){
printf("Todos os os seus parceiros:\n");
     printf("-------------------------------------\n");
    printPilhapok(pokepilha[0]);
x=0;
}

pokemon aliado, inimigo;
tp_habilidade aliadohab, inimigohab;
int escolha;
int inimigosort;

aliado = trocaPokemon(&pokepilha[0]);
inimigo = poppok(&pokepilha[1]);
printf("\n");
printf("-------------------------------------\n");
printf("Jogador escolheu o pokemon %s\n", aliado.nome);
printf("Inimigo escolheu o pokemon %s\n", inimigo.nome);

printf("antes loop:  %d", alturaPilhapok(&pokepilha[0]));

while(!pilhaVaziapok(&pokepilha[0]) && !pilhaVaziapok(&pokepilha[1])){
    printf("Inimigo: \n");
    printf("%s   %dlvl   vida: %d/%d\n", inimigo.nome, inimigo.nivel, inimigo.vida, inimigo.vidamax);
    printf("-------------------------------------------------------------------\n");
    printf("Aliado: \n");
    printf("%s   %dlvl   vida: %d/%d\n", aliado.nome, aliado.nivel, aliado.vida, aliado.vidamax);
    printf("-------------------------------------------------------------------\n");
    printf("Escolha uma habilidade para ser usada\n");
    printf("----------------------------------------\n");
    printhabilidade(aliado.habilidade1);
    printhabilidade(aliado.habilidade2);
    printhabilidade(aliado.habilidade3);
    printhabilidade(aliado.habilidade4);
    printf("Digite 1, 2, 3 ou 4 para %s, %s, %s, %s, respectivamente\n", aliado.habilidade1.nome, aliado.habilidade2.nome, aliado.habilidade3.nome, aliado.habilidade4.nome);
    scanf("%d", &escolha);
    printf("\n\n");

    switch(escolha){
        case 1:
        aliadohab =  aliado.habilidade1;
        break;
        case 2:
        aliadohab =  aliado.habilidade2;
        break;
        case 3:
        aliadohab =  aliado.habilidade3;
        break;
        case 4:
        aliadohab =  aliado.habilidade4;
        break;
    }
    inimigosort = (rand() % 4)+1;
    switch(inimigosort){
        case 1:
        inimigohab =  inimigo.habilidade1;
        break;
        case 2:
        inimigohab =  inimigo.habilidade2;
        break;
        case 3:
        inimigohab =  inimigo.habilidade3;
        break;
        case 4:
        inimigohab =  inimigo.habilidade4;
        break;
    }
    printf("O pokemon adversário escolheu a habilidade %s\n", inimigohab.nome);
    combate(&aliado, &inimigo, aliadohab, inimigohab);

    if(inimigo.vida <= 0){
        printf("O pokemon adversário morreu!\n");
        inimigo = poppok(&pokepilha[1]);
        printf("O inimigo escolheu o pokemon %s\n", inimigo.nome);
    }
    if(aliado.vida <= 0){
        printf("Seu pokemon morreu!\n");
        aliado = trocaPokemon(&pokepilha[0]);
    }
    printf("\n\n\n\n");
}
  return 0;
}




//todas as funcoes usadas

void imprimirPokemon(pokemon p) {
    printf("Nome: %s\n", p.nome);
    printf("Vida: %d\n", p.vida);
    printf("Nível: %d\n", p.nivel);
    printf("Habilidade 1: %s\n", p.habilidade1.nome);
    printf("Habilidade 2: %s\n", p.habilidade2.nome);
    printf("Habilidade 3: %s\n", p.habilidade3.nome);
    printf("Habilidade 4: %s\n", p.habilidade4.nome);
  printf("Defesa : %d\n",p.defesa);
  printf("Ataque : %d\n",p.ataque);
    printf("Velocidade : %d\n",p.velocidade);
    printf("Tipo: %s\n", p.tipo);
    printf("-------------------------------------\n");
}
// feito para definir o nome do jogador
int nomeJogador(char n[MAX]){
   int x;
   printf("escolha seu nome de jogador : ");
   scanf("%[^\n]s", n);
   do {
      printf("\n\nSe deseje alterar o nome\nDigite: 1.\nou, digite 2 para continuar : ");
      scanf("%d", &x);
      if(x != 1 && x != 2)
         printf("\nNúmero inválido!\n");
     if(x==1){
       memset(n, 0, MAX);
       printf("\n--------------------------------------\n");
       printf("escolha seu nome de jogador : \n");
        scanf(" %[^\n]s", n);
   }
   } while(x != 2);
  printf("\n--------------------------------------\n");
printf("Bom jogo : %s",n);
  printf("\n--------------------------------------");

  return 1;
}
//-------------------------------------PILHA------------------------------------------
void inicializaPilhapok(Pilha *p) {
    p->topo = -1;
}


int pilhaVaziapok(Pilha *p) {
    return p->topo == -1;
}

int pilhaCheiapok(Pilha *p) {
    return p->topo == MAX - 1;
}

void pushpok(Pilha *p, pokemon item) {
    if (pilhaCheiapok(p)) {
        printf("Pilha cheia!\n");
        return;
    }
    p->itens[++(p->topo)] = item;
}

pokemon poppok(Pilha *p) {
    if (pilhaVaziapok(p)) {
        printf("Pilha vazia!\n");
        exit(1); 
    }
    return p->itens[(p->topo)--];
}

pokemon topopok(Pilha *p) {
    if (pilhaVaziapok(p)) {
        printf("Pilha vazia!\n");
        exit(1); 
    }
    return p->itens[p->topo];
}

int pokemonIgual(pokemon p1, pokemon p2) {
  return strcmp(p1.nome, p2.nome) == 0;
}

int pokemonNaPilha(Pilha *p, pokemon item) {
  for (int i = 0; i <= p->topo; i++) {
      if (pokemonIgual(p->itens[i], item)) {
          return 1;
      }
  }
  return 0;
}
void printPilhapok(Pilha p){
  pokemon e;
  printf("\n");
  while(!pilhaVaziapok(&p)){ 
    e = poppok(&p);
    imprimirPokemon(e);
  }
}
int alturaPilhapok(Pilha *p){
  return p->topo+1; 
}
//-------------------------------------PILHA------------------------------------------

//-------------------------------------FILA------------------------------------------
void iniciaFilahab(tp_filahab *f) {
    f->ini= f->fim = MAX-1;
    f->tam = 0;
}

int filaVaziahab(tp_filahab *f){
    if (f->fim == f->ini) return 1;
    return 0;
}

int proximohab(int pos){
    if(pos == MAX-1) return 0;
    pos++;
    return pos;
}

int filaCheiahab(tp_filahab *f){
    if(proximohab(f->fim) == f->ini)
        return 1;
    return 0;
}

int insereFilahab(tp_filahab *f, tp_itemm e){
    if (filaCheiahab(f)) 
        return 0;
    f->fim = proximohab(f->fim);
    f->item[f->fim] = e;
    f->tam ++;
    return 1;
}

int retiraFilahab(tp_filahab *f, tp_itemm *e){
    if(filaVaziahab(f))
        return 0;
    f->ini = proximohab(f->ini);
    *e = f->item[f->ini];
    f->tam --;
    return 1;
}

void printFilahab(tp_filahab f){
    tp_itemm e;
    while(!filaVaziahab(&f)){
    retiraFilahab(&f, &e);
    printf("\n%s", e.nome);
}
}
//-------------------------------------FILA------------------------------------------
void embaralhar(pokemon *vetor, int n) {
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        pokemon temp = vetor[i];
        vetor[i] = vetor[j];
        vetor[j] = temp;
    }
}

void embaralharparceiro(int *vetor, int n) {
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = vetor[i];
        vetor[i] = vetor[j];
        vetor[j] = temp;
    }
}

//funcao para calcular quem vai atacar primeiro, e chamar a funcao calcula dano (chamar a funcao uma vez)
void combate(pokemon *p1, pokemon *p2, tp_habilidade h1, tp_habilidade h2){

    if(strcmp(h1.nome, "Quick Attack") == 0 && strcmp(h2.nome, "Quick Attack") != 0 && strcmp(h2.nome, "Extreme Speed") != 0){
        printf("Quick Attack ataca primeiro\n");
    calculadano(p1, p2, h1);
    if(p2->vida > 0){
        calculadano(p2, p1, h2);
    }

    }else if(strcmp(h2.nome, "Quick Attack") == 0 && strcmp(h1.nome, "Quick Attack") != 0 && strcmp(h1.nome, "Extreme Speed") != 0){
        printf("Quick Attack ataca primeiro\n");
        calculadano(p2, p1, h2);
        if(p1->vida > 0){
            calculadano(p1, p2, h1);
        }

}else if(strcmp(h1.nome, "Extreme Speed") == 0  && strcmp(h2.nome, "Extreme Speed") != 0){
    printf("Extreme Speed ataca primeiro\n");
    calculadano(p1, p2, h1);
    if(p2->vida > 0){
        calculadano(p2, p1, h2);
    }
}else if(strcmp(h2.nome, "Extreme Speed") == 0 && strcmp(h1.nome, "Extreme Speed") != 0){
    printf("Extreme Speed ataca primeiro\n");
    calculadano(p2, p1, h2);
    if(p1->vida > 0){
        calculadano(p1, p2, h1);
    }
}else{
    if(p1->velocidade >= p2->velocidade){
        calculadano(p1, p2, h1);
        if(p2->vida > 0){
            calculadano(p2, p1, h2);
        }
    }else{
        calculadano(p2, p1, h2);
        if(p1->vida > 0){
            calculadano(p1, p2, h1);
        }
    }
}
}
//funcao para calcular e aplicar o dano
void calculadano(pokemon *pAta, pokemon *pDef, tp_habilidade h1){

    if(strcmp(h1.nome, "Dragon Dance")==0){
        printf("%s usou %s\n", pAta->nome, h1.nome);
        pAta->ataque = pAta->ataque*1.3;
        pAta->ataque = pAta->ataque*1.3;
        printf("O ataque e velocidade de %s aumentaram!\n", pAta->nome);
    }else if(strcmp(h1.nome, "Calm Mind")==0){
        printf("%s usou %s\n", pAta->nome, h1.nome);
        pAta->ataque = pAta->ataque*1.3;
        pAta->defesa = pAta->defesa*1.3;
        printf("O ataque e defesa de %s aumentaram!\n", pAta->nome);
    }else if(strcmp(h1.nome, "Rest")==0){
        printf("%s usou %s\n", pAta->nome, h1.nome);
        pAta->vida = pAta->vida + 90;
        if(pAta->vida > pAta->vidamax)
            pAta->vida = pAta->vidamax;
        printf("%s recuperou vida!\n", pAta->nome);
    }

    //chance de acerto
    int sorteio = rand()%100;
    if(sorteio >= h1.precisao){
        printf("O ataque de %s errou!\n", pAta->nome);
        return;
    }else{
        //calcular dano
        int dano;
        dano = (h1.dano*pAta->ataque)/100;
        dano = dano - pDef->defesa;

        sorteio = rand()%100;
        if(sorteio>=95){
            dano = dano*1.3;
            printf("%s causou um acerto crítico!\n", pAta->nome);
        }
        //superefetivo ou pouco superefetivo
        // Normal
    if (strcmp(pDef->tipo, "Normal") == 0) {
        if (strcmp(h1.tipo, "Fighting") == 0) {
            dano *= 1.5;
            printf("%s foi super efetivo!\n", h1.nome);
        } else if (strcmp(h1.tipo, "Ghost") == 0) {
            printf("%s é imune ao ataque %s!\n", pDef->nome, h1.nome);
            dano = 0;
        }
    } 
    // Grass/Poison
    else if (strcmp(pDef->tipo, "Grass/Poison") == 0) {
        if (strcmp(h1.tipo, "Fire") == 0 || strcmp(h1.tipo, "Psychic") == 0 || 
            strcmp(h1.tipo, "Flying") == 0 || strcmp(h1.tipo, "Ice") == 0) {
            dano *= 1.5;
            printf("%s foi super efetivo!\n", h1.nome);
        } else if (strcmp(h1.tipo, "Water") == 0 || strcmp(h1.tipo, "Grass") == 0 || 
                   strcmp(h1.tipo, "Electric") == 0 || strcmp(h1.tipo, "Fairy") == 0) {
            dano *= 0.5;
            printf("%s foi pouco efetivo.\n", h1.nome);
        }
    } 
    // Electric
    else if (strcmp(pDef->tipo, "Electric") == 0) {
        if (strcmp(h1.tipo, "Ground") == 0) {
            printf("%s é imune ao ataque %s!\n", pDef->nome, h1.nome);
            dano = 0;
        } else if (strcmp(h1.tipo, "Water") == 0 || strcmp(h1.tipo, "Flying") == 0) {
            dano *= 1.5;
            printf("%s foi super efetivo!\n", h1.nome);
        } else if (strcmp(h1.tipo, "Electric") == 0 || strcmp(h1.tipo, "Grass") == 0) {
            dano *= 0.5;
            printf("%s foi pouco efetivo.\n", h1.nome);
        }
    } 
    // Fire/Flying
    else if (strcmp(pDef->tipo, "Fire/Flying") == 0) {
        if (strcmp(h1.tipo, "Water") == 0 || strcmp(h1.tipo, "Electric") == 0 || 
            strcmp(h1.tipo, "Rock") == 0) {
            dano *= 1.5;
            printf("%s foi super efetivo!\n", h1.nome);
        } else if (strcmp(h1.tipo, "Bug") == 0 || strcmp(h1.tipo, "Grass") == 0 || 
                   strcmp(h1.tipo, "Fairy") == 0) {
            dano *= 0.5;
            printf("%s foi pouco efetivo.\n", h1.nome);
        }
    } 
    // Water
    else if (strcmp(pDef->tipo, "Water") == 0) {
        if (strcmp(h1.tipo, "Electric") == 0 || strcmp(h1.tipo, "Grass") == 0) {
            dano *= 1.5;
            printf("%s foi super efetivo!\n", h1.nome);
        } else if (strcmp(h1.tipo, "Fire") == 0 || strcmp(h1.tipo, "Water") == 0 || 
                   strcmp(h1.tipo, "Ice") == 0) {
            dano *= 0.5;
            printf("%s foi pouco efetivo.\n", h1.nome);
        }
    } 
    // Fairy
    else if (strcmp(pDef->tipo, "Fairy") == 0) {
        if (strcmp(h1.tipo, "Steel") == 0 || strcmp(h1.tipo, "Poison") == 0) {
            dano *= 1.5;
            printf("%s foi super efetivo!\n", h1.nome);
        } else if (strcmp(h1.tipo, "Fighting") == 0 || strcmp(h1.tipo, "Bug") == 0 || 
                   strcmp(h1.tipo, "Dark") == 0) {
            dano *= 0.5;
            printf("%s foi pouco efetivo.\n", h1.nome);
        }
    } 
    // Ghost/Poison
    else if (strcmp(pDef->tipo, "Ghost/Poison") == 0) {
        if (strcmp(h1.tipo, "Psychic") == 0 || strcmp(h1.tipo, "Ghost") == 0) {
            dano *= 1.5;
            printf("%s foi super efetivo!\n", h1.nome);
        } else if (strcmp(h1.tipo, "Bug") == 0 || strcmp(h1.tipo, "Poison") == 0 || 
                   strcmp(h1.tipo, "Grass") == 0 || strcmp(h1.tipo, "Fairy") == 0) {
            dano *= 0.5;
            printf("%s foi pouco efetivo.\n", h1.nome);
        }
    } 
    // Fighting
    else if (strcmp(pDef->tipo, "Fighting") == 0) {
        if (strcmp(h1.tipo, "Flying") == 0 || strcmp(h1.tipo, "Psychic") == 0 || 
            strcmp(h1.tipo, "Fairy") == 0) {
            dano *= 1.5;
            printf("%s foi super efetivo!\n", h1.nome);
        } else if (strcmp(h1.tipo, "Rock") == 0 || strcmp(h1.tipo, "Bug") == 0 || 
                   strcmp(h1.tipo, "Dark") == 0) {
            dano *= 0.5;
            printf("%s foi pouco efetivo.\n", h1.nome);
        }
    } 
    // Psychic
    else if (strcmp(pDef->tipo, "Psychic") == 0) {
        if (strcmp(h1.tipo, "Bug") == 0 || strcmp(h1.tipo, "Ghost") == 0 || 
            strcmp(h1.tipo, "Dark") == 0) {
            dano *= 1.5;
            printf("%s foi super efetivo!\n", h1.nome);
        } else if (strcmp(h1.tipo, "Fighting") == 0 || strcmp(h1.tipo, "Psychic") == 0) {
            dano *= 0.5;
            printf("%s foi pouco efetivo.\n", h1.nome);
        }
    } 
    // Dragon/Flying
    else if (strcmp(pDef->tipo, "Dragon/Flying") == 0) {
        if (strcmp(h1.tipo, "Ice") == 0 || strcmp(h1.tipo, "Dragon") == 0 || 
            strcmp(h1.tipo, "Fairy") == 0) {
            dano *= 1.5;
            printf("%s foi super efetivo!\n", h1.nome);
        } else if (strcmp(h1.tipo, "Fire") == 0 || strcmp(h1.tipo, "Water") == 0 || 
                   strcmp(h1.tipo, "Grass") == 0 || strcmp(h1.tipo, "Electric") == 0 || 
                   strcmp(h1.tipo, "Fighting") == 0 || strcmp(h1.tipo, "Bug") == 0) {
            dano *= 0.5;
            printf("%s foi pouco efetivo.\n", h1.nome);
        }
    } 
    // Water/Flying
    else if (strcmp(pDef->tipo, "Water/Flying") == 0) {
        if (strcmp(h1.tipo, "Electric") == 0 || strcmp(h1.tipo, "Rock") == 0) {
            dano *= 1.5;
            printf("%s foi super efetivo!\n", h1.nome);
        } else if (strcmp(h1.tipo, "Fighting") == 0 || strcmp(h1.tipo, "Bug") == 0 || 
                   strcmp(h1.tipo, "Water") == 0 || strcmp(h1.tipo, "Steel") == 0) {
            dano *= 0.5;
            printf("%s foi pouco efetivo.\n", h1.nome);
        }
    } 
    // Fire
    else if (strcmp(pDef->tipo, "Fire") == 0) {
        if (strcmp(h1.tipo, "Water") == 0 || strcmp(h1.tipo, "Rock") == 0 || 
            strcmp(h1.tipo, "Ground") == 0) {
            dano *= 1.5;
            printf("%s foi super efetivo!\n", h1.nome);
        } else if (strcmp(h1.tipo, "Bug") == 0 || strcmp(h1.tipo, "Fire") == 0 || 
                   strcmp(h1.tipo, "Grass") == 0 || strcmp(h1.tipo, "Fairy") == 0) {
            dano *= 0.5;
            printf("%s foi pouco efetivo.\n", h1.nome);
        }
    }
        if(dano <= 0){
            printf("Dano causado de %s: 0\n", h1.nome);
            return;
        }else{
            pDef->vida = pDef->vida - dano;
            printf("Dano causado de %s: %d\n", h1.nome, dano);
        }
    }
    printf("Vida de %s após o ataque: %d\n", pDef->nome, pDef->vida);
}

//nao chamar funcao quando pilha está vazia, só quando um pokemon morrer e ainda tiver algum vivo
pokemon trocaPokemon(Pilha *poke){

    Pilha pokeaux;
    inicializaPilhapok (&pokeaux);
    char trocapoke[MAX];
    pokemon p;
    printf("Pokemons disponíveis:\n");

    while(!pilhaVaziapok(poke)){
        p = poppok(poke);
        imprimirPokemon(p); 
        pushpok(&pokeaux, p);
    }                                           //printa pokemon, sem excluir
    while(!pilhaVaziapok(&pokeaux)){
        p = poppok(&pokeaux);
        pushpok(poke, p);
    }

    printf("Digite o nome do pokemon que quer colocar em batalha: ");
    scanf("%s", trocapoke);
    
    while(!pilhaVaziapok(poke)){
        p = poppok(poke);
        
    if(strcmp(p.nome, trocapoke) == 0){
        printf("Pokemon escolhido: %s\n", p.nome);
        return p;
    }else{
        pushpok(&pokeaux, p);
        
    }
    }
    printf("aaa  %d", alturaPilhapok(&pokeaux));
    while(!pilhaVaziapok(&pokeaux)){
        p = poppok(&pokeaux);
        pushpok(poke, p);
    } 
    printf("Escolha inválida, pokemon escolhido: %s\n", p.nome);
    return p;
}

void printhabilidade(tp_habilidade hab){
    printf("%s  ",hab.nome);
    printf("%s  ", hab.tipo);
    printf("dano: %d  ", hab.dano);
    printf("precisão: %d", hab.precisao);
    printf("------------------------------------\n");
}
