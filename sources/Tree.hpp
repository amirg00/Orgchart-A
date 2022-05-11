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
#include "stack"
#include "queue"
#include "string"
using std::queue; using std::stack; using std::string;
//using std::cout; using std::endl; // For debugging - remove it!

template <typename T>
class Tree{
public:
    Tree() : root(nullptr), _size(0) {}

    // Destructor in order to tree class instance.
    // Performs postorder traversal in order to free
    // all the elements without losing a certain element.
    ~Tree(){
        clear_via_postorder(root);
    }

    // Method adds the root with a given value
    void add_root(const T& val) {
        root = new Node(val, nullptr, nullptr, nullptr);
        _size++;
    }

    // Method adds the sub element under the super given element.
    void add_sub(const T& super, const T& sub){
        Node* super_ref = search(super);
        Node* subNode = new Node(sub, nullptr, super_ref, nullptr);
        Node* sub_list = super_ref->sub;

        // New sub element
        if (sub_list == nullptr){
            super_ref->sub = subNode;
            _size++;
            return;
        }

        // O.W
        while(sub_list->next_sib != nullptr){
            sub_list = sub_list->next_sib;
        }
        sub_list->next_sib = subNode;
        _size++;
    }

    // Returns tree's size.
    int size(){
        return _size;
    }

    /* Returns a string in a reasonable format, represents the current tree.
    For example:
       CEO
       |--------|--------|
       CTO      CFO      COO
       |                 |
       VP_SW             VP_BI
    */
    // Note: method performs level order traversal
    // in order to easily return a fair formatted string
    // which represents the string.
    string to_string() const {
        if (root == nullptr) {return "";}
        string tree_str = root->info + "\n";
        Node* it = root;
        queue<Node*> Q;
        Q.push(root);
        while(!Q.empty()){
            Node* curr = Q.front();
            Q.pop();
            it->next = curr;
            it = it->next;
            for (Node* child = curr->sub; child != nullptr; child = child->next_sib) {
                tree_str += child->info + "\t";
                Q.push(child);
            }
            tree_str+="\n";
        }
        return tree_str;
    }

private:
    // Avoid copying
    Tree (const Tree& rhs) = default;
    Tree& operator=(const Tree& rhs) = default;

    // Node inner class
    struct Node{
        T info;                 /* Node's value*/
        Node* parent;           /* Parent's node*/
        Node* sub;              /* Current node's sub-entities list (points to first leftmost sub-entity)*/
        Node* next_sib;         /* Sub-entities' siblings list*/
        Node* next;             /* Next property for iterators*/
        Node(const T& val, Node* node, Node* parNode, Node* sib): info(val), sub(node), parent(parNode), next_sib(sib), next(nullptr) {}
    };

    // Fields
    Node* root;                 /* Tree's root field*/
    int _size;                  /* Tree's nodes amount*/

    // Method finds node by value
    Node* search(const T& val){
        return search(root, val);
    }

    // Auxiliary recursive function for search
    Node* search(Node* ptr, const T& val){
        if (ptr->info == val){ /* Data corresponds the node's data*/
            return ptr;
        }

        Node* subList = ptr->sub;
        while (subList != nullptr){
            Node* currSub = search(subList, val);
            if (currSub != nullptr){
                return currSub;
            }
            subList = subList->next_sib;
        }

        return nullptr;
    }
    //-------------------------------------------------------------------
    // Tree traversals related code:
    // Following methods perform non-binary tree's traversals,
    // then return a linked list using Node class's next_sib property.
    // Those methods are auxiliary methods for the iterators code section
    //-------------------------------------------------------------------

    // Auxiliary function for the class's destructor.
    // Postorder traversal: clears the nodes.
    void clear_via_postorder(Node* ptr) {
        if (ptr == nullptr) {return;}
        clear_via_postorder(ptr->sub);
        clear_via_postorder(ptr->next_sib);
        delete ptr; // deletes visited node
    }

    // Level-order traversal: the inorder traversal in a non-binary tree.
    // Return in the end a linked list for iterations.
    // The returned pointer will be pointer to the head of the linked list.
    static Node* level_order(Node* root){
        if (root == nullptr) {return nullptr;}
        Node* it = root;
        queue<Node*> Q;
        Q.push(root);
        while(!Q.empty()){
            Node* curr = Q.front();
            Q.pop();
            it->next = curr;
            it = it->next;
            for (Node* child = curr->sub; child != nullptr; child = child->next_sib) {
                Q.push(child);
            }
        }
        return root;
    }

    // Reverse-order traversal: the reverse oder of the
    // level-order traversal which can be shown above.
    // Return in the end a linked list for iterations.
    // The returned pointer will be pointer to the head of the linked list.
    static Node* reverse_order(Node* root){
        if (root == nullptr) {return nullptr;}
        Node* levelOrderList = level_order(root);
        Node* reversedList = reverse_linkedList(levelOrderList);
        return reversedList;
    }

    // Function reverse the given linked list.
    static Node* reverse_linkedList(Node* head){
        if (head == nullptr) {return nullptr;}
        Node* prev = nullptr; Node* curr = head; Node* next = nullptr;

        while (curr != nullptr){
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        head = prev;
        return head;
    }

    // Function clears the linked list.
    // Sets all next pointers to nullptr.
    static void clearLinkedList(Node* head){
        if (head == nullptr) {return;}
        clearLinkedList(head->next);
        head->next = nullptr;
    }

    // Preorder traversal: performs the preorder traversal
    // for a non-binary tree.
    // Return in the end a linked list for iterations.
    // The returned pointer will be pointer to the head of the linked list.
    static Node* preorder(Node* root){
        if (root == nullptr) {return nullptr;}

        Node* lst = root;
        stack<Node*> tmpS; // temporary stack to reverse children
        stack<Node*> stack;
        stack.push(root);
        while (!stack.empty()) {
            Node* curr = stack.top();
            stack.pop();
            lst->next = curr;
            lst = lst->next;
            curr->next = nullptr;
            for (Node* child = curr->sub; child != nullptr; child = child->next_sib) {
                tmpS.push(child);
            }
            while(!tmpS.empty()){
                stack.push(tmpS.top());
                tmpS.pop();
            }
        }
        return root;
    }

    //-------------------------------------------------------------------
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
        explicit level_order_iterator(Node* root) {
            clearLinkedList(root);
            ptr_to_curr_node = level_order(root);
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
            ptr_to_curr_node = ptr_to_curr_node->next;
            return *this;
        }

        //        // Postfix increment: iterator++;
        //        const level_order_iterator operator++(int) {
        //            level_order_iterator tmp = *this;
        //            ptr_to_curr_node = ptr_to_curr_node->next;
        //            return tmp;
        //        }

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
        explicit reverse_level_order_iterator(Node* root) {
            clearLinkedList(root);
            ptr_to_curr_node = reverse_order(root);
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
            ptr_to_curr_node = ptr_to_curr_node->next;
            return *this;
        }

        //        // Postfix increment: iterator++;
        //        const reverse_level_order_iterator operator++(int) {
        //            reverse_level_order_iterator tmp = *this;
        //            ptr_to_curr_node = ptr_to_curr_node->next;
        //            return tmp;
        //        }

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
        explicit preorder_iterator(Node* root) {
            clearLinkedList(root);
            ptr_to_curr_node = preorder(root);
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
            ptr_to_curr_node = ptr_to_curr_node->next;
            return *this;
        }

        //        // Postfix increment: ++iterator;
        //        const preorder_iterator operator++(int) {
        //            preorder_iterator tmp = *this;
        //            ptr_to_curr_node = ptr_to_curr_node->next;
        //            return tmp;
        //        }

        bool operator==(const preorder_iterator& rhs) const {
            return ptr_to_curr_node == rhs.ptr_to_curr_node;
        }

        bool operator!=(const preorder_iterator& rhs) const {
            return ptr_to_curr_node != rhs.ptr_to_curr_node;
        }
    }; // END OF CLASS preorder_iterator

    level_order_iterator begin_level_order(){
        return level_order_iterator{root};
    }

    level_order_iterator end_level_order(){
        return level_order_iterator{nullptr};
    }

    reverse_level_order_iterator begin_reverse_order() {
        return reverse_level_order_iterator{root};
    }

    reverse_level_order_iterator end_reverse_order() {
        return reverse_level_order_iterator{nullptr};
    }

    preorder_iterator begin_preorder() {
        return preorder_iterator{root};
    }

    preorder_iterator end_preorder() {
        return preorder_iterator{nullptr};
    }
    //--------------------------------------------------------------------
};