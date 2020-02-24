#include <stdio.h>
#include <string.h>

void help(){

FILE *open = fopen("shellManual.txt","r");

if(open==NULL){ // it never should

    printf("Couldn't find manual");
} else {
        char print = getc(open);
        while(print != EOF){
            printf("%c",print);
            print=getc(open);
        }

}


}


int main(){

help();

}
