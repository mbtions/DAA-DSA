#include<iostream>
using namespace std;
#define MAX 20
int M[MAX]; // global memoization array

struct Interval 
{
	int startTime;
	int finishTime;
	int Weight;
};

class WIS 
{
	Interval I[MAX]; 	// Intervals array
	
	public:
		int n; 			// number of intervals
		
		// constructor to initialize the memoization array as {0,0,0,0,...}
		WIS () 
		{
			for (int i = 0; i <= MAX; i++)
				M[i] = 0;
		}
		
		void sortIntervals(); 	// sorting the intervals
		int mComputeOpt(int); 	// computing maximum weighted scheduling
		void input();			// function to get input		
		int p(int);				// getting last(recently) finished non-overlapping interval
};

int WIS::p(int j) 
{
	for (int i = j-1; i > 0; i--) 
	{
		if (I[i].finishTime <= I[j].startTime)
			return i;
	}
	return 0;
}

void WIS::input()
{
	cout<<"Enter the number of Intervals: ";
	cin>>n;
	
	cout<<"Enter the starting time <Si>, finishing time <Fi> and Weight value <Vi> for the intervals: ";
	cout<<"\n\nSi Fi Vi\n";
	for (int i=1; i<=n; i++)
	{
		cin>>I[i].startTime;
			
		cin>>I[i].finishTime;
		
		cin>>I[i].Weight;
	}
}

void WIS::sortIntervals() 
{
	int i, flag=1;
	Interval temp; // temporary interval
	
	for (i = 1; (i <= n) && flag; i++) 
	{
		flag = 0;
		
		for (int j = 1; j < n; j++)
		{
			if (I[j+1].finishTime < I[j].finishTime)
			{
				temp = I[j];
				I[j] = I[j+1];
				I[j+1] = temp;
				flag=1; // swapped
			}
		}
	}
	
	for (i = 1; i <= n; i++) 
	{
		for (int j = i+1; j <= n; j++)
		{
			if (I[i].finishTime == I[j].finishTime && I[i].startTime > I[j].startTime) 
			{
				temp = I[i];
				I[i] = I[j];
				I[j] = temp;
			}
		}
	}
	
	cout<<"I<i>\t\tS<i>\t\tF<i>\t\tV<i>\n";
	for(int i = 1; i <= n; i++)
	{
		cout<<i<<"\t\t"<<I[i].startTime<<"\t\t"<<I[i].finishTime<<"\t\t"<<I[i].Weight<<"\n";
	}
}

int WIS::mComputeOpt(int j) 
{
	if (j == 0) 
	{
		return 0;
	}
	else if (M[j])
	{
		return M[j];
	}
	else
	{
		M[j] = max((I[j].Weight + mComputeOpt(p(j))), mComputeOpt(j-1));
	}	 

	return M[j];
}

int main() 
{
	WIS job;
	
	job.input();
	
	cout<<"\nSorted Input Intervals: \n";
	job.sortIntervals();
	
	cout<<endl;
	
	for(int i = 1; i <= job.n; i++)
		cout<<"OPT["<<i<<"]\t";
		
	cout<<endl;
	
	for(int i = 1; i <= job.n; i++)
		cout<<job.mComputeOpt(i)<<"\t";
		
	return 0;
}

