#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdlib.h>
typedef long long int ll;

void* counting(void *argv){
    ll a=strtol((char *)argv,NULL,10);
    ll num=1;
    for(ll i=2;i<=a;i++) num*=i;
    printf("Hasil %lld! = %lld\n",a,num);
    return NULL;
}

int main(int argc,char *argv[]){
    pthread_t tid[argc-1];
    for(int i=0;i<argc-1;i++){
        pthread_create(&(tid[i]),NULL,&counting,(void *)argv[i+1]);
    }
    for(int i=0;i<argc-1;i++){
        pthread_join(tid[i],NULL);
    }
}