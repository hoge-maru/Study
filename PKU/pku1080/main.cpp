
#include <fstream>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <limits.h>

#include <map>

using namespace std;
#define FILE

#ifdef FILE
std::ifstream ifs("input.txt");
std::ofstream ofs("out.txt");
#define readline(str) getline(ifs, str)
#else
#define readline(str) getline(cin, str)
#endif


#define REP(i, x) for(int i = 0; i < x; i++)
#define REP1(i, x) for(int i = 1; i <= x; i++)

const int MAX = 500;
int exlcstable[MAX][MAX];

int N = 0;

const int PMAX = 5;
const char psec[] = {'A', 'C', 'G', 'T', '-'};
const int POINTT[PMAX][PMAX] = {{5, -1, -2, -1, -3}, {-1, 5, -3, -2, -4}, {-2, -3, 5, -2, -2}, {-1, -2, -2, 5, -1}, {-3, -4, -2, -1, 0}};

map<char, int> pmap;

void init()
{
	REP(i, MAX){
		REP(j, MAX){

			exlcstable[i][j] = 0;
		}
	}

	REP(i, PMAX){
		pmap.insert(map<char, int>::value_type(psec[i], i));
	}

}


int main()
{
	std::string str;
	init();

	readline(str);
	sscanf(str.c_str(), "%d", &N);

	while(N-- > 0)
	{
		char buf1[MAX];
		char buf2[MAX];
		memset(buf1, 0, sizeof(buf1));
		memset(buf2, 0, sizeof(buf2));

		int val1 = 0;
		int val2 = 0;

		readline(str);
		sscanf(str.c_str(), "%d %s", &val1, buf1);
		readline(str);
		sscanf(str.c_str(), "%d %s", &val2, buf2);
		
		REP1(i1, val1){
			char hi = '-';
			char c = buf1[i1-1];
			int p = POINTT[pmap[hi]][pmap[c]];
			exlcstable[i1][0] = p + exlcstable[i1-1][0];
		}
		REP1(i2, val2){
			char hi = '-';
			char c = buf2[i2-1];
			int p = POINTT[pmap[hi]][pmap[c]];
			exlcstable[0][i2] = p + exlcstable[0][i2-1];
		}

		REP1(i1, val1){
			char c1 = buf1[i1-1];
			REP1(i2, val2){
				char c2 = buf2[i2-1];
				if(c1==c2){
					int index1 = pmap[c1];
					int index2 = pmap[c2];
					int point = POINTT[index1][index2];
					char hi = '-';

					int val1 = exlcstable[i1-1][i2-1] + point;
					int val2 = exlcstable[i1-1][i2] + POINTT[pmap[c1]][pmap[hi]];
					int val3 = exlcstable[i1][i2-1] + POINTT[pmap[hi]][pmap[c2]];

					int val = std::max(std::max(val1, val2), val3);
					exlcstable[i1][i2] = val;

				}else{
					int index1 = pmap[c1];
					int index2 = pmap[c2];
					int point = POINTT[index1][index2];
					char hi = '-';

					int val1 = exlcstable[i1-1][i2-1] + point;
					int val2 = exlcstable[i1-1][i2] + POINTT[pmap[c1]][pmap[hi]];
					int val3 = exlcstable[i1][i2-1] + POINTT[pmap[hi]][pmap[c2]];

					int val = std::max(std::max(val1, val2), val3);

					exlcstable[i1][i2] = val;
				}
			}
		}

		cout<<exlcstable[val1][val2]<<endl;

	}



#ifdef FILE
	ifs.close();
	ofs.close();
#endif

	return 0;

}

