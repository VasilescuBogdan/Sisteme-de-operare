#include <iostream>

int main(){
    
    for (int i = 1; i <= 10000; i++){
        int count = 0;
        for (int j = 2; j <= i / 2; j++){
            
            if (i % j == 0){
                count++;
            }
        }
        if (count == 0)
            std::cout << i << " ";
    }
    std::cout << std::endl;
    return 0;
}