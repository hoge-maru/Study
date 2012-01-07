
#include <fstream>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <sstream>

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
const int MAXDATE = 100;
int candidate_table[MAXDATE];

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

void cleartable()
{
	memset(candidate_table, 0, sizeof(candidate_table));
}

void init()
{
	cleartable();

}



int getDate(int quorum)
{
	int max = INT_MIN;
	int candidate = 0;
	REP(i, MAXDATE)
	{
		int val = std::max(candidate_table[i], max);
		
		//update
		if(val > max){
			candidate = i;
			max = val;
		}
	}

	if(max >= quorum){
		return candidate;
	}
	else{
		return 0;
	}
}

int main()
{
	std::string str;
	init();

	while(true){
		int n = 0;
		int quorum = 0;
		readline(str);
		sscanf(str.c_str(), "%d %d", &n, &quorum);
		if(n == 0 && quorum == 0)
			break;

		REP(i, n){
			readline(str);
			std::stringstream ss(str);

			int num = 0;
			ss>>num;
			while(num-- > 0){
				int val = 0;
				ss>>val;
				candidate_table[val]++;
			}
		}
		int date = getDate(quorum);

		cout<<date<<endl;
		cleartable();
	}


	end();

	return 0;

}

