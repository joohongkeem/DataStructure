#include <iostream>
#include <stdio.h>
#include <intrin.h>
#include <math.h>
#include <stdlib.h>

using namespace std;

// #1. 에라토스테네스의 체 (bitMASK)
// - n 이하의 모든 소수를 찾는 과정
//   가장 먼저, 2부터 n까지의 숫자를 쭉 적고, 지워지지 않은 수들을 순회하며, 이 수의 배수를 지우는 과정을 반복한다.
//
// ★[핵심]★
// - MAX_N 개의 원소를 MAX_N/8바이트만 써서 구현한다. (메모리절약!!)
// - k번 원소가 참인지를 알기 위해서는 k/8 번재 원소의 k%8 번째 비트가 켜져있는지 확인하면 된다.
// - 오른쪽으로 3비트 시프트 = 8로 나눈다.
// - 7과 AND 연산 = 8로 나눈 나머지를 구한다.
//

#define MAX_N 987654321
unsigned char Prime[(MAX_N)/8 + 1];
int N;

inline bool isPrime(int k)			//함수를 호출하는게 아니라 그대로 대입하기 위해 inline함수 사용
{
	return Prime[k>>3] & (1 << (k & 7) );
}

inline void setComposite(int k)
{
	Prime[k>>3] &= ~(1<<(k&7));
	//
	// 37이 소수가 아니라면
	// Prime[37>>3] 즉, 37/8=4인 Prime[4] 의 5번째 비트를 0으로 바꾼다.
	// 38이 소수가 아니라면 Prime[4]의 6번째 비트를 0으로!
	// 39가 소수가 아니라면 Prime[4]의 7번째 비트를 0으로!
	// 40이 소수가 아니라면 Prime[5]의 0번재 비트를 0으로!!!!
}
int main()
{
	cout << "N 입력 : " ;
	cin >> N;


	memset(Prime,255,sizeof(Prime));
	
	setComposite(0);
	setComposite(1);
	
	int maxRange = int(sqrt((double)N));
	for(int i = 2; i<= maxRange; ++i)
		if (isPrime(i))
			for(int j = i*i; j<=N; j+=i) setComposite(j);

	for(int i = 0; i<=N; i++)
		if (isPrime(i)) cout << i << "는 Prime " << endl;
	return 0;
}