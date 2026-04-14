COMPE 496 - Assignment 1
David Carlsson

===============================================
	  BUILD AND RUN INSTRUCTIONS
===============================================
IDE - Built on VS Code using C++ compiler.

Command line -
g++ -g -O0 dcarlsson_DSA.cpp dcarlsson_calculator.cpp -o run
./run

================================================
		     FILES
================================================
- dcarlsson_DSA.h		Class declarations
- dcarlsson_DSA.cpp		Stack/Queue/BST logic
- dcarlsson_calculator.cpp	Calculator/MyTest()/Main()

================================================
		   ASSUMPTIONS
================================================
NOTE: Sentinel value for error return = INT_MIN

Stacks/Queues:
	When Empty:
	-pop(), top(), dequeue(), front() print an error and return INT_MIN.

	When Full (array implementations):
	-push()/enqueue() print an error and do not modify the array.

Binary Search Tree (BST):
	Duplicates:
	-Duplicate inserts are ignored (no new node).

	Traversals:
	-Prints traversals in the required orders.

	Copying:
	-Copy constructor and assignment operator are disabled (stored in private).

Calculator:
	Supported Operators:
	- (+, -, *, /, ^)

	Integer Division:
	-Uses C/C++ integer division (e.g. 3/2 = 1).

	Division By Zero:
	-Prints an error and returns INT_MIN.

	Infix Pointer Return:
	-When calling infix make sure to use delete[] to delete returned pointer for rpn string.

	Negative Value Handling (Infix):
	-A negative value using '-' is converted during infix->RPN conversion into "0 val _". '_' performs subtraction.
	-Used for higher precedence over other operators so the 0-val subtraction can be completed without interference.

	Positive Value Handling (Infix):
	-If a value is entered as +val (e.g +5), the '+' will be ignored.

	Negative Value Handling (RPN):
	-RPN accepts negative values such as -12 when '-' appears at the start of a token and is followed by digits.
	-The start of a token is denoted by any white space before '-' or the index being i == 0.

	Negative Exponentiation:
	-Negative exponents return 0 (base > 1) due to C/C++ integer division (e.g. 2^-3 = 1/8 = 0).

==========================================
	    EXTRA EDGE CASES
==========================================
	Infix stress test using negative values (-val) and positive values (+val) (Verified answer with desmos using exact division = 9):
	-"12/(-3) * -2 + 6/-(1+2) - -7 + 3*-(2+1) + +5"

	Negative RPN handling:
	-"6 -2 /" -> expected result = -3
	
