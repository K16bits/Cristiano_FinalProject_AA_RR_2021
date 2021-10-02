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

node* criarNode(int caractere,int frequencia){
    node* root = malloc(sizeof(node));
    root->caractere = (char)caractere;
    root->frequencia = frequencia;
    root->esq = root->dir = NULL;
    return root;
}

void MinHeapify(filaP* f,int pos){
    int esq = left(pos);
    int dir = rigth(pos);
    int menor = pos;

    if(esq < f->tamanhoHeap && f->vetor[esq]->frequencia < f->vetor[pos]->frequencia)
        menor = esq;

    if(dir < f->tamanhoHeap && f->vetor[dir]->frequencia < f->vetor[menor]->frequencia)
        menor = dir;
    
    node* aux;
    if(menor != pos){
        aux = f->vetor[pos];
        f->vetor[pos] = f->vetor[menor];
        f->vetor[menor] = aux;
        MinHeapify(f,menor);
    }
}

node* extraindoMinFila(filaP *f){ 
    node* aux;
    aux = f->vetor[0];
    f->vetor[0] = f->vetor[f->tamanhoHeap-1];
    f->tamanhoHeap--;

    MinHeapify(f,0); // falha aqui
    return aux;
}

int pegandoFrequencias(int vetorFrequencia[],char vetor[], int tam){
    for(int i = 0;i < tam;i++){
        int x = (int)vetor[i];
        vetorFrequencia[x]++;
    }
}

void adicionarNaFila(filaP* f,node* root){
    f->tamanhoHeap++;
    int pos = f->tamanhoHeap-1;

    while (pos > 0 && f->vetor[parent(pos)]->frequencia > root->frequencia) {
        f->vetor[pos] = f->vetor[parent(pos)];
        pos = parent(pos);
    }

    f->vetor[pos] = root;
}

node* criarHuffman(int vetorFrequencia[]){
    filaP* f = iniciaFila();
    for(int i = 0; i < N_ASCII;i++){
        if(vetorFrequencia[i] != 0){
            node* auxNode = criarNode(i,vetorFrequencia[i]); 
            adicionarNaFila(f,auxNode);
        }
    }
    
}

int main(){
    int vetorFrequencia[N_ASCII];

    char teste[] = {'a','b','c','a','a','f'};

    int tamVetor = sizeof(teste)/sizeof(teste[0]);
    memset(vetorFrequencia,0,sizeof(vetorFrequencia));
    pegandoFrequencias(vetorFrequencia,teste,tamVetor);

    criarHuffman(vetorFrequencia);
}