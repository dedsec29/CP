#include <bits/stdc++.h>
using namespace std;

void countSort(vector<int>& p,vector<int>& c) {//sorting p based on equivalence class in linear time
	int n=p.size();
	vector<int> freq(n);
	for (auto i: c) freq[i]++;
	vector<int> p_new(n),pos(n);
	//pos i gives the starting of bucket (we can do running sum as well which gives i the end of bucket)
	pos[0]=0;
	for (int i=1;i<n;i++) 
		pos[i]=pos[i-1]+freq[i-1];
	for (auto x: p) {
		p_new[pos[c[x]]]=x;
		pos[c[x]]++;
	}
	p=p_new;
}

void make_suffixArray(vector<int>& p,string s) { //O(nlogn)
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
		for (int i=0;i<n;i++) 
			p[i]= (p[i]-(1<<k)+n)%n; //we will get p already sorted on basis of eq class of right part of string
		countSort(p,c); 
		// now making c for updated p
		vector<int> c_new(n);
		c_new[p[0]]=0;
		for (int i=1;i<n;i++) {
			pair<int,int> now= {c[p[i]], c[(p[i]+(1<<k))%n]};
			pair<int,int> prev= {c[p[i-1]], c[(p[i-1]+(1<<k))%n]};
			if (now==prev)
				c_new[p[i]]=c_new[p[i-1]];
			else
				c_new[p[i]]=c_new[p[i-1]]+1;
		}
		c=c_new;
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