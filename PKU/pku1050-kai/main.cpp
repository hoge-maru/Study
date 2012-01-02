#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;
int N;
int MAP[101][101];
int SUM[102][102];
int SUM2[102][102];
#define REP(i,x)for(int i=0;i<(int)x;i++)

#define FILE

int H,W;
int calc(int x1,int x2,int y1,int y2){
	return SUM2[x2][y2]+SUM2[x1][y1]-SUM2[x1][y2]-SUM2[x2][y1];
}
int main() {
	

#ifdef FILE
	std::ifstream ifs("input.txt");
	std::ofstream ofs("out.txt");
	ifs>>N;H=W=N;;
#else
	cin>>N;H=W=N;
#endif

	int ans=-888888;
	REP(i,H){
		SUM[0][i]=0;
		REP(j,W){
#ifdef FILE
			ifs>>MAP[j][i];
#else
			cin>>N;H=W=N;
#endif
			SUM[j+1][i]=SUM[j][i]+MAP[j][i];
		}
	}
	REP(x,W+1){
		SUM2[x][0]=0;
		REP(y,H){
			SUM2[x][y+1]=SUM2[x][y]+SUM[x][y];
		}
	}
#ifndef ONLINE_JUDGE
	REP(y,H+1){
		REP(x,W+1){
			cout<<setw(4)<<SUM2[x][y];
		}
		cout<<endl;
	}
#endif
	REP(y1,H){
		for(int y2=y1+1;y2<=H;y2++){
			REP(x1,W){
				for(int x2=x1+1;x2<=W;x2++){
					int val = calc(x1,x2,y1,y2);
					ans=max(ans,val);
				}
			}
		}
	}
	cout<<ans<<endl;
	return 0;
}