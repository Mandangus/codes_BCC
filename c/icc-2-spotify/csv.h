#define BUFFER 1024
typedef struct track track_t;
typedef struct artist artist_t;
typedef struct matrix mat_t;
typedef struct registro reg_t;
typedef struct lista lista_t;
lista_t* initialize();
int search_artist(lista_t* l,char* nome);
void alocar(lista_t* l);
void add_music(lista_t* l,char*t_id,char*t_name,int indice,char*t_date,char*t_len,char*t_pop,double*atributos,mat_t*matriz,char*a_name);
mat_t* ini_matrix();
void add_matrix(mat_t*matriz,char* t_id,char* t_name,char* a_name);
void print_mat(mat_t*matriz);
void add_art(lista_t* l,char*a_id,char*a_name);
void printar(lista_t* l);
void remove_space(char*string);
void sortar(lista_t* l);
char* read_line();