#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
  int number,readStatus;

  while(1){
    readStatus=fscanf(stdin,"%d",&number);

    if(readStatus==EOF)
      return 0;
    else if(readStatus==0){
      printf("Numbers only\n");

      while(fgetc(stdin)!='\n'){}}

    else{
      if(number==0)
	return 0;
      switch(number%2)
	{  case 0:
	fprintf(stdout,"even number %d\n",number);
        break;
           case 1:
	fprintf(stderr,"Odd number %d\n",number);
	break;}
	




    }




  }






}
