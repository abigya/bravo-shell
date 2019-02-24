#include <libgen.h>
#include <string.h>
#include "sushi.h"

int sushi_exit = 0;

static void refuse_to_die(int sig)
{
  // TODO
}

static void prevent_interruption() {
  // TODO
}

int main(int argc, char *argv[]) {
    char *path = "$HOME/sushi.conf";
    char *tok1 = strdup(path);
    char *tok2 = strdup(path);
    char *filename = basename(tok2);
    FILE *f = stdin; //stdin is passed as file for read_line
    int p;
    char *input;
    sushi_read_config(filename);
    
    prevent_interruption();
    
    while(sushi_exit==0){
     fprintf(stdout,"%s",SUSHI_DEFAULT_PROMPT);
     input = sushi_read_line(f);
     if (input!=NULL){
      	p = sushi_parse_command(input);
      }
     //not sure if ! should be in the history array 
     if (p==0){
     	sushi_store(input);
     }
   
    }

    return 0;
}

