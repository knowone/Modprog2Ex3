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
 * Finds the the leaf with the minimum (least) depth in the BST.
 * It uses a Breadth-First Search algorithm to traverse the tree "horizontally",
 * meaning it goes through all the nodes in the same height from the root
 * (starting from 1), going left to right, and if a leaf was not found, advances
 * to traverse all nodes with height of 2 and so on..
 * Using 2 Queues to undo changes to the state of node_visited in each node.
 * Note: we override the const modifier by getting a pointer from the root node
 * to it's Tree parent struct and back to the root without a const modifier.
 * This casting is necessary for the algorithm to work. No modifications are
 * done to any Node and any change is reverted.
 *
 * @param root the first Node of the tree.
 * @return pointer to the Node that is in the minimum depth (first one from any
 * other node, ordered by in-order).
 */
const Node* min_depth_leaf(const Node *root) ;
/*--------------------------- Queue   Function -------------------------------*/

/**
 * Creates an empty Queue struct in size of @param size
 * @param size the size of the desired queue.
 * Note: Queue Should be the size of the tree.
 * @return empty Queue pointer.
 */
Queue * createQueue(int size);

/**
 * Deletes the Queue object
 * @param q to delete
 */
void    deleteQueue(Queue* q);

/**
 * Add @param node to Queue @param queue. (FIFO)
 * @param queue where to enqueue
 * @param node add node to end of the line
 */
void    enqueue(Queue* queue, Node* node);

/**
 * Remove next Node in the @param queue.
 * @param queue to dequeue from
 * @return pointer to the next node in the queue.
 */
Node*   dequeue(Queue* queue);

/**
 * Checks if the @param queue is empty.
 * @param queue to check.
 * @return true if queue has no items in it, false otherwise.
 */
bool    isEmpty(Queue* queue);

/**
 * Helper Function. Simply checks if @param node is a leaf.
 * @param node to check.
 * @return true if node has no child nodes, meaning it is a leaf.
 * False, otherwise.
 */
bool    isLeaf(const Node* node);

/*----------------------------------------------------------------------------*/
/*------------------------- Function Implementation --------------------------*/
/*----------------------------- Main Section ---------------------------------*/
/**
 * Create am empty tree, and gets the user input and adds them to the tree,
 * creating a BST.
 * Then, finds the minimum node in the tree and prints it's value.
 * Lastly, deleting the tree.
 */
int main() {
    Tree *t = treeCreate();
    getUserValues(t);
    const Node *node;

    //Not an empty tree:
    if (t->_treeSize != 0) {
        node = min_depth_leaf(t->_root);
        if (node != NULL) {
            cout << node->_data;
        }
    }
    treeDelete(t);
    return EXIT_SUCCESS;
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