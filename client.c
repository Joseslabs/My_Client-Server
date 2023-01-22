#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#define MODE 0642
#define BUF_SIZE 8371000     //1048576

int init(const char* fname);

int main(int argc, char const *argv[]) {
    if(argc >= 1){
        printf("\n Exécution de client.c ...\n\n");
        int ret, sc, csc, fd, buf_t=1;
        // récupération et conversion si nécessaire des variables en entrée

        const char* filename = argv[1];

        sc = init(filename);
        //while(1);
    }
    else{
        fprintf(stderr,"\n Le nombre d'arguments en entrée ne correspond pas, veuillez réessayer ... \n\n");
        exit(-1);
    }
    return 0;
}

int init(const char* fname){
    struct sockaddr_in serv_addr;
    int sc, fd, in, out;
    char buf[BUF_SIZE];
    /* Creation du socket*/
    if((sc = socket(AF_INET, SOCK_STREAM, 0))< 0){
        printf("\n Erreur  de socket \n");
        return sc;
    }

    /* Initialisation du strucutre du socket */
    serv_addr.sin_family = AF_INET;
    //serv_addr.sin_port = htons(4445); // port
    serv_addr.sin_port = htons(8080);
    //serv_addr.sin_addr.s_addr = inet_addr("196.192.16.70");
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");


    if(connect(sc, (struct sockaddr *)&serv_addr, sizeof(serv_addr))<0){
        printf("\n Error: Connect Failed (%d) \n", errno);
        return -1;
    }
    fprintf(stdout, "Connecté au serveur ...\n");
    //char buffer[buf_t];
    fd = creat(fname, MODE); if(fd < 0) exit(3);

    while(1){
        in = read(sc,buf,BUF_SIZE);
        if(in <= 0) break;
        out = write(fd, buf, in);
        if(out <= 0) break;
    }
    close(fd);
    fprintf(stdout, "\n Fin de la communication.\n");
    //for(;;){}
    return sc;
}
