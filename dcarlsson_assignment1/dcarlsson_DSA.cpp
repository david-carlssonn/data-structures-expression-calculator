#include <cstdio>
#include <climits>
#include "dcarlsson_DSA.h"

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@//
//                                                                   //
//                  ARRAY-BASED STACK IMPLEMENTATION                 //
//                                                                   //
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@//

//Fixed Capacity
//Elements are stored in stack_arr[0...count_arr-1]
//Time Complexity: push/pop are O(1)
//Edge Cases: push on full prints error and pop/top on empty prints error and returns INT_MIN

//========================CONSTRUCTOR===================================
    MyStackArrayType::MyStackArrayType() {
        count_arr = 0;
        popped_val_arr = 0;
        top_val_arr = 0;
    }
//======================================================================

//-------------------------FUNCTIONS------------------------------------
//Push: add item to top of stack and prints error if full.
void MyStackArrayType::push(int data_arr) {
    if(count_arr == SIZE_ARR) {
        printf("ERROR: Array stack is full.\n");
    }
    else {
        stack_arr[count_arr] = data_arr;
        // printf("Pushed: %d\n", data_arr);
        count_arr++;
    }
}
//----------------------------------------------------------------------
//Pop: remove and return the top value. If stack is empty, print error and return INT_MIN sentinel.
int MyStackArrayType::pop() {
    if(count_arr == 0) {
        printf("ERROR: Array stack is empty.\n");
        return INT_MIN;
    }
    else {
        popped_val_arr = stack_arr[count_arr-1];
        // printf("Popped: %d\n", popped_val_arr);
        count_arr--;
        return popped_val_arr;
    }
}
//----------------------------------------------------------------------
//Top: returns top value of stack. If stack is empty, print error and return INT_MIN sentinel.
int MyStackArrayType::top() {
    if(count_arr != 0) {
        top_val_arr = stack_arr[count_arr-1];
        // printf("Top value: %d\n", top_val_arr);
        return top_val_arr;
    }
    else {
        printf("ERROR: No top value (array stack is empty).\n");
        return INT_MIN;
    }
}
//----------------------------------------------------------------------
//Is_Empty: returns true if stack is empty, otherwise it returns false.
bool MyStackArrayType::is_empty() {
    if(count_arr == 0) {
        // printf("TRUE: Array stack is empty.\n");
        return true;
    }
    else {
        // printf("FALSE: Array stack contains values.\n");
        return false;
    }
}
//----------------------------------------------------------------------
//Size: returns stack count.
int MyStackArrayType::size() {
    // printf("Size of array stack: %d\n", count_arr);
    return count_arr;
}
//----------------------------------------------------------------------

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@//
//                                                                   //
//               LINKED-LIST-BASED STACK IMPLEMENTATION              //
//                                                                   //
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@//

//No fixed capacity (until memory runs out)
//Head points to top of stack
//Time Complexity: push/pop are O(1)
//Edge Cases: pop/top on empty prints error and returns INT_MIN
//Copying: deep copy occurs in copy constructor, and operator= handles copy swap via helper function copy_over_stack()

//========================CONSTRUCTOR===================================
    MyStackLinkedListType::MyStackLinkedListType() {
        head = nullptr;
        count_ll = 0;
        popped_val_ll = 0;
        top_val_ll = 0;
    }
//======================================================================

//++++++++++++++++++COPY CONSTRUCTOR & COPY OVER++++++++++++++++++++++++
//                         COPY LOGIC (FOR MY REFERENCE)
//Steps through the source stack to create a deep copy of it and is stored into copy_stack
//In copy_over_stack (a swap), the destination stack pointers/count are stored into a tmp variable,
//so that it can point towards the new deep copy
//Since the deep copy was transferred into the destination stack, the tmp variables addresses get stored in copy_stack
//Now copy_stack points to the old nodes so when the function terminates the destructor is called and deletes the old nodes
//Finally, the desination and source stacks have unique addresses for nodes but retain the same values and structure

MyStackLinkedListType::MyStackLinkedListType(const MyStackLinkedListType& copy_stack) {
    head = nullptr;
    count_ll = 0;

    Node* tail = nullptr;
    Node* curr = copy_stack.head;
    while(curr) {
        Node* newNode = new Node;
        newNode->data_ll = curr->data_ll;
        newNode->next = nullptr;
        if(head == nullptr) {
            head = newNode;
            tail = newNode;
        }
        else {
            tail->next = newNode;
            tail = newNode;
        }
        count_ll++;
        curr = curr->next;
    }
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
MyStackLinkedListType& MyStackLinkedListType::operator=(MyStackLinkedListType copy_stack) {
    copy_over_stack(copy_stack);
    return *this;
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void MyStackLinkedListType::copy_over_stack(MyStackLinkedListType& copy_stack) {
    Node* tmp_copy_ptr;
    int tmp_copy_int;

    tmp_copy_ptr = head;
    head = copy_stack.head;
    copy_stack.head = tmp_copy_ptr;

    tmp_copy_int = count_ll;
    count_ll = copy_stack.count_ll;
    copy_stack.count_ll = tmp_copy_int;

}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//\/\/\/\/\/\/\/\/\/\/\/\/\DESTRUCTOR/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
//Destructor: steps through linked list and deletes each node and updates count to 0.
MyStackLinkedListType::~MyStackLinkedListType() {
    while(head != nullptr) {
        Node* del_node = head;
        head = head->next;
        delete del_node;
    }
    count_ll = 0;
}
//\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/

//-------------------------FUNCTIONS------------------------------------
//Push: add item to top of stack.
void MyStackLinkedListType::push(int data) {
        Node* newNode = new Node;
        newNode->next = head;
        newNode->data_ll = data;
        head = newNode;
        count_ll++;
        // printf("Pushed: %d\n", data);
}
//----------------------------------------------------------------------
//Pop: remove and return the top value. If stack is empty, print error and return INT_MIN sentinel.
int MyStackLinkedListType::pop() {
    Node* prevHead;

    if(count_ll != 0) {
        prevHead = head;
        head = head->next;
        popped_val_ll = prevHead->data_ll;
        delete prevHead;
        count_ll--;
        // printf("Popped: %d\n", popped_val_ll);
        return popped_val_ll;
    }
    else {
        printf("ERROR: LL stack is empty.\n");
        return INT_MIN;
    }
}
//----------------------------------------------------------------------
//Top: returns top value of stack. If stack is empty, print error and return INT_MIN sentinel.
int MyStackLinkedListType::top() {
    if(count_ll != 0) {
        top_val_ll = head->data_ll;
        // printf("Top value: %d\n", top_val_ll);
        return top_val_ll;
    }
    else {
        printf("ERROR: No top value (LL stack is empty).\n");
        return INT_MIN;
    }
}
//----------------------------------------------------------------------
//Is_Empty: returns true if stack is empty, otherwise it returns false.
bool MyStackLinkedListType::is_empty() {
    if(count_ll == 0) {
        // printf("TRUE: LL stack is empty.\n");
        return true;
    }
    else {
        // printf("FALSE: LL stack contains values.\n");
        return false;
    }
}
//----------------------------------------------------------------------
//Size: returns stack count.
int MyStackLinkedListType::size() {
    // printf("Size of LL stack: %d\n", count_ll);
    return count_ll;
}
//----------------------------------------------------------------------

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@//
//                                                                   //
//                  ARRAY-BASED QUEUE IMPLEMENTATION                 //
//                                                                   //
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@//

//Fixed capacity
//head_arr is the index of front while tail_arr is next insert index
//head/tail advance using modulo SIZE_Q_ARR to achieve a circular buffer
//Time Complexity: enqueue/dequeue are O(1)
//Edge Cases: enqueue when full prints error and dequeue/front on empty prints error and returns INT_MIN

//========================CONSTRUCTOR===================================
MyQueueArrayType::MyQueueArrayType() {
    count_q_arr = 0;
    front_val_arr = 0;
    dequeue_val_arr = 0;
    head_arr = 0;
    tail_arr = 0;
}
//======================================================================

//-------------------------FUNCTIONS------------------------------------
//Enqueue: adds item to back of queue and prints error if full.
void MyQueueArrayType::enqueue(int item) {
    if(count_q_arr != SIZE_Q_ARR) {
        queue[tail_arr] = item;
        tail_arr = (tail_arr + 1) % SIZE_Q_ARR; //Wraps index
        count_q_arr++;
        // printf("Enqueued: %d\n", item);
    }
    else {
        printf("ERROR: Array queue is full.\n");
    }
}
//----------------------------------------------------------------------
//Dequeue: removes and returns front of the queue. If queue is empty, print error and return INT_MIN sentinel.
int MyQueueArrayType::dequeue() {
    if(count_q_arr != 0) {
        dequeue_val_arr = queue[head_arr];
        head_arr = (head_arr + 1) % SIZE_Q_ARR; //Wraps index
        count_q_arr--;
        // printf("Dequeued: %d\n", dequeue_val_arr);
        return dequeue_val_arr;
    }
    else {
        printf("ERROR: Array queue is empty.\n");
        return INT_MIN;
    }
}
//----------------------------------------------------------------------
//Front: returns front value of queue. If queue is empty, print error and return INT_MIN sentinel.
int MyQueueArrayType::front() {
    if(count_q_arr != 0) {
        front_val_arr = queue[head_arr];
        // printf("Front value: %d\n", front_val_arr);
        return front_val_arr;
    }
    else {
        printf("ERROR: No front value (array queue is empty).\n");
        return INT_MIN;
    }
}
//----------------------------------------------------------------------
//Is_Empty: returns true if the queue is empty, otherwise it returns false.
bool MyQueueArrayType::is_empty() {
    if(count_q_arr == 0) {
        // printf("TRUE: Array queue is empty.\n");
        return true;
    }
    else {
        // printf("FALSE: Array queue contains values.\n");
        return false;
    }
}
//----------------------------------------------------------------------
//Size: returns queue count.
int MyQueueArrayType::size() {
    // printf("Size of array queue: %d\n", count_q_arr);
    return count_q_arr;
}
//----------------------------------------------------------------------

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@//
//                                                                   //
//               LINKED-LIST-BASED QUEUE IMPLEMENTATION              //
//                                                                   //
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@//

//No fixed capacity (until memory runs out)
//front_ptr points to front and rear points to back of queue
//Time Complexity: enqueue/dequeue are O(1)
//Edge Cases: dequeue/front on empty prints error and returns INT_MIN

//========================CONSTRUCTOR===================================
MyQueueLinkedListType::MyQueueLinkedListType() {
    count_q_ll = 0;
    front_val_ll = 0;
    dequeue_val_ll = 0;
    front_ptr = nullptr;
    rear = nullptr;
}
//======================================================================

//++++++++++++++++++COPY CONSTRUCTOR & COPY OVER++++++++++++++++++++++++
//                         COPY LOGIC (FOR MY REFERENCE)
//Steps through the source queue to create a deep copy of it and is stored into copy_queue
//In copy_over_queue (a swap), the destination queue pointers/count are stored into a tmp variable,
//so that it can point towards the new deep copy
//Since the deep copy was transferred into the destination queue, the tmp variables addresses get stored in copy_queue
//Now copy_queue points to the old nodes so when the function terminates the destructor is called and deletes the old nodes
//Finally, the desination and source queues have unique addresses for nodes but retain the same values and structure

MyQueueLinkedListType::MyQueueLinkedListType(const MyQueueLinkedListType& copy_queue) {
    count_q_ll = 0;
    front_val_ll = 0;
    dequeue_val_ll = 0;
    front_ptr = nullptr;
    rear = nullptr;

    Node* curr = copy_queue.front_ptr;
    while(curr) {
        Node* newNode = new Node;
        newNode->data_q_ll = curr->data_q_ll;
        newNode->next = nullptr;
        if(front_ptr == nullptr) {
            front_ptr = newNode;
            rear = newNode;
        }
        else {
            rear->next = newNode;
            rear = newNode;
        }
        count_q_ll++;
        curr = curr->next;
    }
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
MyQueueLinkedListType& MyQueueLinkedListType::operator=(MyQueueLinkedListType copy_queue) {
    copy_over_queue(copy_queue);
    return *this;
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void MyQueueLinkedListType::copy_over_queue(MyQueueLinkedListType& copy_queue) {
    Node* tmp_copy_ptr;
    int tmp_copy_int;

    tmp_copy_ptr = front_ptr;
    front_ptr = copy_queue.front_ptr;
    copy_queue.front_ptr = tmp_copy_ptr;

    tmp_copy_ptr = rear;
    rear = copy_queue.rear;
    copy_queue.rear = tmp_copy_ptr;

    tmp_copy_int = count_q_ll;
    count_q_ll = copy_queue.count_q_ll;
    copy_queue.count_q_ll = tmp_copy_int;

}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//\/\/\/\/\/\/\/\/\/\/\/\/\DESTRUCTOR/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
MyQueueLinkedListType::~MyQueueLinkedListType() {
    while(front_ptr != nullptr) {
        Node* del_node = front_ptr;
        front_ptr = front_ptr->next;
        delete del_node;
    }
    count_q_ll = 0;
    rear = nullptr;
}
//\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/

//-------------------------FUNCTIONS------------------------------------
//Enqueue: adds item to back of queue.
void MyQueueLinkedListType::enqueue(int item) {
    if(count_q_ll == 0) {
        Node* newNode = new Node;
        newNode->data_q_ll = item;
        newNode->next = nullptr;
        front_ptr = newNode;
        rear = newNode;
        count_q_ll++;
        // printf("Queued: %d\n", rear->data_q_ll);
    }
    else {
        Node* newNode = new Node;
        newNode->data_q_ll = item;
        newNode->next = nullptr;
        rear->next = newNode;
        rear = newNode;
        count_q_ll++;
        // printf("Queued: %d\n", rear->data_q_ll);
    }
}
//----------------------------------------------------------------------
//Dequeue: removes and returns front of the queue. If queue is empty, print error and return INT_MIN sentinel.
int MyQueueLinkedListType::dequeue() {
    Node* prevFront;
    Node* lastNode;

    if(count_q_ll != 0) {
        if(count_q_ll == 1) {
            lastNode = rear;
            dequeue_val_ll = lastNode->data_q_ll;
            delete lastNode;
            front_ptr = nullptr;
            rear = nullptr;
            count_q_ll--;
            // printf("Dequeued: %d\n", dequeue_val_ll);
            return dequeue_val_ll;
        }
        prevFront = front_ptr;
        front_ptr = front_ptr->next;
        dequeue_val_ll = prevFront->data_q_ll;
        delete prevFront;
        count_q_ll--;
        // printf("Dequeued: %d\n", dequeue_val_ll);
        return dequeue_val_ll;
    }
    else {
        printf("ERROR: LL queue is empty.\n");
        return INT_MIN;
    }
}
//----------------------------------------------------------------------
//Front: returns front value of queue. If queue is empty, print error and return INT_MIN sentinel.
int MyQueueLinkedListType::front() {
    if(count_q_ll != 0) {
        front_val_ll = front_ptr->data_q_ll;
        // printf("Front value: %d\n", front_val_ll);
        return front_val_ll;
    }
    else {
        printf("ERROR: No front value (LL queue is empty).\n");
        return INT_MIN;
    }
}
//----------------------------------------------------------------------
//Is_Empty: returns true if the queue is empty, otherwise it returns false.
bool MyQueueLinkedListType::is_empty() {
    if(count_q_ll == 0) {
        // printf("TRUE: LL queue is empty.\n");
        return true;
    }
    else {
        // printf("FALSE: LL queue contains values.\n");
        return false;
    }
}
//----------------------------------------------------------------------
//Size: returns queue count.
int MyQueueLinkedListType::size() {
    // printf("Size of LL queue: %d\n", count_q_ll);
    return count_q_ll;
}
//----------------------------------------------------------------------

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@//
//                                                                   //
//               BINARY SEARCH TREE IMPLEMENTATION                   //
//                                                                   //
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@//

//No fixed capacity (until memory runs out)
//Edge Cases: duplicates are ignored on insert
//Copying: disabled copy contructor and assignment operator

//========================CONSTRUCTOR===================================
MyBinaryTreeType::MyBinaryTreeType() {
    root = nullptr;
}
//======================================================================

//\/\/\/\/\/\/\/\/\/\/\/\/\DESTRUCTOR/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
//Recursive traversal of left and right sub-trees and deletes each node once a nullptr is hit
MyBinaryTreeType::~MyBinaryTreeType() {
    destroy(root);
    root = nullptr;
    // printf("All tree nodes deleted.\n");
}
void MyBinaryTreeType::destroy(Node* node) {
    if(node == nullptr) return;
    else {
        destroy(node->left);
        destroy(node->right);
        // printf("Deleted: %d\n", node->data);
        delete node;
    }
}
//\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/

//-------------------------FUNCTIONS------------------------------------
//Insert: inserts value into BST. Duplicates get ignored (no new node).
void MyBinaryTreeType::insert(int value) {
    if(root == nullptr) {
        Node* newNode = new Node;
        newNode->data = value;
        newNode->left = nullptr;
        newNode->right = nullptr;
        root = newNode;
        // printf("Inserted: %d (ROOT).\n", value);
    }
    else {
        Node* curr = root;
        while(curr != nullptr) {
            if(value == curr->data) {
                // printf("NOTICE: %d already exists in BST.\n", value);
                return;
            }
            else if(value > curr->data) {
                // printf("Inserting... Current Node Data: %d\n", curr->data);
                if(curr->right == nullptr) {
                    Node* newNode = new Node;
                    newNode->data = value;
                    newNode->right = nullptr;
                    newNode->left = nullptr;
                    curr->right = newNode;
                    // printf("Inserted: %d is Right Child of %d.\n", value, curr->data);
                    break;
                }
                curr = curr->right;
            }
            else if(value < curr->data) {
                // printf("Inserting... Current Node Data: %d\n", curr->data);
                if(curr->left == nullptr) {
                    Node* newNode = new Node;
                    newNode->data = value;
                    newNode->right = nullptr;
                    newNode->left = nullptr;
                    curr->left = newNode;
                    // printf("Inserted: %d is Left Child of %d.\n", value, curr->data);
                    break;
                }
                curr = curr->left;
            }
        }
    }
}
//----------------------------------------------------------------------
//Find: returns true if value exists in BST, otherwise returns false.
bool MyBinaryTreeType::find(int value) {
    Node* curr = root;
    while(curr != nullptr) {
        if(value == curr->data) {
            // printf("SUCCESS: %d exists in BST.\n", value);
            return true;
        }
        else if(value > curr->data) {
            curr = curr->right;
        }
        else if(value < curr->data) {
            curr = curr->left;
        }
    }
    // printf("FAIL: %d does not exist in BST.\n", value);
    return false;
}
//----------------------------------------------------------------------
//In_Order_Traversal: prints values in ascending order (LEFT, NODE, RIGHT).
void MyBinaryTreeType::in_order_traversal() {
    printf("In-Order: ");
    in_order_help(root);
    printf("\n");
}
//----------------------------------------------------------------------
//Pre_Order_Traversal: prints values in root -> left -> right order.
void MyBinaryTreeType::pre_order_traversal() {
    printf("Pre-Order: ");
    pre_order_help(root);
    printf("\n");
}
//----------------------------------------------------------------------
//Post_Order_Traversal: prints values in left -> right -> root order.
void MyBinaryTreeType::post_order_traversal() {
    printf("Post-Order: ");
    post_order_help(root);
    printf("\n");
}
//----------------------------------------------------------------------
//In_Order_Help: recursive helper for in_order_traversal (node == nullptr is base case).
void MyBinaryTreeType::in_order_help(Node* node) {
    if(node == nullptr) return;
    else {
        in_order_help(node->left);
        printf("%d ", node->data);
        in_order_help(node->right);
    }
}
//----------------------------------------------------------------------
//Pre_Order_Help: recursive helper for pre_order_traversal (node == nullptr is base case).
void MyBinaryTreeType::pre_order_help(Node* node) {
    if(node == nullptr) return;
    else {
        printf("%d ", node->data);
        pre_order_help(node->left);
        pre_order_help(node->right);
    }
}
//----------------------------------------------------------------------
//Post_Order_Help: recursive helper for post_order_traversal (node == nullptr is base case).
void MyBinaryTreeType::post_order_help(Node* node) {
    if(node == nullptr) return;
    else {
        post_order_help(node->left);
        post_order_help(node->right);
        printf("%d ", node->data);
    }
}
//----------------------------------------------------------------------