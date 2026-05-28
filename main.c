#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

#define n 9
#define sqn 3

int board[n][n];

bool validate_board() {
    for (int i = 0; i < n; i++) {
        int freq[n + 1] = { 0 };
        
        for (int j = 0; j < n; j++)
            freq[board[i][j]]++;
        
        for (int j = 1; j <= n; j++) {
            if (freq[j] > 1)
                return false;
        }
    }
    
    for (int i = 0; i < n; i++) {
        int freq[n + 1] = { 0 };
        
        for (int j = 0; j < n; j++)
            freq[board[j][i]]++;
        
        for (int j = 1; j <= n; j++) {
            if (freq[j] > 1)
                return false;
        }
    }
    
    for (int i = 0; i < sqn; i++) {
        for (int j = 0; j < sqn; j++) {
            int freq[n + 1] = { 0 };
            for (int bi = 0; bi < sqn; bi++) {
                for (int bj = 0; bj < sqn; bj++) {
                    int ci = i * sqn + bi, cj = j * sqn + bj;
                    freq[board[ci][cj]]++;
                }
            }
            
            for (int k = 1; k <= n; k++) {
                if (freq[k] > 1)
                    return false;
            }
        }
    }
    return true;
}

bool solve(int i, int j) {
    if (j == n) {
        i++;
        j = 0;
    }
    
    if (i == n)
        return validate_board();
    else if (board[i][j])
        return solve(i, j + 1);
    else if (!validate_board())
        return false;
    
    for (int val = 1; val <= n; val++) {
        board[i][j] = val;
        
        if (solve(i, j + 1))
            return true;
        
        board[i][j] = 0;
    }
    
    return false;
}

int main(void) {
    printf("Enter the sudoku board (0 for empty cell):\n");
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            assert(scanf("%d", &board[i][j]));
            assert((board[i][j] <= n) && (board[i][j] >= 0));
        }
    }
    
    if (!solve(0, 0)) {
        printf("The entered board is invalid\n");
        return 1;
    }
    
    printf("\nThe solution is:\n");
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%d ", board[i][j]);
        putchar('\n');
    }
    return 0;
}