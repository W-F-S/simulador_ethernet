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
        uint64_t mac_adr;
        int size = 1548;
        struct mem *meio;

    
        Cliente(key_t key, uint64_t mac_adr = -1, struct mem *meio = NULL){
            this->mem_id = connect_meio(key);
            if(mac_adr == -1){
                this->mac_adr = generate_mac();
            }
            if(meio != nullptr){
                this->meio = meio;                
            }
        }



        bool iniciar(){
            pid_t pid = getpid();
            char *mensagem = (char *)malloc(200 * sizeof(char));            
            snprintf(mensagem, 199, "Process ID is: %d", pid);

            printf("Cliente(%d) iniciando processo\n", pid);
            long long numero = generateRandomNumber<long long>(20);
            while (1){
                printf("(%d) ... (%d)\n", pid, this->meio->flag);
                if((this->meio->flag) == 0){
                    int sec = generateRandomNumber2<int>(10);

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
            return this->mac_adr;
        }

        int getMac(){
            return this->mac_adr;
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

        //gpt
        template <typename T>
        T generateRandomNumber(int byteLength) {
            std::random_device rd;
            std::mt19937_64 eng(rd());
            std::uniform_int_distribution<T> distr(0, std::numeric_limits<T>::max());
            T randomValue = 0;
            for (int i = 0; i < byteLength; i++) {
                randomValue = (randomValue << 8) | distr(eng);
            }
            randomValue &= ((T(1) << (byteLength * 8)) - 1);
            return randomValue;
        }

//gpt
        template <typename T>
        T generateRandomNumber2(int max) {
            std::random_device rd;
            std::mt19937_64 eng(rd());
            std::uniform_int_distribution<T> distr(0, max);
            return distr(eng);
        }

        int write_to_memory(char* message){
            return write_to_memory(message, this->mem_id);
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
            return _read_from_memory(this->mem_id);
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

        long long generate_packet(){
            return generateRandomNumber<long long>(1400);
        }
};