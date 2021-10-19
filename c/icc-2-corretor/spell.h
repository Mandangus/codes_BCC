#define BUFFER 46
typedef struct list lis_t;
lis_t* initialize();
char* read_line();
char* tweet_txt(FILE* fp);
void parse_txt(FILE *fp,lis_t* lista);
void parse_tweet(char* tweet,lis_t* livro);