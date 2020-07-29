#include <bits/stdc++.h>
using namespace std;
#define ll long long

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

void make_suffixArray(vector<int>& p,string& s,vector<int>& c) { //O(nlogn)
	int n=s.size();
	//vector<int> c(n); //equivalence class array

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

void make_lcpArray(vector<int>& p,vector<int>& c,vector<int>& lcp,string const& s) {
	int k=0,n=s.size();
	for (int i=0;i<n-1;i++) { //c is the inverse function of p (i.e. (p,i) ka (i,p))
		int pi=c[i]; //pos of ith suffix in pi
		if (pi==0) continue;
		int j=p[pi-1];
		//now we need to find lcp[i]=lcp(s[i..],s[j..])
		while (s[i+k]==s[j+k]) k++;
		lcp[pi]=k;
		k=max(k-1,0);
	}
}

int main() { //https://cp-algorithms.com/string/suffix-array.html
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	string s; cin>>s; s+='#';
	int boundary=s.size()-1; 
	string t; cin>>t; s+=t+'$';
	int n=s.size();
	vector<int> p(n),c(n); //p is the suffix array, c the eq class array
	make_suffixArray(p,s,c);
	vector<int> lcp(n); //lcp[i]=LCP(p[i],p[i-1])
	make_lcpArray(p,c,lcp,s);
	int mx=0,pos=-1;
	for (int i=0;i<n-1;i++) {
		if ((p[i]<boundary && p[i+1]>boundary) || (p[i+1]<boundary && p[i]>boundary)) { //making sure one belongs to s, the other to t
			if (mx<lcp[i+1]) {
				mx=lcp[i+1];
				pos=min(p[i+1],p[i]);
			}
		}
	}
	string ans=s.substr(pos,mx);
	cout<<ans<<"\n";
	return 0;
}
