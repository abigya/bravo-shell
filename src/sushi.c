#include <stdlib.h>
#include <stdio.h>
#include "sushi.h"


#define FILENAME "sushi.conf" // DZ: Must be $HOME/sushi.conf

int main(int argc, char *argv[]) {
  FILE *f = stdin; // DZ: ???
    int status;
    char *input;
    status = sushi_read_config(FILENAME);
    //testing history function
    if (status==0){
     fprintf(stdout,"%s",SUSHI_DEFAULT_PROMPT);
     input = sushi_read_line(f);
     sushi_store(input);
     sushi_show_history();
    }else{
        return EXIT_FAILURE;
    } 
    
    return EXIT_SUCCESS;

}


