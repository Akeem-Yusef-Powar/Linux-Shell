#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
char path[50] ;
 getcwd(path,50);// gets current directory
char buffer[100];
char* evaluation[30];

char* builtIn[8];
builtIn[0] = "cd";
builtIn[1] = "clr";
builtIn[2] = "dir";
builtIn[3] = "environ";
builtIn[4] = "echo";
builtIn[5] = "help";
builtIn[6] = "pause";
builtIn[7] = "quit";


evaluation[0] = "0"; // my while loop doesn't run when strcmp (NULL,quit) this is a work around
for(int fill=1; fill<30;){
evaluation[fill]= NULL;
fill=fill+1;
}


while(strcmp(evaluation[0],builtIn[7])!=0){
// get command
printf("%s/myShell> ",path);
fgets(buffer,100,stdin); // get command
//------------------------------------------------------------------------------
//parse command into its individual components
char* command = strtok(buffer," "); // break command down
int j=0;

while(command != NULL){ // while we still have commands
    //printf("%s\n",command); // print so i can see it happen step by step for testing
    evaluation[j]= command;// fill evaluation arry with each token
    j=j+1;
    command = strtok(NULL," "); //breaks while loop so i can evaluate
}
evaluation[j-1] = strtok(evaluation[j-1],"\n");// gets rid of \n from last command

//------------------------------------------------------------------------------------------
//evaluate whats needs to be done and do it
for(int i=0; i<30;){
printf("%d-%s\n",i,evaluation[i]); // so i can see what commands are in what index

    if(strcmp(evaluation[i],builtIn[0])==0){
        printf("changing directory\n");
    }
    else if(strcmp(evaluation[i],builtIn[1])==0){
        printf("clearing screen\n");
    }
    else if(strcmp(evaluation[i],builtIn[2])==0){
        printf("Listing directory\n");
    }
    else if(strcmp(evaluation[i],builtIn[3])==0){
        printf("getting environment variables\n");
    }
    else if(strcmp(evaluation[i],builtIn[4])==0){
        printf("echoing\n");
    }
    else if(strcmp(evaluation[i],builtIn[5])==0){
        printf("getting help manual\n");
    }
    else if(strcmp(evaluation[i],builtIn[6])==0){
        printf("paused\n");
    }
    else if(strcmp(evaluation[i],"<") == 0){
        printf("%s will replace stdin with %s\n",evaluation[0],evaluation[i+1]);
    }
    else if(strcmp(evaluation[i],">")==0){
        printf("%s will replace stdout and overwrite %s\n",evaluation[0],evaluation[i+1]);
    }
    else if(strcmp(evaluation[i],">>")==0){
        printf("%s will append output to %s\n",evaluation[0],evaluation[i+1]);
    }
    else if(strcmp(evaluation[i],"|")==0){
        printf("%s will write to pipe and %s will read from the pipe\n",evaluation[0],evaluation[i+1]);
    }
    else if(strcmp(evaluation[i],"&")==0){
        printf("%s will run in the background\n",evaluation[0]);
    }
    if(evaluation[i+1]== NULL){
        break;
    }
        i=i+1;
    }
if(strcmp(evaluation[0],builtIn[7])==0){
break;
} // the below statment I suspect was clearing quit before my shell loop could assess it
 
for(int i=0;i<30;){ // This loop clears my evaluation buffer
memset(&evaluation[i],'\0',1); // so privous commands do not interfere
i=i+1;
}
printf("\n"); 
} // end shell

return 0;
}

