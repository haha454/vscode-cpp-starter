#include <bits/stdc++.h>

using namespace std;

char char_at(string &s, int d)
{
	if (d >= s.length())
		return 0;
	return s[d];
}

void qr_sort(vector<string>::iterator lo, vector<string>::iterator ro, int d)
{
	if (lo >= ro)
		return;
	auto lt = lo;
	auto rt = ro;
	char pivot = char_at(*lt, d);
	auto i = next(lt);

	while (i < rt)
	{
		char cur = char_at(*i, d);
		if (cur < pivot)
		{
			swap(*lt, *i);
			lt = next(lt);
			i = next(i);
		}
		else if (cur > pivot)
		{
			rt = prev(rt);
			swap(*i, *rt);
		}
		else
		{
			i++;
			lt++;
		}
	}

	qr_sort(lo, lt - 1, d);
	if (pivot > 0)
		qr_sort(lt, rt, d + 1);
	qr_sort(rt, ro, d);
}

int main()
{
	vector<string> strs{"ahah", "haha", "ahha", "ahh"};
	qr_sort(strs.begin(), strs.end(), 0);
	for (auto const &s : strs)
		cout << s << endl;
	return 0;
}
