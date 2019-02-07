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
   if (line != NULL && sizeof(history)!= 0){ 
     for(int i = count;i>0;i--){
      history[i]=history[i-1];
    }
      history[0]=line;
      count++;
  }

   // DZ: sizeof(history) is never 0
   //add to first index if history is empty
   if(line!=NULL && sizeof(history)==0){
   	history[0]=line;
        count++;
   }
   
   // DZ: This part is wrong. The last item has been already removed
   // DZ: from the history above, too late to free it.
    //check if history is full and remove least recently inserted string 
    if (count>(hist-1)){
      fprintf(stdout,"history is full!\n");
      free(history[hist-1]);
      count = hist-1;
    }
   
 }

void sushi_show_history() {
  // DZ: No need for count; unused items are NULLs
    for(int j=0;j<count;j++){
        fprintf(stdout,"%5d%*s%s\n",j+1,2,"",history[j]);
    }
}
