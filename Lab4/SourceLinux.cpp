#include<unistd.h>
#include<iostream>
#include<sys/wait.h>
#include<stdlib.h>

int main(){
    
    int id;
    for (int i = 0; i < 3; i++)
    {
        //creating the child process
        id = fork();
        //only the child process will enter this block
        if (id == 0)
        {
            sleep(i+1);
            std::cout << "Process " << i + 1 << " was executed." << std::endl;
            return 0;
        //the child process ends execution here
        } else
        //when the child process isn't created
        if (id < 0)
        {
            std::cout << "The fork has failed !!!" << std::endl;
            return 0;
        }
    }
    //the parent process waits for his children to end execution
    for (int i = 0; i < 3; i++)
        wait(NULL);
    std::cout << "All processes have finished!!!";
    return 0;
}
