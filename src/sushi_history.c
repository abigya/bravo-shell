#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "sushi.h"

static int count = 0;
static char *history[SUSHI_HISTORY_LENGTH] = {NULL};

void sushi_store(char *line){
 
   int hist =  SUSHI_HISTORY_LENGTH;
  //if history is not empty shift elements to right by 1
   if (line != NULL ){ 
     for(int i = count;i>0;i--){
      history[i]=history[i-1];
    }
      history[0]=line;
      count++;
  }
  //delete oldest element in history, this code seems to work fine, program gives weird output without this code 
  //I am not sure why
  if(count>(hist-1)){
	fprintf(stdout,"History is full\n");
        free(history[hist-1]);
        count = hist-1;
  
   } 
   
 }

void sushi_show_history() {
  //i get segmentation fault if i use sizeof(history) here
    for(int j=0;j<count;j++){
        fprintf(stdout,"%5d%*s%s\n",j+1,2,"",history[j]);
    }
}
