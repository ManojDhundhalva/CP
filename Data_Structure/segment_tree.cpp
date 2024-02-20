#include <bits/stdc++.h>
#define ll long long int
using namespace std;

void build(ll ind, ll low, ll high, vector<ll> &a, vector<ll> &seg)
{
	if (low == high)
	{
		seg[ind] = a[low];
		return;
	}

	ll mid = low + ((high - low) / 2);
	build(2 * ind + 1, low, mid, a, seg);
	build(2 * ind + 2, mid + 1, high, a, seg);
	seg[ind] = max(seg[2 * ind + 1], seg[2 * ind + 2]);
}

ll query(ll ind, ll low, ll high, ll l, ll r, vector<ll> &seg)
{
	if (low >= l && high <= r)
	{
		return seg[ind];
	}
	if (high < l || low > r) { return INT_MIN; }

	ll mid = low + ((high - low) / 2);
	ll left = query(2 * ind + 1, low, mid, l, r, seg);
	ll right = query(2 * ind + 2, mid + 1, high, l, r, seg);
	return max(left, right);
}

void code()
{
	// Question : Find max element in the range [L, R]

	ll n;
	cin >> n;

	vector<ll> a(n), seg(4 * n);
	for (ll i = 0; i < n; ++i)
	{
		cin >> a[i];
	}
	build(0, 0, n - 1, a, seg);

	ll q;
	cin >> q;

	while (q--)
	{
		ll l, r;
		cin >> l >> r;

		l--;
		r--;

		cout << query(0, 0, n - 1, l, r, seg) << '\n';
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif

	ll t;
	cin >> t;

	while (t--)
	{
		code();
	}
	return 0;
}
