#include<stdio.h>
#include<locale.h>
#include<cstdlib>
#include<string.h>
#include <conio.h>

// Autor: Cleyton Rafael Gomes Silva
// Data de Cria��o: 22/02/2018 Hora: 10:00
// Objetivo: Programa de Criptografia

// estrutura para armazenamento de caracteres em formato de pilha;

	typedef struct pilha{
	
	char caractere; // caractere digitado
	
	struct pilha *proximo; // endere�o do pr�ximo caractere
	
	} Texto;

// estrutura para armazenamento de pilhas em formato de lista;	

	typedef struct lista{
	
	struct lista *proximo; // proxima pilha
	struct pilha *pilha; // endere�o de in�cio da pilha
	
	} Pilhas;


// escopo das fun��es

	Pilhas *inicializarPilhas();
	Pilhas *inserirPilhas(Pilhas*);
	Texto *inicializar();
	Texto *inserir(Texto*);
	Texto *push(Texto*,char);
	Texto *pop(Texto*);
	Texto *inverte(Texto*);
	Texto *gerarChave(int);
	int tamanho(Texto*);
	void imprimir(Texto*);
	bool consultaChave(int,Texto*);
	

// fun��o principal

main(){

// configura��o do idioma
	setlocale(LC_ALL,"Portuguese");
	
	
// vari�veis auxiliares
	
	char caractere; //armazenar os caracteres digitados
	int max; // m�ximo n�vel permitido e n�vel escolhido
	int nivel; // n�vel escolhido - quantidade de pilhas
	int senha; // leitura da chave para desencripta��o
	int divisao; // quantidade de caracteres por pilha
	int x,y,z; // controle de loops 

//estruturas pilha
	
	Texto *conteudo; //estrutura para armazenar o conte�do do texto a ser criptografado
	Texto *chave; //estrutura para armazenar a chave de acesso
	
// estruturas pilha auxiliares
	
	Texto *auxiliarTexto; // estrutura para controle de loop
	Texto *temporario; // estrutura tempor�ria para as pilhas
	
// estrutura lista
	Pilhas *pilhas; //estrutura para armazenar o endere�o inicial das pilhas
	
//estruturas lista auxiliar
			
	Pilhas *auxiliarPilhas; // estrutura para controle de loop
		
// inicializa��o de vari�veis	
	
	conteudo=inicializar();
	chave=inicializar();
	int menu=20; //controle do loop de menu

//personaliza��o de design

	system("color f5");

//menu
    
	for(;menu!=0;){

//exibia��o e leitura de menu

	printf("\n---------------------------------------------------");
	printf("\n-------------------Criptografia--------------------");
	printf("\n---------------------------------------------------\n");
	
	printf("1- Criptografar Texto\n");
	printf("2- Descriptografar Texto\n");
	printf("0- Sair\n");

	printf("\n---------------------------------------------------\n");
	printf("Digite a op��o desejada:");
	scanf("%d",&menu);
	fflush(stdin);

	//controle de menu
	switch(menu){
		
	case 1:
	
		conteudo = inicializar();
		
	    printf("\nDigite o texto a ser criptografado:");
	    
		for(;caractere!=13;){ // ler o texto por caractere, incluir o caracter na pilha e parar a leitura pela tecla enter = 13 - c�digo ASCII
			
			caractere=getche(); // getche - l� um caractere
			if(caractere==8) // remove a letra em caso de backspace
			conteudo=pop(conteudo);
			else
			conteudo=push(conteudo,caractere); // empilha caractere lido
		
		}
		
		fflush(stdin);
				
		max = tamanho(conteudo); // calcula o n�mero m�ximo de n�veis
		
		printf("\nDigite a quantidade de n�veis de criptografia entre 2 e %d: ",max-1);
		scanf("%d",&nivel);
		fflush(stdin);
		
		if(nivel<2||nivel>max){ // verifica se a quantidade de n�veis escolhidos atende o permitido, caso contr�rio reinicia a aplica��o
				
			printf("\nQuantidade n�o permitida!");
			conteudo = inicializar();
			break;
			
		}
		
		printf("\nChave de acesso: ");
		
		chave=gerarChave(nivel);
		
		divisao = (max-1) / nivel;
		
		conteudo = inverte(conteudo); // inverte a pilha para atender a ordem original do texto



		pilhas = inicializarPilhas();
		
		printf("\nTexto: ");
// cria o n�mero de pilhas referentes a escolha do usu�rio, utilizando lista.
				
		for(x=1;x<nivel;x++){
		
			pilhas = inserirPilhas(pilhas);	
		}

        temporario = inicializar(); 

// insere a quantidade dividida dos caracteres chave por chave 
                                                                                  
		for(y=1;chave!=NULL;chave=chave->proximo,y++){
			
// procura pela pilha referente a primeira chave e assim por diante
			
			for(auxiliarPilhas=pilhas, x=1; auxiliarPilhas!=NULL ; x++, auxiliarPilhas=auxiliarPilhas->proximo){
		
// empilha os caracteres na pilha referente a sequ�ncia das chaves			
				if (chave->caractere==x){
		
					if(y==nivel){
		
						for(;conteudo!=NULL;){  // caso seja a ultima chave, empilha todos os caracteres restante, em caso de divis�es n�o inteiras
		
							temporario = push(temporario,conteudo->caractere);
							conteudo=pop(conteudo);
						}
				
					} else {
		
						for(z = 0; z<divisao; z++){
						
							temporario = push(temporario,conteudo->caractere);
							conteudo=pop(conteudo);
											
						}
					}			
			
	
				temporario = inverte(temporario); // inverte a pilha da chave para bater com a ordem de desimpilhamento na desemcripta��o
				
				auxiliarPilhas->pilha=temporario; // guarda na lista a loca��o da pilha referente a chave
				
				temporario = inicializar(); // reinicia a pilha tempor�ria
		
				break; // inicia mais um ciclo do for
			
				}

			}	
		
		}
		printf("\n");
		printf("\nCriptografado!\n");
		printf("\n");
		printf("\n");
		
		
		break;
		
		
		
	case 2: 
		
		chave = inicializar(); // reinicia a chave
		
		
		printf("\nDigite os %d n�meros da chave separador por enter:\n\n",nivel);

// empilha a chave informada	
	
		for(x=0;x<nivel;x++){
	
			scanf ("%d",&senha);
			chave = push(chave,senha);
			
		}
				
		fflush(stdin);
		
		chave = inverte(chave); // inverte a chave para coincidir com a ordem de digita��o
		
		printf("\nChave informada:");
	
		imprimir(chave);
		
		printf("\nConte�do desencriptado: ");
		printf("\n\n");
		
		temporario = inicializar();
		

// procura pela pilha referente as chaves		
		for(;chave!=NULL;chave=chave->proximo){
			
// procura pela pilha referente a primeira chave e assim por diante
				
			for(auxiliarPilhas=pilhas, x=1; auxiliarPilhas!=NULL ; x++, auxiliarPilhas=auxiliarPilhas->proximo){
				
				if (chave->caractere==x){
					
					temporario = auxiliarPilhas->pilha;
					
					for(;temporario!=NULL;){ // desimpila a pilha
						
						temporario = pop(temporario);
						
					}
										
					break;
					
				}

			}
			
		temporario = inicializar();	
			
		}
		
		printf("\n");
		printf("\n");
	
	 	break;
	 
	case 0: return 0; break;
	
	default: printf("\nOp��o inv�lida!\n\n");
		
  	}
  	
	caractere='\n'; // limpa a vari�vel caractere
	
	system("pause");
	system("cls");
	}
	
return 0;

}

//fun��o para inicializa��o de lista ou pilha
	Texto *inicializar(){
		
		return NULL;
		
	}

//fun��o para inicializa��o de lista ou pilha
	Pilhas *inicializarPilhas(){
		
		return NULL;
		
	}
	
//fun��o para empilhar
	Texto *push(Texto *texto, char caractere){
		
		Texto *novo = (Texto*) malloc(sizeof(Texto));
		
		novo->caractere = caractere;
		novo->proximo=texto;
		texto = novo;
		
		return novo;
	}

// desempilhamento
	Texto *pop(Texto *texto){
		
	//	printf("%c",texto->caractere);
		texto = texto->proximo;
		
		return texto;
	}

//fun��o para retornar o tamanho de uma pilha ou lista
	int tamanho(Texto *texto){
	
		int tamanho=0;
		Texto *auxiliar;
		
		for(auxiliar=texto;auxiliar!=NULL;auxiliar=auxiliar->proximo,tamanho++);
		
		return tamanho;
	
	}

//fun��o para gerar a chave de acesso

	Texto* gerarChave(int nivel){

	Texto *chave;
	chave = inicializar();
	
	int aleatorio;
	
	
	for(;nivel>tamanho(chave);){
		
		aleatorio = rand() % nivel+1; // gerar n�meros aleat�rios entre o intervalo da chave
	
		if(consultaChave(aleatorio,chave)==1&&aleatorio!=0) // elimina chaves recorentes ou zero
		
			chave = push(chave,aleatorio);
	
	}
	
	chave = inverte(chave); // inverte para coincidir com a ordem de digita��o
	
	imprimir(chave);
	
	return chave;
	
	}

//fun��o para consultar se o valor foi inserido na chave

	bool consultaChave(int numero, Texto *texto){
	
	Texto *auxiliar;	

	for(auxiliar=texto;auxiliar!=NULL;auxiliar=auxiliar->proximo){
	
		if (auxiliar->caractere==numero)
			
			return 0; // retorna zero se o n�mero j� foi inserido
	
	}
	
	return 1; // retorna um se o n�mero n�o foi inserido
	
	}
	
// fun��o para imprimir uma lista

	void imprimir(Texto *texto){
	
	Texto *auxiliar;
	
    for(auxiliar=texto;auxiliar!=NULL;auxiliar=auxiliar->proximo)
    	
		printf("%d ",auxiliar->caractere);
	
	printf("\n");
	
	}

// fun��o para inverter pilhas 

	Texto *inverte(Texto *texto){
	
	Texto *auxiliar;
	Texto *revertido;
	
	revertido = inicializar();
	
	for(auxiliar=texto;auxiliar!=NULL;auxiliar=auxiliar->proximo){
		
	revertido=push(revertido,auxiliar->caractere);
	
	}
	
	return revertido;
	
	}

// fun��o para inserir espa�os para armazenar a posi��o inicial de pilhas em uma fila
	
	Pilhas *inserirPilhas(Pilhas *pilhas){
	
	Pilhas *novo = (Pilhas*) malloc(sizeof(Pilhas));
	
	novo->proximo = pilhas;
	
	pilhas = novo;
	
	return novo;
	
	}
