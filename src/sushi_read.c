#include <stdlib.h>
#include <stdio.h>
#include "sushi.h"
#include <string.h>
#include <ctype.h>


//strlcpy is not provided on windows so i created a function
//credits : stackoverflow
void strlcpy(char* dst, const char* src, size_t bufsize){
  size_t srclen =strlen(src);
  size_t result =srclen; /* Result is always the length of the src string */
  if(bufsize>0)
  {
    if(srclen>=bufsize)
       srclen=bufsize-1;
    if(srclen>0)
       memcpy(dst,src,srclen);
    dst[srclen]='\0';
  }
}
char *sushi_read_line(FILE *in) {
  //create buffer for line
  char *buffer;
  buffer = (char*)malloc(sizeof(char)*SUSHI_MAX_INPUT+1);
  ssize_t line; //number of characters read by the buffer
  size_t len = SUSHI_MAX_INPUT; // number of bytes in the read buffer    
  line = getline(&buffer, &len, in); // check this line 
  
  //check for errors in I/O
  if (line ==-1){ //check this line 
    perror("There is some error with the input!\n");
    return NULL;
  }
  //check for blank line
  if (isspace(buffer[0])){
      return NULL;
  }

  //check length of line 
  char *string;
  size_t length;
  if (line>SUSHI_MAX_INPUT){
      fprintf(stderr,"Line is too long,truncated\n");
      length = SUSHI_MAX_INPUT;
      string = (char*)malloc(sizeof(char)*(SUSHI_MAX_INPUT+1));

      strlcpy(string,buffer,length);
      return string;

    }else{
      buffer[strcspn(buffer, "\n")] = 0;
       length = line;
      string = (char*)malloc(sizeof(char)*(line+1));
      strlcpy(string,buffer,length);
      return string;
   
  }
 
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
      sushi_store(line);
    }

    fclose(infile);

  return 0;
}
