#include<iostream>
#include<cstdio>
using namespace std;

int n, num[100086];

struct Range {
	int start, end;
	Range() {}
	Range(int s, int e) {
		start = s;
		end = e;
	}
};

template <typename T>
void quick_sort(T arr[], const int len) {
	if (len <= 0) return;

	int p = 0;
	Range r[len];
	r[p++] = Range(1, len);

	while (p) {
		Range cur = r[--p];

		if (cur.start >= cur.end) continue;

		T left, right, mid;
		left = cur.start;
		right = cur.end - 1;
		mid = arr[cur.end];

		while (left < right) {
			while (arr[left] < mid && left < right) left++;
			while (arr[right] >= mid && left < right) right--;
			swap(arr[left], arr[right]);
		}
		if (arr[left] >= arr[cur.end])
			swap(arr[left], arr[cur.end]);
		else
			left++;

		r[p++] = Range(cur.start, left - 1);
		r[p++] = Range(left + 1, cur.end);
	}
}

int main() {
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
		scanf("%d", &num[i]);

	quick_sort(num, n);

	for (int i = 1; i <= n; i++)
		printf("%d ", num[i]);

	return 0;
}

