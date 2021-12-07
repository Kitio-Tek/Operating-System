#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void binary(int *,int )

int main(int argc, char *argv[]){
int n, *vet;

if(argc<2){
fprintf(stderr,"Run it as: program n\n");
exit(1);
}
 n=atoi(argv[1]);
 vet=(int *)malloc(n*sizeof(int));

if(vet==NULL){
printf("Allocation Error .\n");
exit(1);}

printf("Binary Numbers :\n");
binary(vet,n);
free(vet);

return 0;
}

void binary(int *vet,int n){
int i,j;
pid_t pid1,pid2;

for(i=0;i<=n;i++){
	if(i==n){
		for(j=0;j<n;j++)
		printf("%d", vet[j]);

      printf("\n");
      exit(0);
}
       else{

       pid1=fork();
       if(!pid1)
       { //CHILD 1
       vet[i]=0;}

       else{
       //Padre 1
       pid2=fork();

       if(!pid2){
       //CHILD 2
       	 vet[i]=1;
}
      else{
      wait((int *)0);
      wait((int *)0);
      exit(1);

}
       

}




}


}


exit(0);
}
