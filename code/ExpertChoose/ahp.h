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
    Matrix result_matrix;   //记录层次总排序
    double totalCR;  //总排序的一致性检验

public:

///-------------构造函数--------------
    AHP() {
        //init();
    }
///-------------初始化a,b，输入各个对比矩阵--------------
    void init() {
        //输入a和b
        cout<<"请输入准则层因素数量："<<endl;
        cin>>a;
        cout<<"请输入方案层因素数量："<<endl;
        cin>>b;

        //设置层次总排序矩阵
        result_matrix=Matrix(b,1);

        //输入成对比矩阵
        single_matrix=Matrix(a,a);
        single_matrix.inputMatrix();

        for(int i=0; i<a; i++) {
            Matrix temp = Matrix(b,b);
            temp.inputMatrix();
            array_matrix.push_back(temp);
        }
    }
///-------------获取和设置A/B---------------
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

///-------------显示成对比矩阵---------------
    void displayInnerMatrix() {
        single_matrix.displayMatrix("A");

        for(int i=0; i<a; i++) {
            cout<<"B"<<i+1<<"："<<endl;
            array_matrix[i].displayMatrix();
        }
    }

///-----------层次单排序一致性检验-------------
    void singleSortCheck() {
        cout<<"\n\n--------------->层次单排序及其一致性检验<-----------------\n"<<endl;

        //A对Z的层次单排序一致性检验
        double temp=single_matrix.CR();
        while(temp>=0.1) {
            cout<<"\n准则层对总目标的CR为："<<temp<<"。\n未通过一致性检验，请重新输入准则层对总目标的成对比矩阵"<<endl;
            single_matrix.inputMatrix();
            temp=single_matrix.CR();
        }
        cout<<"\n准则层对总目标的CR为："<<temp<<"。\t通过一致性检验"<<endl;
        single_matrix.displayCalInfo();


        //B对Ai的层次单排序与一致性检验
        for(int i=0; i<a; i++) {
            Matrix currentMatrix=array_matrix[i];
            while(currentMatrix.CR()>=0.1) {
                cout<<"\n方案层B对A"<<i+1<<"的CR为："<<currentMatrix.CR()<<"。\n未通过一致性检验，请重新输入成对比矩阵"<<endl;
                array_matrix[i].inputMatrix();
            }
            cout<<"\n方案层B对A"<<i+1<<"的CR为："<<currentMatrix.CR()<<"。\t通过一致性检验"<<endl;
            currentMatrix.displayCalInfo();
        }
    }

///-----------层次总排序及其一致性检验-------------
    void totalSortCheck() {
        cout<<"\n\n-------------->层次总排序及其一致性检验<-----------------\n"<<endl;

        Matrix totalVector=single_matrix.getNormalizedEigenVector();//A的单排序结果矩阵
        Matrix currentMatrix;   //遍历B对比矩阵时，指向当前的操作矩阵
        double tempValue=0; //累加总排序值的临时量
        double ai=0;    //A层对总目标的排序
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
            result_matrix.setValue(i,0,tempValue);//将结果存入结果矩阵
        }

        totalCR=totalCI/totalRI;
    }

///-----------显示结果------------
    void displayResult() {
        result_matrix.displayMatrix("层次总排序");
        cout<<"层次总排序一致性检验结果为："<<totalCR<<endl;
    }

///-----------插入测试数据------------
    void insertTestData() {
        a=5;
        b=3;
        cout<<"a："<<a<<"\tb："<<b<<"\n"<<endl;

        //设置层次总排序矩阵
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
