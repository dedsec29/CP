#include <bits/stdc++.h>
using namespace std;
#define ll long long

void make_suffixArray(vector<int>& p,string s) { //O(n(logn)^2)
	int n=s.size();
	vector<int> c(n); //equivalence class array
	
	//for k=0th iteration: (in curly because then we can reuse the variable names)
	{
		vector<pair<char,int>> a(n); //for making current p array
		for (int i=0;i<n;i++) a[i]={s[i],i};
		sort(a.begin(),a.end());
		for (int i=0;i<n;i++) p[i]=a[i].second;
		c[p[0]]=0; //making equivalence for current p
		for (int i=1;i<n;i++) {
			if (a[i].first==a[i-1].first)
				c[p[i]]=c[p[i-1]];
			else
				c[p[i]]=c[p[i-1]]+1;
		}
	}

	int k=0; //current phase, now making transition to next phase
	// we make transitions till 2^k < n
	while ((1<<k)<n) {
		vector<pair<pair<int,int>,int>> a(n); //(eq class of left, eq class of right), index
		for (int i=0;i<n;i++) 
			a[i]={{c[i],c[(i+(1<<k))%n]}, i}; //we use class equivalence to compare in O(1)
		sort(a.begin(),a.end());
		for (int i=0;i<n;i++) p[i]=a[i].second; //updated suffix array. now make equivalence class for this
		c[p[0]]=0;
		for (int i=1;i<n;i++) {
			if (a[i].first==a[i-1].first)
				c[p[i]]=c[p[i-1]];
			else
				c[p[i]]=c[p[i-1]]+1;
		}
		k++;
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	string s; cin>>s;
	s+='$';
	int n=s.size();
	vector<int> p(n); //p is the suffix array
	make_suffixArray(p,s);
	for (int i=0;i<n;i++) cout<<p[i]<<" ";
	return 0;
}