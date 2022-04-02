//Given an array of integers, find the first missing positive integer in linear time and constant space.
//In other words, find the lowest positive integer that does not exist in the array.
//The array can contain duplicates and negative numbers as well.

// For example, the input [3, 4, -1, 1] should give 2. The input [1, 2, 0] should give 3.
// You can modify the input array in-place.
#include <vector>
#include <iostream>

#define DISPLAY 1

void swap(int *i, int *j){
    int temp = *j;
    *j = *i;
    *i = temp;
}

int smallestPositiveNumber(int *array, int size){
    #if DISPLAY==1
    std::cout << "Orriginal Array" << std::endl;
    for(int i = 0; i < size; i++){
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
    #endif

    //On the first pass, we seperate negative numbers from posative numbers.
    int *end = (array + (size-1));
    int steps = 0;
    //while the arrays below are nested, the algorithm below ensures that each index in the array is visited at most once, thus is O(n).
    for(int i = 0; i < size; i++){
        if(array[i] <= 0){
            while(*end < 0 && end != (array+i)){
                end -= 1;
                steps++;
            }
            if(end == (array + i)){
                break; //partitioning is done
            }else{
                swap((array + i), end);
            }
        }
        steps++;
    }

    //make adjustment to end if all are positive
    if(*end > 0){
        end = array + size;
    }

    #if DISPLAY==1
    std::cout << "Array after partitioning" << std::endl;
    for(int i = 0; i < size; i++){
        if((array + i) == end && *end <= 0){
            std::cout << " | ";
        }
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
    #endif

    //we can short circuit the rest of the algorithm if there are only negative numbers in the array
    if(end == array && *end <= 0){
        std::cout << "3n = " << 3*size << std::endl << "steps = " << steps << std::endl;
        return 1;
    }

    //On the second pass through, we know that if we have e.x. 4 positive numbers than we have 2 cases.
    //case 1, our smallest number not included in the array x, is such that 1<=x<=4 or, case 2 x = 5.
    //so we want to look for positive number 1, 2, 3, 4 in our array. To accomplish this, we can mark
    //the numbers in the 1th, 2nd, 3rd, and 4th index if 1, 2, 3, 4 are found respectively.
    
    int *start = array;
    while(start != end){
        int abs_start = std::abs(*start);
        if(abs_start <= (end - array)){
            *(array + (abs_start-1)) < 0 ? *(array + (abs_start-1)) = *(array + (abs_start-1)) * 1 : *(array + (abs_start-1)) = *(array + (abs_start-1)) * -1;
        }
        start++;
        steps++;
    }

    #if DISPLAY==1
    std::cout << "Array after marking" << std::endl;
    for(int i = 0; i < size; i++){
        if((array + i) == end){
            std::cout << " | ";
        }
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
    #endif

    start = array;
    int r_value = -1;
    while(start != end){
        if(*start > 0){
            r_value = (start - array) + 1;
            break;
        }
        start++;
        steps++;
    }
    if(r_value == -1){
        r_value = (end-array) +1;
    }

    #if DISPLAY
    //showing that the number of operations is O(n), and more exactly is in the worst case proportional to 3n
    std::cout << "3n = " << 3*size << std::endl << "steps = " << steps << std::endl;
    #endif

    return r_value;
}
 
int main(int argc, char **argv){
    int list_size;
    int *val_array;
    if(argc > 1){
        try{
            list_size = argc-1;
            val_array = (int *)malloc(list_size * sizeof(int));
            for(int i = 1; i <= list_size; i++){
                int num = std::stoi(argv[i]);
                val_array[i-1] = num;
            }
        }catch(std::exception &e){
            std::cerr << "Invalid parameters. All arguments should be integers." <<std::endl;
            return 1;
        }
    }else{
        list_size = 4;
        val_array = (int *)malloc(list_size * sizeof(int));
        val_array[0] = 3;
        val_array[1] = 4;
        val_array[2] = -1;
        val_array[3] = 1;
    }

    int smallest = smallestPositiveNumber(val_array, list_size);
    std::cout << "The smallest posative integer not found in the input array is: " << smallest << std::endl;

    free(val_array);

    return 0;
}