#include<stdio.h>
#include<stdlib.h>

#define INT_MAX 10000

int visitado[10] = {0,0,0,0,0,0,0,0,0,0};


void print(int*vect){
    for (int i = 0; i < 4; i++)
    {
        printf("%d ",vect[i]);
    }
    printf("\n");
}

int valid(int**p,int numP,int *vect){
    
    for (int i = 0; i < numP; i++)
    {
        int count = 0;

        for (int j = 0; j < 4; j++){
            if(p[i][j]==vect[j]) count++;    
        }
        if (count == 4){
            return 0;
        } 
    }
    return 1;
}

int done(int*vect,int*destino){
    for (int i = 0; i < 4; i++) if (vect[i]!=destino[i]) return 0;
    
    return 1;
}

void solve(int*result,int*moves,int**p,int numP,int*destino,int*vect){
    if(done(vect,destino)){
        if(*moves<*result){
            *result = *moves;
        }
        for (int i = 0; i < 10; i++)
        {
            visitado[i] = 0;
        }
        
    }
    for (int i = 0; i < 4; i++)//para cada casa
    {
        if (vect[i]!=destino[i])
        {
            int preadd = vect[i];

            //mover para horario
            if (vect[i]==9){
                vect[i] = 0;
            }else vect[i]++;


            if (valid(p,numP,vect)&&!visitado[vect[i]])
            {
                visitado[vect[i]] = 1;
                print(vect);
                *moves++;
                solve(result,moves,p,numP,destino,vect);

            }

            //voltar para antes de movimentar para horario
            vect[i] = preadd;

            //mover para anti-horario
            if (vect[i]==0){
            vect[i] = 9;
            }else vect[i]--;


            if (valid(p,numP,vect)&&!visitado[vect[i]])//eh valido?
            {
                visitado[vect[i]] = 1;
                print(vect);
                *moves++;
                solve(result,moves,p,numP,destino,vect);
            }else vect[i] = preadd;
            
            
        }
    }
    

    



}


int main(){
    int numCasos = 0,k = 0;
    scanf("%d",&numCasos);
    while (k<numCasos)
    {
        int origem[4];
        int vetor[4];
        for (int i = 0; i < 4; i++){
            scanf("%d",&origem[i]);
            vetor[i] = origem[i]; 
        }
        
        int destino[4];
        for (int i = 0; i < 4; i++) scanf("%d",&destino[i]);
        

        int numProibidos;
        scanf("%d",&numProibidos);
        int **proibidos = (int**)malloc(numProibidos*sizeof(int*));
        for (int i = 0; i < numProibidos; i++)
        {
            proibidos[i] = (int*)malloc(4*sizeof(int));
            for (int j = 0; j < 4; j++) scanf("%d",&proibidos[i][j]);
        }
        int moves = 0;
        int result = INT_MAX;
        print(vetor);
        solve(&result,&moves,proibidos,numProibidos,destino,vetor);

        if(result==INT_MAX) printf("-1\n"); 
        else printf("%d\n",result);


        getchar();
        

        k++;
    }
    
    



    return 0;
}
