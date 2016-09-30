#include <stdio.h>
#include <stdlib.h>


void inserirValores (float **, float *, int , int );
void revelaResultado (float **, float *, int , int );


int main (void){

	float **A, *B;
	int numeroLinhas, numeroColunas, i, j, h,  linha, linhasNaoNulas, linhaPivo, colunaPivo, coluna;
	float auxiliar, pivo, multiplicador;

	printf("Qual o tamanho da sua matriz ? Digite primeiro o número de linha depois o de \n");
	scanf("%d %d", &numeroLinhas, &numeroColunas);

	A = malloc (numeroLinhas * sizeof(float *));

	for(i = 0 ; i < numeroLinhas ; i++){
		A[i] = malloc(numeroColunas * sizeof(float));
	}

	B = malloc (numeroColunas * sizeof(float));

	inserirValores(A, B, numeroLinhas, numeroColunas);

	linhasNaoNulas = numeroLinhas;

	for(linha = 0 ; linha < numeroLinhas ; linha++){

		linhaPivo = numeroLinhas-1;
		colunaPivo = numeroColunas-1;

		for(i = linha ; i < linhasNaoNulas ; i++){

			coluna = 1;

			while ( coluna <= numeroColunas && (A[i][coluna-1]) == 0 ){
				coluna++;
			}

			if ( coluna == numeroColunas+1 ){

				if ( B[i] != 0 ){
					printf(" SISTEMA IMPOSSÍVEL \n");
					return 0;
				}

				for (j = 0 ; j < numeroColunas ; j++){
					auxiliar = A[i][j];
					A[i][j] = A[linhasNaoNulas-1][j];
					A[linhasNaoNulas-1][j] = auxiliar;
				}

				auxiliar = B[i];
				B[i] = B[linhasNaoNulas-1];
				B[linhasNaoNulas-1] = auxiliar;
				linhasNaoNulas--;

			}

			if ( coluna-1 < colunaPivo ){
				colunaPivo = coluna-1;
				linhaPivo = i;
			}

		}

		if ( linha != linhaPivo){
			for( i = 0 ; i < numeroColunas ; i++){
				auxiliar = A[linha][i];
				A[linha][i] = A[linhaPivo][i];
				A[linhaPivo][i] = auxiliar;
			}
			auxiliar = B[linha];
			B[linha] = B[linhaPivo];
			B[linhaPivo] = auxiliar;
		}

		pivo = A[linha][colunaPivo];

		for ( i = colunaPivo ; i < numeroColunas ; i++ ){
			A[linha][i] = A[linha][i] / pivo;
		}

		B[linha] = ( B[linha]/pivo );


		for ( i = linha + 1 ; i < linhasNaoNulas ; i++ ){
			multiplicador = A[i][colunaPivo];
			for ( j = colunaPivo ; j < numeroColunas ; j++){
				A[i][j] = A[i][j] - multiplicador*A[linha][j];
			}
			B[i] = B[i] - (multiplicador*B[linha]);
		}

		if (linha > 	0){
			for ( i = 0 ; i < linha ; i++ ){
				multiplicador = A[i][colunaPivo];
				for ( j = colunaPivo ; j < numeroColunas ; j++){
					A[i][j] = A[i][j] - multiplicador*A[linha][j];
				}
				B[i] = B[i] - (multiplicador*B[linha]);
			}
		}

	}
	
	revelaResultado(A, B, numeroLinhas, numeroColunas);

}

void revelaResultado(float **A, float *B, int n, int m){

	int i, j;

	printf("\n   A Matriz Final Aumentada Ficou : \n\n");

	for(i = 0 ; i < n ; i++){
		printf("  ");
		for(j = 0 ; j < m ; j++){
			printf("   %3.3f", A[i][j]);
		}
		printf("   %3.3f", B[i]);
		printf("\n");
	}

	printf("\n\n");
}

void inserirValores (float **A, float *B, int n, int m){

	int i, j;

	printf("Digite os valores para sua matriz\n");


	for(i = 0 ; i < n ; i++){
		for(j = 0 ; j < m ; j++){
			printf("Valor da Linha %d coluna %d\n", i + 1, j + 1);
			scanf("%f", &A[i][j]);
		}
	}

	for(i = 0 ; i < m ; i++){
		printf("Valor da Linha %d \n", i+1);
		scanf("%f", &B[i]);
	}

}