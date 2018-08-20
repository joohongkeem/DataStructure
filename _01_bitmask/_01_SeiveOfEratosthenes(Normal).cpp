#include <iostream>
#include <stdio.h>
#include <intrin.h>
#include <math.h>
#include <stdlib.h>

using namespace std;

// #1. 에라토스테네스의 체 (일반적인Ver)
// - n 이하의 모든 소수를 찾는 과정
//   가장 먼저, 2부터 n까지의 숫자를 쭉 적고, 지워지지 않은 수들을 순회하며, 이 수의 배수를 지우는 과정을 반복한다.
//

int main()
{
	int N;
	cout << "N의 값을 입력하세요 : ";
	cin >> N;

	bool *isPrime = new bool[N+1];			// C++ 의 bool자료형과, new 할당법을 이용
	char *Prime = (char *) malloc(N+1);		// C 의 malloc함수를 이용
														// 둘 다 쓰레기값이 들어있다!! ★★
														// new bool[N](); 를 하면 모두 0으로 초기화
														// (char *) calloc(N,1);를 하면 모두 0으로 초기화!!

	cout << _msize(isPrime) << endl;			// 그냥 sizeof()로 하면 4출력 Why? bool형 포인터이므로
	cout << _msize(Prime) << endl;			// 그냥 sizeof()로 하면 4출력 Why? char형 포인터이므로
														// >> _misze()를 사용해줘야 값이 정상적으로 출력된다. ★★★★★

	memset(isPrime, 1, N+1);							// 쓰레기값이 들어있으므로 일단 모두 1로 초기화
	memset(Prime, 1, N+1);								// 쓰레기값이 들어있으므로 일단 모두 1로 초기화
	for(int i=0; i<=N; i++) printf("%d ", isPrime[i]);
	puts("");
	for(int i=0; i<=N; i++) printf("%d ", Prime[i]);
	puts("");													// 정상적으로 초기화됐는지 확인함.


	isPrime[0] = isPrime[1] = false;
	Prime[0] = Prime[1] = 0;							// 0과 1을 항상 예외처리 해준다.

	int maxRange = int(sqrt((double)N));				// 소수판별은 sqrt(N) 까지만 검색하면 된다.
	
	for(int i = 2 ; i<= maxRange ; i++)
	{
		if( isPrime[i] == true )
			for(int j = i*i; j<=N; j+=i)					// i보다 작은수에대해서는 체크 완료이므로 i*i부터 시작
				isPrime[j] = false;
	}
	
	for(int i = 2 ; i<= maxRange ; i++)
	{
		if( Prime[i] == 1 )
			for(int j = i*i; j<=N; j+=i)					// i보다 작은수에대해서는 체크 완료이므로 i*i부터 시작
				Prime[j] = 0;
	}

	for(int i=0; i<=N; i++) if(isPrime[i]) cout << i << " " ;
	cout << endl;
	for(int i=0; i<=N; i++) if(Prime[i]) cout << i << " " ;
	cout << endl;

	delete [] isPrime ;
	free(Prime);

	return 0;
}