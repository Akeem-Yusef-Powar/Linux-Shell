#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/wait.h>
#include<fcntl.h>

//------------------------------------------------ Functions will not be added as a library as I need to make a project and I'm not sure what to do their

void cd(char *goingTo[])
{
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

void clr()
{
    printf("\033[H\033[J");
}

void dir()
{

    struct dirent *entry; // pointer to directory entry point
    DIR *dirc = opendir("."); // dirc is a pointer of dir type
    while ((entry = readdir(dirc)) != NULL) // while directory has files
    {
        printf("%s\n", entry->d_name);
    }



}

void envi(char * envp[])
{

    int i=0;
    while(envp[i] != NULL)
    {
        printf("%s\n", envp[i]);
        i=i+1;
    }

}

void echo (char x[])
{

    printf("%s \n",x);

}

void help()
{

    FILE *open = fopen("shellManual.txt","r");

    if(open==NULL)  // it never should
    {

        printf("Couldn't find manual in directory");
    }
    else
    {
        char print = getc(open);
        while(print != EOF)
        {
            printf("%c",print);
            print=getc(open);
        }

    }

}

void pausee()
{

    printf("in pause \n");
    char x;
    x = getchar();
    while(x != '\n')
    {
        x=getchar();
    }

}


//------------------------------------------------

int main(int argc, char *argv[], char * envp[])
{

    char path[50] ;
    char buffer[100]; // this is where the command line initially stores input
    char* evaluation[30]; // each index represents a argument from the command line to act on
    int fd[2]; // declare my file descriptors here so they can be used as needed

    char* builtIn[8]; // built in function for the shell to recognize
    builtIn[0] = "cd";
    builtIn[1] = "clr";
    builtIn[2] = "dir";
    builtIn[3] = "environ";
    builtIn[4] = "echo";
    builtIn[5] = "help";
    builtIn[6] = "pause";
    builtIn[7] = "quit";

    int in = 0; // this values will be 0 or 1
    int trunk = 0; // they will tell the child what operations it needs to do
    int app = 0; // e.g prog < infile in set in to 1 and the child will act according
    int pipee = 0;


    evaluation[0] = "0"; // my while loop doesn't run when strcmp (NULL,quit) this is a work around
    for(int fill=1; fill<30;)  // initialize evaluation array to clear junk
    {
        evaluation[fill]= NULL;
        fill=fill+1;
    }


    while(strcmp(evaluation[0],builtIn[7])!=0)
    {
// get command
        getcwd(path,50);// in case of cd call, get new working directory
        printf("%s/myShell> ",path);
        fgets(buffer,100,stdin); // get command
//------------------------------------------------------------------------------
//parse command into its individual components
        char* command = strtok(buffer," "); // break command down
        int j=0;
        int args = -1; //account initial program call
        while(command != NULL)  // while we still have commands
        {
            //printf("%s\n",command); // print so i can see it happen step by step for testing
            evaluation[j]= command;// fill evaluation arry with each token
            j=j+1;
            command = strtok(NULL," "); //breaks while loop so i can evaluate
        }
        evaluation[j-1] = strtok(evaluation[j-1],"\n");// gets rid of \n from last command

//------------------------------------------------------------------------------------------
//evaluate whats needs to be done and do it
        for(int i=0; i<30;)
        {

            if(strcmp(evaluation[0],builtIn[0])==0)
            {

                char *space[15] = {NULL};
                for(int j=i+1; j<30;) // this sections accounts for spaces that might be in the path name doesn't account for 2 spaces
                {
                    strcat(space,evaluation[j]);
                    if(evaluation[j+1] == NULL || evaluation[j+1] == '\0')
                    {
                        break;
                    }
                    strcat(space," ");
                    j=j+1;
                }
                cd(space);
            }
            else if(strcmp(evaluation[0],builtIn[1])==0)
            {
                clr();
            }
            else if(strcmp(evaluation[0],builtIn[2])==0)
            {
                dir();
            }
            else if(strcmp(evaluation[0],builtIn[3])==0)
            {
                envi(envp);
            }
            else if(strcmp(evaluation[0],builtIn[4])==0)
            {
                char echoo[15]="";
                for(int j=i+1; j<30;) // this sections accounts for spaces that might be in the path name doesn't account for 2 spaces
                {
                    strcat(echoo,evaluation[j]);
                    if(evaluation[j+1] == NULL || evaluation[j+1] == '\0')
                    {
                        break;
                    }
                    strcat(echoo," ");
                    j=j+1;
                }
                echo(echoo);
            }
            else if(strcmp(evaluation[0],builtIn[5])==0)
            {
                help();
            }
            else if(strcmp(evaluation[0],builtIn[6])==0)
            {
                pausee();
            }
            else if(strcmp(evaluation[0],builtIn[7])==0)
            {
                return 0;
            }

//-------------------------------------------------------------------------------------- end of built in functions
            else if(strcmp(evaluation[i],"<") == 0)
            {

                printf("%s will replace stdin with %s\n",evaluation[0],evaluation[i+1]);
                fd[0] = open(evaluation[i-1],O_RDONLY); // assume use has file they want
                in = 1; // indicates  fd[0] needs to be dup2'ed in child
                args = args - 1; // acoount for my arg counter count everything that isn't a token
            }
            else if(strcmp(evaluation[i],">")==0)
            {

                printf("%s will replace stdout and overwrite %s\n",evaluation[0],evaluation[i+1]);
                fd[1] = open(evaluation[i+1],O_WRONLY|O_CREAT|O_TRUNC);
                trunk = 1;
                args = args - 1;
            }
            else if(strcmp(evaluation[i],">>")==0)
            {

                printf("%s will append output to %s\n",evaluation[0],evaluation[i+1]);
                fd[1] = open(evaluation[i+1],O_WRONLY|O_CREAT|O_APPEND);
                app = 1;
                args = args - 1;
            }
            else if(strcmp(evaluation[i],"|")==0)
            {
                printf("%s will write to pipe and %s will read from the pipe\n",evaluation[0],evaluation[i+1]);
                if(pipe(fd)<0)  // 0 on success, -1 on error
                {

                    printf("error: could not create pipe\n");
                    break;
                } //parent needs to know about it & child will need a copy

                if(in > 0 || trunk >0 || app > 0)
                {

                    printf("error : too many assignments to file descriptors\n");
                    break;
                }
                pipee = i; // this helps me find the second program at exe time
                //args = args - 1;
            }
            else if(strcmp(evaluation[i],"&")==0)
            {
                printf("%s will run in the background\n",evaluation[0]);
                args = args - 1;
            }
            else
            {
                args = args +1;
            }

            if(evaluation[i+1]== NULL || strcmp(evaluation[i+1],"\0") == 0)
            {
                break;
            }

            i=i+1;
        }

        for(int see =0; see<10;)
        {

            printf("%d-%s\n",see,evaluation[see]);
            see = see +1;
        }

// break down down token index's marked args counted <,>,>>,| (& can be done in above statements)


        char* argsPassed [10]= {NULL}; // commands to be executed
        char* argsPassPipe[10]= {NULL}; // if a pipe command takes arguments from commandline too
        int argpipe = 0;

        if(args > 0)  // if arguments need to be passed
        {
            argsPassed[0]= evaluation[0];

            printf ("args = %d\n", args);

            for (int i=1; i <=args;)
            {
                if(strcmp(evaluation[i],"|")==0)
                {

                    args = args+1;// acount for |
                    i=i+1 ; // skip |

                    for(int j = i; j<=args;)
                    {
                        argsPassPipe[argpipe] = evaluation[j];
                        printf("argPassPipe %d - %s\n",argpipe,argsPassPipe[argpipe]);
                        j=j+1;
                        argpipe=argpipe+1;
                    }

                    break; // break i loop
                }

                argsPassed[i] = evaluation[i];
                printf("arg %d - %s\n",i,argsPassed[i]);
                i=i+1;

            }
        }

        else if(args == 0)  // program with no arguments
        {
            argsPassed[0]=evaluation[0];
        }

        printf("pipe status before %d\n",pipee);

        int child = fork(); // child created at this point

        if(child == 0)
        {

            if(in != 0)  // i want the child to asses all these statements
            {
                close(0); // close stdin
                dup2(fd[0],0); // copy in fd[0] which was opened
            }
            else if(trunk != 0)
            {
                printf("closing and duping for trunk\n");
                close(1); // close stdout
                dup2(fd[1],1);
            }
            else if(app != 0)
            {
                printf("appending a file\n");
                close (1);
                dup2(fd[1],1); // same behavior as above different task
            }
            else if(pipee != 0)
            {
                printf("piping\n");
                close(1); // close 1st child out
                dup2(fd[1],1); // this child writes to pipe
                close(fd[0]);// close read side of pipe

            }

// child knows what to do now and arguments are passed if needed

            execvp(argsPassed[0], argsPassed);
            printf("didn't execvp\n");

        }
        else
        {
// in parent


            if(pipee != 0)
            {
// create second child to do 2nd pipe command

                int child4pipe = fork();
                if(child4pipe <0)
                {
                    printf("error");
                }
                if(child4pipe==0)
                {
                    wait(NULL); // wait for 1st child to send input to pipe
                    close(0); // close 2ndchild in
                    dup2(fd[0],0); // 2ndchild in = 1st out at this point
                    close(fd[1]);// close write side of pipe
                    execvp(argsPassPipe[0],argsPassPipe);
                }
                else
                {
                    printf("parent waiting 4 pipe\n");
                    wait(NULL);
                    printf("child/children is/are done, parent is back at work");

                }


            }
            printf("parent waiting\n");
            wait(NULL);

        }
//------------------------------------------------------------------------ now clear everything for next loop

        for(int i=0; i<30;) // This loop clears my evaluation buffer
        {
            memset(&evaluation[i],'\0',1); // so privous commands do not interfere
            i=i+1;
        }
        in =0;
        trunk=0;
        app=0;
        pipee=0;
        printf("\n"); // just to make it clearer
    } // end shell

    return 0;
}
