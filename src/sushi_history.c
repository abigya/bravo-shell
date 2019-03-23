#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "sushi.h"

static int count = 0;
static char *history[SUSHI_HISTORY_LENGTH] = {NULL};

void sushi_store(char *line){
 
  //if history is not empty shift elements to right by 1
   if (line != NULL ){ 
     for(int i = count;i>0;i--){
      history[i]=history[i-1];
    }
      history[0]=line;
      count++;
  }
  //delete oldest element in history
  if(count>(SUSHI_HISTORY_LENGTH-1)){
	fprintf(stdout,"History is full\n");
        history[SUSHI_HISTORY_LENGTH-1]=NULL;
        count = SUSHI_HISTORY_LENGTH-1;
  
   } 
   
 }

void sushi_show_history() {
    for(int j=0;j<count;j++){
        fprintf(stdout,"%5d%*s%s\n",j+1,2,"",history[j]);
    }
}
