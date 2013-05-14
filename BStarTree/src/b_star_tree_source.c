#include "b_star_tree_header.h"

#define MM  1
#define MM2 2

#define TRUE 1
#define FALSE 0


void Pesquisa(TipoRegistro *x, TipoApontador *Ap) {
	int i;
	TipoApontador Pag;
	Pag = *Ap;
	if ((*Ap)->Pt == Interna) {
		i = 1;
		while (i < Pag->UU.U0.ni && x->Chave > Pag->UU.U0.ri[i - 1])
			i++;
		if (x->Chave < Pag->UU.U0.ri[i - 1]) Pesquisa(x, &Pag->UU.U0.pi[i - 1]);
		else Pesquisa(x, &Pag->UU.U0.pi[i]);
		return;
	}
	i = 1;
	while (i < Pag->UU.U1.ne && x->Chave > Pag->UU.U1.re[i - 1].Chave)
		i++;
	if (x->Chave == Pag->UU.U1.re[i - 1].Chave)
		*x = Pag->UU.U1.re[i - 1];
	else
		printf("TipoRegistro nao esta presente na arvore\n");
}

void Inicializa(TipoApontador *Dicionario) {
	*Dicionario = NULL;
}

void Insere(TipoRegistro Reg, TipoApontador *Ap) {
	short Cresceu;
	TipoRegistro RegRetorno;
	TipoPagina *ApRetorno, *ApTemp;
	Ins(Reg, *Ap, &Cresceu, &RegRetorno, &ApRetorno);

	if (Cresceu) {
		ApTemp = (TipoPagina *)malloc(sizeof(TipoPagina));
		ApTemp->Pt = 1;
		ApTemp->UU->U0->ni=1;
		ApTemp->ri[0] = RegRetorno;
		ApTemp->p[1] =com ApRetorno;
		ApTemp->p[0] = *Ap;  *Ap = ApTemp;
	}
}

void Ins(TipoRegistro Reg, TipoApontador Ap, short *Cresceu,
		TipoRegistro *RegRetorno,  TipoApontador *ApRetorno) {
	long i = 1; long j;
	TipoApontador ApTemp;
	if (Ap == NULL){
		*Cresceu = TRUE; (*RegRetorno) = Reg; (*ApRetorno) = NULL;
		return;
	}
	while (i < Ap->n && Reg.Chave > Ap->r[i-1].Chave)
		i++;
	if (Reg.Chave == Ap->r[i-1].Chave) {
		printf(" Erro: Registro ja esta presente\n"); *Cresceu = FALSE;
		return;
	}
	if (Reg.Chave < Ap->r[i-1].Chave)
		i--;
	Ins(Reg, Ap->p[i], Cresceu, RegRetorno, ApRetorno);

	if (!*Cresceu)
		return;

	if (Ap->n < MM) {   /* Pagina tem espaco */
		InsereNaPagina(Ap, *RegRetorno, *ApRetorno);
		*Cresceu = FALSE;
		return;
	}

	/* Overflow: Pagina tem que ser dividida */
	ApTemp = (TipoApontador)malloc(sizeof(TipoPagina));
	ApTemp->n = 0;  ApTemp->p[0] = NULL;
	if (i < M + 1) {
		InsereNaPagina(ApTemp, Ap->r[MM-1], Ap->p[MM]);
		Ap->n--;
		InsereNaPagina(Ap, *RegRetorno, *ApRetorno);
	}
	else InsereNaPagina(ApTemp, *RegRetorno, *ApRetorno);

	for (j = M + 2; j <= MM; j++)
		InsereNaPagina(ApTemp, Ap->r[j-1], Ap->p[j]);

	Ap->n = M;  ApTemp->p[0] = Ap->p[M+1];
	*RegRetorno = Ap->r[M];  *ApRetorno = ApTemp;
}


