#include<iostream>
#include<cstring>
#include<sstream>
#include<cstdlib>
using namespace std;

class treenode{
public:
    friend class BT;
    treenode(){
        open=false;
    }
    treenode& operator=(treenode k){
        data=k.data;
        leftchild=k.leftchild;
        rightchild=k.rightchild;
        parent=k.parent;
        return *this;
    }
private:
    int data;
    bool open;
    treenode *leftchild;
    treenode *rightchild;
    treenode *parent;
};
class BT{
public:
    BT(const char *cptr){
        a=cptr;
        string tsr(a);
        s=tsr;
        counter=0;
    }
    void build(treenode *p,int input1,int input2){
        treenode *left = new treenode;
        if(input1==-1) left->open=true;
        left->data=input1;
        left->leftchild=NULL;
        left->rightchild=NULL;
        p->leftchild=left;
        left->parent=p;
        treenode *right = new treenode;
        if(input2==-1) right->open=true;
        right->data=input2;
        right->leftchild=NULL;
        right->rightchild=NULL;
        p->rightchild=right;
        right->parent=p;
    }
    void buildtree(int i,treenode *right){
        if(i*2+1<counter){
            build(right,value[i*2],value[i*2+1]);
        }
        if(right->leftchild) buildtree(i*2,right->leftchild);
        if(right->rightchild) buildtree(i*2+1,right->rightchild);
    }
    void inorder(void){
        stringstream tpe;
        tpe<<s;
        int x;
        while(tpe>>x){
            value[counter]=x;
            counter++;
        }
        if(counter>1&&counter!=2){
            int i=1;
            treenode *tr;
            treenode *root=new treenode;
            root->data=value[1];
            root->parent=NULL;
            tr=root;
            buildtree(i,root);
            treenode *currentnode=tr;
            while(1){
                while(currentnode->leftchild&&currentnode->leftchild->open==false){
                    currentnode=currentnode->leftchild;
                }
                if(currentnode){
                    if(currentnode->open==false){
                        cout<<currentnode->data<<" ";
                        currentnode->open=true;
                    }
                    if(currentnode->rightchild&&currentnode->rightchild->open==false){
                        currentnode=currentnode->rightchild;
                    }
                    else{
                        if(currentnode->parent) currentnode=currentnode->parent;
                        else break;
                    }
                }
            }
        }
        else if(counter==2){
            cout<< value[1] <<endl;
        }
    }
private:
    const char* a;
    int value[100000];
    string s;
    int counter;
};
int main()
{
  const char *a = "4 3 11 5 6 12 8 4 -1 9 -1 -1 -1 17";
  BT bt(a);
  bt.inorder();
  system("pause");
  return 0;
}
