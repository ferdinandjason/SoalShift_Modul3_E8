#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdlib.h>
typedef long long int ll;
pthread_t tid[5];
ll a,b,c;
void* counta(void *argv){
    ll num=1;
    for(ll i=2;i<=a;i++) num*=i;
    printf("Hasil %lld! = %lld\n",a,num);
    return NULL;
}
void* countb(void *argv){
    ll num=1;
    for(ll i=2;i<=b;i++) num*=i;
    printf("Hasil %lld! = %lld\n",b,num);
    return NULL;
}
void* countb(void *argv){
    ll num=1;
    for(ll i=2;i<=c;i++) num*=i;
    printf("Hasil %lld! = %lld\n",c,num);
    return NULL;
}
int main(){
    scanf("%lld %lld %lld",&a,&b,&c);
    pthread_create(&(tid[0]),NULL,&count1,NULL);
}