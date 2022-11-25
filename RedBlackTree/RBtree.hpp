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

        RBNode<T,U>* inserted_node(RBNode<T,U>*& node, const T& key);
        void fix_insert(RBNode<T,U>*& node);
        void fix_remove(RBNode<T,U>*& node);
        RBNode<T,U>* find_successor(RBNode<T,U>*& node);
        void handle_double_black(RBNode<T,U>*& node);
};

template<typename T, typename U>
void RBTree<T,U>::insert(const T& key, const U& value) {
    root = insert(root, key, value);

    RBNode<T,U>* newNode = inserted_node(root, key);

    fix_insert(newNode);
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
            newNode->color = 1;
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
    // 해당 key가 존재할때만 이 함수를 call 하므로 예외 경우는 없다.
    
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
    
    delete node;
    return;
}

template<typename T, typename U>
RBNode<T,U>* RBTree<T,U>::inserted_node(RBNode<T,U>*& node, const T& key) {
    
    // 현재 node의 key보다 작은 경우,
    if (key < node->key)
        return inserted_node(node->left, key);
    // 현재 node의 key보다 큰 경우,
    else if (key > node->key)
        return inserted_node(node->right, key);
    // key가 현재 node의 key와 일치하는 경우,
    else
        return node;
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
        RBNode<T,U>* uncle;

        uncle = (grand_parent->left == parent) ? grand_parent->right : grand_parent->left;

        // Case 3-1 : P is red, U is red
        if (uncle && uncle->color) {
            parent->color = 0;
            uncle->color = 0;
            if (grand_parent != root)
                grand_parent->color = 1;

            node = grand_parent;
        }
        // Case 3-2 : P is red and U is black (or NIL)
        else if ((uncle && !(uncle->color)) || !uncle) {
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

    // node가 leaf node(no child)이면 두 가지 경우가 있다.
    // node가 black leaf node일 경우. -> double black
    if (!node->color && !node->left && !node->right)
        handle_double_black(node);
    // node가 red leaf node일 경우.
    else if (node->color && !node->left && !node->right) {
        if (node->parent->left == node)
            node->parent->left = nullptr;
        else
            node->parent->right = nullptr;
        delete node;
    // node가 one child를 갖고 있는 경우, node : black, child : red 인 경우 뿐이다.
    } else if ((node->left && !node->right) || (!node->left && node->right)) {        
        RBNode<T,U>* child = node->left ? node->left : node->right;
        // copy contents
        node->key = child->key;
        node->value = child->value;

        if (node->left == child)
            node->left = nullptr;
        else
            node->right = nullptr;

        delete child;
    // node가 two children을 갖고 있는 경우
    } else if (node->left && node->right) {
        RBNode<T,U>* successor = find_successor(node->right);
        // successor이 red leaf node 인 경우, 
        if (successor->color && (!successor->left && !successor->right)){
            node->key = successor->key;
            node->value = successor->value;

            if (successor->parent->left == successor)
                successor->parent->left = nullptr;
            else
                successor->parent->right = nullptr;
            
            delete successor;
        // successor이 one child를 가진 black node,
        // child가 red leaf node인 경우. child는 successor의 right child일 수 밖에 없다.
        } else if (!successor->color && (!successor->left && successor->right)) {
            node->key = successor->key;
            node->value = successor->value;

            RBNode<T,U>* successor_child = successor->right;

            successor->key = successor_child->key;
            successor->value = successor_child->value;
            successor->right = nullptr;

            delete successor_child;
        // successor이 black leaf node인 경우, -> double black
        } else if (!successor->color && (!successor->left && !successor->right)) {
            node->key = successor->key;
            node->value = successor->value;
            handle_double_black(successor);
        }
    }

    return;
}

template<typename T, typename U>
RBNode<T,U>* RBTree<T,U>::find_successor(RBNode<T,U>*& node) {

    RBNode<T,U>* current = node;

    while (current->left)
        current = current->left;
    
    return current;
}

template<typename T, typename U>
void RBTree<T,U>::handle_double_black(RBNode<T,U>*& node) {

    RBNode<T,U>* sibling = node->parent->left == node ? node->parent->right : node->parent->left;

    if (!sibling->color) {
        // case 1
        if (sibling == node->parent->right && sibling->right && sibling->right->color) {
            sibling->color = node->parent->color;
            node->parent->color = 0;
            sibling->right->color = 0;
            rotate_left(node->parent);

            node->parent->left = nullptr;
            delete node;
        } else if (sibling == node->parent->left && sibling->left && sibling->left->color) {
            sibling->color = node->parent->color;
            node->parent->color = 0;
            sibling->left = 0;
            rotate_right(node->parent);

            node->parent->right = nullptr;
            delete node;
        // case 2
        } else if (sibling == node->parent->right && sibling->left && sibling->left->color) {
            sibling->color = 1;
            sibling->left->color = 0;
            rotate_right(sibling);
            sibling->parent->color = node->parent->color;
            node->parent->color = 0;
            sibling->color = 0;
            rotate_left(node->parent);

            node->parent->left = nullptr;
            delete node;
        } else if (sibling == node->parent->left && sibling->right && sibling->right->color) {
            sibling->color = 1;
            sibling->right->color = 0;
            rotate_left(sibling);
            sibling->parent->color = node->parent->color;
            node->parent->color = 0;
            sibling->color = 0;
            rotate_right(node->parent);

            node->parent->right = nullptr;
            delete node;
        // case 3
        } else {
            sibling->color = 1;
            if (sibling == node->parent->left)
                node->parent->right = nullptr;
            else
                node->parent->left = nullptr;

            if (node->parent->color)
                node->parent->color = 0;
            else {
                // 이게 필요한지 모르겠다.
                if (node->parent == root)
                    node->parent->color = 0;
                else
                    handle_double_black(node->parent);
            }
            delete node;
        }
    } else {
        // case 4
        sibling->color = 0;
        node->parent->color = 1;

        if (sibling == node->parent->right)
            rotate_left(node->parent);
        else
            rotate_right(node->parent);

        if (sibling == node->parent->left)
            node->parent->right = nullptr;
        else
            node->parent->left = nullptr;
        delete node;
    }
    
    return;
}