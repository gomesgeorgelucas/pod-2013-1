/*
 ============================================================================
 Name        : BStarTree.c
 Author      : George Lucas Gomes / Otávio Lima / Luíz Sérgio / Walderi Willy
 Version     : 0.1b
 Copyright   : Free Distribution
 Description : Algorithm for B* Trees 17/05/2013 Seminar
 ============================================================================
 */

#include "b_star_tree_header.h"

#define false 0
#define true 1

int main(int argc, char *argv[]) {

	TipoRegistro x;
	TipoPagina *D;
	Inicializa(&D);
	printf("Chave: ");
	scanf("%ld%*[^\n]", &x.Chave);
	getchar();
	while (x.Chave != 0) {
		Insere(x, &D);
		Imprime(D); printf("Chave: ");
		scanf("%ld%*[^\n]", &x.Chave);
		getchar();
	}

	Testa(D);
	printf("Chave: ");
	scanf("%ld%*[^\n]", &x.Chave);
	getchar();

	while (x.Chave != 0) {
		Retira(x.Chave, &D);
		Imprime(D);
		printf("Chave: ");
		scanf("%ld%*[^\n]", &x.Chave);
		getchar();
	}
	Testa(D);

	return true;
}

