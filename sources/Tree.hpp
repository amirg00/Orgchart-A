/**
 * <--------- CLASS DESCRIPTION ---------->
 * A template Tree class.
 * Implemented as a doubly linked list.
 *
 * @author Amir Gillette
 * @since 6-5-22
 * -----------------------------------------
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
    class level_order_iterator{
    private:
        Node* ptr_to_curr_node;
    public:
        explicit level_order_iterator(Node* ptr = nullptr)
        : ptr_to_curr_node(ptr) {
        }

        // Note that the method is const as this operator does not
        // allow changing of the iterator.
        // Note that it returns T& as it allows changing what it points to.
        // A const_iterator class will return const T&
        // and the method will still be const
        T& operator*() const {
            return ptr_to_curr_node->info;
        }

        T* operator->() const {
            return &(ptr_to_curr_node->info);
        }

        // Prefix increment: ++iterator;
        level_order_iterator& operator++() {
            //++pointer_to_current_node;
            ptr_to_curr_node = ptr_to_curr_node->m_next;
            return *this;
        }

        // Postfix increment: ++iterator;
        const level_order_iterator operator++(int) {
            level_order_iterator tmp = *this;
            ptr_to_curr_node = ptr_to_curr_node->m_next;
            return tmp;
        }

        bool operator==(const level_order_iterator& rhs) const {
            return ptr_to_curr_node == rhs.ptr_to_curr_node;
        }

        bool operator!=(const level_order_iterator& rhs) const {
            return ptr_to_curr_node != rhs.ptr_to_curr_node;
        }
    }; // END OF CLASS level_order_iterator

    class reverse_level_order_iterator{
    private:
        Node* ptr_to_curr_node;
    public:
        explicit reverse_level_order_iterator(Node* ptr = nullptr)
        : ptr_to_curr_node(ptr) {
        }

        // Note that the method is const as this operator does not
        // allow changing of the iterator.
        // Note that it returns T& as it allows changing what it points to.
        // A const_iterator class will return const T&
        // and the method will still be const
        T& operator*() const {
            return ptr_to_curr_node->info;
        }

        T* operator->() const {
            return &(ptr_to_curr_node->info);
        }

        // Prefix increment: ++iterator;
        reverse_level_order_iterator& operator++() {
            //++pointer_to_current_node;
            ptr_to_curr_node = ptr_to_curr_node->m_next;
            return *this;
        }

        // Postfix increment: ++iterator;
        const reverse_level_order_iterator operator++(int) {
            reverse_level_order_iterator tmp = *this;
            ptr_to_curr_node = ptr_to_curr_node->m_next;
            return tmp;
        }

        bool operator==(const reverse_level_order_iterator& rhs) const {
            return ptr_to_curr_node == rhs.ptr_to_curr_node;
        }

        bool operator!=(const reverse_level_order_iterator& rhs) const {
            return ptr_to_curr_node != rhs.ptr_to_curr_node;
        }
    }; // END OF CLASS reverse_level_order_iterator

    class preorder_iterator{
    private:
        Node* ptr_to_curr_node;
    public:
        explicit preorder_iterator(Node* ptr = nullptr)
        : ptr_to_curr_node(ptr) {
        }

        // Note that the method is const as this operator does not
        // allow changing of the iterator.
        // Note that it returns T& as it allows changing what it points to.
        // A const_iterator class will return const T&
        // and the method will still be const
        T& operator*() const {
            return ptr_to_curr_node->info;
        }

        T* operator->() const {
            return &(ptr_to_curr_node->info);
        }

        // Prefix increment: ++iterator;
        preorder_iterator& operator++() {
            //++pointer_to_current_node;
            ptr_to_curr_node = ptr_to_curr_node->m_next;
            return *this;
        }

        // Postfix increment: ++iterator;
        const preorder_iterator operator++(int) {
            preorder_iterator tmp = *this;
            ptr_to_curr_node = ptr_to_curr_node->m_next;
            return tmp;
        }

        bool operator==(const preorder_iterator& rhs) const {
            return ptr_to_curr_node == rhs.ptr_to_curr_node;
        }

        bool operator!=(const preorder_iterator& rhs) const {
            return ptr_to_curr_node != rhs.ptr_to_curr_node;
        }
    }; // END OF CLASS preorder_iterator


};