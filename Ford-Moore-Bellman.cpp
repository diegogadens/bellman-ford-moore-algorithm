#include "stdafx.h"
#include "conio.h"

typedef struct no{
	int custo;
	int anterior;
}No;
/*
* Estrutura de dados utilizada para representar o grafo, onde "custo" guardará o valor
* do  menor  caminho encontrado até o nó em  questão, "anterior" guardará a referência
* (índice) do nó imediatamente anterior  a  cada um dos nós do grafo,  ou -1 para o nó 
* inicial.
*/

No GRAFO[10]; //Vetor de estruturas do tipo "No".
int custo_anterior[10];//Vetor utilizado para armazenar os custos dos nos na iteração
					   //anterior a que estiver a execução do programa.
int MATRIZ[10][10];// Matriz para representação do grafo.
int INFINITO = 32766;
int NULO = -32766;
int qtd_nos, it, ciclo_negativo;


//Protótipos das funções utilizadas neste algoritmo.
//Suas explicações detalhadas encontram nas próprias funções, logo após a função main()
void inicializa_variaveis();
void passo1();
int min(int x, int y);
int menor_caminho(int no);
int parada();
void gera_grafo(int a, int b, int c);
void imprime_Menor_Caminho();


void main()
{
/* Esta é a função principal do algoritmo, sua função é apenas controlar a chamada das
*  funções específicas de seleção e cálculo para definição do menor caminho do grafo.
*  Além  deste  controle, é  aqui onde as informações, como quantidade e custo dos nós
*  do grafo são inseridas.
*/
	

	//chamada à função de inicialização de todas as variáveis do grafo
	//EQUIVALENTE AO PASSO 0 - Inicialização das variáveis.
	inicializa_variaveis();



	/*No trecho de código abaixo, são solicitadas ao usuário as informações à respeito
	* do grafo, o  usuário deve inserir uma linha contendo três inteiros separados por 
	* um  espaço,  onde  o  primeiro  item  corresponde  ao  nó origem, o segundo item 
	* corresponde ao  nó destino, e o terceiro item corresponde aó custo do arco entre
	* estes dois nós. Para terminar a inserção deve-se inserir a linha 0 0 0.
	*/
	int k, l, m;
	printf("\n\nInsira os dados do grafo, no formato x y z onde: \n"); 
	printf("x= origem, y=destino, z=custo. Insira 0 0 0 para finalizar. \n\n");
	do
	{
		
		scanf("%d %d %d", &k, &l, &m);
			gera_grafo(k, l, m);
			// chama a  função que insere os dados na matriz que representa o grafo, 
			// tantas vezes quantas forem o número de arcos (este número dobra se os
			// arcos forem não direcionados.)
	}while ((k + l) != 0);

	
	
	/*Terminada a inserção dos dados na matriz, iniciam-se  os cálculos para encontrar 
	* o menor  caminho,  é  realizado  um laço, que se repete enquanto as condições de 
	* parada  não forem  atendidas, a cada iteração todos os nós são  visitados,  e  é
	* feita a comparação do seu valor na  iteração  atual  com  o  valor  na  iteração
	* anterior, e com base nisto as atualizações são feitas. Este processo é explicado
	* em detalhes nas funções específicas.
	*/
	do
	{
		passo1();	
	}while (parada() != 1);


	
	/*
	* Se não foi identificado um ciclo negativo, então a impressão dos resultados é  
	* realizada, senão o programa é encerrado, e a mensagem de que existe um  ciclo 
	* negativo é exibida.
	*/
	if (ciclo_negativo != 1)
	{
		imprime_Menor_Caminho();
	}
	else
		printf("Existe um circuito com custo negativo\n\n");

/*
* A função getch() serve apenas para pausar o programa, para que  o  usuário 
* possa ver os resultados, sem que ele se encerre automaticamente.
*/
getch();
}


void inicializa_variaveis()
{
//EQUIVALENTE AO PASSO 0 - Inicialização das variáveis//
	
	printf("Insira a quantidade de nos: \n");
		scanf("%d", &qtd_nos);
	int i, j;
	for (i=0; i<10; i++)
	  for(j=1; j<10; j++)
	    MATRIZ[i][j] = NULO;
		/*Preenche a Matriz com o valor NULO, e não -1, pois neste algoritmo, os custos
		* dos arcos podem ser negativos.
		*/

	for (i=0; i<10; i++)
	{	
		custo_anterior[i] = INFINITO;
		/* Este vetor armazena os custos dos vertices sempre referentes à iteração
		* passada à atual  de  execução  do código, e por meio do acesso a ele são 
		* feitas as comparações.
		*/
		GRAFO[i].anterior = -1;
		//Atribuindo -1 para o antecessor de todos os nós do grafo, indicamos que ainda
		//não foi encontrado o menor camiho para nenhum destes nós.
		GRAFO[i].custo = INFINITO;
		//todos os nós recebem custo infinito.
	}
	/*Selecionamos  o  nó  origem,  e  definimos  que o custo mínimo para ele é 0(zero)
	* pois  ele  é  o  primeiro  nó  de  todos  os  caminhos. Como ele já tem seu valor 
	* mínimo  definido, guardamos este valor também no vetor  que  armazena  os  custos
	* anteriores.
	*/
	GRAFO[0].custo = 0;
	custo_anterior[0] = 0;	
	it = 0;
}


void passo1()
{
/*
* Esta é  a  função  responsável  por  fazer  a  visita  a  todos  os  nós, e possível
* atualização de seus valores,  antes  de  atualizar  um  valor, este é salvo no vetor 
* que armazena os custos da  iteração  anterior,  após isso são chamadas duas funções,
* uma sendo parâmetro de outra, a fim de encontrar o menor caminho para um determinado
* nó. Para cada nó do grafo,  são  verificados  todos  os  seus  adjacentes,  e  então 
* comparados os seus valores atuais e anteriores para realizar as atualizações.
* 
*/

	int i, j;
	
	for (i = 1; i < 10; i++)
	{
		custo_anterior[i] = GRAFO[i].custo;
		
		/*Chamada à função min(), com 2 parâmetros, sendo o primeiro o custo do vértice
		* na   iteração   passada,   e   o  segundo  parâmetro  é  o  retorno da função 
		* menor_caminho(), explicada logo abaixo.
		*/
		GRAFO[i].custo = min(custo_anterior[i], menor_caminho(i));
	}

	it++;
}
	

int min(int x, int y)
{
	//Retorna o menor entre 2 valores recebidos.
	if (x < y)
		return x;
	else
		return y;
}


int menor_caminho(int no)
{
/*
* Esta é uma função muito importante dentro deste algoritmo, ela recebe por parâmetro
* a referencia para um nó, e então analisa a coluna inteira, da Matriz, que correspon
* de a este nó com o objetivo de encontrar o menor nó adjacente  ao  nó do parâmetro, 
* com isso a função que fez as chamadas terá  os  parâmetro  para efetuar os calculos
* É efetuada a soma do custo anterior mais o  custo do arco para definir qual o menor
* caminho possível, e é esta soma que será retornada. O motivo do uso desta função, é
* o de que cada nó pode possuir um número diferente de adjacencias, portanto a função
* mais acima ( min(,) ), poderia ter diversos números  de  parâmetros, para  resolver 
* este problema, esta função faz esta busca pelo menor possível, e retorna este valor
* possibilitando assim que a função min() trabalhe sempre com 2 parâmetros.
*/
int i, menor;
menor = INFINITO;

	for (i = 0; i<10; i++)
	{
		if (MATRIZ[i][no] != NULO)
		{
			if (custo_anterior[i] + MATRIZ[i][no] < menor)
			{
				menor = (custo_anterior[i] + MATRIZ[i][no]);
				GRAFO[no].anterior = i;
			}
		}
	}

return menor;

}


int parada()
{
//EQUIVALENTE AO PASSO 2 - Critério de Parada//
/*
* Esta função é a responsável por fazer o programa terminar, tendo ele conseguido
* alcançar o seu resultado ou não. A primeira condição avaliada é a comparação dos
* custos de todos os vertices na iteração ATUAL e ANTERIOR, se todos os valores de 
* todos os vertices forem iguais, então o algoritmo pode ser finalizado, pois o cami-
* nho mínimo já foi encontrado. Senão é verificado se o número de iterações é menor 
* que a quantidade de nós menos 1, se sim, o programa continua executando, senão foi
* detectado um ciclo com custo negativo e o programa é encerrado.
*/


int i, result;
result = 1;
	
	for (i=0; i<10; i++)
	{	
		if(GRAFO[i].custo == custo_anterior[i])
		//Se todos os valores estiverem com seus correspondentes iguais, então a variável
		//result fica com o valor 1, e o algoritmo encerra.
			result = result * 1;
		else
			result = result * 0;
	}

	if (result == 1)
		//Se result vale 1, então o caminho mínimo foi encontrado.
		return 1;
	else
	{
		//Senão, se a iteração for menor que o n° de nós menos 1, o programa continua em
		//execução.
		if (it <= (qtd_nos -1))
			return 0;
		else
		{	
			//Senão, foi detectado um ciclo negativo e o programa é encerrado.
			ciclo_negativo = 1;
			return 1;
		}
	}
}


void gera_grafo(int a, int b, int c)
{
/* Esta  função  recebe  os  valores da entrada  do usuário e os  coloca  na  matriz  que 
* representa o grafo, sendo linha=origem, coluna=destino e intersecção=custo.
*/
	MATRIZ[a][b] = c;
}

void imprime_Menor_Caminho()
{ 
/*Esta função serve para imprimir o resultado encontrado para os menores caminhos do grafo
*ela imprime os custos mínimos de cada nó, bem como o caminho que deve ser percorrido para
*alcançar estes nós.  A função imprime o caminho da seguinte maneira, para cada vertice, é
*é impresso seu antecessor e a variável responsável por esta informação recebe o valor  do
*próximo antecessor, fazendo isto dentro de uma  estrutura  de  repetição,  até  que  seja
*encontrado  o  antecessor  -1,  o  que significa  que  o  nó  inicial  foi  alcançado,  e
*portanto  o  caminho  está  completo. O caminho deve ser lido da direita para a esquerda.
*/
	printf("\n\n");
	int i;
	for (i =0; i<qtd_nos; i++)
	{
		int dest = i;
		printf("Custo minimo ate o no %d: %d    Caminho: ", dest, GRAFO[dest].custo);
		do	
		{
			printf("%d ", dest);
			dest = GRAFO[dest].anterior;
		}while (dest != -1);
		printf("\n");
	}
}