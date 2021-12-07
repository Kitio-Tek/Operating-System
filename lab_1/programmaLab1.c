#include <stdio.h>

int main(int argc,char *argv[]){
  FILE *fpS,*fpD;
  char c;

  fpS=fopen(argv[1],"r");
  fpD=fopen(argv[2],"w");

  while(fscanf(fpS,"%c",&c)!=EOF)
    fprintf(fpD,"%c",c);

  fclose(fpS);
  fclose(fpD);


}
