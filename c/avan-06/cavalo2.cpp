#include <cstdio>
#include <cstdlib>
#include <cstring>

#define MAX 5

long int np = 0;

int movimentos[8][2] = {-1,2,
						-2, 1,
						-2,-1,
						-1,-2,
						1,-2,
						2,-1,
						2,1,
						1,2
						};


void imprimeTab(int mat[MAX][MAX]){
	for (int i = 0; i < MAX; ++i) {
		for (int j = 0; j < MAX; ++j)
		{
			printf("%d\t", mat[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}



// se a posicao é valida e SE aina nao foi visitado !!!!!
bool valido(int tab[MAX][MAX], int lin, int col){
	return ((lin>=0) && (lin<MAX) && (col>=0) && (col<MAX) && tab[lin][col] == -1);
}

void backtracking(int tabuleiro[MAX][MAX], int lin, int col, int cont){
	int c, l;
	// consegui colocar o cavalo em todas as posicoes do tabuleiro
	//printf("%d\n", cont);
	if (cont == MAX*MAX-1){
		np++;
		imprimeTab(tabuleiro);
		return;
	}
 	// para cada possivel movimento de um cavalo no tabuleiro..
	for (int i = 0; i < 8; ++i)
	{
		l = lin + movimentos[i][0];
		c = col + movimentos[i][1];
		if (valido(tabuleiro, l,c)) {
		// coloca o cavalo...
			tabuleiro[l][c] = cont+1;
			backtracking(tabuleiro, l, c, cont+1);
			tabuleiro[l][c] = -1;
		}
	}

}


int main(int argc, char const *argv[]){
	int tab[MAX][MAX];

	memset (tab, -1, sizeof tab);
	tab[0][0] = 0;
	backtracking(tab, 0, 0,0);
	printf(" nro caminhos: %ld\n", np);
	return 0;
}


