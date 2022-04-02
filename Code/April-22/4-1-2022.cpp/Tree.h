#ifndef TREE_H
#define TREE_H

class Node{
public:
    Node(int val, Node *left = nullptr, Node *right = nullptr, bool root = false): value(val), left(left), right(right), root(root){}
    Node(const Node &other): value(other.value), left(new Node(*other.left)), right(new Node(*other.right)), root(root){}
    ~Node();

    static Node *deserialize(std::string serialized_node);

    inline Node *getLeft() {return this->left;}
    inline Node *getRight() {return this->right;}
    inline void setLeft(Node *new_left) {this->left = new_left;}
    inline void setRight(Node *new_right) {this->right = new_right;}
    inline int getValue() {return this->value;}
    inline bool isRoot() {return this->root;}

    std::string serialize() const;
    bool operator==(const Node& rhs);
    inline friend std::ostream& operator<<(std::ostream& out, const Node& n) {
        std::string value = n.serialize();
        out << value;
        return out;
    }

private:
    int value;
    Node *left;
    Node *right;
    bool root;
    std::string write();
};

class Tree{
public:
    Tree(Node *root):root(root){}
    Tree(const Tree &other): root(new Node(*other.root)){}
    ~Tree();

    static Tree *deserialize(std::string serialized_tree);

    inline Node *getRoot() {return this->root;}
    std::string serialize() const;
    inline bool operator==(const Tree& rhs){ return *(this->root) == *(rhs.root);}

    inline friend std::ostream& operator<<(std::ostream& out, const Tree& t) {
        std::string value = t.serialize();
        out << value;
        return out;
    }
private:
    Node *root;
    int test_value = 3;
};


#endif