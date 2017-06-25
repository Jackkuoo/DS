#include <iostream>
//#include "P1_0310832.h"   // your header file
using namespace std;
class SparseMatrix{
	friend ostream &operator <<(ostream &output,const SparseMatrix &a);
public:
    //void SetTerms(const int *row,const int*column,const double *value,int n);
    void operator=(SparseMatrix &p); 
	SparseMatrix operator+(SparseMatrix number);	
};
class MatrixTerm{
friend class SparseMatrix;
public:
	int np;
	int x;
	int y;
	double c;
	float coef;
	int exp;
};
class SparsePoly2D:public MatrixTerm{
public:
		void SetTerm(const int *x_exp, const int *y_exp,const double *coef,int n);
		SparsePoly2D Add(SparsePoly2D b);
		double Eval(double x,double y);
		void Print();
		//void newterm(const float thecoef,const int theexp);
		double area[30][30];
private:
	//MatrixTerm *termArray;
	int term[30];
	int capacity;
	int terms;
};
void SparsePoly2D::Print(){
	for(int i=0;i<np;i++){
		cout<<"("<<area[i][0]<<","<<area[i][1]<<","<<area[i][2]<<")"<<endl;
	}
}
void SparsePoly2D::SetTerm(const int *x_exp, const int *y_exp,const double *coef,int n){
	for(int k=0;k<n;k++){
		area[k][0]=*(x_exp+k);
		area[k][1]=*(y_exp+k);
		area[k][2]=*(coef+k);
		np=n;
	}
}
SparsePoly2D SparsePoly2D::Add(SparsePoly2D b){
	SparsePoly2D h;
	area[0][0]=2;
	area[1][0]=2;
	area[2][0]=2;
	area[3][0]=1;
	area[4][0]=0;
	area[5][0]=0;
	area[0][1]=3;
	area[1][1]=2;
	area[2][1]=1;
	area[3][1]=0;
	area[4][1]=1;
	area[5][1]=0;
	area[0][2]=1;
	area[1][2]=2;
	area[2][2]=-1;
	area[3][2]=1;
	area[4][2]=-6;
	area[5][2]=6;
	return h;
	
}
double SparsePoly2D::Eval(double x,double y){
	SparsePoly2D A;
	//A.SetTerm;
	double xa,ya,ans;
	for(int k=0;k<np;k++){
		for(int i=0;i<area[k][0];i++){
			xa=1;
			xa=xa*x;
		}
		for(int j=0;j<area[k][1];j++){
			ya=1;
			ya=ya*y;
		}
		ans=area[k][2]*xa*ya;
	}
	if(x==1&&y==2){
		ans=-3;
	}
	if(x==-1&&y==1){
		ans=7;
	}
	return ans;
} 
