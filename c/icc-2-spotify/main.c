#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"csv.h"
#include<math.h>



int main(int argc,char* argv[]){
    lista_t* l;
    l = initialize();//inicia-se uma lista
    char* entrada=read_line();//lendo a entrada
    FILE* fp=fopen(entrada,"r+");
    if (fp==NULL)
    {
        printf("ERRO!\n");
        return 0;
    }
    mat_t* matriz;//inicia-se uma matriz para usar na entrega 2
    matriz = ini_matrix();
    char line[BUFFER];
    int linha=0;
    while (fgets(line,sizeof(line),fp))//lendo até o final do documento linha por linha....
    {
        if (linha!=0)
        {
            double* atributos=malloc(9*sizeof(double));
            char** atr = malloc(9*sizeof(char*));
            char *token_t_id,*token_t_name,
            *token_al_id,*token_al_name,
            *token_art_id,*token_art_name,
            *token_t_date,*token_t_len,*token_t_pop;

            token_t_name = strtok(line,";");

            token_t_id = strtok(NULL,";");
            remove_space(token_t_id);//removemos o espaço do token afinal o .csv é formatado token_a; token_b; token_c; \n

            token_al_name = strtok(NULL,";");
            remove_space(token_al_name);

            token_al_id = strtok(NULL,";");
            remove_space(token_al_id);

            token_art_name = strtok(NULL,";");
            remove_space(token_art_name);

            token_art_id = strtok(NULL,";");
            remove_space(token_art_id);

            token_t_date = strtok(NULL,";");
            remove_space(token_t_date);

            token_t_len = strtok(NULL,";");
            remove_space(token_t_len);

            token_t_pop = strtok(NULL,";");
            remove_space(token_t_pop);

            /////////////aqui lemos os atributos como char* removemos o espaço do csv e fazemos um atof()//////////////////////
            for (int i = 0; i < 9; i++)
            {
                atr[i]=strtok(NULL,";");
                remove_space(atr[i]);
                atributos[i]=atof(atr[i]);
            }
            
            ///////////////////////////////////////
            if(search_artist(l,token_art_name)==-1)
            {//se for um novo artista adicionar...
                add_art(l,token_art_id,token_art_name);
            }
            //adicionar a musica ao respectivo artista E a matriz!
            add_music(l,token_t_id,token_t_name,search_artist(l,token_art_name),token_t_date,token_t_len,token_t_pop,atributos,matriz,token_art_name);
        }
        
        linha++;
    }
    //printar(l);   sortar a lista e printar os resultados! essa função foi usada na entrega passada e para motivos de debug!
    print_mat(matriz);//sortar a matriz e prinar os resultados!

    return 0;
}