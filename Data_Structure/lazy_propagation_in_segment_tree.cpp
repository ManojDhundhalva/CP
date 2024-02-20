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
	seg[ind] = seg[2 * ind + 1] + seg[2 * ind + 2];
}

void rangeUpdate(ll ind, ll low, ll high, ll l, ll r, vector<ll> &seg, vector<ll> &lazy, ll val)
{
	if (lazy[ind] != 0)
	{
		seg[ind] += (high - low + 1) * lazy[ind];
		if (low != high)
		{
			lazy[2 * ind + 1] += lazy[ind];
			lazy[2 * ind + 2] += lazy[ind];
		}
		lazy[ind] = 0;
	}

	if (r < low || l > high || low > high) { return; }

	if (low >= l && high <= r)
	{
		seg[ind] += (high - low + 1) * val;
		if (low != high)
		{
			lazy[2 * ind + 1] += val;
			lazy[2 * ind + 2] += val;
		}
		return;
	}

	ll mid = low + ((high - low) / 2);
	rangeUpdate(2 * ind + 1, low, mid, l, r, seg, lazy, val);
	rangeUpdate(2 * ind + 2, mid + 1, high, l, r, seg, lazy, val);
	seg[ind] = seg[2 * ind + 1] + seg[2 * ind + 2];
}

ll querySumLazy(ll ind, ll low, ll high, ll l, ll r, vector<ll> seg, vector<ll> lazy)
{
	if (lazy[ind] != 0)
	{
		seg[ind] += (high - low + 1) * lazy[ind];
		if (low != high)
		{
			lazy[2 * ind + 1] += lazy[ind];
			lazy[2 * ind + 2] += lazy[ind];
		}
		lazy[ind] = 0;
	}

	if (r < low || l > high || low > high) { return 0; }
	if (low >= l && high <= r)
	{
		return seg[ind];
	}
	ll mid = low + ((high - low) / 2);
	return (querySumLazy(2 * ind + 1, low, mid, l, r, seg, lazy) + querySumLazy(2 * ind + 2, mid + 1, high, l, r, seg, lazy));
}

void code()
{
/*

option 1 : [L, R] sum
option 2 : [l, R] addition by "val" 

*/

	ll n;
	cin >> n;

	vector<ll> a(n), seg(4 * n), lazy(4 * n, 0);
	for (ll i = 0; i < n; ++i)
	{
		cin >> a[i];
	}

	build(0, 0, n - 1, a, seg);

	ll q;
	cin >> q;

	while (q--)
	{
		ll option, l, r;
		cin >> option >> l >> r;

		l--;
		r--;

		if (option == 1)
		{

			cout << querySumLazy(0, 0, n - 1, l, r, seg, lazy) << '\n';
		}
		else
		{
			ll val;
			cin >> val;

			rangeUpdate(0, 0, n - 1, l, r, seg, lazy, 5);
		}
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