/**
 * A template Tree class.
 * Implemented as a linked list.
 *
 * @author Amir Gillette
 * @since 6-5-22
 */

#pragma once

template <typename T>
class Tree{
public:
    Tree() : root(nullptr) {}

    // Destructor in order to tree class instance.
    // Performs postorder traversal in order to free
    // all the elements without losing a certain element.
    ~Tree(){
        postorder(root);
    }

    // Method adds the root with a given value
    void add_root(const T& val) {
        root = new Node(val, nullptr, nullptr, nullptr);
    }

    // Method adds the sub element under the super given element.
    void add_sub(const T& super, const T& sub){
        Node* super_ref = search(super);
        Node* subNode = new Node(sub, super_ref, nullptr, nullptr);
        Node* sub_list = super_ref->sub;

        // New sub element
        if (sub_list == nullptr){
            sub_list->next_sib = subNode;
            super_ref->sub = subNode;
            return;
        }

        // O.W
        while(sub_list->next_sib != nullptr){
            sub_list = sub_list->next_sib;
        }
        sub_list->next_sib = subNode;
        super_ref->sub = subNode;
    }

private:
    // Node inner class
    struct Node{
        T info;                 /* Node's value*/
        Node* parent;           /* Parent's node*/
        Node* sub;              /* Current node's sub-entities list (points to first sub-entity)*/
        Node* next_sib;         /* Sub-entities' siblings list*/
        Node(const T& val, Node* node, Node* parNode, Node* sib): info(val), sub(node), parent(parNode), next_sib(sib){}
    };

    // Fields
    Node* root;                 /* Root field*/

    // Method finds node by value
    Node* search(const T& val){
        return search(root, val);
    }
    // Auxiliary recursive function for search
    Node* search(Node* ptr, const T& val){
        if (ptr->info == val){ /* Data corresponds the node's data*/
            return ptr;
        }
        else{
            Node* subList = ptr->sub;
            while (subList != nullptr){
                Node* currSub = search(subList, val);
                if (currSub != nullptr){
                    return currSub;
                }
                subList = subList->next_sib;
            }
        }
        return nullptr;
    }
    // Auxiliary function for the class's destructor.
    // Postorder traversal: clears the nodes.
    void postorder(Node* ptr) {
        if (ptr == nullptr) return;
        postorder(ptr->sub);
        delete ptr; // deletes visited node
        postorder(ptr->next_sib);
    }

public:
    //-------------------------------------------------------------------
    // iterator related code:
    // inner class and methods that return instances of iterators
    // which perform non-binary traversals
    //-------------------------------------------------------------------


};