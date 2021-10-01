#include<stdio.h>

int main(){
    FILE* file;
    file = fopen("teste.html","r");
    char c;
    while ((c = getc(file)) != EOF)
        printf("caractere: %c\n",c);
    fclose(file);
}