#include <iostream>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include <cstring>
#include <cstdlib>
#include <unistd.h>
using namespace std;
 

int max = 1542;

/**
1º temos que simular um meio
    max 1544 bytes
    flag de acesso.

2º tempo que implementar um pc

3º temos que criar pacotes

*/

struct mem{
    int flag;
    int_8t max_size = 1542;
    int mem_id;
    key_t key;
};


struct pc{
    long mac;
};

int create_or_att_memory(key_t key){

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
    char 
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
    write_to_memory("teste123", teste->mem_id);
    read_from_memory(teste->mem_id);
    return 0;
}

