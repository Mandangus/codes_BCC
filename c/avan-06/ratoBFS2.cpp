#include <cstring>
#include <iostream>
#include <cstdio>
#include <queue>

#define MAX 30

short int lab[MAX][MAX];
short int sol[MAX][MAX];
int n;

using namespace std;

typedef pair<int,int> pi; // armazena a coordenada... 
typedef pair<pi,int> pii; 

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


int Caminho(int x, int y){
	int nx, ny;
	queue<pii> q;
	q.push(make_pair(make_pair(x,y),0)); //coloca na fila..
	sol[x][y] = 1; // marca como visitado
	pii dt;

	while (!q.empty()){ // enquanto houver elementos na fila...
		
		dt = q.front(); q.pop(); //retira da fila...

		// verifica se chegou ao fim...
		if (dt.first.first == n-1 && dt.first.second == n-1 && lab[dt.first.first][dt.first.second] == 1)
			return dt.second;

		// para todos os possiveis movimentos do rato
		for (int i = 0; i < 4; ++i){
			nx = dt.first.first+moves[i][0];
			ny = dt.first.second+moves[i][1];
			if (valido(nx,ny)){
				sol[nx][ny] = 1;  // marca a posicao como visitada
				// coloca na fila
				q.push(make_pair(make_pair(nx,ny),dt.second+1));
			}
		}
	}
	// se tudo falhar... diz que nao tem saida do labirinto...
	return -1;
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

	int dist;
	if ((dist = Caminho(0,0)) != -1){
		cout << "Achamos uma solucao para este labirinto em " << dist << " passos."<< endl;
	} else 
	cout << "Nao tem solucao para este labirinto." << endl;

	printMat(lab);
	cout << endl;
	printMat(sol);

	return 0;
}
