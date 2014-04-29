#include<vector>

using namespace std;

const double pai=3.1415926;

class Genome
{
public:

	 friend class GenAlg;
	 friend class GenEngine;

	 Genome():fitness(0){}
		
     Genome(vector <double> vec, double f): vecGenome(vec), fitness(f){}  //类的带参数初始化参数。
private:
	 vector <double> vecGenome;  // dFitness用于存储对该基因的适应性评估。
	
	 double fitness; //类的无参数初始化参数。

};

//遗传算法
class GenAlg	
	{
	
	public:
	
	//这个容器将储存每一个个体的染色体
	
	vector <Genome>    vecPop;
	
	//人口(种群)数量
	
	int popSize;
	
    //每一条染色体的基因的总数目
	
	int chromoLength;
	
	//所有个体对应的适应性评分的总和
	
	double totalFitness;
	
	//在所有个体当中最适应的个体的适应性评分
	
	double bestFitness;
	
	//所有个体的适应性评分的平均值
	
	double averageFitness;
	
	//在所有个体当中最不适应的个体的适应性评分
	
	double worstFitness;
	
	//最适应的个体在m_vecPop容器里面的索引号
	
	Genome fittestGenome;
	
	//基因突变的概率,一般介于0.05和0.3之间
	
	double mutationRate;
	
	//基因交叉的概率一般设为0.7
	
	double crossoverRate;
	
	//代数的记数器
	
	int generation;

	//最大变异步长

	double maxPerturbation;

	double leftPoint;

	double rightPoint;
	
	//构造函数
	
	GenAlg();
	
	//初始化变量
	
	void Reset();
	
	//初始化函数

	void init(int popsize, double MutRate, double CrossRate, int GenLenght,double LeftPoint,double RightPoint);
	
	//计算TotalFitness, BestFitness, WorstFitness, AverageFitness等变量
	
	void CalculateBestWorstAvTot();
	
	//轮盘赌选择函数
	
	Genome GetChromoRoulette();


	//基因变异函数
	
	void Mutate(vector<double> &chromo);
	
	//这函数产生新一代基因
	
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

//遗传运算引擎

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

	//报告每一代的运行情况

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




