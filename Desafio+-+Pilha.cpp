#include<stdio.h>
#include<locale.h>
#include<cstdlib>
#include<string.h>
#include <conio.h>

// Autor: Cleyton Rafael Gomes Silva
// Data de Criação: 22/02/2018 Hora: 10:00
// Objetivo: Programa de Criptografia

// estrutura para armazenamento de caracteres em formato de pilha;

	typedef struct pilha{
	
	char caractere; // caractere digitado
	
	struct pilha *proximo; // endereço do próximo caractere
	
	} Texto;

// estrutura para armazenamento de pilhas em formato de lista;	

	typedef struct lista{
	
	struct lista *proximo; // proxima pilha
	struct pilha *pilha; // endereço de início da pilha
	
	} Pilhas;


// escopo das funções

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
	

// função principal

main(){

// configuração do idioma
	setlocale(LC_ALL,"Portuguese");
	
	
// variáveis auxiliares
	
	char caractere; //armazenar os caracteres digitados
	int max; // máximo nível permitido e nível escolhido
	int nivel; // nível escolhido - quantidade de pilhas
	int senha; // leitura da chave para desencriptação
	int divisao; // quantidade de caracteres por pilha
	int x,y,z; // controle de loops 

//estruturas pilha
	
	Texto *conteudo; //estrutura para armazenar o conteúdo do texto a ser criptografado
	Texto *chave; //estrutura para armazenar a chave de acesso
	
// estruturas pilha auxiliares
	
	Texto *auxiliarTexto; // estrutura para controle de loop
	Texto *temporario; // estrutura temporária para as pilhas
	
// estrutura lista
	Pilhas *pilhas; //estrutura para armazenar o endereço inicial das pilhas
	
//estruturas lista auxiliar
			
	Pilhas *auxiliarPilhas; // estrutura para controle de loop
		
// inicialização de variáveis	
	
	conteudo=inicializar();
	chave=inicializar();
	int menu=20; //controle do loop de menu

//personalização de design

	system("color f5");

//menu
    
	for(;menu!=0;){

//exibiação e leitura de menu

	printf("\n---------------------------------------------------");
	printf("\n-------------------Criptografia--------------------");
	printf("\n---------------------------------------------------\n");
	
	printf("1- Criptografar Texto\n");
	printf("2- Descriptografar Texto\n");
	printf("0- Sair\n");

	printf("\n---------------------------------------------------\n");
	printf("Digite a opção desejada:");
	scanf("%d",&menu);
	fflush(stdin);

	//controle de menu
	switch(menu){
		
	case 1:
	
		conteudo = inicializar();
		
	    printf("\nDigite o texto a ser criptografado:");
	    
		for(;caractere!=13;){ // ler o texto por caractere, incluir o caracter na pilha e parar a leitura pela tecla enter = 13 - código ASCII
			
			caractere=getche(); // getche - lê um caractere
			if(caractere==8) // remove a letra em caso de backspace
			conteudo=pop(conteudo);
			else
			conteudo=push(conteudo,caractere); // empilha caractere lido
		
		}
		
		fflush(stdin);
				
		max = tamanho(conteudo); // calcula o número máximo de níveis
		
		printf("\nDigite a quantidade de níveis de criptografia entre 2 e %d: ",max-1);
		scanf("%d",&nivel);
		fflush(stdin);
		
		if(nivel<2||nivel>max){ // verifica se a quantidade de níveis escolhidos atende o permitido, caso contrário reinicia a aplicação
				
			printf("\nQuantidade não permitida!");
			conteudo = inicializar();
			break;
			
		}
		
		printf("\nChave de acesso: ");
		
		chave=gerarChave(nivel);
		
		divisao = (max-1) / nivel;
		
		conteudo = inverte(conteudo); // inverte a pilha para atender a ordem original do texto



		pilhas = inicializarPilhas();
		
		printf("\nTexto: ");
// cria o número de pilhas referentes a escolha do usuário, utilizando lista.
				
		for(x=1;x<nivel;x++){
		
			pilhas = inserirPilhas(pilhas);	
		}

        temporario = inicializar(); 

// insere a quantidade dividida dos caracteres chave por chave 
                                                                                  
		for(y=1;chave!=NULL;chave=chave->proximo,y++){
			
// procura pela pilha referente a primeira chave e assim por diante
			
			for(auxiliarPilhas=pilhas, x=1; auxiliarPilhas!=NULL ; x++, auxiliarPilhas=auxiliarPilhas->proximo){
		
// empilha os caracteres na pilha referente a sequência das chaves			
				if (chave->caractere==x){
		
					if(y==nivel){
		
						for(;conteudo!=NULL;){  // caso seja a ultima chave, empilha todos os caracteres restante, em caso de divisões não inteiras
		
							temporario = push(temporario,conteudo->caractere);
							conteudo=pop(conteudo);
						}
				
					} else {
		
						for(z = 0; z<divisao; z++){
						
							temporario = push(temporario,conteudo->caractere);
							conteudo=pop(conteudo);
											
						}
					}			
			
	
				temporario = inverte(temporario); // inverte a pilha da chave para bater com a ordem de desimpilhamento na desemcriptação
				
				auxiliarPilhas->pilha=temporario; // guarda na lista a locação da pilha referente a chave
				
				temporario = inicializar(); // reinicia a pilha temporária
		
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
		
		
		printf("\nDigite os %d números da chave separador por enter:\n\n",nivel);

// empilha a chave informada	
	
		for(x=0;x<nivel;x++){
	
			scanf ("%d",&senha);
			chave = push(chave,senha);
			
		}
				
		fflush(stdin);
		
		chave = inverte(chave); // inverte a chave para coincidir com a ordem de digitação
		
		printf("\nChave informada:");
	
		imprimir(chave);
		
		printf("\nConteúdo desencriptado: ");
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
	
	default: printf("\nOpção inválida!\n\n");
		
  	}
  	
	caractere='\n'; // limpa a variável caractere
	
	system("pause");
	system("cls");
	}
	
return 0;

}

//função para inicialização de lista ou pilha
	Texto *inicializar(){
		
		return NULL;
		
	}

//função para inicialização de lista ou pilha
	Pilhas *inicializarPilhas(){
		
		return NULL;
		
	}
	
//função para empilhar
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

//função para retornar o tamanho de uma pilha ou lista
	int tamanho(Texto *texto){
	
		int tamanho=0;
		Texto *auxiliar;
		
		for(auxiliar=texto;auxiliar!=NULL;auxiliar=auxiliar->proximo,tamanho++);
		
		return tamanho;
	
	}

//função para gerar a chave de acesso

	Texto* gerarChave(int nivel){

	Texto *chave;
	chave = inicializar();
	
	int aleatorio;
	
	
	for(;nivel>tamanho(chave);){
		
		aleatorio = rand() % nivel+1; // gerar números aleatórios entre o intervalo da chave
	
		if(consultaChave(aleatorio,chave)==1&&aleatorio!=0) // elimina chaves recorentes ou zero
		
			chave = push(chave,aleatorio);
	
	}
	
	chave = inverte(chave); // inverte para coincidir com a ordem de digitação
	
	imprimir(chave);
	
	return chave;
	
	}

//função para consultar se o valor foi inserido na chave

	bool consultaChave(int numero, Texto *texto){
	
	Texto *auxiliar;	

	for(auxiliar=texto;auxiliar!=NULL;auxiliar=auxiliar->proximo){
	
		if (auxiliar->caractere==numero)
			
			return 0; // retorna zero se o número já foi inserido
	
	}
	
	return 1; // retorna um se o número não foi inserido
	
	}
	
// função para imprimir uma lista

	void imprimir(Texto *texto){
	
	Texto *auxiliar;
	
    for(auxiliar=texto;auxiliar!=NULL;auxiliar=auxiliar->proximo)
    	
		printf("%d ",auxiliar->caractere);
	
	printf("\n");
	
	}

// função para inverter pilhas 

	Texto *inverte(Texto *texto){
	
	Texto *auxiliar;
	Texto *revertido;
	
	revertido = inicializar();
	
	for(auxiliar=texto;auxiliar!=NULL;auxiliar=auxiliar->proximo){
		
	revertido=push(revertido,auxiliar->caractere);
	
	}
	
	return revertido;
	
	}

// função para inserir espaços para armazenar a posição inicial de pilhas em uma fila
	
	Pilhas *inserirPilhas(Pilhas *pilhas){
	
	Pilhas *novo = (Pilhas*) malloc(sizeof(Pilhas));
	
	novo->proximo = pilhas;
	
	pilhas = novo;
	
	return novo;
	
	}
