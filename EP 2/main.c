#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int MAX(int a, int b) {
    return a > b ? a : b;
}

typedef struct noBst {
    int chave;
    struct noBst * esq;
    struct noBst * dir;
} BST;

BST * bstNovoNo(int chaveParaCriacao) {
    BST * no = malloc(sizeof(struct noBst));
    no->chave = chaveParaCriacao;
    no->esq = NULL;
    no->dir = NULL;
    return no;
}

BST * bstInsert(BST * raiz, int chaveParaInsercao) {
    if (raiz == NULL) {
        return bstNovoNo(chaveParaInsercao);
    }

    if (chaveParaInsercao > raiz->chave) {
        raiz->dir = bstInsert(raiz->dir, chaveParaInsercao);
    }
    else {
        raiz->esq = bstInsert(raiz->esq, chaveParaInsercao);
    }

    return raiz;
}

int bstCalculaAltura(BST * raiz) {
 if(raiz == NULL) {
   return 0;
 }
  else {
   int noEsquerda;
   int noDireita;
   noEsquerda = bstCalculaAltura(raiz->esq);
   noDireita = bstCalculaAltura(raiz->dir);
   if(noEsquerda > noDireita) {
     return noEsquerda + 1;
   }
   else {
     return noDireita + 1;
   }
 }
}

void bstFree(BST * raiz) {
  if (raiz == NULL) return;

  if (raiz->esq != NULL)
    bstFree(raiz->esq);
  if (raiz->dir != NULL)
    bstFree(raiz->dir);
  
  free(raiz);
}

typedef struct noAvl {
  int valor;
  struct noAvl *esquerdo, *direito;
  int altura;
}AVL;

AVL* novoNo(int X){
  AVL *novo = malloc(sizeof(AVL));

    if(novo){
      novo->valor = X;
      novo->esquerdo = NULL;
      novo->direito = NULL;
      novo->altura = 1;
    }
    else
      printf("\nERRO ao alocar no em novoNo!\n");
    return novo;
  
}
int maior(int a, int b){
  return(a > b)? a: b;
}

int alturaDaAvl(AVL * no){
  if(no == NULL)
    return 0;
  else
    return no->altura;
}

int fatorDB(AVL *no) {
  if(no)
    return (alturaDaAvl(no->esquerdo) - alturaDaAvl(no->direito));
  else
    return 0;
}

AVL* rotacaoEsquerda(AVL *r) {
  AVL *y, *f;

  y = r->direito;
  f = y->esquerdo;

  y->esquerdo = r;
  r->direito = f;

  r->altura = maior(alturaDaAvl(r->esquerdo), alturaDaAvl(r->direito)+1);
  y->altura = maior(alturaDaAvl(y->esquerdo), alturaDaAvl(y->direito)+1);

  return y;
}

AVL* rotacaoDireita(AVL *r) {
  AVL *y, *f;

  y = r->esquerdo;
  f = y->direito;

  y->direito = r;
  r->esquerdo = f;

  r->altura = maior(alturaDaAvl(r->esquerdo), alturaDaAvl(r->direito)+1);
  y->altura = maior(alturaDaAvl(y->esquerdo), alturaDaAvl(y->direito)+1);

  return y;
}

AVL* rotacaoDireitaEsquerda(AVL *r) {
  r->direito = rotacaoDireita(r->direito);
  return rotacaoEsquerda(r);
}

AVL* rotacaoEsquerdaDireita(AVL *r) {
  r->esquerdo = rotacaoEsquerda(r->esquerdo);
  return rotacaoDireita(r);
}

AVL* balancear(AVL *raiz) {
  int FB = fatorDB(raiz);

  if(FB < -1 && fatorDB(raiz->direito) <= 0)
    raiz = rotacaoEsquerda(raiz);
    
  else if(FB > 1 && fatorDB(raiz->esquerdo) >= 0)
    raiz = rotacaoDireita(raiz);
    
  else if(FB > 1 && fatorDB(raiz->esquerdo) < 0)
    raiz = rotacaoEsquerdaDireita(raiz);
    
  else if(FB < - 1 && fatorDB(raiz->direito) > 0)
    raiz = rotacaoDireitaEsquerda(raiz);
  
  return raiz;
}

AVL* inserir(AVL *raiz, int x) {
  if(raiz==NULL)
    return novoNo(x);
  else {
    if(x < raiz->valor)
      raiz->esquerdo = inserir(raiz->esquerdo, x);
    else if(x > raiz->valor)
      raiz->direito = inserir(raiz->direito, x);
  }
  raiz->altura = maior(alturaDaAvl(raiz->esquerdo), alturaDaAvl(raiz->direito)) + 1;
  raiz = balancear(raiz);
    
  return raiz;
}

void imprimir(AVL *raiz, int nivel) {
    int i;
    if(raiz) {
        imprimir(raiz->direito, nivel + 1);
        printf("\n\n");
        
        for(i = 0; i < nivel; i++)
            printf("\t");
        printf("%d", raiz->valor);
        imprimir(raiz->esquerdo, nivel + 1);
        
    }
}

void avlFree(AVL * raiz) {
  if (raiz == NULL) return;

  if (raiz->esquerdo != NULL)
    avlFree(raiz->esquerdo);
  if (raiz->direito != NULL)
    avlFree(raiz->direito);
  
  free(raiz);
}

int* geraNumerosAleatorios(int N) {
    int* numerosAleatorios = malloc(sizeof(int) * N);
    int igual, i = 0;
    do {
        numerosAleatorios[i] = rand() % N*2;
        igual = 0;
        for(int j = 0; j < i; j++) {
            if(numerosAleatorios[j] == numerosAleatorios[i])
                igual = 1;
        }
        if(igual == 0)
            i++;
    }while(i < N);
  
    /*for(i=0; i<N; i++){
        //printf("%d ", numerosAleatorios[i]);
    }*/
    
    return numerosAleatorios;
  }

void print(char * msg) {
    printf("%s", msg);
    printf("\n");
}

void gerarArvores(){
    int A, N;
    float somaBst=0, somaAvl=0, somaGeral=0, mediaBst, mediaAvl, mediaGeral;
    
    printf("Digite o número de amostras: ");
    scanf("%d", &A);
    printf("Digite o número de nós: ");
    scanf("%d", &N);

    for (int i = 0; i < A; i++) {
        int * numerosAleatorios = geraNumerosAleatorios(N);
        BST * rBst = NULL;
        AVL * rAvl = NULL;
        for (int k = 0; k < N; k++) {
            rBst = bstInsert(rBst, numerosAleatorios[k]);
            rAvl = inserir(rAvl, numerosAleatorios[k]);
        }
        int alturaBst = bstCalculaAltura(rBst);
        somaBst += alturaBst;
        int alturaAvl = alturaDaAvl(rAvl);
        somaAvl += alturaAvl;

        //printf("\n AVL %i", alturaAvl);
        //printf("\nArvore AVL : \n");
        //imprimir(rAvl, 1);
        //printf("\n BST %i", alturaBst);
        //printf("\nArvore BST : \n");
        //imprimir(rBst, 1);
    }

mediaBst = somaBst / A;
mediaAvl = somaAvl / A;
somaGeral = mediaAvl + mediaBst;
mediaGeral = somaGeral / 2;

printf("\nExperimento com A = %d e N = %d\n", A, N);
print("--------------------------------");
printf("\nA media da BST é : %0.1f", mediaBst);
printf("\nA media da AVL é : %0.1f", mediaAvl);
printf("\nA media Geral é : %0.1f\n", mediaGeral);
}

int main(int argc, const char * argv[]) {
    srand(time(NULL));
    int continuar=1;
    
        print("EP2 - Nas alturas - Template");
        print("--------------------------------");
        
    do {
        printf("\n1) Nova simulação");
        printf("\n2) Sair\n");
        scanf("%d", &continuar);
    switch(continuar) {
        case 1:
            gerarArvores();
            break;
        case 2:
            printf("Saindo...\n");
            continuar=0;
            break;
        default:
            printf("\nopção invalida\n");
    }
}while (continuar);
    
        
    
    return 0 ;
}
