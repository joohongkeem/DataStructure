#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <string.h>			// memset
#include <vector>
using namespace std;

// [부분합]
// - 2차원에서도 이러한 부분합을 사용하여 구간합을 빠르게 계산할 수 있다.
//


vector<vector<int> > partialSum (const vector<vector<int> >&a)
{
	vector <vector<int> > ret(a.size() ,vector<int>( a[0].size()));

	ret[0][0] = a[0][0];

	for(unsigned int i=1; i<a.size(); i++)
	{
		ret[i][0] = ret[i-1][0] + a[i][0];
	}
	for(unsigned int i=1; i<a[0].size(); i++)
	{
		ret[0][i] += ret[0][i-1] + a[0][i];
	}
	for(unsigned int i=1; i<a.size(); i++)
	{
		for(unsigned int j=1; j<a[0].size(); j++)
		{
			ret[i][j] = ret[i-1][j] + ret[i][j-1] - ret[i-1][j-1]+ a[i][j];
		}
	}

	return ret;
}

int rangeSum(const vector<vector<int> >& psum, int y1, int x1, int y2, int x2)
{
	int ret = psum[y2][x2];

	if(y1>0) ret -= psum[y1-1][x2];
	if(x1>0) ret -= psum[y2][x1-1];
	if(y1>0 && x1>0) ret += psum[y1-1][x1-1];

	return ret;
}

int main()
{
	int N,M;
	cout << "배열의 크기를 입력하세요 (NxM): " ;
	cin >> N >> M;

	vector < vector<int> > vDarr;					// 쉬프트 연산자와 구분하기위해 반드시 듸어쓰기로 구분해주어야 한다.
	for(int i=0; i<N; i++)
	{
		vector<int> element(M,1);					// 모두 1로 초기화(1안쓰면 0으로 초기화)
		vDarr.push_back(element);
	}
	//vector<vector<int> > vDarr(N, vector<int>(M,0));		// 이렇게하면 한줄로 0으로 초기화까지 가능
	
	cout << vDarr.size() << endl;							// N값 출력
	cout << vDarr.size()*vDarr[0].size() << endl;			// 전체 배열 크기 출력

	for(unsigned int i=0; i<vDarr.size(); i++)
	{
		for(unsigned int j=0; j<vDarr[i].size(); j++)
		{
			cout << vDarr[i][j]<< " ";								// 모두 1 출력
		}
		cout<<endl;
	}
	for(unsigned int i=0; i<vDarr.size(); i++)
	{
		for(unsigned int j=0; j<vDarr[i].size(); j++)
		{
			vDarr[i][j] = i*vDarr[i].size()+j;							// 이미 크기만큼 할당했으므로, push_back이 아닌 직접 대입!!
		}
	}
	for(unsigned int i=0; i<vDarr.size(); i++)
	{
		for(unsigned int j=0; j<vDarr[i].size(); j++)
		{
			cout << vDarr[i][j]<< " ";								// 0부터 N*M-1까지 순서대로 출력
		}
		cout<<endl;
	}

	cout << "----------------------------------------------------------------\n";

	int x1,x2,y1,y2;
	cout << "좌상단 점 (y1,x1) 입력 : ";
	cin >> y1 >> x1;
	cout << "우하단 점 (y2,x2) 입력 : ";
	cin >> y2 >> x2;

	cout << rangeSum(partialSum(vDarr), y1,x1,y2,x2) << endl;

	return 0;
}