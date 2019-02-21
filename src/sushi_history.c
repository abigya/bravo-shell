#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "sushi.h"

static int count = 0;
static char *history[SUSHI_HISTORY_LENGTH] = {NULL};

void sushi_store(char *line){
 
   int hist =  SUSHI_HISTORY_LENGTH;
   // DZ: sizeof(history) is never 0; why not return at once if line==NULL?
  //if history is not empty shift elements to right by 1
   if (line != NULL){ 
     for(int i = count;i>0;i--){
      history[i]=history[i-1];
    }
      history[0]=line;
      count++;
  }

   
   
 }

void sushi_show_history() {
  // DZ: No need for count; unused items are NULLs
    for(int j=0;j<count;j++){
        fprintf(stdout,"%5d%*s%s\n",j+1,2,"",history[j]);
    }
}
