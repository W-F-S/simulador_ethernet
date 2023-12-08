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
    int max_size = 1542;
    int mem_id;
    key_t key;
};


struct pc{
    long mac;
};


int write_to_memory(char* message, int mem_id){
    // shmat to attach to shared memory
    printf("teste1\n");
    char *str = (char*)shmat(mem_id, NULL, 0);
    if (str == (char*)-1) {
        perror("shmat");
        exit(1);
    }
    printf("teste2\n");
    snprintf(str, 1542, "%s", message );
    printf("teste3\n");

//    cout << "Data written in memory: " << str << endl;
    shmdt(str);
    return 0;
}

int read_from_memory(int mem_id){
    char *str = (char*)shmat(mem_id, NULL, 0);
    if (str == (char*)-1) {
        perror("shmat");
        exit(1);
    }
    printf("Data from memory %s", str);

    shmdt(str);
    return 0;
}



//while(1){
//    sleep(3);
//    cout << "esperando\n";
//}
 
int main()
{
    int size = 1547;

    struct mem *teste = (struct mem*)malloc(sizeof(struct mem)); 

    teste->key = ftok("./mem2", 55);  //toda vez que mudar o tamnho da memoria, associar a um arquivo ou ID novo
    if(teste->key == -1){
        perror("ftok");
        exit(1);
    }

    printf("teste: key: %d \n", teste->key);    
    
    // shmget returns an identifier in shmid
    while(((teste->mem_id = shmget(teste->key, size, IPC_CREAT) < 0))){
        cout << "impossível criar memoria " << size << "\n";
        //size = size - 1;
        sleep(2);
        
        //shmctl(teste->key, IPC_RMID, NULL);
    }

    exit(1);

    printf("Mem_id: %d\n", teste->mem_id);
    if(teste->mem_id == -1 && shmctl(teste->key, IPC_RMID, NULL) == -1){
        perror("shmctl IPC_RMID");
        exit(0);
    }
    teste->mem_id = shmget(teste->key, 1542, 0777);

    printf("teste: id: %d \n", teste->mem_id);    
    write_to_memory("teste123", teste->mem_id);
    read_from_memory(teste->mem_id);
    return 0;
}

