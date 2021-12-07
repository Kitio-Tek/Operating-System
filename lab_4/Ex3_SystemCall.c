#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define N 400
#define M 400

int main(int argc, char *argv[]){
  FILE *fp;
  char cmd[M];
    char buffer[N];
    int i=0;

    if(argc!=2){
      fprintf(stderr,"Error in the number of parameter\n");
      exit(0);
    }

    if((fp=fopen(argv[1],"r"))==NULL)
      {fprintf(stderr,"Error in file reading\n");
	exit(-1);}

    while(fscanf(fp,"%s",buffer)!=EOF){
      if(strcmp(buffer,"end")==0){
        system(cmd);
	cmd[0]='\0';
      }
      else{
	
	strcat(cmd,buffer);
	strcat(cmd," ");

      }


    }

    fclose(fp);
    return 0;


}
