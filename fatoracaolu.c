#include <stdio.h>
#include <stdlib.h>


void inserirValores (float **, int , int );
void revelaResultado (float **, float **, float **, float**, int , int );
float ** multiplicaMatriz (float **, float **, int, int );


int main (void){

	float **A, **L, **P, **saveA;
	int numeroLinhas, numeroColunas, i, j, h,  linha, linhasNaoNulas, linhaPivo, colunaPivo, coluna;
	float auxiliar, pivo, multiplicador;

	printf("Qual o tamanho da sua matriz ? Digite primeiro o número de linha depois o de \n");
	scanf("%d %d", &numeroLinhas, &numeroColunas);

	A = malloc (numeroLinhas * sizeof(float *));
	L = malloc (numeroLinhas * sizeof(float *));
	P = malloc (numeroLinhas * sizeof(float *));
	saveA = malloc (numeroLinhas * sizeof(float *));

	for(i = 0 ; i < numeroLinhas ; i++){
		A[i] = malloc(numeroColunas * sizeof(float));
		L[i] = malloc(numeroColunas * sizeof(float));
		P[i] = malloc(numeroColunas * sizeof(float));
		saveA[i] = malloc(numeroColunas * sizeof(float));
	}

	for(i = 0 ; i < numeroLinhas ; i++){
		for(j = 0 ; j < numeroColunas ; j++){
			if(i == j){
				P[i][j] = 1;
				L[i][j] = 0;
			}
			else{
				P[i][j] = 0;
				L[i][j] = 0;
			}
		}
	}

	inserirValores(A, numeroLinhas, numeroColunas);

	for(i = 0 ; i < numeroLinhas ; i++){
		for(j = 0 ; j < numeroColunas ; j++){
			saveA[i][j] = A[i][j];
		}
	}

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
					auxiliar = P[i][j];
					P[i][j] = P[linhasNaoNulas-1][j];
					P[linhasNaoNulas-1][j] = auxiliar;
					auxiliar = L[i][j];
					L[i][j] = L[linhasNaoNulas-1][j];
					L[linhasNaoNulas-1][j] = auxiliar;
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
				auxiliar = P[linha][i];
				P[linha][i] = P[linhaPivo][i];
				P[linhaPivo][i] = auxiliar;
				auxiliar = L[linha][i];
				L[linha][i] = L[linhaPivo][i];
				L[linhaPivo][i] = auxiliar;
			}
		}

		pivo = A[linha][colunaPivo];
		L[linha][linha] = pivo;

		for ( i = colunaPivo ; i < numeroColunas ; i++ ){
			if(pivo != 0){
				A[linha][i] = A[linha][i] / pivo;
			}
		}

		for ( i = linha + 1 ; i < linhasNaoNulas ; i++ ){
			multiplicador = A[i][colunaPivo];
			L[i][colunaPivo] = multiplicador;
			for ( j = colunaPivo ; j < numeroColunas ; j++){
				A[i][j] = A[i][j] - multiplicador*A[linha][j];
			}
		}

	}
	
	revelaResultado(A, L, P, saveA, numeroLinhas, numeroColunas);

}

void revelaResultado(float **U, float **L, float **P, float **A, int n, int m){

	int i, j;
	float **LU, **PA;

	LU = multiplicaMatriz(L, U, n, m);
	PA = multiplicaMatriz(P, A, n, m);

	printf("\n   A Matriz A Original : \n\n");

	for(i = 0 ; i < n ; i++){
		printf("  ");
		for(j = 0 ; j < m ; j++){
			printf("   %3.3f", A[i][j]);
		}
		printf("\n");
	}

	printf("\n");

	printf("\n   A Matriz L Ficou : \n\n");

	for(i = 0 ; i < n ; i++){
		printf("  ");
		for(j = 0 ; j < m ; j++){
			printf("   %3.3f", L[i][j]);
		}
		printf("\n");
	}

	printf("\n");

	printf("\n   A Matriz U Ficou : \n\n");

	for(i = 0 ; i < n ; i++){
		printf("  ");
		for(j = 0 ; j < m ; j++){
			printf("   %3.3f", U[i][j]);
		}
		printf("\n");
	}

	printf("\n");

	printf("\n   A Matriz LU Ficou : \n\n");

	for(i = 0 ; i < n ; i++){
		printf("  ");
		for(j = 0 ; j < m ; j++){
			printf("   %3.3f", LU[i][j]);
		}
		printf("\n");
	}

	printf("\n");

	printf("\n   A Matriz PA Ficou : \n\n");

	for(i = 0 ; i < n ; i++){
		printf("  ");
		for(j = 0 ; j < m ; j++){
			printf("   %3.3f", PA[i][j]);
		}
		printf("\n");
	}

	printf("\n");
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

float** multiplicaMatriz(float **A, float **B, int n, int m){

	float **C;
	int i, j, linhas, colunas, aux;

	C = malloc(n * sizeof(float*));

	for(i = 0 ; i < n ; i++){
		C[i] = malloc(m * sizeof(float*));
	}

	for(i = 0 ; i < n ; i++){
		for(j = 0 ; j < m ; j++){
			C[i][j] = 0;
		}
	}

	for(linhas = 0 ; linhas < n ; linhas++){
		for(colunas = 0 ; colunas < m ; colunas++){
			for(i = 0 ; i < n ; i++){
				C[linhas][colunas] += A[linhas][i] * B[i][colunas];
			}
		}
	}

	return C;
}