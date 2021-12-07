#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#include <limits.h>
#include <errno.h>
#include <stdarg.h>

#define N 300
#define SPACE 2
#define BUFFSIZE 4096

void DirVisit(char *,char *,int);
void Print(int);
void FileCopy(char *,char *,mode_t);


int main(int argc, char *argv[]){

   if(argc!=3){
    fprintf(stderr,"Usage: pgrm<pathname>");
    exit(1);
    }
  
  
   DirVisit(argv[1],argv[2],1);

  return 0;

}
void DirVisit(char *Fullname,char *FullnameD, int level){
  DIR *dp;
  char Name[N],NameD[N];
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

  /*Create New Directory*/
  Print(level);
  fprintf(stdout,"Creating %s: level %d\n",FullnameD,level);
  mkdir(FullnameD,buf.st_mode);

  /*Visit Old Directory*/

  if((dp=opendir(Fullname))==NULL){
    fprintf(stderr,"Error.\n"); exit(1);
  }

  while((dirp=readdir(dp))!=NULL){
    sprintf(Name,"%s/%s",Fullname,dirp->d_name);
    sprintf(NameD,"%s/%s",FullnameD,dirp->d_name);

    if(lstat(Name,&buf)<0){
      fprintf(stderr,"Error.\n"); exit(1);
    }

    /*File*/
    if(S_ISDIR(buf.st_mode)==0){

      Print(level+1);
      fprintf(stdout,"Reading %s; level %d\n",Name,level+1);
      Print(level+1);
      fprintf(stdout,"Copying %s to %s; level %d\n",Name,NameD,level+1);

      FileCopy(Name,NameD,buf.st_mode);
    }

    else{
      /*Directory*/
      if(strcmp(dirp->d_name,".")==0 ||  strcmp(dirp->d_name,"..")==0)
	continue;

      DirVisit(Name,NameD,level+1);
    }

  }

  if(closedir(dp)<0)
    { fprintf(stderr,"Error.\n"); exit(1);}

  return;
}



void FileCopy(char *nameR,char *nameD,mode_t mode){
  int nR,nW,fdR,fdW;
  char buf[BUFFSIZE];

  fdR=open(nameR,O_RDONLY);
  fdW=open(nameD,mode|O_WRONLY|O_CREAT);

  if(fdR==(-1) || fdW==(-1)){
    fprintf(stdout,"File Open Error (R=%d)(W=%d).\n",fdR,fdW);
    exit(1);
  }

  while((nR=read(fdR,buf,BUFFSIZE))>0){
    nW=write(fdW,buf,nR);
    if(nR!=nW)
      fprintf(stderr,"Write Error (read %d, write %d).\n",nR,nW);

  }
  if(nW<0)
    fprintf(stderr,"Write Error.\n");

  close(fdR);
  close(fdW);

  return;



}






void Print(int n){
  int i;
  for(i=0;i<(n-1)*SPACE;i++)
    fprintf(stdout," ");

  return ;

}
