#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED

#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <iomanip>

using namespace std;

//定义矩阵的最大维数
const int X=50;
const int Y=50;
const double EPSILON=0.000001;

//定义随机一致性指标RI
const double RI_DATA[11]= {0,0,0.58,0.90,1.12,1.24,1.32,1.41,1.45,1.49,1.51};

class Matrix
{
private:
    double inner_matrix[X][Y];
    int xx,yy;    //x和y
    double eigenValue;
    Matrix* eigenVector;
    bool hasCal;
public:

///-------默认构造函数-------
    Matrix() {
        init();
    }
    Matrix(int x,int y) {
        init(x,y);
    }

///-------输入矩阵-------
    void inputMatrix() {
        cout<<"\n请输入"<<xx*yy<<"个数据，以构成"<<xx<<"行"<<yy<<"列的数组"<<endl;
        for(int i = 0; i < xx; i++) {
            for(int j = 0; j < yy; j++) {
                cin >> inner_matrix[i][j];
            }
        }
    }

///-------设置矩阵容量-------
    void setSize() {
        cout << "输入矩阵:";
        cout << "\n行数:";
        cin >> xx;
        cout << "列数:";
        cin >> yy;
    }

///-------初始化矩阵-------
    void init(int x,int y) {
        hasCal=false;
        //初始化特征向量
        eigenVector=0;

        xx=x;
        yy=y;
        for(int i=0; i<X; i++) {
            for(int j=0; j<Y; j++) {
                inner_matrix[i][y]=0;
            }
        }
    }
    void init() {
        init(0,0);
    }

///-------将数组数据依次插入矩阵中-------
    void insertFromArray(double *arr) {
        hasCal=false;
        int counter=0;
        for(int i=0; i<xx; i++) {
            for(int j=0; j<yy; j++) {
                inner_matrix[i][j]=arr[counter];
                counter++;
            }
        }
    }

///-------显示矩阵-------
    void displayMatrix(string name="") {
        int i, j;
        cout <<name<<"表示如下:";
        for(i = 0; i < xx; i++) {
            cout << endl;
            for(j = 0; j < yy; j++) {
                cout << setw(7) << setiosflags(ios::left) << inner_matrix[i][j];
            }
        }
        cout<<"\n"<<endl;
    }


///-------获得最大元素-------
    double findMaxElement(int x,int y) {
        double m=0;
        for(int i=0; i<x; i++) {
            for(int j=0; j<y; j++) {
                if(m<inner_matrix[i][j]) {
                    m=inner_matrix[i][j];
                }
            }
        }
        return m;
    }

    double findMaxElement() {
        return findMaxElement(xx,yy);
    }

///-------获得所有数之和-------
    double sum(int x,int y) {
        double total=0;
        for(int i=0; i<x; i++) {
            for(int j=0; j<y; j++) {
                total+=inner_matrix[i][j];
            }
        }
        return total;
    }

    double sum(){
        return sum(xx,yy);
    }

///-------获取X/Y-------
    double getX() {
        return xx;
    }
    double getY() {
        return yy;
    }

///-------获取元素值--------
    double getValue(int x,int y) {
        return inner_matrix[x][y];
    }

///-------设置元素值--------
    void setValue(int x,int y,double value) {
        hasCal=false;
        inner_matrix[x][y]=value;
    }

///-------矩阵转置--------
    Matrix& transpose() {
        for(int i=0; i<xx; i++) {
            for(int j=0; j<i; j++) {
                double temp=0;
                temp=inner_matrix[i][j];
                inner_matrix[i][j]=inner_matrix[j][i];
                inner_matrix[j][i]=temp;
            }
        }
        int temp=0;
        temp=xx;
        xx=yy;
        yy=temp;
        return *this;
    }

///-------获取子矩阵的副本--------
    Matrix& getSubMatrix(int x,int y) {
        Matrix subMatrix = Matrix(x,y);
        for(int i=0; i<x; i++) {
            for(int j=0; j<y; j++) {
                subMatrix.setValue(i,j,inner_matrix[i][j]);
            }
        }
        return subMatrix;
    }

///--------矩阵和一个数相乘-------
    Matrix& dotProduct(double aValue) {
        int i,j;
        for(i=0; i<xx; i++) {
            for(j=0; j<yy; j++) {
                inner_matrix[i][j]=inner_matrix[i][j]*aValue;
            }
        }
        return *this;
    }

///-------两个矩阵相乘-------
    Matrix& matrixProduct(Matrix& anotherMatrix) {
        if(yy!=anotherMatrix.getX()) {
            cerr<<"两个矩阵无法相乘！"<<endl;
        }

        Matrix resultMatrix=Matrix(xx,anotherMatrix.getY());
        for(int i=0; i<xx; i++) {
            for(int j=0; j<anotherMatrix.getY(); j++) {
                double temp=0;
                for(int k=0; k<yy; k++) {
                    temp+=inner_matrix[i][k]*anotherMatrix.getValue(k,j);
                }
                resultMatrix.setValue(i,j,temp);
            }
        }
        return resultMatrix;
    }

///-------求最大特征值和特征向量-------
    void power() {
        Matrix xk=getSubMatrix(xx,1);//取第一列为xk
        double c=0;
        Matrix yk=Matrix();
        int count=50;//迭代次数
        Matrix old_xk=xk;

        while(count>0) {
            yk=matrixProduct(xk);
            c=xk.findMaxElement(xk.getX(),1);
            xk=yk.dotProduct(1/c);

//以下代码有问题，当差很小，计算出来的epsilon总是很大
            double epsilon=0.0;
            for(int i=0; i<xx; i++) {
                double cha=xk.getValue(i,0)-old_xk.getValue(i,0);
                epsilon=epsilon+pow(cha,2);
            }
            old_xk=xk;
            if(sqrt(epsilon)<EPSILON) {
                break;
            }
            count--;
        }

        eigenValue=c;
        eigenVector=&xk;
    }

///-------获取/打印特征值特征向量-------
    double getEigenValue() {
        checkCal();
        return eigenValue;
    }
    Matrix& getEigenVector() {
        checkCal();
        return *eigenVector;
    }

    void displayEigenValue() {
        checkCal();
        cout<<"\n矩阵特征值是："<<eigenValue<<endl;
    }
    void displayEigenVector() {
        checkCal();
        eigenVector->displayMatrix("矩阵的特征向量");
    }

    void checkCal() {
        if(!hasCal) {
            power();
        }
    }

///-------获得/显示归一化特征向量-------
    Matrix& getNormalizedEigenVector() {
        checkCal();
        return eigenVector->dotProduct(1/eigenVector->sum());
    }

///-------获得一致性指标CI-------
    double CI() {
        checkCal();
        return (eigenValue-xx)/(xx-1.0);
    }

///-------------获得RI------------

    double RI() {
        return RI_DATA[xx-1];
    }

///-------计算一致性比率CR-------
    double CR() {
        return  CI()/RI();
    }

///-------显示层次单排序的相关信息-------
    void displayCalInfo(){
        cout<<"CI："<<CI()<<"\nLamda："<<getEigenValue()<<endl;
        getNormalizedEigenVector().displayMatrix("归一化向量");
    }

};


#endif // MATRIX_H_INCLUDED
