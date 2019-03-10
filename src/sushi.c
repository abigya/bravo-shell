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
    char *directory; // DZ: Declare variables where needed
    char *fname = "/sushi.conf";
    directory = super_malloc(strlen(getenv("HOME"))+ strlen(fname)+1);
    strcat(strcpy(directory,getenv("HOME")),fname);
    int p; 
    char *input;
    int x = sushi_read_config(directory);
    
    prevent_interruption();
    
  if (x==0){
    while(sushi_exit==0){
      fprintf(stdout,"%s",SUSHI_DEFAULT_PROMPT); // DZ: fputs?
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

