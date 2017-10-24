#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdlib.h>

void* counting(void *argv){
    char *grep="grep --only-matching ";
    char *match=(char*)argv;
    char *file=" Novel.txt | wc -l";
    strcat(grep,match);
    strcat(grep,file);
    system(grep);
}


int main(int argc,char *argv[]){
    pthread_t tid[argc];
    int counter[argc],i;
    
}