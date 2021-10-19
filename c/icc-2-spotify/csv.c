#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"csv.h"
#include<math.h>



struct registro
{
    double linha;//vai receber as distancias de cada track
    int indice;//vetor paralelo à linha que guarda o índice das tracks que fizeram a distancia com a track original na matrix
};

struct track//tipo musica
{
    char *name,*id,*albname,*albid,*date;
    int length,pop;
    double *atributos;//os 9 atributos da música!
    reg_t* dist;//vetor para a distancia e indice para a track que foi feita a distancia!
};
struct artist//tipo artista que contem uma lista de musicas
{
    char *name,*id;
    int song_num;
    double song_pop;
    track_t* songs;
};
struct lista//tipo lista que contem uma lista de artistas mais o numero de artistas e musicas totais
{
    int num_art,num_songs;
    artist_t* artistas;
};
struct matrix//tipo matri que guarda cada musica e o tamanho total
{
    track_t*coluna;
    int tam;
};


void remove_space(char*string){//removendo o espaço da formatação do .csv
    int len=strlen(string);
    for (int i = 0; i < len-1; i++)
    {
        string[i]=string[i+1];
    }
    string[len-1]='\0';
}
lista_t* initialize(){
    lista_t* l;
    l=(lista_t*)malloc(sizeof(lista_t));
    l->num_art=0;
    l->artistas=(artist_t*)malloc((BUFFER)*sizeof(artist_t));
    l->artistas[0].songs=(track_t*)malloc(BUFFER*sizeof(track_t));
    l->num_songs=0;
    return l;
};
char* read_line(){
    char* aux=(char*)malloc(BUFFER*sizeof(char));
    char letra;
    int pos=0;
    do
    {
        letra=getchar();
        if (letra!='\n'&&letra!='\r')
        {
            aux[pos]=letra;
        }
        pos++;
    } while (letra!='\n');
    aux[pos]='\0';
    return aux;
}
int search_artist(lista_t* l,char* nome){
    if (l->num_art==0)
    {
        return -1;
    }
    
    for (int i = 0; i < l->num_art; i++)
    {
        if (strcmp(l->artistas[i].name,nome)==0)
        {
            return i;
        }

    }
    return -1;

}//se existe o artista retorna o indice, caso contrário retorna -1





int busca(mat_t*matriz,int max,char*procura){
    //binary search básico só que sem recursão e com strcmp
    //buscamos por ID
    int esq = 0;
    int dir = max - 1;
    while (esq<=dir)
    {
        int meio = esq + (dir-esq) / 2;
        int indice = 0;
        if (strcmp(procura,matriz->coluna[meio].id)==0) return meio;    
        if (strcmp(procura,matriz->coluna[meio].id)>0) esq = meio + 1;
        if (strcmp(procura,matriz->coluna[meio].id)<0) dir = meio - 1;
    }
    //não achou!
    return -1;
    
}
void add_music(lista_t* l,char*t_id,char*t_name,int indice,char*t_date,char*t_len,char*t_pop,double*atributos,mat_t* matriz,char*a_name){//adicionar uma musica!
    //adicionando a track para o artista...
    int num=l->artistas[indice].song_num;
    l->artistas[indice].songs[num].albname=strdup(a_name);
    l->artistas[indice].songs[num].name=strdup(t_name);
    l->artistas[indice].songs[num].id=strdup(t_id);
    l->artistas[indice].songs[num].pop=atoi(t_pop);
    l->artistas[indice].songs[num].length=atoi(t_len);
    l->artistas[indice].songs[num].date=strdup(t_date);
    l->artistas[indice].songs[num].atributos=atributos;
    //adicionando a track para a coluna da matriz...
    matriz->coluna[matriz->tam]=l->artistas[indice].songs[num];
    l->artistas[indice].song_num++;
    l->num_songs++;
    matriz->tam++;
}
void add_art(lista_t* l,char*t_id,char*t_name){//adicionar um artista
    l->artistas[l->num_art].name=strdup(t_name);
    l->artistas[l->num_art].id=strdup(t_id);
    l->artistas[l->num_art].songs=(track_t*)malloc(BUFFER*sizeof(track_t));
    l->artistas[l->num_art].song_num=0;
    l->artistas[l->num_art].song_pop=0;
    l->num_art++;
}
void find_pop(lista_t* l){//media aritmetica da popularidade de cada musica de cada artista
    for (int i = 0; i < l->num_art; i++)
    {
        int sum=0;
        for (int j = 0; j < l->artistas[i].song_num; j++)
        {
            sum+=l->artistas[i].songs[j].pop;
        }
        l->artistas[i].song_pop=sum/l->artistas[i].song_num;
    }
    
}
void artcpy(artist_t*a,artist_t*aux){
    //src a para dest aux
    aux->id=strdup(a->id);
    aux->name=strdup(a->name);
    aux->songs=a->songs;
    aux->song_num=a->song_num;
    aux->song_pop=a->song_pop;
}
void trocar(artist_t*a,artist_t*b){
    artist_t* aux=(artist_t*)malloc(sizeof(artist_t));
    aux->songs=(track_t*)malloc(BUFFER*sizeof(track_t));
    artcpy(a,aux);//similar ao strcpy()!
    artcpy(b,a);
    artcpy(aux,b);
}
void sortar(lista_t* l){
    int flag=0;
    do
    {
        flag=0;
        for (int j = 0; j < l->num_art-1; j++)
        {
            if (l->artistas[j].song_pop<l->artistas[j+1].song_pop)
            {
                trocar(&l->artistas[j],&l->artistas[j+1]);
                flag=1;
            }
            
        } 
    } while (flag!=0);
    
}

mat_t* ini_matrix(){//inicializar a matriz com espaço suficiente para as tracks
    mat_t* matriz = malloc(sizeof(mat_t));
    matriz->coluna = malloc(30*BUFFER*sizeof(track_t));
    matriz->tam = 0;
    return matriz;
}
double distancia(track_t a,track_t b){
    double d,sum=0;
    for (int i = 0; i < 9; i++)
    {//obtemos primeiro (a1-b1)^2 + (a2-b2)^2
        sum +=pow((a.atributos[i]-b.atributos[i]),2);
    }
    //depois tiramos a raíz
    d = sqrt(sum);
    return d;
}
void printar(lista_t* l){ 
    find_pop(l);//setamos a popularidade de cada artista
    sortar(l);//sort básico para arrumar por popularidade
    printf("O Dataset contem %d Artistas e %d Musicas\n",l->num_art,l->num_songs);
    printf("Os artistas mais populares sao:\n");
    for (int i = 0; i < l->num_art; i++)
    {
        printf("(%d) Artista: %s, Musicas: %d musicas, Popularidade: %.2lf, Link: https://open.spotify.com/artist/%s\n",i+1,l->artistas[i].name,l->artistas[i].song_num,l->artistas[i].song_pop,l->artistas[i].id);
    }
    
}
//aqui damos um cast de const void* para o tipo track para que possamos usar a função strcmp no qsort
//assim sortaremos a COLUNA pelo ID
int compare(const void*a,const void*b){
    track_t* aa = (track_t*)a;
    track_t* bb = (track_t*)b;
    return strcmp(aa->id,bb->id);
}
//aqui calculamos o valor de cada distancia e o indice da track que o alvo fez distancia com!
reg_t* calc_linha(track_t a,mat_t* matriz){
    reg_t* temp = (reg_t*)malloc(matriz->tam*sizeof(reg_t));
    for (int i = 0; i < matriz->tam; i++)
    {
        temp[i].linha=distancia(a,matriz->coluna[i]);
        temp[i].indice=i;
    }
    return temp;
}
void radix(track_t* a,int tam){
    //base fixa 256 + counting sort
    int P = 1000000;
    double count[256]={0};
    int pos[256];
    reg_t* copia = (reg_t*)malloc(tam*sizeof(reg_t));
    for (int shift = 0; shift <= 24; shift+=8)
    {
        for (int i = 0; i < tam; i++)
        {
            short k = ((int)round(a->dist[i].linha*P)>>shift) & 255;
            count[k]++;
            copia[i]=a->dist[i];
        }
        pos[0] = 0;
        for (int j = 1; j < 256; j++)
        {
            pos[j] = pos[j-1] + count[j-1];
            count[j-1] = 0;
        }
        for (int i = 0; i < tam; i++)
        {
            short k = ((int)round(copia[i].linha*P)>>shift) & 255;
            a->dist[pos[k]] = copia[i];
            pos[k]++;
        }
        
    }
}
//aqui temos a função principal dessa entrega.
void similarity(int Q,int K,mat_t* matriz){
    int x =0;
    char*procura;
    int index;
    do
    {
        procura=read_line();
        index = busca(matriz,matriz->tam,procura);//fazemos um binary search para achar o ID e guardamos o indice em index
        matriz->coluna[index].dist=calc_linha(matriz->coluna[index],matriz);//calculamos as distancias SOMENTE com essa track assim nos salvamos do caso O(n^2/2) que era montar essa matriz inteira!
        radix(&matriz->coluna[index],matriz->tam);//fazemos o radix so da linha selecionada economizando tempo
        printf("----As %d musicas mais parecidas com %s sao:\n", K, matriz->coluna[index].name);
        for (int i = 0; i < K; i++)
        {
            int pos = matriz->coluna[index].dist[i].indice;//para simplificar a sintaxe..
            printf("\t(%d)Artista: %s\n", i, matriz->coluna[pos].albname);
            printf("\t\tMusica: %s\n", matriz->coluna[pos].name);
            printf("\t\tDissimilaridade: %lf\n", matriz->coluna[index].dist[i].linha);
            printf("\t\tLink: https://open.spotify.com/track/%s\n", matriz->coluna[pos].id);
        }
        printf("\n");
        x++;
    } while (x<Q);
    
    return;
}
void print_mat(mat_t* matriz){
    //sortamos apenas as tracks da coluna com qsort
    qsort(matriz->coluna,matriz->tam,sizeof(track_t),compare);
    int q,k;
    scanf("%d %d\n",&q,&k);
    similarity(q,k,matriz);
}