#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdlib.h>
int hp_lohan=100;
int hp_kepiting=100;

void *starving_lohan(void *argv){
    while(1){
        sleep(10);
        hp_lohan-=15;
    }
}

void *starving_kepiting(void *argv){
    while(1){
        sleep(20);
        hp_kepiting-=10;
    }
}

void *add_hp_lohan(void *argv){
    hp_lohan+=10;
}

void *add_hp_kepiting(void *argv){
    hp_kepiting+=10;
}


int main(){
    pthread_t tid[4];
    pthread_create(&(tid[2]),NULL,starving_lohan,NULL);
    pthread_create(&(tid[3]),NULL,starving_kepiting,NULL);
    while(1){
        int n;scanf("%d",&n);
        if(n==1){
            pthread_create(&(tid[0]),NULL,add_hp_lohan,NULL);
        }
        else if(n==2){
            pthread_create(&(tid[1]),NULL,add_hp_kepiting,NULL);
        }
        printf("%d %d\n",hp_lohan,hp_kepiting);
        if(hp_lohan>100 || hp_lohan<=0 || hp_kepiting>100 || hp_kepiting<=10){
            printf("selesai ~~");
            break;
        }
    }
}