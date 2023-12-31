//
// ========================================
// HW10: Implement Binary Tree Traverse 
//       and Data Structure Conversion 
// ========================================
// 
// In this assignment, we will implement four 
// traverse algorithms on a given list-based 
// binary tree, and one function that coverts 
// this tree into an array-based tree. We will 
// also implement a function that measures the 
// height of a list-based tree (for conversion). 
// 
// The binary tree has been constructed for you. 
// It is almost the same as the example tree in 
// lecture, except we use key=0 to indicate empty 
// node. Do not modify it. (We will practice tree 
// class and related operations in future hw's.) 
// 
// You should implement three functions. 
// 
#include <iostream>
#include <cmath>
#include <queue>
using namespace std;

class Node {
private:
	int key;
	Node* left;
	Node* right;
	Node* parent;
public:
	void Set_key(int x);
	int Get_key();
	void Set_left(Node* p);
	void Set_right(Node* p);
	void Set_parent(Node* p);
	Node* Get_left();
	Node* Get_right();
	Node* Get_parent();
	Node();
};
Node::Node() {
	key = 0;
	left = NULL;
	right = NULL;
	parent = NULL;
}
void Node::Set_key(int x) {
	key = x;
}
int Node::Get_key() {
	return key;
}
void Node::Set_left(Node* p) {
	left = p;
}
void Node::Set_right(Node* p) {
	right = p;
}
void Node::Set_parent(Node* p) {
	parent = p;
}
Node* Node::Get_left() {
	return left; 
}
Node* Node::Get_right() {
	return right;
}
Node* Node::Get_parent() {
	return parent;
}


// 
// -------------------------------
// ---------- Task 1 -------------
// -------------------------------
// Please implement the following Traverse 
// function, which can perform pre-order, 
// post-order and in-order traverse as well 
// as breadth-first traverse, depending on 
// the input string "s".
// 
// Input "s" expects value in {"pre","post","in","bf"}
// "pre" means pre-order traverse
// "post" means post-order traverse
// "in" means in-order traverse
// "bf" means breadth-first traverse
// If any other value of "s" is input, 
// just print "-1" (without recursion). 
// 
// Input "p" should point to the node 
// being visited, but you are free to 
// use it in any other way. 
// 
// You don't have to implement the (incomplete) 
// algorithm described in lecture slides. 
// You are welcome to come up with your own 
// design -- as long as they are correct.
// 
// Finally, after visiting every non-empty 
// node, you should print its key value 
// using "cout << p->Get_key();". 
// Do not add space or any other character 
// in the printout. Just print key.
// 
void Traverse(Node* p, string s) {
	//Base Case
	if(p == NULL){
		return;
	}
	//Pre-order traversal
	if(s == "pre"){
		cout << p->Get_key();
		Traverse(p->Get_left(), s);
		Traverse(p->Get_right(), s);
	}
	//Post-order traversal
	else if(s == "post"){
		Traverse(p->Get_left(), s);
        Traverse(p->Get_right(), s);
        cout << p->Get_key();
	}
	// In-order traversal
	else if (s == "in") {
        Traverse(p->Get_left(), s);
        cout << p->Get_key();
        Traverse(p->Get_right(), s);
	}
	// Breadth-first traversal
	else if (s == "bf") {
        queue<Node*> nodeQueue;
        nodeQueue.push(p);

        while (!nodeQueue.empty()) {
            Node* current = nodeQueue.front();
            nodeQueue.pop();

			//Output current key
            cout << current->Get_key();

			//Update current to left if it exsits
            if (current->Get_left()) {
                nodeQueue.push(current->Get_left());
            }
			//Update current to right if it exsits
            if (current->Get_right()) {
                nodeQueue.push(current->Get_right());
            }
        }
	}
	else{
		//If s is invalid
		cout << "-1";
	}
}

// 
// -------------------------------
// ---------- Task 2 -------------
// -------------------------------
// Please implement the following Height
// function, which measures height of a 
// list-based tree. 
// 
// Input "root" points to the root node 
// of the tree. The function returns an 
// integer which is height of the tree. 
// 
// You are free to design any algorithm 
// that measures the height (correctly). 
// You are also welcome to design any 
// additional (recursive) functions 
// that are called by Height. 
//

//Returns the height plus one recursivly
int heightPlusOne(Node* root){
	//Base Case
	if (root == nullptr) {
        return 0; // An empty tree has a height of 0.
    }
	//Recursive call for left
    int leftHeight = heightPlusOne(root->Get_left());
	//Recursive call for right
    int rightHeight = heightPlusOne(root->Get_right());

    // Return leftHeight plus 1 if its bigger, rightHeight + 1 if it is not
    if (leftHeight > rightHeight) return 1 + leftHeight;
 	else return 1 + rightHeight;
}

//Calls height plus one, decrements value, returns result
int Height(Node* root) {
	int height = heightPlusOne(root);
	return --height;
}
// 
// -------------------------------
// ---------- Task 3 -------------
// -------------------------------
// Please implement the following Convert 
// function, which converts a list-based 
// tree into an array-based tree. 
// 
// This function takes two inputs. 
// 1."root" is a pointer to the root node 
//   of the given list-based tree. 
// 2."height" is height of the tree 
//   (returned by your Height function). 
// 
// The function returns a pointer 
// of an object array which holds 
// the tree. 
// 
// -----------------
// --- Important --- 
// ----------------- 
// Size of the array can be determined 
// autmatically based on input height. 
// 
// In fact, the maximum possible number 
// of nodes in a tree is determined by 
// its height. (We will cover this in 
// future lectures.) This means, we 
// can predict the largest necessary 
// size of the array needed to hold 
// all possible nodes in a tree. 
// 
// For now, just follow this rule: 
// ArraySize = 2^(height+1) - 1
// 
// ("2^x" means 2 to the power of x)
// (You can use the "pow" function
// to compute power. See test mode 5 
// as an example.)
// 
Node* Convert2Array(Node* root, int height) {
	//Get array size with given formula
	double arraySizeDouble = pow(2.0, (double)height + 1.0) - 1.0;
	//Convert to int
	int arraySizeInt = (int)arraySizeDouble;
	//Dynamically allocate array with size
	Node* list2Array = new Node[arraySizeInt];
	//Fill array with "empty" nodes
	for(int i = 0; i < arraySizeInt; ++i){
		Node temp;
		list2Array[i].Set_key(temp.Get_key());
		list2Array[i].Set_left(temp.Get_left());
		list2Array[i].Set_right(temp.Get_right());
		list2Array[i].Set_parent(temp.Get_parent());
	}

	//Reuse Breadth-first traversal algorithm for inputting key values
	Node* p = root;

	queue<Node*> nodeQueue;
    nodeQueue.push(p);

	int i = 0;

    while (!nodeQueue.empty()) {
        Node* current = nodeQueue.front();
        nodeQueue.pop();

        list2Array[i].Set_key(current->Get_key());

        if (current->Get_left()) {
            nodeQueue.push(current->Get_left());
        }
        if (current->Get_right()) {
            nodeQueue.push(current->Get_right());
        }
		
		i++;
    }

	return list2Array;
}

// There is nothing you need to do 
// in the main function. 
int main()
{
	// Constructing a binary tree. 
	Node A, B, C, D, E, F, G;
	A.Set_key(5);
	B.Set_key(4);
	C.Set_key(2);
	D.Set_key(11);
	E.Set_key(9);
	F.Set_key(12);
	G.Set_key(7);
	A.Set_left(&B);
	A.Set_right(&C);
	B.Set_left(&D);
	B.Set_right(&E);
	C.Set_left(&F);
	C.Set_right(&G);
	B.Set_parent(&A);
	C.Set_parent(&A);
	D.Set_parent(&B);
	E.Set_parent(&B);
	F.Set_parent(&C);
	G.Set_parent(&C);

	Node* root = &A;

	// Input test mode. 
	int mode;

	cin >> mode;

	// Mode 0: test pre-order traverse
	if (mode == 0) {
		Traverse(root, "pre");
	}
	// Mode 1: test post-order traverse 
	else if (mode == 1) {
		Traverse(root, "post");
	}
	// Mode 2: test in-order traverse 
	else if (mode == 2) {
		Traverse(root, "in");
	}
	// Mode 3: test breadth-first traverse 
	else if (mode == 3) {
		Traverse(root, "bf");
	}
	// Mode 4: test Height function 
	else if (mode == 4) {
		cout << Height(root);
	}
	// Mode 5: test Convert2Array function 
	else if (mode == 5) {
		Node *arr = Convert2Array(root, Height(root));
		for (int i = 0; i < pow(2, Height(root) + 1) - 1; i++) {
			cout << arr[i].Get_key();
		};
	}

	return 0;
}

