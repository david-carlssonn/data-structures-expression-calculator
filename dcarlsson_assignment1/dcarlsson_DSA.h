static const int SIZE_SQ = 4096;
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@//
//                                                                   //
//                  ARRAY-BASED STACK IMPLEMENTATION                 //
//                                                                   //
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@//

//---------CLASS LOGIC (FOR MY FUTURE REFERENCE)----------
//Fixed size array that increments index with each push
//Decrements index for overriding with each pop
//--------------------------------------------------------

class MyStackArrayType
{ public:
    void push(int data);
    int pop();
    int top();
    bool is_empty();
    int size();

    MyStackArrayType();

    private:
        static const int SIZE_ARR = SIZE_SQ;
        int stack_arr[SIZE_ARR];
        int count_arr;
        int popped_val_arr;
        int top_val_arr;

};

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@//
//                                                                   //
//               LINKED-LIST-BASED STACK IMPLEMENTATION              //
//                                                                   //
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@//

//-----------------------------CLASS LOGIC (FOR MY FUTURE REFERENCE)-----------------------------------
//Uses head ptr to keep track of top of stack
//                          PUSH MECHANICS
//When a new value is pushed, head gets the address of the new node
//The next pointer of the new node points to the previous head before its updated
//                          POP MECHANICS
//When a value is popped, the head's current address gets stored in a temp pointer
//Then the new head's address is assigned head's next pointer (last value pushed before current head)
//Deleting the temp pointer gets rid of the old head since it doesnt point to anything anymore
//-----------------------------------------------------------------------------------------------------

class MyStackLinkedListType
{ public:
    void push(int data);
    int pop();
    int top();
    bool is_empty();
    int size();

    MyStackLinkedListType();
    ~MyStackLinkedListType();
    MyStackLinkedListType(const MyStackLinkedListType& copy_stack);
    MyStackLinkedListType& operator=(MyStackLinkedListType copy_stack);

    void copy_over_stack(MyStackLinkedListType& copy_stack);

    private:
        int count_ll;
        int popped_val_ll;
        int top_val_ll;

        typedef struct Node {
            int data_ll;
            struct Node* next;
        } Node;
        Node* head;
};

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@//
//                                                                   //
//                  ARRAY-BASED QUEUE IMPLEMENTATION                 //
//                                                                   //
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@//

//---------------------------------------CLASS LOGIC (FOR MY FUTURE REFERENCE)------------------------------------------------
//Uses a head variable to keep track of front of queue for dequeuing and peeking.
//Uses a tail variable to keep track of where new value will be queued.
//Modulus is used for wrapping the head/tail value to keep it within bounds of SIZE (circular array).
//Enqueue Logic: Value that is queued is always placed at the current index of tail.
//               The tail index is incremented after a value is enqueued to point to the next empty space.
//Dequeue Logic: Value that is dequeued isn't removed from the array itself but the head increments so that /
//               It points to the next value in the queue, and the old value has the potential to be overwritten by the tail.
//-----------------------------------------------------------------------------------------------------------------------------

class MyQueueArrayType
{ public:
    void enqueue(int item);
    int dequeue();
    int front();
    bool is_empty();
    int size();

    MyQueueArrayType();

    private:
        static const int SIZE_Q_ARR = SIZE_SQ;
        int queue[SIZE_Q_ARR];
        int count_q_arr;
        int front_val_arr;
        int dequeue_val_arr;
        int head_arr;
        int tail_arr;
};

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@//
//                                                                   //
//               LINKED-LIST-BASED QUEUE IMPLEMENTATION              //
//                                                                   //
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@//

//---------------------------------CLASS LOGIC (FOR MY FUTURE REFERENCE)-----------------------------------------
//Uses front_ptr and rear to keep track of the beginning and end of the queue
//                          ENQUEUE LOGIC
//If the queue is empty a new node is made that ends up being both the front and rear.
//Any value thats enqueued after the first node has rear's next pointer updated to /
//the new node to create a chain and after that rear points to the new node added.
//After each added node the queue count increments.
//                          DEQUEUE LOGIC
//If the queue contains elements, the front_ptr is stored into a temp ptr.
//front_ptr updates its pointer to the next value after the front.
//Since the old pointer for the front is in a temp variable it can be deallocated properly.
//The queue count is then decremented.
//If there is only one node remaining, the rear pointer gets stored into a temp ptr.
//This allows for proper deallocation of the last node and both the front_ptr and rear pointers get set to null.
//The queue count decrements to 0.
//---------------------------------------------------------------------------------------------------------------

class MyQueueLinkedListType
{ public:
    void enqueue(int item);
    int dequeue();
    int front();
    bool is_empty();
    int size();

    MyQueueLinkedListType();
    ~MyQueueLinkedListType();
    MyQueueLinkedListType(const MyQueueLinkedListType& copy_queue);
    MyQueueLinkedListType& operator=(MyQueueLinkedListType copy_queue);

    void copy_over_queue(MyQueueLinkedListType& copy_queue);

    private:
        int count_q_ll;
        int front_val_ll;
        int dequeue_val_ll;

        typedef struct Node {
            int data_q_ll;
            struct Node* next;
        } Node;

        Node* front_ptr;
        Node* rear;
};


//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@//
//                                                                   //
//               BINARY SEARCH TREE IMPLEMENTATION                   //
//                                                                   //
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@//

//--------------------------------------------------CLASS LOGIC (FOR MY FUTURE REFERENCE)---------------------------------------------
//Has a root pointer to keep track of the first element inserted into the tree.
//                              INSERT LOGIC
//If root is nullptr (tree is empty), then the root is created and the children are set to nullptr.
//After this, there is a while loop that checks if the current node exists yet or not.
//For each run through the current node starts at the root of the tree.
//In this loop, the value that is being inserted is compared to the current nodes value.
//If the value already exists in the tree it is ignored.
//If the value is greater than the current node's value, then it moves down to the right child of the current node.
//If the value is less than the current node's value, then it moves down to the left child of the current node.
//This happens until one of the children of the current node doesn't exist and that is where the new node is placed.
//                              FIND LOGIC
//Similar logic to insert but instead of creating a new node, 
//in each iteration of the loop it compares the value with the current node's value.
//If the value is greater it goes to the right child and if its less it goes to the left child.
//This happens until the value is found in the tree or until a nullptr is hit (it doesnt exist in tree).
//                              TRAVERSAL LOGIC
//Each traversal uses a helper function, so that the current node can be passed through as an argument.
//Depending on the order, the function will do a recursive call left/right or printing of the current node.
//Base Case: (node == nullptr)
//In-Order: Recursively traverses left subtree from root, visits (prints) the node, and recursively traverses the right subtree.
//Pre-Order: Prints current node first, then recursively traverses the left subtree, then recursively traverses the right.
//Post-Order: Recursively traverses the left subtree, then recursively taverses the right, and prints the node after.
//----------------------------------------------------------------------------------------------------------------------------------

class MyBinaryTreeType
{ public:
    void insert(int value);
    bool find(int value);
    void in_order_traversal();
    void pre_order_traversal();
    void post_order_traversal();

    MyBinaryTreeType();
    ~MyBinaryTreeType();

    private:
        typedef struct Node {
            int data;
            struct Node* right;
            struct Node* left;
        } Node;

        Node* root;
        void in_order_help(Node* node);
        void pre_order_help(Node* node);
        void post_order_help(Node* node);
        void destroy(Node* node);
        //Placed assignment operator and copy constructor in private
        //to disable copying of binary tree obj to another
        MyBinaryTreeType(const MyBinaryTreeType& copy_tree);
        MyBinaryTreeType& operator=(MyBinaryTreeType copy_tree);
};