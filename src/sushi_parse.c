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
  // TODO - but not this time
}

// Skeleton
void sushi_assign(char *name, char *value) {
}

// Skeleton
char *sushi_safe_getenv(char *name) {
  return NULL; // DZ: change it!
}


int sushi_spawn(prog_t *exe, prog_t *pipe, int bgmode) {
   pid_t child;
   int status;
   pid_t c;
   
  int size = exe->args.size;
  exe->args.args = super_realloc(exe->args.args,(size+1)*sizeof(char*));
  exe->args.args[size] = NULL;
  child = fork(); //fork new process
  
  /**if (child!=0 && bgmode==0){
      waitpid(-1,&status,WNOHANG);
  }**/
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

    if (status==0){
        perror("Child process terminated normally\n");
    }

    if (status==1){
        perror("Child process terminated with an error\n");
    }
  }
  
 /**if (child ==0){
     execvp(exe->args.args[0],exe->args.args);
     free_memory(exe,pipe);
    perror("Child could not be created!\n");
    exit(0);
  
  }else{
  	if (child==(pid_t)(-1)){
             perror("fork failed!\n");
             exit(0);
        }else{
           //execvp(exe->args.args[0],exe->args.args);
           c = wait(&status);
            
        }
  }**/
 
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



