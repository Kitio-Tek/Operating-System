#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>

#include <limits.h>
#include <errno.h>
#include <stdarg.h>

#define N 300
void DirVisit(char *,int);
void Print(int);

int main(int argc, char *argv[]){

   if(argc!=2){
    fprintf(stderr,"Usage: pgrm<pathname>");
    exit(1);
    }
  
  
  DirVisit(argv[1],1);

  return 0;

}
void DirVisit(char *Fullname, int level){
  DIR *dp;
  char Name[N];
  struct dirent *dirp;
  struct stat buf;
  
  Print(level);
  fprintf(stdout,"Entering %s:level %d\n",Fullname,level);

  if(lstat(Fullname,&buf)<0){
    fprintf(stderr,"Error.\n"); exit(1);
  }
  if(S_ISDIR(buf.st_mode)==0){
    fprintf(stderr,"Error.\n"); exit(1);
  }

  if((dp=opendir(Fullname))==NULL){
    fprintf(stderr,"Error.\n"); exit(1);
  }

  while((dirp=readdir(dp))!=NULL){
    sprintf(Name,"%s/%s",Fullname,dirp->d_name);

    if(lstat(Name,&buf)<0){
      fprintf(stderr,"Error.\n"); exit(1);
    }
    if(S_ISDIR(buf.st_mode)==0){

      Print(level+1);
      fprintf(stdout,"Reading %s; level %d\n",dirp->d_name,level+1);
    }

    else{
      if(strcmp(dirp->d_name,".")!=0 &&  strcmp(dirp->d_name,"..")!=0)
	 DirVisit(Name,level+1);
    }

  }

  if(closedir(dp)<0)
    { fprintf(stderr,"Error.\n"); exit(1);}

  return;
}

void Print(int n){
  int i;
  for(i=0;i<(n-1)*2;i++)
    fprintf(stdout," ");

  return ;

}
