////P2-0310832.h  use Dev-C++ 5.7.1 ////
#include <iostream>
#include <stack>
using namespace std;
class stackabc{
friend class non_recursive_perm;
public:
    stackabc(){}
private:
    string str;
    int i,j;
};
class non_recursive_perm{
public:
    non_recursive_perm(char *a,int i,int n){
        stackabc mistake;
        mistake.i=i;
        mistake.j=i;
        string s(a,n+1);
        mistake.str=s;
        ptr.push(mistake);
        while(ptr.empty()!=true){
            if(ptr.top().i==n){
                cout<<ptr.top().str<<endl;
                ptr.pop();
                if(ptr.empty())break;
                swap(a[ptr.top().i],a[ptr.top().j]);
                ptr.top().j++;
            }
            else if(ptr.top().j==n+1){
                ptr.pop();
                if(ptr.empty())break;
                swap(a[ptr.top().i],a[ptr.top().j]);
                if(ptr.top().j<n) ptr.top().j++;
                else if(ptr.top().j==n){
                    ptr.pop();
                    if(ptr.empty())break;
                    swap(a[ptr.top().i],a[ptr.top().j]);
                    ptr.top().j++;
                }
            }
            else{
                stackabc marc;
                string s(a,n+1);
                swap(a[ptr.top().i],a[ptr.top().j]);
                marc.str=s;
                marc.i=ptr.top().i+1;
                marc.j=ptr.top().i+1;
                ptr.push(marc);
            }
        }
    }
private:
    stack <stackabc> ptr;
};
int main(){
 	char a[] = "ABCD";
	non_recursive_perm(a, 0, 3);
	system("pause");
	return 0;
} 
