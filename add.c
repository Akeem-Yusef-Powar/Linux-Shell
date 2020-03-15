#include <stdio.h>
#include<stdlib.h>

int add(int x,int y){

int z = x+y;
printf("%d\n",z);

}

int main(int argc, char *argv[]){

if (argc < 3) {
printf("Need 2 numbers\n");
        

}
char *a = argv[1];
int first = atoi(a);
char *b = argv[2];
int second = atoi(b);
add(first,second);
}
