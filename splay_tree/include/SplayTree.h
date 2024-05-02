#pragma once
#include <iostream>
#include <fstream>


#define UNREACHABLE std::cout << __FUNCTION__ << " " << __LINE__ << std::endl;\
                    throw std::runtime_error("Unreachable");


// --------------------------------------------------------------------------------------------------------------------
// Class declarations
// --------------------------------------------------------------------------------------------------------------------

template <typename T> class Node;


template <typename T>
class Tree
{
  public:
    Node<T>* root_ = nullptr;

    std::pair(Node<T>*, Node<T>*) Split(T value)
    {
        if (root_ == nullptr) {
            return std::pair(nullptr, nullptr);
        }

        
    }

    void Insert(T value)
    {
        if (root_ == nullptr) {
            root_ = new Node<T>(value);
        }

    }

    Node<T>* Find(T value);
    void Delete(T value);
    
};



template <typename T>
class Node
{
    template <typename U> friend class Tree;

  public:
    T value_;
    Node<T>* left_node_ = nullptr;
    Node<T>* right_node_ = nullptr;
    Node<T>* predessor_node_ = nullptr;
    Node(T value) : value_(value), predessor_node_(nullptr) {}
    Node(T value, Node<T>* predessor_ptr) : value_(value), predessor_node_(predessor_ptr) {
        if (predessor_node_ != nullptr) {

            if (predessor_node_->value_ > value) {
                predessor_node_->left_node_ = this;
            }

            else {
                predessor_node_->right_node_ = this;
            }
        }
    }

    Node<T>* LeftRotate();
    Node<T>* RightRotate();

    Node<T>* Zig(Node<T>* predessor_node, Node<T>* x_node, Node<T>* root)
    {
        if (predessor_node != root) {
            throw std::runtime_error("ERROR! Zig with not root predessor");
        }

        if (predessor_node->left_node_ == x_node) {
            return predessor_node->RightRotate();
        }
        else if (predessor_node->right_node_ == x_node) {
            return predessor_node->LeftRotate();
        }
        else {
            UNREACHABLE
        }
    }

    void GraphVizPrint(std::ofstream& out) {       
        if (left_node_ != nullptr) {
            out << value_ << " -> " << left_node_->value_ << std::endl;
            left_node_->GraphVizPrint(out);
        }
        else {
            out << value_ << " -> L_NULL" << value_ << std::endl;
        }

        if (right_node_ != nullptr) {
            out << value_ << " -> " << right_node_->value_ << std::endl;
            right_node_->GraphVizPrint(out);
        }
        else {
            out << value_ << " -> R_NULL" << value_ << std::endl;
        }
    }
};


template <typename T>
Node<T>* Node<T>::LeftRotate()
{
    if (right_node_ == nullptr) {
        return this;
    }

    Node<T>* root_right_left = right_node_->left_node_;
    Node<T>* new_root = right_node_;

    new_root->left_node_ = this;

    if (predessor_node_ != nullptr) {
        if (predessor_node_->left_node_ == this) {
            predessor_node_->left_node_ = new_root;
        }
        else {
            predessor_node_->right_node_ = new_root;
        }
    }

    new_root->predessor_node_ = predessor_node_;
    predessor_node_ = new_root;
    right_node_ = root_right_left;

    if (right_node_ != nullptr) {
        right_node_->predessor_node_ = this;
    }

    return new_root;
}


template <typename T>
Node<T>* Node<T>::RightRotate()
{
    if (left_node_ == nullptr) {
        return this;
    }

    Node<T>* root_left_right = left_node_->right_node_;
    Node<T>* new_root = left_node_;

    new_root->right_node_ = this;

    if (predessor_node_ != nullptr) {
        if (predessor_node_->right_node_ == this) {
            predessor_node_->right_node_ = new_root;
        }
        else {
            predessor_node_->left_node_ = new_root;
        }
    }

    new_root->predessor_node_ = predessor_node_;
    predessor_node_ = new_root;
    left_node_ = root_left_right;

    if (left_node_ != nullptr) {
        left_node_->predessor_node_ = this;
    }

    return new_root;
}