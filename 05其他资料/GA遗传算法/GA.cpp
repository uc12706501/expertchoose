#include<vector>

#include<stdio.h>
#include <stdlib.h>
#include <time.h>
#include<iostream>
#include"GA.h"
	
using namespace std;


//srand((unsigned) time(NULL));

double random()
{
	double randNum;
	randNum=rand()*1.0/RAND_MAX;
	return randNum;
}

 GenAlg::GenAlg()
{

}



void GenAlg::init(int popsize, double MutRate, double CrossRate, int GenLenght,double LeftPoint,double RightPoint)

{

	popSize = popsize;

	mutationRate = MutRate;

	crossoverRate = CrossRate;

	chromoLength = GenLenght;

	totalFitness = 0;

	generation = 0;

	//fittestGenome = 0;

	bestFitness = 0.0;

	worstFitness = 99999999;

	averageFitness = 0;

	maxPerturbation=0.004;

	leftPoint=LeftPoint;

	rightPoint=RightPoint;

	//�����Ⱥ�������Գ�ʼ��

	vecPop.clear();

	for (int i=0; i<popSize; i++)

	{     

		//��Ĺ��캯���Ѿ�����Ӧ�����ֳ�ʼ��Ϊ0

		vecPop.push_back(Genome());

		//�����еĻ�������ʼ��Ϊ���������ڵ��������

		for (int j=0; j<chromoLength; j++)

		{
			
			vecPop[i].vecGenome.push_back(random() * 

				(rightPoint - leftPoint) + leftPoint);

		}

	}

}

void GenAlg::Reset()
{
	totalFitness=0;
	//bestFitness=0;
    //worstFitness=9999;
	averageFitness=0;
	
}

void GenAlg::CalculateBestWorstAvTot()
{
	for (int i=0; i<popSize; ++i)

	{

		//�ۼ���Ӧ�Է���.
		totalFitness+= vecPop[i].fitness;

		if(vecPop[i].fitness>=bestFitness)
		{
			bestFitness=vecPop[i].fitness;
			fittestGenome=vecPop[i];
		}

		if(vecPop[i].fitness<=worstFitness)
			worstFitness=vecPop[i].fitness;
		
	}

	averageFitness=totalFitness/popSize;



}



Genome GenAlg:: GetChromoRoulette()

{

	//����һ��0���˿�����Ӧ�������ܺ�֮��������.

	//��m_dTotalFitness��¼��������Ⱥ����Ӧ�Է����ܺ�)

	double Slice = (random()) * totalFitness;

	//������򽫳���ת����ѡ�������Ǹ�����.

	Genome TheChosenOne;

	//�ۼ���Ӧ�Է����ĺ�.

	double FitnessSoFar = 0;

	//�������˿������ÿһ��Ⱦɫ�塣

	for (int i=0; i<popSize; ++i)

	{

		//�ۼ���Ӧ�Է���.

		FitnessSoFar += vecPop[i].fitness;

		//����ۼƷ������������,��ѡ���ʱ�Ļ���.

		if (FitnessSoFar >= Slice)

		{

			TheChosenOne = vecPop[i];

			break;

		}

	}

	//����ת��ѡ�����ĸ������

	return TheChosenOne;

}

void GenAlg::Mutate(vector<double> &chromo)
{	

	//��ѭԤ����ͻ�����,�Ի������ͻ��

	for (int i=0; i<chromo.size(); ++i)

	{

		//�������ͻ��Ļ�

		if (random() < mutationRate)

		{

			//ʹ��Ȩֵ���ӻ��߼���һ����С�������ֵ

			chromo[i] += ((random()-0.5) * maxPerturbation);

			//��֤��������������Ȼ������.

			if(chromo[i] < leftPoint)

			{

				chromo[i] = rightPoint;

			}

			else if(chromo[i] > rightPoint)

			{

				chromo[i] = leftPoint;

			}

			//���ϴ���ǻ�������һ���Դ���ֻ��������֤�������Ŀ����ԡ�

		}


	}
}

	//�˺��������µ�һ��,��֤������������ȫ����.
	
	//�Ը�����Ⱥ�Ļ�����������Ϊ��������ȥ,�ú��������������������һ���Ļ�����(��Ȼ�Ǿ�������ʤ��̭��)
	
void GenAlg::Epoch(vector<Genome> &vecNewPop)

{

	//����ĳ�Ա���������游���Ļ�����(�ڴ�֮ǰm_vecPop������ǲ�����ֵ�����л�����)

	vecPop = vecNewPop;

	//��ʼ����ر���

	Reset();

	//Ϊ��ر�����ֵ

	CalculateBestWorstAvTot();

	//���װ������Ⱥ������

	vecNewPop.clear();       

	//������һ�������л�����

	while (vecNewPop.size() < popSize)

	{

		//ת����������������

		Genome mum = GetChromoRoulette();

		Genome dad = GetChromoRoulette();

		//���������Ӵ�������

		vector<double> baby1, baby2;

		//�Ȱ����Ƿֱ����óɸ�����ĸ���Ļ���

		baby1 = mum.vecGenome;

		baby2 = dad.vecGenome;

		//ʹ�Ӵ�����������ͻ��

		Mutate(baby1);

		Mutate(baby2);

		//�������Ӵ�������ŵ��µĻ�������������

		vecNewPop.push_back( Genome(baby1, 0) );

		vecNewPop.push_back( Genome(baby2, 0) );

	}//�Ӵ��������

	//��������õ��˿������ǵ����Ļ�,�ͻ���ֱ���

	if(vecNewPop.size() != popSize)

	{

		//MessageBox("����˿���Ŀ���ǵ���!!!");
		cout<<"error"<<endl;

		return;

	}

}

Genome GenAlg::GetBestFitness()
{
	return fittestGenome;
}

double GenAlg::GetAverageFitness()
{
	return averageFitness;
}

void GenEngine::report(const int&genNum)
{
	cout<<"��"<<genNum<<"��"<<endl;
    cout<<"�����Ӧ�ȣ�"<<bestFitness<<endl;
	cout<<"�����Ӧ�Ȼ���ȡֵ��"<<bestSearch<<endl;
	cout<<"ƽ����Ӧ�ȣ�"<<averageFitness<<endl<<endl;
}


void GenEngine:: OnStartGenAlg()
	
{
	

	//���������

	srand( (unsigned)time( NULL ) );

	//��ʼ���Ŵ��㷨����

	genAlg.init(g_popsize, g_dMutationRate, g_dCrossoverRate, g_numGen,g_LeftPoint,g_RightPoint);

	//�����Ⱥ����

	m_population.clear();

	//��Ⱥ����װ�����������ʼ������Ⱥ

	m_population = genAlg.vecPop;

	//����������������װ�������������뼰�����������������ǵ����뵥����ģ������Ժ�����������ô�򵥣�������������������������׼������

	vector <double> input;
	double output;

	input.push_back(0);

	for(int Generation = 0;Generation <= g_Generation;Generation++)

	{

		//�����Ƕ�ÿһ��Ⱦɫ����в���

		for(int i=0;i<g_popsize;i++)

		{

			input = m_population[i].vecGenome;

			//Ϊÿһ����������Ӧ�����ۣ���֮ǰ˵�ģ����۷������Ǻ���ֵ����

			//Function�����������������Ա������غ���ֵ�����߿��Բο�����롣

			output = (double)curve.function(input);
		
			m_population[i].fitness = output;

		}

		//�ɸ�����Ⱥ�������Ӵ���Ⱥ������������ǰ�ˡ���

		genAlg.Epoch(m_population);

		
		//if(genAlg.GetBestFitness().fitness>=bestFitness)
		bestSearch=genAlg.GetBestFitness().vecGenome[0];
		bestFitness=genAlg.GetBestFitness().fitness;
		averageFitness=genAlg.GetAverageFitness();
		//cout<<bestSearch<<endl;
		report(Generation+1);
	}

	//return bestSearch;

}

