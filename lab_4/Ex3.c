#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define M 100

void matfree(char **argm,int n);

int main(int argc ,char *argv[]){
  FILE *fp;
  char **arg;
  int i=0, N=4;
  char buffer[M];

  if(argc!=2){
    fprintf(stderr,"Wrong number of arguments\n");
    exit(-1);}

  if((fp=fopen(argv[1],"r"))==NULL){
    fprintf(stderr,"Error in reading file\n");
    exit(2);
}
  arg=calloc(N,sizeof(char*));

  while(fscanf(fp,"%s",buffer)!=EOF){
    if(strcmp(buffer,"end")==0){
      if(!fork()){ //CHILD
	execvp(arg[0],arg);
      }
      else{ sleep(3);
        	matfree(arg,i);

		i=0;
		N=4;
		arg=calloc(N,sizeof(char*));



      }

      

    }


    else{
      arg[i++]=strdup(buffer);
      if(i>=N){
        N=2*N;
	arg=realloc(arg,N*sizeof(char*));}

      


    }


  }
  
  matfree(arg,i);  
  fclose(fp);

  return 0;

}

void matfree(char **argm, int n){
  for(int i=0;i<n;i++)
    free(argm[i]);

  free(argm);

}
