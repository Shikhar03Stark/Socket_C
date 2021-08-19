#include <stdio.h>
#include <stdlib.h>
//Data structures
#include <sys/types.h>
#include <sys/socket.h>
//Network
#include <netinet/in.h>

void run(int ser_socket){

    char s_greet[6500] = "Hello, connected to server\n";
    int cnt = 5;
    while(cnt--){
        int client_socket;
        //client_socket is now ready for transmission
        client_socket = accept(ser_socket, NULL, NULL);

        send(client_socket, s_greet, sizeof(s_greet), 0);
        send(client_socket, &cnt, sizeof(cnt), 0);

        shutdown(client_socket, SHUT_RDWR);

        printf("Conn left: %d\n", cnt);
    }

}

int main(){
    int ser_socket;
    ser_socket = socket(AF_INET, SOCK_STREAM, 0);

    //define server addr
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(3000);
    server_address.sin_addr.s_addr = INADDR_ANY;

    //same as connect but to perfom listen ops
    bind(ser_socket, (const struct sockaddr*) &server_address, sizeof(server_address));

    //listen with queue len of 3
    listen(ser_socket, 3);

    run(ser_socket);

    shutdown(ser_socket, SHUT_RDWR);
    return 0;
}