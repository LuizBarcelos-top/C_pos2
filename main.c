#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	
	char palavrasecreta[20];
	//Sprint serve para concatenar chars em um array de modo rápido
	sprintf(palavrasecreta,"asmodeus");
	int acertou = 0;
	int enforcou = 0;
	
	char chutes[26];
	int tentativas = 0;
	
	printf("Forca \n");
	
	do {
		for(int i = 0; i < strlen(palavrasecreta);i++){
			
			int achou = 0;
			
			for(int j = 0; j < tentativas; j++){
				if(chutes[j] == palavrasecreta[i]){
					achou = 1;
					break;
				}
			}
			if(achou){
				printf("%c ", palavrasecreta[i]);
			}else{
				printf("_ ");
			}
			
		}
		printf("\n");
		
		
		char chute;
		scanf(" %c", &chute);
		
		chutes[tentativas] = chute;
		tentativas++;
		
	} while(!acertou && !enforcou);
	
	//Para finalizar o percurso de um array, colocamos /0 no ultimo slot dele
	
	/*
	palavrasecreta[0] = 'M';
	palavrasecreta[1] = 'E';
	palavrasecreta[2] = 'L';
	
	printf("%c%c%c",palavrasecreta[0],palavrasecreta[1],palavrasecreta[2]);
	*/
	
	 
}
