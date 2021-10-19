typedef struct no no_t;
int minimo(no_t* raiz);//dada uma raiz retorna o menor valor da arvore ou sub-arvore pertencente
int maximo(no_t* raiz);//dada uma raiz retorna o maior valor da arvore ou sub-arvore pertencente
no_t* pai(no_t* raiz,int chave);//dada a chave e a raiz de uma arvore retorna um ponteiro para o pai do no cuja chave pertence
void printord(no_t*raiz);//print em ordem
no_t* insert(no_t* raiz,int chave);//insere respeitando as regras listadas no .c da llrb
no_t* predecessor(no_t*raiz,int chave);//dada uma raiz e uma chave retorna o predecessor do no cuja chave pertence
no_t* sucessor(no_t*raiz,int chave);//dada uma raiz e uma chave retorna o sucessor do no cuja chave pertence
void printpre(no_t*raiz);//print em preordem
void printposord(no_t*raiz);//print em posordem