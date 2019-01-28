#include <stdlib.h>
#include <stdio.h>
#include "sushi.h"
#include "sushi_read.c"
#include "sushi_history.c"

#define FILENAME "sushi.conf"

int main(int argc, char *argv[]) {
    FILE *f = stdin;
    int status;
    char *input;
    status = sushi_read_config(FILENAME);
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

