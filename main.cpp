//Author Joel Woeste
//Last Modified 10/01/2024

//Need to make all GatorID into strings!!!

#include <iostream>
#include <string>
#include <stack>
#include <queue>
#include <regex>

using namespace std;

//Initialize Tree-Node as StudentTree

class StudentTree{
public:
    string name;
    string gatorID;
    int depth;


    StudentTree* left;      //Student Tree Object to the "left"
    StudentTree* right;     //Student Tree Object to the "right" (These work together to make an easy traversal that can go up or down depending on if it has reached the end of a branch)

    StudentTree(string name, string gatorID){
        this->name = name;                  //Initialize Student Object
        this->gatorID = gatorID;
        left = right = nullptr;             //Set Both Left & Right Side to Nullptr
        depth = 1;
    }
};


class AVL_Tree{
public:
    StudentTree* root;         //Initialize StudentTree Object root

    //need a height or balance attribute to track how many values are on each side.
    //balance should work by counting the furthest most down
    //child values and subtracting to see if they equal 0, if not it needs to adjust.

    AVL_Tree(){
        root = nullptr;     // Empty Tree Initialization
    }

    //Build a Recursive Height Calculator

    //Recursive Insert Function
    StudentTree* insert(StudentTree* node, string name, string gatorID, bool iscalled){


        if(gatorID.size() != 8){
            if(iscalled) {
                cout << "unsuccessful" << endl;
            }
            return node;
        }

        // Check for duplicates by traversing the entire tree
        StudentTree* currNode = node;
        stack<StudentTree*> stack; // Stack for in-order traversal

        while (currNode != nullptr || !stack.empty()) {
            while (currNode != nullptr) {
                stack.push(currNode);
                currNode = currNode->left;
            }
            currNode = stack.top();
            stack.pop();

            if (currNode->gatorID == gatorID) {
                cout << "unsuccessful" << endl;
                return node;
            }
            currNode = currNode->right;
        }


        if(node == nullptr){
            if(iscalled) {
                cout << "successful" << endl;               // Node is the current Node in the Tree, Newly Created Node Will be placed somewhere below this forking node.
            }
            return new StudentTree(name, gatorID);      //If StudentTree current node is nullptr, it adds the data value; this means also that the starting "root" is the first value added, and therefore the first node.
        }

        if(gatorID == node->gatorID){
            if(iscalled) {
                cout << "unsuccessful" << endl;
            }
            return node;
        }


        //If Original Nodes GatorID is Greater Than New Node (one you're adding), place it to the left of the Original Node. NewNode < CurrNode.
        if(gatorID < node->gatorID){
            node->left = insert(node->left,name,gatorID,false); //Recursively calls itself until the value at the node is nullptr.
        }
        //If Original Nodes GatorID is Less Than New Node (one you're adding), place it to the right of the Original Node. NewNode > CurrNode.
        if(gatorID > node->gatorID){
            node->right = insert(node->right,name,gatorID,false); //DIDO
        }

        //Updates Depth As Insert Adds.
        updateDepth(node);
        if(iscalled) {
            cout << "successful" << endl;
        }
        return balanceStudentTree(node);
        //This checks if tree is balanced and rebalances it every time it inserts if the tree becomes unbalanced.
    }

    void insert(string name, string gatorID){
        root = insert(root,name,gatorID,true);    //Recursive StudentTree Insert Function; root/node tells which node to insert new data at
    }

    //Recursive Depth Check
    int depth(StudentTree* node) {
        if (node == nullptr) {
            return 0;
        }
        else{
            return node->depth;
        }
    }

    //Update Depth/Height Function for node Location
    void updateDepth(StudentTree* node) {
        if (node != nullptr) {
            node->depth = 1 + max(depth(node->left), depth(node->right));
        }
    }

    int getBF(StudentTree* node) {
        if (node != nullptr) {
            int leftDepth = depth(node->left);
            int rightDepth = depth(node->right);
            int balanceFactor = leftDepth - rightDepth;
            //cout << "Balance Factor (Left - Right): " << balanceFactor << endl;
            return balanceFactor;
        } else {
            //cout << "The tree is empty." << endl;
            return 0;
        }
    }


    StudentTree* balanceStudentTree(StudentTree* node) {
        int bf = getBF(node);

        // Left Side Leaning
        if(bf > 1) {
            if(getBF(node->left) < 0) {
                node->left = rotateLeft(node->left); //Makes a Left Rotation on Child Class to rebalance child class subtree that is currently right leaning (LR Rotation)
            }
            return rotateRight(node);                     //Makes A Right Rotation to rebalance Tree
        }

        //Right Side Leaning
        if(bf < -1) {
            if(getBF(node->right) > 0) {
                node->right = rotateRight(node->right); //Makes a Right Rotation on Child Class to rebalance child class subtree that is currently left leaning (RL Rotation)
            }
            return rotateLeft(node);                         //Makes a Left Rotation to rebalance Tree
        }

        return node;
    }


    //Moves Node to Right of New "swap" Root Node
    StudentTree* rotateRight(StudentTree* node){
        StudentTree* swapRoot = node->left; //Set equal to left node
        node->left = swapRoot->right;       //The left node is set equal to the right of swapRoot
        swapRoot->right = node;             //The right value of swapRoot is set to be the node
        updateDepth(node);                  //Must Update Depth Accordingly
        updateDepth(swapRoot);
        return swapRoot;
    }


    //Moves Node to Left of New "swap" Root Node
    StudentTree* rotateLeft(StudentTree* node){
        StudentTree* swapRoot = node->right;    //Dido Everything Above
        node->right = swapRoot->left;
        swapRoot->left = node;
        updateDepth(node);
        updateDepth(swapRoot);
        return swapRoot;
    }


    //Recrusive Remove - Similar Sifting Function to Insert
    StudentTree* remove(StudentTree* node, string gatorID, bool iscalled){

        if(node == nullptr) {               //Could Not Find Node
            if(iscalled) {
                cout << "unsuccessful" << endl;
            }
            return nullptr;
        }

        StudentTree* currNode = node;
        stack<StudentTree*> stack;
        bool idExists = false;

        while (currNode != nullptr || !stack.empty()) {
            while (currNode != nullptr) {
                stack.push(currNode);
                currNode = currNode->left;
            }
            currNode = stack.top();
            stack.pop();

            if (currNode->gatorID == gatorID) {
                idExists = true;
                break;
            }
            currNode = currNode->right;
        }


        if (!idExists) {
            if (iscalled) {
                cout << "unsuccessful" << endl;
            }
            return node;
        }


        //If Original Nodes GatorID is Greater Than New Node (one you're adding), place it to the left of the Original Node. NewNode < CurrNode.
        if(stoi(gatorID) < stoi(node->gatorID)){
            node->left = remove(node->left,gatorID,false); //Recursively calls itself until the value at the node is nullptr.
        }
        //If Original Nodes GatorID is Less Than New Node (one you're adding), place it to the right of the Original Node. NewNode > CurrNode.
        if(stoi(gatorID) > stoi(node->gatorID)){
            node->right = remove(node->right,gatorID,false); //DIDO
        }

        if(stoi(gatorID) == stoi(node->gatorID)){
            /* if(iscalled) {
                cout << "successful" << endl;
            } */

            //If there are no children of the node:
            if(node->left == nullptr && node->right == nullptr){
                return nullptr;
            }

            //Node has one child (either side)
            if(node->left == nullptr){
                return node->right;                 //Set Node to Child
            }
            if(node->right == nullptr){
                return node->left;
            }

            //Node has two children
            StudentTree* newParent = node->right;
            while(newParent->left != nullptr) {
                newParent = newParent->left;        //Go Furthest Left inside Right Child Class
            }
            node->gatorID = newParent->gatorID;     //replace current node values
            node->name = newParent->name;
            //remove the newParent node from right sub-tree
            node->right = remove(node->right,newParent->gatorID,false);

        }
        if (iscalled) {
            cout << "successful" << endl;
        }
        updateDepth(node);
        return balanceStudentTree(node);
    }

    //Remove MANUAL Call
    void remove(string gatorID){
        root = remove(root,gatorID,true);
    }

    //Non-Recursive searchName - Mostly Wanted to Just Try it This Way, Honestly Was More of A Hassle to do it this way.
    void searchName(string findName) {
        // Unlike Recursive Calls, this should start at root always, and does not need a call, should end when it finds value.
        StudentTree *currNode = root;
        bool nameExist = false;
        stack<StudentTree*> stack; //Stack to Allow for In-Order Traversal

        while (currNode != nullptr || !stack.empty()) {
            while (currNode != nullptr) {
                stack.push(currNode);
                currNode = currNode->left;
            }
            currNode = stack.top();
            stack.pop();

            if (currNode->name == findName) {
                cout << currNode->gatorID << endl;
                nameExist = true;
            }
            currNode = currNode->right;
        }
        if(nameExist == false){
            cout << "unsuccessful" << endl;
        }
    }

    //Non-Recursive searchID
    void searchID(string testID){
        StudentTree *currNode = root;
        bool idExist = false;
        stack<StudentTree*> stack; //Stack to Allow For In-Order Traversal

        while (currNode != nullptr || !stack.empty()) {
            while (currNode != nullptr) {
                stack.push(currNode);
                currNode = currNode->left;
            }
            currNode = stack.top();
            stack.pop();

            if(currNode->gatorID == testID) {
                cout << currNode->name << endl;
                idExist = true;
            }
            currNode = currNode->right;
        }
        if(idExist == false){
            cout << "unsuccessful" << endl;
        }
    }

    //Recursive printInorder Function, called Each Time
    void printInorder(StudentTree* node,string &output){
        if(node != nullptr){
            printInorder(node->left,output); //Function Calls Itself To Look at Node Left of Root
            if (!output.empty()) {
                output += ", ";
            }
            output += node->name;
            printInorder(node->right,output); //Function Calls Itself To Look at Node Right of Root
        }
        //The smallest value in the current node’s right subtree (useful for coding this project)
    }

    //Start call of printInorder Function, called once, starting from the root/top value.
    void printInorder(){
        string output;
        printInorder(root,output);   //recursively call print in order starting from root   //recursively call print in order starting from root
        cout << output << "\n";
    }


    //Recursive printPreorder
    void printPreorder(StudentTree* node, string &output){
        if(node != nullptr){
            if (!output.empty()) {
                output += ", ";
            }
            output += node->name;
            printPreorder(node->left,output); //Function Calls Itself To Look at Node Left of Root
            printPreorder(node->right,output); //Function Calls Itself To Look at Node Right of Root
        }
        //The smallest value in the current node’s right subtree (useful for coding this project)
    }

    void printPreorder(){
        string output;
        printPreorder(root,output);   //recursively call print in order starting from root
        cout << output << "\n";
    }

    //Recursive printPostorder
    void printPostorder(StudentTree* node, string &output){
        if(node != nullptr){
            printPostorder(node->left,output); //Function Calls Itself To Look at Node Left of Root
            printPostorder(node->right,output); //Function Calls Itself To Look at Node Right of Root
            if (!output.empty()) {
                output += ", ";
            }
            output += node->name;
        }
    }

    void printPostorder(){
        string output;
        printPostorder(root,output);   //recursively call print post order starting from root
        cout << output << "\n";
    }

    //Recursive printLevelCount - See How Many Levels There Are in The Tree.
    void printLevelCount(StudentTree* node){

        queue<StudentTree*> queue;
        queue.push(node);
        int level = 0;

        if(node == nullptr){
            cout << 0 << endl;
            return;
        }

        while(!queue.empty()) {
            int lvlSize = queue.size();

            for(int i = 0; i < lvlSize; i++) {
                StudentTree *currNode = queue.front();
                queue.pop();


                if(currNode->left != nullptr){
                    queue.push(currNode->left);
                }
                if(currNode->right != nullptr){
                    queue.push(currNode->right);
                }

            }

            level += 1;
        }
        cout << level << endl;
    }

    //Recursive printLevelCount
    void printLevelCount(){
        printLevelCount(root);
    }

    //Recursive removeInorder - Remove the Nth term in an inorder traversal
    bool removeInorder(StudentTree* node, int &nodePosition, int N){
        if(node == nullptr){
            return false;
        }

        if(removeInorder(node->left,nodePosition,N)){
            return true;
        }

        if(nodePosition == N){
            root = remove(root,node->gatorID,false);
            cout << "successful" << endl;
            return true;
        }
        nodePosition += 1;

        return removeInorder(node->right, nodePosition, N);
        //The smallest value in the current node’s right subtree (useful for coding this project)
    }

    void removeInorder(int N){
        int nodePosition = 0;
        if(!removeInorder(root,nodePosition,N)){
            cout << "unsuccessful" << endl;
        }
    }
};

bool isNum(const string& str) {
    regex pattern("^\\d+$");
    return regex_match(str, pattern);
}

bool isName(const string& name) {
    regex pattern("^[A-Za-z\\s]+$");
    return regex_match(name, pattern);
}

string removeQuotation(string& input) {
    if (input.find('"') == string::npos && input.find('\'') == string::npos) {
        return input; // Return the original input if no quotations are found
    }

    string result;
    for (char n : input) {
        if (n != '"' && n != '\'') {
            result += n;
        }
    }
    return result;
}

int main(){
    AVL_Tree tree;

//    tree.insert("Brandon",45679999);
//    tree.insert("Brian",35459999);
//    tree.insert("Briana",87879999);
//    tree.insert("Bella",95469999);
//    tree.printInorder();
//    tree.remove(45679999);
//    tree.removeInorder(2);
//    tree.printInorder();

    //cout << "Hello AVL!\n";

    //cout << "\n";

    int total = 0;
    int count = 0;
    string input;

    getline(cin, input);
    if (!input.empty()) {
        try {
            total = stoi(input);
        } catch (const invalid_argument&) {
            cout << "unsuccessful" << endl;
            return 1;
        }
    }

    while (count < total) {
        getline(cin, input);
        if (input.empty()) {
            cout << "unsuccessful" << endl;
            continue;
        }

        stringstream ss(input);
        string command;
        ss >> command;

        if (command == "insert") {
            string quotedName;
            string gatorID;

            getline(ss, quotedName, '"');
            getline(ss, quotedName, '"');


            if (!(ss >> gatorID)) {
                continue;
            }
            string name = removeQuotation(quotedName);
            bool isValidname = true;
            bool isValidID = true;

            if(gatorID.size() != 8){
                isValidID = false;
            }

            for (int i = 0; i < static_cast<int>(name.size()); i++) {
                if (!isalpha(name[i]) && !isspace(name[i])) {       //This was causing me trouble.
                    isValidname = false;
                }
            }

            if (isValidname == true && isValidID == true) {
                tree.insert(name, gatorID);
            } else {
                cout << "unsuccessful" << endl;
            }

        }else if (command == "remove") {
            string gatorID;
            if (ss >> gatorID) {

                if(gatorID.size() != 8){
                    cout << "unsuccessful" << endl;
                } else {
                    tree.remove(gatorID);
                }
            }else{
                cout << "unsuccessful" << endl;
            }
        } else if (command == "search") {
            string quotedSearch;
            if (ss >> quotedSearch) {
                string search = removeQuotation(quotedSearch);
                if (isNum(search)) {
                    string gatorID = search;
                    tree.searchID(gatorID);
                } else if (isName(search)) {
                    tree.searchName(search);
                } else {
                    cout << "unsuccessful" << endl;
                }
            }
        }else if (command == "printInorder") {
            tree.printInorder();
        }else if (command == "printPreorder") {
            tree.printPreorder();
        }else if (command == "printPostorder") {
            tree.printPostorder();
        }else if (command == "printLevelCount") {
            tree.printLevelCount();
        }else if (command == "removeInorder") {
            int N;
            if (ss >> N) {
                tree.removeInorder(N);
            } else {
                cout << "unsuccessful" << endl;
            }
        } else {
            cout << "unsuccessful" << endl;
        }
        count++;
    }
    return 0;
}