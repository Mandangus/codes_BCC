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

// se a posicao é valida e SE aina nao foi visitado !!!!!
bool valido(bool tab[MAX][MAX], int lin, int col){
	return ((lin>=0) && (lin<MAX) && (col>=0) && (col<MAX) && !tab[lin][col]);
}

void backtracking(bool tabuleiro[MAX][MAX], int lin, int col, int cont){
	int c, l;
	// consegui colocar o cavalo em todas as posicoes do tabuleiro
	//printf("%d\n", cont);
	if (cont == MAX*MAX-1){
		np++;
		//printf("Encontrei um caminho\n");
		return;
	}
 	// para cada possivel movimento de um cavalo no tabuleiro..
	for (int i = 0; i < 8; ++i)
	{
		l = lin + movimentos[i][0];
		c = col + movimentos[i][1];
		if (valido(tabuleiro, l,c)) {
		// coloca o cavalo...
			tabuleiro[l][c] = true;
			backtracking(tabuleiro, l, c, cont+1);
			tabuleiro[l][c] = false;
		}
	}

}


int main(int argc, char const *argv[])
{
	bool tab[MAX][MAX];

	memset (tab, false, sizeof tab);
	tab[0][0] = true;
	backtracking(tab, 0, 0,0);
	printf(" nro caminhos: %ld\n", np);
	return 0;
}


