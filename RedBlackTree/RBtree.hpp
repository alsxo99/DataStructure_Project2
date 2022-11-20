#include <iostream>
#include <algorithm>
#include <optional>
#include <unistd.h>

template <typename T, typename U>
class RBNode{
    
    public :
        T key;
        U value;
	RBNode<T,U> * parent;
        RBNode<T,U> * left;
        RBNode<T,U> * right;
        int color; // 1 -> red, 0 -> black

        RBNode<T,U>(const T& k, const U& v)
        {
            key = k;
            value = v;
            left = nullptr;
            right = nullptr;
            parent = nullptr;
        }

};

template <typename T, typename U>
class RBTree {
    public : 
        RBNode<T,U> * root = nullptr;
        ~RBTree() {
            removeall(root);
        }

        void insert(const T& key, const U& value);
        U search(const T& key);
        bool remove(const T& key);

        //for checking
        void preorder(RBNode<T,U>*& node){
            if(!node) return;

            std::cout<<node->key<<": "<<node->value<<std::endl;
            preorder(node->left);
            preorder(node->right);
        }
        void inorder(RBNode<T,U>*& node){
            if(!node) return;

            inorder(node->left);
            std::cout<<node->key<<": "<<node->value<<std::endl;
            inorder(node->right);
        }

    private :
        RBNode<T,U>* rotate_left(RBNode<T,U>*& node);
        RBNode<T,U>* rotate_right(RBNode<T,U>*& node);

        RBNode<T,U>* insert(RBNode<T,U>*& node, const T& key, const U& value);
        U search(RBNode<T,U>*& node, const T& key);
        RBNode<T,U>* remove(RBNode<T,U>*& node, const T& key);
        void removeall(RBNode<T,U>*& node);

};

template<typename T, typename U>
void RBTree<T,U>::insert(const T& key, const U& value) {
    root = insert(root, key, value);
}

template<typename T, typename U>
U RBTree<T,U>::search(const T& key) {
    return search(root, key);
}

template<typename T, typename U>
bool RBTree<T,U>::remove(const T& key) {
    if(!search(root,key).length()) return false;
    root = remove(root, key);
    return true;
}

template<typename T, typename U>
RBNode<T,U>* RBTree<T,U>::rotate_left(RBNode<T,U>*& node){
    //TODO    
    RBNode<T,U>* right_child = node->right;

    node->right = right_child->left;
    right_child->left = node;

    //parent update?
    node->right->parent = node;
    node->parent = right_child;

    return right_child;
}

template<typename T, typename U>
RBNode<T,U>* RBTree<T,U>::rotate_right(RBNode<T,U>*& node){
    //TODO
    RBNode<T,U>* left_child = node->left;

    node->left = left_child->right;
    left_child->right = node;

    node->left->parent = node;
    node->parent = left_child;

    return left_child;
}

template<typename T, typename U>
RBNode<T,U>* RBTree<T,U>::insert(RBNode<T,U>*& node, const T& key, const U& value) {
    //TODO
    if (!node) {
        RBNode<T,U>* newNode = new RBNode<T,U>(key, value);
        // Case 1
        // initial insertion에서는 black node를 return.
        if (root)
            newNode->color = 1; // color : red
        return newNode;
    }

    if (key < node->key) {
        node->left = insert(node->left, key, value);
        node->left->parent = node;
    }
    else if (key > node->key) {
        node->right = insert(node->right, key, value);
        node->right->parent = node;
    }
    else {
        node->value = value;
        return node;
    }

    // 현재 node가 P이다
    // Case 2
    // P is black -> do nothing
    if (!(node->color))
        return node;

    // black인 경우 위에서 걸렀기 때문에, P is red
    RBNode<T,U>* grand_parent = node->parent;
    RBNode<T,U>* sibling;

    sibling = (grand_parent->left == node) ? grand_parent->right : grand_parent->left;

    // Case 3-1 : P is red, U is red
    if (sibling && sibling->color) {
        node->color = 0;
        sibling->color = 0;
        if (grand_parent != root)
            grand_parent->color = 1;
    // Case 3-2 : P is red and U is black (or NIL)
    } else if ((sibling && !(sibling->color)) || !sibling) {
        // Case 3-2-1 
        if (grand_parent->right == node && node->left)
        {
            /* code */
        }
        
    }


}

template<typename T, typename U>
U RBTree<T,U>::search(RBNode<T,U>*& node, const T& key) {
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
RBNode<T,U>* RBTree<T,U>::remove(RBNode<T,U>*& node, const T& key) {
    //TODO

}

template<typename T, typename U>
void RBTree<T,U>::removeall(RBNode<T,U>*& node) {
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