#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void abertura(){
	printf("*******************\n");
	printf("*  Jodo De Forca  *\n");
	printf("*******************\n\n");
}


/*
Em uma função, caso queiramos trabalhar com a variável em um escopo global, isso é, para que a variável
seja a mesma tanto na função fora da main quanto dentro, precisamos trabalhar com o endereço da memória
Isso é, ma declaração da função, precisamos colocar o * na declaração do tipo, como int* ou double*, e
ao chamar função, colocamos o & antes do parametro. Se não fazermos isso, a função criará uma cópia da
da variável que será terminada após o fim da execução e não alterará o valor dela em outros escopos. 
Para trabalhar com operações matemáticas dentro dessa função, é necessário também colocar o (*), ou senão
ele fará as operações com o valor do endereço da memória e não o valor da variável
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

Com isso, o c não é mais um inteiro, é um ponteiro para un inteiro, apenas está apontando para o que 
será o parametro c.
Resumindo ==> * pega um endereço de memória e o & passa um endereço de memória
*/

void chuta(char chutes[26], int* tentativas){
	char chute;
	scanf(" %c", &chute);	
	//Arrays não precisam de *, pois são naturalmente ponteiros em C
	chutes[(*tentativas)] = chute;
	// Lembrando que para a operação funcionar, é preciso o (*)
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
	//Sprint serve para concatenar chars em um array de modo rápido
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
		/*Ao chamar essa função, colocamos o & antes do parametro para que ele seja de fato a variável
		tentativas e não uma cópia que será descartada após o fim da execução da função
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
