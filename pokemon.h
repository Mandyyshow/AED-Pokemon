
#include <string.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 100
#define MAXt 5

//struct de uma habilidade
typedef struct {
	char nome[MAX];
	char tipo[MAX];
	float dano;
	int precisao;
} tp_habilidade;
// estrutura de um pokemon
typedef struct {
	char nome[MAX];
	int vida;
	int nivel;
	tp_habilidade habilidade1;
	tp_habilidade habilidade2;
	tp_habilidade habilidade3;
	tp_habilidade habilidade4;
	float defesa;
	float ataque;
	int velocidade;
	int vidamax;
	char tipo[MAX];
} pokemon;

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


//todas as funcoes usadas

void imprimirPokemon(pokemon p) {
	printf("Nome: %s\n", p.nome);
	printf("Vida: %d\n", p.vida);
	printf("NC-vel: %d\n", p.nivel);
	printf("Habilidade 1: %s\n", p.habilidade1.nome);
	printf("Habilidade 2: %s\n", p.habilidade2.nome);
	printf("Habilidade 3: %s\n", p.habilidade3.nome);
	printf("Habilidade 4: %s\n", p.habilidade4.nome);
	printf("Defesa : %.0lf\n",p.defesa);
	printf("Ataque : %.0lf\n",p.ataque);
	printf("Velocidade : %d\n",p.velocidade);
	printf("Tipo: %s\n", p.tipo);
	printf("-------------------------------------\n");
}
// feito para definir o nome do jogador
int nomeJogador(char n[MAX]) {
	int x;
	printf("escolha seu nome de jogador : ");
	scanf("%[^\n]s", n);
	do {
		printf("\nSe deseje alterar o nome, Digite: 1.\nou, digite 2 para continuar : ");
		scanf("%d", &x);
		if(x != 1 && x != 2)
			printf("\nNC:mero invC!lido!\n");
		if(x==1) {
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
		printf("\n<!!!!!Pilha cheia!!!!!!>\n");
		return;
	}
	p->itens[++(p->topo)] = item;
}

pokemon poppok(Pilha *p) {
	if (pilhaVaziapok(p)) {
		printf("\n<!!!!!Pilha vazia!!!!!!>\n");
		exit(1);
	}
	return p->itens[(p->topo)--];
}

pokemon topopok(Pilha *p) {
	if (pilhaVaziapok(p)) {
		printf("\n<!!!!!Pilha vazia!!!!!>\n");
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
void printPilhapok(Pilha p) {
	pokemon e;
	printf("\n");
	while(!pilhaVaziapok(&p)) {
		e = poppok(&p);
		imprimirPokemon(e);
	}
}
int alturaPilhapok(Pilha *p) {
	return p->topo+1;
}
//-------------------------------------PILHA------------------------------------------

//-------------------------------------FILA------------------------------------------
void iniciaFilahab(tp_filahab *f) {
	f->ini= f->fim = MAX-1;
	f->tam = 0;
}

int filaVaziahab(tp_filahab *f) {
	if (f->fim == f->ini) return 1;
	return 0;
}

int proximohab(int pos) {
	if(pos == MAX-1) return 0;
	pos++;
	return pos;
}

int filaCheiahab(tp_filahab *f) {
	if(proximohab(f->fim) == f->ini)
		return 1;
	return 0;
}

int insereFilahab(tp_filahab *f, tp_itemm e) {
	if (filaCheiahab(f))
		return 0;
	f->fim = proximohab(f->fim);
	f->item[f->fim] = e;
	f->tam ++;
	return 1;
}

int retiraFilahab(tp_filahab *f, tp_itemm *e) {
	if(filaVaziahab(f))
		return 0;
	f->ini = proximohab(f->ini);
	*e = f->item[f->ini];
	f->tam --;
	return 1;
}

void printFilahab(tp_filahab f) {
	tp_itemm e;
	while(!filaVaziahab(&f)) {
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
//funcao para calcular e aplicar o dano
void calculadano(pokemon *pAta, pokemon *pDef, tp_habilidade h1) {

	if(strcmp(h1.nome, "Dragon Dance")==0) {
		printf("%s usou %s!!!\n", pAta->nome, h1.nome);
		pAta->ataque = pAta->ataque*1.3;
		pAta->ataque = pAta->ataque*1.3;
		printf("O ataque e velocidade de %s aumentaram!!!\n", pAta->nome);
	} else if(strcmp(h1.nome, "Calm Mind")==0) {
		printf("%s usou %s!!!\n", pAta->nome, h1.nome);
		pAta->ataque = pAta->ataque*1.3;
		pAta->defesa = pAta->defesa*1.3;
		printf("O ataque e defesa de %s aumentaram!!!\n", pAta->nome);
	} else if(strcmp(h1.nome, "Rest")==0) {
		printf("%s usou %s!!!\n", pAta->nome, h1.nome);
		pAta->vida = pAta->vida + 90;
		if(pAta->vida > pAta->vidamax)
			pAta->vida = pAta->vidamax;
		printf("%s recuperou vida!!!\n", pAta->nome);
	}

	//chance de acerto
	int sorteio = rand()%100;
	if(sorteio >= h1.precisao) {
		printf("O ataque de %s errou!!!\n", pAta->nome);
		return;
	} else {
		//calcular dano
		float dano;
		dano = (h1.dano*(pAta->ataque/pDef->defesa))/4;

		sorteio = rand()%100;
		if(sorteio>=95) {
			dano = dano*1.3;
			printf("%s causou um acerto crC-tico!!!\nSMAAAAAAASSSSSHHHHHH!!!!!!!\n", pAta->nome);
		}
		//superefetivo ou pouco superefetivo
		// Normal
		if (strcmp(pDef->tipo, "Normal") == 0) {
			if (strcmp(h1.tipo, "Fighting") == 0) {
				dano *= 1.5;
				printf("%s foi super efetivo!!!\n", h1.nome);
			} else if (strcmp(h1.tipo, "Ghost") == 0) {
				printf("%s C) imune ao ataque %s!!!\n", pDef->nome, h1.nome);
				dano = 0;
			}
		}
		// Grass/Poison
		else if (strcmp(pDef->tipo, "Grass/Poison") == 0) {
			if (strcmp(h1.tipo, "Fire") == 0 || strcmp(h1.tipo, "Psychic") == 0 ||
			        strcmp(h1.tipo, "Flying") == 0 || strcmp(h1.tipo, "Ice") == 0) {
				dano *= 1.5;
				printf("%s foi super efetivo!!!\n", h1.nome);
			} else if (strcmp(h1.tipo, "Water") == 0 || strcmp(h1.tipo, "Grass") == 0 ||
			           strcmp(h1.tipo, "Electric") == 0 || strcmp(h1.tipo, "Fairy") == 0) {
				dano *= 0.5;
				printf("%s foi pouco efetivo...\n", h1.nome);
			}
		}
		// Electric
		else if (strcmp(pDef->tipo, "Electric") == 0) {
			if (strcmp(h1.tipo, "Ground") == 0) {
				printf("%s C) imune ao ataque '%s'!!!\n", pDef->nome, h1.nome);
				dano = 0;
			} else if (strcmp(h1.tipo, "Water") == 0 || strcmp(h1.tipo, "Flying") == 0) {
				dano *= 0.5;
				printf("%s foi pouco efetivo...\n", h1.nome);
			} else if (strcmp(h1.tipo, "Electric") == 0 || strcmp(h1.tipo, "Grass") == 0) {
				dano *= 1.5;
				printf("%s foi super efetivo!!!\n", h1.nome);
			}
		}
		// Fire/Flying
		else if (strcmp(pDef->tipo, "Fire/Flying") == 0) {
			if (strcmp(h1.tipo, "Water") == 0 || strcmp(h1.tipo, "Electric") == 0 ||
			        strcmp(h1.tipo, "Rock") == 0) {
				dano *= 1.5;
				printf("%s foi super efetivo!!!\n", h1.nome);
			} else if (strcmp(h1.tipo, "Bug") == 0 || strcmp(h1.tipo, "Grass") == 0 ||
			           strcmp(h1.tipo, "Fairy") == 0 || strcmp(h1.tipo, "Fire") == 0) {
				dano *= 0.5;
				printf("%s foi pouco efetivo...\n", h1.nome);
			}
		}
		// Water
		else if (strcmp(pDef->tipo, "Water") == 0) {
			if (strcmp(h1.tipo, "Electric") == 0 || strcmp(h1.tipo, "Grass") == 0) {
				dano *= 1.5;
				printf("%s foi super efetivo!!!\n", h1.nome);
			} else if (strcmp(h1.tipo, "Fire") == 0 || strcmp(h1.tipo, "Water") == 0 ||
			           strcmp(h1.tipo, "Ice") == 0) {
				dano *= 0.5;
				printf("%s foi pouco efetivo...\n", h1.nome);
			}
		}
		// Fairy
		else if (strcmp(pDef->tipo, "Fairy") == 0) {
			if (strcmp(h1.tipo, "Steel") == 0 || strcmp(h1.tipo, "Poison") == 0) {
				dano *= 1.5;
				printf("%s foi super efetivo!!!\n", h1.nome);
			} else if (strcmp(h1.tipo, "Fighting") == 0 || strcmp(h1.tipo, "Bug") == 0 ||
			           strcmp(h1.tipo, "Dark") == 0) {
				dano *= 0.5;
				printf("%s foi pouco efetivo...\n", h1.nome);
			}
		}
		// Ghost/Poison
		else if (strcmp(pDef->tipo, "Ghost/Poison") == 0) {
			if (strcmp(h1.tipo, "Psychic") == 0 || strcmp(h1.tipo, "Ghost") == 0) {
				dano *= 1.5;
				printf("%s foi super efetivo!!!\n", h1.nome);
			} else if (strcmp(h1.tipo, "Bug") == 0 || strcmp(h1.tipo, "Poison") == 0 ||
			           strcmp(h1.tipo, "Grass") == 0 || strcmp(h1.tipo, "Fairy") == 0) {
				dano *= 0.5;
				printf("%s foi pouco efetivo...\n", h1.nome);
			}
		}
		// Fighting
		else if (strcmp(pDef->tipo, "Fighting") == 0) {
			if (strcmp(h1.tipo, "Flying") == 0 || strcmp(h1.tipo, "Psychic") == 0 ||
			        strcmp(h1.tipo, "Fairy") == 0) {
				dano *= 1.5;
				printf("%s foi super efetivo!!!\n", h1.nome);
			} else if (strcmp(h1.tipo, "Rock") == 0 || strcmp(h1.tipo, "Bug") == 0 ||
			           strcmp(h1.tipo, "Dark") == 0) {
				dano *= 0.5;
				printf("%s foi pouco efetivo...\n", h1.nome);
			}
		}
		// Psychic
		else if (strcmp(pDef->tipo, "Psychic") == 0) {
			if (strcmp(h1.tipo, "Bug") == 0 || strcmp(h1.tipo, "Ghost") == 0 ||
			        strcmp(h1.tipo, "Dark") == 0) {
				dano *= 1.5;
				printf("%s foi super efetivo!!!\n", h1.nome);
			} else if (strcmp(h1.tipo, "Fighting") == 0 || strcmp(h1.tipo, "Psychic") == 0) {
				dano *= 0.5;
				printf("%s foi pouco efetivo...\n", h1.nome);
			}
		}
		// Dragon/Flying
		else if (strcmp(pDef->tipo, "Dragon/Flying") == 0) {
			if (strcmp(h1.tipo, "Ice") == 0 || strcmp(h1.tipo, "Dragon") == 0 ||
			        strcmp(h1.tipo, "Fairy") == 0) {
				dano *= 1.5;
				printf("%s foi super efetivo!!!\n", h1.nome);
			} else if (strcmp(h1.tipo, "Fire") == 0 || strcmp(h1.tipo, "Water") == 0 ||
			           strcmp(h1.tipo, "Grass") == 0 || strcmp(h1.tipo, "Electric") == 0 ||
			           strcmp(h1.tipo, "Fighting") == 0 || strcmp(h1.tipo, "Bug") == 0) {
				dano *= 0.5;
				printf("%s foi pouco efetivo...\n", h1.nome);
			}
		}
		// Water/Flying
		else if (strcmp(pDef->tipo, "Water/Flying") == 0) {
			if (strcmp(h1.tipo, "Electric") == 0 || strcmp(h1.tipo, "Rock") == 0) {
				dano *= 1.5;
				printf("%s foi super efetivo!!!\n", h1.nome);
			} else if (strcmp(h1.tipo, "Fighting") == 0 || strcmp(h1.tipo, "Bug") == 0 ||
			           strcmp(h1.tipo, "Water") == 0 || strcmp(h1.tipo, "Steel") == 0||strcmp(h1.tipo, "Fire") == 0) {
				dano *= 0.5;
				printf("%s foi pouco efetivo...\n", h1.nome);
			}
		}
		// Fire
		else if (strcmp(pDef->tipo, "Fire") == 0) {
			if (strcmp(h1.tipo, "Water") == 0 || strcmp(h1.tipo, "Rock") == 0 ||
			        strcmp(h1.tipo, "Ground") == 0) {
				dano *= 1.5;
				printf("%s foi super efetivo!!!\n", h1.nome);
			} else if (strcmp(h1.tipo, "Bug") == 0 || strcmp(h1.tipo, "Fire") == 0 ||
			           strcmp(h1.tipo, "Grass") == 0 || strcmp(h1.tipo, "Fairy") == 0) {
				dano *= 0.5;
				printf("%s foi pouco efetivo...\n", h1.nome);
			}
		}

		pDef->vida = pDef->vida - dano;
		printf("//////Dano causado de %s: %.3lf//////\n", h1.nome, dano);

	}

}

//funcao para calcular quem vai atacar primeiro, e chamar a funcao calcula dano (chamar a funcao uma vez)
void combate(pokemon *p1, pokemon *p2, tp_habilidade h1, tp_habilidade h2) {

	if(strcmp(h1.nome, "Quick Attack") == 0 && strcmp(h2.nome, "Quick Attack") != 0 && strcmp(h2.nome, "Extreme Speed") != 0) {
		printf("Quick Attack ataca primeiro!!!\n");
		calculadano(p1, p2, h1);
		if(p2->vida > 0) {
			calculadano(p2, p1, h2);
		}

	} else if(strcmp(h2.nome, "Quick Attack") == 0 && strcmp(h1.nome, "Quick Attack") != 0 && strcmp(h1.nome, "Extreme Speed") != 0) {
		printf("Quick Attack ataca primeiro!!!\n");
		calculadano(p2, p1, h2);
		if(p1->vida > 0) {
			calculadano(p1, p2, h1);
		}

	} else if(strcmp(h1.nome, "Extreme Speed") == 0  && strcmp(h2.nome, "Extreme Speed") != 0) {
		printf("Extreme Speed ataca primeiro!!!\n");
		calculadano(p1, p2, h1);
		if(p2->vida > 0) {
			calculadano(p2, p1, h2);
		}
	} else if(strcmp(h2.nome, "Extreme Speed") == 0 && strcmp(h1.nome, "Extreme Speed") != 0) {
		printf("Extreme Speed ataca primeiro!!!\n");
		calculadano(p2, p1, h2);
		if(p1->vida > 0) {
			calculadano(p1, p2, h1);
		}
	} else {
		if(p1->velocidade >= p2->velocidade) {
			calculadano(p1, p2, h1);
			if(p2->vida > 0) {
				calculadano(p2, p1, h2);
			}
		} else {
			calculadano(p2, p1, h2);
			if(p1->vida > 0) {
				calculadano(p1, p2, h1);
			}
		}
	}
}


//nao chamar funcao quando pilha estC! vazia, sC3 quando um pokemon morrer e ainda tiver algum vivo
pokemon trocaPokemon(Pilha *poke) {

	Pilha pokeaux;
	inicializaPilhapok (&pokeaux);
	char trocapoke[MAX];
	pokemon p;
	pokemon paux;

	printf("---------------Pokemons disponiveis:\n");
	while(!pilhaVaziapok(poke)) {
		p = poppok(poke);
		imprimirPokemon(p);
		pushpok(&pokeaux, p);
	}                                           //printa pokemon, sem excluir
	while(!pilhaVaziapok(&pokeaux)) {
		p = poppok(&pokeaux);
		pushpok(poke, p);
	}

	printf("[Digite o nome do pokemon que quer colocar em batalha:] ");
	scanf("%s", trocapoke);
	int Existe=0;
	int x = alturaPilhapok(poke);
	for(int i=0;i<x;i++){
	    if(strcmp(trocapoke, poke->itens[i].nome) == 0){
	        Existe=1;
	    }
	}
	if(Existe==0){
	    printf("!!!!Erro!!!!\nO pokemon digitado nao existe dentro da party!!!\nVamos colocar um para voce usar...\n");
	    p=poppok(poke);
	    pushpok(poke, p);
	    return p;
	}
	while(!pilhaVaziapok(poke)) {
		p = poppok(poke);
		if(strcmp(p.nome, trocapoke) == 0) {
			printf("[Pokemon escolhido: (%s)]\n", p.nome);  //pokemon escolhido = p
			break;
		} else {
			pushpok(&pokeaux, p);
		}
	}
	while(!pilhaVaziapok(&pokeaux)) {
		paux = poppok(&pokeaux);                    //volta pra pilha original
		pushpok(poke, paux);
	}
	pushpok(poke, p);                               //pokemon escolhido fica no topo
	return p;
}

pokemon trocaPokemonVivo(Pilha *poke) {

	Pilha pokeaux;
	inicializaPilhapok (&pokeaux);
	char trocapoke[MAX];
	pokemon p;
	pokemon paux;
	pokemon patu;

	patu = poppok(poke);

	if(pilhaVaziapok(poke)) {
		printf("---------------VocC* nC#o tem outros pokemons disponiveis!\n\n");
		pushpok(poke, patu);
		return patu;                                            //retorna pokemon atual
	}

	printf("---------------Pokemons disponC-veis:\n");
	while(!pilhaVaziapok(poke)) {
		p = poppok(poke);
		imprimirPokemon(p);
		pushpok(&pokeaux, p);
	}                                           //printa pokemon, sem excluir
	while(!pilhaVaziapok(&pokeaux)) {
		p = poppok(&pokeaux);
		pushpok(poke, p);
	}

	printf("Digite o nome do pokemon que quer colocar em batalha ou digite (n) para cancelar: ");
	scanf("%s", trocapoke);
	int Existe=0;
	int x = alturaPilhapok(poke);
	for(int i=0;i<x;i++){
	    if(strcmp(trocapoke, poke->itens[i].nome) == 0){
	        Existe=1;
	    }
	}
	if(Existe==0 && strcmp(trocapoke, "n") != 0 && strcmp(trocapoke, "N") != 0){
	    printf("!!!!Erro!!!!\nO pokemon digitado n�o existe dentro da party!!!\nVamos colocar um para voce usar...\n");
	    p=poppok(poke);
	    pushpok(poke, patu);
	    pushpok(poke, p);
	    return p;
	}
	else if(strcmp(trocapoke, "n") == 0 || strcmp(trocapoke, "N") == 0) {
		pushpok(poke, patu);
		return patu;
	}
	while(!pilhaVaziapok(poke)) {
		p = poppok(poke);
		if(strcmp(p.nome, trocapoke) == 0) {
			printf("Pokemon escolhido: %s\n", p.nome);  //pokemon escolhido = p
			break;
		} else {
			pushpok(&pokeaux, p);
		}
	}
	while(!pilhaVaziapok(&pokeaux)) {
		paux = poppok(&pokeaux);                    //volta pra pilha original
		pushpok(poke, paux);
	}
	pushpok(poke, patu);                            //coloca o pokemon que estava antes no combate na pilha
	pushpok(poke, p);                               //pokemon escolhido fica no topo
	return p;
}

void printhabilidade(tp_habilidade hab) {
	printf("%s  ",hab.nome);
	printf("%s  ", hab.tipo);
	printf("dano: %.0lf  ", hab.dano);
	printf("precisC#o: %d\n", hab.precisao);
	printf("------------------------------------\n");
}

void level_up(pokemon *p) {
	srand(time(NULL));
	int x = (rand()%3) + 1;
	p->vida = p->vida + x;
	p->vidamax = p->vidamax + x;
	p->defesa = p->defesa + (rand()%3) + 1;
	p->ataque = p->ataque + (rand()%3) + 1;
	p->velocidade = p->velocidade + (rand()%3) + 1;

}

	//se for 1, coloca o pokemon inimigo na pilha de pokemons aliados e coloca no combate, troca o pokemon inimigo
	int captura(float vida, float vidamax){
	float chance;
	int x;
	chance = (vida/vidamax)*100;
	x = rand()%100 + 20;

	if(x >= chance) {
		printf("Parabens, voce capturou o pokemon inimigo!\n");
		printf("Ele irá lutar para você agora!\n");
		return 1;
	}else{
		printf("Você não conseguiu capturar o pokemon\n");
		return 0;
	}
}

void usa_item(pokemon *aliado, char item[]){
	if(strcmp(item, "Pocao Base de Vida")==0){
		aliado->vida += 20;
		if(aliado->vida > aliado->vidamax){
			aliado->vida = aliado->vidamax;
		}
		printf("%s recuperou vida!!!\n", aliado->nome);
	}else if(strcmp(item, "Pocao Forte de Vida")==0){
		aliado->vida += 50;
		if(aliado->vida > aliado->vidamax){
			aliado->vida = aliado->vidamax;
		}
		printf("%s recuperou vida!!!\n", aliado->nome);
	}else if(strcmp(item, "Aumentar Ataque")==0){
		aliado->ataque += 25;
		printf("Ataque de %s aumentou!!!\n", aliado->nome);
	}else if(strcmp(item, "Aumentar Defesa")==0){
		aliado->defesa += 25;
		printf("Defesa de %s aumentou!!!\n", aliado->nome);
	}
}

