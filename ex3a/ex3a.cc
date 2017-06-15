/*----------------------------------------------------------------------------*/
/******************************************************************************
 ** Created by @author Omer Schwartz

               @email 23know.one(2).omer at gm(a)il d.o.t.com

        ## See ID and login on README file attached! ##

   This Program

 ******************************************************************************/
/*--------------------------- Include Section --------------------------------*/
#include <iostream>
#ifndef EXIT_FAILURE
#include <cstdlib>
#endif
/*--------------------------- Using Section ----------------------------------*/
using std::cin;
using std::cout;
using std::cerr;
using std::endl;
/*--------------------------- Type Definition --------------------------------*/
struct Node {
    int _data ;
    struct Node *_left, *_right ;
};

typedef struct{

    struct Node* _root;

}Tree;

/*------------------------- Function Declaration -----------------------------*/
/*-------------------------- Private  Function -------------------------------*/
/**
 *
 * @param tree
 */
void    getUserValues(Tree* tree);

/**
 *
 * @param value
 * @return
 */
Node*   createNewNode(const int value);

/**
 *
 * @param node
 * @param toAdd
 */
void    nodeAdd(Node* node, Node* const toAdd);

/**
 *
 * @param node
 */
void    nodeDelete(Node* node);
//DEBUG
void    debugTreePrint(const Node* node);
/*--------------------------- Public  Function -------------------------------*/
/**
 *
 * @return
 */
Tree*   treeCreate();

/**
 *
 * @param tree
 * @param value
 */
void    treeAdd(Tree* tree, const int value);

/**
 *
 * @param root
 */
void    printTreeLeaves(const Node* root);

/**
 *
 * @param tree
 */
void    printMinimumTreeValue(const Tree *const tree);

/**
 *
 * @param tree
 */
void    treeDelete(Tree* tree);

/*----------------------------------------------------------------------------*/
/*------------------------- Function Implementation --------------------------*/
/*----------------------------- Main Section ---------------------------------*/
/**
 *
 * @return
 */
int main() {
    Tree *t = treeCreate();
    getUserValues(t);
    printMinimumTreeValue(t);
    printTreeLeaves(t->_root);
    treeDelete(t);
    return 0;
}
/*----------------------------------------------------------------------------*/
Tree*   treeCreate(){
     Tree* t;
    if ((t = new(std::nothrow) Tree) == NULL){
        //TODO: add alloc checks
    }
    return t;
}
/*----------------------------------------------------------------------------*/
void    treeDelete(Tree* tree){

    if (tree != NULL && tree->_root != NULL){
        nodeDelete(tree->_root);
    }
    delete(tree);
}
/*----------------------------------------------------------------------------*/
void    nodeDelete(Node* node){

    if (node->_left == NULL && node->_right == NULL){
        delete(node);
    }
    else{
        if (node->_left != NULL){
            nodeDelete(node->_left);
        }
        if (node->_right != NULL){
            nodeDelete(node->_right);
        }
        delete(node);
    }
}
/*----------------------------------------------------------------------------*/
void    getUserValues(Tree* tree){

    int userInput = 0;
    cin >> userInput;
    while (userInput != 0){
        treeAdd(tree, userInput);
        cin >> userInput;
    }
}
/*----------------------------------------------------------------------------*/
void    treeAdd(Tree* tree, const int value){

    Node* newNode = createNewNode(value);
    Node* currentNode;
    if (tree->_root == NULL){
        tree->_root = newNode;
    }
    else{
        currentNode = tree->_root;
        nodeAdd(currentNode, newNode);
    }

}
/*----------------------------------------------------------------------------*/
void    nodeAdd(Node* node, Node* const toAdd){
    if (node->_data < toAdd->_data){
        if (node->_right == NULL){
            //Insert new node to right subtree
            node->_right = toAdd;
        }
        else{
            nodeAdd(node->_right, toAdd);
        }
    }
    else {
        if (node->_left == NULL) {
            //Insert new node to the left subtree
            node->_left = toAdd;
        }
        else {
            nodeAdd(node->_left, toAdd);
        }
    }
}
/*----------------------------------------------------------------------------*/
Node*   createNewNode(const int value){
    Node* newNode;
    if ((newNode = new(std::nothrow) Node) == NULL) {
        //TODO: add alloc checks
    }
    newNode->_data = value;
    return newNode;
}
/*----------------------------------------------------------------------------*/
void    debugTreePrint(const Node* node){

    if (node->_left != NULL){
        debugTreePrint(node->_left);
    }

    cout << node->_data << " ";

    if (node->_right != NULL){
        debugTreePrint(node->_right);
    }
}
/*----------------------------------------------------------------------------*/
void    printTreeLeaves(const Node* const root){

    if (root == NULL){
        return;
    }
    if (root->_left != NULL){
        printTreeLeaves(root->_left);
    }
    if (root->_left == NULL && root->_right == NULL) {
        cout << root->_data << " ";
    }
    if (root->_right != NULL){
        printTreeLeaves(root->_right);
    }
}
/*----------------------------------------------------------------------------*/
void    printMinimumTreeValue(const Tree *const tree){

    Node* node = tree->_root;
    if (node == NULL){
        cout << "0" << endl;
    }
    else {
        while (node->_left != NULL) {
            node = node->_left;
        }
        cout << node->_data << endl;
    }
}
/*----------------------------------------------------------------------------*/