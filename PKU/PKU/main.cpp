#include <fstream>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <deque>

using namespace std;
//#define FILE

const int MAX = 26;
const int INPUTMAX = 13+1;

int list[MAX];
int reinitlist[MAX];
int cache[INPUTMAX] = {0};


enum status{
	INIT,
	VIRTUE,
	EVIL,
	DEAD,
};

void init(int k)
{
	for(int i=0; i < MAX; i++){

		if(i < k){
			list[i] = VIRTUE;
		}else if( i >= k && i < 2*k){
			list[i] = EVIL;
		}else{
			list[i] = INIT;
		}
	}


	memcpy(reinitlist, list, sizeof(list));
}

void reinit()
{
	memcpy(list, reinitlist, sizeof(list));
}

void reconfigure(){
	
	for(int i=0; i < MAX-1; i++){

		if(list[i] == DEAD){
			list[i] = list[i+1];
			list[i+1] = DEAD;
		}
	}
}

bool execution(int start, int k)
{
	int index = start;
	bool rtn = false;
	int evilkilled = 0;

	int k2 = 2*k;

	if(index > (k2-1)){
		index = index % k2;
	}

	while(true){

		if(evilkilled == k){
			rtn = true;
			break;
		}

		if(list[index] == EVIL){

			if(list[index] == EVIL){
				evilkilled++;
			}

			//list[index] = DEAD;
			//reconfigure();
			int size = k2 - evilkilled;
			
			index = index + (start);
			if(index > size){
				index = index % size;

			}

		}else if(list[index] == VIRTUE){
			rtn = false;
			break;
		}
		else{
			perror("this path is illegal.");
			exit(1);
		}
		
	}

	return rtn;
}

int main()
{
	std::string str;
	int k = 0;

#ifdef FILE
	std::ifstream ifs("input.txt");
	std::ofstream ofs("out.txt");
	while(getline(ifs, str))
#else
	while(cin>>k)
#endif FILE
	{
		int m = 0;
		//sscanf(str.c_str(), "%d", &k);

		if(cache[k]){
			cout<<cache[k]<<endl;
			continue;
		}

		if(k == 0)
			break;
		m = k;
		init(k);
		
		for(int i = 1; i < INT_MAX; i++){
			int ptn = (k+1)*i-1;
			bool result = false;

			for(int j=0; j < 2; j++){
				ptn += j;
				result = execution(ptn, k);

				if(result){
					cout<<ptn+1<<endl;
					cache[k] = ptn+1;
					break;
				}else{
					reinit();
					continue;
				}

			}
			if(result) break;


		}

	}

#ifdef FILE
	ifs.close();
#endif

	return 0;

}