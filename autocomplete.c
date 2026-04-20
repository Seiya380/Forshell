#include <termios.h>
#include <dirent.h>

struct termios original;

void fs_raw_mod(){
    tcgetattr(0,&original);
    struct termios raw = original;
    raw.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(0, TCSANOW, &raw);
}

void fs_restore(){
    tcsetattr(0, TCSANOW, &original);
}

void fs_autocomplete(char *buffer, int position){
    buffer[position] = '\0';
    printf("\r\033[K");
    printf("\r\033[K\033[A\033[K");
    char *matches[100];
    int count = 0;
    char cwd[1024];

    getcwd(cwd, sizeof(cwd));                                        
    printf("%s\nForshell> ", cwd); 
    fwrite(buffer, 1, position, stdout);                             
    fflush(stdout);
    printf("\n");

    DIR *dir = opendir(".");
    struct dirent *entry;                                     
    while ((entry = readdir(dir)) != NULL) {                  
        if (strncmp(entry->d_name, buffer, strlen(buffer)) == 0) {   
            matches[count] = entry->d_name;                       
            count++;                                                 
        }
    }                                                                
    closedir(dir);
    for (int i = 0; i < count; i++) {                                
        printf("  %s", matches[i]);  
    }
}