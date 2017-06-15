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
/*--------------------------- Public  Function -------------------------------*/
/**
 *
 * @return
 */
Tree*   treeCreate();

/**
 *
 * @param tree
 */
void    treeDelete(Tree* tree);

/**
 *
 * @param tree
 * @param value
 */
void    treeAdd(Tree* tree, const int value);

List_node*    addListNode(List_node*& list, const int value);

/**
 *
 * @param list
 * @param current
 * @param node
 */
void    createSortedList(List_node *& list,
                         List_node *& current, const Tree_node* node);
/**
 *
 * @param node
 */
void    printSortedList(const List_node* node);

/**
 *
 * @param list
 */
void    sortedListDelete(List_node *list);
/*----------------------------------------------------------------------------*/
/*------------------------- Function Implementation --------------------------*/
/*----------------------------- Main Section ---------------------------------*/
/**
 *
 * @return
 */
int main() {

    List_node* ln = NULL, *ln_current = NULL;
    Tree *t = treeCreate();

    getUserValues(t);
    createSortedList(ln, ln_current, t->_root);
    printSortedList(ln);

    treeDelete(t);
    sortedListDelete(ln);
    return EXIT_SUCCESS;
}
/*----------------------------------------------------------------------------*/
Tree*   treeCreate(){
    return new(std::nothrow) Tree;
    //TODO: check memory
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
    //TODO: memory check
    newNode->_data = value;
    return newNode;
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
void    createSortedList(List_node *& list,
                      List_node *& current, const Tree_node* node){

    if (node == NULL){
        return;
    }
    if (node->_left != NULL){
        createSortedList(list, current, node->_left);
    }

    if (list == NULL) {
        current = addListNode(list, node->_data);
    }
    else{
        current = addListNode(current, node->_data);
    }
    if (node->_right != NULL){
        createSortedList(list, current, node->_right);
    }
}
/*----------------------------------------------------------------------------*/
List_node*    addListNode(List_node*& list, const int value){

    List_node* list_node = new(std::nothrow) List_node;
    //TODO: check memory
    if (list == NULL){
        list =  list_node;
        list->_data = value;
        return list;
    }
    else {
        list_node->_data = value;
        list->_next = list_node;
        return list->_next;
    }
}
/*----------------------------------------------------------------------------*/
void    sortedListDelete(List_node *list){

    List_node* node = list, *next_node;
    while (node != NULL){
        next_node = node->_next;
        delete(node);
        node = next_node;
    }
    delete(list);
}
/*----------------------------------------------------------------------------*/
void    printSortedList(const List_node* node){

    const List_node* list_node = node;

    while (list_node != NULL){

        cout << list_node->_data << " ";
        list_node = list_node->_next;
    }
    cout << endl;
}
/*----------------------------------------------------------------------------*/