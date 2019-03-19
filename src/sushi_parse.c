#include <string.h>
#include <ctype.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "sushi.h"
#include "sushi_yyparser.tab.h"
#include <stdlib.h>

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
            break;
          case 'a' :
            new_str[count] = '\a';
            break;

          case 'b' :
            new_str[count]= '\b';
            break;

          case 'f' :
            new_str[count]= '\f';
            break;

          case 'r' :
            new_str[count]= '\r';
            break;

          case 't' :
            new_str[count]= '\t';
            break;
          case 'v' :
            new_str[count]= '\v';
            break;

          case '\'' :
            new_str[count]= '\'';
            break;

          default :
            new_str[count]= '\\';
            break;
    } 
    i++;
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
    int arsize = exe->args.size;
    for (int i=0; i<arsize;i++){
    	if(exe->args.args[i]!=NULL){
        	free(exe->args.args[i]);    
        }
     }
     free(exe->args.args);
     if (exe->redirection.in!=NULL){
          free(exe->redirection.in);
     } 
      if (exe->redirection.out1!=NULL){
          free(exe->redirection.out1);
     } 
      if (exe->redirection.out2!=NULL){
          free(exe->redirection.out2);
     } 
    
    free(exe);
 
  
}

// Skeleton
void sushi_assign(char *name, char *value) {
    setenv(name,value,strlen(value));
    free(value);
    free(name);
}

// Skeleton
char *sushi_safe_getenv(char *name) {
  char *vname =  getenv(name);
  if (vname!=NULL){
      return vname;
  }else{
  	return ""; 
 }

}


int sushi_spawn(prog_t *exe, prog_t *pipe, int bgmode) {
   pid_t child;
   int status;
   pid_t c;
   
  int size = exe->args.size;
  exe->args.args = super_realloc(exe->args.args,(size+1)*sizeof(char*));
  exe->args.args[size] = NULL;
  child = fork(); //fork new process
  

  if (child ==0 && bgmode ==1){ //child process
      setpgid(child,0); //create new process group leader
      execvp(exe->args.args[0],exe->args.args); //execute background process
      exit(0);
  }
  if (child ==0 && bgmode !=1){
     execvp(exe->args.args[0],exe->args.args);
  }else if(bgmode!=1){//parent process
     free_memory(exe,pipe);
     waitpid(child,&status,WUNTRACED);
    
     char *retval = malloc(sizeof(status));
     sprintf(retval,"%d",status);
     setenv("_",retval,strlen(retval));
  }
 
  return 0;
  
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
char *super_strdup(void *ptr){
  void* result = strdup(ptr);
  if(NULL == result){
    abort();
  }
  return result;
}



