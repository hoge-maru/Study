#include <fstream>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <limits.h>

#include <functional>
#include <algorithm>

using namespace std;
#define FILE

const int MAX = 150;

int map[MAX][MAX];
int N = 0;
int tothemax[MAX*MAX] = {0};
int maxhash[MAX*MAX] = {0};

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

int calcVal(int leftupx, int leftupy, int w, int h)
{
	
	int yi = 0;

	int sum = 0;

	int k = (w+1)*(h+1);

	for(int xi = leftupx; xi < leftupx+w+1; xi++){
		for(int yi = leftupy; yi < leftupy+h+1; yi++){
			
			if(xi >= N || yi >= N){
				break;
			}


			int val = map[yi][xi];
			if(val == INT_MIN){
				perror("illegal path");
				exit(1);
			}
			sum += val;
			k--;

			//if(k*mxnum+sum < maxSubRec && k!=0){
			if(maxhash[k]+sum < maxSubRec && k!=0){
				break;
			}

		}
	}

	return sum;
}

int calcVal(t_pos* prev, t_pos* now)
{

	int rtn = INT_MIN;

	if(prev->h == INT_MIN){
		rtn = calcVal(now->leftupx, now->leftupy, now->w, now->h);
		g_prevVal = rtn;
		return rtn;
	}
	int diffh = now->h - prev->h;
	int diffw = now->w - prev->w;


	if(diffh == 1 && diffw == 0){
		int updated_yi = prev->leftupy + prev->h+1; 
		int nowval = calcVal(prev->leftupx, updated_yi, now->w, 0);
		rtn = g_prevVal+nowval;
	}else if(diffh == 0 && diffw == 1){
		int updated_xi = prev->leftupx + prev->w+1; 
		int nowval = calcVal(updated_xi, prev->leftupy,  0, now->h);
		rtn = g_prevVal+nowval;
	}else{
		rtn = calcVal(now->leftupx, now->leftupy, now->w, now->h);
	}

	g_prevVal = rtn;

	return rtn;
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
		tothemax[zi++] = val;

	}

	sort(tothemax, tothemax+zi, greater<int>());
	for(int l = 0; l < N*N; l++){
		int sum = 0;
		for(int m = 0; m < l+1; m++){
			sum += tothemax[m];
		}
		maxhash[l] = sum;
	}

	t_pos maxpos;

	t_pos prevpos;
	t_pos nowpos;
	resetPos(&prevpos);
	resetPos(&nowpos);

	for(xi = 0; xi < N; xi++){
		for(yi = 0; yi < N; yi++){

			for(int w =0; w < (N-xi); w++){
				for(int h =0; h < (N-yi); h++){
					//int tmp = calcVal(xi, yi, w, h);
					nowpos.h = h;
					nowpos.w = w;
					nowpos.leftupx = xi;
					nowpos.leftupy = yi;

					int tmp = calcVal(&prevpos, &nowpos);

					prevpos.h = h;
					prevpos.w = w;
					prevpos.leftupx = xi;
					prevpos.leftupy = yi;

					if(tmp > maxSubRec ){
						maxSubRec = tmp;
						maxpos.leftupx = xi;
						maxpos.leftupy = yi;
						maxpos.w = w;
						maxpos.h = h;

					}
				}
				resetPos(&prevpos);
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

