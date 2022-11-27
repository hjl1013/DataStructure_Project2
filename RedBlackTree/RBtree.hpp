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

}

template<typename T, typename U>
RBNode<T,U>* RBTree<T,U>::rotate_right(RBNode<T,U>*& node){
    //TODO

}

template<typename T, typename U>
RBNode<T,U>* RBTree<T,U>::insert(RBNode<T,U>*& node, const T& key, const U& value) {
    //TODO

}

template<typename T, typename U>
U RBTree<T,U>::search(RBNode<T,U>*& node, const T& key) {
    //TODO
    //return NULL if there are no such key, return value if there is
}

template<typename T, typename U>
RBNode<T,U>* RBTree<T,U>::remove(RBNode<T,U>*& node, const T& key) {

    //TODO

}

template<typename T, typename U>
void RBTree<T,U>::removeall(RBNode<T,U>*& node) {
    //TODO
    //for destructor
        
    }
    
}
