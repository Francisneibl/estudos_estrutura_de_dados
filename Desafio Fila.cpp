#include<stdio.h>
#include<stdlib.h>
#include<locale.h>

typedef struct fila{
	int cod;
	int prioridade;
	char software[100];
	fila *proximo;
}Fila;

Fila *iniciar();
void *inserir();
void imprimir(Fila *x,int y);
Fila *enfileirar(Fila *x,Fila *novo);
void desenfileirar();
bool fila_vazia(Fila *x);
void relatorio();

Fila *p1,*p2,*p3;

main(){
	
	setlocale(LC_ALL,"Portuguese");
	
		
	p1=iniciar();
	p2=iniciar();
	p3=iniciar();
	
	
	for(int menu=20;menu!=0;){
		printf("============ MENU ============\n");
		printf("1 - Iniciar processo\n");
		printf("2 - Terminar processo\n");
		printf("3 - Mostrar todos os processos\n");
		printf("0 - Sair\n");
		printf("Digite o opção desejada: ");
		scanf("%d",&menu);
		
		
		switch(menu){
			case 1: inserir();break;
			case 2: desenfileirar() ;break;
			case 3: relatorio();break;
			case 0: printf("Saindo....") ;break;
			default: system("cls"),printf("Opção invalida !!!! \n");
		}
	}
}


Fila *iniciar(){
	return NULL;
}


void *inserir(){

	Fila *novo = (Fila*)malloc(sizeof(Fila));
	
	printf("Digite o codigo do processo: ");
	scanf("%d",&novo->cod);
	ERRO:
	printf("Digite a prioridade do processo\n");
	printf("1 - Alta\n");
	printf("2 - Média\n");
	printf("3 - Baixa\n");
	scanf("%d",&novo->prioridade);
	if(novo->prioridade!=1&&novo->prioridade!=2&&novo->prioridade!=3){
		printf("Valor de prioridade incorreto!!!\n");
		goto ERRO;
	}
	printf("Digite o nome do software: ");
	fflush(stdin);
	gets(novo->software);
	
	if(novo->prioridade==1){
		p1=enfileirar(p1, novo);
	}else if(novo->prioridade==2){
		p2=enfileirar(p2, novo);
	}else if(novo->prioridade==3){
		p3=enfileirar(p3, novo);
	}
}

Fila *enfileirar(Fila *x, Fila *novo){
	Fila *aux;
	
	if(x==NULL){
		novo->proximo=x;
		system("cls");
		return novo;
	}
	
	for(aux=x;aux->proximo!=NULL;aux=aux->proximo);
	novo->proximo=NULL;
	aux->proximo=novo;
	system("cls");
	return x;
}

void desenfileirar(){
	system("cls");
	if(p1!=NULL){
		printf("Encerrando processo...\n");	
		imprimir(p1,1);
		p1=p1->proximo;
		system("pause");
		system("cls");
	}else if(p2!=NULL){
		printf("Encerrando processo...\n");	
		imprimir(p2,1);
		p2=p2->proximo;
		system("pause");
		system("cls");
	}else if(p3!=NULL){
		printf("Encerrando processo...\n");	
		imprimir(p3,1);
		p3=p3->proximo;
		system("pause");
		system("cls");
	}else{
		system("cls");
		printf("\nNenhum processo em execução !!!\n\n");
	}
}

void relatorio(){
	
	system("cls");
	
	Fila *aux;
	printf("====== PROCESSOS PRIORIDADE ALTA =====\n");
	imprimir(p1,2);

	printf("====== PROCESSOS PRIORIDADE MÉDIA =====\n");
	imprimir(p2,2);
	
	
	printf("====== PROCESSOS PRIORIDADE BAIXA =====\n");
	imprimir(p3,2);
	
	system("pause");
	system("cls");
}

bool fila_vazia(Fila *x){
	if(x==NULL){
		return true;
	}else{
		return false;
	}
}

void imprimir(Fila *x,int y){
	Fila *aux;

	if(fila_vazia(x)){
		printf("Nenhum processo em execução!!!\n\n");
	}else{
		for(aux=x;aux!=NULL;aux=aux->proximo){
			printf("Codigo = %d\n",aux->cod);
			printf("Prioridade = %d\n",aux->prioridade);
			printf("Software = %s\n\n",aux->software);
			if(y==1)break;
		}	
	}
}
