# SoalShift_Modul3_E8

Soal Shift Praktikum Modul 3 (Thread dan IPC)

```
@@@@@@@@@@    @@@@@@   @@@@@@@   @@@  @@@  @@@          @@@@@@ 
@@@@@@@@@@@  @@@@@@@@  @@@@@@@@  @@@  @@@  @@@          @@@@@@@
@@! @@! @@!  @@!  @@@  @@!  @@@  @@!  @@@  @@!              @@@
!@! !@! !@!  !@!  @!@  !@!  @!@  !@!  @!@  !@!              @!@
@!! !!@ @!@  @!@  !@!  @!@  !@!  @!@  !@!  @!!          @!@!!@ 
!@!   ! !@!  !@!  !!!  !@!  !!!  !@!  !!!  !!!          !!@!@! 
!!:     !!:  !!:  !!!  !!:  !!!  !!:  !!!  !!:              !!:
:!:     :!:  :!:  !:!  :!:  !:!  :!:  !:!   :!:             :!:
:::     ::   ::::: ::   :::: ::  ::::: ::   :: ::::     :: ::::
 :      :     : :  :   :: :  :    : :  :   : :: : :      : : : 

      +-++-++-++-++-++-+ +-++-++-+ +-++-++-+
      |T||h||r||e||a||d| |d||a||n| |I||P||C|
      +-++-++-++-++-++-+ +-++-++-+ +-++-++-+
```
## Daftar Isi
- [1. Thread](https://github.com/ferdinandjason/SoalShift_Modul3_E8#thread)
- [2. IPC](https://github.com/ferdinandjason/SoalShift_Modul3_E8#ipc)
- [3. Pipes](https://github.com/ferdinandjason/SoalShift_Modul3_E8#pipes)
- [4. Socket](https://github.com/ferdinandjason/SoalShift_Modul3_E8#socket)
- [5. Message Queue](https://github.com/ferdinandjason/SoalShift_Modul3_E8#message-queue)
- [6. Semaphores](https://github.com/ferdinandjason/SoalShift_Modul3_E8#semaphores)
- [7. Shared Memory](https://github.com/ferdinandjason/SoalShift_Modul3_E8#shared-memory)
- [8. Soal Shift](https://github.com/ferdinandjason/SoalShift_Modul3_E8#soal-shift)


## Thread

Thread merupakan unit terkecil dalam suatu proses yang bisa dijadwalkan oleh sistem operasi. Dimana THREAD juga bisa menjalankan suatu tugas secara bersamaan. Dalam thread terdapat ID Thread, Program COunter, Register dan Stack.
Untuk mengecek bisa menggunakan perintah
```
$ top -H
```
Untuk membuat suatu Thread menggunakan :
```c
int pthread_create(pthread_t * thread,const pthread_attr_t * attr,void * (*start_routine)(void *),void *arg);
```
Hasil kembalian dari inisialisasi adalah 0 atau 1, 0 berarti tidak ada error sedangkan 1 berarti ada error.
Penjelasan Syntax:
```
- thread : mengembalikan thread id.
- attr   : Set menjadi NULL jika default thread attribut digunakan. Jika
           tidak definisi members dari struct pthread_attr_t didefinisikan menjadi bits/pthreadtypes.h) Atribut-atribut yang termasuk:
    * detached state (joinable? Default: PTHREAD_CREATE_JOINABLE. Other option: PTHREAD_CREATE_DETACHED)
    * scheduling policy (real-time? PTHREAD_INHERIT_SCHED,PTHREAD_EXPLICIT_SCHED,SCHED_OTHER)
    * scheduling parameter
    * inheritsched attribute (Default: PTHREAD_EXPLICIT_SCHED Inherit from parent thread: PTHREAD_INHERIT_SCHED)
    * scope (Kernel threads: PTHREAD_SCOPE_SYSTEM User threads: PTHREAD_SCOPE_PROCESS Pick one or the other not both.)
    * guard size
    * stack address (See unistd.h and bits/posix_opt.h _POSIX_THREAD_ATTR_STACKADDR)
    * stack size (default minimum PTHREAD_STACK_SIZE set in pthread.h)
- void * (*start_routine) : pointer ke fungsi yang akan menjadi thread. Fungsi menjadi sebuah argument yang menunjuk ke fungsi void.
- *arg - pointer ke argument fungsi. 
```
## IPC
IPC (*Interprocess Communication*) adalah cara atau mekanisme pertukaran data antara satu proses dengan proses lain, baik pada komputer yang sama atau komputer jarak jauh yang terhubung melalui suatu jaringan.

## Pipes
Pipe merupakan komunikasi sequensial antar proses yang saling terelasi. Kelemahannya, hanya dapat digunakan untuk proses yang saling berhubungan dan secara sequensial.
Terdapat dua jenis pipe:
- unnamed pipe : Komunikasi antara parent dan child proses.
- named pipe : Biasa disebut sebagai FIFO, digunakan untuk komunikasi yang berjalan secara independen. **Hanya bisa digunakan jika kedua proses menggunakan *filesystem* yang sama.**
```
$ ls | less
```

## Socket
*Socket* merupakan sebuah *end-point* dalam sebuah proses yang saling berkomunikasi. Biasanya *socket* digunakan untuk komunikasi antar proses pada komputer yang berbeda, namun dapat juga digunakan dalam komputer yang sama.

Example : [socket-server.c](https://github.com/desyrahmi/sisop-modul-3/blob/master/socket-server.c) [socket-client.c](https://github.com/desyrahmi/sisop-modul-3/blob/master/socket-client.c)

Server
```c
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#define PORT 8080

int main(int argc, char const *argv[]) {
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    char *hello = "Hello from server";
      
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
      
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
      
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    valread = read( new_socket , buffer, 1024);
    printf("%s\n",buffer );
    send(new_socket , hello , strlen(hello) , 0 );
    printf("Hello message sent\n");
    return 0;
}
```
Client
```c
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#define PORT 8080
  
int main(int argc, char const *argv[]) {
    struct sockaddr_in address;
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char *hello = "Hello from client";
    char buffer[1024] = {0};
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }
  
    memset(&serv_addr, '0', sizeof(serv_addr));
  
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
      
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
  
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }

    send(sock , hello , strlen(hello) , 0 );
    printf("Hello message sent\n");
    valread = read( sock , buffer, 1024);
    printf("%s\n",buffer );
    return 0;
}
```
Jalankan proses server dulu, kemudian jalankan clientnya. Dan amati apa yang terjadi.

## Message Queues
Merupakan komunikasi antar proses dimana proses tersebut menciptakan internal linked-list pada alamat kernel Sistem Operasi. Pesannya disebut sebagai *queue* sedangkan pengenalnya disebut *queue* ID. *Queue* ID berguna sebagai *key* untuk menandai pesan mana yang akan dikirim dan tujuan pengiriman pesannya.

## Semaphores
Semaphore berbeda dengan jenis-jenis IPC yang lain. Pada pengaplikasiannya, semaphore merupakan sebuah counter yang digunakan untuk controlling resource oleh beberapa proses secara bersamaan.
- Jika suatu counter block memory memiliki nilai positif, semaphore dapat menggunakan resource untuk prosesnya, dan mengurangi nilai counter block dengan 1 untuk menandai bahwa suatu block memory tengah digunakan.
- Sebaliknya, jika semaphore bernilai 0, proses akan masuk pada mode sleep sampai semaphore bernilai lebih besar dari 0.

## Shared Memory
Sebuah mekanisme *mapping area(segments)* dari suatu blok *memory* untuk digunakan bersama oleh beberapa proses. Sebuah proses akan menciptakan *segment memory*, kemudian proses lain yang diijinkan dapat mengakses *memory* tersebut. *Shared memory* merupakan cara yang efektif untuk melakukan pertukaran data antar program.

## Soal Shift
```
SOAL 1 (Menggunakan Shared Memory)
Aidil Abdillah Suyudi, biasa dipanggil Aidil, adalah seorang yang mempunyai kepribadian “ingin didengar” dan “ingin diperhatikan” oleh semua orang. Ketika Aidil sedang berada di depan banyak orang, Aidil suka sekali memukul sebuah kayu dengan menggunakan palu. Aidil melakukan hal tersebut supaya orang-orang yang berada di depannya diam dan hanya fokus kepada Aidil. Lama kelamaan, Aidil merasa bosan dengan cara tersebut. Maka Aidil mencari jalan lain. Aidil mempunyai ide bagaimana jika dia membeli beberapa senjata. Maka datanglah Aidil ke seorang distributor senjata yang bernama Khawari Muhammad Dzakwan, biasa dipanggil Hawari. 

Singkat cerita, Aidil sering kali membeli senjata ke Hawari. Suatu ketika Hawari meminta tolong kepada Aidil untuk membuatkan sebuah sistem informasi sederhana untuk tokonya. Sistem yang diminta oleh Hawari terdapat dua, untuk pembeli dan juga untuk Hawari sendiri. Spesifikasi sistem untuk Hawari (penjual) antara lain :
Terdapat dua menu : lihat stock senjata dan tambah stock senjata. Menu tersebut harus bisa ditampilkan di sistem.
Tambah stock senjata memiliki format inputan : [nama_barang] [jumlah_barang]. Jika barang yang sudah ada di stock diinputkan kembali, maka jumlah barang tersebut ditambah.
    Contoh :
    Jumlah MP4A1 di stock = 19 barang
    MP4A1 20 -> menjalankan fitur tambah stock
    Maka stock MP4A1 akan menjadi 39 barang
Lihat stock senjata berfungsi untuk menampilkan semua senjata yang terdapat di dalam stock. Oh iya, Hawari juga meminta hanya ditampilkan senjata-senjata yang stock > 0. Format outputnya adalah : [nama_barang] [jumlah_barang]
Catatan : Barang yang dijual di toko Hawari -> MP4A1, PM2-V1, SPR-3, SS2-V5, SPG1-V3, dan MINE
Spesifikasi sistem untuk pembeli antara lain :
Terdapat dua menu : lihat stock senjata dan beli senjata. Menu tersebut harus bisa ditampilkan di sistem.
Fitur beli senjata memiliki format inputan : [nama_barang] [jumlah_barang]. Jika fitur ini dijalankan, maka stock senjata akan berkurang sesuai jumalh yang dibeli. Jika jumlah pembelian lebih dari stock yang tersedia, maka program menampilkan pesan “barang di stock tidak cukup”.
Lihat stock senjata berfungsi untuk menampilkan semua senjata yang terdapat di dalam stock. Senjata yang jumlah stock nya kosong juga ikut ditampilkan. Format outputnya adalah : [nama_barang] [jumlah_barang]



SOAL 2
Aidil akhirnya mempunyai banyak senjata. Senjata-senjata tersebut sering dia pakai dan akhirnya cepat habis. Tetapi MINE (ranjau) yang dia beli tidak dipakai sedikitpun. Aidil pun akhirnya mempunyai ide untuk memasang MINE yang dia miliki di sekitar rumahnya supaya rumah Aidil aman dari perampok / orang-orang jahat.

Suatu hari, ada teman Aidil yang bernama Raldo Kusuma, biasa dipanggil Raldo, ingin bertamu ke rumah Aidil. Aidil pun memberitahu ke Raldo kalau harus berhati-hati saat akan memasuki halaman rumahnya karena terdapat banyak ranjau. Singkat cerita, Raldo pun akhirnya masuk ke rumah Aidil dan mereka pun berbincang.

Raldo adalah seorang yang sangat suka bermain game, dia pun akhirnya menawarkan kepada Aidil untuk membuat game. Game yang akan dibuat adalah game ranjau, terinspirasi dari apa yang Aidil lakukan untuk halaman rumahnya. Spesifikasi dari game yang akan dibuat Raldo adalah sebagai berikut:
Terdapat 2 pemain, tiap pemain dapat memasukan nama sesuai inputan.
Masing-masing pemain mempunyai 16 lubang yang nantinya bisa diisi oleh ranjau.
Selama game berlangsung, pemain ke-1 dan pemain ke-2 akan saling bergantian mengisi lubang-lubang yang dimilikinya dengan ranjau. Sedangkan salah satunya memberikan tebakan lubang mana saja yang aman dari ranjau.
Setiap gilirannya, pemain bisa memasang 1-4 ranjau di lubang yang berbeda, dan lawannya harus menebak 4 lubang.
Cara pemasanganan maupun penebakan ranjau adalah : [nomor_lubang]
Pemain yang memasang ranjau mendapatkan poin +1 jika pemain yang menebak salah menebak lubang (lubang tersebut ada ranjaunya)
Pemain yang menebak lubang mendapatkan poin +1 jika pemain lubang yang dia tebak tidak terdapat ranjau.
Game berakhir ketika:
Salah satu pemain ada yang mendapatkan nilai 10
Tidak ada pemain yang mendapatkan nilai 10, dan kedua lubang dari kedua pemain sudah terisi penuh dengan ranjau.
Terdapat fitur untuk mengecek poin dari kedua pemain
Permainan ini hanya dijalankan di 1 console saja
Permainan ini harus menggunakan lebih dari 1 thread




SOAL 3
Suatu hari Aidil pun ingin mempunyai sebuah kolam sendiri, yang nantinya hanya akan diisi oleh Lohan dan Kepiting. Sebelum membuat sebuah lohan tersebut, Aidil ingin memvisualisasikan kolamnya tersebut dalam sebuah program C. Program yang ingin Aidil buat memiliki spesifikasi sebagai berikut:
Hewan yang tersedia adalah Lohan dan Kepiting
Kedua hewan tersebut mempunyai status, yang nantinya akan digunakan sebagai parameter lapar / tidak.
Status awal dari kedua hewan tersebut adalah 100.
Pada hewan lohan, setiap 10 detik statusnya berkurang sebanyak 15
Pada hewan kepiting, setiap 20 detik statusnya berkurang sebanyak 10
Terdapat dua fitur menu, antara lain beri makan lohan & beri makan kepiting.
Beri makan lohan berfungsi untuk memberi makan lohan, dan statusnya bertambah sebanyak 10
Beri makan kepiting berfungsi untuk memberi makan kepiting, dan statusnya bertambah sebanyak 10
Game akan berakhir jika:
Status dari salah satu hewan tersebut <= 0
Status dari salah satu hewan tersebut > 100
Program ini harus menggunakan lebih dari 1 thread

Capek ya baca cerita Aidil terus, gantian cerita yang lain ya h3h3


SOAL 4
Aidil mempunyai teman dekat, teman seperjuangan selama kurang lebih 6 bulan untuk menjadi bagian dari salah satu lab di jurusannya, sebut saja Aguel. Aguel adalah mahasiswa semester tiga. Saat kuliah kalkulus, Aguel teringat jika pernah membuat sebuah program untuk mencari hasil dari bilangan faktorial. Tetapi Aguel sadar, jika program yang ia buat tidaklah sepurna, dan bisa dibilang program tersebut terlalu lama. Karena Aguel kesusahan untuk membuat program yang sempurna dan dapat berjalan lebih cepat, Aguel meminta tolong kepada temannya bernama Syach Putri. Syach Putri mempunyai ide untuk membuat program yang baru dengan menggunakan thread. Setiap bilangan faktorial yang dicari hasilnya akan dibuatkan thread untuk mempercepat perhitungan. Syach Putri sangatlah baik, maka ia bersedia untuk membantu Aguel.

    Contoh Input :
    ./faktorial 3 2 4

    Contoh Output :
    Hasil 2! = 2
    Hasil 3! = 6
    Hasil 4! = 24


Soal 5
Suatu hari, Ridho sedang asik membaca buku Novel. Ridho kaget karena didalam buku tersebut ada nama dua cewek yang diidolakannya yaitu Ifah dan Fina. Ridhopun kepo ada berapa kali nama cewek yang diidolakannya tertulis pada novel. Bantulah Ridho untuk membuat program pencarian kata menggunakan thread. Setiap kata yang dicari akan dibuatkan thread tersendiri.

Input :
./cari Ifah Fina

Output : 
Ifah : 2
Fina : 10
```


Kelompok E8
  - Ferdinand Jason 0511164000033
  - Nurlita Dhuha F 0511164000092

Teknik Informatika - Institut Teknologi Sepuluh November
