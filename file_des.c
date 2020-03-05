#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>
#include <sys/wait.h>


int main(){

int fd[2]; // creates descriptors

if(pipe(fd)<0){ // 0 on success, -1 on error
    return -1;
}
// 0 = stdin, 1 = stdout
fd[0] = open("blank.txt",O_RDWR|O_CREAT); //open/create file and address descriptor

int child = fork();
if(child ==0){
    close(1); // close child out
    dup2(fd[0],1); // replace it with blank's stdin
close(fd[1]); // close stdout side blank
char *path = "/home/TU/tug31545/Sumtest";
    execl(path,"Sumtest",(char*)0);
	} else {
printf("waiting\n");
wait(NULL);
}

printf("Done\n");
}
