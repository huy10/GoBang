#include "wuziqi.h"

wuziqi::wuziqi(const int n)
{
    N = n;
    Init();
}

wuziqi::~wuziqi(void)
{
}

void wuziqi::Init(void)
{
    vector<int> temp(N, 0);
    for (int i = 0; i < N; i++)
    {
        Data.push_back(temp);
    }
    first = true; 
}

void wuziqi::GetData(vector<vector<int> > & data)
{
	data.clear();
	data.resize(N);
	for (int i = 0; i < N; i++)
	{
		data[i].resize(N);
		for (int j = 0; j < N; j++)
		{
			data[i][j] = Data[i][j];
		}
	}
}

void wuziqi::Judge(int & player)
{

    if (Total == N*N) //  nobody wins
    {
        player = 3;
        return;
    }
    int state = 0;
    for (int x = 0; x < N; x++)
    {
        for (int y = 0; y < N; y++)
        {
            if (Data[x][y] == 0) 
            {
                continue;
            }
            for (int i = 0; i < 4; i++)
            {
                int k, j;
                switch (i)
                {
             
                case 0: //horizontal
                    k = x+1;//  left -> right
                    while (k < N && Data[k][y] == Data[x][y])
                    {
                        state++;
                        k++;
                    }
                    if (state >= 4)
                    {
                        player = Data[x][y];
                        return;
                    }
                    else
                    {
                        state = 0;
                    }
                    break;
                case 1: // vertical
                    j = y + 1; // up -> down
                    while (j < N && Data[x][j] == Data[x][y])
                    {
                        state++;
                        j++;
                    }
                    if (state >= 4)
                    {
                        player = Data[x][y];
                        return;
                    }
                    else
                    {
                        state = 0;
                    }
                    break;
                case 2: //  45 
                    k = x + 1;
                    j = y + 1;
                    while (k < N && j < N && Data[k][j] == Data[x][y])
                    {
                        state++;
                        k++;
                        j++;
                    }
                    if (state >= 4)
                    {
                        player = Data[x][y];
                        return;
                    }
                    else
                    {
                        state = 0;
                    }
                    break;
                case 3: // -45
                    k = x - 1;
                    j = y + 1;
                    while (k >= 0 && j < N && Data[k][j] == Data[x][y])
                    {
                        state++;
                        k--;
                        j++;
                    }
                    if (state >= 4)
                    {
                        player = Data[x][y];
                        return;
                    }
                    else
                    {
                        state = 0;
                    }
                    break;
                default:
                    break;
                }

            }
        }
    }
    player = 0;
    return;
}

bool wuziqi::ChangePos(const POINT & srcPos, POINT & desPos,
	     const int & beginPos, const int & endPos) 
{
    if (srcPos.x < beginPos || srcPos.y < beginPos || srcPos.x > endPos || srcPos.y > endPos)
    {
        return false;
    }
    desPos.x = -1;
    desPos.y = -1;

   
    for (int i = 0; i < N; i++)
    {
        if (srcPos.x > beginPos + i*20 - 10 && srcPos.x <= beginPos + i*20 + 10)
        {
            desPos.x = i;
            break;
        }
    }
    for (int i = 0; i < N; i++)
    {
        if (srcPos.y > beginPos + i*20 - 10 && srcPos.y <= beginPos + i*20 + 10)
        {
            desPos.y = i;
            break;
        }
    }
    return true;
}

bool wuziqi::Fall(const POINT & ps, const int & who,
		  const int & beginPos, const int & endPos)
{
    POINT tempPos;
    if (ChangePos(ps, tempPos, beginPos, endPos) == false)
    {
	    return false;
    }
    if (tempPos.x < 0 || tempPos.y < 0)
    {
	    return false;
    }
    if (Data[tempPos.x][tempPos.y] == 0)
    {
        if (who == 1 || who == 2)
        {
            Data[tempPos.x][tempPos.y] = who;
            if (who == 2)
            {
                ps_Now.x = tempPos.x;
                ps_Now.y = tempPos.y;
            }
            Total++; 
            return true;
        }
        
    }
    
}

bool wuziqi::UnFall(const POINT & ps, const int & who,  const int & beginPos, const int & endPos)
{
    POINT tempPos;
    if (ChangePos(ps, tempPos, beginPos, endPos) == false)
    {
	    return false;
    }
    if (tempPos.x < 0 || tempPos.y < 0)
    {
	    return false;
    }
    if (Data[tempPos.x][tempPos.y] == who)
    {
	Data[tempPos.x][tempPos.y] = 0;
	Total--;
	return true;
    }
    
}

void wuziqi::Clear(void)
{
    for (int x = 0; x < N; x++)
    {
        for (int y = 0; y < N; y++)
        {
            Data[x][y] = 0;
        }
    }
    Total = 0;
}

void wuziqi::Run(POINT & ps, const int & Which, const int & Who)
{

     if (Which == 2)
    {
	Player(ps);
	if (ps.x == -1 || ps.y == -1)
	{
		return;
	}
    }

    return;
}



void wuziqi::Player(POINT & ps)
{
    
    if (Total == 0)
    {
	ps.x = rand()%N;
	ps.y = rand()%N;
	return;
    }

    vector<vector<int> > HumanState, ComputerState;
    vector<int> temp(N, 0);
    for (int i = 0; i < N; i++)
    {
        HumanState.push_back(temp);
        ComputerState.push_back(temp);
    }
    POINT ps1, ps2;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (Data[i][j] == 0)
            {
                SetScore(i, j, 1, HumanState);
                SetScore(i, j, 2, ComputerState);
            }
        }
    }

    int maxP = 0, maxC = 0; 
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (HumanState[i][j] > maxP)
            {
                maxP = HumanState[i][j];
                ps1.x = i;
                ps1.y = j;
            }
            if (ComputerState[i][j] > maxC)
            {
                maxC = ComputerState[i][j];
                ps2.x = i;
                ps2.y = j;
            }
        }
    }
    if (maxP >= maxC)
    {
        ps.x = ps1.x;
        ps.y = ps1.y;
    }
    else
    {
        ps.x = ps2.x;
        ps.y = ps2.y;
    }
}


void wuziqi::SetScore(const int i, const int j, const int Who,
                    vector<vector<int> > & State)
{
    int Another; 
    if (Who == 1)
    {
        Another = 2;
    }
    else if (Who == 2)
    {
        Another = 1;
    }
    else
    {
        return;
    }
    int bp[2], k, num, max = 0, temp = 0;

    //horizontal
    // right
    bp[0] = 1; bp[1] = 1;
    num = 0;
    for (k = 1; k < N - i; k++)
    {
        if (Data[i+k][j] == Who)
        {
            num++;
            continue;
        }
        if (Data[i+k][j] == 0)
        {
            bp[1] = 0;
            break;
        }
        if (Data[i+k][j] == Another)
        {
            bp[1] = 1;
            break;
        }
    }
    //left
    for (k = 1; k <= i; k++)
    {
        if (Data[i-k][j] == Who)
        {
            num++;
            continue;
        }
        if (Data[i-k][j] == 0)
        {
            bp[0] = 0;
            break;
        }
        if (Data[i-k][j] == Another)
        {
            bp[0] = 1;
            break;
        }
    }
    temp = p_Score(num, bp);
    max += temp;

    //vertical
    bp[0] = 1; bp[1] = 1;
    num = 0;
    //down
    for (k = 1; k < N - j; k++)
    {
        if (Data[i][j+k] == Who)
        {
            num++;
            continue;
        }
        if (Data[i][j+k] == 0)
        {
            bp[1] = 0;
            break;
        }
        if (Data[i][j+k] == Another)
        {
            bp[1] = 1;
            break;
        }
    }
    //up
    for (k = 1; k <= j; k++)
    {
        if (Data[i][j-k] == Who)
        {
            num++;
            continue;
        }
        if (Data[i][j-k] == 0)
        {
            bp[0] = 0;
            break;
        }
        if (Data[i][j-k] == Another)
        {
            bp[0] = 1;
            break;
        }
    }
    temp = p_Score(num, bp);
    max += temp;

    //45 
    bp[0] = 1; bp[1] = 1;
    num = 0;

    //down
    for (k = 1; k < N-i && k < N-j; k++)
    {
        if (Data[i+k][j+k] == Who)
        {
            num++;
            continue;
        }
        if (Data[i+k][j+k] == 0)
        {
            bp[1] = 0;
            break;
        }
        if (Data[i+k][j+k] == Another)
        {
            bp[1] = 1;
            break;
        }
    }
    //up
    for (k = 1; k <= j && k <= i; k++)
    {
        if (Data[i-k][j-k] == Who)
        {
            num++;
            continue;
        }
        if (Data[i-k][j-k] == 0)
        {
            bp[0] = 0;
            break;
        }
        if (Data[i-k][j-k] == Another)
        {
            bp[0] = 1;
            break;
        }
    }
    temp = p_Score(num, bp);
    max += temp;

    //-45
    bp[0] = 1; bp[1] = 1;
    num = 0;
    //down
    for (k = 1; k < N-j && k <= i; k++)
    {
        if (Data[i-k][j+k] == Who)
        {
            num++;
            continue;
        }
        if (Data[i-k][j+k] == 0)
        {
            bp[1] = 0;
            break;
        }
        if (Data[i-k][j+k] == Another)
        {
            bp[1] = 1;
            break;
        }
    }
    //up
    for (k = 1; k <= j && k < N-i; k++)
    {
        if (Data[i+k][j-k] == Who)
        {
            num++;
            continue;
        }
        if (Data[i+k][j-k] == 0)
        {
            bp[0] = 0;
            break;
        }
        if (Data[i+k][j-k] == Another)
        {
            bp[0] = 1;
            break;
        }
    }
    temp = p_Score(num, bp);
    max += temp;

    if (max > State[i][j])
    {
        State[i][j] = max;
    }
}


int wuziqi::p_Score(int num, int bp[])
{
    int max = 0;
    if (num >= 4)
    {
        max += 10000; //成五
    }
    else if (num == 3)
    {
        if (bp[1] == 1 && bp[0] == 1) //不成五
        {
            max += 0;
        }
        else if (bp[1] == 0 && bp[0] == 0) //活四
        {
            max += 3000;
        }
        else
        {
            max += 900; //冲四
        }
    }
    else if (num == 2)
    {
        if (bp[0] == 0 && bp[1] == 0)
        {
            max += 460; //活三
        }
        else if (bp[0] == 1 && bp[1] == 1)
        {
            max += 0; //不成五
        }
        else
        {
            max += 30; //死三
        }
    }
    else if (num == 1)
    {
        if (bp[0] == 0 && bp[1] == 0)
        {
            max += 45;  //活二
        }
        else if (bp[0] == 1 && bp[1] == 1)
        {
            max += 0;
        }
        else
        {
            max += 5;
        }
    }
    else if (num == 0)
    {
        if (bp[0] == 0 && bp[1] == 0)
        {
            max += 3;
        }
        else if (bp[0] == 1 && bp[1] == 1)
        {
            max += 0;
        }
        else
        {
            max += 1;
        }
    }
    return max;
}


