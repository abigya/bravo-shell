#include <stdlib.h>
#include <stdio.h>
#include "sushi.h"
#include <string.h>
#include <ctype.h>

//static char *history[SUSHI_HISTORY_LENGTH] = {NULL};
char *sushi_read_line(FILE *in) {
  //create buffer for line
  char *buffer;
  buffer = (char*)malloc(sizeof(char)*SUSHI_MAX_INPUT+1);
  size_t line = 80; //number of characters read by the buffer
  size_t len = 81;//MAX_LINE_LENGTH; // number of bytes in the read buffer    
  line = getline(&buffer, &len, in);

  //check for errors in I/O
  if (line==-1){
    perror("There is some error with the input!");
    return NULL;
  }
  //check for blank line
  if (isspace(buffer[0])){
      return NULL;
  }
  //check length of line 
  if (line>SUSHI_MAX_INPUT){
      fprintf(stderr,"Warning! line %d is too long. Only %d characters will be used\n", SUSHI_MAX_INPUT);
      buffer[strlen(buffer)]='\0';
    }else{
     buffer[strcspn(buffer, "\n")] = 0;
  }
  return buffer;
}

 

int sushi_read_config(char *fname) {
   FILE* fp = fopen(fname,"r");
   if (NULL == fp){
        perror("Error opening file.");
        return 1;
    }

    char *line;
    while (0 != feof(fp)){
      line = sushi_read_line(fp);
      sushi_store(line);
    }
    fclose(fp);

  return 0;
}