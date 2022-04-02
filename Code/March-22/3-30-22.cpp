//Good morning! Here's your coding interview problem for today.
//
//This problem was recently asked by Google.
//
//Given a list of numbers and a number k, return whether any two numbers from the list add up to k.
//                      7   -8  -11  -18
//For example, given [10, 15,  3,   7] =  35 and k of 17, return true since 10 + 7 is 17.
//                   [ 7,  2, 14,  10] = -13
//Bonus: Can you do this in one pass?
#include <unordered_map>
#include <iostream>
#include <vector>
#include <random>
#include <cmath>

void generateWorkingList(int size, int k, std::vector<int> &outList){
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(-2*std::abs(k), 2*std::abs(k));

    for (int i=0; i<size - 1; ++i){
        outList.push_back(std::floor(dist(mt)));
    }

    std::uniform_real_distribution<double> dist2(0, size);
    int rand_index = std::floor(dist2(mt));
    int summandOne = outList.at(rand_index);
    int summandTwo = k - summandOne;
    rand_index = std::floor(dist2(mt)) - 1;
    outList.emplace(outList.begin() + rand_index, summandTwo);
}

void generateRandomList(int size, int k, std::vector<int> &outList){
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(-2*std::abs(k), 2*std::abs(k));

    for (int i=0; i<size - 1; ++i){
        outList.push_back(std::floor(dist(mt)));
    }
}

bool doesSum(int val, std::vector<int> val_list, int &summandOne, int &summandTwo){
    std::unordered_map<int, bool> hash_table;

    for(auto num : val_list){
        int summand = val - num;
        if(hash_table.find(summand) != hash_table.end()){
            summandOne = num;
            summandTwo = summand;
            return true;
        }else{
            hash_table.emplace(num, true);
        }
    }

    return false;
}


int main(int argc, char **argv){
    int list_size, k, outValOne, outValTwo;
    std::vector<int> val_list;
    if(argc > 2){
        try{
            k = std::stoi(argv[1]);
            list_size = std::stoi(argv[2]);
            generateWorkingList(list_size, k, val_list);
        }catch(std::exception &e){
            std::cerr << "Invalid parameters. Parameter one should be an integer, parameter two should be an integer" <<std::endl;
            return 1;
        }
    }else{
        k = 17;
        list_size = 4;
        val_list.push_back(10);
        val_list.push_back(15);
        val_list.push_back(3);
        val_list.push_back(7);
    }

    bool flag = doesSum(k, val_list, outValOne, outValTwo);

    if(flag){
        std::cout << "True. " << outValOne << " + " << outValTwo << " = " << k << "\nlist: [";
        for(auto it = val_list.begin(); it != val_list.end(); it++){
            std::cout << *it << (it + 1 == val_list.end() ? "]" : ", ");
        }
        std::cout <<"\nValue:" << k << std::endl;
    }else{
        std::cout << "No two number in the list sum to the value.\n" << "list: [";
        for(auto it = val_list.begin(); it != val_list.end(); it++){
            std::cout << *it << (it + 1 == val_list.end() ? "]" : ", ");
        }
        std::cout <<"\nValue:" << k << std::endl;
    }


    return 0;
}