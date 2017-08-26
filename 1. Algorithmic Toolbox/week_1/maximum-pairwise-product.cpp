#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
	int n;
	cin >> n;
	ll ar[n];
	for (int i = 0; i < n; i++) cin >> ar[i];

	sort(ar, ar + n);
	ll l1 = ar[n - 1], l2 = ar[n - 2], s1 = ar[0], s2 = ar[1];

	ll ans = l1 * l2 > s1 * s2 ? l1 * l2 : s1 * s2;
	cout << ans << endl;

	return 0;
}