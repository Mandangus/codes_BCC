#include <cstring>
#include <iostream>
#include <cstdio>

#define MAX 30

short int lab[MAX][MAX];
short int sol[MAX][MAX];
int n;

using namespace std;

char moves[4][2] = {1,0,
					-1,0,
					0,-1,
					0,1};


void printMat(short int mat[][MAX]){
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
			cout << mat[i][j] << " ";
		cout << endl;
	}
}

bool valido(int x, int y){
	// x e y esta no tabuleiro, se nao é parede e se nao visitei ainda
	if (x<n && x>=0 && y<n && y>=0 && lab[x][y]==1 && sol[x][y]==0)
		return true;

	return false;
}


bool Caminho(int x, int y){
	int nx, ny;
	// se chegou ao fim... (coordenada n-1 E a posicao nao é parede ??)
	if (x == n-1 && y == n-1 && lab[x][y] == 1){
		return true;
	return false;
	}

	
	// para todos os possiveis movimentos do rato
	for (int i = 0; i < 4; ++i){
		nx = x+moves[i][0];
		ny = y+moves[i][1];
		if (valido(nx,ny)){
			sol[nx][ny] = 1;  // marca a posicao como visitada
			if (Caminho(nx,ny)) // backtracking em nx e ny...
				return true;
			sol[nx][ny] = 0; // Se o caminho foi infrutifero, 'desvisita !!'
		}
	}
	// se tudo falhar... diz que nao tem saida do labirinto...
	return false;
}

int main(int argc, char const *argv[])
{
	cin >> n;
	// ninguem visitado ainda...
	memset(sol, 0, sizeof sol);

	// lendo o labririnto
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			cin >> lab[i][j];

	sol[0][0] = 1;  // o caminho comeca em 0,0
	if (Caminho(0,0)){
		cout << "Achamos uma solucao para este labirinto." << endl;
	} else 
	cout << "Nao tem solucao para este labirinto." << endl;

	printMat(lab);
	cout << endl;
	printMat(sol);

	return 0;
}