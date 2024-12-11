#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "pokemon.h"
#include "loja.h"
#include "ranking.h"
#define MAX 100
#define MAXt 5

int main() {

	// nome do jogador
	char nome[MAX];

	//necessario para embaralhar
	srand(time(NULL));

	//filas para as habilidades
	tp_filahab fila[3];

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
		{"Frenzy Plant", "Grass", 120, 90},
		{"Calm Mind", "Psychic", 0, 100},  // +30% ataque +30% defesa
		{"Dragon Dance", "Dragon", 0, 100},//+30% ataque +30% velocidade
		{"Rest", "Psychic", 0, 100},   //46     //cura 50% do hp
	};

	//todos os pokemons presentes
	pokemon pokedex[15] = {
		{"Pikachu", 40, 10, habilidades[0], habilidades[1], habilidades[2], habilidades[3], 40, 55, 90, 40, "Electric"},
		{"Charizard", 78, 36, habilidades[4], habilidades[5], habilidades[6], habilidades[7], 78, 84, 100, 78, "Fire/Flying"},
		{"Bulbasaur", 45, 12, habilidades[8], habilidades[9], habilidades[25], habilidades[10], 49, 49, 45, 45,"Grass/Poison"},
		{"Squirtle", 44, 10, habilidades[11], habilidades[12], habilidades[13], habilidades[14], 65, 48, 43, 44, "Water"},
		{"Eevee", 55, 8, habilidades[1], habilidades[13], habilidades[15], habilidades[16], 50, 55, 55, 55, "Normal"},
		{"Jigglypuff", 115, 7, habilidades[20], habilidades[17], habilidades[18], habilidades[19], 20, 45, 20, 115, "Fairy"},
		{"Snorlax", 130, 30, habilidades[17], habilidades[21], habilidades[46], habilidades[22], 75, 55, 30, 130,  "Normal"},
		{"Gengar", 60, 28, habilidades[23], habilidades[24], habilidades[26], habilidades[26], 60, 65, 110, 60, "Ghost/Poison"},
		{"Machamp", 90, 25, habilidades[28], habilidades[29], habilidades[30], habilidades[31], 70, 90, 55, 90, "Fighting"},
		{"Alakazam", 70, 35, habilidades[32], habilidades[23], habilidades[33], habilidades[44], 50, 80, 120, 70, "Psychic"},
		{"Dragonite", 91, 50, habilidades[34], habilidades[21], habilidades[25], habilidades[45], 85, 110, 80, 91, "Dragon/Flying"},
		{"Gyarados", 95, 40, habilidades[36], habilidades[13], habilidades[14], habilidades[45], 79, 105, 81, 95,  "Water/Flying"},
		{"Arcanine", 90, 32, habilidades[4], habilidades[38], habilidades[37], habilidades[39], 80, 100, 95, 90, "Fire"},
		{"Blastoise", 79, 36, habilidades[14], habilidades[40], habilidades[13], habilidades[41], 100, 83, 78, 79, "Water"},
		{"Venusaur", 80, 35, habilidades[10], habilidades[27], habilidades[42], habilidades[43], 83, 82, 80, 80, "Grass/Poison"}
	};

	// momento de escolher os pokemons
	printf("\n Agora escolha os seus 3 pokemons.\n");
	for(int i=0; i<15; i++) {
		printf("%d: %s\n",i,pokedex[i].nome);
	}
	printf("\n");
	for(int i=0; i<3; i++) {
		printf("Pokemon %d : ",i+1);
		scanf("%d", &parceiro[i]);
		if(i==1) {
			if(parceiro[0]==parceiro[1]) {
				printf("Escolha invC!lida. NC#o escolha pokemons iguais.\n");
				i--;
			}
		}
		if(i==2) {
			if(parceiro[0]==parceiro[2] || parceiro[1]==parceiro[2]) {
				printf("Escolha invC!lida. NC#o escolha pokemons iguais.\n");
				i--;
			}
		}
		if(parceiro[i] < 0 || parceiro[i] >= 15) {
			printf("Escolha invC!lida! Tente novamente.\n");
			i--;
		}
	}

	//imprimindo os pokemons escolhidos
	printf("\n");
	printf("Esses sao seus pokemons:\n");
	printf("-------------------------------------\n");
	for(int i=0; i<3; i++) {
		imprimirPokemon(pokedex[parceiro[i]]);
	}


	//inicializa as 3 filas
	for(int i=0; i<3; i++) {
		iniciaFilahab(&fila[i]);
	}


	//enfileira todas as habilidades
	for(int i=0; i<3; i++) {
		insereFilahab(&fila[i], pokedex[parceiro[i]].habilidade1);
		insereFilahab(&fila[i], pokedex[parceiro[i]].habilidade2);
		insereFilahab(&fila[i], pokedex[parceiro[i]].habilidade3);
		insereFilahab(&fila[i], pokedex[parceiro[i]].habilidade4);
	}


// mostra as habilidades na fila
	printf("\n");
	printf("deseja verificar a fila de habilidades? se sim digite 1\n ");
	scanf("%d", &x);
	if(x==1) {
		for(int i=0; i<3; i++) {
			printf("Fila %d: ",i+1);
			printFilahab(fila[i]);
			printf("\n\n");
		}
		x=0;
	}

//inicializas as pilhas de pokemon
	for(int i=0; i<2; i++) {
		inicializaPilhapok(&pokepilha[i]);
	}

//embaralha e empilha os parceiros
	embaralharparceiro(parceiro,3);
	for(int i=0; i<3; i++) {
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

	if(x==1) {
		printf("Todos os PokC)mon na pilha:\n");
		printf("-------------------------------------\n");
		printPilhapok(pokepilha[1]);
		x=0;
	}
//verifica o embaralhamento e o empilhamento dos parceiros
	printf("\n");
	printf("deseja verificar o embaralhamento dos parceiros? se sim digite 1 \n");

	scanf("%d", &x);
	printf("\n");
	if(x==1) {
		printf("Todos os os seus parceiros:\n");
		printf("-------------------------------------\n");
		printPilhapok(pokepilha[0]);
		x=0;
		system("cls");

	}

	pokemon aliado, inimigo, auxiliar1;
	int money = 1000, pokebola = 5;	
	tp_habilidade aliadohab, inimigohab;
	int escolhahab, escolhaacao=0, inimigosort, comb = 1, round = 1, capturou;
	int pontuacao=0;
	char item_comprado[50];
	Pilha pokepilhamorto;
	inicializaPilhapok(&pokepilhamorto);

	loja *l = inicializa_listase();

	aliado = trocaPokemon(&pokepilha[0]);
	inimigo = poppok(&pokepilha[1]);
	system("cls");
	printf("\n");
	printf("-------------------------------------\n");
	printf("Jogador escolheu o pokemon %s\n", aliado.nome);
	printf("Inimigo escolheu o pokemon %s\n", inimigo.nome);
	printf("-------------------------------------\n\n");

	while(comb == 1) {
		printf("Inimigo: \n");
		printf("%s  LVL %d  vida: %d/%d\n", inimigo.nome, inimigo.nivel, inimigo.vida, inimigo.vidamax);
		printf("-------------------------------------------------------------------\n");
		printf("Aliado: \n");
		printf("%s  LVL %d  vida: %d/%d\n", aliado.nome, aliado.nivel, aliado.vida, aliado.vidamax);
		printf("-------------------------------------------------------------------\n\n");
		escolhaacao=0;
		while(escolhaacao < 1 || escolhaacao > 3){
		printf("O que deseja fazer?\n///////\n1 para lutar\n2 para trocar de pokemon\n3 usar uma pokebola\n");
		scanf("%d", &escolhaacao);
		if(escolhaacao < 1 || escolhaacao > 3) {
			printf("Escolha inválida!\n\n");
		}
		}
		
		printf("\n");

		if(escolhaacao == 1) {
			printf("Escolha uma habilidade para ser usada\n");
			printf("----------------------------------------\n");
			printhabilidade(aliado.habilidade1);
			printhabilidade(aliado.habilidade2);
			printhabilidade(aliado.habilidade3);
			printhabilidade(aliado.habilidade4);
			printf("Digite:\n1 para --> %s\n2 para --> %s\n3 para --> %s\n4 para --> %s\n----------------------------------------\n", aliado.habilidade1.nome, aliado.habilidade2.nome, aliado.habilidade3.nome, aliado.habilidade4.nome);
			scanf("%d", &escolhahab);
			printf("\n\n");
			system("cls");


			switch(escolhahab) {
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
			switch(inimigosort) {
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
			printf("O pokemon adversario escolheu a habilidade %s!!!\n", inimigohab.nome);
			combate(&aliado, &inimigo, aliadohab, inimigohab);

			if(inimigo.vida <= 0) {
				printf("O pokemon adversario morreu\n(R.I.P)!\n");

				if(alturaPilhapok(&pokepilha[1]) == 0) {
					printf("Todos os pokemons inimigos morreram. Embaralhando novamente...\nAguarde...\n");
					embaralhar(pokedex,15);
					for (int i = 0; i < 15; i++) {
						if (!pokemonNaPilha(&pokepilha[0], pokedex[i])) {           //todos os pokemons que vocC* nao tem vao para a pilha de inimigos
							pushpok(&pokepilha[1], pokedex[i]);
						}
					}
				}
				inimigo = poppok(&pokepilha[1]);
				for(int i = 0; i<round; i++) {              //aumenta status do inimigo cada vez q ele morre
					level_up(&inimigo);
				}
				money += 90;
				pontuacao += 50;
				defineItensRandom(&l, item_comprado, &money);
				if(strcmp(item_comprado, "Nenhum") != 0){
				if(strcmp(item_comprado, "Pokebola") == 0){
					pokebola++;
				}
				else{
					usa_item(&aliado, item_comprado);
				}
				}
				printf("Os inimigos ficaram mais fortes!!!\n\n");
				printf("\n\n'HERE COMES A NEW CHALLENGER!!!'\n\n%s selvagem apareceu!!!\n", inimigo.nome);
				round ++;
				printf("%s ficou mais forte!!!\n", aliado.nome);
				level_up(&aliado);
			}


			if(aliado.vida <= 0) {
				printf("\n<!!!!!Seu pokemon morreu!!!!!>\n\n");
				auxiliar1 = poppok(&pokepilha[0]);               //retira o pokemon do topo da pilha
				pushpok(&pokepilhamorto, auxiliar1);                    //empilha na pilha de mortos
				if(pilhaVaziapok(&pokepilha[0])) {
					printf("\n---------------------------------\nVoce nao tem mais pokemons usaveis. Jogo encerrado.\n\nGAME OVER");
					salvar_ranking(nome, pontuacao);
					exibir_ranking();
					break;
				}
				aliado = trocaPokemon(&pokepilha[0]);
			}
			printf("\n\n\n\n");

		} else if(escolhaacao == 2) {
			aliado = trocaPokemonVivo(&pokepilha[0]);

		} else {
			if(pokebola == 0) {
				printf("Voce nao tem mais pokebolas.\n");
			}else if(alturaPilhapok(&pokepilha[0]) >= 6) {
				printf("Sua equipe está cheia. Não é possível capturar mais pokemons.\n");
			}
			else{
				pokebola--;
			capturou = captura(inimigo.vida, inimigo.vidamax);
			if(capturou){
				inimigo.vida = inimigo.vidamax*0.6;
				aliado = inimigo;
				pushpok(&pokepilha[0], inimigo);
				if(alturaPilhapok(&pokepilha[1]) == 0) {
					printf("Todos os pokemons inimigos morreram. Embaralhando novamente...\nAguarde...\n");
					embaralhar(pokedex,15);
					for (int i = 0; i < 15; i++) {
						if (!pokemonNaPilha(&pokepilha[0], pokedex[i])) {           //todos os pokemons que vocC* nao tem vao para a pilha de inimigos
							pushpok(&pokepilha[1], pokedex[i]);
						}
					}
				}
				inimigo = poppok(&pokepilha[1]);
				for(int i = 0; i<round; i++) {              //aumenta status do inimigo cada vez q ele morre
					level_up(&inimigo);
				}
				money += 90;
				pontuacao += 50;
				defineItensRandom(&l, item_comprado, &money);
				if(strcmp(item_comprado, "Nenhum") != 0){
				if(strcmp(item_comprado, "Pokebola") == 0){
					pokebola++;
				}
				else{
					usa_item(&aliado, item_comprado);
				}
				}
				}
				printf("Os inimigos ficaram mais fortes!!!\n\n");	
				printf("\n\n'HERE COMES A NEW CHALLENGER!!!'\n\n%s selvagem apareceu!!!\n", inimigo.nome);
				round ++;
				printf("%s ficou mais forte!!!\n", aliado.nome);
				level_up(&aliado);
			}
			}
		}

	return 0;
}
