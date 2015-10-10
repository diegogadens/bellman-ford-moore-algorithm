#include "stdafx.h"
#include "conio.h"

typedef struct no{
	int custo;
	int anterior;
}No;
/*
* Estrutura de dados utilizada para representar o grafo, onde "custo" guardar� o valor
* do  menor  caminho encontrado at� o n� em  quest�o, "anterior" guardar� a refer�ncia
* (�ndice) do n� imediatamente anterior  a  cada um dos n�s do grafo,  ou -1 para o n� 
* inicial.
*/

No GRAFO[10]; //Vetor de estruturas do tipo "No".
int custo_anterior[10];//Vetor utilizado para armazenar os custos dos nos na itera��o
					   //anterior a que estiver a execu��o do programa.
int MATRIZ[10][10];// Matriz para representa��o do grafo.
int INFINITO = 32766;
int NULO = -32766;
int qtd_nos, it, ciclo_negativo;


//Prot�tipos das fun��es utilizadas neste algoritmo.
//Suas explica��es detalhadas encontram nas pr�prias fun��es, logo ap�s a fun��o main()
void inicializa_variaveis();
void passo1();
int min(int x, int y);
int menor_caminho(int no);
int parada();
void gera_grafo(int a, int b, int c);
void imprime_Menor_Caminho();


void main()
{
/* Esta � a fun��o principal do algoritmo, sua fun��o � apenas controlar a chamada das
*  fun��es espec�ficas de sele��o e c�lculo para defini��o do menor caminho do grafo.
*  Al�m  deste  controle, �  aqui onde as informa��es, como quantidade e custo dos n�s
*  do grafo s�o inseridas.
*/
	

	//chamada � fun��o de inicializa��o de todas as vari�veis do grafo
	//EQUIVALENTE AO PASSO 0 - Inicializa��o das vari�veis.
	inicializa_variaveis();



	/*No trecho de c�digo abaixo, s�o solicitadas ao usu�rio as informa��es � respeito
	* do grafo, o  usu�rio deve inserir uma linha contendo tr�s inteiros separados por 
	* um  espa�o,  onde  o  primeiro  item  corresponde  ao  n� origem, o segundo item 
	* corresponde ao  n� destino, e o terceiro item corresponde a� custo do arco entre
	* estes dois n�s. Para terminar a inser��o deve-se inserir a linha 0 0 0.
	*/
	int k, l, m;
	printf("\n\nInsira os dados do grafo, no formato x y z onde: \n"); 
	printf("x= origem, y=destino, z=custo. Insira 0 0 0 para finalizar. \n\n");
	do
	{
		
		scanf("%d %d %d", &k, &l, &m);
			gera_grafo(k, l, m);
			// chama a  fun��o que insere os dados na matriz que representa o grafo, 
			// tantas vezes quantas forem o n�mero de arcos (este n�mero dobra se os
			// arcos forem n�o direcionados.)
	}while ((k + l) != 0);

	
	
	/*Terminada a inser��o dos dados na matriz, iniciam-se  os c�lculos para encontrar 
	* o menor  caminho,  �  realizado  um la�o, que se repete enquanto as condi��es de 
	* parada  n�o forem  atendidas, a cada itera��o todos os n�s s�o  visitados,  e  �
	* feita a compara��o do seu valor na  itera��o  atual  com  o  valor  na  itera��o
	* anterior, e com base nisto as atualiza��es s�o feitas. Este processo � explicado
	* em detalhes nas fun��es espec�ficas.
	*/
	do
	{
		passo1();	
	}while (parada() != 1);


	
	/*
	* Se n�o foi identificado um ciclo negativo, ent�o a impress�o dos resultados �  
	* realizada, sen�o o programa � encerrado, e a mensagem de que existe um  ciclo 
	* negativo � exibida.
	*/
	if (ciclo_negativo != 1)
	{
		imprime_Menor_Caminho();
	}
	else
		printf("Existe um circuito com custo negativo\n\n");

/*
* A fun��o getch() serve apenas para pausar o programa, para que  o  usu�rio 
* possa ver os resultados, sem que ele se encerre automaticamente.
*/
getch();
}


void inicializa_variaveis()
{
//EQUIVALENTE AO PASSO 0 - Inicializa��o das vari�veis//
	
	printf("Insira a quantidade de nos: \n");
		scanf("%d", &qtd_nos);
	int i, j;
	for (i=0; i<10; i++)
	  for(j=1; j<10; j++)
	    MATRIZ[i][j] = NULO;
		/*Preenche a Matriz com o valor NULO, e n�o -1, pois neste algoritmo, os custos
		* dos arcos podem ser negativos.
		*/

	for (i=0; i<10; i++)
	{	
		custo_anterior[i] = INFINITO;
		/* Este vetor armazena os custos dos vertices sempre referentes � itera��o
		* passada � atual  de  execu��o  do c�digo, e por meio do acesso a ele s�o 
		* feitas as compara��es.
		*/
		GRAFO[i].anterior = -1;
		//Atribuindo -1 para o antecessor de todos os n�s do grafo, indicamos que ainda
		//n�o foi encontrado o menor camiho para nenhum destes n�s.
		GRAFO[i].custo = INFINITO;
		//todos os n�s recebem custo infinito.
	}
	/*Selecionamos  o  n�  origem,  e  definimos  que o custo m�nimo para ele � 0(zero)
	* pois  ele  �  o  primeiro  n�  de  todos  os  caminhos. Como ele j� tem seu valor 
	* m�nimo  definido, guardamos este valor tamb�m no vetor  que  armazena  os  custos
	* anteriores.
	*/
	GRAFO[0].custo = 0;
	custo_anterior[0] = 0;	
	it = 0;
}


void passo1()
{
/*
* Esta �  a  fun��o  respons�vel  por  fazer  a  visita  a  todos  os  n�s, e poss�vel
* atualiza��o de seus valores,  antes  de  atualizar  um  valor, este � salvo no vetor 
* que armazena os custos da  itera��o  anterior,  ap�s isso s�o chamadas duas fun��es,
* uma sendo par�metro de outra, a fim de encontrar o menor caminho para um determinado
* n�. Para cada n� do grafo,  s�o  verificados  todos  os  seus  adjacentes,  e  ent�o 
* comparados os seus valores atuais e anteriores para realizar as atualiza��es.
* 
*/

	int i, j;
	
	for (i = 1; i < 10; i++)
	{
		custo_anterior[i] = GRAFO[i].custo;
		
		/*Chamada � fun��o min(), com 2 par�metros, sendo o primeiro o custo do v�rtice
		* na   itera��o   passada,   e   o  segundo  par�metro  �  o  retorno da fun��o 
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
* Esta � uma fun��o muito importante dentro deste algoritmo, ela recebe por par�metro
* a referencia para um n�, e ent�o analisa a coluna inteira, da Matriz, que correspon
* de a este n� com o objetivo de encontrar o menor n� adjacente  ao  n� do par�metro, 
* com isso a fun��o que fez as chamadas ter�  os  par�metro  para efetuar os calculos
* � efetuada a soma do custo anterior mais o  custo do arco para definir qual o menor
* caminho poss�vel, e � esta soma que ser� retornada. O motivo do uso desta fun��o, �
* o de que cada n� pode possuir um n�mero diferente de adjacencias, portanto a fun��o
* mais acima ( min(,) ), poderia ter diversos n�meros  de  par�metros, para  resolver 
* este problema, esta fun��o faz esta busca pelo menor poss�vel, e retorna este valor
* possibilitando assim que a fun��o min() trabalhe sempre com 2 par�metros.
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
//EQUIVALENTE AO PASSO 2 - Crit�rio de Parada//
/*
* Esta fun��o � a respons�vel por fazer o programa terminar, tendo ele conseguido
* alcan�ar o seu resultado ou n�o. A primeira condi��o avaliada � a compara��o dos
* custos de todos os vertices na itera��o ATUAL e ANTERIOR, se todos os valores de 
* todos os vertices forem iguais, ent�o o algoritmo pode ser finalizado, pois o cami-
* nho m�nimo j� foi encontrado. Sen�o � verificado se o n�mero de itera��es � menor 
* que a quantidade de n�s menos 1, se sim, o programa continua executando, sen�o foi
* detectado um ciclo com custo negativo e o programa � encerrado.
*/


int i, result;
result = 1;
	
	for (i=0; i<10; i++)
	{	
		if(GRAFO[i].custo == custo_anterior[i])
		//Se todos os valores estiverem com seus correspondentes iguais, ent�o a vari�vel
		//result fica com o valor 1, e o algoritmo encerra.
			result = result * 1;
		else
			result = result * 0;
	}

	if (result == 1)
		//Se result vale 1, ent�o o caminho m�nimo foi encontrado.
		return 1;
	else
	{
		//Sen�o, se a itera��o for menor que o n� de n�s menos 1, o programa continua em
		//execu��o.
		if (it <= (qtd_nos -1))
			return 0;
		else
		{	
			//Sen�o, foi detectado um ciclo negativo e o programa � encerrado.
			ciclo_negativo = 1;
			return 1;
		}
	}
}


void gera_grafo(int a, int b, int c)
{
/* Esta  fun��o  recebe  os  valores da entrada  do usu�rio e os  coloca  na  matriz  que 
* representa o grafo, sendo linha=origem, coluna=destino e intersec��o=custo.
*/
	MATRIZ[a][b] = c;
}

void imprime_Menor_Caminho()
{ 
/*Esta fun��o serve para imprimir o resultado encontrado para os menores caminhos do grafo
*ela imprime os custos m�nimos de cada n�, bem como o caminho que deve ser percorrido para
*alcan�ar estes n�s.  A fun��o imprime o caminho da seguinte maneira, para cada vertice, �
*� impresso seu antecessor e a vari�vel respons�vel por esta informa��o recebe o valor  do
*pr�ximo antecessor, fazendo isto dentro de uma  estrutura  de  repeti��o,  at�  que  seja
*encontrado  o  antecessor  -1,  o  que significa  que  o  n�  inicial  foi  alcan�ado,  e
*portanto  o  caminho  est�  completo. O caminho deve ser lido da direita para a esquerda.
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