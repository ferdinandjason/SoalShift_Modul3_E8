#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

int lubang[2][17]={{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};
int status=0;
struct input{
    int a;
    int b;
    int c;
    int d;
    int orang;
};
int skor[2]={0,0};

int nol,satu;

struct input hehe[2];

void* isi(void *arg){
    status=1;
    struct input skrng=*((struct input*)arg);
    if(skrng.a>=0) lubang[skrng.orang][skrng.a]=1;
    if(skrng.b>=0) lubang[skrng.orang][skrng.b]=1;
    if(skrng.c>=0) lubang[skrng.orang][skrng.c]=1;
    if(skrng.d>=0) lubang[skrng.orang][skrng.d]=1;
    status=0;
}

void* tebak(void *arg){
    while(status!=0){
        //do nothing
    }
    struct input skrng=*((struct input *)arg);
    if(lubang[skrng.orang^1][skrng.a]) skor[skrng.orang^1]++;
    else skor[skrng.orang]++;
    if(lubang[skrng.orang^1][skrng.b]) skor[skrng.orang^1]++;
    else skor[skrng.orang]++;
    if(lubang[skrng.orang^1][skrng.c]) skor[skrng.orang^1]++;
    else skor[skrng.orang]++;
    if(lubang[skrng.orang^1][skrng.d]) skor[skrng.orang^1]++;
    else skor[skrng.orang]++;
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
        penuh+=lubang[role][i];
    }
    return penuh;
}

int main(){
    pthread_t tid[2];
    int role=0;
    char nama[2][100];
    printf("Masukkan nama player 1 : ");scanf("%s",nama[0]);
    printf("Masukkan nama player 2 : ");scanf("%s",nama[1]);
    while(1){
        //system("clear");
        if( (skor[0]>=10 || skor[1]>=10) || (skor[0]<10 && skor[1]<=10 && lubangfull(0)==16 && lubangfull(1)==16 ) ){
            printf("FINISH\n");
            if(skor[0]>skor[1]) printf("%s WIN\n",nama[0]);
            else if(skor[0]<skor[1]) printf("%s WIN\n",nama[1]);
            else printf("DRAW\n");
            break;
        }
        printf("1. Play!\n");
        printf("2. Cek!\n");
        printf("3. Cek Lubang!\n");
        printf("Pilihan : ");
        int p;scanf("%d",&p);
        if(p==1){
            int a,b,c,d;
            printf("Now turn %s player to place bomb!\n",nama[role]);
            int k;scanf("%d",&k);
            while(k < 16-lubangfull(role)){printf("ERROR!!\n");scanf("%d",&k);}
            if(k==4){
                printf("1st hole : ");scanf("%d",&a);
                while(a<=0 || a>16 || lubang[role][a]==1){
                    printf("ERROR!!\n");
                    printf("1st hole : ");scanf("%d",&a);
                }
                hehe[role].a=a;
                printf("2nd hole : ");scanf("%d",&b);
                while(b<=0 || b>16 || lubang[role][b]==1 || b==a){
                    printf("ERROR!!\n");
                    printf("2nd hole : ");scanf("%d",&b);
                }
                hehe[role].b=b;
                printf("3rd hole : ");scanf("%d",&c);
                while(c<=0 || c>16 || lubang[role][c]==1 || c==a || c==b){
                    printf("ERROR!!\n");
                    printf("3rd hole : ");scanf("%d",&c);
                }
                hehe[role].c=c;
                printf("4th hole : ");scanf("%d",&d);
                while(d<=0 || d>16 || lubang[role][d]==1 || d==a || d==b || d==c){
                    printf("ERROR!!\n");
                    printf("4th hole : ");scanf("%d",&d);
                }
                hehe[role].d=d;
            }
            if(k==3){
                printf("1st hole : ");scanf("%d",&a);
                while(a<=0 || a>16 || lubang[role][a]==1){
                    printf("ERROR!!\n");
                    printf("1st hole : ");scanf("%d",&a);
                }
                hehe[role].a=a;
                printf("2nd hole : ");scanf("%d",&b);
                while(b<=0 || b>16 || lubang[role][b]==1 || b==a){
                    printf("ERROR!!\n");
                    printf("2nd hole : ");scanf("%d",&b);
                }
                hehe[role].b=b;
                printf("3rd hole : ");scanf("%d",&c);
                while(c<=0 || c>16 || lubang[role][c]==1 || c==a || c==b){
                    printf("ERROR!!\n");
                    printf("3rd hole : ");scanf("%d",&c);
                }
                hehe[role].c=c;
            }
            if(k==2){
                printf("1st hole : ");scanf("%d",&a);
                while(a<=0 || a>16 || lubang[role][a]==1){
                    printf("ERROR!!\n");
                    printf("1st hole : ");scanf("%d",&a);
                }
                hehe[role].a=a;
                printf("2nd hole : ");scanf("%d",&b);
                while(b<=0 || b>16 || lubang[role][b]==1 || b==a){
                    printf("ERROR!!\n");
                    printf("2nd hole : ");scanf("%d",&b);
                }
                hehe[role].b=b;
            }
            if(k==1){
                printf("1st hole : ");scanf("%d",&a);
                while(a<=0 || a>16 || lubang[role][a]==1){
                    printf("ERROR!!\n");
                    printf("1st hole : ");scanf("%d",&a);
                }
                hehe[role].a=a;
            }
            hehe[role].orang=role;

            system("clear");
            printf("Now turn %s player! to quess bomb!\n",nama[(role^1)]);
            printf("1st hole : ");scanf("%d",&a);
            while(a<=0 || a>16){
                printf("ERROR!!\n");
                printf("1st hole : ");scanf("%d",&a);
            }
            hehe[role^1].a=a;
            printf("2nd hole : ");scanf("%d",&b);
            while(b<=0 || b>16|| b==a){
                printf("ERROR!!\n");
                printf("2nd hole : ");scanf("%d",&b);
            }
            hehe[role^1].b=b;
            printf("3rd hole : ");scanf("%d",&c);
            while(c<=0 || c>16 || c==a || c==b){
                printf("ERROR!!\n");
                printf("3rd hole : ");scanf("%d",&c);
            }
            hehe[role^1].c=c;
            printf("4th hole : ");scanf("%d",&d);
            while(d<=0 || d>16 || d==a || d==b || d==c){
                printf("ERROR!!\n");
                printf("4th hole : ");scanf("%d",&d);
            }
            hehe[role^1].d=d;
            hehe[role^1].orang=role^1;
            system("clear");
    
            pthread_create(&(tid[role]),NULL,&isi,&hehe[role]);
            pthread_create(&(tid[role^1]),NULL,&tebak,&hehe[role^1]);
            pthread_join(tid[role],NULL);
            pthread_join(tid[role^1],NULL);
            role^=1;
        }
        else if(p==2){
            printf("Skor %s = %d\n",nama[role],skor[role]);
            printf("Skor %s = %d\n",nama[(role^1)],skor[role^1]);
        }
        else if(p==3){
            printf("Pemain Berapa ? ");
            int x;scanf("%d",&x);
            cek_lubang(x-1);
        }
    }
}
