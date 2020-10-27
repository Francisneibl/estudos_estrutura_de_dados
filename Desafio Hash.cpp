#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<locale.h>
#define TAM 100

typedef struct tabela{
	int codigo;
	char nome[100];
	int saldo;
}Estoque;

typedef Estoque* hash[TAM];
hash estoque;

void inserir(hash x);
void relatorio(hash estoque);
void excluir(hash estoque);
int espalhamento(int x);
int espalhamento2(int x);
void consultar(hash estoque);
void clear();

main(){
	
	setlocale(LC_ALL,"Portuguese");
	for(int menu=20;menu!=0;){	
		printf("1 - Cadastrar produto: \n");
		printf("2 - Relatorio completo de estoque\n");
		printf("3 - Consultar produto\n");
		printf("4 - Excluir produto\n");
		printf("0 - Sair\n");
		printf("Digite a opção desejada:");
		scanf("%d",&menu);
		
		switch(menu){
			case 1: inserir(estoque);break;
			case 2: relatorio(estoque);break;
			case 3: consultar(estoque);break;
			case 4: excluir(estoque);break;
			case 0: printf("Saindo...");break;
			default: clear(),printf("Opção inválida\n\n");
		}
	
	}
}


void inserir(hash x){
	clear();
	int codigo;
	int indice;
	
	printf("Digite o codigo do produto: ");
	scanf("%d",&codigo);
	
	indice=espalhamento(codigo);// calcula indice primario
	
	while(estoque[indice]!=NULL){
		indice=(indice+espalhamento2(codigo))%TAM; //caso ocorra colisão no indice primario
	}											   //é calculado um novo indice com uma segunda funçao						
	
	estoque[indice] = (Estoque*)malloc(sizeof(Estoque));
	estoque[indice]->codigo=codigo;
	printf("Digite a descrição do produto: ");
	fflush(stdin);
	gets(estoque[indice]->nome);
	
	printf("Digite o saldo: ");
	scanf("%d",&estoque[indice]->saldo);
	
	printf("\nArmazenado com sucesso na posição[x]  = %d \n\n",indice);
	system("pause");
	clear();
}

void consultar(hash estoque){
	clear();
	int codigo;
	int indice;
	printf("Digite o codigo do produto: ");
	scanf("%d",&codigo);
	
	indice=espalhamento(codigo);
	
	while(estoque[indice]!=NULL){
		if(estoque[indice]->codigo==codigo){
			printf("Codigo = %d\n",estoque[indice]->codigo);
			printf("Descrição = %s\n",estoque[indice]->nome);
			printf("Descrição = %d\n",estoque[indice]->saldo);
			system("pause");
			clear();
			return;
		}
	// caso o item não seja encontrado no indice primeiro, é recalculado um novo indice da mesma forma que no metodo de inserção	
		indice=(indice+espalhamento2(codigo))%TAM;  
	}
	printf("Produto não encontrado!!!\n");
	system("pause");
	clear();
}

void relatorio(hash estoque){
	clear();
	int cont = 0;
	for(int c=0;c<TAM;c++){
		if(estoque[c]!=NULL){
			printf("Codigo = %d\n",estoque[c]->codigo);
			printf("Descrição = %s\n",estoque[c]->nome);
			printf("Saldo = %d\n",estoque[c]->saldo);
			printf("Posição [x] = %d\n",c);
			printf("\n\n");
			cont++;
		}
	}
	if(cont==0){
		printf("Nenhum produto cadastrado!!!\n\n");
	}
	system("pause");
	clear();
}

void excluir(hash estoque){
	clear();
	int codigo;
	int indice;
	printf("Digite o codigo do produto: ");
	scanf("%d",&codigo);
	
	indice=espalhamento(codigo);
	
	while(estoque[indice]!=NULL){
		if(estoque[indice]->codigo==codigo){
			printf("Codigo = %d\n",estoque[indice]->codigo);
			printf("Descrição = %s\n",estoque[indice]->nome);
			estoque[indice]=NULL;
			printf("\nProduto excluido com sucesso!\n");
			system("pause");
			clear();
			return;
		}
		
		indice=(indice+espalhamento2(codigo))%TAM;
	}
	printf("Produto não encontrado!!!\n");
	system("pause");
	clear();
}

int espalhamento(int x){
	return (x%TAM);
}

void clear(){
	system("cls");
}

int espalhamento2(int x){
	return(3+(x%(TAM-3)));
}
