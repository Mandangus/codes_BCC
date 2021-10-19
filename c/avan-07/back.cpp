#include <cstring>
#include <iostream>
#include <cstdio>
#include <queue>

#define INT_MAX 100000

using namespace std;

short int comb[10][10][10][10];
short int sol[10][10][10][10];
int destino[4];
int n = 10;




typedef struct _No{
    int coord[4];
    int depth;

} No;

typedef pair<int, No> pino; 

short int moves[8][4]={0,-1,0,0,
					   0,1,0,0,   
					  -1,0,0,0,   
					   1,0,0,0,
                       0,0,-1,0,
                       0,0,1,0,
                       0,0,0,-1,
                       0,0,0,1,   
					  }; 


bool operator<(const pino& p1, const pino& p2)
{
    return p1.first > p2.first;
}

bool valido(int x,int y, int z, int w){

    if (x >= 0 && x < n && y >= 0 && y < n && z >= 0 && z < n && w >= 0 
               && w < n && comb[x][y][z][w] != 1 && sol[x][y][z][w] == -1)
        return true;
    return false;
}

int funcaoF(No src, int target[4]){
    int g = src.depth;
    int h = 0;
    for (int i = 0; i < 4; i++)
    {
        h += abs(src.coord[i]-target[i]);
    }
    return g + h;
}

bool isFim(No no){
    int l = 0;
    for (int i = 0; i < 4; i++)
    {
        if (no.coord[i] == destino[i]) l++;
        
    }
    if (l==4 && comb[no.coord[0]][no.coord[1]][no.coord[2]][no.coord[3]]!=1)
    {
        return true;
    }
    return false;
}

int aEstrela(int x,int y,int z,int w){
    int nx, ny, nz, nw;
    priority_queue<pino> q;
    No no;
    no.coord[0] = x;
    no.coord[1] = y;
    no.coord[2] = z;
    no.coord[3] = w;
    no.depth = 0;
    q.push(make_pair(funcaoF(no,destino),no));
    sol[x][y][z][w] = funcaoF(no,destino);
    pino dt;
    while (!q.empty())
    {
        dt = q.top(); q.pop();
        no = dt.second;
         
        if (isFim(no)) return no.depth;

        for (int i = 0; i < 8; i++)
        {
            nx = no.coord[0] + moves[i][0];
            ny = no.coord[1] + moves[i][1];
            nz = no.coord[2] + moves[i][2];
            nw = no.coord[3] + moves[i][3];
            if (valido(nx,ny,nz,nw))
            {
                No aux;
                aux.coord[0] = nx;
                aux.coord[1] = ny;
                aux.coord[2] = nz;
                aux.coord[3] = nw;
                aux.depth = no.depth + 1;
                q.push(make_pair(funcaoF(aux,destino),aux));
                sol[nx][ny][nz][nw] = funcaoF(aux,destino);
            }
            
        }
        
        
    }
    return -1;
}

int main(){


    
    int numCasos = 0,k = 0;
    scanf("%d",&numCasos);
    while (k<numCasos)
    {


        memset(comb,0,sizeof comb);
        memset(sol, -1, sizeof sol);

        int origem[4];
        for (int i = 0; i < 4; i++) scanf("%d",&origem[i]);
        
        
        
        for (int i = 0; i < 4; i++) scanf("%d",&destino[i]);
        

        int numProibidos;
        scanf("%d",&numProibidos);
        for (int i = 0; i < numProibidos; i++)
        {
            int proibido[4];
            for (int j = 0; j < 4; j++) scanf("%d",&proibido[j]);
            comb[proibido[0]][proibido[1]][proibido[2]][proibido[3]] = 1;
        }

        int result = aEstrela(origem[0],origem[1],origem[2],origem[3]);
        if(result != -1){
            printf("%d\n",result);
        }else printf("-1\n");
        


        getchar();
        

        k++;
    }
    



    return 0;
}