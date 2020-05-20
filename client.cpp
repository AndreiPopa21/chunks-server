#include "utils.h"

using namespace std;

#define ARGC 4

void close_client(int tcp_sockfd, int udp_sockfd);

int main (int argc, char* argv[]) {

    int tcp_sockfd;
    int udp_sockfd;
    struct sockaddr_in tcp_serv_addr;
    struct sockaddr_in udp_serv_addr;
    bzero(&tcp_serv_addr, sizeof(struct sockaddr_in));
    bzero(&udp_serv_addr, sizeof(struct sockaddr_in));


    if (argc != ARGC){
        cout << "Wrong number of arguments (" << argc << ") should be "<< ARGC << endl;
        exit(0); 
    }

    //............init UDP socket.............
    udp_sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (udp_sockfd < 0) {
        cout << "[client] Failed to create UDP socket\n";
        exit(0);
    }

    //............init TCP socket.............
    tcp_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (tcp_sockfd < 0) {
        cout << "[client] Failed to create TCP socket\n";
        exit(0);
    }


    //...........preparing UDP connection..........
    int udp_port = atoi(argv[3]);
    char* udp_ip = argv[1];
    udp_serv_addr.sin_family = AF_INET;
    udp_serv_addr.sin_port = htons(udp_port);
    inet_aton(udp_ip, &udp_serv_addr.sin_addr);


    //...........preparing TCP connection...........
    int tcp_port = atoi(argv[2]);
    char* tcp_ip = argv[1];
    tcp_serv_addr.sin_family = AF_INET;
    tcp_serv_addr.sin_port = htons(tcp_port);
    inet_aton(tcp_ip, &tcp_serv_addr.sin_addr);


    int wp = open(OUTPUT, O_WRONLY | O_APPEND);
    

    return 0;
}

void close_client(int tcp_sockfd, int udp_sockfd) {
    close(tcp_sockfd);
    close(udp_sockfd);
    exit(0);
}