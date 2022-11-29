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
        int color; // 1 -> red, 0 -> black, 2 -> double black, 3 -> double black nil node

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
    RBNode<T,U>* org_node = node;
    RBNode<T,U>* org_right = node->right;
    RBNode<T,U>* org_right_left = node->right->left;

    // change structure
    node = org_right;
    node->left = org_node;
    node->left->right = org_right_left;

    // update parent
    node->parent = org_node->parent;
    node->left->parent = node;
    if (node->left->right) node->left->right->parent = node->left;

    return node;
}

template<typename T, typename U>
RBNode<T,U>* RBTree<T,U>::rotate_right(RBNode<T,U>*& node){
    //TODO
    RBNode<T,U>* org_node = node;
    RBNode<T,U>* org_left = node->left;
    RBNode<T,U>* org_left_right = node->left->right;

    // change structure
    node = org_left;
    node->right = org_node;
    node->right->left = org_left_right;

    // update parent
    node->parent = org_node->parent;
    node->right->parent = node;
    if (node->right->left) node->right->left->parent = node->right;

    return node;
}

template<typename T, typename U>
RBNode<T,U>* RBTree<T,U>::insert(RBNode<T,U>*& node, const T& key, const U& value) {
    //TODO
    //end case
    if (!node){
        RBNode<T,U> *new_node = new RBNode<T,U>(key, value);
        if (node == root){
            new_node->color = 0;
        }
        else {
            new_node->color = 1;
        }
        new_node->parent = new_node;
        return new_node;
    }

    //insert recursively and change structure if needed
    if (key < node->key){
        //insert
        node->left = insert(node->left, key, value);
        node->left->parent = node;

        //change structure
        if (node->color == 0 && node->left->color == 1) {
            if (node->left->left && node->left->left->color == 1) {
                if (node->right && node->right->color == 1){
                    node->color = 1;
                    node->left->color = 0;
                    node->right->color = 0;
                }
                else {
                    node = rotate_right(node);
                    node->color = 0;
                    node->left->color = 1;
                    node->right->color = 1;
                }
            }
            else if (node->left->right && node->left->right->color == 1) {
                if (node->right && node->right->color == 1){
                    node->color = 1;
                    node->left->color = 0;
                    node->right->color = 0;
                }
                else {
                    node->left = rotate_left(node->left);
                    node = rotate_right(node);
                    node->color = 0;
                    node->left->color = 1;
                    node->right->color = 1;
                }
            }
        }
    }
    else if (key > node->key) {
        //insert
        node->right = insert(node->right, key, value);
        node->right->parent = node;

        //change structure
        if (node->color == 0 && node->right->color == 1) {
            if (node->right->right && node->right->right->color == 1) {
                if (node->left && node->left->color == 1){
                    node->color = 1;
                    node->left->color = 0;
                    node->right->color = 0;
                }
                else {
                    node = rotate_left(node);
                    node->color = 0;
                    node->left->color = 1;
                    node->right->color = 1;
                }
            }
            else if (node->right->left && node->right->left->color == 1) {
                if (node->left && node->left->color == 1){
                    node->color = 1;
                    node->left->color = 0;
                    node->right->color = 0;
                }
                else {
                    node->right = rotate_right(node->right);
                    node = rotate_left(node);
                    node->color = 0;
                    node->left->color = 1;
                    node->right->color = 1;
                }
            }
        }
    }
    else {
        node->value = value;
    }

    //always update root node color to black.
    if (node->parent == node){
        node->color = 0;
    }

    return node;
}

template<typename T, typename U>
U RBTree<T,U>::search(RBNode<T,U>*& node, const T& key) {
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
RBNode<T,U>* RBTree<T,U>::remove(RBNode<T,U>*& node, const T& key) {
    //TODO

    // remove node
    if (key < node->key){
        node->left = remove(node->left, key);
    }
    else if (key > node->key) {
        node->right = remove(node->right, key);
    }
    else {
        if (!node->left || !node->right){
            if (node->color == 1) { //has 0 child
                delete node;
                node = nullptr;
                return nullptr;
            }
            else { //node->color = black(0)
                if (node->left) {
                    RBNode<T,U> *child = node->left;
                    delete node;
                    node = nullptr;
                    if (child->color == 1) {
                        child->color = 0;
                    }
                    else{
                        child->color = 2; //double black
                    }
                    return child;
                }
                else if (node->right) {
                    RBNode<T,U> *child = node->right;
                    delete node;
                    node = nullptr;
                    if (child->color == 1) {
                        child->color = 0;
                    }
                    else{
                        child->color = 2; //double black
                    }
                    return child;
                }
                else{
                    node->color = 3;
                }
            }
        }
        else { //has two children
            RBNode<T,U> *replace = node->right;
            while (replace->left) {
                replace = replace->left;
            }
            node->key = replace->key;
            node->value = replace->value;
            node->right = remove(node->right, replace->key);
        }
    }

    //solve problems
    if (node->left && node->left->color >= 2) {
        if (node->left->color == 3) {
            delete node->left;
            node->left = nullptr;
        }

        if (node->right->color == 0) {
            if (node->right->right && node->right->right->color == 1) {
                node->right->color = node->color;
                node->color = node->right->right->color = 0;
                node = rotate_left(node);
            }
            else if (node->right->left && node->right->left->color == 1) {
                node->right->left->color = node->color;
                node->color = node->right->color = 0;
                node->right = rotate_right(node->right);
                node = rotate_left(node);
            }
            else {
                node->right->color = 1;
                if (node->color == 0) node->color = 2;
                else node->color = 0;
                if (node->left) node->left->color = 0;
            }
        }
        else {
            node->color = 1;
            node->right->color = 0;
            node = rotate_left(node);

            RBNode<T,U> *child = node->left;
            if (child->right->right && child->right->right->color == 1) {
                child->right->color = child->color;
                child->color = child->right->right->color = 0;
                child = rotate_left(child);
            }
            else if (child->right->left && child->right->left->color == 1) {
                child->right->left->color = child->color;
                child->color = child->right->color = 0;
                child->right = rotate_right(child->right);
                child = rotate_left(child);
            }
            else {
                child->right->color = 1;
                if (child->color == 0) child->color = 2;
                else child->color = 0;
                if (child->left) child->left->color = 0;
            }
        }
    }
    else if (node->right && node->right->color >= 2) {
        if (node->right->color == 3) {
            delete node->right;
            node->right = nullptr;
        }

        if (node->left->color == 0) { //existence of right children and right grandchildren is guaranteed
            if (node->left->left && node->left->left->color == 1) {
                node->left->color = node->color;
                node->color = node->left->left->color = 0;
                node = rotate_right(node);
            }
            else if (node->left->right && node->left->right->color == 1) {
                node->left->right->color = node->color;
                node->color = node->left->color = 0;
                node->left = rotate_left(node->left);
                node = rotate_right(node);
            }
            else {
                node->left->color = 1;
                if (node->color == 0) node->color = 2;
                else node->color = 0;
                if (node->right) node->right->color = 0;
            }
        }
        else {
            node->color = 1;
            node->left->color = 0;
            node = rotate_right(node);

            RBNode<T,U> *child = node->right;
            if (child->left->left && child->left->left->color == 1) {
                child->left->color = child->color;
                child->color = child->left->left->color = 0;
                child = rotate_right(child);
            }
            else if (child->left->right && child->left->right->color == 1) {
                child->left->right->color = child->color;
                child->color = child->left->color = 0;
                child->left = rotate_left(child->left);
                child = rotate_right(child);
            }
            else {
                child->left->color = 1;
                if (child->color == 0) child->color = 2;
                else child->color = 0;
                if (child->right) child->right->color = 0;
            }
        }
    }

    if (root->color == 2) {
        root->color = 0;
    }
    else if (root->color == 3) {
        delete root;
        root = nullptr;
    }

    return node;
}

template<typename T, typename U>
void RBTree<T,U>::removeall(RBNode<T,U>*& node) {
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
