#include <stdio.h>
#include <stdlib.h>

typedef struct Heap{
    int length;
    int heap_size;
    int VET[100];
}heap;

heap* heap_create(){
    heap* no = malloc(sizeof(heap));
    no->heap_size = 0;
    no->length = 0;
    return no;
}

int parent(int i){
    return i/2;
}

int left(int i){
    return 2*i;
}

int rigth(int i){
    return 2*i+1;
}

void troca(int *a, int *b) {
    int aux;
    aux = *a;
    *a = *b;
    *b = aux;
}

void maxHeapify(heap* no,int i){
    int l,r,maior;
    l = left(i);
    r = rigth(i);

    if(l <= no->heap_size && no->VET[l] > no->VET[i]){
        maior = l;
    }else
        maior = i;
    if(r <= no->heap_size && no->VET[r] > no->VET[i]){
        maior = r;
    }

    if(maior != i){
        troca(&no->VET[i],&no->VET[maior]);
        maxHeapify(no,maior);
    }
}

void buildMaxHeap(heap* no,int* vet,int len){
    no->length = no->heap_size = len;
    for (int i=0; i<len; i++)
        no->VET[i] = vet[i];

    for (int i=len/2; i>=0; i--)
        maxHeapify(no, i);
}



int main(){
    heap* no = heap_create();
    int vetor[] = {15,10,5};
    int size = sizeof(vetor)/sizeof(vetor[0]);

    buildMaxHeap(no, vetor, size);

    for(int i = 0; i<no->heap_size; i++)
        printf("%d ", no->VET[i]);
    printf("\n");
}