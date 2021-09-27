#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N_ASCII 255

typedef struct Node{
    char caractere;
    int frequencia;
    struct Node *esq;
    struct Node *dir;
}node;

typedef struct filaP{
    int tamanhoHeap;
    node* vetor[N_ASCII];
}filaP;

filaP* iniciaFila(){
    filaP* f = malloc(sizeof(filaP));
    f->tamanhoHeap = 0;
    return f;
}

int parent(int i){return (i-1)/2;}
int left(int i){return (i*2+1);}
int rigth(int i){ return (i*2+2);}
void troca(int *a, int *b) {
    int aux;
    aux = *a;
    *a = *b;
    *b = aux;
}

node* initNode(char caractere){
    node* root = malloc(sizeof(node));
    root->caractere = caractere;
    root->esq = root->dir = NULL;
    return root;
}

int pegandoFrequencias(int vetorMvetorFrequencia[],char vetor[], int tam){
    for(int i = 0;i < tam;i++){
        int x = (int)vetor[i];
        vetorMvetorFrequencia[x]++;
        //printf(" - %d",x);
    }
}

void adicionarNaFila(filaP* f,node* root){
    f->tamanhoHeap++;
    int pos = f->tamanhoHeap-1;

    while (pos>=0 && f->vetor[parent(pos)]->frequencia > root->frequencia) {
        f->vetor[pos] = f->vetor[parent(pos)];
        pos = parent(pos);
    } 
    f->vetor[pos] = root;
}

node* criarHuffman(int* vetorFrequencia[]){
    filaP* f = iniciaFila();
    printf("%d",f->tamanhoHeap);
}

int main(){
    int vetorFrequencia[N_ASCII];
    char teste[5] = {'a','b','c','a','a'};
    int tamVetor = sizeof(teste)/sizeof(teste[0]);
    memset(vetorFrequencia,0,sizeof(vetorFrequencia));
    pegandoFrequencias(vetorFrequencia,teste,tamVetor);

    //printf("posi - N 97: %d",vetorFrequencia[97]);
}