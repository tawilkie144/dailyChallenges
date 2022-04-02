// Given an array of integers, return a new array such that each element at index i of
// the new array is the product of all the numbers in the original array except the one at i.

// For example, if our input was [1, 2, 3, 4, 5], the expected output would be [120, 60, 40, 30, 24].
// If our input was [3, 2, 1], the expected output would be [2, 3, 6].

// Follow-up: what if you can't use division?
#include <iostream>

//O(n) with worst case n division operations
int * multipleArray_WithDivision(int *starting_array, int size){
    int * r_array = new int[size];
    int zero_count = 0;

    int total_multiple = 1;
    for(int i = 0; i < size; i++){
        if(starting_array[i] == 0){
            zero_count++;
        }else{
            total_multiple*=starting_array[i];
        }
    }

    for(int i = 0; i < size; i++){
        if(starting_array[i] != 0){
            r_array[i] = zero_count > 0 ? 0 : total_multiple/starting_array[i];
        }else{
            r_array[i] = zero_count > 1 ? 0 : total_multiple;
        }
    }

    return r_array;
}

//O(n^2)
int * multipleArray(int *starting_array, int size){
    int * r_array = new int[size];

    for(int i = 0; i < size; i++){
        int index_multiple = 1;
        for(int j = 0; j < size; j++){
            if(j != i){
                index_multiple *= starting_array[j];
            }
        }
        r_array[i] = index_multiple;
    }

    return r_array;
}

int main(int argc, char **argv){
    int list_size;
    int *val_array, *r_array;
    if(argc > 1){
        try{
            list_size = argc-1;
            val_array = new int[list_size];
            for(int i = 1; i <= list_size; i++){
                int num = std::stoi(argv[i]);
                val_array[i-1] = num;
            }
        }catch(std::exception &e){
            std::cerr << "Invalid parameters. All arguments should be integers." <<std::endl;
            return 1;
        }
    }else{
        list_size = 5;
        val_array = new int[list_size];
        for(int i = 0; i < list_size; i++){
            val_array[i] = i+1;
        }
    }

    r_array = multipleArray_WithDivision(val_array, list_size);

    std::cout<<"orriginal list: [";
    for(int i = 0; i < list_size; i++){
        if(i != list_size-1){
            std::cout << val_array[i] << ", ";
        }else{
            std::cout <<val_array[i] << "]";
        }
    }
    std::cout<<"\nmultiple list: [";
        for(int i = 0; i < list_size; i++){
        if(i != list_size-1){
            std::cout << r_array[i] << ", ";
        }else{
            std::cout <<r_array[i] << "]" <<std::endl;
        }
    }

    if(r_array){
        delete[](r_array);
    }
    if(val_array){
        delete[](val_array);
    }


    return 0;
}