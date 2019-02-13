#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "sushi.h"

static char *history[SUSHI_HISTORY_LENGTH] = {NULL};

void sushi_store(char *line){
  //shift elements to right by 1 and put new command on top
  if (line != NULL){
     for(int i = sizeof(history);i>0;i--){
      history[i]=history[i-1];
     }
      history[0]=line;
  }
   
 }

void sushi_show_history() {
    for(int j=0;j<(int)sizeof(history);j++){
        fprintf(stdout,"%5d%*s%s\n",j+1,2,"",history[j]);
    }
}
