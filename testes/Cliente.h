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



struct mem{
    int flag=0;
    int max_size = 1542;

    int mem_id;
    key_t key = 0;
};

class Cliente{
    public:
        std::vector<uint64_t> know_macs;
        int mem_id;
        char* mac_adr;
        int size = 1548;
        struct mem *meio;

    
        Cliente(struct mem *meio){
            this->meio = meio;
            generate_random_string(48);
        }



        bool iniciar(){
            pid_t pid = getpid();
            char *mensagem = (char *)malloc(200 * sizeof(char));            
            snprintf(mensagem, 199, "Process ID is: %d", pid);

            printf("Cliente(%d) iniciando processo\n", pid);
            //long long numero = generateRandomNumber<long long>(20);
            while (1){
                printf("(%d) ... (%d)\n", pid, this->meio->flag);
                if((this->meio->flag) == 0){
            //        int sec = generateRandomNumber2<int>(10);
                    int sec = 0;

                    this->meio->flag = 1;
                    
                    printf("memoria livre, Cliente(%d) tentando escrever na memoria\n", pid);
                    
                    write_to_memory(mensagem);
                    char * lido = read_from_memory();
                    printf("escrito: %s\n", lido);

                    sleep(sec);
                    this->meio->flag = 0;
                }else {                    
                    printf("Cliente(%d) tentando ler, memoria(%d)\n", pid, this->meio->flag);
                    char *teste = read_from_memory();
                    printf("\n\n\n\naaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\n\n\n\n");
                    printf("Conteudo lido da memoria: %s\n", teste);
                }
            }
        }


        void setMac(char* mac_adr){
            this->mac_adr = mac_adr;
        }

        char* getMac(){
            return this->mac_adr;
        }

         
        int generateRandomNumber2(int max) {
            std::random_device rd;
            std::mt19937_64 eng(rd());
            std::uniform_int_distribution<int> distr(0, max);
            return distr(eng);
        }



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

        int write_to_memory(char* message){
            return write_to_memory(message, this->meio->mem_id);
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

        char* read_from_memory(){
            return _read_from_memory(this->meio->mem_id);
        }

        char* _read_from_memory(int mem_id){
            char* tmp;        
            char *str = (char *)shmat(mem_id, NULL, 0);

            if (str == (char *)-1) {
                printf("Erro ao ler da memória\n");
                perror("shmat");
                exit(1);
            }

            tmp = static_cast<char*>(malloc(strlen(str) + 1));

            strcpy(tmp, str);
            shmdt(str);
            return tmp;
        }

        
};