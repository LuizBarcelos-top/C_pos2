#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "forca.h"
#include <time.h>


//	Variaveis globais - USAR COM CUIDADO
char palavrasecreta[20];
char chutes[26];
int chutesdados = 0;

void abertura(){
	printf("*******************\n");
	printf("*  Jogo De Forca  *\n");
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

void chuta(){
	char chute;
	scanf(" %c", &chute);	
	//Arrays n�o precisam de *, pois s�o naturalmente ponteiros em C
	chutes[chutesdados] = chute;
	// Lembrando que para a opera��o funcionar, � preciso o (*)
	chutesdados++;
}

int jachutou(char letra){
	int achou = 0;
	for(int j = 0; j < chutesdados; j++){
		if(chutes[j] == letra){
			achou = 1;
			break;
		}
	}
	return achou;
}

void desenhaforca(){
	int erros = chuteserrados();
	
	printf("  _______       \n");
	printf(" |/      |      \n");
	printf(" |      %c%c%c  \n", (erros>=1?'(':' '), 
	    (erros>=1?'_':' '), (erros>=1?')':' '));
	printf(" |      %c%c%c  \n", (erros>=3?'\\':' '), 
	    (erros>=2?'|':' '), (erros>=3?'/': ' '));
	printf(" |       %c     \n", (erros>=2?'|':' '));
	printf(" |      %c %c   \n", (erros>=4?'/':' '), 
	    (erros>=4?'\\':' '));
	printf(" |              \n");
	printf("_|___           \n");
	printf("\n\n");
	
	for(int i = 0; i < strlen(palavrasecreta);i++){
		int achou = jachutou(palavrasecreta[i]);
		if(achou){
			printf("%c ", palavrasecreta[i]);
		}else{
			printf("_ ");
		}
		 
	}
	printf("\n");
}

void adicionapalavra(){
	char quer;
	printf("Voc^quer adicionar uma nova palavra? (S/N)");
	scanf(" %c", &quer);
	
	if (quer == 'S'){
		char novapalavra[20];
		printf("Qual a nova palavra?");
		scanf("%s", novapalavra);
		
		//Abrindo o arquivo
		FILE* f;
		// o segundo argumento, r+, quer dizer read+, isso �, leitura e escrita
		f = fopen("palavras.txt","r+");
		
		if (f == 0){
			printf("Banco de dados n�o dispon�vel\n\n");
			//exit mata o programa caso coloque um n�mero maior que 0
			exit(1);
		}
		
		//antes de tudo, precisamos ler o num da regra de a primeira linha ser o total de palavras
		int qtd;
		fscanf(f, "%d", &qtd);
		qtd++;
		// Como o ponteiro n�o necessariamente estar� no primeiro bite, precisamos apontar ele para l�
		//FSEEK aponta para algum lugar, sendo o 0 o parametro. SEEK_SET � uma constante de in�cio
		fseek(f, 0, SEEK_SET);
		// Escrevemos no TXT a nova qtd
		fprintf(f,"%d", qtd);
		
		
		//fprintf escreve no arquivo, na primeira linha
		//Precisamos adicionar a palavra na ultima linha, por isso usamos seek_end
		fseek(f, 0, SEEK_END);
		// Escrevemos no TXT a nova palavra
		fprintf(f,"\n%s",novapalavra);
		
		fclose(f);
	}
}

void escolhepalavra(){
	//Sprint serve para concatenar chars em um array de modo r�pido
	//sprintf(palavrasecreta,"asmodeus");
	
	//Para criar uma variavel de texto, usamos FILE*, nunca esquecer do *, pois � um ponteiro que leva ao txt
	FILE* f;
	/*Para atribuir o valor do nosso txt em uma vari�vel, usamos fopen com dois argumentos. O primeiro
	� o arquivo que queremos, com aspas duplas, e o segundo o que queremos fazer com ele. Neste caso
	a letra r de read
	*/
	f = fopen("palavras.txt", "r");
	/*
	Quando lidamos com leitura de arquivos externos, � uma boa pratica tratar eles, pois � preciso
	ter uma medida para caso o arquivo esteja corromp�do, tenha sido excl�ido ou seja inacess�vel
	*/
	if (f == 0){
		printf("Banco de dados n�o dispon�vel\n\n");
		//exit mata o programa caso coloque um n�mero maior que 0
		exit(1);
	}
	
	
	
	/*
	Aqui, eleborei o padr�o de a primeira linha do arquivo txt ser o n�mero de palavras do aquivo e
	atribui o n�mero ao qtddepalavras. O rand � para escolher aleatoriamente um n�mero dentro do qtd
	*/
	int qtddepalavras;
	fscanf(f, "%d", &qtddepalavras);
	
	srand(time(0));
	int randomico = rand() % qtddepalavras;
	
	//Agora lemos v�rias linhas, at� chegar na que randomizamos
	for(int i = 0; i <=randomico; i++){
		//Aqui, lemos o arquivo f e atribuimos a string usando %s. A atribuimos a vari�vel palavrasecreta
		fscanf(f, "%s", palavrasecreta);
	}
	
	//Uma boa pr�tica � sempre fechar o arquivo da vari�vel
	fclose(f);
}

// extra�mos pra c� o peda�o daquela fun��o 
// que contava a quantidade de erros
int chuteserrados() {
    int erros = 0;

    for(int i = 0; i < chutesdados; i++) {

        int existe = 0;

        for(int j = 0; j < strlen(palavrasecreta); j++) {
            if(chutes[i] == palavrasecreta[j]) {
                existe = 1;
                break;
            }
        }

        if(!existe) erros++;
    }

    return erros;
}

int enforcou() {
    // usamos a fun��o que acabamos de criar
    return chuteserrados() >= 5;
}

int ganhou(){
	for(int i = 0; i < strlen(palavrasecreta);i++){
		if(!jachutou(palavrasecreta[i])){
			return 0;	
		}
	}
	return 1;
}

int main(int argc, char *argv[]) {
	
	escolhepalavra();
	abertura();
	
	do {
		desenhaforca(palavrasecreta, chutes, chutesdados);
		/*Ao chamar essa fun��o, colocamos o & antes do parametro para que ele seja de fato a vari�vel
		chutesdados e n�o uma c�pia que ser� descartada ap�s o fim da execu��o da fun��o
		*/
		chuta(chutes, &chutesdados);

	} while(!ganhou() && !enforcou());
	//Para finalizar o percurso de um array, colocamos /0 no ultimo slot dele
	adicionapalavra();
	if(ganhou()) {
	    printf("\nParab�ns, voc� ganhou!\n\n");
	
	    printf("       ___________      \n");
	    printf("      '._==_==_=_.'     \n");
	    printf("      .-\\:      /-.    \n");
	    printf("     | (|:.     |) |    \n");
	    printf("      '-|:.     |-'     \n");
	    printf("        \\::.    /      \n");
	    printf("         '::. .'        \n");
	    printf("           ) (          \n");
	    printf("         _.' '._        \n");
	    printf("        '-------'       \n\n");

	} else {
	    printf("\nPuxa, voc� foi enforcado!\n");
	    printf("A palavra era **%s**\n\n", palavrasecreta);
	
	    printf("    _______________         \n");
	    printf("   /               \\       \n"); 
	    printf("  /                 \\      \n");
	    printf("//                   \\/\\  \n");
	    printf("\\|   XXXX     XXXX   | /   \n");
	    printf(" |   XXXX     XXXX   |/     \n");
	    printf(" |   XXX       XXX   |      \n");
	    printf(" |                   |      \n");
	    printf(" \\__      XXX      __/     \n");
	    printf("   |\\     XXX     /|       \n");
	    printf("   | |           | |        \n");
	    printf("   | I I I I I I I |        \n");
	    printf("   |  I I I I I I  |        \n");
	    printf("   \\_             _/       \n");
	    printf("     \\_         _/         \n");
	    printf("       \\_______/           \n");
	}
	/*
	palavrasecreta[0] = 'M';
	palavrasecreta[1] = 'E';
	palavrasecreta[2] = 'L';
	printf("%c%c%c",palavrasecreta[0],palavrasecreta[1],palavrasecreta[2]);
	*/
}














