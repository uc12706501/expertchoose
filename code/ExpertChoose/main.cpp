#include <iostream>
#include "matrix.h"
#include "ahp.h"
using namespace std;

void matrix_test()
{

    Matrix m1=Matrix(2,3);
    Matrix m2=Matrix(3,4);

    int i=0,j=0,count=0;

    for(i=0; i<m1.getX(); i++) {
        for(j=0; j<m1.getY(); j++) {
            m1.setValue(i,j,++count);
        }
    }
    cout<<"m1:\tx："<<m1.getX()<<"\ty："<<m1.getY()<<endl;
    m1.displayMatrix("m1");

    count=0;
    for(i=0; i<m2.getX(); i++) {
        for(j=0; j<m2.getY(); j++) {
            m2.setValue(i,j,++count);
        }
    }
    m2.displayMatrix("m2");

    cout<<"m2中的最大数为："<<m2.findMaxElement()<<endl;
    cout<<"m2第一列中的最大值为："<<m2.findMaxElement(m2.getX(),1)<<endl;

    Matrix m3=m2.getSubMatrix(3,2);
    m3.displayMatrix("m3");
    m3=m2.getSubMatrix(3,3);
    m3.displayMatrix("m3");
    m3.transpose();
    m3.displayMatrix("m3转置之后");

    Matrix m4=m1.matrixProduct(m2);
    m4.displayMatrix("m1*m2");

    m1.dotProduct(2.1);
    cout<<"\nm1点乘2.1之后为"<<endl;
    m1.displayMatrix();

    Matrix m5=Matrix(3,3);
    m5.setValue(0,0,2);
    m5.setValue(0,1,2);
    m5.setValue(0,2,-2);
    m5.setValue(1,0,2);
    m5.setValue(1,1,5);
    m5.setValue(1,2,-4);
    m5.setValue(2,0,-2);
    m5.setValue(2,1,-4);
    m5.setValue(2,2,5);
    m5.displayMatrix("m5");
    m5.power();
    m5.displayEigenValue();
    m5.displayEigenVector();
}

void ahp_test()
{
    AHP ahptester=AHP();
    ahptester.insertTestData(); //插入测试数据
    ahptester.singleSortCheck();    //层次单排序及其一致性检验
    ahptester.totalSortCheck();     //层次总排序及其一致性检验
    ahptester.displayResult();
}

int main()
{
    cout << "Let's begin!" << endl;
    //matrix_test();
    ahp_test();

    return 0;
}
