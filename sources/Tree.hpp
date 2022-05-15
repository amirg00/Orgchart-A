/**
 * <--------- CLASS DESCRIPTION ---------->
 * A template Tree class.
 * Implemented as a doubly linked list.
 *
 * @author Amir Gillette
 * @since 6-5-22
 * ----------------------------------------
 */

#pragma once
#include "stack"
#include "queue"
#include "string"
#include <stdexcept>
using std::queue; using std::stack; using std::string; using std::runtime_error; using std::invalid_argument; using std::ostream;

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
        if(root != nullptr){
            throw invalid_argument("Root already exist!");
        }
        root = new Node(val, nullptr, nullptr, nullptr);
        _size++;
    }

    // Method adds the sub element under the super given element.
    void add_sub(const T& super, const T& sub){
        Node* super_ref = search(super);
        if (super_ref == nullptr){
            throw runtime_error("Superior element cannot be found!");
        }

        Node* subNode = new Node(sub, nullptr, super_ref, nullptr);
        Node* sub_list = super_ref->sub;

        // New sub element
        if (sub_list == nullptr){
            super_ref->sub = subNode;
            super_ref->children_size++;
            _size++;
            return;
        }

        // O.W: add the node as last child
        while(sub_list->next_sib != nullptr){
            sub_list = sub_list->next_sib;
        }
        super_ref->children_size++;
        sub_list->next_sib = subNode;
        _size++;
    }

    // Returns tree's size.
    int size() const{
        return _size;
    }

    /* Puts a string in a reasonable format to the given output stream, which represents the current tree.
    For example:
       CEO
        ├── CTO
        │       └── VP_SW
        ├── CFO
        └── COO
                └── VP_BI
    */
    // Note: method performs level order traversal with recursion,
    // in order to easily return a fair formatted string
    // which visualizes the tree's levels.
    void getTreeVisual(ostream& os) const {
        string tree_str;
        os << root->info << "\n";
        visualSubtree(root, tree_str, os);
    }

    // Avoid copying
    Tree(const Tree &src) = default;
    Tree(Tree&& other) = delete; // move constructor
    Tree& operator=(const Tree& other) = delete; // copy assignment
    Tree& operator=(Tree&& other) = delete ;// move assignment

private:
    // Node inner class
    struct Node{
        T info;                 /* Node's value*/
        int children_size;      /* node's Children amount*/
        Node* parent;           /* Parent's node*/
        Node* sub;              /* Current node's sub-entities list (points to first leftmost sub-entity)*/
        Node* next_sib;         /* Sub-entities' siblings list*/
        Node* next;             /* Next property for iterators*/
        Node(const T& val, Node* node, Node* parNode, Node* sib): info(val), sub(node), parent(parNode), next_sib(sib), next(nullptr), children_size(0) {}
    };

    // Fields
    Node* root;                 /* Tree's root field*/
    int _size;                  /* Tree's nodes amount*/

    // Method finds node by value
    Node* search(const T& val){
        return search(root, val);
    }

    // Auxiliary recursive function for search a node
    // which holds the given value
    Node* search(Node* ptr, const T& val){
        if (ptr->info == val){ /* Data corresponds the node's data*/
            return ptr;
        }
        Node* subList = ptr->sub;
        while (subList != nullptr){
            Node* currSub = search(subList, val);
            if (currSub != nullptr){ /*Return first to be found*/
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
        it->next = nullptr; // override last's next in case such already exist
        return root;
    }

    // Reverse Level-order traversal: uses the same technique as the level order,
    // with reversing the child's insertion order to the queue (right towards left) using stack.
    // Return in the end a linked list for iterations.
    // The returned pointer will be pointer to the head of the linked list.
    static Node* reverse_level_order(Node* root){
        if (root == nullptr) {return nullptr;}
        queue<Node*> Q;
        stack<Node*> S; stack<Node*> tmpS;
        Q.push(root);
        while(!Q.empty()){
            Node* curr = Q.front();
            Q.pop();
            S.push(curr); // Push stack for reverse level order
            for (Node* child = curr->sub; child != nullptr; child = child->next_sib) {
                tmpS.push(child);
            }
            // Insert children in inverse order (right towards left).
            while(!tmpS.empty()){
                Q.push(tmpS.top());
                tmpS.pop();
            }
        }
        // Return a linked list contains the nodes of the traversal
        Node* it = S.top();
        S.pop();
        Node* curr = it;
        while(!S.empty()){
            curr->next = S.top();
            curr = curr->next;
            S.pop();
        }
        curr->next = nullptr; // override last's next in case such already exist
        return it;
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
            curr->next = nullptr; // override next in case such already exist
            for (Node* child = curr->sub; child != nullptr; child = child->next_sib) {
                tmpS.push(child);
            }
            // Reverse child order using the temporary stack
            while(!tmpS.empty()){
                stack.push(tmpS.top());
                tmpS.pop();
            }
        }
        return root;
    }

    // Method performs level order traversal with recursion,
    // in order to easily return a fair formatted string
    // which visualizes the tree's levels.
    void visualSubtree(Node* curr, const string &prefix, ostream& os) const{
        if (curr->children_size == 0) {return;}
        const string soleWorkerSign = "├── "; const string lastWorkerSign = "└── ";
        os << prefix;
        int size = curr->children_size;
        os << (size > 1 ? soleWorkerSign : "");
        int cnt = 0;
        for (Node* child = curr->sub; child != nullptr; child = child->next_sib, cnt++) {
            if (cnt < size - 1) { // It isn't the last child
                if (cnt > 0) {
                    os << prefix << soleWorkerSign;
                }
                bool printStrand = size > 1 && curr->children_size != 0;
                string newPrefix = prefix + (printStrand ? "│\t" : "\t");
                os << child->info << "\n";
                visualSubtree(child, newPrefix, os);
            } else { // Last child
                os << (size > 1 ? prefix : "") << lastWorkerSign;
                os << child->info << "\n";
                visualSubtree(child,prefix + "\t", os);
            }
        }
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
        explicit level_order_iterator(Node* root)
        :ptr_to_curr_node(level_order(root)){
        }

        // Note: the method is const as this operator does not
        // allow changing of the iterator.
        // Note: method returns T& as it allows changing what it points to.
        // A level_order_iterator class will return const T&
        // and the method will still be const.
        T& operator*() const {
            return ptr_to_curr_node->info;
        }

        T* operator->() const {
            return &(ptr_to_curr_node->info);
        }

        // Prefix increment: ++iterator;
        level_order_iterator& operator++() {
            ptr_to_curr_node = ptr_to_curr_node->next;
            return *this;
        }

        // Postfix increment: iterator++;
        level_order_iterator operator++(int) {
            level_order_iterator tmp = *this;
            ptr_to_curr_node = ptr_to_curr_node->next;
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
        explicit reverse_level_order_iterator(Node* root)
        :ptr_to_curr_node(reverse_level_order(root)){
        }

        // Note: the method is const as this operator does not
        // allow changing of the iterator.
        // Note: method returns T& as it allows changing what it points to.
        // A reverse_level_order_iterator class will return const T&
        // and the method will still be const.
        T& operator*() const {
            return ptr_to_curr_node->info;
        }

        T* operator->() const {
            return &(ptr_to_curr_node->info);
        }

        // Prefix increment: ++iterator;
        reverse_level_order_iterator& operator++() {
            ptr_to_curr_node = ptr_to_curr_node->next;
            return *this;
        }

        // Postfix increment: iterator++;
        reverse_level_order_iterator operator++(int) {
            reverse_level_order_iterator tmp = *this;
            ptr_to_curr_node = ptr_to_curr_node->next;
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
        explicit preorder_iterator(Node* root)
        : ptr_to_curr_node(preorder(root)){
        }

        // Note: the method is const as this operator does not
        // allow changing of the iterator.
        // Note: method returns T& as it allows changing what it points to.
        // A preorder_iterator class will return const T&
        // and the method will still be const.
        T& operator*() const {
            return ptr_to_curr_node->info;
        }

        T* operator->() const {
            return &(ptr_to_curr_node->info);
        }

        // Prefix increment: ++iterator;
        preorder_iterator& operator++() {
            ptr_to_curr_node = ptr_to_curr_node->next;
            return *this;
        }

        // Postfix increment: ++iterator;
        preorder_iterator operator++(int) {
            preorder_iterator tmp = *this;
            ptr_to_curr_node = ptr_to_curr_node->next;
            return tmp;
        }

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