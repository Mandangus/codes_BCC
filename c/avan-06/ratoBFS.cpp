#include <cstring>
#include <iostream>
#include <cstdio>
#include <queue>

#define MAX 10

short int lab[MAX][MAX][MAX][MAX];
short int sol[MAX][MAX][MAX][MAX];
int n;

using namespace std;



char moves[8][4] = {1,0,0,0,//somar e subtrair no milhar...
					-1,0,0,0,
					0,1,0,0,//na centena...
					0,-1,0,0,
					0,0,1,0,//na dezena...
					0,0,-1,0,
					0,0,0,1,//na unidade.
					0,0,0,-1};


bool valido(int x, int y){
	// x e y esta no tabuleiro, se nao é parede e se nao visitei ainda
	if (x<n && x>=0 && y<n && y>=0 && lab[x][y]==1 && sol[x][y]==0)
		return true;

	return false;
}


bool Caminho(int x, int y){
	int nx, ny;
	queue<pi> q;
	q.push(make_pair(x,y)); //coloca na fila..
	sol[x][y] = 1; // marca como visitado
	pi coord;

	while (!q.empty()){ // enquanto houver elementos na fila...
		
		coord = q.front(); q.pop(); //retira da fila...

		// verifica se chegou ao fim...
		if (coord.first == n-1 && coord.second == n-1 && lab[coord.first][coord.second] == 1)
			return true;

		// para todos os possiveis movimentos do rato
		for (int i = 0; i < 4; ++i){
			nx = coord.first+moves[i][0];
			ny = coord.second+moves[i][1];
			if (valido(nx,ny)){
				sol[nx][ny] = 1;  // marca a posicao como visitada
				// coloca na fila
				q.push(make_pair(nx,ny));
			}
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