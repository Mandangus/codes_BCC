#include<stdio.h>
#include<stdlib.h>

typedef struct task tar_t;

struct task//definindo um tipo tarefa para facilitar a sintaxe...
{
    int weight;//pesos
    int lenght;//distancias
    double ratio;//relação peso/distancia
};


int agendamento(tar_t* tarefas,int n){//calcula o valor total do agendamento 
    int total = 0;
    int completude = 0;
    for (int i = 0; i < n; i++)
    {
        completude += tarefas[i].lenght;
        total += tarefas[i].weight * completude;
    }

    return total;
}

void solve(tar_t*tarefas,int n){// resolve o problema ao ordenar o vetor de maneira a ordenar de maneira decrescente a relação peso/tamanho

    for (int i = 0; i < n-1; i++)
    {
        for (int j = i+1; j < n; j++)
        {
            if (tarefas[i].ratio < tarefas[j].ratio)
            {
                tar_t temp = tarefas[i];
                tarefas[i] = tarefas[j];
                tarefas[j] = temp;
            }
            
        }
        
    }

    return;
}

int main(){
    
    int num_casos = 0, k = 0;
    scanf("%d",&num_casos);
    getchar();
    while (k<num_casos)
    {
        int jobs = 0, l = 0;
        scanf("%d",&jobs);
        getchar();
        tar_t* tarefas = (tar_t*)malloc(jobs*sizeof(tar_t));
        while (l<jobs)
        {
            scanf("%d",&tarefas[l].lenght);
            scanf("%d",&tarefas[l].weight);
            tarefas[l].ratio = tarefas[l].weight / (double)tarefas[l].lenght; 
            
            getchar();

            l++;
        }
        

        solve(tarefas,jobs);

        printf("%d\n",agendamento(tarefas,jobs));
        free(tarefas);
        k++;
    }
    




    return 0;
}