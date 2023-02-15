#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void abertura(){
	printf("*******************\n");
	printf("*  Jodo De Forca  *\n");
	printf("*******************\n\n");
}


/*
Em uma fun��o, caso queiramos trabalhar com a vari�vel em um escopo global, isso �, para que a vari�vel
seja a mesma tanto na fun��o fora da main quanto dentro, precisamos trabalhar com o endere�o da mem�ria
Isso �, ma declara��o da fun��o, precisamos colocar o * na declara��o do tipo, como int* ou double*, e
ao chamar fun��o, colocamos o & antes do parametro. Se n�o fazermos isso, a fun��o criar� uma c�pia da
da vari�vel que ser� terminada ap�s o fim da execu��o e n�o alterar� o valor dela em outros escopos. 
Para trabalhar com opera��es matem�ticas dentro dessa fun��o, � necess�rio tamb�m colocar o (*), ou sen�o
ele far� as opera��es com o valor do endere�o da mem�ria e n�o o valor da vari�vel
EX I:  

void calcula(int* c){
	(*c)++;
}

int main(){
	int c = 10;
	calcula(&c);
}

EX II:
\\SEM PONTEIRO
void troca(int x, int y){
	int temp;
	temp = x;
	x = y;
	y = temp;
	printf("Valor de X em troca: %d \n"), x);
	printf("Valor de Y em troca: %d \n"), y);
}
int main(){
	int a = 5;
	int b = 10;
	printf("Valor de a antes da troca: %d \n"), a);
	printf("Valor de b antes da troca: %d \n"), b);
	troca(a,b);
	printf("Valor de a depois da troca: %d \n"), a);
	printf("Valor de b depois da troca: %d \n"), b);
}

\\COM PONTEIRO
void troca(int *x, int *y){
	int temp;
	temp = *x;
	*x = *y;
	*y = temp;
	printf("Valor de X em troca: %d \n"), *x);
	printf("Valor de Y em troca: %d \n"), *y);
}
int main(){
	int a = 5;
	int b = 10;
	printf("Valor de a antes da troca: %d \n"), a);
	printf("Valor de b antes da troca: %d \n"), b);
	troca(&a, &b);
	printf("Valor de a depois da troca: %d \n"), a);
	printf("Valor de b depois da troca: %d \n"), b);
}

Com isso, o c n�o � mais um inteiro, � um ponteiro para un inteiro, apenas est� apontando para o que 
ser� o parametro c.
Resumindo ==> * pega um endere�o de mem�ria e o & passa um endere�o de mem�ria
*/

void chuta(char chutes[26], int* tentativas){
	char chute;
	scanf(" %c", &chute);	
	//Arrays n�o precisam de *, pois s�o naturalmente ponteiros em C
	chutes[(*tentativas)] = chute;
	// Lembrando que para a opera��o funcionar, � preciso o (*)
	(*tentativas)++;
}

int jachutou(char letra, char chutes[26], int tentativas){
	int achou = 0;
	for(int j = 0; j < tentativas; j++){
		if(chutes[j] == letra){
			achou = 1;
			break;
		}
	}
	return achou;
}

int main(int argc, char *argv[]) {
	
	char palavrasecreta[20];
	//Sprint serve para concatenar chars em um array de modo r�pido
	sprintf(palavrasecreta,"asmodeus");
	int acertou = 0;
	int enforcou = 0;
	
	char chutes[26];
	int tentativas = 0;
	
	abertura();
	
	do {
		for(int i = 0; i < strlen(palavrasecreta);i++){
			
			int achou = jachutou(palavrasecreta[i], chutes, tentativas);

			if(achou){
				printf("%c ", palavrasecreta[i]);
			}else{
				printf("_ ");
			}
			
		}
		printf("\n");
		/*Ao chamar essa fun��o, colocamos o & antes do parametro para que ele seja de fato a vari�vel
		tentativas e n�o uma c�pia que ser� descartada ap�s o fim da execu��o da fun��o
		*/
		chuta(chutes, &tentativas);


	} while(!acertou && !enforcou);
	
	//Para finalizar o percurso de um array, colocamos /0 no ultimo slot dele
	
	/*
	palavrasecreta[0] = 'M';
	palavrasecreta[1] = 'E';
	palavrasecreta[2] = 'L';
	
	printf("%c%c%c",palavrasecreta[0],palavrasecreta[1],palavrasecreta[2]);
	*/
	
	 
}
