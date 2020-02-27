#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h> 

int main(){

char *path = "/home/TU/tug31545/Sumtest";


int pid = fork();

if(pid == 0){
    printf("in the child, doing work\n");
    printf("process ID: %d\n",pid);
	execl(path,"Sumtest",(char*)0);
	printf("This shouldn't print");
}
else {
printf("do this before wait\n");
wait(NULL);
printf("Back in parent\n");
printf("%d\n", getpid());
}

return 0;




}
