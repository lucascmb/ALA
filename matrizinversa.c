#include <stdio.h>
#include <stdlib.h>


void inserirValores (float **, int , int );
void revelaResultado (float **, int , int );


int main (void){

	float **A, **I;
	int numeroLinhas, numeroColunas, i, j, h,  linha, linhasNaoNulas, linhaPivo, colunaPivo, coluna;
	float auxiliar, pivo, multiplicador;

	printf("Qual o tamanho da sua matriz ? Digite primeiro o número de linhas e depois o de colunas \n");
	scanf("%d %d", &numeroLinhas, &numeroColunas);

	A = malloc (numeroLinhas * sizeof(float *));
	I = malloc (numeroLinhas * sizeof(float *));

	for(i = 0 ; i < numeroLinhas ; i++){
		A[i] = malloc(numeroColunas * sizeof(float));
		I[i] = malloc(numeroColunas * sizeof(float));
	}

	for(i = 0 ; i < numeroLinhas ; i++){
		for(j = 0 ; j < numeroColunas ; j++){
			if(i == j){
				I[i][j] = 1;
			}
			else{
				I[i][j] = 0;
			}
		}
	}

	inserirValores(A, numeroLinhas, numeroColunas);

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

				for (j = 0 ; j < numeroColunas ; j++){
					auxiliar = A[i][j];
					A[i][j] = A[linhasNaoNulas-1][j];
					A[linhasNaoNulas-1][j] = auxiliar;
					auxiliar = I[i][j];
					I[i][j] = I[linhasNaoNulas-1][j];
					I[linhasNaoNulas-1][j] = auxiliar;
				}

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
				auxiliar = I[linha][i];
				I[linha][i] = I[linhaPivo][i];
				I[linhaPivo][i] = auxiliar;
			}
		}

		pivo = A[linha][colunaPivo];

		for ( i = colunaPivo ; i < numeroColunas ; i++ ){
			A[linha][i] = A[linha][i] / pivo;
		}
		for ( i = 0 ; i < numeroColunas ; i++){
			I[linha][i] = I[linha][i] / pivo;
		}

		for ( i = linha + 1 ; i < linhasNaoNulas ; i++ ){
			multiplicador = A[i][colunaPivo];
			for ( j = colunaPivo ; j < numeroColunas ; j++){
				A[i][j] = A[i][j] - multiplicador*A[linha][j];
			}
			for ( j = 0 ; j < numeroColunas ; j++){
				I[i][j] = I[i][j] - multiplicador*I[linha][j];
			}
		}

		if (linha > 0){
			for ( i = 0 ; i < linha ; i++ ){
				multiplicador = A[i][colunaPivo];
				for ( j = colunaPivo ; j < numeroColunas ; j++){
					A[i][j] = A[i][j] - multiplicador*A[linha][j];
				}
				for ( j = 0 ; j < numeroColunas ; j++){
					I[i][j] = I[i][j] - multiplicador*I[linha][j];
				}
			}
		}

	}
	
	revelaResultado(I, numeroLinhas, numeroColunas);

}

void revelaResultado(float **I, int n, int m){

	int i, j;

	printf("\n   A Matriz Inversa é : \n\n");

	for(i = 0 ; i < n ; i++){
		printf("  ");
		for(j = 0 ; j < m ; j++){
			printf("   %3.3f", I[i][j]);
		}
		printf("\n");
	}

	printf("\n\n");
}

void inserirValores (float **A, int n, int m){

	int i, j;

	printf("Digite os valores para sua matriz\n");


	for(i = 0 ; i < n ; i++){
		for(j = 0 ; j < m ; j++){
			printf("Valor da Linha %d coluna %d\n", i + 1, j + 1);
			scanf("%f", &A[i][j]);
		}
	}

}
