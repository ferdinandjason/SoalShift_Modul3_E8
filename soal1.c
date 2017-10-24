#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

char *s[]={"MP4A1","PM2-V1","SPR-3","SS2-V5","SPG1-V3","MINE"};
int point;

void* penjual(void *arg){
    printf("1. Lihat Stock Senjata\n");
    printf("2. Tambah Stock Senjata\n");
    printf("Pilih : \n");
    key_t pointer = point;
    int *stok;
    int shmid = shmget(pointer,sizeof(int),IPC_CREAT | 0666);
    stok = shmat(shmid,NULL,0);

    int pilihan;scanf("%d",&pilihan);
    if(pilihan==1){
        for(int i=0;i<6;i++){
            if(*(stok+i)>0){
                printf("Jumlah %s di stock = %d barang\n",s[i],*(stok+i));
            }
        }
    }
    else if(pilihan==2){
        char input[20];
        int hehe,i=0;
        scanf("%s %d",input,&hehe);
        for(i=0;i<6;i++){
            if(strcmp(input,s[i])==0){
                *(stok+i)+=hehe;
            }
        }
    }
}

void* pembeli(void *arg){

}

int main(){
    point=&stoks;

}