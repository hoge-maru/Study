#include <fstream>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <limits.h>

#include <map>

using namespace std;
#define FILE

int N;
int tzolcycle =  13*20;
int haabcycle =  20*18+5;

char* HAABMON[] = {"pop", "no", "zip", "zotz", "tzec", "xul", "yoxkin", "mol", "chen", "yax", "zac", "ceh", "mac", "kankin", "muan", "pax", "koyab", "cumhu", "uayet"};
char* TZOLKINDAY[] = {"imix", "ik", "akbal", "kan", "chicchan", "cimi", "manik", "lamat", "muluk", "ok", "chuen", "eb", "ben", "ix", "mem", "cib", "caban", "eznab", "canac", "ahau"};

map<string, int> HAABMHash;
map<int, string> TZOLHash;

#define REP(i, x) for(int i = 0; i < x; i++)

int uayat = 18;

void init()
{
	REP(i, 19){
		HAABMHash.insert( map<string, int>::value_type(HAABMON[i], i));
	}

	REP(i, 20){
		TZOLHash.insert(map<int, string>::value_type(i+1, TZOLKINDAY[i]));
	}

}


int main()
{
	std::string str;
	int i = 0;
	init();
	int val;


#ifdef FILE
	std::ifstream ifs("input.txt");
	std::ofstream ofs("out.txt");
	ifs>>N;
	cout<<N<<endl;
	while(getline(ifs, str))
#else
	cin>>N;
	cout<<N<<endl;
	while(getline(std::cin, str))
#endif
	{	
		int haabDay, haabMon, haabYear;
		char haabMonStrC[8];

		if(str.length() == 0){
			continue;
		}
		sscanf(str.c_str(), "%d\. %s %d", &haabDay, haabMonStrC, &haabYear);
		string haabMonStr = haabMonStrC;

		int hb = HAABMHash[haabMonStr];
		int date = date = haabDay + hb*20 + haabYear*365;

		int tZolYear = date/tzolcycle;
		int tzday = (date % tzolcycle)%13 + 1;
		int tzindex = date%20+1;
		string tzdaystr = TZOLHash[tzindex];

		cout<<tzday<<" "<<tzdaystr<<" "<<tZolYear<<endl;
		
	}



#ifdef FILE
	ifs.close();
	ofs.close();
#endif

	return 0;

}

