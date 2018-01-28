#include <stdio.h>
#include <stdbool.h>
#include <math.h>

int minimax(int depth, int node, int values[]);
int alphabeta(int depth, int node, bool you, int values[], int alpha, int beta);
int max(int a, int b) { return (a > b) ? a : b; }
int min(int a, int b) { return (a < b) ? a : b; }

#define MAX 1000
#define MIN -1000
#define DEPTH 3
#define LEAF 8

// アルファベータ法によって自分にとって最も良い葉を選択する
int alphabeta(int depth, int node, bool you, int values[], int alpha, int beta)
{
	// 葉に達していれば終了
    if (depth == DEPTH) return values[node];
 
    if (you) {
        int best = MIN;
        // Recur for left and right children
        for (int i=0; i<2; i++) {
            int val = alphabeta(depth+1, node*2+i, false, values, alpha, beta);
            best = max(best, val);
            alpha = max(alpha, best);
            if (beta <= alpha) break; // Alpha Beta Pruning
        }
        return best;
    }
    else {
        int best = MAX;
        // Recur for left and right children
        for (int i=0; i<2; i++) {
            int val = alphabeta(depth+1, node*2+i, true, values, alpha, beta);
            best = min(best, val);
            beta = min(beta, best);
            if (beta <= alpha) break; // Alpha Beta Pruning
        }
        return best;
    }

}

// ミニマックス法とインタフェースを揃えるためのラッパー関数
int minimax(int depth, int node, int values[]) {
	return alphabeta(depth, node, true, values, MIN, MAX);
	// int depth, int node, bool you, int values[], int alpha, int beta
}

int main(void)
{
	int values[LEAF] = {3, 5, 6, 9, 1, 2, 0, -1}; // これらが葉の評価値
	// ここでの探索木は、バイナリツリーとしている。
	printf("the optimal values is : %d\n", minimax(0, 0, values));
	return 0;
}