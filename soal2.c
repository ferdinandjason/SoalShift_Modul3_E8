#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

int lubang[2][16]={{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};
int status=0;
struct input{
    int a=-1,b=-1,c=-1,d=-1,orang;
}
int skor[2]={0,0};

struct input hehe[2];

void* isi(void *arg){
    status=1;
    struct input skrng=(struct input)arg;
    if(skrng.a>=0) lubang[skrng.orang][skrng.a]++;
    if(skrng.b>=0) lubang[skrng.orang][skrng.b]++;
    if(skrng.c>=0) lubang[skrng.orang][skrng.c]++;
    if(skrng.d>=0) lubang[skrng.orang][skrng.d]++;
    status=0;
}

void* tebak(void *arg){
    while(status!=0){
        //do nothing
    }
    struct input skrng=(struct input)arg;
    if(lubang[skrng.orang^1][skrng.a]) skor[skrng.orang]++;
    else skor[skrng.orang^1]++;
    if(lubang[skrng.orang^1][skrng.b]) skor[skrng.orang]++;
    else skor[skrng.orang^1]++;
    if(lubang[skrng.orang^1][skrng.c]) skor[skrng.orang]++;
    else skor[skrng.orang^1]++;
    if(lubang[skrng.orang^1][skrng.d]) skor[skrng.orang]++;
    else skor[skrng.orang^1]++;
}