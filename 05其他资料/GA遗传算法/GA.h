#include<vector>

using namespace std;

const double pai=3.1415926;

class Genome
{
public:

	 friend class GenAlg;
	 friend class GenEngine;

	 Genome():fitness(0){}
		
     Genome(vector <double> vec, double f): vecGenome(vec), fitness(f){}  //��Ĵ�������ʼ��������
private:
	 vector <double> vecGenome;  // dFitness���ڴ洢�Ըû������Ӧ��������
	
	 double fitness; //����޲�����ʼ��������

};

//�Ŵ��㷨
class GenAlg	
	{
	
	public:
	
	//�������������ÿһ�������Ⱦɫ��
	
	vector <Genome>    vecPop;
	
	//�˿�(��Ⱥ)����
	
	int popSize;
	
    //ÿһ��Ⱦɫ��Ļ��������Ŀ
	
	int chromoLength;
	
	//���и����Ӧ����Ӧ�����ֵ��ܺ�
	
	double totalFitness;
	
	//�����и��嵱������Ӧ�ĸ������Ӧ������
	
	double bestFitness;
	
	//���и������Ӧ�����ֵ�ƽ��ֵ
	
	double averageFitness;
	
	//�����и��嵱�����Ӧ�ĸ������Ӧ������
	
	double worstFitness;
	
	//����Ӧ�ĸ�����m_vecPop���������������
	
	Genome fittestGenome;
	
	//����ͻ��ĸ���,һ�����0.05��0.3֮��
	
	double mutationRate;
	
	//���򽻲�ĸ���һ����Ϊ0.7
	
	double crossoverRate;
	
	//�����ļ�����
	
	int generation;

	//�����첽��

	double maxPerturbation;

	double leftPoint;

	double rightPoint;
	
	//���캯��
	
	GenAlg();
	
	//��ʼ������
	
	void Reset();
	
	//��ʼ������

	void init(int popsize, double MutRate, double CrossRate, int GenLenght,double LeftPoint,double RightPoint);
	
	//����TotalFitness, BestFitness, WorstFitness, AverageFitness�ȱ���
	
	void CalculateBestWorstAvTot();
	
	//���̶�ѡ����
	
	Genome GetChromoRoulette();


	//������캯��
	
	void Mutate(vector<double> &chromo);
	
	//�⺯��������һ������
	
	void Epoch(vector<Genome> &vecNewPop);
	
	Genome GetBestFitness();

	double GetAverageFitness();
	};

class Curve
{
public:
	double function(const vector<double>& input)
	{
		double x=input[0];
        double output;
		output=x*sin(10*pai*x)+2.0;
		return output;
	}

private:
	
	
};

//�Ŵ���������

class GenEngine
{
public:
	GenEngine(const int& popsize,const double& mutationRate,const double& crossoverRate,const int&numGen,const int&generation
		,const double& leftPoint, const double& rightPoint):genAlg(),curve(),m_population()
	{
		g_popsize=popsize;
		g_dMutationRate=mutationRate;
		g_dCrossoverRate=crossoverRate;
		g_numGen=numGen;
		g_Generation=generation;
		g_LeftPoint=leftPoint;
		g_RightPoint=rightPoint;
	    bestFitness=0;
        bestSearch=0;
		
	}
	
	void OnStartGenAlg();

	//����ÿһ�����������

	void report(const int&genNum);


	
private:
	GenAlg genAlg;
	Curve curve;
	vector<Genome> m_population;
	int g_popsize;
	double g_dMutationRate;
	double g_dCrossoverRate;
	int g_numGen;
	int g_Generation;
	double g_LeftPoint;
	double g_RightPoint;
	double bestFitness;
    double bestSearch;
	double averageFitness;



};




