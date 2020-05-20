#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/select.h>
#include <time.h> 
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <openssl/ssl.h>
#include <openssl/bio.h>
#include <openssl/err.h>

using namespace std;
using std::vector;
using std::string;

#define FILENAME "small.txt"
#define OUTPUT "result.txt"
#define CHUNKS 10
#define COUNT 5

void generate_n_random(vector<int>& numbers, int n, int upper) {
    srand(time(NULL));
    for (int i = 0; i < n;) {
        int r = rand() % upper;
        if (find(numbers.begin(), numbers.end(), r) == numbers.end()) {
            numbers.push_back(r);
            i += 1;
        }
    }
}

void display_vector(vector<int>& v) {
    cout << "\nDisplaying vector: ";
    for (auto it = v.begin(); it != v.end(); ++it) {
        cout << (*it) << " ";
    }
    cout << endl;
}


void compute_indices(vector<int>& indices, int chunks, int filesize) {
    int step = filesize / chunks;
    int curr_index = 0;
    for (int i = 0; i < chunks; i++) {
        indices.push_back(curr_index);
        curr_index += step;
    }
    indices.push_back(filesize);
}

void display_chunks(vector<int>& numbers, vector<int>& indices, int fd, int filesize, int chunks) {
    int step = filesize / indices.size();
    char* chunk = (char*)calloc(2*step + 1, sizeof(char));

    for (int i = 0; i < chunks; i++) {
        int r = numbers.at(i);
        int chunk_start = indices.at(r);
        int chunk_end = indices.at(r+1);
        cout << endl << chunk_start << '\t' << chunk_end << endl;
        lseek(fd, 0, SEEK_SET);
        lseek(fd, chunk_start, SEEK_SET);
        read(fd, chunk, chunk_end - chunk_start);
        printf("\Printing chunk from %d to %d:\n", chunk_start, chunk_end - 1);
        printf("%s\n", chunk);
        bzero(chunk, chunk_end - chunk_start + 1);
    }
    cout << endl;
    free(chunk);
}


void compute_sha256(char* filename, int filesize, vector<char>& sha256_v) {

    SSL_library_init ();
    ERR_load_BIO_strings();
    SSL_load_error_strings();
    OpenSSL_add_all_algorithms();

    FILE* fp = fopen(filename, "rb");
    if (fp != NULL) {

        unsigned char* sha256_dgst = (unsigned char*) calloc(SHA256_DIGEST_LENGTH, sizeof(char));
        SHA256_CTX sha_ctx;
        if (!SHA256_Init(&sha_ctx)) {
            return;
        }

        char* filebuf = (char*)calloc(filesize + 1, sizeof(char));

        while (!feof(fp))
        {
            size_t total_read = fread(filebuf, 1, sizeof(filebuf), fp);
            if (!SHA256_Update(&sha_ctx, filebuf, total_read))
            {   
                printf("Returning...\n");
                return;
            }
        }
        fclose(fp);

        if (!SHA256_Final(sha256_dgst, &sha_ctx))
            return;

        printf("SHA256: ");
        for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
            char d = sha256_dgst[i];
            printf("%hhu ", d);
        }
        printf("\n");

        free(filebuf);
    }


}

#endif