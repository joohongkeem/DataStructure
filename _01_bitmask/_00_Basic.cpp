#include <iostream>
#include <stdio.h>
#include <intrin.h>
using namespace std;

/*
	[장점]
		- 더 빠른 수행 시간
		- 더 간결한 코드
		- 더 작은 메모리 사용량
		- 연관 배열을 배열로 대체 가능
		>> 특히 집합을 표현할 때 유용함

	[주의사항]
		- 비트 연산자의 연산자 우선순위는 비교 연산자(==, !=) 보다 낮다.
		  즉, int c = ( 6 & 4 == 4); 라고 하면, 4 == 4가 먼저 실행되고 6 & 1 이 실행된다.
		>> 비트마스크 사용하는 식에는 가능한 괄호를 자세하게 추가하자. (int c = ( ( 6 & 4 ) == 4); )

		- 64비트 정수를 비트마스로 사용할때의 오버플로를 주의하자.
		  예를 들어, unsigned int a & 1을 하게되면, 1은 32bit 상수로 취급되기 때문에 정상적으로 동작하지 않는다.
		>> unsigned int a & 1ull 을 사용해주자.

		- 32비트 모두 사용하고 싶다면, 앞의 1비트가 부호를 나타내지 않도록 unsigned 형으로 선언해주자.

*/

// 비트마스크를 사용한 집합 구현의 예제
//
int main()
{
	
	// 20개를 표현하기 위해 20비트를 사용할 것이므로 int로 선언해준다. (0부터 19까지의 index 사용)
	// 만약, 32개의 비트를 모두 사용하려면 unsigned int로 선언하자!!
	//
	int toppings = 0;
	
	int full_toppings = (1<<20) - 1;		// (1<<20)이 1뒤에 20개의 0이 있는 것이므로, 1을 빼주면 20개의 비트가 모두 켜진 '꽉 찬 집합'
	int none_toppings = 0;					// 모든 비트가 꺼져있으므로, 0비트

	// [원소의 추가]
	//
	toppings |= (1<<0);						// 0번 비트를 켜준다.
	toppings |= (1<<1);						// 1번 비트를 켜준다.
	toppings |= (1<<19);
	toppings |= (1<<10);

	// [원소의 포함 여부 확인]
	//
	for(int p=0; p<20; p++)
		if( toppings & ( 1<<p ) ) cout << p << " is in Toppings" << endl;
	cout << endl;
	//
	// [★주의사항★]
	// 반환값이 0 또는 1<<p 이므로, if( (toppings & ( 1<<p )) == 1)로 하면 정상적으로 동작하지 않는다!!!!


	// [원소의 삭제]
	//
	toppings &= ~(1<<1);
	toppings &= ~(1<<10);
	toppings &= ~(1<<5);		// 집합에 포함되지 않은 비트를 삭제해도 오작동하지 않는다.
	for(int p=0; p<20; p++)
		if( toppings & ( 1<<p ) ) cout << p << " is in Toppings" << endl;
	cout << endl;

	// [원소의 토글]
	// - 켜져있는 건 끄고, 꺼져있는건 켠다.
	//
	for(int p=0; p<20; p++) toppings ^= (1<<p);
	for(int p=0; p<20; p++)
		if( toppings & ( 1<<p ) ) cout << p << " is in Toppings" << endl;
	cout << endl;

	// [집합의 연산]
	// - 합집합, 교집합, 차집합, toggled집합(둘중 하나에만 포함된 집합) 을 아주 쉽게 계산할 수 있다.
	//
	int union_set = (toppings | none_toppings);				// 괄호를 꼭 씌우는 습관을 들이자.
	int intersection_set = (toppings & none_toppings);
	int difference_set = (toppings & (~none_toppings));	// - 를 하면 오작동할 수 있으므로, & ~를 활용해준다.
	int toggled_set = (toppings ^ none_toppings);

	// [집합의 크기 구하기]
	// - 집합에 포함된 원소의 수를 구하려면 재귀 함수를 구현해야 하지만,
	//   각 컴파일러 혹은 언어에 내장된 함수를 사용하면 손쉽게 구할 수 있다.
	//
	// (직접 구현)
	// int bitCount(int x)
	// { if(x==0) return 0; 
	//	 else return x%2 + bitCount(x/2);}
	//
	// (내장함수)
	// gcc/g++ -> __builtin_popcount(toppings)
	// Visual C++ -> __popcnt(toppings)			( intrin.h를 include 해야한다.)
	// JAVA -> Integer.bitCount(toppings);
	//
	printf("%d\n\n",__popcnt(toppings));		// 18이 정상적으로 출력된다.

	// [ 최소 원소 찾기 ]
	// - 집합에 포함된 가장 작은 원소를 찾는 과정
	// >> 켜져있는 최하위 비트의 번호를 반환한다.(즉, 끝에 붙어있는 0의 개수를 참조하며 동작)
	//
	// (내장함수)
	// gcc/g++ -> __builtin_ctz(toppings);					(입력이 0일땐 동작하지 않는다)
	// Visual C++ -> _BitScanForward(&index, toppings);
	// JAVA -> Integer.numberOfTrailingZeros(toppings);
	//
	int b = 110;
	for(int p=0; p<20; p++)
		if( b & ( 1<<p ) ) cout << p << " is in a Set" << endl;
	cout << endl;
	
	unsigned long int min_ele;
	_BitScanForward(&min_ele,b);	// 이걸 바로 출력해도 1이 나온다.
	printf("%ld\n", min_ele);			// 1이 출력된다. (1 2 3 5 6 번 비트가 켜져있음)

	// 만약, 최소비트의 번호가 아닌, 그 값을 얻고 싶다면 아래와 같은 방법을 사용한다.
	// (즉, 3번 비트가 아닌, 2^3을 구하고 싶을때)
	// 
	int firstTopping = (b & -b);
	cout << endl << firstTopping << endl << endl;		// 2가 출력된다.
	//
	// 위의 계산은, 컴퓨터가 음수를 표현하기위해 '2의 보수' 를 사용한다는 점을 이용한다.
	// 2의 보수를 취하면, 뒤에 붙어있는 모든 0이 1로 바뀌고, 1을 더하기 때문에 딱 필요한 비트만 1이 된다. 
	// (그 위의 비트들은 toggled했기 때문에 &연산해도 0)
	// ★★★ 펜윅 트리에서 유용하게 사용

	// [최소 원소 지우기]
	// - 최소 원소를 얻은 뒤, 그 원소를 지우는 과정보다 훨씬 간결하다.
	//
	int b_next = ( b & (b-1) );	// 최소원소 1번비트가 삭제됐다.
										// Why?
										// b-1은 켜져있는 최하위비트를 끄고, 그 아래 비트를 모두 켠 것이다.
										// 즉, &연산을 하면 최하위 비트만 꺼지고, 나머지는 그대로 출력된다.
	//
	// 위의 방법은 어떤 정수가 2의 거듭제곱인지 확인할 때 자주 사용한다.
	// 2의 거듭제곱은 켜진 비트가 하나뿐이므로, 최하위 비트를 지웠을때 0이 출력된다.
	for(int p=0; p<20; p++)
		if( b_next & ( 1<<p ) ) cout << p << " is in a Set" << endl;		// 1번비트가 정상적으로 지워짐을 확인
	cout << endl;


	// [모든 부분집합 순회하기]
	// 예를 들어 pizza가 {페퍼로니, 소시지, 양파} 라면
	// {페퍼로니}, {페퍼로니 소시지}, {페퍼로니 소시지 양파} {페퍼로니 양파} {소시지} {소시지 양파} {양파} 를 열거하는 것
	//
	int pizza = 7;
	for(int subset = pizza; subset; subset = ((subset-1) & pizza))
	{
		cout << subset << endl; 
	}	// 7,6,5,4,3,2,1 이 모두 출력된다.
	//
	// (동작 과정)
	// (subset-1) 은 켜져있던 최하위 비트가 꺼지고, 그 밑의 비트들은 전부 켜진다.
	// 이 것을 pizza와 교집합 하면, 그 중 pizza에 속하지 않는 비트들은 모두 꺼지게 된다.
	// 즉, pizza의 모든 부분집합을 방문하게 된다.
	// 예를 들어, pizza = 11001이 있으면
	// subset  (subset-1)   (subset-1)&pizza  
	// 11001    11000           11000
	// 11000    10111           10001
	// 10001    10000           10000
	// 10000    01111           01001
	// 01001    01000           01000
	// 01000    00111           00001
	// 00001    00000           00000 (종료)
	//
	// ★★ subset=0인 시점에서 좀료하므로, 공집합은 방문하지 않는다.
	
	return 0;
}