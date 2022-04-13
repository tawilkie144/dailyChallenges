// Given the mapping a = 1, b = 2, ... z = 26, and an encoded message, count the number of ways it can be decoded.

// For example, the message '111' would give 3, since it could be decoded as 'aaa', 'ka', and 'ak'.


///!!!!!!!!!!!!
///Not Finished
///!!!!!!!!!!!!

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <set>
#include <iterator>

#define DISPLAY 1

class Partition{
public:
    Partition(const Partition &other):partition_set_(other.partition_set_), size_(other.size_){}
    Partition(std::vector<int>partition):partition_set_(partition), size_(partition.size()){}
    Partition():size_(0){}

    std::vector<int>::iterator begin() {return this->partition_set_.begin();}
    std::vector<int>::iterator end() {return this->partition_set_.end();}

    void add(int value) {partition_set_.push_back(value); size_++;}
    int operator[](int index){return partition_set_[index];}
    size_t size() {return size_;}
    bool operator==(const Partition &other);
    bool IsMinimal();
private:
    size_t size_;
    std::vector<int>partition_set_;

};

bool Partition::operator==(const Partition &other){
    if(other.partition_set_.size() != this->partition_set_.size()) return false;
    for(int i = 0; i < other.partition_set_.size(); i++){
        if(other.partition_set_[i] != this->partition_set_[i]) return false;
    }
    return true;
}

bool Partition::IsMinimal(){
    for(int value : this->partition_set_){
        if(value > 10 && value !=20 ){
            return false;
        }
    }

    return true;
}

void GetPartitions(Partition base, )

int CountArangements(std::string encoded_message){
    int count = 0, len = encoded_message.size();
    int top_level_partition_count = 2;

    //first set, we want to generate the top level partitions, those of which have the maximum number of maximally sized tokens.
    //In the "111" example, the two partitions we create here would be {11, 1} and {1, 11}. With our mapping, we will have a
    //maximum of 2 of these top level partitions, which would be dependant on the largest size of acceptable tokens. Since 
    //26 is the largest size, with 2 digits, there can be two such lists. If we were decoding with base three numbers, our
    //largest posible token would be 222 so we would have a maximum of 3 of these partions.
    std::vector<Partition> top_level_partitions;
    std::vector<Partition> partitions;
    std::set<int> points_of_change;
    bool clear;
    int inc = 1, val, test_val;
    for(int c = 0; c < top_level_partition_count; c++){
        Partition cur_partition;
        for(int i = 0; i < len; i+=inc){
            if(i + 1 < len && (points_of_change.count(i) == 0 || encoded_message[i+1] == '0' ) && ((val = std::stoi(encoded_message.substr(i,2))) <= 26)){
                inc = 2;
                points_of_change.insert(i);
                cur_partition.add(val);
            }else{
                if(i + 2 < len && points_of_change.count(i) > 0 && encoded_message[i+1] != 0 && ((test_val = std::stoi(encoded_message.substr(i+1,2))) > 26)){
                    inc = 2;
                    val = std::stoi(encoded_message.substr(i, 2));
                    points_of_change.insert(i);
                    cur_partition.add(val);
                }else{
                    inc = 1;
                    cur_partition.add(std::stoi(encoded_message.substr(i,1)));
                }
            }
        }
        top_level_partitions.push_back(cur_partition);
    }

    //If there is only one way to make a top level partition, erase any duplicates.
    if(top_level_partitions[0] == top_level_partitions[1]){
        top_level_partitions.pop_back();
    }

    for(auto partition : top_level_partitions){
        for(int i = 0; i < partition.size(); i++){
            std::cout << partition[i] << " ";
        }
        std::cout << std::endl;
    }

    return 0;

    for(auto partition: top_level_partitions){
        partitions.push_back(partition);
        Partition new_partition = partition;
        while(!new_partition.IsMinimal()){
            Partition temp;
            for(int value : new_partition){
                if(value > 10 && value != 20){
                    std::string value_string = std::to_string(value);
                    temp.add(std::stoi(value_string.substr(0,1)));
                    temp.add(std::stoi(value_string.substr(1,1)));
                }else{
                    temp.add(value);
                }
            }
            new_partition = temp;
            partitions.push_back(new_partition);
        }
    }

    //Pairwise go throuhg all partitions and remove duplicates
    std::vector<int> to_erase;
    for(int i = 0; i < partitions.size(); i++){
        for(int j = i+1; j <partitions.size(); j++){
            if(partitions[i] == partitions[j]){
                to_erase.push_back(i);
            }
        }
    }
    for(int i = to_erase.size()-1; i >= 0;i--){
        int index = to_erase[i];
        partitions.erase(partitions.begin() + index);
    }

    #if DISPLAY
    for(auto partition : partitions){
        for(int i = 0; i < partition.size(); i++){
            std::cout << partition[i] << " ";
        }
        std::cout << std::endl;
    }
    #endif


    return partitions.size();
}

int main(int argc, char**argv){
    std::string test = "12211221";

    int count = CountArangements(test);
    std::cout << "Number of partitions of this set under described constraints: " << count <<std::endl;

    return 0;
}