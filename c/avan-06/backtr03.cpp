#include <cstring>
#include <iostream>
#include <cstdio>



int destino[4];
int origem[4];
int proibidos[100][4];
int numProibidos;
int result = INT32_MAX;

void print(int*origem){
    for (int i = 0; i < 4; i++)
    {
        printf("%d ",origem[i]);
    }
    printf("\n");
}

int valid(int *origem){
    
    for (int i = 0; i < numProibidos; i++)
    {
        int count = 0;

        for (int j = 0; j < 4; j++){
            if(proibidos[i][j]==origem[j]) count++;    
        }
        if (count == 4){
            return 0;
        } 
    }
    return 1;
}

int done(){
    for (int i = 0; i < 4; i++) if (origem[i]!=destino[i]) return 0;
    
    return 1;
}

void solve(int*moves){
    if(done()){
        if(*moves<result){
            result = *moves;
        }

    }
    for (int i = 0; i < 4; i++)//para cada casa
    {
        if (origem[i]!=destino[i])
        {
            int preadd = origem[i];

            //mover para horario
            if (origem[i]==9){
                origem[i] = 0;
            }else origem[i]++;


            if (valid(origem))
            {
                print(origem);
                *moves++;
                solve(moves);

            }
            /*
            //voltar para antes de movimentar para horario
            origem[i] = preadd;

            //mover para anti-horario
            if (origem[i]==0){
            origem[i] = 9;
            }else origem[i]--;


            if (valid(origem))//eh valido?
            {
                print(origem);
                *moves++;
                solve(moves);
            }else origem[i] = preadd;
            */
            
        }
    }
    

    



}


int main(){
    int numCasos = 0,k = 0;
    scanf("%d",&numCasos);
    while (k<numCasos)
    {
        for (int i = 0; i < 4; i++){
            scanf("%d",&origem[i]);
        }
        
        for (int i = 0; i < 4; i++) scanf("%d",&destino[i]);
        

        
        scanf("%d",&numProibidos);
        for (int i = 0; i < numProibidos; i++)
        {
            for (int j = 0; j < 4; j++) scanf("%d",&proibidos[i][j]);
        }
        int moves = 0;
        
        solve(&moves);

        if(result==INT32_MAX) printf("-1\n"); 
        else printf("%d\n",result);


        getchar();
        

        k++;
    }
    
    



    return 0;
}
