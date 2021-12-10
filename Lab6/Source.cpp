#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>
#include <semaphore.h>
#include <sys.wait>

int main(){
    // create shared memory object
    int md = shm_open("my_memory", O_CREAT | O_RDWR, 0);
    long pg_size = synconf (_SC_PAGESIZE);
    if((ftruncate(md, pg_size)) == -1){
        perror ("ftruncate failed");
        return 0;
    }
    void* virt-addr = mmap(0, pg_size, PROT_READ|PROT_WRITE, MAP_SHARED, md, 0); //caddr-t type no longer supported. Using void* instead

    //create an unnamed semaphore
    sem_t semp;
    int status = sem_init(&semp, true, 1);
    if(status){
        perror("sem_init failed");
        return 0;
    }

    //create the child process
    int pid = fork();
    //cast the virtual addres to instead
    int* count = (int*) virt_addr;
    *count = 0;

    while (*count < 1000){
        //lock the semaphore
        status = sem_wait(&semp);
        // flip the coin
        if (rand() % 2 + 1 == 2){
            //increment the shared memory
            count++;
        }
        //free the semaphore
        status = sem_post(&semp);
    }

    //close and unmap the shared memory
    status = munmap(virt_addr, pg_size);
    status = close(md);
    status = shm-unlink ("my_memory");

    //close the semaphore
    status = sem_close(&semp); 

    //wait the child process to finish execution before for good measure
    if(pid != 0){
        wait(null);
    }

    return 0;
}