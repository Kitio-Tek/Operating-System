#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

void Pright(void);
void Pleft(void);

 int main(){
   pid_t pid;
   fprintf(stdout,"P1 (pid=%d)\n",getpid());
   pid=fork();

   if(pid==0){
     Pright();
     exit(0);
   }
   else{
     Pleft();
     wait(NULL);
     fprintf(stdout,"P9 (pid=%d)\n",getpid());

   }

   return 0;

 }

void Pleft(){
  pid_t pid;
  fprintf(stdout,"P2 (pid=%d)\n",getpid());
  pid=fork();

  if(pid==0){
    fprintf(stdout,"P5 (pid=%d)\n",getpid());
    exit(0);
  } else{
    fprintf(stdout,"P4 (pid=%d)\n",getpid());
    waitpid(pid,NULL,0);

    fprintf(stdout,"P7 (pid=%d)\n",getpid());
    return;
  }


}
void Pright(){
  pid_t pid;
  fprintf(stdout,"P3 (pid=%d)\n",getpid());
  pid=fork();

  if(pid==0){
    fprintf(stdout,"P6 (pid=%d)\n",getpid());
    exit(0);
  }

  else{
    waitpid(pid,NULL,0);

    fprintf(stdout,"P8 (pid=%d)\n",getpid());
    return;

  }

}
