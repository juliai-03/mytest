#include <stdio.h>
#include <iostream>
#include <vector>
#include <iostream>
#include <cmath>
#include <time.h>

#define graphVertices 7
#define edges 8
#define start 2
#define finish 5
#define combinations 256

using namespace std;

bool haveWay = false;
vector<double> probabilities;
int visited[graphVertices] = { 0 };
long double solveRES = 0;
double p = 0.125;
double eps = 0.01;
int N = (9 * 0.25) / (eps * eps);
int Nhw = 0;
double resLab1;
double resLab2Part1;
double resLab2Part2;
int lenMax = edges - 3;
int lenMin = 1;
int NPart2 = 0;

vector<int> generateMask()
{
	vector<int> res;
	for (int i = 0; i < edges; i++)
	{
		double g = (double)(rand()) / RAND_MAX;
		if (g > p)
		{
			res.push_back(0);
		}
		else
		{
			res.push_back(1);
		}
	}

	return res;
}

int weightMask(vector<int> mask)
{
	int res = 0;

	for (auto iter = mask.begin(); iter != mask.end(); iter++)
	{
		if (*iter == 1) res++;
	}

	return res;
}

vector < vector < int>> createMtx(int mtx[edges][2], vector<int> maska)
{
	vector < vector < int>> res;
	int step = 0;
	for (vector<int>::iterator iter = maska.begin(); iter != maska.end(); iter++,
		step++)
	{
		if (*iter == 1)
		{
			vector<int> tmpE;
			tmpE.push_back(mtx[step][0]);
			tmpE.push_back(mtx[step][1]);
			res.push_back(tmpE);
		}
	}
	return res;
}


void dfs(int cur, vector < vector < int>> mtx)
{
	if (cur == finish)
	{
		haveWay = true;
	}
	if (haveWay == true)
	{
		return;
	}
	visited[cur] = 1;
	for (int i = 0; i < mtx.size(); i++)
	{
		if (haveWay == true) { return; }
		if (mtx[i][0] == cur && visited[mtx[i][1]] == 0)
		{
			dfs(mtx[i][1], mtx);
		}
		else if (mtx[i][1] == cur && visited[mtx[i][0]] == 0)
		{
			dfs(mtx[i][0], mtx);
		}
	}
}

void myDecToBin(int number, vector<int>* res)
{
	res->clear();
	while (number > 0)
	{
		vector<int>::iterator it = res->begin();
		res->insert(it, number % 2);
		number = number / 2;
	}
	while (res->size() < edges)
	{
		vector<int>::iterator it = res->begin();
		res->insert(it, 0);
	}
}

void zeriongVisited()
{
	for (int i = 0; i < graphVertices; i++)
	{
		visited[i] = 0;
	}
}

void countProbability(vector < vector <int>> mtx)
{
	double res;
	// Count uints ============================================================
	double tmpRes1 = pow(p, mtx.size());
	int nullTmp = edges - mtx.size();
	// Count zeros ============================================================
	double tmpRes2 = pow((1 - p), nullTmp);
	res = tmpRes1 * tmpRes2;
	probabilities.push_back(res);
}

void solveLab1(int mtx[edges][2])
{
	for (int mask = 0; mask < combinations; mask++)
	{
		// Create params =====================================================

		vector<int> binMask;
		myDecToBin(mask, &binMask);
		vector < vector < int>> tmpMtx = createMtx(mtx, binMask);
		// Call DFS ==========================================================
		zeriongVisited();
		haveWay = false;
		dfs(start, tmpMtx);
		// Check result =======================================================
		if (haveWay == true)
		{
			countProbability(tmpMtx);
		}
	}
	// Cout results ===========================================================
	for (int i = 0; i < probabilities.size(); i++)
	{
		solveRES += probabilities[i];
	}
	//cout <<solveRES << endl;
	resLab1 = solveRES;
}

void solveLab2Part1(int mtx[edges][2])
{
	Nhw = 0;
	for (int i = 0; i < N; i++)
	{

		// Генерация маски ==========================================================================================

		vector<int> binMask =
			generateMask();

		// Создание списка ребер ====================================================================================

		vector < vector < int>> tmpMtx = createMtx(mtx, binMask);

		// Определение наличия пути в подграфе ======================================================================

		zeriongVisited();
		haveWay = false;
		dfs(start, tmpMtx);

		if (haveWay == true)
		{
			Nhw++;
		}
	}

	resLab2Part1 = (double)Nhw / N;
	//cout « "Epsilon: " « eps « endl;
	//cout « "Part1:\t\t" « pe « endl;
}

void solveLab2Part2(int mtx[edges][2])
{
	Nhw = 0;
	NPart2 = 0;
	for (int i = 0; i < N; i++)
	{

		// Генерация маски ===================================================================================

		vector<int> binMask = generateMask();

		// Определение веса ==================================================================================

		int w = weightMask(binMask);

		// Оптимизация =======================================================================================

		if (w > lenMax)
		{
			Nhw++;
			continue;
		}
		else if (w < lenMin)
		{
			continue;
		}
		else
		{
			NPart2++;
			// Создание списка ребер =========================================================================

			vector < vector < int>> tmpMtx = createMtx(mtx, binMask);

			// Определение наличия пути в подграфе ===========================================================

			zeriongVisited();
			haveWay = false;
			dfs(start, tmpMtx);

			if (haveWay == true)
			{
				Nhw++;
			}
		}
	}

	resLab2Part2 = (double)Nhw / N;
}

int main()
{
	// Init random ==============================================================================================

	srand((unsigned int)time(0));
	cout.precision(10);
	//cout << "All N: " << N << endl;


	// Different probabilities ===============================================================================

	for (p = 0.0; p <= 1.0; p = p + 0.1)
	{
		//p = q;
		//cout « "Pr: " « p;
		int mtx[edges][2];
		mtx[0][0] = 1;
		mtx[0][1] = 3;
		mtx[1][0] = 1;
		mtx[1][1] = 5;
		mtx[2][0] = 1;
		mtx[2][1] = 6;
		mtx[3][0] = 2;
		mtx[3][1] = 5;
		mtx[4][0] = 2;
		mtx[4][1] = 6;
		mtx[5][0] = 2;
		mtx[5][1] = 4;
		mtx[6][0] = 3;
		mtx[6][1] = 4;
		mtx[7][0] = 5;
		mtx[7][1] = 6;
		solveLab1(mtx);
		solveLab2Part1(mtx); //Имитационное моделирование
		solveLab2Part2(mtx); //Ускорение имитационного моделирования
		cout << "Pr: " << p << endl;
		cout << resLab1 << endl;
		cout << resLab2Part1 << endl;
		cout << resLab2Part2 << endl << endl;
		//cout << "N: \t\t" << NPart2 << endl;
		cout << "win: \t\t" <<(double)N / NPart2 << endl;
		//cout « "ThRES:\t\t" « thRES « "\n" «endl;
		haveWay = false;
		NPart2 = 0;
		Nhw = 0;
		probabilities.clear();
		zeriongVisited();
		solveRES = 0;
	}

	return 0;
}