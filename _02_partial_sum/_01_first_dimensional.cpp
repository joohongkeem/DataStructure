#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <string.h>			// memset
#include <vector>
using namespace std;

// [부분합]
// N개의 배열에서 a번째부터 b번째까지의 평균을 계산할때, 유용한 방법
// psum배열에 각 배열까지의 합을 모두 더해둔다.
// Ex) psum[0] = arr[0];
//		psum[1] = psum[0]+arr[1];
//		psum[2] = psum[1]+arr[2];
//				.....
// 이 때, a부터 b까지의 부분합은 psum[b] - psum[a-1] 이다.
//
// 위의 방식을 이용하면, 분산 역시 쉽게 구할 수 있다. (제곱의 합을 미리 입력받아두면 더 빠르게 계산 가능 ★★★★)

vector<int> partialSum (const vector<int>&a)
{
	vector<int>ret(a.size());
	ret[0] = a[0];
	for(unsigned int i=1; i<a.size(); i++)
	{
		ret[i] = ret[i-1] + a[i];
	}
	return ret;
}

int rangeSum(const vector<int>& psum, int a, int b)
{
	if(a==0) return psum[b];
	else return psum[b] - psum[a-1];
}

int main()
{
	int N;
	cout << "배열의 크기를 입력하세요 : " ;
	cin >> N;

	vector<int> vArr;
	for(int i=0; i<N; i++) 
	{
		int tmp;
		printf("vArr[%d] 값 입력 : ", i);
		scanf("%d",&tmp);
		vArr.push_back(tmp);
	}

	cout << "a부터 b까지의 부분합을 계산합니다.\na와 b를 입력하세요 : ";
	int a, b;
	cin >> a >> b;

	cout << rangeSum(partialSum(vArr),a,b) << endl;

	vArr.clear();

	return 0;
}