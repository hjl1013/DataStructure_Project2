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
    AVLNode<T,U>*& org_node = node;
    AVLNode<T,U>*& org_right = node->right;
    AVLNode<T,U>*& org_right_left = node->right->left;

    // change structure
    node = org_right;
    node->left = org_node;
    node->left->right = org_right_left;

    // update heights
    node->left->height = (node->left->left->height>node->left->right->height)? node->left->left->height+1: node->left->right->height+1;
    node->height = (node->left->height>node->right->height)? node->left->height+1: node->right->height+1;

    return node;
}

template<typename T, typename U>
AVLNode<T,U>* AVLTree<T,U>::rotate_right(AVLNode<T,U>*& node){
    //TODO
    AVLNode<T,U>*& org_node = node;
    AVLNode<T,U>*& org_left = node->left;
    AVLNode<T,U>*& org_left_right = node->left->right;

    // change structure
    node = org_left;
    node->right = org_node;
    node->right->left = org_left_right;

    // update heights
    node->right->height = (node->right->left->height>node->right->right->height)? node->right->left->height+1: node->right->right->height+1;
    node->height = (node->left->height>node->right->height)? node->left->height+1: node->right->height+1;

    return node;
}

template<typename T, typename U>
AVLNode<T,U>* AVLTree<T,U>::insert(AVLNode<T,U>*& node, const T& key, const U& value) {
    //TODO
    //End case
    if (node == nullptr) {
        node = new AVLNode<T, U>*&(key, value);
    }
    
    //right-left
    if (key > node->key && key < node->right->key) {
        node->right->left = insert(node->right->left, key, value);

        if (node->right->height - node->left->height > 1) {
            AVLNode<T, U> *&org_node = node;
            AVLNode<T, U> *&org_right = node->right;
            AVLNode<T, U> *&org_right_left = node->right->left;

            //change structure
            org_node->right = org_right_left->left;
            org_right->left = org_right_left->right;
            node = org_right_left;
            node->left = org_node;
            node->right = org_right;

            //update height
            org_node->height = (org_node->left->height > org_node->right->height)? org_node->left->height+1: org_node->right->height+1;
            org_right->height = (org_right->left->height > org_right->right->height)? org_right->left->height+1: org_right->right->height+1;
            org_right_left->height = (org_right_left->left->height > org_right_left->right->height)? org_right_left->left->height+1: org_right_left->right->height+1;
        }
    }

    //right-right
    if (key > node->key && key > node->right->key) {
        node->right->right = insert(node->right->right, key, value);

        if (node->right->height - node->left->height > 1) {
            node = rotate_right(node); //this updates height automatically
        }
    }

    //left-right
    if (key < node->key && key > node->left->key) {
        node->left->right = insert(node->left->right, key, value);

        if (node->left->height - node->right->height > 1) {
            AVLNode<T, U> *&org_node = node;
            AVLNode<T, U> *&org_left = node->left;
            AVLNode<T, U> *&org_left_right = node->left->right;

            //change structure
            org_node->left = org_left_right->right;
            org_right->right = org_left_right->left;
            node = org_left_right;
            node->right = org_node;
            node->left = org_left;

            //update height
            org_node->height = (org_node->left->height > org_node->right->height)? org_node->left->height+1: org_node->right->height+1;
            org_left->height = (org_left->left->height > org_left->right->height)? org_left->left->height+1: org_left->right->height+1;
            org_left_right->height = (org_left_right->left->height > org_left_right->right->height)? org_left_right->left->height+1: org_left_right->right->height+1;
        }
    }
   
    //left-left
    if (key < node->key && key < node->left->key) {
        node->left->left = insert(node->left->left, key, value);

        if (node->left->height - node->right->height > 1) {
            node = rotate_left(node); //this updates height automatically
        }
    }

    return node;
}

template<typename T, typename U>
U AVLTree<T,U>::search(AVLNode<T,U>*& node, const T& key) {
    //TODO
    //return NULL if there are no such key, return value if there is

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
    
}
