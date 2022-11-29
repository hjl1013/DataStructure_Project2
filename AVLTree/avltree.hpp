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
    AVLNode<T,U>* org_node = node;
    AVLNode<T,U>* org_right = node->right;
    AVLNode<T,U>* org_right_left = node->right->left;

    // change structure
    node = org_right;
    node->left = org_node;
    node->left->right = org_right_left;

    // update heights
    node->left->height = (getHeight(node->left->left)> getHeight(node->left->right))? getHeight(node->left->left)+1: getHeight(node->left->right)+1;
    node->height = (getHeight(node->left)> getHeight(node->right))? getHeight(node->left)+1: getHeight(node->right)+1;

    return node;
}

template<typename T, typename U>
AVLNode<T,U>* AVLTree<T,U>::rotate_right(AVLNode<T,U>*& node){
    //TODO
    AVLNode<T,U>* org_node = node;
    AVLNode<T,U>* org_left = node->left;
    AVLNode<T,U>* org_left_right = node->left->right;

    // change structure
    node = org_left;
    node->right = org_node;
    node->right->left = org_left_right;

    // update heights
    node->right->height = (getHeight(node->right->left) > getHeight(node->right->right))? getHeight(node->right->left)+1: getHeight(node->right->right)+1;
    node->height = (getHeight(node->left)> getHeight(node->right))? getHeight(node->left)+1: getHeight(node->right)+1;

    return node;
}

template<typename T, typename U>
AVLNode<T,U>* AVLTree<T,U>::insert(AVLNode<T,U>*& node, const T& key, const U& value) {
    //TODO
    //End case
    if (!node) {
        return new AVLNode<T, U>(key, value);
    }

    //insert recursively
    if (key > node->key){
        node->right = insert(node->right, key, value);
    }
    else if (key < node->key){
        node->left = insert(node->left, key, value);
    }
    else {
        node->value = value;
        return node;
    }

    //update height
    node->height = (getHeight(node->left) > getHeight(node->right))? getHeight(node->left) + 1: getHeight(node->right) + 1;

    //reorganize structure
    //right-left
    if (key > node->key && key < node->right->key && getHeight(node->right) - getHeight(node->left) > 1) {
        node->right = rotate_right(node->right);
        node = rotate_left(node);
    }

    //right-right
    if (key > node->key && key > node->right->key && getHeight(node->right) - getHeight(node->left) > 1) {
        node = rotate_left(node); //this updates height automatically
    }

    //left-right
    if (key < node->key && key > node->left->key && getHeight(node->left) - getHeight(node->right) > 1) {
        node->left = rotate_left(node->left);
        node = rotate_right(node);
    }
   
    //left-left
    if (key < node->key && key < node->left->key && getHeight(node->left) - getHeight(node->right) > 1) {
        node = rotate_right(node); //this updates height automatically
    }

    return node;
}

template<typename T, typename U>
U AVLTree<T,U>::search(AVLNode<T,U>*& node, const T& key) {
    //TODO
    //return NULL if there are no such key, return value if there is
    if (!node) {
        return "";
    }

    if (key < node->key){
        return search(node->left, key);
    }
    else if (key > node->key){
        return search(node->right, key);
    }
    else {
        return node->value;
    }
}

template<typename T, typename U>
AVLNode<T,U>* AVLTree<T,U>::remove(AVLNode<T,U>*& node, const T& key) {
    //end case
    if (key == node->key) {
        if (!node->left){
            AVLNode<T,U> *org_right = node->right;
            delete node;
            node = nullptr;
            return org_right;
        }
        else if(!node->right) {
            AVLNode<T,U> *org_left = node->left;
            delete node;
            node = nullptr;
            return org_left;
        }
        else {
            AVLNode<T, U> *replace = node->right;
            while (replace->left) {
                replace = replace->left;
            }
            node->key = replace->key;
            node->value = replace->value;
            node->right = remove(node->right, replace->key);
        }
    }
    // remove recursively
    else if (key < node->key){
        node->left = remove(node->left, key);
    }
    else {
        node->right = remove(node->right, key);
    }

    // update height
    node->height = (getHeight(node->left) > getHeight(node->right))? getHeight(node->left)+1: getHeight(node->right)+1;

    // change structure if unbalanced
    if (getHeight(node->right) - getHeight(node->left) > 1) {
        if (getHeight(node->right->right) >= getHeight(node->right->left)){
            node = rotate_left(node);
        }
        else {
            node->right = rotate_right(node->right);
            node = rotate_left(node);
        }
    }
    else if(getHeight(node->left) - getHeight(node->right) > 1) {
        if (getHeight(node->left->left) >= getHeight(node->left->right)){
            node = rotate_right(node);
        }
        else {
            node->left = rotate_left(node->left);
            node = rotate_right(node);
        }
    }

    return node;
}

template<typename T, typename U>
void AVLTree<T,U>::removeall(AVLNode<T,U>*& node) {
    //TODO
    //for destructor
    if (!node) {
        return;
    }

    // remove recursively
    removeall(node->left);
    removeall(node->right);
    delete node;
    node = nullptr;
}
