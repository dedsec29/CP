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

void make_suffixArray(vector<int>& p,string const& s,vector<int>& c) { //O(nlogn)
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

vector<int> kl,c;
int n; 

void precomputation(string const& s) {
	int n=s.size();
	int k=2, p=0; 
	kl[1]=0;
	while ( (k>>1) <=n) {
		int l= k>>1, r=min(k,n);
		for (int i=l;i<r;i++) 
			kl[i]=p;
		k=k<<1; p++;
	}
}

bool comp(pair<int,int>& x,pair<int,int>& y) {
	if (x.first==y.first)
		return (x.second-x.first+1)<(y.second-y.first+1);
	int l=min(x.second-x.first+1,y.second-y.first+1);
	int k=kl[l];
	pair<int,int> a= {c[x.first-1], c[(x.first-1+l-(1<<k))%n]};
	pair<int,int> b= {c[y.first-1], c[(y.first-1+l-(1<<k))%n]};
	return a<b;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	string s; cin>>s;
	s+='$';
	n=s.size();
	vector<int> p(n); //p is the suffix array, c the eq class array
	c.assign(n,0);
	make_suffixArray(p,s,c);
	vector<int> lcp(n);
	make_lcpArray(p,c,lcp,s);	//lcp[i]=LCP(p[i],p[i-1])
	kl.assign(n,0); //greatest k such that 2^k <= l, where 1<=l<=n
	precomputation(s);
	int m; cin>>m;
	vector<pair<int,int>> J;
	while (m--) {
		int l,r; cin>>l>>r;
		J.push_back({l,r});
	}
	sort(J.begin(),J.end(),comp);
	for (auto x: J) cout<<x.first<<" "<<x.second<<"\n";
	return 0;
}