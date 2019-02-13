#include <stdlib.h>
#include <stdio.h>
#include "sushi.h"


#define FILENAME "$HOME/sushi.conf"

int main(int argc, char *argv[]) {
    //passed stdin to file pointer since sushi_read_line has a File pointer as a parameter 
    FILE *f = stdin;
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


