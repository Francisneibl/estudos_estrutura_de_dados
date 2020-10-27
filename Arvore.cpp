#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<locale.h>


typedef struct estrutura{
	int id;
	char nome[100];
	char cpf[14];
	
	struct estrutura * proxD=NULL;
	struct estrutura * proxE=NULL;
	
}Aluno;

Aluno *cadastro(Aluno *registro);
Aluno *decisao(Aluno *registro, Aluno *novo);
void imprimirD(Aluno *registro);
void imprimirE(Aluno *registro);
void imprimirT(Aluno *registro);

main(){
	
	Aluno *registro;
	
	registro = NULL;
	
	
	for(int menu=20;menu!=0;){
	printf("Digite a opcao desejada: \n1 - Novo Aluno \n2 - Imprimir Esquerda \n3-Imprimir Direita\n4 - Imprimir Tudo\n");
	scanf("%d",&menu);
	
	switch(menu){
		case 1: registro = cadastro(registro);break;
		case 2: imprimirE(registro);break;
		case 3: imprimirD(registro);break;
		case 4: imprimirT(registro);break;  
		case 0: exit(0);break;
	}
	}

	
}


Aluno *cadastro(Aluno *registro){
	
	Aluno *novo = (Aluno*) malloc(sizeof(Aluno));
	
	printf("Digite o id do aluno: ");
	scanf("%d",&novo->id);
	fflush(stdin);
	
	printf("Digite o nome do aluno:");
	gets(novo->nome);
	fflush(stdin);
	
	printf("Digite o cpf: ");
	gets(novo->cpf);
	
	novo->proxD = NULL;
	novo->proxE = NULL;
	
	if(registro==NULL){
		printf("\nprimeiro\n");
		return novo;
	}else{
		decisao(registro,novo);
	}
	
	
}

Aluno *decisao(Aluno *registro, Aluno *novo){
	
	Aluno *aux;
	aux=registro;
	
	if(novo->id>aux->id){
		if(aux->proxD==NULL){
			aux->proxD=novo;
		}else{
			aux=aux->proxD;
			aux = decisao(aux,novo);
		}
	}else{
		if(aux->proxE==NULL){
			aux->proxE = novo;
		}else{
			aux=aux->proxE;
			aux = decisao(aux,novo);
		}
	}
	
	return registro;
	
}


void imprimirD(Aluno *registro){
	
	Aluno* aux;
	
	for(aux=registro;aux!=NULL;aux=aux->proxD){
		printf("Nome = %s\n",aux->nome);
	}
	
}

void imprimirE(Aluno *registro){
	Aluno* aux;
	
	for(aux=registro;aux!=NULL;aux=aux->proxE){
		printf("Nome = %s\n",aux->nome);
	}	
	
}

void imprimirT(Aluno *registro){
	
	if(registro != NULL){
		printf("%s\n",registro->nome);
		imprimirT(registro->proxD);
		imprimirT(registro->proxE);
		
	}
	
}
