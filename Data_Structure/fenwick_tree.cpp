#include <bits/stdc++.h>
#define ll long long int
using namespace std;

// update only "i"th element(1-based indexing)
void update(ll i, ll add, vector<ll> &fen)
{
	while (i < fen.size())
	{
		fen[i] += add;
		i += (i & (-i));
	}
}

// give sum till "i"(1-based indexing)
ll sum(ll i, vector<ll> &fen)
{
	ll s = 0;
	while (i > 0)
	{
		s += fen[i];
		i -= (i & (-i));
	}
	return s;
}

void code()
{
	/*
		fenwick tree always start with 1-based indexing
		option 1 : sum [L, R]
		option 2 : addition at "i"th index by val
	*/

	ll n;
	cin >> n;

	vector<ll> a(n), fen(n + 1, 0);
	for (ll i = 0; i < n; ++i)
	{
		cin >> a[i];
		update(i + 1, a[i], fen);
	}
	for (ll i = 0; i <= n; ++i)
	{
	    cout << fen[i] << " ";
	}
	cout << '\n';

	ll q;
	cin >> q;

	while(q--)
	{
		ll option;
		cin >> option;

		if(option == 1)
		{
			ll l, r;
			cin >> l >> r;

			cout << sum(r, fen) - sum(l - 1, fen) << '\n';
		}
		else
		{
			ll index, val;
			cin >> index >> val;

			update(index, val, fen);
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

	ll t = 1;
	cin >> t;

	while (t--)
	{
		code();
	}
	return 0;
}