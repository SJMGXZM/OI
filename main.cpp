#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
int n, p[100500], s[100500];
double f[100500], A[100500], B[100500], Rate[100500];
struct Point {
   double x, y;
}q[100500], t[100500];
struct cash { 
   int k; 
   double a, b, r; 
} h[100500];
int cur = -1; 
double x[100500], y[100500];  

int cmp(cash A, cash B) { 
    return -A.a/A.b > -B.a/B.b; 
}

void solve(int l, int r) {
	if(l == r) {  
	   q[l].x = (f[l]*Rate[l])/(A[l]*Rate[l]+B[l]);
	   q[l].y = q[l].x/Rate[l];
	   x[0] = q[l].x;
	   y[0] = q[l].y;
	   cur = 0;
	   return; 
	}
	int mid = l + (r-l)/2;
	int m1 = l-1, m2 = mid ;
    for(int i = l; i <= r; i++)
         if(h[p[i]].k <= mid) s[++m1] = p[i]; else s[++m2] = p[i];
    for(int i = l; i <= r; i++) p[i] = s[i];
    solve(l, mid); // 递归左边
	
	int j = 0;
	for(int i = mid+1; i <= r; i++) {
		f[h[p[i]].k] = max(f[h[p[i]].k-1], f[h[p[i]].k]);
	    double g = -h[p[i]].a/h[p[i]].b;
		while(g <= (y[j+1]-y[j])/(x[j+1]-x[j]) && j < cur) j++;
		f[h[p[i]].k] = max(f[h[p[i]].k], x[j]*h[p[i]].a + y[j]*h[p[i]].b);
    } // 更新左对右的影响 
    
	solve(mid+1, r); // 递归右边
	
	int top1 = l, top2 = mid + 1;
	for(int i = l; i <= r; i++) {
	   if(top1 > mid) {
	       t[i] = q[top2++];
           continue;
	   }
	   if(top2 > r) {
	       t[i] = q[top1++];
	       continue;
	   }
	   if(q[top1].x < q[top2].x) t[i] = q[top1++];
	   else t[i] = q[top2++];
	}
	for(int i = l; i <= r; i++) q[i] = t[i];
	
	cur = -1;
	for(int i = l; i <= r; i++) {
	   double g;
	   while(1) {
		 if(q[i].x == x[cur] && q[i].y >= y[cur] && cur >= 0){
		    cur--;
			continue;
		 }
		 if(cur < 0) break; 
	     g = (q[i].y-y[cur])/(q[i].x-x[cur]);
	     if(g >= (y[cur]-y[cur-1])/(x[cur]-x[cur-1]) && cur >= 0) cur--;
	     else break;
	   }
	   x[++cur] = q[i].x;
	   y[cur] = q[i].y;
    }
}
int main() {
	freopen("cash.in", "r", stdin);
	freopen("cash.out", "w", stdout);
    scanf("%d", &n);
    scanf("%lf", &f[0]);
    for(int i = 1; i < n; i++) f[i] = f[0];
    for(int i = 0; i < n; i++) {
	   scanf("%lf%lf%lf", &A[i], &B[i], &Rate[i]);
	   h[i].a = A[i]; 
	   h[i].b = B[i]; 
	   h[i].r = Rate[i]; 
	   h[i].k = i;
	}
    sort(h, h+n, cmp);
    for(int i = 0; i < n; i++) p[i] = i;
    solve(0, n-1);
    printf("%.3f", f[n-1]);
return 0; 
}

