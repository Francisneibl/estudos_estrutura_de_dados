#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<locale.h>

typedef struct estrutura{
	int codigo;
	char nome[50];
	struct estrutura *proximo;
}Pilha;


Pilha *inserir(Pilha *nomes);
void imprimir(Pilha*);
Pilha *remover(Pilha* nomes);

main(){
	
	setlocale(LC_ALL,"Portuguese");
	
	Pilha *nomes;
	nomes = NULL;
	nomes = inserir(nomes);
	nomes = inserir(nomes);
	imprimir(nomes);
}

Pilha *inserir(Pilha *nomes){
	Pilha*novo = (Pilha*) malloc(sizeof(Pilha));
	
	printf("Digite o codigo:");
	scanf("%d",&novo->codigo);
	fflush(stdin);
	printf("Digite o nome:");
	gets(novo->nome); 
	
	novo->proximo = nomes;
	
	return novo;
}

void imprimir(Pilha *nomes){
	
	Pilha *aux;
	
	for(aux=nomes;aux!=NULL;aux=aux->proximo){
		printf("Código : %d\n",aux->codigo);
		printf("Nome : %s\n",aux->nome);
	}
}

Pilha *remover(Pilha* nomes){
	
	nomes = nomes->	proximo;
	return nomes;
}
