#include <stdlib.h>
#include <stdio.h>
#include <libgen.h>
#include <string.h>
#include "sushi.h"

int sushi_exit = 0;
int main(int argc, char *argv[]) {
  // DZ: There is no such file "$HOME/sushi.conf"
  // DZ: $HOME must be replaced by its value using getenv()
    char *path = "$HOME/sushi.conf";
    char *tok1 = strdup(path); // DZ - ???
    char *tok2 = strdup(path); // DZ - ???
    char *filename = basename(tok2); // DZ - ???
    // DZ: Why not pass stdin directly? Do not copy vatiables without a need
    FILE *f = stdin; //stdin is passed as file for read_line
    int p;
    char *input;
    sushi_read_config(filename);
   
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

