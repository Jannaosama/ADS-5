
#include<string>
#include<iostream>
#include<vector>
#include <algorithm>
#include<queue>
#include<numeric>
#include<fstream>
#include<sstream>

using namespace std;

struct ExchangeRate{
	string date;
	double rate;
	double ChangeFromMean;

ExchangeRate (string d, double r, double c) //Constructer to initialize the objects of the previous struct
{
	date = d;
	rate = r;
	ChangeFromMean = c;
}
};
ExchangeRate ExchangeRateObject(string date1, double rate1, double ChangeFromMean1);

vector<ExchangeRate> readCSV(const string& EuroDollar )
{
	vector <ExchangeRate> ExchangeRateVector;
	ifstream file(EuroDollar);
	if (!file.is_open())
	{
		cout << "Error opening the file" << EuroDollar << endl;
		return ExchangeRateVector;
	}
	string line;
	while (getline(file, line))
	{
		stringstream ss(line);
		string date;
		double rate;
		double ChangeFromMean;
		char delimiter = ',';

		if (getline(ss, date, delimiter) && ss >> rate >> delimiter >> ChangeFromMean)
		{
			ExchangeRateVector.emplace_back(date, rate, ChangeFromMean);
		}
		else {
			cout << "Error reading line :" << line << endl;
		}
	}
	file.close();
	return ExchangeRateVector;
}

double CalculateMeanExchangeRate(vector <ExchangeRate>& ExchangeRateVector )
{
	double SumExchangeRate = 0;
	int TotalDays = ExchangeRateVector.size();

	for (const auto&rate1 : ExchangeRateVector)
	{
		SumExchangeRate += rate1.rate;
	}

	double Mean = SumExchangeRate / TotalDays;

	cout << "Total number of days " << TotalDays << endl;
	cout << " Sum of all exchange Rates " << SumExchangeRate << endl;
	cout << " Mean : Average Exchange over a period of time" << Mean << endl;
	return Mean;

}
vector<double>CalculateChangeFromMean(vector<ExchangeRate>& ExchangeRateVector, double Mean)
{
	vector<double> ChangeFromMean;
	for (const auto& rate : ExchangeRateVector)
	{
		ChangeFromMean.push_back(rate.rate - Mean);
	}
	return ChangeFromMean;
}
void FindHighestNLowestN(vector<double>& ChangeFromMean, int n)
{
	priority_queue<double>maxheap(ChangeFromMean.begin(), ChangeFromMean.end());
	priority_queue<double, vector<double>, greater<>> minheap(ChangeFromMean.begin(), ChangeFromMean.end());

	cout << "N highest exchange rate days based on change from mean:" << endl;
	for (int i = 0; i < n; i++)
	{
		cout << maxheap.top() << "	";
		maxheap.pop();
	}
	cout << endl;

	cout << "N lowest exchange rate days based on change from mean" << endl;
	for (int i = 0; i < n;i++)
	{
		cout << minheap.top()<< "	";
		minheap.pop();
	}
	cout << endl;
}

void MaxSubsequenceSum(vector<double>& ChangeFromMean)
{
	int begin = 0;
	int end = 0;
	int CurrentStart= 0;
	double MaxSum = ChangeFromMean[0];
	double CurrentSum = ChangeFromMean[0];

	for (int i = 1; i < ChangeFromMean.size(); i++)
	{
		if (ChangeFromMean[i] > CurrentSum + ChangeFromMean[i])
		{
			CurrentSum = ChangeFromMean[i];
			CurrentSum = i;
		}
		else {
			CurrentSum += ChangeFromMean[i];
		}
		if (CurrentSum > MaxSum)
		{
			MaxSum = CurrentSum;
			begin = CurrentStart;
			end = i;
		}
	}
	cout << "Maximum Subsequence Sum" << MaxSum << endl;
	cout << "Start date:" << begin << ", End date: " << endl;
}
void BalanceHeapInsertion(vector<double>& heap, int index)
{
	while (index > 0 && (heap[(index - 1)] / 2) < heap[index])
	{
		swap (heap[(index-1)/2], heap[index]);
		index = (index - 1) / 2;
	}
}
void BalanceHeapRemoval(vector<double>& heap, int index, int heapSize)
{
	int max = index;
	int left  = 2 * index + 1;
	int right = 2 * index + 2;

	if (left<heapSize && heap[left]>heap[max])
	{
		max = left;
	}
	if (right<heapSize && heap[right]> heap[max])
	{
		max = right;
	}
	if (index != max)
	{
		swap(heap[index], heap[max]);
		BalanceHeapRemoval(heap, max, heapSize);
	}
}void insert(vector<double>& heap, double value)
{
	heap.push_back(value);
	BalanceHeapInsertion(heap, heap.size() - 1);
}
bool CheckEmptyHeap(vector<double>& heap)
{
	if (heap.empty())
	{
		cout << "Heap is empty" << endl;
		return 0;
	}
 }
double deleteMax(vector<double>& heap)
{
	if (CheckEmptyHeap(heap));

	double maxValue = heap[0];
	heap[0] = heap.back();
	heap.pop_back();
	BalanceHeapRemoval(heap, 0, heap.size());
	return maxValue;
}
double getMax(vector<double>& heap)
{
	if (CheckEmptyHeap(heap));
	return heap[0];
}

	
int main() {
	string EuroDollar = "C_Users_User_Documents_ADS 5_EuroDollar.csv"; 

	vector<ExchangeRate> exchangeRateData = readCSV(EuroDollar);

	CalculateMeanExchangeRate(exchangeRateData);

	double mean = CalculateMeanExchangeRate(exchangeRateData);
		vector<double> ChangeFromMean = CalculateChangeFromMean(exchangeRateData, mean);

	int N = 5;
	FindHighestNLowestN(ChangeFromMean, N);

	MaxSubsequenceSum(ChangeFromMean);

	return 0;
}
