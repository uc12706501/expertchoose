#ifndef AHP_H_INCLUDED
#define AHP_H_INCLUDED

#include <iostream>
#include <math.h>
#include <vector>
#include "matrix.h"

using namespace std;

class AHP
{
private:
    int a,b;
    Matrix single_matrix;
    vector<Matrix> array_matrix;
    Matrix result_matrix;   //��¼���������
    double totalCR;  //�������һ���Լ���

public:

///-------------���캯��--------------
    AHP() {
        //init();
    }
///-------------��ʼ��a,b����������ԱȾ���--------------
    void init() {
        //����a��b
        cout<<"������׼�������������"<<endl;
        cin>>a;
        cout<<"�����뷽��������������"<<endl;
        cin>>b;

        //���ò�����������
        result_matrix=Matrix(b,1);

        //����ɶԱȾ���
        single_matrix=Matrix(a,a);
        single_matrix.inputMatrix();

        for(int i=0; i<a; i++) {
            Matrix temp = Matrix(b,b);
            temp.inputMatrix();
            array_matrix.push_back(temp);
        }
    }
///-------------��ȡ������A/B---------------
    int getA() {
        return a;
    }
    void setA(int value) {
        a=value;
    }
    int getB() {
        return b;
    }
    void setB(int value) {
        b=value;
    }

///-------------��ʾ�ɶԱȾ���---------------
    void displayInnerMatrix() {
        single_matrix.displayMatrix("A");

        for(int i=0; i<a; i++) {
            cout<<"B"<<i+1<<"��"<<endl;
            array_matrix[i].displayMatrix();
        }
    }

///-----------��ε�����һ���Լ���-------------
    void singleSortCheck() {
        cout<<"\n\n--------------->��ε�������һ���Լ���<-----------------\n"<<endl;

        //A��Z�Ĳ�ε�����һ���Լ���
        double temp=single_matrix.CR();
        while(temp>=0.1) {
            cout<<"\n׼������Ŀ���CRΪ��"<<temp<<"��\nδͨ��һ���Լ��飬����������׼������Ŀ��ĳɶԱȾ���"<<endl;
            single_matrix.inputMatrix();
            temp=single_matrix.CR();
        }
        cout<<"\n׼������Ŀ���CRΪ��"<<temp<<"��\tͨ��һ���Լ���"<<endl;
        single_matrix.displayCalInfo();


        //B��Ai�Ĳ�ε�������һ���Լ���
        for(int i=0; i<a; i++) {
            Matrix currentMatrix=array_matrix[i];
            while(currentMatrix.CR()>=0.1) {
                cout<<"\n������B��A"<<i+1<<"��CRΪ��"<<currentMatrix.CR()<<"��\nδͨ��һ���Լ��飬����������ɶԱȾ���"<<endl;
                array_matrix[i].inputMatrix();
            }
            cout<<"\n������B��A"<<i+1<<"��CRΪ��"<<currentMatrix.CR()<<"��\tͨ��һ���Լ���"<<endl;
            currentMatrix.displayCalInfo();
        }
    }

///-----------�����������һ���Լ���-------------
    void totalSortCheck() {
        cout<<"\n\n-------------->�����������һ���Լ���<-----------------\n"<<endl;

        Matrix totalVector=single_matrix.getNormalizedEigenVector();//A�ĵ�����������
        Matrix currentMatrix;   //����B�ԱȾ���ʱ��ָ��ǰ�Ĳ�������
        double tempValue=0; //�ۼ�������ֵ����ʱ��
        double ai=0;    //A�����Ŀ�������
        double totalCI,totalRI;

        for(int i=0; i<b; i++) {
            totalCI=totalRI=tempValue=0;
            for(int j=0; j<a; j++) {
                currentMatrix=array_matrix[j];
                ai=totalVector.getValue(j,0);
                double c=currentMatrix.getNormalizedEigenVector().getValue(i,0);
                tempValue+=c*ai;

                totalCI+=currentMatrix.CI()*ai;
                totalRI+=currentMatrix.RI()*ai;
            }
            result_matrix.setValue(i,0,tempValue);//���������������
        }

        totalCR=totalCI/totalRI;
    }

///-----------��ʾ���------------
    void displayResult() {
        result_matrix.displayMatrix("���������");
        cout<<"���������һ���Լ�����Ϊ��"<<totalCR<<endl;
    }

///-----------�����������------------
    void insertTestData() {
        a=5;
        b=3;
        cout<<"a��"<<a<<"\tb��"<<b<<"\n"<<endl;

        //���ò�����������
        result_matrix=Matrix(b,1);

        double a_array[25]= {1,0.5,4,3,3,2,1,7,5,5,1/4.0,1/7.0,1,1/2.0,1/3.0,1/3.0,1/5.0,2,1,1,1/3.0,1/5.0,3,1,1};
        single_matrix=Matrix(a,a);
        single_matrix.insertFromArray(a_array);

        Matrix temp1 = Matrix(b,b);
        double b1[9]= {1,2,5,1/2.0,1,2,1/5.0,1/2.0,1};
        temp1.insertFromArray(b1);
        array_matrix.push_back(temp1);

        Matrix temp2 = Matrix(b,b);
        double b2[9]= {1,1/3.0,1/8.0,3,1,1/3.0,8,3,1};
        temp2.insertFromArray(b2);
        array_matrix.push_back(temp2);

        Matrix temp3 = Matrix(b,b);
        double b3[9]= {1,1,3,1,1,3,1/3.0,1/3.0,1};
        temp3.insertFromArray(b3);
        array_matrix.push_back(temp3);

        Matrix temp4 = Matrix(b,b);
        double b4[9]= {1,3,4,1/3.0,1,1,1/4.0,1,1};
        temp4.insertFromArray(b4);
        array_matrix.push_back(temp4);

        Matrix temp5 = Matrix(b,b);
        double b5[9]= {1,1,1/4.0,1,1,1/4.0,4,4,1};
        temp5.insertFromArray(b5);
        array_matrix.push_back(temp5);

        displayInnerMatrix();
    }
};


#endif // AHP_H_INCLUDED
