#include <signal.h>
#include <string.h>
#include <unistd.h>
#include "sushi.h"

int sushi_exit;

static void refuse_to_die(int sig){
   signal(SIGINT,refuse_to_die);
   fprintf(stderr,"\nType exit to quit!\n");
}

static void prevent_interruption() {
 signal(SIGINT,refuse_to_die);
 
}

int main(int argc, char *argv[]) {
  // DZ: The name of the variable is SHELL
  // DZ: The order of parameters is wrong
    setenv(argv[0],"$SHELL",1);
    char *directory;
    char *fname = "/sushi.conf";
    directory = super_malloc(strlen(getenv("HOME"))+ strlen(fname)+1);
    strcat(strcpy(directory,getenv("HOME")),fname);
    int p;
    char *input;
    int x = sushi_read_config(directory,1);
    
    
    prevent_interruption();
    
  if (x==0){
     while(sushi_exit==0){
       // DZ: The name of the variable is PS1
     char* prompt_var = getenv("$PS1"); 
	if(prompt_var==NULL){
		fprintf(stdout,"%s",SUSHI_DEFAULT_PROMPT);
     
	}else{
		fprintf(stdout,"%s",prompt_var);	
	}
     input = sushi_read_line(stdin);
     if (input!=NULL){
      	p = sushi_parse_command(input);

      }
     
     if (p==0){
     	sushi_store(input);
     }
   
    }
  }

    return 0;
}

