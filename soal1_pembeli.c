#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

char *s[]={"MP4A1","PM2-V1","SPR-3","SS2-V5","SPG1-V3","MINE"};
int point=12345;
int hehe;

void* pembeli(void *arg){
    int pilihan=(int)arg;
    key_t pointer = point;
    int *stok;
    int shmid = shmget(pointer,6*sizeof(int),IPC_CREAT | 0666);
    stok = shmat(shmid,NULL,0);
    for(int i=0;i<6;i++){
        printf("Jumlah %s di stock = %d barang\n",s[i],*(stok+i));
    }
    getchar();
}

void* pembeli2(void *arg){
    key_t pointer = point;
    int *stok,i=0;
    int shmid = shmget(pointer,6*sizeof(int),IPC_CREAT | 0666);
    stok = shmat(shmid,NULL,0);
    char *input=(char*)arg;
    for(i=0;i<6;i++){
        //printf("%s %s : %d\n",input,s[i],strcmp(input,s[i]));
        if(strcmp(input,s[i])==0 && *(stok+i)>=hehe){
            *(stok+i)-=hehe;
        }
        else if(strcmp(input,s[i])==0 ){
            printf("“barang di stock tidak cukup\n");        
        }
    }
}

int main(){
    pthread_t tid;
    while(1){
        //system("clear");
        printf("1. Lihat Stock Senjata\n");
        printf("2. Beli Senjata\n");
        printf("Pilih : ");
        int pilihan;scanf("%d",&pilihan);
        if(pilihan==1) pthread_create(&(tid),NULL,&pembeli,(void*)pilihan);
        else if(pilihan==2){
            char input2[50];
            scanf("%s %d",input2,&hehe);
            pthread_create(&(tid),NULL,&pembeli2,(void*)input2);
        }
        pthread_join(tid,NULL);
        getchar();
    }
}
