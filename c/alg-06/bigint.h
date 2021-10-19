#define BUFFER 1024
typedef struct no no_t;
typedef struct lista lista_t;
char* read_line();
int comando(char* entry);
lista_t* ini();
void big_int(lista_t*l,char*num);
void printar(lista_t*l);
int big(lista_t*num1,lista_t*num2);
lista_t* sum(lista_t*num1,lista_t*num2);
int sml(lista_t*num1,lista_t*num2);
int eql(lista_t*num1,lista_t*num2);