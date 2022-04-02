// Given the root to a binary tree, implement serialize(root), which serializes the tree into a string,
// and deserialize(s), which deserializes the string back into the tree.

// For example, given the following Node class

// class Node:
//     def __init__(self, val, left=None, right=None):
//         self.val = val
//         self.left = left
//         self.right = right
// The following test should pass:

// node = Node('root', Node('left', Node('left.left')), Node('right'))
// assert deserialize(serialize(node)).left.left.val == 'left.left'
#include <string>
#include <iostream>
#include <vector>

#include "Tree.h"

Node::~Node(){
    if(this->left != nullptr){
        delete this->left;
    }
    if(this->right != nullptr){
        delete this->right;
    }
}

bool Node::operator==(const Node& rhs){
    bool flag = true;
    //check value;
    flag = flag && this->value == rhs.value;
    //check root;
    flag = flag && this->root == rhs.root;
    if(!flag) return flag; //short circuit as checking all children can be expensive
    //check left node;
    if((!this->left && rhs.left) || (!rhs.left && this->left)) return false;
    if(this->left && rhs.left) flag = flag && *(this->left) == *(rhs.left);
    //check right node;
    if((!this->right && rhs.right) || (!rhs.right && this->right)) return false;
    if(this->right && rhs.right) flag = flag && *(this->right) == *(rhs.right);
    return flag;
}

Tree::~Tree(){
    if(this->root != nullptr){
        delete this->root;
    }
}


Node *Node::deserialize(std::string serialized_node){
    if(serialized_node == "null"){
        return nullptr;
    }
    Node *left_node, *right_node, *r_node;
    std::string edit_string = serialized_node;
    std::vector<std::string> attributes;
    char object_delimeter_start = '{';
    char object_delimeter_end = '}';
    char attribute_delimeter = ',';
    char value_delimeter = ':';

    int object_start_pos = edit_string.find(object_delimeter_start);
    int object_end_pos = edit_string.rfind(object_delimeter_end);
    std::string node = edit_string.substr(object_start_pos, object_end_pos+1);

    int value_start = node.find("value");
    int value_end = node.substr(value_start, node.length()).find(',') + node.substr(0,value_start + 1).length() + 1;
    std::string value_attribute = node.substr(value_start, value_end - (value_start+2));
    int value = std::stoi(value_attribute.substr(value_attribute.find(':')+2));

    int left_start = node.find("left");
    int left_end = node.substr(left_start, node.length()).find(',') + node.substr(0,left_start + 1).length() + 1;
    std::string left_attribute = node.substr(left_start, left_end - (left_start+2));
    if(left_attribute.find("null") != -1){
        left_node = nullptr;
    } 
    else{
        left_node = Node::deserialize(left_attribute.substr(left_attribute.find(':')+2));
    } 

    int right_start = node.find("right");
    int right_end = node.substr(right_start, node.length()).find(',') + node.substr(0,right_start + 1).length() + 1;
    std::string right_attribute = node.substr(right_start, right_end - (right_start+2));
    if(right_attribute.find("null") != -1) {
        right_node = nullptr;
    }
    else{
        right_node = Node::deserialize(right_attribute.substr(right_attribute.find(':')+2));
    }

    int root_start = node.find("root");
    int root_end = node.substr(root_start, node.length()).find(',') + node.substr(0,root_start + 1).length() + 1;
    std::string root_attribute = node.substr(root_start, root_end - (root_start+2));
    bool root = (bool)std::stoi(root_attribute.substr(root_attribute.find(':')+2));


    r_node = new Node(value, left_node, right_node, root);

    return r_node;
}

Tree *Tree::deserialize(std::string tree){
    
    return nullptr;
}

std::string Node::serialize() const{
    std::string node_value;
    std::string r_string;
    //serializing value
    r_string.append("{ \"value\":\"").append(std::to_string(this->value)).append("\",");
    //Serializing Left node
    r_string.append("\"left\":");
    node_value = this->left == nullptr ? "null" : this->left->serialize();
    r_string.append(node_value).append(",");
    //Serializing Right node
    r_string.append("\"right\":");
    node_value = this->right == nullptr ? "null" : this->right->serialize();
    r_string.append(node_value).append(",");

    //serializing root indicator and end
    r_string.append("\"root\":\"").append(std::to_string(this->root)).append("\"}");

    return r_string;
}

std::string Tree::serialize() const{
    std::string r_string, node_value;

    r_string.append("{\"Tree\": {\"Root\":");

    node_value = this->root == nullptr ? "null" : this->root->serialize();
    r_string.append(node_value);

    r_string.append("}}");

    return r_string;
}

int main(int argc, char **argv){
    Node *node1 = new Node(1, nullptr, nullptr, true);
    Node *node2 = new Node(2);
    //Node *node3 = new Node(3);
    //Node *node4 = new Node(4);
    //Node *node5 = new Node(5);
    //Node *node6 = new Node(6);
    //Node *node7 = new Node(7);

    node1->setLeft(node2);
    //node1->setRight(node3);
    //node2->setLeft(node4);
    //node2->setRight(node5);
    //node5->setLeft(node6);
    //node6->setRight(node7);

    Node *node3 = Node::deserialize(node1->serialize());

    std::cout << *node1 <<std::endl;
    std::cout << *node3 <<std::endl;

    // Tree *tree = new Tree(node1);
    // std::string serialized_tree = tree->serialize();
    // //Tree *deserialized_tree = Tree::Deserialize(serialized_tree);

     std::cout <<(*node1 == *node3) <<std::endl;

    delete node1;
    //delete node2;
    delete node3;


    return 0;
}