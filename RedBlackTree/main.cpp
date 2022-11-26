#include <algorithm>
#include <iterator>
#include <vector>
#include <random>
#include <time.h>
#include <string>

#include "RBtree.hpp"
#include <iostream>

using namespace std;

int main () {

    clock_t start_insert_remove, finish_insert_remove;
    clock_t start_search, finish_search;

    RBTree<int,string> tree;
    
    cout<<"<< RB tree >>"<<endl<<endl;

    start_insert_remove = clock();
   
    tree.insert(16545, "yeonnamdong");
    tree.insert(54312, "sinsadong");
    
    tree.insert(11243, "sillimdong");
    tree.insert(66443, "bongcheondong");
    tree.insert(55443, "jungangdong");
    tree.insert(32340, "banpodong");
    tree.insert(33450, "dobongdong");
    tree.insert(25234, "samseongdong");    
    tree.remove(54312);
    tree.insert(54155, "gurodong");
    tree.insert(51211, "banghwadong");
    
    tree.remove(11243);
    
    finish_insert_remove = clock();

    cout<<"print inorder"<<endl;
    cout<<"_________________________"<<endl;
    tree.inorder(tree.root);
    cout<<endl;
    cout<<"print preorder"<<endl;
    cout<<"_________________________"<<endl;
    tree.preorder(tree.root);
    cout<<endl;

    start_search = clock();

    cout<<"print search"<<endl;
    cout<<"_________________________"<<endl;
    cout<<"search 54155: "<<tree.search(54155)<<endl;
    //print 0 if none
    cout<<"search 12345:"<<tree.search(12345)<<endl;
    cout<<"search 11243:"<<tree.search(11243)<<endl; //removed

    finish_search = clock();
   
    //time for operation ( this case may have 0ms )
    cout<<endl<<"print time for opration"<<endl;
    cout<<"_________________________"<<endl;
    cout<<"time for insert and remove: "<<(double)(finish_insert_remove-start_insert_remove)<<"ms"<<endl;   
    cout<<"time for search: "<<(double)(finish_search-start_search)<<"ms"<<endl;  
    return 0;
}
