
#include <fstream>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <limits.h>


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

typedef struct _node{
	int val;
	struct _node* next;
	struct _node* prev;
}node;

node* ptop = NULL;
node* pbottom = NULL;


void deleteNodeList()
{
	node* n = pbottom;
	while(n != NULL){
		node* next = n->next;
		free(n);
		n = next;
	}
}

void createNodeList(int n)
{

	node* prevn = NULL;
	REP1(i, n){
		node* pnode = (node*)malloc(sizeof(node));
		pnode->val = i;
		pnode->next = NULL;
		if(prevn != NULL){
			pnode->prev = prevn;
			prevn->next = pnode;
		}

		if(i == 1){
			pbottom = pnode;
		}

		if(i == n){
			ptop = pnode;
		}

		prevn = pnode;
	}
	ptop->next = NULL;
	pbottom->prev = NULL;
}

void init()
{
}

void shuffle(int p, int c)
{
	node* s1top = ptop;
	node* s1bottom = NULL;

	node* tmp = ptop;
	REP(i, p-2){
		tmp = tmp->prev;
	}
	s1bottom = tmp;

	node* s2top = s1bottom->prev;
	tmp = s2top;
	REP(i, c-1){
		tmp = tmp->prev;
	}
	node* s2bottom = tmp;

	node* s3top = NULL;
	if(s2bottom != NULL){
		 s3top = s2bottom->prev;
	}

	if(s3top != NULL){
		//switch s1<->s2
		s3top->next = s1bottom;
	
		s2bottom->prev = s1top;
		s2top->next = NULL;
		ptop = s2top;
		ptop->next = NULL;

		s1bottom->prev = s3top;
		s1top->next = s2bottom;
	}else{
		//switch s1<->s2
		s2bottom->prev = s1top;
		s2top->next = NULL;
		ptop = s2top;
		s1top->next = s2bottom;
		pbottom = s1bottom;
		pbottom->prev = NULL;
	}
}

int main()
{
	std::string str;
	init();

	int n, r;
	while(true){
		readline(str);
		sscanf(str.c_str(), "%d %d", &n, &r);
		if(n == 0 && r == 0){
			break;
		}
		createNodeList(n);

		while(r-- > 0){
			int p, c;
			readline(str);
			sscanf(str.c_str(), "%d %d", &p, &c);
			if(p-1 != 0 && p+c <= n+1){
				shuffle(p, c);
			}
			
		}
		cout<<ptop->val<<endl;
		deleteNodeList();

	}


#ifdef FILE
	ifs.close();
	ofs.close();
#endif

	return 0;

}

