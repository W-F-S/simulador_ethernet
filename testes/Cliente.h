#include <cstddef>
#include <cstdint>
#include <iostream>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <cstring>
#include <cstdlib>
#include <sys/types.h>
#include <unistd.h>
#include <random>
#include <vector>

class Cliente{
    public:
        std::vector<uint64_t> know_macs;
        int mem_id;
        uint64_t mac_adr;
        int size = 1548;

    
        Cliente(key_t key, uint64_t mac_adr = -1){
            this->mem_id = connect_meio(key);
            if(mac_adr == -1){
                this->mac_adr = generate_mac();
            }
        }


        uint64_t generate_mac(){
            std::random_device rd;
            std::mt19937_64 eng(rd());
            std::uniform_int_distribution<uint64_t> distr(0, (UINT64_C(1) << 46) - 1);

            // Generate a random 46-bit number
            uint64_t randomValue = distr(eng);

            // Clear the first 2 bits
            randomValue &= ~(UINT64_C(0b11) << 46);

            return randomValue;
        }

        int connect_meio(key_t key){
            int mem_id = shmget(key, this->size, 0777 | IPC_CREAT);
            if (mem_id < 0) {
                perror("impossível criar memoria\nshmget");
            }
            return mem_id;
        }

        int setMac(uint64_t mac_adr){
            this->mac_adr = mac_adr;
        }

        int set_mem_id(int mem_id){
            char *str = (char*)shmat(mem_id, NULL, 0);
            if (str == (char*)-1) {
                printf("Impossível conectar no endereço: %d\n" , mem_id);
                perror("shmat");
                return -1;
            }else{
                this->mem_id = mem_id;
                return 1;
            }
        }

        int write_to_memory(char* message, int mem_id){
            // shmat to attach to shared memory
            char *str = (char*)shmat(mem_id, NULL, 0);
            if (str == (char*)-1) {
                printf("Erro ao escrever na memória\n");
                perror("shmat");
                return(-1);
            }
            snprintf(str, 1542, "%s", message );

            shmdt(str);
            return 1;
        }


        char* read_from_memory(int mem_id){
            char* tmp;        
            char *str = (char *)shmat(mem_id, NULL, 0);
            if (str == (char *)-1) {
                printf("Erro ao ler da memória\n");
                perror("shmat");
                exit(1);
            }
            printf("Data from memory %s\n", str);


            // Allocate memory for a new char array to store the data
            tmp = static_cast<char*>(malloc(strlen(str) + 1));
            // Copy the data from str to copiedValue
            strcpy(tmp, str);
            shmdt(str);
            return tmp;
        }
};