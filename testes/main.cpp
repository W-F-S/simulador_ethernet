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

using namespace std;




int main(){
    struct mem *meio = (struct mem*)malloc(sizeof(struct mem)); 


    meio->key = ftok("./main.cpp", 'a');
    if (meio->key == -1) {
        perror("ftok");
        exit(1);
    }

    for(int i = 0; i < 90; ++i) {
        pid_t pid = fork();

        if (pid == -1) {
            perror("fork");
            exit(1);
        } else if (pid == 0) {


            Cliente childCliente(meio->key, -1, meio);

            cout << "Child process " << i << " created. Mac: " << childCliente.getMac()<< endl;
                childCliente.iniciar();


            // Code for the child process


            // You can create a new instance of Cliente in the child process if needed.
            // For example:

            

            // Additional child process logic can be added here.

          // Exit the child process
                      exit(0);
        }
    }





    //int teste = cliente.generateRandomNumber<long long>(1);
    //printf("Teste123: %d", teste);
    //long long teste = cliente.generate_packet();
    //printf("Teste123: %b", teste);

/*
    const char* message = "Hello, shared memory!";
    cliente.write_to_memory(const_cast<char*>(message), cliente.mem_id);
    char* readMessage = cliente.read_from_memory(cliente.mem_id);


    // Display the read message
    if (readMessage != nullptr) {
        std::cout << "Read Message: " << readMessage << std::endl;
        free(readMessage);  // Don't forget to free the allocated memory
    }
*/

    return 0;
}