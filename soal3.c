#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdlib.h>
int hp_lohan=100;
int hp_kepiting=100;
int status_l=1;
int status_k=1;

void *starving_lohan(void *argv){
    while(status_l==1 && status_k==1){
        sleep(2);
        hp_lohan-=15;
        if(hp_lohan<=0 || status_k==0){puts("h");status_l=0;exit(0);}
        printf("hp lohan berkurang menjadi = %d\n",hp_lohan);
    }
}

void *starving_kepiting(void *argv){
    while(status_l==1 && status_k==1){
        sleep(5);
        hp_kepiting-=10;
        if(hp_kepiting<=0 || status_l==0){puts("h");status_k=0;exit(0);}
        printf("hp kepiting berkurang menjadi= %d\n",hp_kepiting);
    }
}

void *add_hp_lohan(void *argv){
    hp_lohan+=10;
    if(hp_lohan>100) status_l=0;
    else printf("hp lohan bertambah menjadi= %d\n",hp_lohan);
}

void *add_hp_kepiting(void *argv){
    hp_kepiting+=10;
    if(hp_kepiting>100) status_k=0;
    else printf("hp kepiting bertambah menjadi= %d\n",hp_kepiting);
}


int main(){
    pthread_t tid[4];
    pthread_create(&(tid[2]),NULL,starving_lohan,NULL);
    pthread_create(&(tid[3]),NULL,starving_kepiting,NULL);

    while(status_l==1 && status_k==1){
        int n;scanf("%d",&n);
        if(n==1){
            pthread_create(&(tid[0]),NULL,add_hp_lohan,NULL);
        }
        else if(n==2){
            pthread_create(&(tid[1]),NULL,add_hp_kepiting,NULL);
        }
        if(hp_lohan>100 || hp_kepiting>100) break;
        printf("%d %d\n",hp_lohan,hp_kepiting);
    }
    printf("selesai\n");
    return 0;
}
