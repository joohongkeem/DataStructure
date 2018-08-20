#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <string.h>			// memset
#include <vector>
using namespace std;

// Ex) 합이 0에 가장 가까운 구간 찾기
//
// - 그냥하면 시간 복잡도가 O(N^2)가 된다.
//	  But, 우리는 psum[j]-psum[i-1] 를 이용하여 부분합을 쉽게 구할 수 있고,
//	  구간의 합이 0에 가깝다는 것은 psum[j]-psum[i-1]의 차이가 가장 적다는 것이다.
//	  즉, psum배열을 정렬한 후에, 인접한 원소의 차가 가장 적은것을 출력하면 된다.
//	  병합정렬은 O(NlogN)에 가능하고, 인접한 원소의 차를 비교하는 것은 O(N)에 가능하므로 시간복잡도 O(NlogN)이 된다.
//

int temp[21];
void mergeSort(int *arr, int left, int right);

int main()
{
	int arr[10] = {-14, 7, 2, 3, -5, 4, -6, 8, 9, 11};
	int arrsize = sizeof(arr)/sizeof(int);

	for(int i=0; i<arrsize; i++) printf("%d ",arr[i]);
	puts("");	


	// 부분합을 계산한다.
	int psum[10] = {0};
	psum[0] = arr[0];
	for(int i=1; i<arrsize; i++) psum[i] = psum[i-1] + arr[i];
	for(int i=0; i<arrsize; i++) printf("%d ",psum[i]);
	puts("");

	// 부분합을 정렬하여 나타낼 배열을 나타낸다.
	int temparr[10];
	for(int i=0; i<arrsize; i++) temparr[i] = psum[i];

	// 정렬이 정상적으로 되었는지 확인한다.
	mergeSort(temparr,0,9);
	for(int i=0; i<arrsize; i++) printf("%d ",temparr[i]);
	puts("");

	int min = 987654321;
	int minIdx=0;
	for(int i=0; i<arrsize-1; i++)
	{
		if(temparr[i+1]-temparr[i] < min){
			min = temparr[i+1]-temparr[i];
			minIdx=i;
		}
	}
	int value1 = temparr[minIdx], value2 = temparr[minIdx+1];
	int start, end;
	for(int i=0; i<arrsize; i++)
	{
		if(psum[i] == value1) {start = i; value1=987654321;}
		if(psum[i] == value2) end = i;
	}
	if(start > end)
	{
		int tmp = start;
		start = end;
		end = tmp;
	}

	cout << start+1 << "부터 " << end << "까지의 합이 0에 제일 가깝습니다. \n"<< endl;

		

	return 0;
}

void mergeSort(int *arr, int left, int right)
{
	// 탈출조건
	if(left>=right) return;

	// 분할
	int mid = (left+right)/2;
	mergeSort(arr,left,mid);
	mergeSort(arr,mid+1,right);

	// 병합
	int length = right-left+1;
	int offset=0, offset1=left, offset2=mid+1;

	while( (offset1<=mid) || (offset2<=right) )
	{
		if(offset1>mid){
			temp[offset++] = arr[offset2++];
			continue;
		}
		if(offset2>right){
			temp[offset++] = arr[offset1++];
			continue;
		}
		if(arr[offset1] > arr[offset2]){
			temp[offset++] = arr[offset2++];
			continue;
		}
		else{
			temp[offset++] = arr[offset1++];
			continue;
		}
	}
	for(int i=0; i<length; i++)
	{
		arr[left+i] = temp[i];
	}

}