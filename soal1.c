#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include<pthread.h>

template <class T>

char *s[]={"MP4A1","PM2-V1","SPR-3","SS2-V5","SPG1-V3","MINE"};
int point=12345;
int hehe;

void* penjual(void *arg){
    int pilihan = (int)arg;
    key_t pointer = point;
    int *stok,i=0;
    int shmid = shmget(pointer,6*sizeof(int),IPC_CREAT | 0666);
    stok = shmat(shmid,NULL,0);
    //printf("%d\n",pilihan);
    for(i=0;i<6;i++){
        if(*(stok+i)>0){
            printf("Jumlah %s di stock = %d barang\n",s[i],*(stok+i));
        }
    }
}

void* penjual2(void *arg){
    key_t pointer = point;
    int *stok,i=0;
    int shmid = shmget(pointer,6*sizeof(int),IPC_CREAT | 0666);
    stok = shmat(shmid,NULL,0);
    char *input=(char*)arg;
    for(i=0;i<6;i++){
        //printf("%s %s : %d\n",input,s[i],strcmp(input,s[i]));
        if(strcmp(input,s[i])==0){
            *(stok+i)+=hehe;
        }
    }
}

void* pembeli(void *arg){
    int pilihan=(int)arg;
    key_t pointer = point;
    int *stok;
    int shmid = shmget(pointer,6*sizeof(int),IPC_CREAT | 0666);
    stok = shmat(shmid,NULL,0);
    for(int i=0;i<6;i++){
        if(*(stok+i)>0){
            printf("Jumlah %s di stock = %d barang\n",s[i],*(stok+i));
        }
    }
}

void* pembeli2(void *arg){
    key_t pointer = point;
    int *stok,i=0;
    int shmid = shmget(pointer,6*sizeof(int),IPC_CREAT | 0666);
    stok = shmat(shmid,NULL,0);
    char *input=(char*)arg;
    for(i=0;i<6;i++){
        //printf("%s %s : %d\n",input,s[i],strcmp(input,s[i]));
        if(strcmp(input,s[i])==0){
            *(stok+i)-=hehe;
        }
    }
}

int main(){
    key_t pointer = point;
    int *stoks;
    int shmid = shmget(pointer,6*sizeof(int),IPC_CREAT | 0666);
    stoks = shmat(shmid,NULL,0);
    int id=0;
    for(id=0;id<6;id++){
        *(stoks+id)=10;
        printf("%d : %s,%d\n",id,s[id],*(stoks+id));
    }

    printf("%d\n",point);
    pthread_t tid[2];
    while(1){
        char s[10];
        scanf("%s",s);
        if(strcmp(s,"pembeli")==0){
            printf("1. Lihat Stock Senjata\n");
            printf("2. Beli Senjata\n");
            printf("Pilih : ");
            int pilihan;scanf("%d",&pilihan);
            if(pilihan==1) pthread_create(&(tid[0]),NULL,&pembeli,(void*)pilihan);
            else if(pilihan==2){
                char input2[50];
                scanf("%s %d",input2,&hehe);
                pthread_create(&(tid[1]),NULL,&pembeli2,(void*)input2);
            }
        }
        else if(strcmp(s,"penjual")==0){
            printf("1. Lihat Stock Senjata\n");
            printf("2. Tambah Stock Senjata\n");
            printf("Pilih : s");
            int pilihan;scanf("%d",&pilihan);
            if(pilihan==1) pthread_create(&(tid[1]),NULL,&penjual,(void*)pilihan);
            else if(pilihan==2){
                char input2[50];
                scanf("%s %d",input2,&hehe);
                pthread_create(&(tid[1]),NULL,&penjual2,(void*)input2);
            }
        }
    }
}