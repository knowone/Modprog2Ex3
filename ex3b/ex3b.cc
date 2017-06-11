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

void    getUserValues(Tree* tree);
Node*   createNewNode(Tree* tree, const int value);
void    nodeAdd(Node* node, Node* const toAdd);
void    nodeDelete(Node* node);

//DEBUG
void    debugTreePrint(const Node* node);
/*--------------------------- Public  Function -------------------------------*/

Tree*   treeCreate();
void    treeAdd(Tree* tree, const int value);
void    printTreeLeaves(const Node* root);

void    treeDelete(Tree* tree);
Node*   min_depth_leaf(const Node *root) ;
bool    isLeaf(const Node* node);

Queue * createQueue(int size);
void deleteQueue(Queue* q);
void enqueue(Queue* queue, Node* node);
Node* dequeue(Queue* queue);
bool isEmpty(Queue* queue);

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
    if (t->_treeSize != 0) {
        Node *node = min_depth_leaf(t->_root);
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
    while (!cin.eof() && userInput != 0){
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
    newNode->_data = value;
    newNode->_rootTree = tree;
    newNode->_visited = false;
    return newNode;
}
/*----------------------------------------------------------------------------*/
Node*   min_depth_leaf(const Node *root){
    Queue* queue = createQueue(root->_rootTree->_treeSize);
    Node* node = root->_rootTree->_root;
    enqueue(queue, node);
    node->_visited = true;
    while(!isEmpty(queue)){
        node = dequeue(queue);
        if (isLeaf(node)){
            break;
        }
        if(node->_left != NULL && !node->_left->_visited){
            node->_left->_visited = true;
            enqueue(queue, node->_left);
        }
        if(node->_right != NULL && !node->_right->_visited){
            node->_right->_visited = true;
            enqueue(queue, node->_right);
        }
    }
    deleteQueue(queue);
    return node;
}


bool isLeaf(const Node* node){
    return (node != NULL && node->_left == NULL && node->_right == NULL);
}

Queue * createQueue(int size){

    Queue* queue = new (std::nothrow) Queue;
    queue->_nodes = new(std::nothrow) Node* [size];
    queue->_head_index = 0;
    queue->_tail_index = -1;
    return queue;
}

void deleteQueue(Queue* q){
    delete[](q->_nodes);
    delete(q);
}

void enqueue(Queue* queue, Node* node){

    queue->_nodes[++queue->_tail_index] = node;
}

Node* dequeue(Queue* queue){

    if (!isEmpty(queue)){
        return queue->_nodes[queue->_head_index++];
    } else return NULL;
}

bool isEmpty(Queue* queue){
    return queue->_tail_index < queue->_head_index;
}