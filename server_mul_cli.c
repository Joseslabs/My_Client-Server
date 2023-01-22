#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#define MODE 0642
#define BUF_SIZE 8371000

int init();

int main(int argc, char const *argv[]) {
    if(argc >= 1){
        printf("\n Exécution de server.c ...\n\n");
        int csc, sc, fd, dst, in, out; // variables pour ouverture et copie
        char buf[BUF_SIZE];
        // récupération et conversion si nécessaire des variables en entrée

        const char* filename = argv[1];
        //printf("%s",filename);
        sc = init();

        while (1) {
            struct sockaddr_in client_addr;
            socklen_t clen = sizeof(client_addr);

            if((csc = accept(sc, (struct sockaddr *)&client_addr, &clen)) < 0){
                fprintf(stderr, "Un petit problème lors du accept %d\n", errno);
                return -1;
            }
            else if(csc>=0){
                fprintf(stdout, "tentative de connexion\n");
                int idfork = fork();
                if (idfork == 0) {
                    close(sc);

                    fd = open(filename, O_RDONLY); if(fd < 0) exit(2);

                    while(1){
                        in = read(fd,buf,BUF_SIZE);
                        if(in <= 0) break;
                        out = write(csc, buf, in);
                        if(out <= 0) break;
                    }
                    fprintf(stdout, "\n Fichier envoyé avec succèss \n");
                    close(fd);

                    close(csc);
                    exit(0);
                }
                else{
                    close(csc);
                }
            }
        }

        // ouverture et envoi du contenu du fichier


        /*fd = open(filename, O_RDONLY); if(fd < 0) exit(2);

        while(1){
            in = read(fd,buf,BUF_SIZE);
            if(in <= 0) break;
            out = write(csc, buf, in);
            if(out <= 0) break;
        }
        fprintf(stdout, "\n Fichier envoyé avec succèss \n");
        close(fd);
        close(csc);

        for(;;){}*/
    }
    else{
        fprintf(stderr,"\n Le nombre d'arguments en entrée ne correspond pas, veuillez réessayer ... \n\n");
        exit(-1);
    }
    return 0;
}

int init(){
    int sc = socket(AF_INET, SOCK_STREAM, 0), ret; // création du socket
    struct sockaddr_in serv_addr;
    if(sc < 0){
        fprintf(stderr,"Error in socket creation\n");
        return sc;
    }
    serv_addr.sin_family = AF_INET; // famille du serveur ici utilisant TCP/IP
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY); // adresse du serveur
    serv_addr.sin_port = htons(8080); // port d'écoute

    ret=bind(sc, (struct sockaddr*)&serv_addr,sizeof(serv_addr)); // liaison du seveur à son adresse
    if(ret<0){
        printf("Error in bind\n");
        close(sc);
        return ret;
    }

    if(listen(sc, 10) == -1) // serveur mis en écoute
    {
        printf("Failed to listen\n");
        return -1;
    }

    return sc;
}
