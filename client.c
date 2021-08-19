#include <stdio.h>
#include <stdlib.h>
//structure types
#include <sys/types.h>
#include <sys/socket.h>
//network header
#include <netinet/in.h>

int main(){
    //create network socket
    int net_socket;
    net_socket = socket(AF_INET, SOCK_STREAM, 0);

    //specify an address for socket
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(3000);
    server_address.sin_addr.s_addr = INADDR_ANY; //loopback

    //connect
    int conn_status = connect(net_socket, (const struct sockaddr *)&server_address, sizeof(server_address));

    if(conn_status == -1){
        printf("Conn status -1, exiting...\n");
        exit(1);
    }

    char buffer[6500];

    //receive data
    recv(net_socket, &buffer, sizeof(buffer), 0);
    //recieve cnt
    int cnt = 0;
    recv(net_socket, &cnt, sizeof(cnt), 0);

    //print data that was received
    printf("Server resp> %s : %d\n", buffer, cnt);

    //close the socket
    shutdown(net_socket, SHUT_RDWR);
    return 0;
}