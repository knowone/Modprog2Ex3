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
typedef struct{

    int _treeSize;
    struct Node* _root;
}Tree;


struct Node {

    Tree* _rootTree;
    int _data ;
    bool _visited;
    struct Node *_left, *_right;
};

typedef struct{

    Node** _nodes;
    int _head_index;
    int _tail_index;
} Queue;
/*------------------------- Function Declaration -----------------------------*/
/*-------------------------- Private  Function -------------------------------*/
/**
 * Create a new node with _data attribute of @param value and tree as _root of
 * newNode
 * @param value non-zero integer
 * @param the Tree struct pointer representing the root of the tree
 * @return pointer to new Node struct
 */
Node*   createNewNode(Tree* tree, const int value);

/**
 * Add @param toAdd into the (sub)tree with root of @param node.
 * Recursively try to find the new node's correct location as a left or right
 * child of node.
 * @param node the root of the (sub)tree that will contain the new toAdd node.
 * @param toAdd the new node to add into the tree
 */
void    nodeAdd(Node* node, Node* const toAdd);

/**
 * Delete the Node struct.
 * @param node to delete
 */
void    nodeDelete(Node* node);

/*--------------------------- Public  Function -------------------------------*/
/**
 * Receives input from user and creates a BST with those values.
 * @param tree pointer to an allocated Tree struct
 */
void    getUserValues(Tree* tree);

/**
 * Allocate an empty Tree struct.
 * Note: the Node struct within _root is uninitialized.
 * @return pointer to newly allocated Tree struct
 */
Tree*   treeCreate();

/**
 * Delete tree struct and all its Node structs.
 * @param tree
 */
void    treeDelete(Tree* tree);

/**
 * Add a value into the Tree.
 * @param tree the Tree struct to add a value to.
 * @param value a non zero integer
 */
void    treeAdd(Tree* tree, const int value);

/**
 *
 * @param root
 * @return
 */
const Node* min_depth_leaf(const Node *root) ;
/*--------------------------- Queue   Function -------------------------------*/

/**
 *
 * @param size
 * @return
 */
Queue * createQueue(int size);

/**
 *
 * @param q
 */
void    deleteQueue(Queue* q);

/**
 *
 * @param queue
 * @param node
 */
void    enqueue(Queue* queue, Node* node);

/**
 *
 * @param queue
 * @return
 */
Node*   dequeue(Queue* queue);

/**
 *
 * @param queue
 * @return
 */
bool    isEmpty(Queue* queue);

/**
 *
 * @param node
 * @return
 */
bool    isLeaf(const Node* node);

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
    const Node *node;
    if (t->_treeSize != 0) {
        node = min_depth_leaf(t->_root);
        if (node != NULL) {
            cout << node->_data;
        }
    }
    treeDelete(t);
    return 0;
}
/*----------------------------------------------------------------------------*/
Tree*   treeCreate(){
    Tree * t = new(std::nothrow) Tree;
    //TODO: alloc check
    t->_treeSize = 0;
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
    while (!cin.eof()){

        treeAdd(tree, userInput);
        cin >> userInput;
    }
}
/*----------------------------------------------------------------------------*/
void    treeAdd(Tree* tree, const int value){

    Node* newNode = createNewNode(tree, value);
    Node* currentNode;
    if (tree->_root == NULL){
        tree->_root = newNode;
    }
    else{
        currentNode = tree->_root;
        nodeAdd(currentNode, newNode);
    }
    ++tree->_treeSize;
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
Node*   createNewNode(Tree* tree, const int value){
    Node* newNode = new(std::nothrow) Node;
    //TODO: alloc check
    newNode->_data = value;
    newNode->_rootTree = tree;
    newNode->_visited = false;
    return newNode;
}
/*----------------------------------------------------------------------------*/
const Node* min_depth_leaf(const Node *root){

    Queue* queue = createQueue(root->_rootTree->_treeSize);
    Queue* secondary = createQueue(root->_rootTree->_treeSize);
    Node* node = root->_rootTree->_root;
    enqueue(queue, node);
    enqueue(secondary, node);
    node->_visited = true;
    while(!isEmpty(queue)){
        node = dequeue(queue);
        if (isLeaf(node)){
            break;
        }
        if(node->_left != NULL && !node->_left->_visited){
            node->_left->_visited = true;
            enqueue(queue, node->_left);
            enqueue(secondary, node->_left);
        }
        if(node->_right != NULL && !node->_right->_visited){
            node->_right->_visited = true;
            enqueue(queue, node->_right);
            enqueue(secondary, node->_right);
        }
    }
    while (!isEmpty(secondary)) {
        dequeue(secondary)->_visited = false;
    }
    deleteQueue(secondary);
    deleteQueue(queue);
    return node;
}
/*----------------------------------------------------------------------------*/
bool isLeaf(const Node* node){
    return (node != NULL && node->_left == NULL && node->_right == NULL);
}

/*----------------------------------------------------------------------------*/
Queue * createQueue(int size){

    Queue* queue = new (std::nothrow) Queue;
    //TODO: alloc check
    queue->_nodes = new(std::nothrow) Node* [size];
    //TODO: alloc check
    queue->_head_index = 0;
    queue->_tail_index = -1;
    return queue;
}
/*----------------------------------------------------------------------------*/
void deleteQueue(Queue* q){
    delete[](q->_nodes);
    delete(q);
}
/*----------------------------------------------------------------------------*/
void enqueue(Queue* queue, Node* node){

    queue->_nodes[++queue->_tail_index] = node;
}
/*----------------------------------------------------------------------------*/
Node* dequeue(Queue* queue){

    if (!isEmpty(queue)){
        return queue->_nodes[queue->_head_index++];
    } else return NULL;
}
/*----------------------------------------------------------------------------*/
bool isEmpty(Queue* queue){
    return queue->_tail_index < queue->_head_index;
}
/*----------------------------------------------------------------------------*/