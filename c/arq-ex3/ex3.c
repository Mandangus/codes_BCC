#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define BUFFER 1024
#define MAXSIZESTR 50

void binarioNaTela(char *nomeArquivoBinario) { /* Você não precisa entender o código dessa função. */

	/* Use essa função para comparação no run.codes. Lembre-se de ter fechado (fclose) o arquivo anteriormente.
	*  Ela vai abrir de novo para leitura e depois fechar (você não vai perder pontos por isso se usar ela). */

	unsigned long i, cs;
	unsigned char *mb;
	size_t fl;
	FILE *fs;
	if(nomeArquivoBinario == NULL || !(fs = fopen(nomeArquivoBinario, "rb"))) {
		fprintf(stderr, "ERRO AO ESCREVER O BINARIO NA TELA (função binarioNaTela): não foi possível abrir o arquivo que me passou para leitura. Ele existe e você tá passando o nome certo? Você lembrou de fechar ele com fclose depois de usar?\n");
		return;
	}
	fseek(fs, 0, SEEK_END);
	fl = ftell(fs);
	fseek(fs, 0, SEEK_SET);
	mb = (unsigned char *) malloc(fl);
	fread(mb, 1, fl, fs);

	cs = 0;
	for(i = 0; i < fl; i++) {
		cs += (unsigned long) mb[i];
	}
	printf("%lf\n", (cs / (double) 100));
	free(mb);
	fclose(fs);
}



int main(int argc,char* argv[]){
    char filename[20];//pegamos o nome do arquivo
    int n;
    scanf("%s",filename);//pegamos a qunatidade de entradas
    getchar();//tratando do \n 
    scanf("%d",&n);
    FILE *fp=fopen(filename,"wb");//abrindo em write binary
    if (fp==NULL) printf("Erro ao criar arquivo!\n");//tratamos um possivel erro...
    for (int i = 0; i < n; i++)
    {
        int idade,id;
        char nome[MAXSIZESTR];
        scanf("%d %s %d",&id,nome,&idade);//coletando a entrada
        getchar();//tratando do \n 
        fwrite(&id,sizeof(int),1,fp);//escrevendo o id
        int len = strlen(nome);//aqui fazemos len+1 = '\0' para garantir o terminador de string na pos correta
        nome[len+1]='\0';
        fwrite(nome,sizeof(char),len+1,fp);//escrevemos a str atentando ao novo tamanho correto
        fwrite(&idade,sizeof(int),1,fp);//mesmo procedimento do id 
    }
    fclose(fp);
    binarioNaTela(filename);


    return 0;
}