#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int g[256][256]; //以邻接矩阵存储，方便查找

int main(){
	int i,j,k,n=4,nlogn,a,b;
	FILE *fp;
	char filename[100];
	srand(time(0));
	for(i=0;i<6;i++){
		n<<=1;
		nlogn=n*(i+3);
		for(j=0;j<n;j++){
			for(k=0;k<n;k++){
				g[j][k]=0; //初始化为0
			}
		}
		sprintf(filename,"size%d/input.txt",i+1);
		fp=fopen(filename,"w");
		for(j=0;j<nlogn;j++){
			do{
				a=rand()%n;
				b=rand()%n;
			}while(g[a][b]); //如果重复则换个位置生成
			g[a][b]=1; //已经生成边则标记为1
			fprintf(fp,"%d,%d\n",a,b);
		}
		fclose(fp);
	}
	return 0;
}
