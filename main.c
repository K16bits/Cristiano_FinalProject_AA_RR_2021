#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N_ASCII 255

typedef struct Node{
    unsigned char caractere;
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

unsigned int pegandoFrequencias(FILE* f, unsigned int vetor[]){
    int r,i;
    for(i = 0;;i++){
        r = fgetc(f);
        if(feof(f)) break;
        vetor[r]++;
    }
    return i;
}

void adicionarNaFila(filaP* f,node* root){
    f->tamanhoHeap++;
    int pos = f->tamanhoHeap-1;

    while ((pos > 0) && (f->vetor[parent(pos)]->frequencia > root->frequencia)) {
        f->vetor[pos] = f->vetor[parent(pos)];
        pos = parent(pos);
    }
    f->vetor[pos] = root;
}

node* criarHuffman(int vetorFrequencia[]){
    filaP* f = iniciaFila();
    for(int i = 0; i < N_ASCII;i++){
            node* auxNode = criarNode(i,vetorFrequencia[i]); 
            adicionarNaFila(f,auxNode);
    }
    
    node* x,*y,*z;
    int n = f->tamanhoHeap-1;
    for(int i = 0; i < n ;  i++){
        z = malloc(sizeof(node));
        x = extraindoMinFila(f);
        y = extraindoMinFila(f);
        z->esq = x;
        z->dir = y;
        z->frequencia = x->frequencia + y->frequencia;
        adicionarNaFila(f,z);
    }
    return extraindoMinFila(f);
}

void traverse (node* root,	int level, char code_so_far[], char *codes[]) {

	// Se estiver em nodo folha
	if ((root->esq == NULL) && (root->dir == NULL)) {
		code_so_far[level] = 0;
		codes[root->caractere] = strdup (code_so_far);
	}else{
		//caso nao seja nodo folha, ir para esquerda com bit 0
		code_so_far[level] = '0';
		traverse (root->esq, level+1, code_so_far, codes);
		//ir para direita com bit 1
		code_so_far[level] = '1';
		traverse (root->dir, level+1, code_so_far, codes);
	}
}

int nbits, current_byte, nbytes;

//output de um bit unico para um arquivo aberto
void bitout (FILE *f, char b) {
	//faz um shift a esquerda no byte atual em 1
	current_byte <<= 1;
	//iremos colocar um 1 no final do byte atual caso b seja 1
	if (b == '1') current_byte |= 1;
	//mais um bit
	nbits++;
	//se tiver bits suficientes, ou seja 8, escrever o byte
	if (nbits == 8) {
		fputc (current_byte, f);
		nbytes++;
		nbits = 0;
		current_byte = 0;
	}
}

//agora utilizamos os codigos no vetor criado para codificar o arquivo
void encode_file (FILE *infile, FILE *outfile, char *codes[]){
	unsigned char ch;
	char *s;
	//inicializamos umas variaveis globais para serem utilizadas na funcao bitout
	current_byte = 0;
	nbits = 0;
	nbytes = 0;

	//continua ate o fim do arquivo
	for (;;){
		//pega um char
		ch = fgetc(infile);
		if (feof(infile)) break;
		//coloca a bitstring correspondente na outfile
		for (s=codes[ch]; *s; s++){
            bitout(outfile, *s);
        }
	}
	//termina o ultimo byte
	while (nbits)bitout(outfile, '0');
}

int main(int argc, char *argv[]){

    if (argc != 2) {
		fprintf (stderr, "Use: %s <arquivo.html>\n", argv[0]);
		exit (1);
	}
    FILE* f,*g,*F_registro;
    unsigned int n;//numero de bytes
    unsigned int vetorFrequencia[N_ASCII];
    char *codes[N_ASCII];//vetor de codigos, um por caractere
	char code[N_ASCII];// vetor para carregar um codigo
    char fname[100]; // nome do novo arquivo huf

    memset(vetorFrequencia,0,sizeof(vetorFrequencia));

    f = fopen(argv[1],"r");
    if(!f){
        perror(argv[1]);
        exit(1);
    }
    n = pegandoFrequencias(f,vetorFrequencia);
    fclose(f);

    node* huff = criarHuffman(vetorFrequencia);
    traverse(huff,0,code,codes);

    // F_registro = fopen("registro.txt","w");
    // fprintf(F_registro,"Key\tValor\n");
    // for(int i =0; i< 100;i++){
    //     fprintf(F_registro,"%c\t%s\n",(char)i,codes[i]);
    // }
    // fclose(F_registro);


    sprintf(fname,"%s.huf",argv[1]);
    g = fopen(fname,"w");
    if(!g){
        perror(fname);
        exit(1);
    }

    fwrite(vetorFrequencia,N_ASCII,sizeof(int),g);
    fwrite(&n, 1, sizeof (int), g);
    
    f = fopen(argv[1], "r");
	if(!f){
		perror(argv[1]);
		exit (1);
	}

    encode_file(f, g, codes);
	fclose (f);
	fclose (g);
    printf("%s is %0.2f%% of %s\n",fname,(float)nbytes/(float)n, argv[1]);
	exit(0);
}