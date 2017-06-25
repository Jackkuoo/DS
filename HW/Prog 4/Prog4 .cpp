#include<iostream>
using namespace std;
template <class K,class E> class BST;
template <class K,class E>
class node{
friend class BST<K,E>;
friend class PolyBST;
private:
    K key;
    E element;
    node<K,E> *leftchild;
    node<K,E> *rightchild;
};
template <class K,class E>
class BST{
private:
    node<int,double> *root;
};
class PolyBST : public BST<int,double>{
public:
    PolyBST(){
        root=NULL;
    }
    void del(node<int,double>* n){
        if(n){
            del(n->leftchild);
            del(n->rightchild);
            delete n;
        }
        else return;
    }
    void build(PolyBST &poly,node<int,double>* n){
        if(n){
            poly.setTerm(n->key,n->element);
            build(poly,n->leftchild);
            build(poly,n->rightchild);
        }
        else return;
    }
    PolyBST(const PolyBST &poly){
        root=NULL;
        node<int,double> *temp=root;
        del(temp);
        root=NULL;
        build(*this,poly.root);
    }
    node<int,double>* leftnode(node<int,double>* n){
        node<int,double> *temp=n;
        while(temp->leftchild){
            temp=temp->leftchild;
        }
        return temp;
    }
    node<int,double>* deletion(int k,node<int,double> *ptr){
        if(root==NULL) return root;
        else if(k<ptr->key) ptr->leftchild=deletion(k,ptr->leftchild);
        else if(k>ptr->key) ptr->rightchild=deletion(k,ptr->rightchild);
        else{
            if(ptr->leftchild==NULL&&ptr->rightchild==NULL){
                delete ptr;
                ptr=NULL;
                return ptr;
            }
            else if(ptr->leftchild==NULL){
                node<int,double> *temp=ptr;
                ptr=ptr->rightchild;
                delete temp;
                return ptr;
            }
            else if(ptr->rightchild==NULL){
                node<int,double> *temp=ptr;
                ptr=ptr->leftchild;
                delete temp;
                return ptr;
            }
            else{
                node<int,double> *temp=leftnode(ptr->rightchild);
                ptr->element=temp->element;
                ptr->key=temp->key;
                ptr->rightchild=deletion(temp->key,ptr->rightchild);
            }
        }
        return ptr;
    }
    void setTerm(int ex, double co){
        node<int,double> *t=root,*p=NULL;
        while(t){
            if(ex==t->key){
                t->element=co;
                if(t->element==0) root=deletion(t->key,root);
                return;
            }
            p=t;
            t=(ex>t->key)? t->rightchild : t->leftchild;
        }
        t=new node<int,double>;
        t->key=ex;
        t->element=co;
        t->leftchild=NULL;
        t->rightchild=NULL;
        if(root){
            if(ex<p->key) p->leftchild=t;
            else p->rightchild=t;
        }
        else{
            root=t;
        }
        if(t->element==0) root=deletion(t->key,root);
    }
    void print(ostream &out) const{
        if(root){
            print(root,out);
        }
        else{
            out<<"0";
        }
        return;
    }
    void print(node<int,double> *ptr,ostream &out) const{
       if(ptr){
            print(ptr->rightchild,out);
            if(ptr->element>=0){
                out<<" + ";
            }
            if(ptr->key!=0) {
                if(ptr->element>=0)
                    out<<ptr->element<<"*"<<"x"<<"^"<<ptr->key;
                else out<<" - "<<-(ptr->element)<<"*"<<"x"<<"^"<<ptr->key;
            }
            else if(ptr->key==0){
                if(ptr->element>=0) out<<ptr->element;
                else out<<" - "<<-(ptr->element);
            }
            print(ptr->leftchild,out);
        }
        else return;
    }
    void addTerm(int ex, double co){
        node<int,double> *t=root,*p=NULL;
        while(t){
            if(ex==t->key){
                t->element+=co;
                if(t->element==0) root=deletion(t->key,root);
                return;
            }
            p=t;
            t=(ex>t->key)? t->rightchild : t->leftchild;
        }
        t=new node<int,double>;
        t->key=ex;
        t->element=co;
        t->leftchild=NULL;
        t->rightchild=NULL;
        if(root){
            if(ex<p->key) p->leftchild=t;
            else p->rightchild=t;
        }
        else{
            root=t;
        }
        if(t->element==0) root=deletion(t->key,root);
    }
    void add(node<int,double>* ptr,PolyBST &bst){
        if(ptr){
            add(ptr->leftchild,bst);
            bst.addTerm(ptr->key,ptr->element);
            add(ptr->rightchild,bst);
        }
    }
    void sub(node<int,double>* ptr,PolyBST &bst){
        if(ptr){
            sub(ptr->leftchild,bst);
            bst.addTerm(ptr->key,-ptr->element);
            sub(ptr->rightchild,bst);
        }
    }
    PolyBST& operator=(const PolyBST &poly){
        node<int,double> *temp=root;
        del(temp);
        root=NULL;
        build(*this,poly.root);
        return *this;
    }
    PolyBST operator+(const PolyBST &poly){
        PolyBST b;
        b=*this;
        add(poly.root,b);
        return b;
    }
    PolyBST operator-(const PolyBST &poly){
        PolyBST b;
        b=*this;
        sub(poly.root,b);
        return b;
    }
    void second(PolyBST &poly,node<int,double>* n1,node<int,double>* n2){
        if(n2){
            poly.addTerm(n1->key+n2->key,n1->element*n2->element);
            second(poly,n1,n2->leftchild);
            second(poly,n1,n2->rightchild);
        }
    }
    void first(PolyBST &poly,node<int,double>* n1,node<int,double>* n2){
        if(n1){
            second(poly,n1,n2);
            first(poly,n1->leftchild,n2);
            first(poly,n1->rightchild,n2);
        }
    }
    PolyBST operator*(const PolyBST &poly){
        PolyBST b;
        first(b,this->root,poly.root);
        return b;
    }
    void mul(node<int,double> *ptr,const double d){
        if(ptr){
            ptr->element*=d;
            mul(ptr->leftchild,d);
            mul(ptr->rightchild,d);
        }
    }
    PolyBST operator*(const double &d){
        PolyBST b;
        b=*this;
        mul(b.root,d);
        return b;
    }
    friend ostream& operator<<(ostream &out,const PolyBST &poly);
private:
    node<int,double> *root=NULL;
};
ostream & operator<<(ostream &out,const PolyBST &poly){
    poly.print(out);
    return out;
}

int main()
{
  PolyBST p1, p2, p3;
  p1.setTerm(2,2);   p1.setTerm(0, -1);
  cout <<"p1 = " << p1 << endl;  // 2*x^2 -1
  p2.setTerm(0,1);   p2.setTerm(2,2);
  cout <<"p2 = " << p2 << endl;  // 2*x^2 + 1
  p3 = p1 * p2;
  cout <<"p1*p2 = " << p3 << endl; // 4*x^4 -1
  p3 = p1 + p2;
  cout <<"p1+p2 = " << p3 << endl; // 4*x^2
  p3 = p1 - p2;
  cout <<"p1¡Vp2 = " << p3 << endl; // ¡V2
  p1.setTerm(2,3);   p1.setTerm(1,2);  p1.setTerm(0,0);
  cout <<"p1 = " << p1 << endl;  // 3*x^2 + 2*x^1
  p3 = p1 * 2;
  cout <<"p1*2 = " << p3 << endl; // 6*x^2 + 4*x^1
  p3 = p1 * 2 - p2;
  cout <<"p1*2-p2 = " << p3 << endl; // 4*x^2 + 4*x^1 - 1
  //system("pause");
  return 0;
}
