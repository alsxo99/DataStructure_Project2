#include <iostream>
#include <algorithm>
#include <optional>
#include <unistd.h>

template <typename T, typename U>
class AVLNode{
    
    public :
        T key;
        U value;
        AVLNode<T,U> * left;
        AVLNode<T,U> * right;
        int height;

        AVLNode<T,U>(const T& k, const U& v)
        {
            key = k;
            value = v;
            left = nullptr;
            right = nullptr;
            height = 1;
        }        
        
};

template <typename T, typename U>
class AVLTree {
    public : 
        AVLNode<T,U> * root = nullptr;
        ~AVLTree() {
            removeall(root);
        }

        void insert(const T& key, const U& value);
        U search(const T& key);
        bool remove(const T& key);

        //for checking
        void preorder(AVLNode<T,U>*& node){
            if(!node) return;

            std::cout<<node->key<<": "<<node->value<<std::endl;
            preorder(node->left);
            preorder(node->right);
        }
        void inorder(AVLNode<T,U>*& node){
            if(!node) return;

            inorder(node->left);
            std::cout<<node->key<<": "<<node->value<<std::endl;
            inorder(node->right);
        }

    private :
        int getHeight(AVLNode<T,U>*& node);
        int getBalance(AVLNode<T,U>*& node);
        AVLNode<T,U>* rotate_left(AVLNode<T,U>*& node);
        AVLNode<T,U>* rotate_right(AVLNode<T,U>*& node);
        AVLNode<T,U>* min_value_node(AVLNode<T,U>*& node);

        AVLNode<T,U>* insert(AVLNode<T,U>*& node, const T& key, const U& value);
        U search(AVLNode<T,U>*& node, const T& key);
        AVLNode<T,U>* remove(AVLNode<T,U>*& node, const T& key);
        void removeall(AVLNode<T,U>*& node);

};

template <typename T, typename U>
int AVLTree<T,U>::getHeight(AVLNode<T,U>*& node){
    if(!node) return 0;
    return node->height;
}

template <typename T, typename U>
int AVLTree<T,U>::getBalance(AVLNode<T,U>*& node){
    if(!node) return 0;
    return getHeight(node->left) - getHeight(node->right);
}

template<typename T, typename U>
void AVLTree<T,U>::insert(const T& key, const U& value) {
    root = insert(root, key, value);
}

template<typename T, typename U>
U AVLTree<T,U>::search(const T& key) {
    return search(root, key);
}

template<typename T, typename U>
bool AVLTree<T,U>::remove(const T& key) {
    if(!search(root,key).length()) return false;
    root = remove(root, key);
    return true;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

template<typename T, typename U>
AVLNode<T,U>* AVLTree<T,U>::rotate_left(AVLNode<T,U>*& node){
    //TODO
    AVLNode<T,U> * right_child = node->right;
    
    node->right = right_child->left;
    right_child->left = node;

    // update height
    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
    right_child->height = max(getHeight(right_child->left), getHeight(right_child->right)) + 1;
    
    return right_child;
}

template<typename T, typename U>
AVLNode<T,U>* AVLTree<T,U>::rotate_right(AVLNode<T,U>*& node){
    //TODO
    AVLNode<T,U> * left_child = node->left;
    
    node->left = left_child->right;
    left_child->right = node;

    // update height
    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
    left_child->height = max(getHeight(left_child->left), getHeight(left_child->right)) + 1;

    return left_child;
}

template<typename T, typename U>
AVLNode<T,U>* AVLTree<T,U>::min_value_node(AVLNode<T,U>*& node) {
    
    AVLNode<T,U>* current = node;

    while (current->left)
        current = current->left;
    
    return current;
}

template<typename T, typename U>
AVLNode<T,U>* AVLTree<T,U>::insert(AVLNode<T,U>*& node, const T& key, const U& value) {
    //TODO
    // Perform insertion recursively
    if (!node)
        return new AVLNode<T,U>(key, value);
    if (key < node->key)
        node->left = insert(node->left, key, value);
    else if (key > node->key)
        node->right = insert(node->right, key, value);
    // key가 현재 node의 key와 일치할 경우, value만 replace 한다.
    else {
        node->value = value;
        return node;
    }

    // update height of this ancestor nodes
    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;

    // balance check of this ancestor nodes
    int balance = getBalance(node);
    
    //left-left
    if (balance > 1 && key < node->left->key)
        return rotate_right(node);
    //right-right
    if (balance < -1 && key > node->right->key)
        return rotate_left(node);
    //left-right
    if (balance > 1 && key > node->left->key) {
        node->left = rotate_left(node->left);
        return rotate_right(node);
    }
    //right-left
    if (balance < -1 && key < node->right->key) {
        node->right = rotate_right(node->right);
        return rotate_left(node);
    }

    return node;
}

template<typename T, typename U>
U AVLTree<T,U>::search(AVLNode<T,U>*& node, const T& key) {
    //TODO
    //return NULL if there are no such key, return value if there is

    if (!node)
        return "";
    // 현재 node의 key보다 작은 경우,
    if (key < node->key)
        return search(node->left, key);
    // 현재 node의 key보다 큰 경우,
    else if (key > node->key)
        return search(node->right, key);
    // key가 현재 node의 key와 일치하는 경우,
    else
        return node->value;
}

template<typename T, typename U>
AVLNode<T,U>* AVLTree<T,U>::remove(AVLNode<T,U>*& node, const T& key) {
    //TODO
    if (!node)
        return node;
    
    if (key < node->key)
        node->left = remove(node->left, key);
    else if (key > node->key)
        node->right = remove(node->right, key);
    
    // remove할 node의 key와 일치.
    else {
        // node with one or no child
        if (!node->left || !node->right)
        {
            AVLNode<T,U>* temp = node->left ? node->left : node->right;

            // no child
            if (!temp) {
                // shallow copy
                temp = node;
                node = nullptr;
            }
            // one child
            else
                // copy contents, except address
                *node = *temp;
            
            delete temp;
        // node with two children
        } else {
            AVLNode<T,U>* temp = min_value_node(node->right);

            node->key = temp->key;
            node->value = temp->value;

            node->right = remove(node->right, temp->key);
        }
    }

    if (!node)
        return node;

    // update height
    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;

    // balance check
    int balance = getBalance(node);

    // left-left
    if (balance > 1 && getBalance(node->left) >= 0)
        return rotate_right(node);
    // right-right
    if (balance < -1 && getBalance(node->right) <= 0)
        return rotate_left(node);
    // left-right
    if (balance > 1 && getBalance(node->left) < 0) {
        node->left = rotate_left(node->left);
        return rotate_right(node);
    }
    // right-left
    if (balance < -1 && getBalance(node->right) > 0) {
        node->right = rotate_right(node->right);
        return rotate_left(node);
    }

    return node;
}

template<typename T, typename U>
void AVLTree<T,U>::removeall(AVLNode<T,U>*& node) {
    //TODO
    //for destructor
    if (node->left)
        removeall(node->left);
    if (node->right)
        removeall(node->right);
    
    std::cout << "delete " << node->key << std::endl;
    delete node;
    return;
}
