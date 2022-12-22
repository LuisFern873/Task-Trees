#ifndef ITERATOR_H
#define ITERATOR_H

#include "node.h"
#include <queue>

template <typename T>
class BSTIterator
{
public:
    enum Type {
        PreOrder, InOrder, PostOrder
    };

private:
    NodeBT<T> *current;
    Type type;
    queue<NodeBT<T>*> pila = {};



public:
    BSTIterator() : current(nullptr), type(InOrder) {};
    BSTIterator(NodeBT<T> *currentt, Type type=InOrder): type(type) {
        current=currentt;
        pila={};
        switch(type){
            case PreOrder:
                displayPreOrder(currentt, pila);
                break;
            case InOrder:
                displayInOrder(currentt, pila);
                break;
            case PostOrder:
                displayPostOrder(currentt, pila);
                break;
        }
        current=pila.front();
    }

    void print(){
        cout<<"Print: ";
        auto p = pila;
        while(p.front()!=nullptr){
            cout<<p.front()->data<<" ";
            p.pop();
        }
        cout<<endl;
    }

    BSTIterator<T> &operator=(BSTIterator<T> other){
        current=other.current;
        type=other.type;
        pila=other.pila;
        return *this;
    };
    bool operator!=(BSTIterator<T> other){
        return current != other.current;
    };
    BSTIterator<T> &operator++(){
        if(!pila.empty())pila.pop();
        if(!pila.empty()){current=pila.front();
            return *this;}
        else *this=nullptr;

    };   //++it
    T operator*(){
        //cout<<"Pilar: ";
        //while(pila.front()!= nullptr){
        //    cout<<pila.front()<<" ";
        //    pila.pop();
        //}
        //return 0;
        //cout<<current->data<<" ";

        if(current!=nullptr)return current->data;
        else return 0;
    };
    void displayInOrder(NodeBT<T>* &node, queue<NodeBT<T>*>& s){
        if(node == nullptr) return;
        displayInOrder(node->left, s);
        s.push(node);
        displayInOrder(node->right, s);
    }

    void displayPreOrder(NodeBT<T>* &node, queue<NodeBT<T>*>& s){
        if(node == nullptr) return;
        s.push(node);
        displayPreOrder(node->left, s);
        displayPreOrder(node->right, s);
    }
    void displayPostOrder(NodeBT<T>* &node, queue<NodeBT<T>*>& s){
        if(node == nullptr) return;
        displayPostOrder(node->left, s);
        displayPostOrder(node->right, s);
        s.push(node);
    }
    void displayBFS(NodeBT<T>* &node, queue<NodeBT<T>*>& s){
        if(node == nullptr) return;
        displayBFS(node->left, s);
        displayBFS(node->right, s);
        s.push(node);
    }
};

#endif
