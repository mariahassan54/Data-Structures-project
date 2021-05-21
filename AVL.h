#pragma once
#include <iostream>
#include "key.h"
#include "LinkedList.h"
using namespace std;

struct information {
    Key* key;
    int lineNumber;
    void operator=(const information& obj) {
        key = obj.key;
        lineNumber = obj.lineNumber;
    }
};

struct node
{
    information info;
    node* left;
    node* right;
    int height;
    node() {
        info.key = nullptr;
        info.lineNumber = 0;
        left = nullptr;
        right = nullptr;
        height = 1;
    }
};

class AVL
{

public:

    int Height(node*);
    node* insertion(node*, information*);
    void in_order(node*);
    void pre_order(node*);
    void post_order(node*);
    node* delete_node(node*, information*);
    int getHeight(node*);
    node* RightRotate(node*&);
    node* LeftRotate(node*&);
    int getBalance(node*);
};

int AVL::getBalance(node* _node)
{
    if (_node == nullptr)
        return 0;
    return (getHeight(_node->left) - getHeight(_node->right));
}

int AVL::getHeight(node* _temp) {
    if (_temp == nullptr) {
        return 0;
    }
    return _temp->height;
}

//--------------------------------------------------------

node* newNode(information* keyinfo)
{
    node* _node = new node();
    _node->info.key = keyinfo->key;
    _node->info.lineNumber = keyinfo->lineNumber;
    _node->left = NULL;
    _node->right = NULL;
    _node->height = 1;
    return(_node);
}

node* AVL::insertion(node* temp, information* keyInfo)
{
    if (temp == NULL)
    {
        return(newNode(keyInfo));
    }

    if (keyInfo->key < temp->info.key)
    {
        temp->left = insertion(temp->left, keyInfo);
    }
    else if (keyInfo->key > temp->info.key)
    {
        temp->right = insertion(temp->right, keyInfo);
    }
    else {
        return temp;
    }

    temp->height = 1 + max(getHeight(temp->left), getHeight(temp->right));
    int balance = getBalance(temp);
    if (balance > 1) {
        if (keyInfo->key < temp->left->info.key) {
            return RightRotate(temp);
        }
        else if (keyInfo->key > temp->left->info.key) {
            temp->left = LeftRotate(temp->left);
            return RightRotate(temp);
        }
    }
    if (balance < -1) {
        if (keyInfo->key > temp->right->info.key) {
            return LeftRotate(temp);
        }
        else if (keyInfo->key < temp->right->info.key) {
            temp->right = RightRotate(temp->right);
            return LeftRotate(temp);
        }
    }
    return temp;
    /*
    if (temp->info > number)
    {
        if (temp->left != NULL)
        {
            insertion(temp->left);
            return;
        }
        else
        {
            temp->left = new node;
            temp->left->info = number;
            temp->left->left = NULL;
            temp->left->right = NULL;
            return;
        }
    }
    if (temp->info < number)
    {
        if (temp->right != NULL)
        {
            insertion(temp->right);
            return;
        }
        else
        {
            temp->right = new node;
            temp->right->info = number;
            temp->right->left = NULL;
            temp->right->right = NULL;
            return;
        }
    }
    */
} //--------------------    Insertion Function  Ends    --------------------------
void AVL::in_order(node* temp)
{
    if (temp == NULL)
    {
        return;
    }
    in_order(temp->left);
    cout << temp->info.key->getKey() << "  ";
    in_order(temp->right);
}

void AVL::pre_order(node* temp)
{
    if (temp == NULL)
    {
        return;
    }
    cout << temp->info.key->getKey() << "  ";
    pre_order(temp->left);
    pre_order(temp->right);
}

void AVL::post_order(node* temp)
{
    if (temp == NULL)
    {
        return;
    }
    post_order(temp->left);
    post_order(temp->right);
    cout << temp->info.key->getKey() << "  ";
}


int AVL::Height(node* _node)
{
    if (_node == NULL)
        return 0;
    else
    {
        int leftDeep = Height(_node->left);
        int rightDeep = Height(_node->right);
        if (leftDeep > rightDeep) {
            return(leftDeep + 1);
        }
        else {
            return(rightDeep + 1);
        }
    }
}

node* AVL::RightRotate(node*& _node)
{
    if (_node->left == nullptr) {
        return _node;
    }
    node* _temp = _node->left;
    node* temp2 = _temp->right;
    _temp->right = _node;
    _node->left = temp2;
    _node->height = max(getHeight(_node->left), getHeight(_node->right)) + 1;
    _temp->height = max(getHeight(_temp->left), _temp->height) + 1;
    return _temp;
}

node* AVL::LeftRotate(node*& _node)
{
    if (_node->right == nullptr) {
        return _node;
    }
    node* _temp = _node->right;
    node* temp2 = _temp->left;
    _temp->left = _node;
    _node->right = temp2;
    _node->height = max(getHeight(_node->left), getHeight(_node->right)) + 1;
    _temp->height = max(getHeight(_temp->right), _temp->height) + 1;
    return _temp;
}

node* AVL::delete_node(node* _temp, information* keyInfo)
{
    if (_temp == NULL)
        return _temp;
    if (keyInfo->key < _temp->info.key)
        _temp->left = delete_node(_temp->left, keyInfo);
    else if (keyInfo->key > _temp->info.key)
        _temp->right = delete_node(_temp->right, keyInfo);
    else {
        if (_temp->left == NULL) {
            node* temp = _temp->right;
            delete _temp;
            return temp;
        }
        else if (_temp->right == NULL) {
            node* temp = _temp->left;
            delete _temp;
            return temp;
        }
        node* temp = _temp->right;
        while (temp && temp->left != NULL)
            temp = temp->left;
        _temp->info = temp->info;
        _temp->right = delete_node(_temp->right, &temp->info);
    }
    if (_temp == NULL) {
        return _temp;
    }
    //Above code is from last lab, now we will rotate if the tree is unbalanced.
    _temp->height = max(getHeight(_temp->left), getHeight(_temp->right)) + 1;
    int balance = getBalance(_temp);
    if (balance > 1) {
        if (getBalance(_temp->left) >= 0) {
            return RightRotate(_temp);
        }
        else {
            _temp->left = LeftRotate(_temp->left);
            return RightRotate(_temp);
        }
    }
    if (balance < -1) {
        if (getBalance(_temp->right) <= 0) {
            return LeftRotate(_temp);
        }
        else {
            _temp->right = RightRotate(_temp->right);
            return LeftRotate(_temp);
        }
    }
    return _temp;
}