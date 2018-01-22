#include <malloc.h>
#include <stdio.h>
#include <time.h>

#define NIL -1

enum { WHITE, GRAY, BLACK };

struct edge {
    int v;
    struct edge *next;
};

struct vertex {
    int d;
    int pi;
    int color;
    int f;
    struct edge *adj; //邻接表的形式
};

struct vertex v[256];   //原图
struct vertex v_t[256]; //转置后的图
int ordered_v[256];     // in order of decreasing u.f
int ordered_v_index;
int Vscc[256 * 2]; //用于保存强连通分量的结果
int Vscc_p;

int time_vi;

void dfs_visit(int i, int n) {
    struct edge *p;
    time_vi++;
    v[i].d = time_vi;
    v[i].color = GRAY;
    for (p = v[i].adj; p; p = p->next) {
        if (v[p->v].color == WHITE) {
            v[p->v].pi = i;
            dfs_visit(p->v, n);
        }
    }
    v[i].color = BLACK;
    time_vi++;
    v[i].f = time_vi;
    ordered_v[ordered_v_index] = i;
    ordered_v_index--;
}

void dfs(int n) {
    int i;
    for (i = 0; i < n; i++) {
        v[i].color = WHITE;
        v[i].pi = NIL;
    }
    time_vi = 0;
    ordered_v_index = n - 1;
    for (i = 0; i < n; i++) {
        if (v[i].color == WHITE) {
            dfs_visit(i, n);
        }
    }
}

void dfs_visit_t(int i, int n) { //对转置图的DFS
    struct edge *p;
    Vscc[Vscc_p++] = i; //保存结果
    time_vi++;
    v_t[i].d = time_vi;
    v_t[i].color = GRAY;
    for (p = v_t[i].adj; p; p = p->next) {
        if (v_t[p->v].color == WHITE) {
            v_t[p->v].pi = i;
            dfs_visit_t(p->v, n);
        }
    }
    v_t[i].color = BLACK;
    time_vi++;
    v_t[i].f = time_vi;
}

void dfs_t(int n) {
    int i;
    for (i = 0; i < n; i++) {
        v_t[i].color = WHITE;
        v_t[i].pi = NIL;
    }
    time_vi = 0;
    Vscc_p = 0;
    for (i = 0; i < n; i++) {
        if (v_t[ordered_v[i]].color == WHITE) {
            dfs_visit_t(ordered_v[i], n);
            Vscc[Vscc_p++] = -1; //分隔DFS森林中不同的树
        }
    }
}

void strongly_connected_components(int n) {
    struct edge *p, *q;
    int i;
    dfs(n);
    for (i = 0; i < n; i++) { //求转置图
        for (p = v[i].adj; p; p = p->next) {
            q = malloc(sizeof(struct edge));
            q->v = i;
            q->next = v_t[p->v].adj;
            v_t[p->v].adj = q;
        }
    }
    dfs_t(n);
}

int main() {
    int i, j, a, b, n = 4;
    FILE *fp;
    char filename[100];
    double diff;
    struct timespec start, stop;
    for (i = 0; i < 6; i++) {
        n <<= 1;
        for (j = 0; j < n; j++) { //初始化
            v[j].d = v_t[j].d = -1;
            v[j].pi = v_t[j].pi = -1;
            v[j].color = v_t[j].color = -1;
            v[j].f = v_t[j].f = -1;
            v[j].adj = v_t[j].adj = NULL;
        }
        sprintf(filename, "../Input/size%d/input.txt", i + 1);
        fp = fopen(filename, "r");
        while (fscanf(fp, "%d,%d", &a, &b) > 0) { //读入数据
            struct edge *p = malloc(sizeof(struct edge));
            p->v = b;
            p->next = v[a].adj;
            v[a].adj = p;
        }
        fclose(fp);
        clock_gettime(CLOCK_MONOTONIC, &start); //开始计时
        strongly_connected_components(n);
        clock_gettime(CLOCK_MONOTONIC, &stop); //结束计时
        diff = (stop.tv_sec - start.tv_sec) +
               (double)(stop.tv_nsec - start.tv_nsec) / 1000000000L;
        sprintf(filename, "../Output/size%d/time1.txt", i + 1);
        fp = fopen(filename, "w");
        fprintf(fp, "%.9fs\n", diff);
        fclose(fp);

        sprintf(filename, "../Output/size%d/output1.txt", i + 1);
        fp = fopen(filename, "w");
        fprintf(fp, "(");
        for (j = 0; j < Vscc_p - 1; j++) { //写入结果
            if (Vscc[j] < 0) {
                fprintf(fp, ")\n(");
            } else {
                fprintf(fp, "%d", Vscc[j]);
                if (Vscc[j + 1] >= 0) {
                    fprintf(fp, ",");
                }
            }
        }
        fprintf(fp, ")\n\n");
        fclose(fp);
    }
    return 0;
}