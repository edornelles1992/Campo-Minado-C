//-------------------------------------------------------------------- 
// Estrutura básica para o desenvolvimento de um jogo de campo minado
//--------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>

//--------------------------------------------
//Struct básica para cada célula do tabuleiro
//--------------------------------------------
struct celula {
	char imprime; // Membro que deverá conter o valor a ser impresso da célula
	int valor;    // Membro que deverá conter o valor de controle da célula
};

//--------------------------------------------
// (2) Escreva aqui a rotina responsável por
// criar bombas no tabuleiro de forma
// aleatória
//--------------------------------------------
void gera_bombas(struct celula *tabuleiro, int lado, int num_bombas){

	int x;
	srand(time(NULL));
	for(x=0;x<num_bombas;x++){
		int num;		
		num = rand() % (lado*lado);
		if (tabuleiro[num].valor==-1){ //garante que nao ira por uma bomba no mesmo local
		x--;
		continue;
		}
		tabuleiro[num].valor = -1;
	}
	

}

//--------------------------------------------
// (3) Escreva aqui a função responsável por
// ler o valor de uma casa vizinha
//--------------------------------------------
int le_vizinho(int x, int y, int posicao, int controle, struct celula *tabuleiro, int lado){
// variaveis x e y validam para qual lado é o vizinho para fazer a verificação do valor dele
int vizinho;
int valor;
char simbolo;	
if (x==0){ //campos da segundo coluna '0'
 	
	 if (y==1){ //meio acima		
 			valor = tabuleiro[posicao-lado].valor;
			simbolo =  tabuleiro[posicao-lado].imprime;
		  }
		
	 if (y==-1)  {//meio abaixo			
 			valor = tabuleiro[posicao+lado].valor;
			simbolo =  tabuleiro[posicao+lado].imprime;
		     }
			

	 }



else if (x==1){//campos da terceira coluna
	if (y==0){ //campo central
			valor = tabuleiro[posicao+1].valor;
			simbolo =  tabuleiro[posicao+1].imprime;
		 }
	else if (y==1){ //direita acima		 
 			valor = tabuleiro[posicao-(lado-1)].valor;
			simbolo =  tabuleiro[posicao-(lado-1)].imprime;
		      } 
	else if (y==-1) { //direita abaixo	
 			valor = tabuleiro[posicao+(lado+1)].valor;
			simbolo =  tabuleiro[posicao+(lado+1)].imprime;
		 	}



}
else {//campos da primeira coluna
	if (y==0){ //campo central
		   valor = tabuleiro[posicao-1].valor;
		   simbolo =  tabuleiro[posicao-1].imprime;
		 }
	else if (y==1){ //esquerda acima		 
 			valor = tabuleiro[posicao-(lado+1)].valor;
			simbolo =  tabuleiro[posicao-(lado+1)].imprime;
		      } 
	else if (y==-1){ //esquerda abaixo	
 			valor = tabuleiro[posicao+(lado-1)].valor;
			simbolo =  tabuleiro[posicao+(lado-1)].imprime;
		       }



}

if (controle==0){
	return valor;	
		}
 else{
	return simbolo;
     }
	
}

//--------------------------------------------
// (4) Escreva aqui a rotina responsável por
// calcular os valores de controle de todas
// as células que não contem uma bomba
//--------------------------------------------
void calcula_celulas(struct celula *tabuleiro, int lado){
// valida a localização da celula para verificar os vizinhos possiveis (dentro do campo)
// de ter alguma bomba
int x;	
	for (x=0;x<lado*lado;x++){
 	if (tabuleiro[x].valor==-1){ continue;}
	int cont=0;
		if (x==0){ //campo acima a esquerda
			if (le_vizinho(1, 0,  x,  0, tabuleiro, lado)==-1){ cont++; }
			if (le_vizinho(0, -1,  x,  0, tabuleiro, lado)==-1){ cont++; }
			if (le_vizinho(1, -1,  x,  0, tabuleiro, lado)==-1){ cont++; }
				
	}   else if(x==lado-1){ //campo acima a direita
			if (le_vizinho(-1, 0,  x,  0, tabuleiro, lado)==-1){ cont++; }
			if (le_vizinho(-1, -1,  x,  0, tabuleiro, lado)==-1){ cont++; }
			if (le_vizinho(0, -1,  x,  0, tabuleiro, lado)==-1){ cont++; }		
	}
	else if(x==(lado*lado)-lado){ //campo abaixo a esquerda
			if (le_vizinho(0, 1,  x,  0, tabuleiro, lado)==-1){ cont++; }
			if (le_vizinho(1, 1,  x,  0, tabuleiro, lado)==-1){ cont++; }
			if (le_vizinho(1, 0,  x,  0, tabuleiro, lado)==-1){ cont++; }		
	}
	else if(x==(lado*lado)-1){ //campo abaixo a direita
			if (le_vizinho(-1, 1,  x,  0, tabuleiro, lado)==-1){ cont++; }
			if (le_vizinho(0, 1,  x,  0, tabuleiro, lado)==-1){ cont++; }
			if (le_vizinho(-1, 0,  x,  0, tabuleiro, lado)==-1){ cont++; }		
	}
	else if (x>0&&x<lado){ //primeira linha
			if (le_vizinho(-1, 0,  x,  0, tabuleiro, lado)==-1){ cont++; }
			if (le_vizinho(-1, -1,  x,  0, tabuleiro, lado)==-1){ cont++; }
			if (le_vizinho(0, -1,  x,  0, tabuleiro, lado)==-1){ cont++; }	
			if (le_vizinho(1, -1,  x,  0, tabuleiro, lado)==-1){ cont++; }
			if (le_vizinho(1, 0,  x,  0, tabuleiro, lado)==-1){ cont++; }	
	} 
	else if ((x>(lado*lado)-lado)&& x<(lado*lado)){//ultima linha
			if (le_vizinho(-1, 0,  x,  0, tabuleiro, lado)==-1){ cont++; }
			if (le_vizinho(-1, 1,  x,  0, tabuleiro, lado)==-1){ cont++; }
			if (le_vizinho(0, 1,  x,  0, tabuleiro, lado)==-1){ cont++; }	
			if (le_vizinho(1, 1,  x,  0, tabuleiro, lado)==-1){ cont++; }
			if (le_vizinho(1, 0,  x,  0, tabuleiro, lado)==-1){ cont++; }	

	} else if((x+1)%lado==0 ) { //ultima coluna
			if (le_vizinho(0, 1,  x,  0, tabuleiro, lado)==-1){ cont++; }
			if (le_vizinho(-1, 1,  x,  0, tabuleiro, lado)==-1){ cont++; }
			if (le_vizinho(-1, 0,  x,  0, tabuleiro, lado)==-1){ cont++; }	
			if (le_vizinho(-1,-1,  x,  0, tabuleiro, lado)==-1){ cont++; }
			if (le_vizinho(0, -1,  x,  0, tabuleiro, lado)==-1){ cont++; }	


	} else if(x%lado==0){ //primeira coluna
			if (le_vizinho(0, 1,  x,  0, tabuleiro, lado)==-1){ cont++; }
			if (le_vizinho(1, 1,  x,  0, tabuleiro, lado)==-1){ cont++; }
			if (le_vizinho(1, 0,  x,  0, tabuleiro, lado)==-1){ cont++; }	
			if (le_vizinho(1,-1,  x,  0, tabuleiro, lado)==-1){ cont++; }
			if (le_vizinho(0, -1,  x,  0, tabuleiro, lado)==-1){ cont++; }

	}
		else{//demais campos no meio da matriz

			
			if (le_vizinho(0, 1,  x,  0, tabuleiro, lado)==-1){ cont++; }
			if (le_vizinho(1, 1,  x,  0, tabuleiro, lado)==-1){ cont++; }
			if (le_vizinho(1, 0,  x,  0, tabuleiro, lado)==-1){ cont++; }	
			if (le_vizinho(1,-1,  x,  0, tabuleiro, lado)==-1){ cont++; }
			if (le_vizinho(0, -1,  x,  0, tabuleiro, lado)==-1){ cont++; }
			if (le_vizinho(-1, -1,  x,  0, tabuleiro, lado)==-1){ cont++; }
			if (le_vizinho(-1, 0,  x,  0, tabuleiro, lado)==-1){ cont++; }
			if (le_vizinho(-1, 1,  x,  0, tabuleiro, lado)==-1){ cont++; }

	}

	

	tabuleiro[x].valor = cont; //salva a qtidade de bombas em celulas vizinhas 
	}


}

//--------------------------------------------
// Rotina para impressão do tabuleiro
// mostrando valores invisíveis para o
// jogador
//--------------------------------------------
void imprime_tabuleiro_debug(struct celula *tabuleiro, int lado){
	int i, celulas=lado*lado;
	//Imprime índices do eixo x
	printf("    ");
	for(i=0;i<lado;i++){
		printf(" %2d",i);
	}
	//Imprime barra para separar o tabuleiro
	printf("\n   ----");
	for(i=1;i<lado;i++){
		printf("---");
	}
	printf("\n");
	i=0;
	//Imprime todas
	while(celulas--){
		if(i%lado==0) printf("%2d |",i/lado);{
		if(tabuleiro->valor==-1){
		printf("  *");
		} 
		else if(tabuleiro->valor==0){
		printf("   ");
		} 
		else{
		printf(" %2d",tabuleiro->valor);
	}
}
		tabuleiro++;
		if(++i%lado==0) printf("\n");
	}
	printf("\n");
}

//--------------------------------------------
// (5) Escreva aqui a rotina responsável por
// imprimir o tabuleiro, mostrando apenas os
// caracteres de impressão para o jogador
//--------------------------------------------
void imprime_tabuleiro(struct celula *tabuleiro, int lado){
	int i, celulas=lado*lado;
	//Imprime índices do eixo x
	printf("    ");
	for(i=0;i<lado;i++){
		printf(" %2d",i);
	}
	//Imprime barra para separar o tabuleiro
	printf("\n   ----");
	for(i=1;i<lado;i++){
		printf("---");
	}
	printf("\n");
	i=0;
	
	while(celulas--){
		if(i%lado==0) printf("%2d |",i/lado); //detecta nova linha
		
		printf("  %c",tabuleiro->imprime);
		tabuleiro++;
		if(++i%lado==0) printf("\n");
	}
	printf("\n");
}

//--------------------------------------------
// (6) Escreva aqui a rotina responsável por
// abrir todas as células até as bordas de
// células próximas a bombas
//--------------------------------------------
//Abre todas células até as bordas de células próximas a bombas
void expande_zero(int celula, struct celula *tabuleiro, int lado){
//função recursiva, adicionado o parametro celula, que recebe a  posição da celula atual
//para começar a expandir. Vai caminhando nas celulas vizinhas e marcando como 'visitadas'
// e abrindo elas até chegar em uma celula com valor (caso base).
	if (celula<0||celula>(lado*lado)-1) {return;} //verifica se o indice n foi pra fora do array
	if (tabuleiro[celula].imprime==' ') {return;} //valida se a casa ja foi visitada
	if (tabuleiro[celula].valor==-1) {return;} //valida se n é uma bomba
	
	 if (tabuleiro[celula].valor==0){ //valida se não tem bombas ao redor	

		tabuleiro[celula].imprime=' '; //altera campo

	   if(celula%lado==0){ //primeira coluna /acima/acima-direita/meio-direita/baixo/baixo direita
		expande_zero(celula-lado, tabuleiro,  lado);
		expande_zero(celula-(lado-1), tabuleiro,  lado);
		expande_zero(celula+1, tabuleiro, lado); //caminha pra direita
		expande_zero(celula+(lado+1), tabuleiro,  lado);
		expande_zero(celula+lado, tabuleiro,  lado);
	   } else if ((celula+1)%lado==0 ){//ultima coluna /acima/acima-esquerda/esquerda/baixo esquerda/baixo
		expande_zero(celula-lado, tabuleiro,  lado);
		expande_zero(celula-(lado+1), tabuleiro, lado);
		expande_zero(celula-1, tabuleiro,  lado);
		expande_zero(celula+(lado-1), tabuleiro,  lado);
		expande_zero(celula+lado, tabuleiro,  lado);
	     }
	
	   else{ //demais campos 
		expande_zero(celula+1, tabuleiro, lado); //caminha pra direita
		expande_zero(celula-1, tabuleiro,  lado); //caminha esquerda
		expande_zero(celula-lado, tabuleiro,  lado); //caminha para cima
		expande_zero(celula+lado, tabuleiro,  lado);	//caminha pra baixo
		expande_zero(celula-(lado+1), tabuleiro, lado);// caminha pra diagonal superior esquerda	
		expande_zero(celula-(lado-1), tabuleiro,  lado);// caminha pra diagonal superior direita
		expande_zero(celula+(lado-1), tabuleiro,  lado);// caminha pra diagonal inferior esquerda
		expande_zero(celula+(lado+1), tabuleiro,  lado); //diagonal inferior a direita
	   }

	}
	if (tabuleiro[celula].valor>0){ //celula fronteira (com valor >0)
			tabuleiro[celula].imprime = tabuleiro[celula].valor + 0x30;

		return;
		}
 

	


}

//--------------------------------------------
// (7) Escreva aqui a rotina responsável por
// solicitar uma coordenada XY e abrir uma
// célula no tabuleiro
//--------------------------------------------
void abrir_celula(struct celula *tabuleiro, int lado){

	int x;
	printf("\nDigite a linha(x): ");
	scanf("%d",&x);
	int y;
	printf("\nDigite a coluna(y): ");
	scanf("%d",&y);

	int posicao = (x*lado)+y;
	if (tabuleiro[posicao].valor==0){
		expande_zero(posicao,tabuleiro,lado);
	} 
	else if (tabuleiro[posicao].valor==-1){
	tabuleiro[posicao].imprime = '*';
	}
	else {	

	tabuleiro[posicao].imprime = tabuleiro[posicao].valor + 0x30;

	}

}

//--------------------------------------------
// (8) Escreva aqui a função responsável por
// verificar se o jogo acabou. Ela
// contabiliza se o numero de bombas
// marcadas e casas fechadas são iguais ao
// numero de bombas do jogo ou se o jogador
// abriu uma bomba
//--------------------------------------------
int fim_jogo(struct celula *tabuleiro, int lado, int total_bombas){
	int cont=0;
	int x;
	for (x=0;x<lado*lado;x++){ //laço pra verificar a quantidade de campos já abertos
		if(tabuleiro[x].imprime=='*'){
		printf("\nVoce abriu uma bomba, fim de jogo!\n");
		
		return 0;
		}
		if(tabuleiro[x].imprime=='B' || tabuleiro[x].valor>=0 ){
		cont++;
		}

	} 
		if(cont==lado*lado){ //valida se o usuario conseguiu abrir todos os campos 
		printf("\nParabéns Voce Completou o campo!\n");					
			return 0;
		 }
	return 1;
}

//--------------------------------------------
// (9) Escreva aqui a rotina responsável por
// solicitar uma coordenada XY e marcar uma
// célula no tabuleiro como bomba. Caso a
// célula já esteja marcada como bomba, a
// rotina desmarca a célula
//--------------------------------------------
void marcar_bomba(struct celula *tabuleiro, int lado){
	int x;
	printf("\nDigite a linha(x): ");
	scanf("%d",&x);
	int y;
	printf("\nDigite a coluna(y): ");
	scanf("%d",&y);

int posicao = (x*lado)+y; //acha a posição no array pelas cordenadas

if (tabuleiro[posicao].imprime=='B'){
tabuleiro[posicao].imprime = '#';

} else {
	tabuleiro[posicao].imprime = 'B';
	
	}
}

//--------------------------------------------
// (10) Escreva aqui a rotina responsável por
// ler os resultados do arquivo e mostrar na
// tela a pontuação histórica do jogo
//--------------------------------------------
void lista_pontuacao(){	
	FILE * pFile;
	char linha[100];
int x=0;
	pFile=fopen("pontos.txt","r");
	if (pFile!=NULL){
		
		do{
			if (fgets(linha,100,pFile) !=NULL){
				printf("%dº - %s",x+1,linha);
			}			
		x++;
		if (x==9) {break;}
		}while(!feof(pFile));
	printf("\n");
	fclose(pFile);
	} else {
		printf("\Erro ao abrir arquivo.\n");	
	}


}

//--------------------------------------------
// (11) Escreva aqui a função responsável por
// calcular e retornar os pontos feitos pelo
// jogador
//--------------------------------------------
double calcula_pontos(struct celula *tabuleiro, int lado, int total_bombas){
	double pct_celulas=0;
	int celulas_abertas=0;
int x;
	for ( x=0;x<lado*lado;x++){
		if (tabuleiro[x].imprime!='#'&&tabuleiro[x].imprime!='B'&&tabuleiro[x].imprime!='*'){
		celulas_abertas++;
		}
	}
	pct_celulas = celulas_abertas/((lado*lado)-total_bombas);

double P = (lado*lado)*(total_bombas)*(pct_celulas);
	return P;
}


//--------------------------------------------
// (12) Escreva aqui a rotina responsável por
// salvar a pontuação do jogador no arquivo
// texto pontos.txt.
//--------------------------------------------

void imprime_resultado(char jogador[20], double pontos){
//função chamada se o jogador completou o campo. Ela grava no txt
//o novo jogador e seu resultado e após isto puxa toda a lista de 
//jogadores e poem no  de struct vetor tabela[]. Com ele criado
// é feita a ordenação em ordem decrescente de pontuação (l 523)
//e apartir da linha 545 e gravado no txt a lista atualizada com o novo jogador.

typedef	struct {
	char nome[20]; // Membro que deverá conter o valor a ser impresso da célula
	char score[20];    // Membro que deverá conter o valor de controle da célula
		} componente;
	componente tabela[100];

	//gravando jogador atual
 
	FILE * pFileAtual;
	pFileAtual = fopen ("pontos.txt","a");
	if (pFileAtual!=NULL){
	char linha[50];
	strcpy(linha,jogador);
	char pt[20];
	sprintf(pt,"%.6f",pontos);
	strcat(linha," ");
	strcat(linha,pt);
	fprintf(pFileAtual,"%s\n",linha);	
	fclose(pFileAtual);
	} else {
		// printf( " Erro ao abrir arquivo.\n");
	}



	int max;
	for (max=0;max<100;max++){ //inicializando todas structs
	tabela[max].nome[0]= '!';
	//tabela[max].score[0]= '-';
	//tabela[max].score[1]= '1';
	}

//pegar a lista de jogadores do .txt
	int x=0;
	FILE * pFile;
	char linha[100];	
	pFile=fopen("pontos.txt","r");
	if (pFile!=NULL){
		do{
			if (fgets(linha,100,pFile) !=NULL){
					int i = 0;
					while(linha[i]!=' '){ //passa o nome pra tabela
						tabela[x].nome[i] = linha[i];
						i++;
					}
					i++;
					int y=0;
					while(linha[i]!='\0'){ //passar a pontuação
					
					tabela[x].score[y] = linha[i];
						i++;y++;
					}
			
			}			
		x++;
		}while(!feof(pFile));
	fclose(pFile);
	} else {
		printf("\Erro ao abrir arquivo.\n");	
	}

	//ordenando a lista em ordem descrescente ***BubbleSort
 int c,d;
 componente swap;
  for (c = 0 ; c < ( 100 - 1 ); c++)
  {
    for (d = 0 ; d < 100 - c - 1; d++)
    { 		
      if (atof(tabela[d].score) < atof(tabela[d+1].score)) 
      {
        swap       = tabela[d];
        tabela[d]   = tabela[d+1];
        tabela[d+1] = swap;
      }
    }
  }

	//gravando a lista atualizada no arquivo
	int cont;

	FILE * pFileArq;
	pFileArq = fopen ("pontos.txt","w+");

if (pFile!=NULL){
for (cont=0;cont<100;cont++){

	char novo[50];
	if (tabela[cont].nome[0]=='!') { break;} //cair fora quando ja gravou todos 
	strcpy(novo,tabela[cont].nome);
	strcat(novo," ");
	strcat(novo,tabela[cont].score);			
			fputs(novo,pFileArq);
					
	}
} else {
				printf("Erro ao abrir arquivo!.\n");
				}
	fclose(pFileArq);
}


//--------------------------------------------
// Função que será executada na função main,
// ela serve para que o jogador realize suas
// jogadas até o final do jogo
//--------------------------------------------
int jogada(struct celula *tabuleiro, int lado, int total_bombas){
	char opcao;
	do{
		printf("\nEntre com a operação (a/b/p/c/s): ");
		scanf(" %c",&opcao);
	} while (opcao!='a' && opcao!='b' && opcao!='p' && opcao!='c' && opcao!='s');
	
 	if (opcao=='a') {
		printf("Abrir posição\n");
		abrir_celula(tabuleiro, lado);
		return fim_jogo(tabuleiro, lado, total_bombas);
 	}
 	else if (opcao=='b') {
		printf("Marcar bomba\n");
	  marcar_bomba(tabuleiro, lado);
		return fim_jogo(tabuleiro, lado, total_bombas);
 	}
 	else if (opcao=='p') {
		printf("Pontuação:\n");
		lista_pontuacao();
 		return 1;
 	}
 	else if (opcao=='c') {
		printf("Comandos:\n a - Abrir posição no tabuleiro;\n b - Marcar/Desmarcar posição no tabuleiro como bomba;\n p - Listar pontuações;\n c - Listar comandos;\n s - Sair do jogo.\n\n");
 		return 1;
 	}
	else return 0;
}

//--------------------------------------------
// Função principal (main).
//--------------------------------------------
int main (int argc, char *argv[]){
	//Tabuleiro e variáveis para controle	
	struct celula *tabuleiro, *tabuleiro_aux;
	int lado_tabuleiro, num_bombas;
	double pontos;
	//Nome do jogador
	char jogador[20];
	
	
	//Variavel para controle de laços
	int i;

  //------------------------------------------
  // (1A) Escreva aqui um trecho de código
	// para verificar a consistência de dados
	// de entrada do programa (argc e argv).
  //------------------------------------------
	if (argc<4) { printf("\n %d, quantidade de parametros invalida!\n", argc);
	return 0;
	}
	if (*argv[3] == '0'|| *argv[3]<48 ){printf("\n Valor de bombas tem que ser maior do que 0!\n");
	return 0;	
	}
	if(*argv[2] < 50) { printf("\n Tamanho do campo invalido! valor minimo: 2\n");
	return 0;
	}
  //------------------------------------------
  // (1B) Escreva aqui um trecho de código
	// para inicializar as variáveis do jogo.
  //------------------------------------------
	strcpy(jogador,argv[1]);
	lado_tabuleiro = atoi(argv[2]);
	num_bombas = atoi(argv[3]);	
	
  //------------------------------------------
  // (1C) Escreva aqui um trecho de código
	// para inicialização do tabuleiro e
	// alocação de espaço em memória
	// (usar malloc).
  //------------------------------------------

   tabuleiro = malloc ((lado_tabuleiro*lado_tabuleiro) * sizeof (int *)); 
	int x;
	for ( x=0;x<lado_tabuleiro*lado_tabuleiro;x++){
	
	tabuleiro[x].valor=0;
	tabuleiro[x].imprime = '#';

	}
	tabuleiro_aux = tabuleiro;	
	
	// Neste momento, as bombas devem ser criadas no
	// tabuleiro e os valores de controle de todas
	// células devem ser calculados.
	gera_bombas(tabuleiro, lado_tabuleiro, num_bombas);
	calcula_celulas(tabuleiro, lado_tabuleiro);
	if ((argc == 5) && (!strcmp("DEBUG",argv[4])))
	  imprime_tabuleiro_debug(tabuleiro, lado_tabuleiro);
			
	// Este trecho de código é o laço do jogo, ele
	// só sai do laço quando o jogo acaba.
	do{
		imprime_tabuleiro(tabuleiro, lado_tabuleiro);
	}while(jogada(tabuleiro, lado_tabuleiro, num_bombas));
//	imprime_tabuleiro(tabuleiro, lado_tabuleiro);
	 imprime_tabuleiro_debug(tabuleiro, lado_tabuleiro);
 
	// Neste momento, devemos calcular e imprimir o
	// resultado no arquivo.
	pontos = calcula_pontos(tabuleiro, lado_tabuleiro, num_bombas);	
  imprime_resultado(jogador, pontos);
	
	lista_pontuacao();
	printf("\n");
		
	


	return 0;
}
