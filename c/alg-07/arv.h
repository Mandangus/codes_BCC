typedef struct no no_t;
typedef struct arv
{
    no_t* raiz;
}arv_t;
void insert_esq(arv_t*arvore,int id,int pai);
void insert_dir(arv_t*arvore,int id,int pai);
arv_t* initialize();
no_t* pai(no_t* raiz,int id);
void montar(arv_t* arvore,int n);