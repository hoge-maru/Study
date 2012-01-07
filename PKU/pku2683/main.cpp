#include <fstream>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

using namespace std;
#define FILE

#ifdef FILE
std::ifstream ifs("input.txt");
std::ofstream ofs("out.txt");
#define readline(str) getline(ifs, str)
#else
#define readline(str) getline(cin, str)
#endif

int N =0;

void end()
{
#ifdef FILE
	ifs.close();
	ofs.close();
#else

#endif
}

#define REP(i, x) for(int i = 0; i < x; i++)
#define REP1(i, x) for(int i = 1; i <= x; i++)

enum{
	SINPLE = 0,
	COMPOUND
};


void init()
{
}

double calcSinpleInterest(int fund, double rate, double charge, int year)
{
	int cummlativeInterest = 0;
	double cfund = fund;
	REP(i, year){
		double interest = cfund * rate;
		interest = floor(interest);
		cummlativeInterest += interest;

		cfund -= charge;
	}

	cfund += cummlativeInterest;

	return cfund;

}

double calcCompoundInterest(int fund, double rate, double charge, int year)
{
	double cfund = fund;
	REP(i, year){
		double interest = cfund * rate;
		interest = floor(interest);

		cfund += interest;
		cfund -= charge;
	}

	return cfund;
}


int main()
{
	std::string str;
	init();

	readline(str);
	sscanf(str.c_str(), "%d", &N);


	int n, r;
	while(N-- > 0){

		double initialFund = 0;
		int initialOperationYear = 0;
		int operations = 0;

		readline(str);
		sscanf(str.c_str(), "%lf", &initialFund);

		readline(str);
		sscanf(str.c_str(), "%d", &initialOperationYear);
		readline(str);
		sscanf(str.c_str(), "%d", &operations);

		double max = -1;
		REP(i, operations){
			int flag;
			double rate;
			double charge;

			readline(str);
			sscanf(str.c_str(), "%d %lf %lf", &flag, &rate, &charge);

			double rtn = 0;
			if(flag == SINPLE){
				rtn = calcSinpleInterest(initialFund, rate, charge, initialOperationYear);
			}else{
				rtn = calcCompoundInterest(initialFund, rate, charge, initialOperationYear);
			}
			max = std::max(rtn, max);

		}

		printf("%.0f\n", max);

	}


	end();

	return 0;

}