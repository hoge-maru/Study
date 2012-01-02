#include <fstream>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <limits.h>

#include <functional>
#include <algorithm>

using namespace std;
//#define FILE

const int MAX = 105;

int map[MAX][MAX];
int N = 0;
int mapsum[MAX][MAX];

int maxSubRec = INT_MIN;
int mxnum = INT_MIN;

int g_prevVal = INT_MIN;

typedef struct _pos{
	int leftupx;
	int leftupy;
	int w;
	int h;
}t_pos;

void init()
{
	for(int i = 0; i < MAX; i++){
		for(int j = 0; j < MAX; j++){
			map[i][j] = INT_MIN;
		}
	}

}

void resetPos(t_pos* pos)
{
	pos->h = INT_MIN;
	pos->w = INT_MIN;
	pos->leftupx = INT_MIN;
	pos->leftupy = INT_MIN;
}

int calcValEx(t_pos* pos)
{

	int val = mapsum[pos->leftupy + pos->h][pos->leftupx + pos->w];
	
	int xi = pos->leftupx + pos->w;
	int yi = pos->leftupy - 1;

	int delA = 0;
	int delB = 0;
	int addC = 0;

	if( !(xi < 0 || yi <0 || xi > N || yi > N) ){
		delA = mapsum[yi][xi];
	}

	xi = pos->leftupx - 1;
	yi = pos->leftupy + pos->h;

	if( !(xi < 0 || yi <0 || xi > N || yi > N) ){
		delB = mapsum[yi][xi];
	}
	xi = pos->leftupx - 1;
	yi = pos->leftupy - 1;
	
	if( !(xi < 0 || yi <0 || xi > N || yi > N) ){
		addC = mapsum[yi][xi];
	}

	int ans = val + addC - delA - delB;


	return ans;
}

int main()
{
	std::string str;
	int i = 0;
	init();
	int val;
	
	int xi = 0;
	int yi = 0;

	int zi = 0;

#ifdef FILE
	std::ifstream ifs("input.txt");
	std::ofstream ofs("out.txt");
	ifs>>N;
	while(ifs>>val)
#else
	cin>>N;
	while(cin>>val)
#endif
	{	
		map[yi][xi++] = val;
		if(xi > N-1 ){
			xi = 0;
			yi++;
		}
		if(val > mxnum){
			mxnum = val;
		}

	}

	for(yi =0; yi < N; yi++){
		int xsum = 0;
		for(xi =0; xi < N; xi++){
			xsum += map[yi][xi];
			mapsum[yi][xi] = xsum;
		}

	}

	for(xi =0; xi < N; xi++){
		int ysum = 0;
		for(yi =0; yi < N; yi++){
			ysum += mapsum[yi][xi];
			mapsum[yi][xi] = ysum;
		}

	}

	t_pos nowpos;
	resetPos(&nowpos);

	int wmax = 0;
	int hmax = 0;

	for(nowpos.leftupx = 0; nowpos.leftupx < N; nowpos.leftupx++){

		wmax = N - nowpos.leftupx;

		for(nowpos.leftupy = 0; nowpos.leftupy < N; nowpos.leftupy++){
			
			hmax = N-nowpos.leftupy;

			for(nowpos.w=0; nowpos.w < wmax; nowpos.w++){

				for(nowpos.h =0; nowpos.h < hmax; nowpos.h++){

					//cout<<"x:"<<nowpos.leftupx<<", y:"<<nowpos.leftupy<<", w:"<<nowpos.w<<", h:"<<nowpos.h<<endl;
					//cout<<ans<<endl;
					maxSubRec = std::max(calcValEx(&nowpos), maxSubRec);

				}
			}
		}
	}
	cout<<maxSubRec<<endl;


#ifdef FILE
	ifs.close();
	ofs.close();
#endif

	return 0;

}

