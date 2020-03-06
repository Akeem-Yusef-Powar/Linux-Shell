#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>

//------------------------------------------------ Functions will not be added as a library as I need to make a project and I'm not sure what to do their

void cd(char *goingTo[]){
    char dir[100];
//char *path;


//strcat(path,goingTo);

//printf("in cd %s",path);
chdir(goingTo);
/*
printf("%s\n",getcwd(dir,100)); // confirm location
    struct dirent *entry; // pointer to directory entry point
    DIR *dirc = opendir("."); // dirc is a pointer of dir type
    while ((entry = readdir(dirc)) != NULL) // while directory has files
    {
        printf("%s\n", entry->d_name);
    }
*/ // used for testing prints name of current directory and content
}

void clr(){
printf("\033[H\033[J");
}

void dir(){

    struct dirent *entry; // pointer to directory entry point
    DIR *dirc = opendir("."); // dirc is a pointer of dir type
    while ((entry = readdir(dirc)) != NULL) // while directory has files
    {
        printf("%s\n", entry->d_name);
    }



}

void envi(char * envp[]){

int i=0;
     while(envp[i] != NULL){
        printf("%s\n", envp[i]);
        i=i+1;
    }

}

void echo (char x[]){

    printf("%s \n",x);

}

void help(){

FILE *open = fopen("shellManual.txt","r");

if(open==NULL){ // it never should

    printf("Couldn't find manual in directory");
} else {
        char print = getc(open);
        while(print != EOF){
            printf("%c",print);
            print=getc(open);
        }

}

}

void pausee(){

    printf("in pause \n");
char x;
x = getchar();
    while(x != '\n'){
    x=getchar();
    }

}


//------------------------------------------------

int main(int argc, char *argv[], char * envp[]){

char path[50] ;
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
getcwd(path,50);// in case of cd call, get new working directory
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
printf("%d-%s\n",i,evaluation[i]); // so i can see what args are in what index

    if(strcmp(evaluation[i],builtIn[0])==0){

            char *space[15] = {NULL};
           for(int j=i+1;j<30;){ // this sections accounts for spaces that might be in the path name doesn't account for 2 spaces
                strcat(space,evaluation[j]);
                if(evaluation[j+1] == NULL || evaluation[j+1] == '\0'){
                    break;
                }
                strcat(space," ");
                j=j+1;
            }
printf("passing %s\n",space); // problem here
        cd(space);
    }
    else if(strcmp(evaluation[i],builtIn[1])==0){
        clr();
    }
    else if(strcmp(evaluation[i],builtIn[2])==0){
        dir();
    }
    else if(strcmp(evaluation[i],builtIn[3])==0){
            envi(envp);
    }
    else if(strcmp(evaluation[i],builtIn[4])==0){
                        char echoo[15]="";
           for(int j=i+1;j<30;){ // this sections accounts for spaces that might be in the path name doesn't account for 2 spaces
                strcat(echoo,evaluation[j]);
                if(evaluation[j+1] == NULL || evaluation[j+1] == '\0'){
                    break;
                }
                strcat(echoo," ");
                j=j+1;
            }
        echo(echoo);
    }
    else if(strcmp(evaluation[i],builtIn[5])==0){
        help();
    }
    else if(strcmp(evaluation[i],builtIn[6])==0){
        pausee();
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
} // the below statment I suspect was clearing quit before my shell loop could assessl it
for(int i=0;i<30;){ // This loop clears my evaluation buffer
memset(&evaluation[i],'\0',1); // so privous commands do not interfere
i=i+1;
}
printf("\n"); // just to make it clearer
} // end shell

return 0;
}

