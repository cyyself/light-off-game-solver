#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
using std::swap;
const int MAXW = 15;
const int MAXH = 15;
int w;
int h;
int n;
int ma[MAXH*MAXW][MAXH*MAXW+1];
int pos[MAXH][MAXW];
void prepare() {
	for (int i=0;i<h;i++)
		for (int j=0;j<w;j++) pos[i][j] = i * w + j;
}
inline int getpos(int x,int y) {//This function only exist for making the code highlight more colorful
	return pos[x][y];
}
int gauss() {
	int ways = 0;
	for (int i=0;i<n;i++) {
		int k = i;
		for (int j=i+1;j<n;j++) if (abs(ma[j][i]) > abs(ma[k][i])) k = j;
		int now = ma[k][i];
		if (now == 0) ways ++;
		if (k != i) for (int j=i;j<=n;j++) swap(ma[i][j],ma[k][j]);
		for (int k=0;k<n;k++) if (k != i && ma[k][i]) {
			for (int j=i;j<=n;j++) ma[k][j] = ma[k][j] ^ ma[i][j];
		}
	}
	return ways;
}
int main() {
	printf("Input height and width splited by space:\n");
	scanf("%d%d",&h,&w);
	n = h * w;
	prepare();
	memset(ma,0,sizeof(ma));
	for (int i=0;i<h;i++)
		for (int j=0;j<w;j++) {
			int curpos = getpos(i,j);
			ma[curpos][curpos] = 1;//d(0,0)
			if (i < h-1) ma[getpos(i+1,j)][curpos] = 1;//d(+1,0)
			if (i > 0) ma[getpos(i-1,j)][curpos] = 1;//d(-1,0)
			if (j < w-1) ma[getpos(i,j+1)][curpos] = 1;//d(0,+1)
			if (j > 0) ma[getpos(i,j-1)][curpos] = 1;//d(0,-1)
		}
	for (int i=0;i<h;i++) 
		for (int j=0;j<w;j++) scanf("%d",&ma[getpos(i,j)][n]);
	printf("This problem has 2^%d ways to solve\n.",gauss());
	printf("-----ANSWER-----\n");
	for (int i=0;i<h;i++) {
		for (int j=0;j<w;j++) printf("%d ",ma[getpos(i,j)][n]);
		printf("\n");
	}
	return 0;
}
