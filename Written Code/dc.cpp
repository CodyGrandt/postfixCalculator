#include <iostream>
#include <cstdlib>
#include "stack.h"
#include "dsexceptions.h"

using namespace std;

class InvalidOperator { };

void decipherInput ( Stack<int>& dc , string input );
void operationApplicator ( Stack<int>& dc , char input );
void pushInteger ( Stack<int>& dc , int input );
void operationP ( const Stack<int>& dc );
void operationN ( Stack<int>& dc );
void operationF ( const Stack<int>& dc );
void operationC ( Stack<int>& dc ); 
void operationD ( Stack<int>& dc );
void operationR ( Stack<int>& dc );
void operationPlus ( Stack<int>& dc );
void operationMinus ( Stack<int>& dc );
void operationMultiplication ( Stack<int>& dc );
void operationDivision ( Stack<int>& dc );
void operationRemainder ( Stack<int>& dc );

int main ( ) {

	Stack<int> dc;
	string input;	
	
	do {

		getline ( cin , input );
		decipherInput ( dc , input );


	} while ( cin );	


return 0;
}

void decipherInput ( Stack<int>& dc , string input ) {

	//Pre:   One line has been read from the keyboard and saved into string. 
	//	 That string and Stack dc are passed in as parameters with the goal 
	//	 of deciphering the user input and carrying out the correct commands
	//	 accordingly.
	//Post:  String input which contains the line read from the console is 
	//	 correclty deciphered. A string buildingNum was used to construct 
	//	 numbers pulled from the string input. If a space, an underscore to
	//	 represent a negative number, or an operator was found in the string 
	//	 input, the current buildingNum was converted into a true integer and 
	//	 pushed on the stack, then reset to a blank string.  From there, a new 
	//	 number could be built.  If an operator is found, it is sent to method 
	// 	 operatorApplicator to carry out the specific command.



	
	string buildingNum;	

	for ( int stringPosition = 0 ; stringPosition < input.length() ; stringPosition++ ) {

		if ( isdigit ( input [ stringPosition ] ) ) {
 
			buildingNum += input [ stringPosition ];

		}
		
		else if ( input [ stringPosition ] == '_' ) {

			if ( buildingNum != "" ) {

				int builtNum = atoi ( buildingNum.c_str() );
				pushInteger ( dc , builtNum );
				buildingNum = "";

			}

			if ( isdigit ( input [ stringPosition + 1 ] ) )
				buildingNum += '-';
			
			else 
				pushInteger ( dc , 0 );
					
		}
	
		else if ( isspace ( input [ stringPosition ] ) ) {

			if ( buildingNum != "" ) {

				int builtNum = atoi ( buildingNum.c_str());
				pushInteger ( dc , builtNum );
				buildingNum = "";
			
			}
		
		}
									
		else {
				
			if ( buildingNum != "" ) {

				int builtNum = atoi ( buildingNum.c_str());
				pushInteger ( dc , builtNum );
				buildingNum = "";
			
			}

			operationApplicator ( dc , input [ stringPosition ] );
			
		}
	
	}
		
	if ( buildingNum != "" ) {

		int builtNum = atoi ( buildingNum.c_str());
		pushInteger ( dc , builtNum );
		buildingNum = "";

	}		

}

void operationApplicator ( Stack<int>& dc , char input ) {

	//Pre:   A char representing the desired operation is sent in via parameter
	//	 with the goal of applying the operation to Stack dc.
	//Post:  The correct operation is applied to Stack dc.

	try {
	
		switch ( input ) {

			case 'p' :	operationP ( dc ); 		break;
			case 'n' : 	operationN ( dc );		break;
			case 'f' :	operationF ( dc );		break;
			case 'c' : 	operationC ( dc );		break;
			case 'd' : 	operationD ( dc );		break;
			case 'r' :	operationR ( dc );		break;
			case '+' : 	operationPlus ( dc );		break;
			case '-' : 	operationMinus ( dc ); 		break;
			case '*' : 	operationMultiplication ( dc );	break;
			case '/' : 	operationDivision ( dc );	break;
			case '%' : 	operationRemainder ( dc ); 	break;
			default  : 	throw InvalidOperator ( ); 
		}	
	}	
	catch ( InvalidOperator exc ) {

		cerr << "Exception -- You have entered an invalid expression. Please re-enter." << endl;
	
	}

}

void pushInteger ( Stack<int>& dc , int input ) {

	//Pre:   Stack dc is sent in via parameter.
	//Post:  The user inputted integer is pushed onto the top of the stack.
	
	try {

		dc.push ( input );
	
	}
	catch ( Overflow obj ) {

		cerr << "Illegal Push -- Stack is Full." << endl;
	
	}

}

void operationP ( const Stack<int>& dc )  {

	//Pre:   Stack dc is sent in via parameter.
	//Post:  The value on the top of the stack is printed without altering
	//	 the stack, and a newline is printed after the value.	

	try {

		cout << dc.top() << endl;

	}
	catch ( Underflow obj ) {
	
		cerr << "Illegal Pop -- Stack is Empty." << endl;

	}

}

void operationN ( Stack<int>& dc ) {

	//Pre:   Stack is sent in via parameter.
	//Post:  The top value of the stack is printed, popped, and a 
	//       new line is not printed afterwards.  

	try {

		cout << dc.topAndPop() << "  ";

	}
	catch ( Underflow obj ) {

		cerr << "Illegal Pop -- Stack is Empty." << endl;
	
	}

}

void operationF ( const Stack<int>& dc ) {

	//Pre:   Stack dc is sent in via parameter.
	//Post:  The entire stack dc is printed without altering the stack, 
	//	 and a new line is printed after each value.

	try {
		
		Stack<int> dcCopy = dc;	

		while ( !dcCopy.isEmpty() ) 	
			cout << dcCopy.topAndPop() << endl;

	}
	catch ( Underflow obj ) {

		cerr << "Illegal Pop -- Stack is Empty." << endl;

	}

}	

void operationC ( Stack<int>& dc ) {

	//Pre:   Stack dc is sent in via parameter.
	//Post   The entire stack dc is cleared, rendering it empty.
	
	dc.makeEmpty();
	
}

void operationD ( Stack<int>& dc ) {

	//Pre:   Stack dc is sent in via parameter.
	//post:  The value on top of stack dc is duplicated and pushed back on the
	//	 stack, thereby duplicating the item on the top of the stack.

	try {

		int topValue = dc.top();
		dc.push( topValue );

	}
	catch ( Overflow obj ) {

		cerr << "Illegal Push -- Stack is Full." << endl;

	}
	catch ( Underflow obj ) {

		cerr << "Illegal Pop -- Stack is Empty." << endl;

	}

}

void operationR ( Stack<int>& dc ) {

	//Pre:   Stack dc is sent in via parameter.
	//Post:  The top two values in the stack dc are reversed.

	try {

		int topValue = dc.top();
		dc.pop();
	
		int bottomValue = dc.top();
		dc.pop();
			
		dc.push ( topValue );
		dc.push ( bottomValue );
	
	}	
	catch ( Underflow obj ) {

		cerr << "Illegal Pop -- Stack is Full." << endl;

	}
}

void operationPlus ( Stack<int>& dc ) {

	//Pre:   Stack dc is sent in via parameter.
	//Post:  The top two values on stack dc are popped, added together, and 
	//	 pushed back onto the stack.

	try {

		int topValue = dc.top();
		dc.pop();
		
		int secondValue = dc.top();
		dc.pop();

		int sumOfValues = secondValue + topValue;
		dc.push ( sumOfValues );
	
	}
	catch ( Underflow obj ) {

		cerr << "Illegal Pop -- Stack is Empty." << endl;

	}	


}

void operationMinus ( Stack<int>& dc ) {

	//Pre:   Stack dc is sent in via parameter.
	//Post:  The top two values on stack dc are popped, the first value
	//	 is subtracted from the second value, and the sum is pushed 
	//	 back onto the stack.

	try {

		int topValue = dc.top();
		dc.pop();

		int secondValue = dc.top();
		dc.pop();
	
		int resultOfSubtraction = secondValue - topValue;
		dc.push ( resultOfSubtraction );

	}
	catch ( Underflow Obj ) {

		cerr << "Illegal Pop -- Stack is Empty." << endl;

	}

}

void operationMultiplication ( Stack<int>& dc ) {

	//Pre:   Stack dc is sent in via parameter.
	//Post:  The top two values from the stack are popped, multiplied 
	//	 together, and the result is pushed back onto the stack.
	
	try {
	
		int topValue = dc.top();
		dc.pop();

		int secondValue = dc.top();
		dc.pop();

		int resultOfMultiplication = topValue * secondValue;
		dc.push ( resultOfMultiplication );	

	}
	catch ( Underflow obj ) {

		cerr << "Illegal Pop -- Stack is Empty." << endl;

	}
	
}

void operationDivision ( Stack<int>& dc ) {

	//Pre:   Stack dc is sent in via parameter.
	//Post:  The top two values from stack dc are popped, divides
	//	 the second one popped from the second one popped, and 
	//	 pushes the result.

	try {
	
		int topValue = dc.top();
		
		if ( topValue == 0 )
			throw DivisionByZero();
	
		dc.pop();

		int secondValue = dc.top();
		dc.pop();

		int resultOfDivision = ( secondValue / topValue );
		dc.push ( resultOfDivision );

	}
	catch ( Underflow obj ) {

		cerr << "Illegal Pop -- Stack is Empty" << endl;

	}
	catch ( DivisionByZero exc ) {

		cerr << "Division By Zero Exception -- Stack Unchanged." << endl;

	}

}

void operationRemainder ( Stack<int>& dc ) {

	//Pre:   Stack dc is sent in via parameter.
	//Post:  The top two values of stack dc are popped, the second 
	//	 one is divided by the first, and the remainder of this 
	//	 is pushed back onto the stack.

	try {	
	
		int topValue = dc.top();

		if ( topValue == 0 )
			throw DivisionByZero();

		dc.pop();

		int secondValue = dc.top();
		dc.pop();
		
		int remainder = ( secondValue % topValue );
		dc.push ( remainder );

	}
	catch ( Underflow obj ) {

		cerr << "Illegal Pop -- Stack is Empty" << endl;

	}
	catch ( DivisionByZero exc ) {

		cerr << "Division By Zero Exception -- Stack Unchanged." << endl;

	}
}
