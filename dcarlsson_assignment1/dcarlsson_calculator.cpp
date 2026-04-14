#include "dcarlsson_DSA.h"
#include <cstdio>
#include <math.h>
#include <climits>
#include <cstring>
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@//
//                                                                   //
//                    CALCULATOR IMPLEMENTATION                      //
//                                                                   //
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@//

//--------------------------------------------------CLASS LOGIC (FOR MY FUTURE REFERENCE)--------------------------------------------
//                                                 INFIX LOGIC
//Takes input infix expression and parses the contents (uses shunting algorithm to convert to RPN)
//Accepts single and multi-digit values separating them with spaces to distinguish values
//Else if statements determine operator precedence for pushing to the operator stack or popping to the output (queue)
//A linked list queue was used to hold the rpn expression
//The parsing algorithm also ignores whitespaces and newlines and skips over them
//Once the null terminator on the string is hit, the rest of the operator stack is drained into the queue
//This queue is then dequeued into a pointer to a string that is returned so that the evaluate_rpn function can use it as input
//It also handles negatives, by checking if there is an operand that will be next (after an operator or '(') and my '-' case handles whether it will be a
//normal subtraction or a negative number by subtracting 0.
//In this case '-' has a higher priority since its (represented as a new operator '_') doing 0-X so I want the '_' to be popped after the operand after 0 is received
//                                                  RPN LOGIC
//Since numbers were stored as a character they represented ASCII values so I converted them back to digits by subtracting '0'
//Once the value was converted its pushed to the rpn stack to be used as operands later
//Else if statements trigger calculations to commence only if the operator stack has at least two values to fill the two operands
//The two values are popped and the result is calculated and pushed back to the rpn stack for the rest of the calculations
//Whitespace and newlines are also ignored while parsing in the rpn function
//If a single value is passed through with no operators that is the result, but if there are multiple operands with no operator there will be an error
//--------------------------------------------------------------------------------------------------------------------------------------

class MyCalculator
{ public:
    int evaluate_rpn(const char* expression);
    char* evaluate_infix(const char* expression);
};

//Evaluate_RPN: takes rpn string and calculates and returns result
int MyCalculator::evaluate_rpn(const char* expression) {
    int i = 0;
    int digit = 0;
    int value = 0;
    int operand1 = 0;
    int operand2 = 0;
    int result = 0;

    MyStackLinkedListType rpn_stack;

    while(expression[i] != '\0') {
        if(expression[i] >= '0' && expression[i] <= '9') {
            while(expression[i] != ' ' && expression[i] != '\n' && expression[i] != '\t' && expression[i] >= '0' && expression[i] <= '9') {
                digit = expression[i] - '0';
                value = value*10 + digit;
                i++;
            }
            rpn_stack.push(value);
            value = 0;
            continue;
        }
        else if(expression[i] == '+') {
            if(rpn_stack.size() < 2) { 
                printf("ERROR: Missing operands.\n");
                return INT_MIN;
            }
            operand2 = rpn_stack.pop();
            operand1 = rpn_stack.pop();
            result = operand1 + operand2;
            rpn_stack.push(result);
        }
        else if(expression[i] == '-') {
        //-------NEGATIVE VALUE HANDLING-----
            if((i == 0 || expression[i-1] == ' ' || expression[i-1] == '\t' || expression[i-1] == '\n') && expression[i+1] != '\0' && expression[i+1] >= '0' && expression[i+1] <= '9') {
                i++;
                while(expression[i] != ' ' && expression[i] != '\n' && expression[i] != '\t' && expression[i] >= '0' && expression[i] <= '9') {
                    digit = expression[i] - '0';
                    value = value*10 + digit;
                    i++;
                }
                rpn_stack.push(-value);
                value = 0;
                continue;
            }
        //----------------------------------
            if(rpn_stack.size() < 2) { 
                printf("ERROR: Missing operands.\n");
                return INT_MIN;
            }       
            operand2 = rpn_stack.pop();
            operand1 = rpn_stack.pop();
            result = operand1 - operand2;
            rpn_stack.push(result);
        }
        else if(expression[i] == '_') {
            if(rpn_stack.size() < 2) { 
                printf("ERROR: Missing operands.\n");
                return INT_MIN;
            }       
            operand2 = rpn_stack.pop();
            operand1 = rpn_stack.pop();
            result = operand1 - operand2;
            rpn_stack.push(result);
        }
        else if(expression[i] == '*') {
            if(rpn_stack.size() < 2) { 
                printf("ERROR: Missing operands.\n");
                return INT_MIN;
            }
            operand2 = rpn_stack.pop();
            operand1 = rpn_stack.pop();
            result = operand1 * operand2;
            rpn_stack.push(result);
        }
        else if(expression[i] == '/') {
            if(rpn_stack.size() < 2) { 
                printf("ERROR: Missing operands.\n");
                return INT_MIN;
            }  
            operand2 = rpn_stack.pop();
            if(operand2 == 0) {
                printf("ERROR: Division by 0.\n");
                return INT_MIN;
            }
            operand1 = rpn_stack.pop();
            result = operand1 / operand2;
            rpn_stack.push(result);
        }
        else if(expression[i] == '^') {
            if(rpn_stack.size() < 2) { 
                printf("ERROR: Missing operands.\n");
                return INT_MIN;
            }         
            operand2 = rpn_stack.pop();
            operand1 = rpn_stack.pop();
            result = pow(operand1, operand2);
            rpn_stack.push(result);
        }
        else if(expression[i] == ' ' || expression[i] == '\n' || expression[i] == '\t') {
            i++;
            continue;
        }
        i++;
    }
    if(rpn_stack.is_empty()) {
        printf("ERROR: No result.\n");
        return INT_MIN;
    }
    else if(rpn_stack.size() != 1) {
        printf("ERROR: Several operands left.\n");
        return INT_MIN;
    }
    else {
        result = rpn_stack.pop();
    }
    printf("Result = %d\n", result);
    return result;
}

//Evaluate_INFIX: takes infix string and converts it to RPN for input to evaluate_rpn()
char* MyCalculator::evaluate_infix(const char* expression) {
    int i = 0;
    int k = 0;
    int digit = 0;
    bool operand_next = true;
    MyQueueLinkedListType rpn_queue;
    MyStackLinkedListType operator_stack;
    char temp_op;
    while(expression[i] != '\0') {
        if(expression[i] >= '0' && expression[i] <= '9') {
            while(expression[i] >= '0' && expression[i] <= '9') {
                rpn_queue.enqueue(expression[i]);
                i++;
            }
            rpn_queue.enqueue(' ');
            operand_next = false;
            continue;
        }
        else if(expression[i] == '^') {
            if(operator_stack.is_empty() || operator_stack.top() == '^' || operator_stack.top() == '*' || operator_stack.top() == '/' || operator_stack.top() == '+' || operator_stack.top() == '-' || operator_stack.top() == '(') {
                operator_stack.push('^');
                operand_next = true;
            }
        }
        else if(expression[i] == '*') {
            if(operator_stack.is_empty() || operator_stack.top() == '+' || operator_stack.top() == '-' || operator_stack.top() == '(') {
                operator_stack.push('*');
                operand_next = true;
            }
            else {
                while(!operator_stack.is_empty() && (operator_stack.top() == '^' || operator_stack.top() == '_' || operator_stack.top() == '*' || operator_stack.top() == '/') && operator_stack.top() != '(')  {
                    temp_op = operator_stack.pop();
                    rpn_queue.enqueue(temp_op);
                    rpn_queue.enqueue(' ');
                }
                operator_stack.push('*');
                operand_next = true;
            }
        }
        else if(expression[i] == '/') {
            if(operator_stack.is_empty() || operator_stack.top() == '+' || operator_stack.top() == '-' || operator_stack.top() == '(') {
                operator_stack.push('/');
                operand_next = true;
            }
            else {
                while(!operator_stack.is_empty() && (operator_stack.top() == '^' || operator_stack.top() == '_' || operator_stack.top() == '*' || operator_stack.top() == '/') && operator_stack.top() != '(') {
                    temp_op = operator_stack.pop();
                    rpn_queue.enqueue(temp_op);
                    rpn_queue.enqueue(' ');
                }
                operator_stack.push('/');
                operand_next = true;
            }
        }
        else if(expression[i] == '+') {
            //If a value is = '+x' ignore the +
            if(operand_next) {
                i++;
                continue;
            }
            //--------------------------------
            if(operator_stack.is_empty() || operator_stack.top() == '(') {
                operator_stack.push('+');
                operand_next = true;
            }
            else {
                while(!operator_stack.is_empty() && (operator_stack.top() == '^' || operator_stack.top() == '_' || operator_stack.top() == '*' || operator_stack.top() == '/' || operator_stack.top() == '-' || operator_stack.top() == '+') && operator_stack.top() != '(') {
                    temp_op = operator_stack.pop();
                    rpn_queue.enqueue(temp_op);
                    rpn_queue.enqueue(' ');
                }
                operator_stack.push('+');
                operand_next = true;
            }
        }
        else if(expression[i] == '-') {
            //----NEGATIVE VALUE HANDLING----
            if(operand_next) {
                rpn_queue.enqueue('0');
                rpn_queue.enqueue(' ');
                operator_stack.push('_');
                i++;
                continue;
            }
            //-------------------------------
            else if(operator_stack.is_empty() || operator_stack.top() == '(') {
                operator_stack.push('-');
                operand_next = true;
            }
            else {
                while(!operator_stack.is_empty() && (operator_stack.top() == '^' || operator_stack.top() == '_' || operator_stack.top() == '*' || operator_stack.top() == '/' || operator_stack.top() == '+' || operator_stack.top() == '-') && operator_stack.top() != '(') {
                    temp_op = operator_stack.pop();
                    rpn_queue.enqueue(temp_op);
                    rpn_queue.enqueue(' ');
                }
                operator_stack.push('-');
                operand_next = true;
            }
        }
        else if(expression[i] == '(') {
            operator_stack.push(expression[i]);
            operand_next = true;
        }
        else if(expression[i] == ')') {
            while(!operator_stack.is_empty() && operator_stack.top() != '(') {
                temp_op = operator_stack.pop();
                rpn_queue.enqueue(temp_op);
                rpn_queue.enqueue(' ');
            }
            if(!operator_stack.is_empty() && operator_stack.top() == '(') {
                operator_stack.pop();
            }
            operand_next = false;
        }
        else if(expression[i] == ' ' || expression[i] == '\n' || expression[i] == '\t') {
            i++;
            continue;
        }
        i++;
    }
    while(!operator_stack.is_empty()) {
        temp_op = operator_stack.pop();
        rpn_queue.enqueue(temp_op);
        rpn_queue.enqueue(' ');
    }
    int rpn_size = rpn_queue.size();
    char* rpn_expression = new char[rpn_size+1];
    for(k = 0; k < rpn_size; k++) {
        rpn_expression[k] = rpn_queue.dequeue();
    }
    rpn_expression[rpn_size] = '\0';
    return rpn_expression;
}

//Contains all tests listed on cavas.
void MyTest() {
    {
        printf("-------------------------STACK ARRAY TESTS-------------------------\n");
        MyStackArrayType MyStack;

        //Push a series of at least five integers and print the stack size after each push.
        MyStack.push(24);
        printf("Stack Array Size: %d\n", MyStack.size());
        MyStack.push(18);
        printf("Stack Array Size: %d\n", MyStack.size());
        MyStack.push(13);
        printf("Stack Array Size: %d\n", MyStack.size());
        MyStack.push(5);
        printf("Stack Array Size: %d\n", MyStack.size());
        MyStack.push(2);
        printf("Stack Array Size: %d\n", MyStack.size());

        //Call top() and verify the correct value is returned without modifying the stack.
        printf("Stack Array Top: %d\n", MyStack.top());

        //Pop all items one by one, printing each value and the remaining size.
        printf("Popped: %d\n", MyStack.pop());
        printf("Stack Array Size: %d\n", MyStack.size());

        printf("Popped: %d\n", MyStack.pop());
        printf("Stack Array Size: %d\n", MyStack.size());

        printf("Popped: %d\n", MyStack.pop());
        printf("Stack Array Size: %d\n", MyStack.size());

        printf("Popped: %d\n", MyStack.pop());
        printf("Stack Array Size: %d\n", MyStack.size());

        printf("Popped: %d\n", MyStack.pop());
        printf("Stack Array Size: %d\n", MyStack.size());


        printf("\n=========================Edge Cases=========================\n");
        //pop()/top() on an empty stack.
        MyStack.pop();
        MyStack.top();

        //Push after a full pop cycle
        MyStack.push(1);
        MyStack.push(2);
        MyStack.push(3);

        printf("Stack Array Top: %d\n", MyStack.top());

        printf("Popped: %d\n", MyStack.pop());
        printf("Stack Array Size: %d\n", MyStack.size());

        printf("Popped: %d\n", MyStack.pop());
        printf("Stack Array Size: %d\n", MyStack.size());

        printf("Popped: %d\n", MyStack.pop());
        printf("Stack Array Size: %d\n", MyStack.size());

        printf("------------------------------------------------------------------\n\n\n\n");
    }
    {
        printf("-------------------------STACK LINKED LIST TESTS-------------------------\n");
        MyStackLinkedListType MyStack;

        //Push a series of at least five integers and print the stack size after each push.
        MyStack.push(4);
        printf("Stack Linked List Size: %d\n", MyStack.size());
        MyStack.push(7);
        printf("Stack Linked List Size: %d\n", MyStack.size());
        MyStack.push(12);
        printf("Stack Linked List Size: %d\n", MyStack.size());
        MyStack.push(19);
        printf("Stack Linked List Size: %d\n", MyStack.size());
        MyStack.push(22);
        printf("Stack Linked List Size: %d\n", MyStack.size());

        //Call top() and verify the correct value is returned without modifying the stack.
        printf("Stack Linked List Top: %d\n", MyStack.top());

        //Pop all items one by one, printing each value and the remaining size.
        printf("Popped: %d\n", MyStack.pop());
        printf("Stack Linked List Size: %d\n", MyStack.size());

        printf("Popped: %d\n", MyStack.pop());
        printf("Stack Linked List Size: %d\n", MyStack.size());

        printf("Popped: %d\n", MyStack.pop());
        printf("Stack Linked List Size: %d\n", MyStack.size());

        printf("Popped: %d\n", MyStack.pop());
        printf("Stack Linked List Size: %d\n", MyStack.size());

        printf("Popped: %d\n", MyStack.pop());
        printf("Stack Linked List Size: %d\n", MyStack.size());

        printf("\n=========================Edge Cases=========================\n");
        //pop()/top() on an empty stack.
        MyStack.pop();
        MyStack.top();

        //Push after a full pop cycle
        MyStack.push(10);
        MyStack.push(9);
        MyStack.push(8);

        printf("Stack Linked List Top: %d\n", MyStack.top());

        printf("Popped: %d\n", MyStack.pop());
        printf("Stack Linked List Size: %d\n", MyStack.size());

        printf("Popped: %d\n", MyStack.pop());
        printf("Stack Linked List Size: %d\n", MyStack.size());

        printf("Popped: %d\n", MyStack.pop());
        printf("Stack Linked List Size: %d\n", MyStack.size());

        printf("------------------------------------------------------------------\n\n\n\n");
    }
    {
        printf("-------------------------QUEUE ARRAY TESTS-------------------------\n");
        MyQueueArrayType MyQueue;

        //Enqueue a series of at least five integers, printing size after each operation.
        MyQueue.enqueue(9);
        printf("Queue Array Size: %d\n", MyQueue.size());
        MyQueue.enqueue(13);
        printf("Queue Array Size: %d\n", MyQueue.size());
        MyQueue.enqueue(19);
        printf("Queue Array Size: %d\n", MyQueue.size());
        MyQueue.enqueue(24);
        printf("Queue Array Size: %d\n", MyQueue.size());
        MyQueue.enqueue(31);
        printf("Queue Array Size: %d\n", MyQueue.size());

        //Call front() and verify correctness without dequeuing.
        printf("Queue Array Front: %d\n", MyQueue.front());

        //Dequeue all items, printing each value and remaining size.
        printf("Dequeued: %d\n", MyQueue.dequeue());
        printf("Queue Array Size: %d\n", MyQueue.size());

        printf("Dequeued: %d\n", MyQueue.dequeue());
        printf("Queue Array Size: %d\n", MyQueue.size());

        printf("Dequeued: %d\n", MyQueue.dequeue());
        printf("Queue Array Size: %d\n", MyQueue.size());

        printf("Dequeued: %d\n", MyQueue.dequeue());
        printf("Queue Array Size: %d\n", MyQueue.size());

        printf("Dequeued: %d\n", MyQueue.dequeue());
        printf("Queue Array Size: %d\n", MyQueue.size());

        printf("\n=========================Edge Cases=========================\n");
        //dequeue()/front() on an empty queue.
        MyQueue.dequeue();
        MyQueue.front();

        //Interleaved enqueue/dequeue.
        MyQueue.enqueue(13);
        printf("Queue Array Size: %d\n", MyQueue.size());

        MyQueue.enqueue(9);
        printf("Queue Array Size: %d\n", MyQueue.size());

        printf("Dequeued: %d\n", MyQueue.dequeue());
        printf("Queue Array Size: %d\n", MyQueue.size());

        MyQueue.enqueue(7);
        printf("Queue Array Size: %d\n", MyQueue.size());

        printf("Dequeued: %d\n", MyQueue.dequeue());
        printf("Queue Array Size: %d\n", MyQueue.size());

        MyQueue.enqueue(2);
        printf("Queue Array Size: %d\n", MyQueue.size());

        printf("Dequeued: %d\n", MyQueue.dequeue());
        printf("Queue Array Size: %d\n", MyQueue.size());

        printf("Dequeued: %d\n", MyQueue.dequeue());
        printf("Queue Array Size: %d\n", MyQueue.size());

        printf("------------------------------------------------------------------\n\n\n\n");
    }
    {
        printf("-------------------------QUEUE LINKED LIST TESTS-------------------------\n");
        MyQueueLinkedListType MyQueue;

        //Enqueue a series of at least five integers, printing size after each operation.
        MyQueue.enqueue(100);
        printf("Queue Linked List Size: %d\n", MyQueue.size());
        MyQueue.enqueue(47);
        printf("Queue Linked List Size: %d\n", MyQueue.size());
        MyQueue.enqueue(32);
        printf("Queue Linked List Size: %d\n", MyQueue.size());
        MyQueue.enqueue(26);
        printf("Queue Linked List Size: %d\n", MyQueue.size());
        MyQueue.enqueue(13);
        printf("Queue Linked List Size: %d\n", MyQueue.size());

        //Call front() and verify correctness without dequeuing.
        printf("Queue Linked List Front: %d\n", MyQueue.front());

        //Dequeue all items, printing each value and remaining size.
        printf("Dequeued: %d\n", MyQueue.dequeue());
        printf("Queue Linked List Size: %d\n", MyQueue.size());

        printf("Dequeued: %d\n", MyQueue.dequeue());
        printf("Queue Linked List Size: %d\n", MyQueue.size());

        printf("Dequeued: %d\n", MyQueue.dequeue());
        printf("Queue Linked List Size: %d\n", MyQueue.size());

        printf("Dequeued: %d\n", MyQueue.dequeue());
        printf("Queue Linked List Size: %d\n", MyQueue.size());

        printf("Dequeued: %d\n", MyQueue.dequeue());
        printf("Queue Linked List Size: %d\n", MyQueue.size());

        printf("\n=========================Edge Cases=========================\n");
        //dequeue()/front() on an empty queue.
        MyQueue.dequeue();
        MyQueue.front();

        //Interleaved enqueue/dequeue
        MyQueue.enqueue(9);
        printf("Queue Linked List Size: %d\n", MyQueue.size());

        printf("Dequeued: %d\n", MyQueue.dequeue());
        printf("Queue Linked List Size: %d\n", MyQueue.size());

        MyQueue.enqueue(25);
        printf("Queue Linked List Size: %d\n", MyQueue.size());

        MyQueue.enqueue(48);
        printf("Queue Linked List Size: %d\n", MyQueue.size());

        printf("Dequeued: %d\n", MyQueue.dequeue());
        printf("Queue Linked List Size: %d\n", MyQueue.size());

        MyQueue.enqueue(52);
        printf("Queue Linked List Size: %d\n", MyQueue.size());

        printf("Dequeued: %d\n", MyQueue.dequeue());
        printf("Queue Linked List Size: %d\n", MyQueue.size());

        MyQueue.enqueue(74);
        printf("Queue Linked List Size: %d\n", MyQueue.size());

        printf("Dequeued: %d\n", MyQueue.dequeue());
        printf("Queue Linked List Size: %d\n", MyQueue.size());

        printf("Dequeued: %d\n", MyQueue.dequeue());
        printf("Queue Linked List Size: %d\n", MyQueue.size());

        printf("------------------------------------------------------------------\n\n\n\n");
    }

        printf("-------------------------BINARY TREE TESTS-------------------------\n");
        MyBinaryTreeType MyBinaryTree;

        //Find on an empty tree.
        printf("\nEDGE CASE(Empty Tree Search): Does Value 10 Exist? (True = 1 | False = 0) --> %d\n", MyBinaryTree.find(10));

        //Insert at least seven integers (including duplicates, negative numbers, and values that test the full tree shape).
        MyBinaryTree.insert(20);
        MyBinaryTree.insert(10);
        MyBinaryTree.insert(30);
        MyBinaryTree.insert(-1);
        MyBinaryTree.insert(10); //Insert duplicate values.
        MyBinaryTree.insert(15);
        MyBinaryTree.insert(25);
        MyBinaryTree.insert(35);
        MyBinaryTree.insert(-1); //Insert duplicate values.

        //Search for integers that are present and integers that are absent, printing the result.
        printf("\n=========================Tree Searches (Non-edge case)=========================\n");
        printf("Does Value 10 Exist? (True = 1 | False = 0) --> %d\n", MyBinaryTree.find(10));
        printf("Does Value 80 Exist? (True = 1 | False = 0) --> %d\n", MyBinaryTree.find(80));
        printf("Does Value -1 Exist? (True = 1 | False = 0) --> %d\n", MyBinaryTree.find(-1));
        printf("Does Value 15 Exist? (True = 1 | False = 0) --> %d\n", MyBinaryTree.find(15));
        printf("Does Value 6 Exist? (True = 1 | False = 0) --> %d\n", MyBinaryTree.find(6));
        printf("Does Value 36 Exist? (True = 1 | False = 0) --> %d\n", MyBinaryTree.find(36));

        //Print the results of all three traversals and verify they match expected output.
        MyBinaryTree.in_order_traversal();
        MyBinaryTree.pre_order_traversal();
        MyBinaryTree.post_order_traversal();
        printf("------------------------------------------------------------------\n\n\n\n");

        printf("-------------------------CALCULATOR TESTS-------------------------\n");
        MyCalculator MyCalculator;

        //Simple RPN expressions: single operator (e.g., "3 4 +").
        printf("\nGiven RPN: 3 4 +\n");
        MyCalculator.evaluate_rpn("3 4 +");

        //Multi-operator RPN with all supported operators.
        printf("\nGiven RPN: 5 1 2 + 4 * + 3 - 2 ^ 10 5 / +\n");
        MyCalculator.evaluate_rpn("5 1 2 + 4 * + 3 - 2 ^ 10 5 / +");

        //Simple infix expressions (e.g., "3 + 4").
        printf("\nGiven Infix: 509 + 744\n");
        char* rpn_exp_input = MyCalculator.evaluate_infix("509 + 744");
        MyCalculator.evaluate_rpn(rpn_exp_input);
        delete[] rpn_exp_input;

        //Complex infix with parentheses and right-associative exponentiation (e.g., "3 + 4 * 2 / (1 - 5) ^ 2 ^ 3").
        printf("\nGiven Infix: 3 + 4 * 2 / (1 - 5) ^ 2 ^ 3\n");
        rpn_exp_input = MyCalculator.evaluate_infix("3 + 4 * 2 / (1 - 5) ^ 2 ^ 3");
        MyCalculator.evaluate_rpn(rpn_exp_input);
        delete[] rpn_exp_input;

        printf("\n=========================Edge Cases=========================\n");
        //Division by zero (INFIX).
        printf("\nGiven Infix: 5 / 0\n");
        rpn_exp_input = MyCalculator.evaluate_infix("5 / 0");
        MyCalculator.evaluate_rpn(rpn_exp_input);
        delete[] rpn_exp_input;

        //Division by zero (RPN).
        printf("\nGiven RPN: 1 0 /\n");
        MyCalculator.evaluate_rpn("1 0 /");

        //Single-operand expressions (INFIX).
        printf("\nGiven Infix: 43\n");
        rpn_exp_input = MyCalculator.evaluate_infix("43");
        MyCalculator.evaluate_rpn(rpn_exp_input);
        delete[] rpn_exp_input;

        //Single-operand expressions (RPN).
        printf("\nGiven RPN: 12\n");
        MyCalculator.evaluate_rpn("12");

        //Infix stress test using negative values (-val) and positive values (+val) (Verified answer with desmos using exact division = 9).
        printf("\nGiven Infix: 12/(-3) * -2 + 6/-(1+2) - -7 + 3*-(2+1) + +5\n");
        rpn_exp_input = MyCalculator.evaluate_infix("12/(-3) * -2 + 6/-(1+2) - -7 + 3*-(2+1) + +5");
        MyCalculator.evaluate_rpn(rpn_exp_input);
        delete[] rpn_exp_input;

        //Negative RPN handling.
        printf("\nGiven RPN: 6 -2 /\n");
        MyCalculator.evaluate_rpn("6 -2 /");

}

int main(int argc, char* argv[]) {
    MyTest();
    return 0;
}