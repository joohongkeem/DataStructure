#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <string.h>			// memset
#include <vector>
using namespace std;
//
// [★핵심아이디어★]
// box배열이 1,2,3,4,5,6 이라하면
// pSum배열은 1,3,2,2,3,1 이다.
// 이때 인덱스 a, b에 대해 pSum[a]==pSum[b] 라면
// a+1번상자부터 b번상자까지의 더한 것은 K로 나누어 떨어진단 소리다.
//
// 즉, 각 값이 나오는 횟수를 저장해두고. 
// 그 횟수가 n일때 nC2를 하여 모두 더해주면 된다.
//
// [★주의사항★]
// 첫째 상자도 Count하기 위해, 0번째 인덱스(box[0])부터 계산해준다.


int T,N,K;

int ansOne(const vector<int> &pSum, int k){

	const int MOD = 20091101;

	int ret = 0;
	vector <long long int> count(k,0);
	
	for(unsigned int i=0; i<pSum.size(); i++) count[pSum[i]]++;

	for(int i=0; i<k; i++){
		if(count[i] >= 2){
			ret = (ret + (count[i] * (count[i] -1) ) / 2) % MOD;
		}
	}
	count.clear();
	return ret;
}

int ansTwo(const vector<int> &pSum, int k){
	// ret[i] => 첫번째 상자부터 i번째 상자까지 고려했을 때 살 수 있는 최대 횟수
	vector<int> ret(pSum.size(), 0);
	// prev[s] => psum[ x ] 의 값이 s였던 마지막 위치 x
	vector<int> previous(k, -1);

	for(unsigned int i=0; i<pSum.size(); i++){
		// i번째 상자를 고려하지 않는 경우
		if(i>0) ret[i] = ret[i-1];
		else ret[i] = 0;

		// pSum[i]를 전에도 본 적이 있으면, prev[pSum[i]] + 1 부터 여기까지 쭉 사본다.
		int loc = previous[pSum[i]];
		if(loc != -1) ret[i] = max(ret[i], ret[loc]+1);	// i번째 상자 사지 않는경우 vs 사는경우

		// prev[]에 현재 위치를 기록한다.
		previous[pSum[i]] = i;
	}

	int ans = ret.back();
	ret.clear();
	previous.clear();
	return ans; // 벡터의 마지막 원소를 리턴한다.
}
int main(){
	scanf("%d",&T);

	while(T--){
		scanf("%d %d",&N, &K);
		vector<int> arr(1,0);			// 가장먼저 인덱스 0을 사용할 벡터에 0값 대입
		for(int i=0; i<N; i++){
			int tmp;
			scanf("%d",&tmp);
			arr.push_back(tmp);
		}

		vector <int> pSum(arr.size());
		pSum[0] = 0;
		for(unsigned int i=1; i<arr.size(); i++){
			pSum[i] = pSum[i-1] + arr[i];
			pSum[i] %= K;
		}

		cout << ansOne(pSum,K) << " ";
		cout << ansTwo(pSum,K) << endl;

		arr.clear();
		pSum.clear();
	}

	return 0;
}
