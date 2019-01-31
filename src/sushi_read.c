#include <stdlib.h>
#include <stdio.h>
#include "sushi.h"
#include <string.h>
#include <ctype.h>

char *sushi_read_line(FILE *in) {
  //create buffer for line
  char *buffer;
  buffer = (char*)malloc(sizeof(char)*SUSHI_MAX_INPUT+1);
  ssize_t line; //number of characters read by the buffer
  size_t len = SUSHI_MAX_INPUT; // number of bytes in the read buffer    
  line = getline(&buffer, &len, in);
  
  //check for errors in I/O
  if (line==-1){
    perror("There is some error with the input!\n");
    return NULL;
  }
  //check for blank line
  if (isspace(buffer[0])){
      return NULL;
  }

  //check length of line 
  char *string;
  if (line>SUSHI_MAX_INPUT){
      fprintf(stderr,"Line is too long,truncated\n");
      string = (char*)malloc(sizeof(char)*(SUSHI_MAX_INPUT+1));
      strncpy(string,buffer,SUSHI_MAX_INPUT);
      string[strlen(string)]='\0';

    }else{
      buffer[strcspn(buffer, "\n")] = 0;
      string = (char*)malloc(sizeof(char)*(line+1));
      strncpy(string,buffer,line);
   
  }
  return string;
}

 
int sushi_read_config(char *fname) {
  FILE *infile;
   if (NULL == (infile = fopen(fname,"r"))){
        perror("Error!");
        return 1;
    }
    char *line;
    while (!feof(infile)){
      line = sushi_read_line(infile);
    }

    fclose(infile);

  return 0;
}

 
