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

        void fix_insert(RBNode<T,U>*& node);
        void fix_remove(RBNode<T,U>*& node);
};

template<typename T, typename U>
void RBTree<T,U>::insert(const T& key, const U& value) {
    RBNode<T,U>* node = insert(root, key, value);
    // 위의 insert하고 나면 root에 new node가, node에 original root이 저장되어 있는 상황.

    // value만 replace한 경우
    if (!root->parent)
        return;

    RBNode<T,U>* temp = root;
    // shallow copy
    root = node;
    node = temp;

    fix_insert(node);
}

template<typename T, typename U>
U RBTree<T,U>::search(const T& key) {
    return search(root, key);
}

template<typename T, typename U>
bool RBTree<T,U>::remove(const T& key) {
    if(!search(root,key).length()) return false;

    RBNode<T,U>* node = remove(root, key);
    // remove할 node를 받은 상태

    fix_remove(node);
    return true;
}

template<typename T, typename U>
RBNode<T,U>* RBTree<T,U>::rotate_left(RBNode<T,U>*& node){
    //TODO    
    RBNode<T,U>* right_child = node->right;

    node->right = right_child->left;
    right_child->left = node;

    //parent update?
    if (node->right)
        node->right->parent = node;

    if (node->parent) {
        if (node->parent->left == node)
            node->parent->left = right_child;
        else
            node->parent->right = right_child;

        right_child->parent = node->parent;
    } else {
        right_child->parent = nullptr;
        root = right_child;
    }

    node->parent = right_child;

    return right_child;
}

template<typename T, typename U>
RBNode<T,U>* RBTree<T,U>::rotate_right(RBNode<T,U>*& node){
    //TODO
    RBNode<T,U>* left_child = node->left;

    node->left = left_child->right;
    left_child->right = node;

    if (node->left)
        node->left->parent = node;

    if (node->parent) {
        if (node->parent->left == node)
            node->parent->left = left_child;
        else
            node->parent->right = left_child;
        
        left_child->parent = node->parent;
    } else {
        left_child->parent = nullptr;
        root = left_child;
    }

    node->parent = left_child;

    return left_child;
}

template<typename T, typename U>
RBNode<T,U>* RBTree<T,U>::insert(RBNode<T,U>*& node, const T& key, const U& value) {
    //TODO
    if (!node) {
        RBNode<T,U>* newNode = new RBNode<T,U>(key, value);
        if (root)
            newNode->color = 1; // color : red
        root = newNode;
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
    else
        node->value = value;

    return node;
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

    // remove할 node를 찾는 함수
    // 해당 key가 존재할때만 이 함수를 call하므로 바로 아래의 code는 사실 기능하지 않는다.
    if (!node)
        return node;
    
    if (key < node->key)
        return remove(node->left, key);
    else if (key > node->key)
        return remove(node->right, key);
    else
        return node;
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

template<typename T, typename U>
void RBTree<T,U>::fix_insert(RBNode<T,U>*& node) {
    // 현재 node는 새로 insert한 newNode

    while (node->parent) {
        RBNode<T,U>* parent = node->parent;
        
        // Case 2
        // P is black -> do nothing
        if (!(parent->color))
            return;

        // black인 경우 위에서 걸렀기 때문에, P is red
        RBNode<T,U>* grand_parent = node->parent->parent;
        RBNode<T,U>* sibling;

        sibling = (grand_parent->left == parent) ? grand_parent->right : grand_parent->left;

        // Case 3-1 : P is red, U is red
        if (sibling && sibling->color) {
            parent->color = 0;
            sibling->color = 0;
            if (grand_parent != root)
                grand_parent->color = 1;

            node = grand_parent;
        }
        // Case 3-2 : P is red and U is black (or NIL)
        else if ((sibling && !(sibling->color)) || !sibling) {
            // Case 3-2-1 : right-right, left-left
            if (grand_parent->right == parent && parent->right == node) {
                grand_parent->color = 1;
                parent->color = 0;
                rotate_left(grand_parent);
            } else if (grand_parent->left == parent && parent->left == node) {
                grand_parent->color = 1;
                parent->color = 0;
                rotate_right(grand_parent);
            }
            // Case 3-2-2 : right-left, left-right
            else if (grand_parent->right == parent && parent->left == node) {
                rotate_right(parent); // 확인 필요
                grand_parent->color = 1;
                node->color = 0;
                rotate_left(grand_parent);
            }
            else if (grand_parent->left == parent && parent->right == node) {
                rotate_left(parent); // 확인 필요
                grand_parent->color = 1;
                node->color = 0;
                rotate_right(grand_parent);  
            }

            return;
        }
    }
}

template<typename T, typename U>
void RBTree<T,U>::fix_remove(RBNode<T,U>*& node) {

    // node가 red leaf node일 경우.
    if (node->color && !node->left && !node->right) {
        if (node->parent->left == node)
            node->parent->left = nullptr;
        else
            node->parent->right = nullptr;
        delete node;
    // node가 one child를 갖고 있는 경우, node : black, child : red 인 경우 뿐이다.
    } else if ((node->left && !node->right) || (!node->left && node->right)) {        
        RBNode<T,U>* temp = node->left ? node->left : node->right;
        // copy contents
        *node = *temp;

        delete temp;
    }
        
}