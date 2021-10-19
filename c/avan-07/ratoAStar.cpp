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

typedef struct _No{
	pi coord; 
	int depth;
} No;


typedef pair<int, No> pino; // Armazena F (g+h) e o No !!!

char moves[4][2] = {0,-1, // esquerda
					0,1,   // direita
					-1,0,   // cima
					1,0,   // baixo
					 };  


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
	if (x<n && x>=0 && y<n && y>=0 && lab[x][y]==1 && sol[x][y]==-1)
		return true;

	return false;
}

// Funcao F = g + h para A*  !!!!
int funcaoF(No source, pi target){
	int g = source.depth;
	// nossa heuristica admissivel é a dist, manhattan.. !!!!
	int h = abs(source.coord.first - target.first) + 
		abs(source.coord.second - target.second);

	//return g+h;
	return h;
}

bool operator<(const pino& p1, const pino& p2)
{
    return p1.first > p2.first;
}


int Caminho(int x, int y){
	int nx, ny;
	priority_queue<pino> q;
	No no;
	no.coord = make_pair(x,y);
	no.depth = 0;
	//pi final = make_pair(n-1, n-1);
	pi final = make_pair(12, 11);

	q.push(make_pair(funcaoF(no,final), no)); //coloca na fila o par (f, no)
	sol[x][y] = funcaoF(no,final); // marca como visitado
	pino dt;
	
	while (!q.empty()){ // enquanto houver elementos na fila...
		
		dt = q.top(); q.pop(); //retira da fila...
		no = dt.second;

		// verifica se chegou ao fim...
		if (no.coord.first == final.first && no.coord.second == final.second && lab[no.coord.first][no.coord.second] == 1)
			return no.depth;

		// para todos os possiveis movimentos do rato
		for (int i = 0; i < 4; ++i){
			nx = no.coord.first+moves[i][0];
			ny = no.coord.second+moves[i][1];
			if (valido(nx,ny)){
				No aux;
				aux.coord = make_pair(nx,ny);
				aux.depth = no.depth+1;
				q.push(make_pair(funcaoF(aux,final), aux)); //coloca na fila o par (f, no)
				sol[nx][ny] = funcaoF(aux,final);  // marca a posicao como visitada

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
	memset(sol, -1, sizeof sol);

	// lendo o labririnto
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			cin >> lab[i][j];

	int dist;
	if ((dist = Caminho(3,2)) != -1){
		cout << "Achamos uma solucao para este labirinto em " << dist << " passos."<< endl;
	} else 
	cout << "Nao tem solucao para este labirinto." << endl;

	printMat(lab);
	cout << endl;
	printMat(sol);

	return 0;
}
