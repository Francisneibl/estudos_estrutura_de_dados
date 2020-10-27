#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<locale.h>

typedef struct lista{
	char letra;
	lista *proximo;
	lista *ant;
}Lista;

typedef struct pilha{
	char letra;
	
	lista *proximo;
}Pilha;

Lista *iniciar();
Lista *inserir(Lista *l);
void imprimir(Lista *l);
void contador();

/*Variavel globais*/
int tam;
int level;

main(){
	setlocale(LC_ALL,"Portuguese");
	Lista *frase;
	frase = iniciar();
	for(int menu=20;menu!=0;){
		printf("MENU\n\n");
		printf("1 - Inserir frase para ser criptografada\n");
		printf("2 - Imprimir frase\n");
		printf("0 - Sair\n");
		printf("Digite a opção desejada: ");
		scanf("%d",&menu);
		switch(menu){
			case 1: frase=inserir(frase);break;
			case 2: imprimir(frase);break;
			case 0: printf("Saindo..."); break;
		}
	}
}

Lista *iniciar(){
	return NULL;
}

Lista *inserir(Lista *l){
	
	char test;
	Lista *novo;
	l = iniciar();
	system("cls");
	erro:
	tam=0;
	printf("Digite a frase desejada: ");
	while(1){
		test=getche();
		if(test!=13){
			novo = (Lista*)malloc(sizeof(Lista));
			novo->letra=test;
			novo->proximo=l;
			novo->ant=NULL;
			if(l!=NULL){
				l->ant=novo;
			}
			tam++;
			l = novo;
		}else{
			if(tam<2){
				system("cls");
				printf("A frase deve ter mais de 2 caracteres\n\n");
				l = iniciar();
				goto erro;
			}else{
				contador();
				break;
			}
		}
	}
	
	system("cls");
	return novo;
}

void contador(){
	
	system("cls");
	
	level=0;
	erro:
	printf("Digite o nivel de criptografia de 2 a %d:",tam);
	scanf("%d",&level);
	if(level>tam){
		system("cls");
		printf("Nivel de criptografia muito alto para o tamanho da frase!!!\n\n");
		goto erro;
	}
	
}

void imprimir(Lista *l){
	
	Lista *aux;
	Lista *test;
	
	for(aux=l;aux!=NULL&&aux->proximo!=NULL;aux=aux->proximo);
	for(test=aux;test!=NULL;test=test->ant){
		printf("%c",test->letra);
	}
	printf("\n\n");
	system("pause");
	system("cls");
}
