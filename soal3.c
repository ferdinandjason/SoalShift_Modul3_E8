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
        sleep(1);
        hp_lohan-=15;
    }
}

void *starving_kepiting(void *argv){
    while(1){
        sleep(2);
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
    
}