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
        RBNode<T,U>* remove_black_leaf(RBNode<T,U>*& node);
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
    // remove??? node??? ?????? ??????

    fix_remove(node);
    return true;
}

template<typename T, typename U>
RBNode<T,U>* RBTree<T,U>::rotate_left(RBNode<T,U>*& node){
    //TODO    
    RBNode<T,U>* right_child = node->right;

    node->right = right_child->left;
    right_child->left = node;

    //parent update
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
        else
            newNode->color = 0;
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
    // ?????? node??? key?????? ?????? ??????,
    if (key < node->key)
        return search(node->left, key);
    // ?????? node??? key?????? ??? ??????,
    else if (key > node->key)
        return search(node->right, key);
    // key??? ?????? node??? key??? ???????????? ??????,
    else
        return node->value;
}

template<typename T, typename U>
RBNode<T,U>* RBTree<T,U>::remove(RBNode<T,U>*& node, const T& key) {
    //TODO
    // remove??? node??? ?????? ??????
    // ?????? key??? ??????????????? ??? ????????? call ????????? ?????? ????????? ??????.
    
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
    
    // ?????? node??? key?????? ?????? ??????,
    if (key < node->key)
        return inserted_node(node->left, key);
    // ?????? node??? key?????? ??? ??????,
    else if (key > node->key)
        return inserted_node(node->right, key);
    // key??? ?????? node??? key??? ???????????? ??????,
    else
        return node;
}

template<typename T, typename U>
void RBTree<T,U>::fix_insert(RBNode<T,U>*& node) {
    // ?????? node??? ?????? insert??? newNode

    while (node->parent) {
        RBNode<T,U>* parent = node->parent;
        
        // Case 2
        // P is black -> do nothing
        if (!(parent->color))
            return;

        // black??? ?????? ????????? ????????? ?????????, P is red
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
                rotate_right(parent); 
                grand_parent->color = 1;
                node->color = 0;
                rotate_left(grand_parent);
            }
            else if (grand_parent->left == parent && parent->right == node) {
                rotate_left(parent); 
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

    if (node == root && !node->left && !node->right) {
        root = nullptr;
        delete node;
    }
    // node??? leaf node(no child)?????? ??? ?????? ????????? ??????.
    // node??? black leaf node??? ??????. -> double black
    else if (!node->color && !node->left && !node->right) {
        node = remove_black_leaf(node);

        if (node->parent->left == node)
            node->parent->left = nullptr;
        else
            node->parent->right = nullptr;
        delete node;
    }
    // node??? red leaf node??? ??????.
    else if (node->color && !node->left && !node->right) {
        if (node->parent->left == node)
            node->parent->left = nullptr;
        else
            node->parent->right = nullptr;
        delete node;
    // node??? one child??? ?????? ?????? ??????, node : black, child : red ??? ?????? ?????????.
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
    // node??? two children??? ?????? ?????? ??????
    } else if (node->left && node->right) {
        RBNode<T,U>* successor = find_successor(node->right);
        // successor??? red leaf node ??? ??????, 
        if (successor->color && (!successor->left && !successor->right)){
            node->key = successor->key;
            node->value = successor->value;

            if (successor->parent->left == successor)
                successor->parent->left = nullptr;
            else
                successor->parent->right = nullptr;
            
            delete successor;
        // successor??? one child??? ?????? black node,
        // child??? red leaf node??? ??????. child??? successor??? right child??? ??? ?????? ??????.
        } else if (!successor->color && (!successor->left && successor->right)) {
            node->key = successor->key;
            node->value = successor->value;

            RBNode<T,U>* successor_child = successor->right;

            successor->key = successor_child->key;
            successor->value = successor_child->value;
            successor->right = nullptr;

            delete successor_child;
        // successor??? black leaf node??? ??????, -> double black
        } else if (!successor->color && (!successor->left && !successor->right)) {
            node->key = successor->key;
            node->value = successor->value;
            successor = remove_black_leaf(successor);

            if (successor->parent->left == successor)
                successor->parent->left = nullptr;
            else
                successor->parent->right = nullptr;
            delete successor;
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
RBNode<T,U>* RBTree<T,U>::remove_black_leaf(RBNode<T,U>*& node) {

    RBNode<T,U>* sibling = node->parent->left == node ? node->parent->right : node->parent->left;

    if (!sibling->color) {
        // case 1
        if (sibling == node->parent->right && sibling->right && sibling->right->color) {
            sibling->color = node->parent->color;
            node->parent->color = 0;
            sibling->right->color = 0;
            rotate_left(node->parent);

        } else if (sibling == node->parent->left && sibling->left && sibling->left->color) {
            sibling->color = node->parent->color;
            node->parent->color = 0;
            sibling->left = 0;
            rotate_right(node->parent);

        // case 2
        } else if (sibling == node->parent->right && sibling->left && sibling->left->color) {
            sibling->color = 1;
            sibling->left->color = 0;
            rotate_right(sibling);
            sibling->parent->color = node->parent->color;
            node->parent->color = 0;
            sibling->color = 0;
            rotate_left(node->parent);

        } else if (sibling == node->parent->left && sibling->right && sibling->right->color) {
            sibling->color = 1;
            sibling->right->color = 0;
            rotate_left(sibling);
            sibling->parent->color = node->parent->color;
            node->parent->color = 0;
            sibling->color = 0;
            rotate_right(node->parent);

        // case 3
        } else {
            sibling->color = 1;

            if (node->parent->color)
                node->parent->color = 0;
            else {
                if (node->parent == root)
                    node->parent->color = 0;
                else
                    remove_black_leaf(node->parent);
            }
        }
    } else {
        // case 4
        sibling->color = 0;
        node->parent->color = 1;

        if (sibling == node->parent->right)
            rotate_left(node->parent);
        else
            rotate_right(node->parent);

    }
    
    return node;
}