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

void chuta(){
	char chute;
	scanf(" %c", &chute);	
	//Arrays não precisam de *, pois são naturalmente ponteiros em C
	chutes[chutesdados] = chute;
	// Lembrando que para a operação funcionar, é preciso o (*)
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
		// o segundo argumento, r+, quer dizer read+, isso é, leitura e escrita
		f = fopen("palavras.txt","r+");
		
		if (f == 0){
			printf("Banco de dados não disponível\n\n");
			//exit mata o programa caso coloque um número maior que 0
			exit(1);
		}
		
		//antes de tudo, precisamos ler o num da regra de a primeira linha ser o total de palavras
		int qtd;
		fscanf(f, "%d", &qtd);
		qtd++;
		// Como o ponteiro não necessariamente estará no primeiro bite, precisamos apontar ele para lá
		//FSEEK aponta para algum lugar, sendo o 0 o parametro. SEEK_SET é uma constante de início
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
	//Sprint serve para concatenar chars em um array de modo rápido
	//sprintf(palavrasecreta,"asmodeus");
	
	//Para criar uma variavel de texto, usamos FILE*, nunca esquecer do *, pois é um ponteiro que leva ao txt
	FILE* f;
	/*Para atribuir o valor do nosso txt em uma variável, usamos fopen com dois argumentos. O primeiro
	é o arquivo que queremos, com aspas duplas, e o segundo o que queremos fazer com ele. Neste caso
	a letra r de read
	*/
	f = fopen("palavras.txt", "r");
	/*
	Quando lidamos com leitura de arquivos externos, é uma boa pratica tratar eles, pois é preciso
	ter uma medida para caso o arquivo esteja corrompído, tenha sido exclúido ou seja inacessível
	*/
	if (f == 0){
		printf("Banco de dados não disponível\n\n");
		//exit mata o programa caso coloque um número maior que 0
		exit(1);
	}
	
	
	
	/*
	Aqui, eleborei o padrão de a primeira linha do arquivo txt ser o número de palavras do aquivo e
	atribui o número ao qtddepalavras. O rand é para escolher aleatoriamente um número dentro do qtd
	*/
	int qtddepalavras;
	fscanf(f, "%d", &qtddepalavras);
	
	srand(time(0));
	int randomico = rand() % qtddepalavras;
	
	//Agora lemos várias linhas, até chegar na que randomizamos
	for(int i = 0; i <=randomico; i++){
		//Aqui, lemos o arquivo f e atribuimos a string usando %s. A atribuimos a variável palavrasecreta
		fscanf(f, "%s", palavrasecreta);
	}
	
	//Uma boa prática é sempre fechar o arquivo da variável
	fclose(f);
}

// extraímos pra cá o pedaço daquela função 
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
    // usamos a função que acabamos de criar
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
		/*Ao chamar essa função, colocamos o & antes do parametro para que ele seja de fato a variável
		chutesdados e não uma cópia que será descartada após o fim da execução da função
		*/
		chuta(chutes, &chutesdados);

	} while(!ganhou() && !enforcou());
	//Para finalizar o percurso de um array, colocamos /0 no ultimo slot dele
	adicionapalavra();
	if(ganhou()) {
	    printf("\nParabéns, você ganhou!\n\n");
	
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
	    printf("\nPuxa, você foi enforcado!\n");
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














