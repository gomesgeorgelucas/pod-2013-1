#ifndef B_STAR_TREE_HEADER_H_INCLUDED
#define B_STAR_TREE_HEADER_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#define MM  1
#define MM2 2

typedef int TipoChave;

typedef struct TipoRegistro {
  TipoChave Chave;
  /* outros componentes */
} TipoRegistro;

typedef enum {
  Interna, Externa
} TipoIntExt;

typedef struct TipoPagina *TipoApontador;

typedef struct TipoPagina {
  TipoIntExt Pt;
  union {
    struct {
      int ni;
      TipoChave ri[MM];
      TipoApontador pi[MM + 1];
    } U0;
    struct {
      int ne;
      TipoRegistro re[MM2];
    } U1;
  } UU;
} TipoPagina;

void Pesquisa(TipoRegistro *x, TipoApontador *Ap);

void Inicializa(TipoApontador *Dicionario);

void Insere(TipoRegistro Reg, TipoApontador *Ap);


#endif
