#include <fstream>
#include <string>
#include <iostream>
#include <stdlib.h>

using namespace std;
#define FILE

const int SAMPLEN = 16;
const int MAX = 256;
const int EUCMAX = 3*MAX*MAX;

int cache[MAX][MAX];

typedef struct _rbg{
	int R;
	int G;
	int B;
}t_rbg;

t_rbg samples[SAMPLEN];

void init()
{
	for(int i = 0; i < MAX; i++){
		for(int j = 0; j < MAX; j++){
			cache[i][j] = 0;
		}
	}
}

int cachePow(int left, int right)
{

	if(!cache[left][right]){
		double tmp = (double)left - (double)right;
		double ans = tmp*tmp;
		int rtn = (int)ans;
		cache[left][right] = rtn;
	}
	return cache[left][right];
}

int calcEuclideanD(t_rbg* input)
{
	int minD = EUCMAX;
	int rtnIndex = 0;

	for(int i =0; i < SAMPLEN; i++){

		int rd = 0;
		int gd = 0;
		int bd = 0;

		int left = input->R;
		int right = samples[i].R;

		rd = cachePow(samples[i].R, input->R);
		gd = cachePow(samples[i].G, input->G);
		bd = cachePow(samples[i].B, input->B);
		
		int tmpMAX = rd+gd+bd;
		if(tmpMAX < minD){
			minD = tmpMAX;
			rtnIndex = i;
		}
	}

	return rtnIndex;
}

int main()
{
	std::string str;
	int i = 0;
	t_rbg input;
	init();

#ifdef FILE
	std::ifstream ifs("input.txt");
	std::ofstream ofs("out.txt");
	while(getline(ifs, str))
#else
	while(getline(std::cin, str))
#endif
	{	
		int val1, val2, val3;
		sscanf(str.c_str(), "%d %d %d", &val1, &val2, &val3);
		input.R = val1;
		input.G = val2;
		input.B = val3;

		if(val1 > 255 || val2 > 255 || val3 > 255){
			continue;
		}
		if(val1 < -1 || val2 < -1 || val3 < -1){
			continue;
		}
		if(input.R == -1 && input.G == -1 && input.B == -1){
			break;
		}


		if(i < SAMPLEN){
			samples[i].R = input.R;
			samples[i].G = input.G;
			samples[i].B = input.B;
		}else{
			int index = calcEuclideanD(&input);
			char buf[64];
			sprintf(buf, "(%d,%d,%d) maps to (%d,%d,%d)", input.R, input.G, input.B, samples[index].R, samples[index].G, samples[index].B);
			cout<<buf<<endl;
		}

		
		i++;
	}

#ifdef FILE
	ifs.close();
	ofs.close();
#endif

	return 0;

}

