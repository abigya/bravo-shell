#include <string.h>
#include <ctype.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "sushi.h"
#include "sushi_yyparser.tab.h"

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
    if(s[i] == '\\'  && !(&s[i+1] == NULL) ){
      switch(s[i+1]){
          case 'n' :
            new_str[count]= '\n';
            i++;
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

          default :
            new_str[count]= '\\';
            i++;
            break;
    } 
    }else{
      new_str[count] = s[i];
    }
    
  }
  return new_str;
}
// Do not modify these functions
void yyerror(const char* s) {
  fprintf(stderr, "Parse error: %s\n", s);
}
void __not_implemented__() {  
  fputs("This operation is not implemented yet\n", stderr);
}

// Function skeletons for HW3
void free_memory(prog_t *exe, prog_t *pipe) {
  // TODO - but not this time
}

int spawn(prog_t *exe, prog_t *pipe, int bgmode) {
   pid_t child;
   int status;
   pid_t c;
   
  int size = exe->args.size;
  super_realloc(exe->args.args,(size+1)*sizeof(char*));
  exe->args.args[size] = NULL;

  if ((child = fork())==0){
    fprintf(stdout,"This is the child process.\n");
    execvp(exe->args.args[0],exe->args.args);
    
   fprintf(stderr,"Child could not be created!\n");
   exit(0);
  
  }else{
  	if (child==(pid_t)(-1)){
             fprintf(stderr,"fork failed!\n");
             exit(0);
        }else{
           c = wait(&status);
            fprintf(stdout,"child process has ended.\n");
        }
  }
  free_memory(exe,pipe);
  return 0;
  
  
 
  /**int status = fork();
  if(status == 0){
    //this is the child process
    fprintf(stdout,"This is the child process.\n");
    int size = exe->args.size;
    super_realloc(exe->args.args, (size+1)*sizeof(char*));
    
    exe->args.args[size] = NULL;

    if(execvp(exe->args.args[0],exe->args.args) == -1){
      exit(0);
    
    }
    free_memory(exe,pipe);
  }else if(status>0){
    fprintf(stdout,"This is the parent process.\n");

  }else{
 	fprintf(stdout,"Child could not be created!\n");
  }  
    
  
  return status;**/
  
}

void *super_malloc(size_t size) {
   void* result = malloc(size);
  if(NULL == result){
    abort();
  }
  return result;
}

void *super_realloc(void *ptr, size_t size) {
  void* result = realloc(ptr, size);
  if(NULL == result){
    abort();
  }
  return result;
}
void *super_strdup(void *ptr){
  void* result = strdup(ptr);
  if(NULL == result){
    abort();
  }
  return result;
}



