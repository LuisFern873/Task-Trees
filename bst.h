#ifndef BSTREE_H
#define BSTREE_H

#include "node.h"
#include "iterator.h"
#include <iostream>
#include<stack>
#include<queue>
#include<vector>
using namespace std;

template <typename T> class BSTree {

private:
    NodeBT<T> *root;
    void insert(T value, NodeBT<T> *&copia) {
        if (copia == nullptr) {
            auto *nodo = new NodeBT<T>(value);
            copia = nodo;
            return;
        }
        if (value > copia->data)
            insert(value, copia->right);
        else if (value < copia->data)
            insert(value, copia->left);
    }
    NodeBT<T> *&find(T value, NodeBT<T> *&copia) {
        if (copia == nullptr || copia->data == value)
            return copia;
        if (value > copia->data)
            return find(value, copia->right);
        return find(value, copia->left);
    }

    NodeBT<T> *&find_parent(T value, NodeBT<T> *&copia) {

        if (copia == nullptr ||
            (copia->left != nullptr && copia->left->data == value) ||
            (copia->right != nullptr && copia->right->data == value)) {
            return copia;
        }
        if (value > copia->data) {
            return find_parent(value, copia->right);
        } else if (value < copia->data) {
            return find_parent(value, copia->left);
        }
    }

    NodeBT<T> *&minValue(NodeBT<T> *&copia) {
        if (copia->left == nullptr)
            return copia;
        return minValue(copia->left);
    }
    NodeBT<T> *&maxValue(NodeBT<T> *&copia) {
        if (copia->right == nullptr)
            return copia;
        return maxValue(copia->right);
    }
/////
    int size(NodeBT<T> *&copia) {
        if (copia == nullptr)
            return 0;
        return 1 + size(copia->left) + size(copia->right);
    }

    NodeBT<T> *&beforeMinValue(NodeBT<T> *&copia) {
        if (copia == nullptr ||
            (copia->left != nullptr && copia->left->left == nullptr))
            return copia;
        return beforeMinValue(copia->left);
    }

    NodeBT<T> *&beforeMaxValue(NodeBT<T> *&copia) {
        if (copia == nullptr ||
            (copia->right != nullptr && copia->right->right == nullptr))
            return copia;
        return beforeMaxValue(copia->right);
    }
    void remove(NodeBT<T> *&copia, NodeBT<T> *&padre) {
        if (copia->left != nullptr) {
            auto *temp = &maxValue(copia->left);
            auto *before_temp = beforeMaxValue(copia->left);
            if (before_temp == nullptr) {
                before_temp = copia;
            }
            swap(copia->data, (*temp)->data);
            remove(*temp, before_temp);
            temp = nullptr;
            delete temp;
        } else if (copia->right != nullptr) {
            auto *temp = &minValue(copia->right);
            auto *before_temp = beforeMinValue(copia->right);
            if (before_temp == nullptr) {
                before_temp = copia;
            }
            swap(copia->data, (*temp)->data);
            remove(*temp, before_temp);
            temp = nullptr;
            delete temp;
        } else {
            if (padre->left != nullptr && padre->left->data == copia->data) {
                padre->left = nullptr;
                delete copia;
                return;
            }
            if (padre->right != nullptr && padre->right->data == copia->data) {
                padre->right = nullptr;
                delete copia;
                return;
            }
        }
    }
    bool isFull(NodeBT<T> *&copia) {
        bool a = copia->left != nullptr;
        bool b = copia->right != nullptr;
        if ((a + b) != 2)
            return !(a + b);
        return isFull(copia->left) && isFull(copia->right);
    }
    NodeBT<T> *&find_s_p(T &value, NodeBT<T> *&copia, T &ans, bool &modo,
                         bool &seen) {
        if (copia == nullptr || copia->data == value) {
            return copia;
        }
        if (value > copia->data) {
            if (!modo) {
                if (seen) {
                    ans = copia->data;
                    seen = false;
                } else if (copia->data > ans) {
                    ans = copia->data;
                }
            }
            return find_s_p(value, copia->right, ans, modo, seen);
        } else if (value < copia->data) {
            if (modo) {
                if (seen) {
                    ans = copia->data;
                    seen = false;
                } else if (copia->data < ans) {
                    ans = copia->data;
                }
            }
            return find_s_p(value, copia->left, ans, modo, seen);
        }
    }
    int isBalanced(NodeBT<T> *&copia) {
        // Caso Vacio
        if (copia == nullptr)
            return -1;
        else{
            int hleft = isBalanced(copia->left);
            int hright = isBalanced(copia->right);
            if(hleft == -2 || hright == -2 || abs(hleft-hright) > 1)
                return -2;
            else
                return max(hleft,hright)+1;
        }
    }
    int height(NodeBT<T> * & copia){ //o(n)
        if(copia == nullptr){
            return 0;
        }
        int left = height(copia->left);
        int right = height(copia->right);
        return max(left,right)+1;
    }
    void buildFromOrderedArray1(T *array,int n) {
        if (0 >= n)
            return;
        insert(array[n / 2]);
        buildFromOrderedArray1(array, n / 2);
        buildFromOrderedArray1(array + n / 2 + 1, n - n / 2 - 1);
    }
    void displayInOrder(NodeBT<T>*& copia,string & ans) {
        if (copia != nullptr) {
            displayInOrder(copia->left,ans);
            ans+=to_string(copia->data);
            ans +=" ";
            displayInOrder(copia->right,ans);
        }
    }
    void displayBFS(string & ans){
        queue<NodeBT<T>*> queue;
        queue.push(this->root);
        while(!queue.empty()){
            NodeBT<T>* node = queue.front();
            queue.pop();
            ans += to_string(node->data);
            ans+=" ";
            if(node->left != nullptr)
                queue.push(node->left);
            if(node->right!= nullptr)
                queue.push(node->right);
        }
    }

    void displayDFS(string & ans){
        stack<NodeBT<T>*> stack;
        stack.push(this->root);
        while(!stack.empty()){
            NodeBT<T>* node = stack.top();
            stack.pop();
            ans += to_string(node->data);
            ans+=" ";
            if(node->right != nullptr)
                stack.push(node->right);
            if(node->left!= nullptr)
                stack.push(node->left);
        }
    }
    void displayPreOrder(string & ans,NodeBT<T> * & copia){
        if(copia!=nullptr){
            ans+=to_string(copia->data);
            ans+=" ";
            displayPreOrder(ans,copia->left);
            displayPreOrder(ans,copia->right);
        }
    }
    void displayPostOrder(string & ans,NodeBT<T> * & copia){
        if(copia!=nullptr){
            displayPostOrder(ans,copia->left);
            displayPostOrder(ans,copia->right);
            ans+=to_string(copia->data);
            ans+=" ";
        }
    }

public:
    typedef BSTIterator<T> iterator;
    //iterator begin(BSTIterator<int>::Type _);   Intento de iteradores (Comentado)
    //iterator end();
    BSTree() : root(nullptr) {}
    int height() {
        return height(root) - 1;
    }
    void insert(T value) { insert(value, root); }
    bool find(T value) { return find(value, root) != nullptr; }
    T minValue() {
        // devolver error si size == 0
      if(root == nullptr) throw std::invalid_argument( "No tiene un valor minimo" );  
      return minValue(root)->data;
    }
    T maxValue() {
      if(root == nullptr) throw std::invalid_argument( "No tiene un valor maximo" );  
        // devolver error si size == 0
        return maxValue(root)->data;
    }
    int size() { return size(root); }
    void remove(T value) {
        if (root == nullptr)
            return;
        auto *a = find(value, root);
        if(a == nullptr) return;
        if (a->left == nullptr && a->right == nullptr) {
            auto *b = find_parent(value, root);
            if (b == nullptr) {
                root = nullptr;
                return;
            }
            if (b->left != nullptr && b->left->data == value) {
                b->left = nullptr;
                delete a;
                return;
            }
            if (b->right != nullptr && b->right->data == value) {
                b->right = nullptr;
                delete a;
                return;
            }
        }
        remove(a, root);
    }
    bool isFull() {
        if (root == nullptr)
            return true;
        return isFull(root);
    }
    T successor(T value) {
        T ans = T{}; // el ans deber ser el valor del root
        bool a = true;
        bool b = true;
        auto *temp = find_s_p(value, root, ans, a, b);
        if (temp == nullptr) {
            throw std::invalid_argument( "Valor no encontrado" );
        }
        if (temp->right != nullptr) {
            ans = minValue(temp->right)->data;
            return ans;
        }
        if (b) {
          throw std::invalid_argument( "Este valor no tiene un successor" );
        }
        return ans;
    }

    T predecessor(T value) {
        T ans = T{}; // el ans deber ser el valor del root
        bool a = false;
        bool b = true;
        auto *temp = find_s_p(value, root, ans, a, b);
        if (temp == nullptr) {
          throw std::invalid_argument( "Valor no encontrado" );
        }
        if (temp->left != nullptr) {
            ans = maxValue(temp->left)->data;
            return ans;
        }
        if (b) {
          throw std::invalid_argument( "Este valor no tiene un predecessor" );
        }
        return ans;
    }
    void clear() {
        root->KillSelf();
        root = nullptr;
    }
    void buildFromOrderedArray(T *array, int n) {
        clear();
        buildFromOrderedArray1(array,n);
    }
    bool isBalanced() { //Tomando en cuenta de que un arbol vacio es balanceado
        return isBalanced(root) !=-2;
    }
    string displayInOrder() {
        // TODO
        string ans = "";
        displayInOrder(root,ans);
        return ans;
    }
    string displayBFS(){
        string ans = "";
        displayBFS(ans);
        return ans;
    }
    string displayDFS(){
        string ans = "";
        displayDFS(ans);
        return ans;
    }
    string displayPreOrder(){
        string ans = "";
        displayPreOrder(ans,root);
        return ans;
    }
    string displayPostOrder(){
        string ans = "";
        displayPostOrder(ans,root);
        return ans;
    }
};

#endif

