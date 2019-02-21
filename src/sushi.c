#include <stdlib.h>
#include <stdio.h>
#include "sushi.h"



#define FILENAME "sushi.conf" // DZ: Must be $HOME/sushi.conf
int sushi_exit = 0;
int main(int argc, char *argv[]) {
    FILE *f = stdin; // DZ: ???
    int p;
    char *input;
    sushi_read_config(FILENAME);
    //testing history function
    while(sushi_exit==0){
     fprintf(stdout,"%s",SUSHI_DEFAULT_PROMPT);
     input = sushi_read_line(f);
     p = sushi_parse_command(input);
     if (p==0){
     	sushi_store(input);
     }
    }

    return 0;
}

