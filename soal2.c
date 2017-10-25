#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

int lubang[2][16]={{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};
int status=0;
struct input{
    int a;
    int b;
    int c;
    int d;
    int orang;
};
int skor[2]={0,0};

struct input hehe[2];

void* isi(void *arg){
    status=1;
    struct input skrng=*((struct input*)arg);
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
    struct input skrng=*((struct input *)arg);
    if(lubang[skrng.orang^1][skrng.a]) skor[skrng.orang]++;
    else skor[skrng.orang^1]++;
    if(lubang[skrng.orang^1][skrng.b]) skor[skrng.orang]++;
    else skor[skrng.orang^1]++;
    if(lubang[skrng.orang^1][skrng.c]) skor[skrng.orang]++;
    else skor[skrng.orang^1]++;
    if(lubang[skrng.orang^1][skrng.d]) skor[skrng.orang]++;
    else skor[skrng.orang^1]++;
}

void cek_lubang(int role){
    int i;
    for(i=0;i<16;i++){
        printf("%d ",lubang[role][i]);
    }
}

int lubangfull(int role){
    int i,penuh;
    for(i=0;i<16;i++){
        if(lubang[role][i]==0) return 0;
    }
    return 1;
}

int main(){
    pthread_t tid[2];
    int role=0;
    while(1){
        system("clear");
        if( (skor[0]>=10 || skor[1]>=10) || (skor[0]<10 && skor[1]<=10 && lubangfull(0) && lubangfull(1) ) ){
            printf("FINISH\n");
            break;
        }
        printf("1. Play!\n");
        printf("2. Cek!\n");
        printf("3. Cek Lubang!\n");
        printf("Pilihan : ");
        int p;scanf("%d",&p);
        if(p==1){
            printf("Now turn %d player to place bomb!\n",role+1);
            printf("1st hole : ");scanf("%d",&hehe[role].a);
            printf("2nd hole : ");scanf("%d",&hehe[role].b);
            printf("3th hole : ");scanf("%d",&hehe[role].c);
            printf("4th hole : ");scanf("%d",&hehe[role].d);
            hehe[role].orang=role;
            system("clear");
            printf("Now turn %d player! to quess bomb!\n",(role^1)+1);
            printf("1st hole : ");scanf("%d",&hehe[role^1].a);
            printf("2nd hole : ");scanf("%d",&hehe[role^1].b);
            printf("3th hole : ");scanf("%d",&hehe[role^1].c);
            printf("4th hole : ");scanf("%d",&hehe[role^1].d);
            hehe[role^1].orang=role^1;
            system("clear");
    
            pthread_create(&(tid[role]),NULL,&isi,&hehe[role]);
            pthread_create(&(tid[role^1]),NULL,&tebak,&hehe[role^1]);
            pthread_join(tid[role],NULL);
            pthread_join(tid[role^1],NULL);
            role^=1;
        }
        else if(p==2){
            printf("Skor %d = %d\n",role+1,skor[role]);
            printf("Skor %d = %d\n",(role^1)+1,skor[role^1]);
        }
        else if(p==3){
            printf("Pemain Berapa ? ");
            int x;scanf("%d",&x);
            cek_lubang(x-1);
        }
    }
}