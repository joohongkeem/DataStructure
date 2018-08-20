#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <string.h>			// memset
using namespace std;



// ★주의사항★
// INF 값을 0x7FFFFFFF으로 두면 정상적으로 동작하지 않아서, 987654321로 뒀다!!
//

int C,N,K,M,L;
int preClasses[12];
int semester[10];
int graph[10][1<<12];				// [1][13] = x이라면, 1학기에 000000001101이므로, {0, 2, 3} 과목을 수강한 상태! , 남은 학기는 x

inline int bitCount(int a)			// 켜진 비트 수를 반환한다.
{
	if(a==0) return 0; 
		 
	else return a%2 + bitCount(a/2);

}

int min(int a, int b)
{
	if(a>b) return b;
	else return a;
}

int graduate(int now, int taken);

int main()
{
	scanf("%d", &C);
	while(C--)
	{
		memset(preClasses,0,12*sizeof(int));
		memset(semester,0,10*sizeof(int));
		memset(graph, -1, sizeof(graph));
		scanf("%d %d %d %d", &N, &K, &M, &L);
		
		for(int i=0;i<N;i++)
		{
			int tmp;
			scanf("%d",&tmp);
			for(int t=0; t<tmp; t++)
			{
				int pre;
				scanf("%d", &pre);
				preClasses[i] |= (1<<pre);
			}
		}
		for(int i=0; i<M; i++)
		{
			int tmp;
			scanf("%d",&tmp);
			for(int t=0; t<tmp; t++)
			{
				int sem;
				scanf("%d", &sem);
				semester[i] |= (1<<sem);
			}
		}

		int ANS = graduate(0,0);
		if(ANS==987654321) cout << "IMPOSSIBLE" << endl;
		else cout << ANS << endl;



	}


	return 0;
}

int graduate(int now, int taken)			// 현재 semester학기이고, 수강한 과목이 taken일때, 앞으로 다녀야할 최소 학기의 수는?
{
	if(bitCount(taken) >= K) return 0;			// K개 이상의 과목을 모두 들은 경우
	if(now == M) return 987654321;			// M학기가 모두 지난 경우
	
	// 메모이제이션
	int& ret = graph[now][taken];		// 
	if(ret != -1) return ret;
	

	ret = 987654321;

	// 이번학기에 들을 수 있는 과목 중 아직 듣지 않은 과목 찾기
	int canTake = (semester[now] & ~taken);

	// 선수과목을 듣지 않은 과목을 거른다.
	for(int i=0; i<N; i++)
		if( (canTake & (1 << i )) && (taken & preClasses[i]) != preClasses[i]) canTake &= ~(1<<i);
	
	// 이 집합의 모든 부분 집합을 순회한다.
	for(int take=canTake; take>0; take=((take-1)&canTake))
	{
		// 한학기에 L 과목까지 들을 수 있다.
		if(bitCount(take) > L) continue;
		ret = min(ret, graduate(now+1, taken|take) +1 );	// 최소 학기 수 비교
	}

	// 이번학기에 아무것도 듣지 않을 경우
	ret = min(ret, graduate(now+1, taken));
	return ret;
}