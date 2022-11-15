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

template<typename T, typename U>
AVLNode<T,U>* AVLTree<T,U>::rotate_left(AVLNode<T,U>*& node){
    //TODO
    //target node의 parent node 정보도 바꿔야하지 않나?
    //target node의 parent node가 없을 경우, node->right이 새로운 root가 되어야한다.
    AVLNode<T,U> * right_child = node->right;
    node->right = right_child->left;
    if (root == node)
        root = right_child;
    right_child->left = node;

    // update height
    node->height = max(node->left->height, node->right->height) + 1;
    right_child->height = max(right_child->left->height, right_child->right->height) + 1

    return right_child;
    //delete 해야하나?

}

template<typename T, typename U>
AVLNode<T,U>* AVLTree<T,U>::rotate_right(AVLNode<T,U>*& node){
    //TODO
    AVLNode<T,U> * left_child = node->left;
    node->left = left_child->right;
    if (root == node)
        root = left_child;
    left_child->right = node;

    // update height
    node->height = max(node->left->height, node->right->height) + 1;
    left_child->height = max(left_child->left->height, left_child->right->height) + 1;

    return left_child;
}

template<typename T, typename U>
AVLNode<T,U>* AVLTree<T,U>::insert(AVLNode<T,U>*& node, const T& key, const U& value) {
    //TODO
    //먼저, insert 할 position을 찾아야한다.
    // 새로운 key가 현재 node의 key보다 작을 경우,
    if (key < node.key) {
        // insert 할 수 있는 position이 아니면 left child에서 다시 insert를 call.
        // node의 left child가 존재한다면, 
        if (node->left)
        {
            return insert(node->left, key, value);
            // return ? 안해주면 문제가 생길 것 같다.
            // 그럼 뭘 return 해주냐..
        // leaf node이면 left child로 insert.
        } else {
            AVLNode<T,U> * newNode(key, value);
            node->left = newNode;
            node->height += 1;
        }
    // 새로운 key가 현재 node의 key보다 클 경우,
    } else if (key > node.key) {
        // node의 right child가 존재한다면,
        if (node->right)
        {
            return insert(node->right, key, value);
        } else {
            AVLNode<T,U> * newNode(key, value);
            node->right = newNode;
            node->height += 1;
        }
    // key가 현재 node의 key와 일치할 경우, value만 replace 한다.
    } else {
        node->value = value;
        return root;
    }

    // 여기까지 insert 완료. 이제 balance check이 필요하다.

    
    
    
    //right-left

    //right-right
    
    //left-right
   
    //right-left
}

template<typename T, typename U>
U AVLTree<T,U>::search(AVLNode<T,U>*& node, const T& key) {
    //TODO
    //return NULL if there are no such key, return value if there is

    // 현재 node의 key보다 작은 경우,
    if (key < node->key) {
        // node의 left child가 존재하면, left child에서 search를 call.
        if (node->left)
        {
            return search(node->left, key);
        // node의 left child가 존재하지 않으면, 해당 key는 존재하지 않는 것이다.
        } else {
            // return ""
            return NULL;
        }
    } else if (key > node->key) {
        if (node->right)
        {
            return search(node->right, key);
        } else {
            return NULL;
        }
    // key가 현재 node의 key와 일치하는 경우,
    } else {
        return node->value;
    }
    
}

template<typename T, typename U>
AVLNode<T,U>* AVLTree<T,U>::remove(AVLNode<T,U>*& node, const T& key) {
    //TODO
}

template<typename T, typename U>
void AVLTree<T,U>::removeall(AVLNode<T,U>*& node) {
    //TODO
    //for destructor
        
}
