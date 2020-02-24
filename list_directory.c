#include <stdio.h>
#include <dirent.h>

void dir()
{
    struct dirent *entry; // pointer for directory entry
    DIR *dirc = opendir("."); // dirc is a pointer of dir type
    while ((entry = readdir(dirc)) != NULL) // while directory has files
    {
        printf("%s\n", entry->d_name);
    }
    close(dirc);
}

int main(){

dir();

}
