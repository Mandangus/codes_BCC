#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>



#define BUFFER 2000// buffer para o caminha da resposta

typedef struct person p_t;

struct person
{
    int id;
    int speed;
    bool lado;// true -> lado final / false -> lado inicial
};

void printVect(p_t* pessoas,int n){

    for (int i = 0; i < n; i++)
    {
        printf("%d ",pessoas[i].speed);   
    }
    printf("\n");

    return;
}

void solve(p_t* pessoas, int n){

    char* caminho = (char*)calloc(BUFFER,sizeof(char));// string para printar a solução do problema
    
    //  sortando o vetor para facilitar o algoritimo
    for (int i = 0; i < n-1; i++)
    {
        for (int j = i+1; j < n; j++)
        {
            if (pessoas[i].speed > pessoas[j].speed)
            {
                p_t tmp = pessoas[i];
                pessoas[i] = pessoas[j];
                pessoas[j] = tmp;
            }
            
        }
        
    }

    char *temp = (char*)calloc(20,sizeof(char));
    int total = 0;
    if (n==1)
    {
        total = pessoas[0].speed;
        sprintf(temp,"%d\n",pessoas[0].speed);
        strcat(caminho,temp);
    }else if (n==2)
    {
        total = pessoas[0].speed + pessoas[1].speed;
        sprintf(temp,"%d %d\n",pessoas[0].speed,pessoas[1].speed);
        strcat(caminho,temp);
    }else
    {
        
        for (int i = n - 2; i >= 2; i-=2)
        {
            //estrategia 1: onde o mais rapido vai e volta com os lentos |vs| estrategia 2: onde o segundo mais rapido vai com o mais rapido e volta com o mais lento 
            if ((2*pessoas[0].speed + pessoas[i].speed + pessoas[i+1].speed) <= (2*pessoas[1].speed + pessoas[0].speed + pessoas[i+1].speed))
            {
                total += (2*pessoas[0].speed + pessoas[i].speed + pessoas[i+1].speed);

                
                sprintf(temp,"%d %d\n",pessoas[0].speed,pessoas[i+1].speed);
                strcat(caminho,temp);
                sprintf(temp,"%d\n",pessoas[0].speed);
                strcat(caminho,temp);
                sprintf(temp,"%d %d\n",pessoas[0].speed,pessoas[i].speed);
                strcat(caminho,temp);
                sprintf(temp,"%d\n",pessoas[0].speed);
                strcat(caminho,temp);
            }else
            {
                total += (2*pessoas[1].speed + pessoas[0].speed + pessoas[i+1].speed);
                

                sprintf(temp,"%d %d\n",pessoas[0].speed,pessoas[1].speed);
                strcat(caminho,temp);
                sprintf(temp,"%d\n",pessoas[0].speed);
                strcat(caminho,temp);
                sprintf(temp,"%d %d\n",pessoas[i].speed,pessoas[i+1].speed);
                strcat(caminho,temp);
                sprintf(temp,"%d\n",pessoas[1].speed);
                strcat(caminho,temp);
            }
            
            
        }
        if (n % 2 != 0)//caso seja impar tem mais um passo com o terceiro mais rapido
        {
            total += pessoas[0].speed + pessoas[2].speed;
            sprintf(temp,"%d %d\n",pessoas[0].speed,pessoas[2].speed);
            strcat(caminho,temp);
            sprintf(temp,"%d\n",pessoas[0].speed);
            strcat(caminho,temp);
        }
        total += pessoas[1].speed;
        sprintf(temp,"%d %d\n",pessoas[0].speed,pessoas[1].speed);//passo final com o segundo mais rapido sendo levado de volta
        strcat(caminho,temp);

    }
    
    
    
    
    printf("%d\n%s",total,caminho);
    free(temp);
    free(caminho);
    return;
}

int main(){
    
    int num_casos = 0, k = 0;
    scanf("%d",&num_casos);
    getchar();
    getchar();
    while (k<num_casos)
    {
        int people = 0, l = 0;
        scanf("%d",&people);
        getchar();
        p_t* pessoas = (p_t*)malloc(people*sizeof(p_t));
        while (l<people)
        {
            pessoas[l].id = l;
            pessoas[l].lado = false;
            scanf("%d",&pessoas[l].speed);
            getchar();
            l++;
        }
        

        solve(pessoas,people);
        if (k!=num_casos-1)
        {
            printf("\n");
        }
        
        
        free(pessoas);
        getchar();
        k++;
    }
    
    



    return 0;
}