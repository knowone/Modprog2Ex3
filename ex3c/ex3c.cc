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
struct Tree_node {
    int _data ;
    struct Tree_node *_left, *_right ;
};

struct List_node {
    int _data ;
    struct List_node * _next;
} ;

typedef struct{

    struct Tree_node* _root;

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
Tree_node*   createNewNode(const int value);

/**
 *
 * @param node
 * @param toAdd
 */
void    nodeAdd(Tree_node* node, Tree_node* const toAdd);

/**
 *
 * @param node
 */
void    nodeDelete(Tree_node* node);
//DEBUG
void    debugTreePrint(const Tree_node* node);
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
void    printTreeLeaves(const Tree_node* root);

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

    treeDelete(t);
    return 0;
}
/*----------------------------------------------------------------------------*/
Tree*   treeCreate(){
    return new(std::nothrow) Tree;
}
/*----------------------------------------------------------------------------*/
void    treeDelete(Tree* tree){

    if (tree != NULL && tree->_root != NULL){
        nodeDelete(tree->_root);
    }
    delete(tree);
}
/*----------------------------------------------------------------------------*/
void    nodeDelete(Tree_node* node){

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
    while (!cin.eof() && userInput != 0){
        treeAdd(tree, userInput);
        cin >> userInput;
    }
}
/*----------------------------------------------------------------------------*/
void    treeAdd(Tree* tree, const int value){

    Tree_node* newNode = createNewNode(value);
    Tree_node* currentNode;
    if (tree->_root == NULL){
        tree->_root = newNode;
    }
    else{
        currentNode = tree->_root;
        nodeAdd(currentNode, newNode);
    }

}
/*----------------------------------------------------------------------------*/
void    nodeAdd(Tree_node* node, Tree_node* const toAdd){
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
Tree_node*   createNewNode(const int value){
    Tree_node* newNode = new(std::nothrow) Tree_node;
    newNode->_data = value;
    return newNode;
}
/*----------------------------------------------------------------------------*/
void    debugTreePrint(const Tree_node* node){

    if (node->_left != NULL){
        debugTreePrint(node->_left);
    }

    cout << node->_data << " ";

    if (node->_right != NULL){
        debugTreePrint(node->_right);
    }
}
/*----------------------------------------------------------------------------*/