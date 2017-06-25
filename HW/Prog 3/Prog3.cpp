#include <iostream>
#include <string.h>
#include <cstring>
#include <stdlib.h>

using namespace std;

class BTnode {
friend class BT;
friend class LinkNode;
    int value = -1;//integer value
    bool printflag = false;
    BTnode* parentptr = NULL;//pointer that point to parent
    BTnode* leftchild = NULL;
    BTnode* rightchild = NULL;
    ~BTnode() {
        delete parentptr;
        delete leftchild;
        delete rightchild;
    }
};
class LinkNode{
friend class BT;
private:
    BTnode *treenode=NULL;
    LinkNode *next=NULL;
    int position=0;//position in full binary tree
public:
    LinkNode() {
        treenode=new BTnode;
    }
    ~LinkNode(){
        delete treenode;
    }
};
class BT {
private:
    BTnode *tree;//root node
public:
    BT(const char *inputstring) {
        LinkNode *link=NULL;//to store array of tree node
        LinkNode *current=NULL,*pre=NULL;//used to establish link
        char *p;
        char *buffer = new char[strlen(inputstring)+1];
        strcpy(buffer,inputstring);
        char *valuestring = strtok(buffer,&p);
        int n=0;
        int i=0;
        int value[10000] = {3};
        //compute the number of node
        while (valuestring != NULL) {
            value[i]=atoi(valuestring);
            valuestring = strtok(NULL,&p);
            i++;
        }
        n = i;
        //construct a linked-list of tree_node;
        for (i = 1; i < n; i++) {
            current = new LinkNode;
            current->position = i;
            current->treenode->value = value[i];
            if (i == 1) {
                link = current;
                pre = current;
            }
            else {
                pre->next = current;
                pre = current;
            }
        }
        //establish relation between each node
        for (i = 1; i < n; i++) {
            current = link;
            pre = link;
            if ((i / 2) != 0) {
                //find parent node
                while (current->position != (i / 2)) {
                    current = current->next;
                }
                //find child node
                while (pre->position != i) {
                    pre = pre->next;
                }
                pre->treenode->parentptr = current->treenode;
                //find leftchild or rightchild
                if (i % 2 == 1) {
                    current->treenode->rightchild = pre->treenode;
                }
                else {
                    current->treenode->leftchild = pre->treenode;
                }
            }
        }
        tree = link->treenode;
    }
    void inorder() {
        BTnode* currentptr = tree;//ptr for traversal
        while (currentptr!=NULL) {
            //go to the left until no left to go
            if (currentptr->leftchild != NULL && currentptr->leftchild->printflag != true) {
                currentptr = currentptr->leftchild;
            }
            //no left to go
            else {
                //print visit
                if (currentptr->printflag != true) {
                    if (currentptr->value != -1) {
                        cout << currentptr->value<<endl;
                    }
                    currentptr->printflag = true;
                }
                //if it can go to right
                if (currentptr->rightchild != NULL && currentptr->rightchild->printflag != true) {
                    currentptr = currentptr->rightchild;
                }
                //can't go left or right so go back to parent
                else {
                    currentptr = currentptr->parentptr;
                }
            }
        }
    }
};
int main()
{
  const char *a = "4 3 11 5 6 12 8 4 -1 9 -1 -1 -1 17";
  BT bt(a);
  bt.inorder();
  system("pause");
  return 0;
}
