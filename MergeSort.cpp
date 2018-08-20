#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdlib.h>		// for rand,srand
#include <time.h>			// for time seed
using namespace std;


// 병합 정렬 구현하기
// - 최악의 경우에도 O(NlogN)을 보장
//   (퀵소트는 최악의경우엔 O(N^2)지만, 대신 병합정렬은 추가적인 메모리 필요)
//

#define SIZE 30
int tmp[SIZE];

void mergeSort(int *arr, int left, int right);

int main()
{
	int arr[SIZE];
	srand(time(NULL));
	for(int i=0; i<SIZE; i++)	arr[i] = rand()%100 -50;		// 난수 생성

	for(int i=0; i<SIZE; i++) printf("%d ", arr[i]);				// 정렬 전) 배열 출력
	puts("");						
	
	mergeSort(arr,0,SIZE-1);

	for(int i=0; i<SIZE; i++) printf("%d ", arr[i]);			// 정렬 후) 배열 출력
	puts("");						
	
}

void mergeSort(int *arr, int left, int right)
{
	// 탈출조건
	if(left >= right) return;

	// 분할
	int mid = (left+right)/2;
	mergeSort(arr,left,mid);
	mergeSort(arr,mid+1,right);

	int length = right-left+1;
	int offset=0, offset1=left, offset2=mid+1;

	while( (offset1<=mid) || (offset2 <= right) )
	{
		if( offset2>right ){
			tmp[offset++] = arr[offset1++];
			continue;
		}
		if( offset1>mid ){
			tmp[offset++] = arr[offset2++];
			continue;
		}
		if( arr[offset1] > arr[offset2] ){
			tmp[offset++] = arr[offset2++];
			continue;
		}
		else{
			tmp[offset++] = arr[offset1++];
			continue;
		}
	}
	for(int i=0; i<length; i++)
	{
		arr[left+i] = tmp[i];
	}
	
}



