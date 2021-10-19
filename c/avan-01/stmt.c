#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define VERBOSE 0 /// usado para imprimir em extenso o tempo de xecução do algoritimo


int** getMatriz(int num_casamentos){ // dado um numero de casamentos desejados alocamos uma matriz de preferencia
    int **pref_w = (int**)malloc((num_casamentos)*sizeof(int*));
    for (int k = 0; k < num_casamentos; k++)
    {
        pref_w[k] = (int*)malloc((num_casamentos)*sizeof(int));
    }
    return pref_w;
}

void scanMatriz(int num_casamentos, int** pref_w){
    for (int k = 0; k < num_casamentos; k++)// atribuindo os valores da entrada para a matriz
    {
        int temp;
        scanf("%d",&temp);//dando scan no primeiro digito da linha
        for (int j = 0; j < num_casamentos; j++)
        {
            int pessoa = 0;
            scanf("%d",&pessoa);
            pref_w[k][j] = pessoa - 1;// -1 pois o programa está indexado em 0 e a entrada em 1
        }
        getchar();//\n
    }
    return;
}

void freeMatriz(int**pref_w,int num_casamentos){
    for (int i = 0; i < num_casamentos; i++)
    {
        free(pref_w[i]);   
    }
    free(pref_w);
}

int isFree(int* vect,int n){//retorna o primeiro homem livre, caso não haja retorna -1

    for (int i = 0; i < n; i++)
    {
        if(vect[i]==-1) return i;
    }
    

    return -1;
}
int searchPref(int*pref,int n,int key){
    for (int i = 0; i < n; i++)
    {
        if(pref[i]==key) return i;
    }
    return -1;
}

int* stableMatching(int**pref_w,int**pref_m,int num_casamentos){
    int* wife = (int*)malloc(num_casamentos*sizeof(int));//lista de casamento das mulheres...
    int* husband = (int*)malloc(num_casamentos*sizeof(int));//          ... e dos homens
    for (int i = 0; i < num_casamentos; i++) wife[i] = husband[i] = -1;
    
    int* count = (int*)calloc(num_casamentos,sizeof(int));//numero de propostas feitas por cada homem

    int k = isFree(wife,num_casamentos);
    while (k!=-1 && count[k]!=num_casamentos)
    {
        int w = pref_m[k][count[k]];//pegamos a mulher que o k ainda n propos
        int prefk = searchPref(pref_w[w],num_casamentos,k);//posicao de k na pref de w
        
        if (husband[w]==-1)
        {
            husband[w] = k;
            wife[k] = w;
            
        }else if (prefk<searchPref(pref_w[w],num_casamentos,husband[w])){
            int temp = husband[w];
            husband[w] = k;
            wife[k] = w;
            wife[temp] = -1;
        }
        count[k]++;
        k = isFree(wife,num_casamentos);
    }
    



    free(husband);
    free(count);
    return wife;
}

void printResult(int* resultado,int n){
    for (int i = 0; i < n; i++)
    {
        int k = resultado[i] +1;//voltando a indexação em 1
        printf("%d %d\n",i+1,k);
    }
    
}

int main(){
    clock_t inicio,fim;
    int num_entr = 0;//numero de casos teste do problema
    scanf("%d",&num_entr);
    getchar();
    
    for (int i = 0; i < num_entr; i++)
    {
        int num_casamentos = 0;//numero de pares que devem ser arrumados no caso
        scanf("%d",&num_casamentos);
        getchar();//\n

        int** pref_w = getMatriz(num_casamentos);//alocando uma matriz de preferencia das mulheres...
        int** pref_m = getMatriz(num_casamentos);//         ... e dos homens

        scanMatriz(num_casamentos,pref_w);//dando scan na entrada do probelma para as mulheres...
        scanMatriz(num_casamentos,pref_m);//            ... e para os homens

        inicio = clock();
        int* resultado = stableMatching(pref_w,pref_m,num_casamentos);//resultado baseado nos homens
        fim = clock();
        printResult(resultado,num_casamentos);
        if (VERBOSE)
        {
            double total = (double)(fim-inicio) / (double)(CLOCKS_PER_SEC);
            printf("O tempo tomado para toda a execução foi %lf milisegundos\n",total*1000);
        }
        
        free(resultado);
        freeMatriz(pref_m,num_casamentos);
        freeMatriz(pref_w,num_casamentos);
    }
    



    return 0;
}