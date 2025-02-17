#include<cstdio>
#include<iostream>
using namespace std;

int n, num[1086];

template <typename T>
void merge_sort(T arr[], T l, T r) {
	if (r - l <= 0) return;

	int mid = (l + r) >> 1;

	int tmp[1086];

	merge_sort(arr, l, mid);
	merge_sort(arr, mid + 1, r);
	//printf("%d",n);

	int i = l, j = mid + 1, k = l;
	while (i <= mid && j <= r) {
		if (arr[i] <= arr[j])
			tmp[k++] = arr[i++];
		else if (arr[i] > arr[j])
			tmp[k++] = arr[j++];
	}

	while (i <= mid)
		tmp[k++] = arr[i++];
	while (j <= r)
		tmp[k++] = arr[j++];

	for (int a = l; a <= r; a++)
		arr[a] = tmp[a];

}

int main() {
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
		scanf("%d", &num[i]);

	merge_sort(num, 1, n);

	for (int i = 1; i <= n; i++)
		printf("%d ", num[i]);

	return 0;
}
