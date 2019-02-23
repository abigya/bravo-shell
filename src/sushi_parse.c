#include <stdlib.h>
#include <stdio.h>
#include "sushi_yyparser.tab.h"
#include <string.h>
#include <ctype.h>

// https://en.wikipedia.org/wiki/Escape_sequences_in_C#Table_of_escape_sequences
char *sushi_unquote(char *s) {
  char *new_str;
  new_str = (char*)malloc(sizeof(char)*strlen(s)+1);
  size_t i = 0;
  size_t count =0;
  size_t length = strlen(s);
  //
  if(length < 2 ){
    strcpy(new_str,s);
    return new_str;
  }
  for(i = 0; i < length; i++, count++){
    //compare the chr to the list of esp chars
    if(s[i] == '\\'  && !(&/* DZ: No &! */s[i+1] == NULL) ){
      switch(s[i+1]){
          case 'n' :
            new_str[count]= '\n';
            i++; // DZ: You repeated this line 10 times.
            break;
          case 'a' :
            new_str[count] = '\a';
            i++;
            break;

          case 'b' :
            new_str[count]= '\b';
            i++;
            break;

          case 'f' :
            new_str[count]= '\f';
            i++;
            break;

          case 'r' :
            new_str[count]= '\r';
            i++;
            break;

          case 't' :
            new_str[count]= '\t';
            i++;
            break;
          case 'v' :
            new_str[count]= '\v';
            i++;
            break;

          case '\'' :
            new_str[count]= '\'';
            i++;
            break;

          case '\\' :
            new_str[count]= '\\';
            i++;
            break;

          //case 'e' :
            //new_str[count] = '\e';
            //i++;
            //break;

      default:  // DZ: No need to implement this
            if(s[i+1] == 'x'){
              //Largest Hexidecimal number in 32bit sys, '7FFF,FFFF' (8 bytes).
              char* number = (char*)malloc(sizeof(char)*8);
              int k;
              for(k = 2; isxdigit(s[i+k]); k++){
                number[k-2] = s[i+k];
              }
              number[k-1]= '\0';
              new_str[count] = (char)strtol(number, NULL, 16);
              i += strlen(number);
              free(number);
            }
            else if (s[i+1] == 'u')
            {
              //Only 4 chars needed
              char* number = (char*)malloc(sizeof(char)*4);
              int k;
              for(k = 2; isxdigit(s[i+k]); k++){
                number[k-2] = s[i+k];
              }
              number[k-1]= '\0';
              new_str[count] = (char)strtol(number, NULL, 16);
              i += strlen(number);
              free(number);  
            }
            else if (isdigit(s[i+1]))
            {
              char* number = (char*)malloc(sizeof(char)*3);
              int k;
              for(k = 2; isdigit(s[i + k]); k++){
                number[k-2] = s[i+k];
              }
              number[k-1]= '\0';
              i += strlen(number);
              new_str[count] = (char)strtol(number, NULL, 8);
              free(number);
          }
          else if (s[i+1] == 'U')
          {
              //Only 8 bits needed
              char* number = (char*)malloc(sizeof(char)*8);
              int k;
              for(k = 2; isxdigit(s[i+k]); k++){
                number[k-2] = s[i+k];
              }
                number[k-1]= '\0';
                i += strlen(number);
                new_str[count] = (char)strtol(number, NULL, 16);
                free(number);
          }        
       }
    }
    else
    {
      new_str[count] = s[i];
    }
    
  }
  return new_str;
}
// Do not modify this function
void yyerror(const char* s) {
  fprintf(stderr, "Parse error: %s\n", s);
}
