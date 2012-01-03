
#include <fstream>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <limits.h>

using namespace std;
//#define FILE

#ifdef FILE
std::ifstream ifs("input.txt");
std::ofstream ofs("out.txt");
#define readline(str) while(getline(ifs, str))
#else
#define readline(str) while(getline(cin, str))
#endif


#define REP(i, x) for(int i = 0; i < x; i++)
#define REP1(i, x) for(int i = 1; i <= x; i++)

const int MAX = 500;
int lcstable[MAX][MAX];

void init()
{
	REP(i, MAX){
		REP(j, MAX){
			lcstable[i][j] = 0;
		}
	}

}


int main()
{
	std::string str;
	init();

	readline(str)
	{
		char buf1[MAX];
		char buf2[MAX];
		memset(buf1, 0, sizeof(buf1));
		memset(buf2, 0, sizeof(buf2));

		sscanf(str.c_str(), "%s %s", buf1, buf2);

		int buf1len = strlen(buf1);
		int buf2len = strlen(buf2);

		if(buf1len == 0 || buf2len == 0){
			continue;
		}
		
		REP1(y, buf1len){
			char c = buf1[y-1];
			REP1(x, buf2len){

				if(c == buf2[x-1]){
					int val1 = lcstable[y-1][x-1]+1; 
					int val2 = lcstable[y-1][x];  
					int val3 = lcstable[y][x-1];
					lcstable[y][x] = std::max(std::max(val1, val2), val3);
				}else{
					int val1 = lcstable[y-1][x-1]; 
					int val2 = lcstable[y-1][x];  
					int val3 = lcstable[y][x-1];
					lcstable[y][x] = std::max(std::max(val1, val2), val3);
				}
			}
		}

		cout<<lcstable[buf1len][buf2len]<<endl;

	}



#ifdef FILE
	ifs.close();
	ofs.close();
#endif

	return 0;

}

