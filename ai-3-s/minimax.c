#include <stdio.h>
#include <stdbool.h>

int minimax(int depth, int node, int values[]);
int alphabeta(int depth, int node, bool you, int values[], int alpha, int beta);
int max(int a, int b) { return (a > b) ? a : b; }
int min(int a, int b) { return (a < b) ? a : b; }

#define MAX 1000
#define MIN -1000
#define DEPTH 3
#define LEAF 8

// アルファベータ法によって自分にとって最も良い葉を選択する
// alpha is the best value that the "maximizer" currently can guarantee at that level or above.
// beta  is the best value that the "minimizer" currently can guarantee at that level or above.
int alphabeta(int depth, int node, bool you, int values[], int alpha, int beta)
{
    // 葉に達していれば終了
    if (depth == DEPTH) return values[node];
 
    // 自分の指し手のとき、つまりmaxを選択したいとき
    if (you) {
        int best = MIN;
        // 左右の子について再帰
        for (int i=0; i<2; i++) {
            int val = alphabeta(depth+1, node*2+i, false, values, alpha, beta);
            best = max(best, val);
            alpha = max(alpha, best);
            if (beta <= alpha) break; // alpha-beta 刈り
        }
        return best;
    }
    else {
        int best = MAX;
        // 左右の子について再帰
        for (int i=0; i<2; i++) {
            int val = alphabeta(depth+1, node*2+i, true, values, alpha, beta);
            best = min(best, val);
            beta = min(beta, best);
            if (beta <= alpha) break; // alpha-beta 刈り
        }
        return best;
    }

}

// ミニマックス法とインタフェースを揃えるためのラッパー関数
int minimax(int depth, int node, int values[]) {
    return alphabeta(depth, node, true, values, MIN, MAX);
    // (int depth, int node, bool you, int values[], int alpha, int beta)
}

int main(void)
{
    int values[LEAF] = {3, 5, 6, 9, 1, 2, 0, -1}; // これらが葉の評価値
    // ここでの探索木は、バイナリツリーとしている。
    printf("the optimal values is : %d\n", minimax(0, 0, values));
    return 0;
}
// 注意として、葉は終了した時の評価値を保持しているが、それが最大のものが戦略的に最も良いとは限らない。
// これは、ゲームでは、相手にとって悪い手を選択することを考慮に入れつつ、自分にとって良い手を選択する必要があるためである。

// output:
// the optimal values is : 5
