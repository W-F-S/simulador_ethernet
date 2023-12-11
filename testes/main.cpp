#include <cstdint>
#include <iostream>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <random>
#include "Cliente.h"


int main(){

    key_t key = ftok("./main.cpp", 'a');
    if (key == -1) {
        perror("ftok");
        exit(1);
    }

    Cliente cliente(key);


    const char* message = "Hello, shared memory!";
    cliente.write_to_memory(const_cast<char*>(message), cliente.mem_id);
    char* readMessage = cliente.read_from_memory(cliente.mem_id);


    // Display the read message
    if (readMessage != nullptr) {
        std::cout << "Read Message: " << readMessage << std::endl;
        free(readMessage);  // Don't forget to free the allocated memory
    }


    return 0;
}