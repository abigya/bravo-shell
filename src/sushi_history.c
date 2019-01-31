#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "sushi.h"

static int count = 0;
static char *history[SUSHI_HISTORY_LENGTH] = {NULL};

void sushi_store(char *line){
 
   int hist =  SUSHI_HISTORY_LENGTH;
  //if history is not empty shift elements to right by 1
  if (count<hist && count!=0){
    for(int i = count+1;i>0;i--){
      history[i]=history[i-1];
    }
  }
   
   if (line!=NULL){
      history[0] = malloc((strlen(line)+1));
      strncpy(history[0],line,strlen(line)+1);
      count++;
    }
  

    //check if history is full and remove recently inserted string
    
    if (count>(hist-1)){
      fprintf(stdout,"history is full!\n");
      free(history[0]);
    }
   
 }

void sushi_show_history() {
    for(int j=0;j<count;j++){
        fprintf(stdout,"%d   %s\n",j+1,history[j]);
    }
}

