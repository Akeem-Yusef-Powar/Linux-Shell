#include <stdio.h>
#include <sys/types.h>

int main(){


int pid = fork();

if(pid == 0){
    printf("in the child, doing work\n");
    printf("process ID: %d\n",pid);
}
else {
wait();
printf("Back in parent");
}

return 0;




}
