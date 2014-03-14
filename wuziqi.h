#ifndef WUZIQI_H
#define WUZIQI_H

#include <iostream>
#include <vector>
#include <list>
#include <cmath>
#include <algorithm>
#include <fstream>

using namespace std;

class POINT
{
public:
	int x;
	int y;
	POINT(const int X=-1, const int Y=-1)   {x = X; y = Y;};
};


class wuziqi
{
private:
    int N; 
    vector<vector<int> > Data; //  1 for black, 2 for white
    POINT ps_Now; 
    int Total;
    void Player(POINT & ps);
    void SetScore(const int i, const int j, const int Who, vector<vector<int> > & State); 
    int p_Score(int num, int bp[]);
    bool first; 
    bool ChangePos(const POINT & srcPos, POINT & desPos,  const int & beginPos, const int & endPos);  
public: 
    wuziqi(const int n = 15); 
    ~wuziqi(void);
    void Init(void);
    void GetData(vector<vector<int> > & data); 
    void Judge(int & player); 
    bool Fall(const POINT & ps, const int & who, const int & beginPos, const int & endPos); 
   
    bool UnFall(const POINT & ps, const int & who, const int & beginPos, const int & endPos);
 
    void Clear(void); 
    void Run(POINT & ps, const int & Which, const int & Who); 
		  
};
#endif
