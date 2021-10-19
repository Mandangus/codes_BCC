typedef struct treap t_t;
typedef struct no no_t;
typedef struct fila fila_t;

char* read_line();
int comando(char* entry);
int comando_printf(char* entry);
no_t* remover(no_t* raiz,int chave);
void printar_larg(no_t* raiz,fila_t* fi);
no_t* update(no_t* raiz);
no_t* insert(no_t* raiz,int chave,int prio);
no_t* busca(no_t* raiz,int chave);
void printposord(no_t*raiz);
void printord(no_t*raiz);
void printpre(no_t*raiz);
fila_t* initialize();