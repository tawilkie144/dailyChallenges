#include <iostream>
#include <string>

unsigned long long int factorial(int n){
    if( n == 1){
        return n;
    }else{
        return n-- * factorial(n);
    }
}

int main(int argc, char **argv){
    unsigned long long int *num_array = new unsigned long long int[20];
    unsigned long long int *check_array = new unsigned long long int[20];
    int n, index;;
    size_t size;
    if(argc > 1){
        try{
            n = std::stoi(argv[1]);
            std::cout << factorial(n) << std::endl;
            return 0;
        }catch(const std::exception& e){
            std::cerr<<e.what()<<std::endl;
        }
        
    }
    index = 0;
    for(int i = 3; i <= 18; i++){
        num_array[index] = factorial(i);
        unsigned long long int test_val = i;
        for(int j = i-1; j > 0; j--){
            test_val *= j;
        }
        check_array[index] = test_val;
        index++;
    }

    for(int i = 0; i < 16; i++){
        if(num_array[i] != check_array[i]){
            std::cout << (i + 3) << "\nfactorial(" << i + 3 << ") = " << num_array[i] << "\ncheck value = " << check_array[i] <<std::endl; 
        }
    }
    
    return 0;
}