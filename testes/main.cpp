#include <cstdint>
#include <iostream>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <random>
#include <vector>
#include "Cliente.h"

using namespace std;



char* generate_random_string(int size) {
    std::random_device rd;
    std::uniform_int_distribution<int> dist(1, 255);

    // Allocate memory for the string
    char* data = (char*)malloc( size * sizeof(char));
    
    for (int i = 0; i < size; i++) {
        data[i] = static_cast<char>(dist(rd) & 0xFF);
        std::cout << i << std::endl;
    }
    data[size-1] = '\0';
     
    return data;
}

int main(){
    struct mem *meio = (struct mem*)malloc(sizeof(struct mem)); 

    meio->mem_id = shmget(999, 1500, 0777 | IPC_CREAT);
    if (meio->mem_id < 0) {
        perror("impossível criar memoria\nshmget");
    }

/*
    for(int i = 0; i < 90; ++i) {
        pid_t pid = fork();

        if (pid == -1) {
            perror("fork");
            exit(1);
        } else if (pid == 0) {


            Cliente childCliente(meio);

            cout << "Child process " << i << " created. Mac: " << childCliente.getMac()<< endl;
            childCliente.iniciar();
        }
    }
*/
    return 0;
}