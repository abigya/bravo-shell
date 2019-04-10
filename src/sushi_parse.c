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
  new_str = (char*)super_malloc(sizeof(char)*strlen(s)+1);
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
void free_memory(prog_t *exe) {
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


/*------------------------------------------------------------------
 * You can use these "convenience" functions as building blocks for
 * HW5 instead of your code, if you want. You may change them, too.
 *------------------------------------------------------------------*/

// Find the number of programs on the command line
static size_t cmd_length(prog_t *exe) {
  int count = 0;
  while(exe->prev) {
    exe = exe->prev;
    count++;
  }
  return count+1;
}

// Wait for the process pid to terminate; once it does, set the
// environmental variable "_" to the exit code of the process.
static int wait_and_setenv(pid_t pid) {
  int status;
  if (-1 == waitpid(pid, &status, 0)) {
    perror("waitpid");
    status = 1; // Something bad happened
  }
  char retval[16]; // Just to be safe
  sprintf(retval, "%d", status);
  if(-1 == setenv("_", retval, 1)) {
    perror("_");
    return 1;
  } else
    return 0;
}

// Execute the program defined in "exe"
static void start(prog_t *exe) {
  arglist_t args = exe->args;
  args.args = realloc(args.args, sizeof(char*) * (args.size + 1));
  args.args[args.size] = (char*)NULL;
  execvp(args.args[0], args.args);
  perror(args.args[0]);
}

// "Rename" fule descriptor "old" to "new," if necessary. After the
// execution of this function a program that "believes" that it uses
// the "old" descriptor (e.g., stdout #1 for output) will be actually
// using the "new" descriprot (e.g., an outgoinf pipe).  This
// functions terminates the process of error and should not be used in
// the parent, only in a child.
static void dup_me (int new, int old) {
  if (new != old && -1 == dup2(new, old)) {
    perror("dup2");
    exit(1);
  }
}

/*--------------------------------------------------------------------
 * End of "convenience" functions
 *--------------------------------------------------------------------*/

int sushi_spawn(prog_t *exe, int bgmode) {
  pid_t child0, child1, child2;
  const int N = cmd_length(exe);

  child1 = -1;
  child2 = -1;
  //master process
   
   pid_t children[(N-1)*2];
   //array of pipes and file descriptors
   int ppipe[2];
   pipe(ppipe);

   prog_t *first_exe= exe;
   prog_t *sec_exe= exe->prev;
   for (int i =0; i < N-1;i++){
	//pipe(pipes[i]);
  child1 = fork();
  if(child1 == 0){
    child2 = fork();
  }
  if(child1 == 0){
    printf("in child 1\n");
    children[i]= getpid();
    close(ppipe[0]);
    dup_me(ppipe[1], 1);
    start(first_exe); 
  }else if(child2){
    printf("in child 2\n");
    children[i]= getpid();
    close(ppipe[1]);
    dup_me(ppipe[0], 0);
    start(sec_exe); 
  }else{
    if(bgmode){
      wait_and_setenv(child1);
      wait_and_setenv(child2);
    }
    //close(ppipe[1]);
    //close(ppipe[2]);
    first_exe = first_exe->prev;
    sec_exe = sec_exe->prev;
    printf("in parent...");
  }
 
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

// DZ: You changed the prototype!
char *super_strdup(const char *ptr){
  void* result = strdup(ptr);
  if(NULL == result){
    abort();
  }
  return result;
}








