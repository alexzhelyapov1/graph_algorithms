#pragma once
#include <iostream>
#include <fstream>

// TODO:
// PreInsertFunction

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

    void Insert(T value);
    std::pair<Node<T>*, Node<T>*> Split(T value);
    static Node<T>* Merge(Node<T>* less, Node<T>* bigger);
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
    Node(T value, Node<T>* predessor_ptr);

    Node<T>* LeftRotate();
    Node<T>* RightRotate();
    Node<T>* Splay();

    Node<T>* Find(T value);
    Node<T>* FindPreInsert(T value);
    Node<T>* FindMax();

    void GraphVizPrint(std::ofstream& out, const std::string& color = "black") {
        if (left_node_ != nullptr) {
            out << value_ << " -> " << left_node_->value_ << " [color = " << color << "]" << std::endl;
            left_node_->GraphVizPrint(out, color);
        }
        else {
            out << value_ << " -> L_NULL" << value_ << " [color = " << color << "]"  << std::endl;
        }

        if (right_node_ != nullptr) {
            out << value_ << " -> " << right_node_->value_  << " [color = " << color << "]" << std::endl;
            right_node_->GraphVizPrint(out, color);
        }
        else {
            out << value_ << " -> R_NULL" << value_ << " [color = " << color << "]"  << std::endl;
        }
    }
};



// --------------------------------------------------------------------------------------------------------------------
// Tree methods
// --------------------------------------------------------------------------------------------------------------------


template <typename T>
void Tree<T>::Insert(T value)
{
    Node<T>* pre_insert = root_->FindPreInsert(value);

    Node<T>* new_node = new Node<T>(value);
    new_node->predessor_node_ = pre_insert;

    if (pre_insert == nullptr) {
        root_ = new_node;
    }
    else if (value > pre_insert->value_) {
        pre_insert->right_node_ = new_node;
    }
    else {
        pre_insert->left_node_ = new_node;
    }

    root_ = new_node->Splay();
}


template <typename T>
std::pair<Node<T>*, Node<T>*> Tree<T>::Split(T value)
{
    if (root_ == nullptr) {
        return std::pair(nullptr, nullptr);
    }

    Node<T>* pre_insert = root_->FindPreInsert(value);
    root_ = pre_insert->Splay();

    std::cout << "New root: " << root_->value_ << std::endl;

    if (root_->value_ >= value) {
        Node<T>* less_tree = root_->left_node_;
        root_->left_node_ = nullptr;

        if (less_tree != nullptr) {
            less_tree->predessor_node_ = nullptr;
        }

        return std::pair<Node<T>*, Node<T>*>(less_tree, root_);
    }

    else {
        Node<T>* bigger_tree = root_->right_node_;
        root_->right_node_ = nullptr;

        if (bigger_tree != nullptr) {
            bigger_tree->predessor_node_ = nullptr;
        }

        return std::pair<Node<T>*, Node<T>*>(root_, bigger_tree);
    }
}


template <typename T>
Node<T>* Tree<T>::Merge(Node<T>* less, Node<T>* bigger)
{
    if (less == nullptr) {
        std::cout << "Empty less\n";

        if (bigger != nullptr) {
            std::cout << "Bigger " << bigger->value_ << std::endl;
        }
        else {
            std::cout << "Empty bigger\n";
        }

        return bigger;
    }

    Node<T>* max = less->FindMax();
    std::cout << "Found max " << max->value_ << std::endl;
    Node<T>* new_root = max->Splay();

    if (new_root == nullptr) {
        std::cout << "Warning. New root is nullptr in Merge";
        return nullptr;
    }

    if (new_root->predessor_node_ != nullptr) {
        std::runtime_error("Predessor of root is not nullptr");
    }

    if (new_root != max) {
        std::runtime_error("Max is not new root");
    }

    if (new_root->right_node_ != nullptr) {
        std::runtime_error("Right node is not empty after splay of max element!");
    }

    new_root->right_node_ = bigger;
    bigger->predessor_node_ = new_root;

    std::cout << "New root " << new_root->value_ << std::endl;
    return new_root;
}


template <typename T>
Node<T>* Node<T>::Find(T value)
{
    Node<T>* node = this;

    while (node != nullptr) {
        if (value > node->value_) {
            node = node->right_node_;
        }
        else if (value < node->value_) {
            node = node->left_node_;
        }
        else {
            std::cout << "Splaing " << node->value_ << std::endl;
            return node->Splay();
        }
    }

    std::cout << "Warning: Element " << value << " not found.\n";
    return node;
}


template <typename T>
Node<T>* Node<T>::FindPreInsert(T value)
{
    Node<T>* pre_insert = nullptr;
    Node<T>* insert = this;

    while (insert != nullptr) {
        pre_insert = insert;

        if (value > insert->value_) {
            insert = insert->right_node_;
        }
        else {
            insert = insert->left_node_;
        }
    }

    return pre_insert;
}


template <typename T>
Node<T>* Node<T>::FindMax()
{
    if (this == nullptr) {
        return nullptr;
    }

    Node<T>* node = this;

    while (node->right_node_ != nullptr) {
        node = node->right_node_;
    }

    return node;
}


template <typename T>
void Tree<T>::Delete(T value)
{
    root_ = root_->Find(value);
    Node<T>* node = root_;

    if (root_ == nullptr) {
        std::cout << "Warning. Nothing to delete\n";
        return;
    }

    if (root_->predessor_node_ != nullptr) {
        std::runtime_error("Predessor of root is not nullptr");
    }

    root_ = Merge(root_->left_node_, root_->right_node_);

    delete node;
}


// --------------------------------------------------------------------------------------------------------------------
// Node methods
// --------------------------------------------------------------------------------------------------------------------


template <typename T>
Node<T>::Node(T value, Node<T>* predessor_ptr) : value_(value), predessor_node_(predessor_ptr) {
    if (predessor_node_ != nullptr) {

        if (predessor_node_->value_ > value) {
            predessor_node_->left_node_ = this;
        }

        else {
            predessor_node_->right_node_ = this;
        }
    }
}


template <typename T>
Node<T>* Node<T>::Splay()
{
    while (predessor_node_ != nullptr) {
            if (predessor_node_->predessor_node_ == nullptr) {

                if (this == predessor_node_->left_node_) {
                    predessor_node_->RightRotate();
                } else {
                    predessor_node_->LeftRotate();
                }
            } else {

                // Zig-Zig
                if (this == predessor_node_->left_node_ && predessor_node_ == predessor_node_->predessor_node_->left_node_) {

                    predessor_node_->predessor_node_->RightRotate();
                    predessor_node_->RightRotate();

                } else if (this == predessor_node_->right_node_ && predessor_node_ == predessor_node_->predessor_node_->right_node_) {

                    predessor_node_->predessor_node_->LeftRotate();
                    predessor_node_->LeftRotate();
                }
                // Zig-Zag step.
                else if (this == predessor_node_->right_node_ && predessor_node_ == predessor_node_->predessor_node_->left_node_) {

                    predessor_node_->LeftRotate();
                    predessor_node_->RightRotate();

                } else if (this == predessor_node_->left_node_ && predessor_node_ == predessor_node_->predessor_node_->right_node_) {

                    predessor_node_->RightRotate();
                    predessor_node_->LeftRotate();
                }
            }
        }

    return this;
}


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
        if (predessor_node_->left_node_ == this) {
            predessor_node_->left_node_ = new_root;
        }
        else {
            predessor_node_->right_node_ = new_root;
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
