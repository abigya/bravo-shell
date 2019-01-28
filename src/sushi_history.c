#include <stdlib.h>
#include <stdio.h>
#include "sushi.h"

static char *history[SUSHI_HISTORY_LENGTH] = {NULL};
static int i = 0;

void sushi_store(char *line){
   //make sure line is not NULL
    if (line!=NULL){
      history[i] = malloc((SUSHI_MAX_INPUT+1));
      strncpy(history[i],line,SUSHI_MAX_INPUT);
      i++;
    }
    //check if history is full and remove recently inserted string
    int hist =  SUSHI_HISTORY_LENGTH;
    if (i>(hist-1)){
      strncpy(history[i],"",SUSHI_MAX_INPUT);
      free(history[i]);
    }
 }

void sushi_show_history() {
    for(int j=0;j<i;j++){
        fprintf(stdout,"%d   %s",j+1,history[j]);
    }
}
