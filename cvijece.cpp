#include<stdio.h>
#include<stdint.h>
#include<vector>
#include<queue>
#include<iostream>
#include <algorithm>

using namespace std;
typedef unsigned int uint;
using namespace std;
struct cvor{
	uint value;
	std::pair<uint, uint> tocka;
};
class komparator
{
public:
  bool operator() (const cvor &lhs, const cvor &rhs) const
  {
    return (lhs.value > rhs.value);
  }
};
bool isSafe(int x, int y,int N, int M){
    return x >= 0 && x < N && y >= 0 && y < M;
}
uint solve(const uint N, const uint M, uint16_t *const problem, std::vector<std::pair<uint, uint> > &solution) {
		uint *acc_cost = new uint[N*M];
		for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            acc_cost[j+i*M] = 4294967295;
        }
    	}
   	priority_queue<cvor, vector<cvor>, komparator> pq;
      std::pair<uint, uint> tocka_kraj;
   	tocka_kraj.first = N-1;
   	tocka_kraj.second = M-1;
   	*acc_cost =*(problem);
   	pq.push({*(problem), {0,0}});
   	while(!pq.empty()) {
   		cvor cvor = pq.top();
   		pq.pop();
   		int x = cvor.tocka.first;
   		int y = cvor.tocka.second;
   		if(isSafe(x,y+1,N,M) && acc_cost[x*M+y+1] == 4294967295) {
 
   			acc_cost[x*M+y+1] = acc_cost[x*M+y] + *(problem + (y+1)%M + x*(M));
				pq.push({acc_cost[x*M+y+1], {x,y+1}});									
		   }
			if(isSafe(x+1,y,N,M) && acc_cost[(x+1)*M+y] == 4294967295) {
         
   		acc_cost[(x+1)*M+y] = acc_cost[x*M+y] + *(problem + y%M + (x+1)*(M));
         
			pq.push({acc_cost[(x+1)*M+y], {x+1,y}});								
		   }
		
		}
   	solution.push_back(tocka_kraj);
		while(true) {
			if(isSafe(tocka_kraj.first,tocka_kraj.second-1,N,M) && isSafe(tocka_kraj.first-1,tocka_kraj.second,N,M)) {
				if(acc_cost[(tocka_kraj.first-1)*M+tocka_kraj.second] >= acc_cost[tocka_kraj.first*M+tocka_kraj.second-1]) {
					tocka_kraj.first = tocka_kraj.first;
					tocka_kraj.second = tocka_kraj.second - 1;
					solution.push_back(tocka_kraj);
				}
				else {
					tocka_kraj.first = tocka_kraj.first -1;
					tocka_kraj.second = tocka_kraj.second;
					solution.push_back(tocka_kraj);
				}
			}
			else if (isSafe(tocka_kraj.first-1,tocka_kraj.second,N,M)) {
				tocka_kraj.first = tocka_kraj.first -1;
				tocka_kraj.second = tocka_kraj.second;
				solution.push_back(tocka_kraj);
				}
			else if (isSafe(tocka_kraj.first,tocka_kraj.second-1,N,M)){
				tocka_kraj.first = tocka_kraj.first;
				tocka_kraj.second = tocka_kraj.second-1;
				solution.push_back(tocka_kraj);
			}	
			else {
				break;
			}
		
		}
	reverse(solution.begin(), solution.end());
   //cout<<acc_cost[N-1][M-1];
	uint cost = acc_cost[N*M-1];
   delete[] acc_cost;
   return cost;
	}
int main() { 

    //uint16_t polje[] = {1, 7, 9, 2, 8, 6, 6, 7, 1, 3, 2, 8};

       uint16_t polje[] = {100, 200, 1000, 0,
                        200, 100,  600, 0,
                        300, 1600, 100, 0};
    uint16_t *ptr;
    ptr = polje;
    std::vector<std::pair<unsigned int, unsigned int> > solution;

    uint16_t brCvijeca = solve(3, 4, ptr, solution);

    cout << "Kolicina cvijeca: " << brCvijeca;
    cout << "\n";

    for(int i=0; i<solution.size(); ++i){
        cout << "(" << solution[i].first << ", " << solution[i].second << ")" << endl;
    }
  
    return 0; 
}
