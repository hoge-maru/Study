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

const int MAX_X = 100;
const int MAX_Y = 100;
int table[MAX_Y][MAX_X];
int accum_table[MAX_Y][MAX_X];

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

void cleartable(int tb[][MAX_X])
{
	memset(table, 0, sizeof(int)*MAX_Y*MAX_X);
}

void init()
{
	cleartable(table);
	cleartable(accum_table);
}

int calcAsterisk(int x, int y, int w, int h, int s, int t)
{
	int rec1_x = x + s - 1;
	int rec1_y = y + t - 1;

	int rec2_x = x - 1;
	int rec2_y = y + t - 1;

	int rec3_x = x + s - 1;
	int rec3_y = y - 1; 

	int rec4_x = x - 1;
	int rec4_y = y - 1;

	// check val
	int checkx[4] = {rec1_x, rec2_x, rec3_x, rec4_x, };
	int checky[4] = {rec1_y, rec2_y, rec3_y, rec4_y, };
	REP(i, 4){
		if(checkx[i] > w || checkx[i] < 0){
			return 0;
		}
		if(checky[i] > h || checky[i] < 0){
			return 0;
		}
	}

	int rec1 = table[rec1_y][rec1_x];
	int rec2 = table[rec2_y][rec2_x];
	int rec3 = table[rec3_y][rec3_x];
	int rec4 = table[rec4_y][rec4_x];

	int rtn = rec1 - rec2 -rec3 + rec4;

	return rtn;
}

int main()
{
	std::string str;
	init();

	while(true){
		int n = 0;
		readline(str);
		sscanf(str.c_str(), "%d", &n);
		if(n == 0){
			break;
		}
		
		int w = 0;
		int h = 0;
		readline(str);
		sscanf(str.c_str(), "%d %d", &w, &h);

		//create data
		REP(i, n){
			int x = 0;
			int y = 0;
			readline(str);
			sscanf(str.c_str(), "%d %d", &x, &y);
			table[y][x] = 1;

		}


		int s, t;
		s = t = 0;
		readline(str);
		sscanf(str.c_str(), "%d %d", &s, &t);
		REP1(y, h){
			REP1(x, w){
				table[y][x] += table[y][x-1];
			}
		}
		REP1(x, w){
			REP1(y, h){
				table[y][x] += table[y-1][x];
			}
		}

		int max = 0;
		REP1(y, h - t +1){
			REP1(x, w - s + 1){
				int tmp = calcAsterisk(x, y, w, h, s, t);
				max = std::max(max, tmp);
			}
		}

		cout<<max<<endl;
		cleartable(table);

	}


	end();

	return 0;

}

