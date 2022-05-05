// Given an array of strictly the characters 'R', 'G', and 'B', segregate the values of the array so that all the Rs come first, 
// the Gs come second, and the Bs come last. You can only swap elements of the array.

// Do this in linear time and in-place.

// For example, given the array ['G', 'B', 'R', 'R', 'B', 'R', 'G'], it should become ['R', 'R', 'R', 'G', 'G', 'B', 'B'].

#include <cstdio>
#include <iostream>

void PrintArray(char *character_list, int size){
    for(int i = 0; i < size; i++){
        std::cout << i << " ";
    }
    std::cout << std::endl;
    for(int i = 0; i < size; i++){
        std::cout << character_list[i] << " ";
    }
    std::cout << std::endl;
}

void SwapValues(char *a, char *b){
    char temp = *a;
    *a = *b;
    *b = temp;    
}

void SortArray(char *character_list, int size){
    int r = 0;
    int b = size - 1;

    if(character_list[r] != 'R'){
        for(int i = 1; i < size; i++){
            if(character_list[i] == 'R'){
                SwapValues(&character_list[i], &character_list[0]);
                r = 1;
                break;
            }
        }
    }

    if(character_list[b] != 'B'){
        for(int i = 1; i < size - 1; i++){
            if(character_list[i] == 'B'){
                SwapValues(&character_list[i], &character_list[size-1]);
                b -= 1;
                break;
            }
        }
    }

    while(character_list[r] == 'R'){
            if(r==size-1) return;
            r++;
    }
    while(character_list[b] == 'B'){
            if(b == 0) return;
            b--;
    }
    

    for(int i = b; i >= r; i--){
        if(character_list[i] == 'R'){
            SwapValues(&character_list[i], &character_list[r]);
            while(character_list[r] == 'R' && r <= b){
                r++;
            }
        }
    }
    for(int i = r; i <= b; i++){
        if(character_list[i] == 'B'){
            SwapValues(&character_list[i], &character_list[b]);
            while(character_list[b] == 'B' && b >= r){
                b--;
            }
        }
    }
}

int main(int argc, char **argv){
    int list_size;
    char *val_array;
    if(argc > 1){
        list_size = argc-1;
        val_array = new char[list_size];
        for(int i = 1; i <= list_size; i++){
            if((int)*argv[i] != 103 && (int)*argv[i] != 71 && (int)*argv[i] != 66 && (int)*argv[i] != 98 && (int)*argv[i] != 82 && (int)*argv[i] != 114){
                std::cout << "Invalid input. Valid inputs are: G, B, R. Quitting" << std::endl;
                exit(1);
            }
            val_array[i-1] = std::toupper((int)*argv[i]);
        }
    }else{
        list_size = 7;
        val_array = new char[list_size];
        val_array[0] = 'G';
        val_array[1] = 'B';
        val_array[2] = 'R';
        val_array[3] = 'R';
        val_array[4] = 'B';
        val_array[5] = 'R';
        val_array[6] = 'G';
    }

    std::cout << "Initial List:" << std::endl;
    PrintArray(val_array,list_size);

    SortArray(val_array, list_size);

    std::cout << "Sored List:" << std::endl;
    PrintArray(val_array, list_size);

    return 0;
}