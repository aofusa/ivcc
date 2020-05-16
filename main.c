#include <stdio.h>
#include "ivcc.h"

// 現在着目しているトークン
extern Token *token;

// 入力プログラム
extern char *user_input;

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "引数の個数が正しくありません\n");
        return 1;
    }

    // トークナイズしてパースする
    user_input = argv[1];
    token = tokenize(user_input);
    Node *node = expr();

    // アセンブリの前半部分を出力
    printf(".intel_syntax noprefix\n");
    printf(".global main\n");
    printf("main:\n");

    // 抽象構文木を下りながらコード生成
    gen(node);

    // スタックトップに式全体の値が残っているはずなので
    // それを RAX にロードして関数からの返り値とする
    printf("        pop rax\n");
    printf("        ret\n");

    return 0;
}
