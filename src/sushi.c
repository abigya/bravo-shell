#include <signal.h>
#include <string.h>
#include <unistd.h>
#include "sushi.h"

int sushi_exit;

static void refuse_to_die(int sig){
   signal(SIGINT,refuse_to_die);
   fprintf(stderr,"Type exit to quit!\n");
}

static void prevent_interruption() {
 signal(SIGINT,refuse_to_die);
 /**struct sigaction sa;
 sa.sa_handler = refuse_to_die;
 sigemptyset(&(sa.sa_mask));
 sigaddset(&(sa.sa_mask),SIGINT);
 sigaction(SIGINT,&sa,NULL);**/
 
}

int main(int argc, char *argv[]) {
    char *directory;
    char *fname = "/sushi.conf";
    directory = malloc(strlen(getenv("HOME"))+ strlen(fname)+1);
    strcat(strcpy(directory,getenv("HOME")),fname);
    FILE *f = stdin; //stdin is passed as file for read_line
    int p;
    char *input;
    sushi_read_config(directory);
    
    prevent_interruption();
    
    while(sushi_exit==0 ){
     fprintf(stdout,"%s",SUSHI_DEFAULT_PROMPT);
     input = sushi_read_line(f);
     if (input!=NULL){
      	p = sushi_parse_command(input);
      }
     
     if (p==0){
     	sushi_store(input);
     }
   
    }

    return 0;
}

