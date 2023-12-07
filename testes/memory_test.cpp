#include <iostream>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
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
