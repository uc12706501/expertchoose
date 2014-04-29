#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED

#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <iomanip>

using namespace std;

//�����������ά��
const int X=50;
const int Y=50;
const double EPSILON=0.000001;

//�������һ����ָ��RI
const double RI_DATA[11]= {0,0,0.58,0.90,1.12,1.24,1.32,1.41,1.45,1.49,1.51};

class Matrix
{
private:
    double inner_matrix[X][Y];
    int xx,yy;    //x��y
    double eigenValue;
    Matrix* eigenVector;
    bool hasCal;
public:

///-------Ĭ�Ϲ��캯��-------
    Matrix() {
        init();
    }
    Matrix(int x,int y) {
        init(x,y);
    }

///-------�������-------
    void inputMatrix() {
        cout<<"\n������"<<xx*yy<<"�����ݣ��Թ���"<<xx<<"��"<<yy<<"�е�����"<<endl;
        for(int i = 0; i < xx; i++) {
            for(int j = 0; j < yy; j++) {
                cin >> inner_matrix[i][j];
            }
        }
    }

///-------���þ�������-------
    void setSize() {
        cout << "�������:";
        cout << "\n����:";
        cin >> xx;
        cout << "����:";
        cin >> yy;
    }

///-------��ʼ������-------
    void init(int x,int y) {
        hasCal=false;
        //��ʼ����������
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

///-------�������������β��������-------
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

///-------��ʾ����-------
    void displayMatrix(string name="") {
        int i, j;
        cout <<name<<"��ʾ����:";
        for(i = 0; i < xx; i++) {
            cout << endl;
            for(j = 0; j < yy; j++) {
                cout << setw(7) << setiosflags(ios::left) << inner_matrix[i][j];
            }
        }
        cout<<"\n"<<endl;
    }


///-------������Ԫ��-------
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

///-------���������֮��-------
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

///-------��ȡX/Y-------
    double getX() {
        return xx;
    }
    double getY() {
        return yy;
    }

///-------��ȡԪ��ֵ--------
    double getValue(int x,int y) {
        return inner_matrix[x][y];
    }

///-------����Ԫ��ֵ--------
    void setValue(int x,int y,double value) {
        hasCal=false;
        inner_matrix[x][y]=value;
    }

///-------����ת��--------
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

///-------��ȡ�Ӿ���ĸ���--------
    Matrix& getSubMatrix(int x,int y) {
        Matrix subMatrix = Matrix(x,y);
        for(int i=0; i<x; i++) {
            for(int j=0; j<y; j++) {
                subMatrix.setValue(i,j,inner_matrix[i][j]);
            }
        }
        return subMatrix;
    }

///--------�����һ�������-------
    Matrix& dotProduct(double aValue) {
        int i,j;
        for(i=0; i<xx; i++) {
            for(j=0; j<yy; j++) {
                inner_matrix[i][j]=inner_matrix[i][j]*aValue;
            }
        }
        return *this;
    }

///-------�����������-------
    Matrix& matrixProduct(Matrix& anotherMatrix) {
        if(yy!=anotherMatrix.getX()) {
            cerr<<"���������޷���ˣ�"<<endl;
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

///-------���������ֵ����������-------
    void power() {
        Matrix xk=getSubMatrix(xx,1);//ȡ��һ��Ϊxk
        double c=0;
        Matrix yk=Matrix();
        int count=50;//��������
        Matrix old_xk=xk;

        while(count>0) {
            yk=matrixProduct(xk);
            c=xk.findMaxElement(xk.getX(),1);
            xk=yk.dotProduct(1/c);

//���´��������⣬�����С�����������epsilon���Ǻܴ�
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

///-------��ȡ/��ӡ����ֵ��������-------
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
        cout<<"\n��������ֵ�ǣ�"<<eigenValue<<endl;
    }
    void displayEigenVector() {
        checkCal();
        eigenVector->displayMatrix("�������������");
    }

    void checkCal() {
        if(!hasCal) {
            power();
        }
    }

///-------���/��ʾ��һ����������-------
    Matrix& getNormalizedEigenVector() {
        checkCal();
        return eigenVector->dotProduct(1/eigenVector->sum());
    }

///-------���һ����ָ��CI-------
    double CI() {
        checkCal();
        return (eigenValue-xx)/(xx-1.0);
    }

///-------------���RI------------

    double RI() {
        return RI_DATA[xx-1];
    }

///-------����һ���Ա���CR-------
    double CR() {
        return  CI()/RI();
    }

///-------��ʾ��ε�����������Ϣ-------
    void displayCalInfo(){
        cout<<"CI��"<<CI()<<"\nLamda��"<<getEigenValue()<<endl;
        getNormalizedEigenVector().displayMatrix("��һ������");
    }

};


#endif // MATRIX_H_INCLUDED
