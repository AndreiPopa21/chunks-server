#include "utils.h"

using namespace std;

#define ARGC 2

void close_server(int sockfd);

int main (int argc, char* argv[]) {

    vector<int> numbers;
    vector<int> indices;
    vector<char> sha256_v;
    numbers.clear();
    indices.clear();
    sha256_v.clear();

    int sockfd;
    struct sockaddr_in serv_addr;
    struct sockaddr_in cli_addr;
    bzero(&serv_addr, sizeof(struct sockaddr_in));
    bzero(&cli_addr, sizeof(struct sockaddr_in));


    if (argc != ARGC){
        cout << "Wrong number of arguments (" << argc << ") should be "<< ARGC << endl;
        exit(0); 
    }

    int port = atoi(argv[1]);

    generate_n_random(numbers, CHUNKS, CHUNKS);
    display_vector(numbers);

    int fd = open(FILENAME, O_RDONLY);
    if (fd == NULL) {
        cout << "[server] Cannot open file\n";
        exit(0);
    }

    int filesize = lseek(fd, 0, SEEK_END);
    cout << filesize << endl;
    lseek(fd, 0, SEEK_SET);

    compute_indices(indices, CHUNKS, filesize);
    display_vector(indices);  

    compute_sha256(FILENAME, filesize, sha256_v);
    //display_chunks(numbers, indices, fd, filesize, COUNT);

    

    //.............init TCP socket................
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        cout << "[server] Failed to create TCP socket\n";
        exit(0);
    }



    //..............preaping TCP connection..........
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    serv_addr.sin_addr.s_addr = INADDR_ANY;

    cout << "Port: " << port << endl;


    //..............bind socket.....................
    if (bind(sockfd, (struct sockaddr*)&serv_addr, sizeof(struct sockaddr)) < 0) {
        cout << "[server] Failed to bind server socket\n";
        close_server(sockfd);
    }
    cout << "[server] Succesfully bind server socket" << endl;


    


    close_server(sockfd);
}


void close_server(int sockfd) {
    close(sockfd);
    exit(0);
}