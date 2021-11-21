#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(){

    int p1[2], p2[2];
    if(pipe(p1) == -1){
        std::cout << "Error pipe!!!" << std::endl;
        return 1;
    }

    if(pipe(p2) == -1){
        std::cout << "Error pipe!!!" << std::endl;
        return 1;
    }

    for(int i = 0; i < 10; i++){
        int idp = fork();
        if(idp == -1){
            std::cout << "Error creating process!!!" << std::endl;
            return 2;
        }else if(idp == 0){
            int finish = 0, n, N;
            read(p2[0], &n, sizeof(int));
            read(p2[0], &N, sizeof(int));
            for(int j = n; j < N; j++){
                int count = 0;
                for(int k = 2; k <= j / 2; k++){
                    if(j % k == 0){
                        count++;
                    }
                }
                if(count == 0){
                    write(p1[1], &j, sizeof(int));
                }
            }
            write(p1[1], &finish, sizeof(int));
            return 0;
        }else{
            int n = 1 + (i * 1000);
            int N = (i + 1) * 1000;
            write(p2[1], &n, sizeof(int));
            write(p2[1], &N, sizeof(int));
        }
    }

    int value;
    for(int i = 0; i < 10; i++){
        do
        {
            read(p1[0], &value, sizeof(int));
            if(value == 0){
                break;
            } else {
                std::cout << value << " ";
            }
        } while (true);
    }

    for(int i = 0; i < 10; i++){
        wait(NULL);
    }

    return 0;
}