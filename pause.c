#include <stdio.h>
#include <string.h>

void echo (char x[]){

printf("%s\n",x);

}

void pause(){
    printf("in pause \n");
char x;
x = getchar();
    while(x != '\n'){
    x=getchar();
    }
}

int main(){

char* evaluation[30]; // where input is evaluated

for(int fill=0; fill<30;){
evaluation[fill]= NULL;
fill=fill+1;
}

//while(strcmp(evaluation[0],"quit")!=0){

    printf("myShell> ");


//-----------------------------------------------------------------------
char buffer[30];

fgets(buffer,30,stdin); // get command
char* command = strtok(buffer," "); // break command down
int j=0;
while(command != NULL){ // while we still have commands
 printf("%s\n",command); // print so i can see it happen step by step for testing
 evaluation[j]= command;// fill evaluation arry with each token
 j=j+1;
    command = strtok(NULL," ");
}
//-------------------------------------------------------

    for(int i=0;i<30;){
        if(strcmp(evaluation[i],"pause")==0){
            pause();
        }
        else if(strcmp(evaluation[i],"echo")==0){
            printf("%s\n", evaluation[i+1]); // need to find out how to print a string and not just a word
        }
          if(evaluation[i+1]== NULL){
        break;
        }
        i=i+1;
    }

//}
//----------------------------------------------------------------------------
return 0;
}
