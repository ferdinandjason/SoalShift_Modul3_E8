#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdlib.h>

void* counting(void *argv){
    char greep[1000]="grep";
    strcat(greep," -o ");
    strcat(greep,(char *)argv);
    strcat(greep," Novel.txt");
    strcat(greep," | echo ");
    strcat(greep,(char *)argv);
    strcat(greep," : ");
    strcat(greep,"$(wc -l)");
    //printf("%s\n",greep);
    system(greep);
    //printf("\n");
}


int main(int argc,char *argv[]){
    pthread_t tid[argc];
    int counter[argc],i;
    for(int i=0;i<argc-1;i++){
        //printf("%s :",argv[i+1]);
        int err=pthread_create(&(tid[i]),NULL,counting,(void*)argv[i+1]);
    }
    for(int i=0;i<argc-1;i++){
        pthread_join(tid[i],NULL);
    }
}