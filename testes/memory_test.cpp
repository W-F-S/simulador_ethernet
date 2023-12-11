#include <cstdint>
#include <iostream>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <cstring>


#include <cstdlib>
#include <unistd.h>
#include <random>
using namespace std;
 

int max = 1542;

/**
1º temos que simular um meio
    max 1544 bytes
    flag de acesso.

2º tempo que implementar um pc

3º temos que criar pacotes

*/


// Function to generate a random number with a fixed byte length
template <typename T>
T generateRandomNumber(int byteLength) {
    std::random_device rd;
    std::mt19937_64 eng(rd());
    std::uniform_int_distribution<uint8_t> distr(0, std::numeric_limits<uint8_t>::max());

    // Set the first 2 bits to 0
    value[0] &= 0b00111111;

    // Fill the rest with random values
    for (int i = 1; i < 6; ++i) {
        value[i] = distr(eng);
    }

    return randomValue;
}





//    int_8t max_size = 1542;

struct mem{
    int flag;
    int max_size = 1542;

    int mem_id;
    key_t key;
};



struct client{
    uint8_t mac;
};


int create_or_att_memory(key_t key){

}


client* generate_client(){
    struct client* tmp = (struct client*)malloc(sizeof(struct client));
    tmp->mac = generateRandomNumber<uint8_t>(6);
}


int write_to_memory(char* message, int mem_id){
    // shmat to attach to shared memory

    char *str = (char*)shmat(mem_id, NULL, 0);
    if (str == (char*)-1) {
        perror("shmat");
        exit(1);
    }

    snprintf(str, 1542, "%s", message );

    shmdt(str);
    return 0;
}


char read_from_memory(int mem_id){
    char *str = (char*)shmat(mem_id, NULL, 0);

    if (str == (char*)-1) {
        perror("shmat");
        exit(1);
    }
    printf("Data from memory %s", str);

    shmdt(str);
    return 0;
}


//gerar um tamanho fixo para cada pacote. nao é precito ter tanta complexidade. 
//estamos trabalhando com um simulador com pacote fixo
//tomar cuidado com o tamanho mínimo do pacote

// setar a flag ta 0 
// o primeiro que colocar alguma coisa, set a flag para 1
// verificar se o pacote é esse ou não
// se não, verificar onde devemos aguardar um tempo e tentar depois

//mac de 24 bits


//um mac deve ter 48 bits 
int main()
{
    int size = 1548;

    struct mem *teste = (struct mem*)malloc(sizeof(struct mem)); 
    struct client *pc_n = generate_client();


    teste->key = ftok("./mem", 55);  //toda vez que mudar o tamnho da memoria, associar a um arquivo ou ID novo

    if(teste->key == -1){
        perror("ftok");
        exit(1);
    }

    
    // shmget returns an identifier in shmid
    while(((teste->mem_id = shmget(teste->key, size, IPC_CREAT) < 0))){
        cout << "impossível criar memoria " << size << "\n";
        perror("shmget");
        sleep(2);
    }

   // printf("Mem_id: %d\n", teste->mem_id);
   // if(teste->mem_id == -1 && shmctl(teste->key, IPC_RMID, NULL) == -1){
   //     perror("shmctl IPC_RMID");
   //     exit(0);
   //     
   // }

    // printf("teste: id: %d \n", teste->mem_id);    


struct pc{
    long mac;
};


int write_to_memory(char* message, int mem_id){
    // shmat to attach to shared memory
    char *str = (char*)shmat(mem_id, (void*)0, 0);
    snprintf(str, max, "%s", message )
//    cout << "Data written in memory: " << str << endl;
    shmdt(str);
    return 0;
}

int read_from_memory(int mem_id){
    char *str = (char*)shmat(mem_id, (void*)0, 0);
    cout << "Data written in memory: " << str << endl;
    shmdt(str);
    return 0;
}

 
int main()
{
    struct mem *teste = (struct mem*)malloc(sizeof(struct mem)); 

    teste->key = ftok("shmfile", 65); 

    // shmget returns an identifier in shmid
    teste->mem_id = shmget(teste->key, teste->max_size, 0777 | IPC_CREAT);

    

    write_to_memory("teste123", teste->mem_id);
    read_from_memory(teste->mem_id);
    return 0;
}