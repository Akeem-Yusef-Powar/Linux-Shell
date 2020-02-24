#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(){
char path[50] ;
 getcwd(path,50);// gets current directory
char buffer[30];
char* evaluation[30];

for(int fill=0; fill<30;){
evaluation[fill]= NULL;
fill=fill+1;
}

printf("%s/myShell> \n",path);
fgets(buffer,30,stdin); // get command

char* command = strtok(buffer," "); // break command down
int j=0;
while(command != NULL){ // while we still have commands
 //printf("%s\n",command); // print so i can see it happen step by step for testing
 evaluation[j]= command;// fill evaluation arry with each token
 j=j+1;
    command = strtok(NULL," ");
}

for(int i=0; i<30;){
//printf("%d-%s\n",i,evaluation[i]); // so i can see what index is causing parsing problems

     if(strcmp(evaluation[i],"<") == 0){

        printf("%s will redirect input from %s\n",evaluation[i-1],evaluation[i+1]);

    }

    else if(strcmp(evaluation[i],">")==0){
       printf("%s will redirect output and overwrite %s\n",evaluation[i-1],evaluation[i+1]);

    }
      else if(strcmp(evaluation[i],">>")==0){
       printf("%s will append output to %s\n",evaluation[i-1],evaluation[i+1]);

    }
    else if(strcmp(evaluation[i],"|")==0){
        printf("%s will write to pipe and %s will read from the pipe\n",evaluation[i-1],evaluation[i+1]);

    }
    else if(strcmp(evaluation[i],"&")==0 ||strcmp(evaluation[i],"&\n")==0){
        printf("%s will run in the background\n",evaluation[i-1]);

    }
    if(evaluation[i+1]== NULL){
        break;
        }
        i=i+1;
    }


return 0;
}

