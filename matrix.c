#include <stdio.h>

#define MAX 100

int Ans[MAX][MAX];

int fitsInt(long long value) {
    int converted = (int)value;
    return (long long)converted == value;
}
int AnsRows = 0, AnsCols = 0;
int AnsValid = 0;

void matrixscan(int r, int c, int x[r][c]) {
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            printf("Row %d, Column %d: ", i + 1, j + 1);
            if (scanf("%d", &x[i][j]) != 1) {
                printf("Invalid matrix element.\n");
                return;
            }
        }
    }
}

void matrixtranspose(int r, int c, int a[r][c], int result[c][r]) {
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++)
            result[j][i] = a[i][j];
}

void matrixprint(int r, int c, int x[r][c]) {
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++)
            printf("%d\t", x[i][j]);
        printf("\n");
    }
}

void saveAns(int r, int c, int x[r][c]) {
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++)
            Ans[i][j] = x[i][j];

    AnsRows = r;
    AnsCols = c;
    AnsValid = 1;
    printf("Result saved to Ans.\n");
}

int matrixinput(int r, int c, int x[r][c]) {
    int option;

    printf("1. Enter a new matrix\n");
    printf("2. Use Ans\n");
    printf("Choose input: ");

    if (scanf("%d", &option) != 1)
        return 0;

    if (option == 1) {
        matrixscan(r, c, x);
        return 1;
    }

    if (option == 2) {
        if (!AnsValid) {
            printf("Ans is empty. Calculate a result first.\n");
            return 0;
        }

        if (AnsRows != r || AnsCols != c) {
            printf("Ans is %dx%d, but %dx%d is required.\n",
                   AnsRows, AnsCols, r, c);
            return 0;
        }

        for (int i = 0; i < r; i++)
            for (int j = 0; j < c; j++)
                x[i][j] = Ans[i][j];

        printf("Using Ans:\n");
        matrixprint(r, c, x);
        return 1;
    }

    printf("Invalid input option.\n");
    return 0;
}

void matrixadd(int r, int c, int a[r][c],
               int b[r][c], int result[r][c]) {
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++)
            result[i][j] = a[i][j] + b[i][j];
}

void matrixsubtract(int r, int c, int a[r][c],
                    int b[r][c], int result[r][c]) {
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++)
            result[i][j] = a[i][j] - b[i][j];
}

void matrixmultiply(int r1, int c1, int c2,
                    int a[r1][c1], int b[c1][c2],
                    int result[r1][c2]) {
    for (int i = 0; i < r1; i++) {
        for (int j = 0; j < c2; j++) {
            result[i][j] = 0;
            for (int k = 0; k < c1; k++)
                result[i][j] += a[i][k] * b[k][j];
        }
    }
}

void matrixidentity(int n, int result[n][n]) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            result[i][j] = (i == j) ? 1 : 0;
}

void matrixpower(int n, int power, int a[n][n],
                 int result[n][n]) {
    int temp[n][n];
    matrixidentity(n, result);

    for (int p = 0; p < power; p++) {
        matrixmultiply(n, n, n, result, a, temp);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                result[i][j] = temp[i][j];
    }
}

void findminor(int n, int a[n][n], int row, int col,
               int minor[n - 1][n - 1]) {
    int r = 0;

    for (int i = 0; i < n; i++) {
        if (i == row)
            continue;

        int c = 0;
        for (int j = 0; j < n; j++) {
            if (j == col)
                continue;
            minor[r][c] = a[i][j];
            c++;
        }
        r++;
    }
}

long long determinant(int n, int a[n][n]);

long long minorvalue(int n, int a[n][n], int row, int col) {
    int minor[n - 1][n - 1];
    findminor(n, a, row, col, minor);
    return determinant(n - 1, minor);
}

long long cofactor(int n, int a[n][n], int row, int col) {
    long long value = minorvalue(n, a, row, col);
    if ((row + col) % 2 != 0)
        value = -value;
    return value;
}

long long determinant(int n, int a[n][n]) {
    if (n == 1)
        return a[0][0];

    if (n == 2)
        return (long long)a[0][0] * a[1][1]
             - (long long)a[0][1] * a[1][0];

    long long det = 0;
    for (int j = 0; j < n; j++)
        det += (long long)a[0][j] * cofactor(n, a, 0, j);
    return det;
}

int matrixadjugate(int n, int a[n][n], long long result[n][n]) {
    int canStore = 1;

    if (n == 1) {
        result[0][0] = 1;
        return 1;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            result[i][j] = cofactor(n, a, j, i);
            if (!fitsInt(result[i][j]))
                canStore = 0;
        }
    }

    return canStore;
}

int main(void) {
    int choice;

    do {
        printf("\n===== MATRIX CALCULATOR =====\n");
        printf("1. Matrix Addition\n");
        printf("2. Matrix Subtraction\n");
        printf("3. Matrix Multiplication\n");
        printf("4. Matrix Power\n");
        printf("5. Identity Matrix\n");
        printf("6. Minor Matrix and Minor Determinants\n");
        printf("7. Cofactor Matrix\n");
        printf("8. Determinant\n");
        printf("9. Display Ans\n");
        printf("10. Clear Ans\n");
        printf("11. Transpose Matrix\n");
        printf("12. Adjugate Matrix\n");
        printf("13. Inverse Matrix\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input.\n");
            return 1;
        }

        switch (choice) {
            case 1:
            case 2: {
                int r, c;
                printf("Enter rows and columns: ");

                if (scanf("%d %d", &r, &c) != 2 ||
                    r < 1 || c < 1 || r > MAX || c > MAX) {
                    printf("Invalid dimensions.\n");
                    break;
                }

                int a[r][c], b[r][c], result[r][c];

                printf("First matrix:\n");
                if (!matrixinput(r, c, a))
                    break;

                printf("Second matrix:\n");
                if (!matrixinput(r, c, b))
                    break;

                if (choice == 1) {
                    matrixadd(r, c, a, b, result);
                    printf("Sum:\n");
                } else {
                    matrixsubtract(r, c, a, b, result);
                    printf("Difference (A - B):\n");
                }

                matrixprint(r, c, result);
                saveAns(r, c, result);
                break;
            }

            case 3: {
                int r1, c1, r2, c2;

                printf("Enter rows and columns of first matrix: ");
                if (scanf("%d %d", &r1, &c1) != 2 ||
                    r1 < 1 || c1 < 1 || r1 > MAX || c1 > MAX) {
                    printf("Invalid dimensions.\n");
                    break;
                }

                printf("Enter rows and columns of second matrix: ");
                if (scanf("%d %d", &r2, &c2) != 2 ||
                    r2 < 1 || c2 < 1 || r2 > MAX || c2 > MAX) {
                    printf("Invalid dimensions.\n");
                    break;
                }

                if (c1 != r2) {
                    printf("Multiplication not possible.\n");
                    break;
                }

                int a[r1][c1], b[r2][c2], result[r1][c2];

                printf("First matrix:\n");
                if (!matrixinput(r1, c1, a))
                    break;

                printf("Second matrix:\n");
                if (!matrixinput(r2, c2, b))
                    break;

                matrixmultiply(r1, c1, c2, a, b, result);
                printf("Product:\n");
                matrixprint(r1, c2, result);
                saveAns(r1, c2, result);
                break;
            }

            case 4: {
                int n, power;
                printf("Enter size of square matrix: ");

                if (scanf("%d", &n) != 1 || n < 1 || n > MAX) {
                    printf("Invalid dimensions.\n");
                    break;
                }

                printf("Enter power (>= 0): ");
                if (scanf("%d", &power) != 1 || power < 0) {
                    printf("Invalid power.\n");
                    break;
                }

                int a[n][n], result[n][n];
                if (!matrixinput(n, n, a))
                    break;

                matrixpower(n, power, a, result);
                printf("A^%d:\n", power);
                matrixprint(n, n, result);
                saveAns(n, n, result);
                break;
            }

            case 5: {
                int n;
                printf("Enter size of identity matrix: ");

                if (scanf("%d", &n) != 1 || n < 1 || n > MAX) {
                    printf("Invalid dimensions.\n");
                    break;
                }

                int result[n][n];
                matrixidentity(n, result);
                printf("Identity matrix:\n");
                matrixprint(n, n, result);
                saveAns(n, n, result);
                break;
            }

            case 6:
            case 7:
            case 8: {
                int n;
                printf("Enter size of square matrix: ");

                if (scanf("%d", &n) != 1 || n < 1 || n > MAX) {
                    printf("Invalid dimensions.\n");
                    break;
                }

                int a[n][n];
                if (!matrixinput(n, n, a))
                    break;

                if (choice == 6) {
                    if (n == 1) {
                        printf("No smaller minor matrix exists for 1x1.\n");
                        break;
                    }

                    printf("Minor determinants:\n");
                    for (int i = 0; i < n; i++) {
                        for (int j = 0; j < n; j++)
                            printf("%lld\t", minorvalue(n, a, i, j));
                        printf("\n");
                    }

                    int minor[n - 1][n - 1];
                    int row, col;
                    printf("\nEnter element row and column to display its minor: ");

                    if (scanf("%d %d", &row, &col) != 2 ||
                        row < 1 || row > n || col < 1 || col > n) {
                        printf("Invalid position.\n");
                        break;
                    }

                    findminor(n, a, row - 1, col - 1, minor);
                    printf("Minor matrix of a[%d][%d]:\n", row, col);
                    matrixprint(n - 1, n - 1, minor);
                    saveAns(n - 1, n - 1, minor);
                } else if (choice == 7) {
                    if (n == 1) {
                        printf("Cofactor matrix for 1x1 is [1].\n");
                        int result[1][1] = {{1}};
                        saveAns(1, 1, result);
                        break;
                    }

                    long long result[n][n];
                    int canStore = 1;

                    printf("Cofactor matrix:\n");
                    for (int i = 0; i < n; i++) {
                        for (int j = 0; j < n; j++) {
                            result[i][j] = cofactor(n, a, i, j);
                            printf("%lld\t", result[i][j]);
                            if (!fitsInt(result[i][j]))
                                canStore = 0;
                        }
                        printf("\n");
                    }

                    if (canStore) {
                        int stored[n][n];
                        for (int i = 0; i < n; i++)
                            for (int j = 0; j < n; j++)
                                stored[i][j] = (int)result[i][j];
                        saveAns(n, n, stored);
                    } else {
                        printf("Cofactors exceed int range; result not saved to Ans.\n");
                    }
                } else {
                    printf("Determinant = %lld\n", determinant(n, a));
                }

                break;
            }

            case 9:
                if (!AnsValid) {
                    printf("Ans is empty.\n");
                } else {
                    printf("Ans (%dx%d):\n", AnsRows, AnsCols);
                    matrixprint(AnsRows, AnsCols, Ans);
                }
                break;

            case 10:
                AnsValid = 0;
                AnsRows = AnsCols = 0;
                printf("Ans cleared.\n");
                break;

            case 11: {
                int r, c;
                printf("Enter rows and columns: ");

                if (scanf("%d %d", &r, &c) != 2 ||
                    r < 1 || c < 1 || r > MAX || c > MAX) {
                    printf("Invalid dimensions.\n");
                    break;
                }

                int a[r][c], result[c][r];
                if (!matrixinput(r, c, a))
                    break;

                matrixtranspose(r, c, a, result);
                printf("Transpose of A:\n");
                matrixprint(c, r, result);
                saveAns(c, r, result);
                break;
            }

            case 12: {
                int n;
                printf("Enter size of square matrix: ");

                if (scanf("%d", &n) != 1 || n < 1 || n > MAX) {
                    printf("Invalid dimensions.\n");
                    break;
                }

                int a[n][n];
                if (!matrixinput(n, n, a))
                    break;

                long long result[n][n];
                int canStore = matrixadjugate(n, a, result);

                printf("Adjugate of A:\n");
                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < n; j++)
                        printf("%lld\t", result[i][j]);
                    printf("\n");
                }

                if (canStore) {
                    int stored[n][n];
                    for (int i = 0; i < n; i++)
                        for (int j = 0; j < n; j++)
                            stored[i][j] = (int)result[i][j];
                    saveAns(n, n, stored);
                } else {
                    printf("Adjugate values exceed int range; result not saved to Ans.\n");
                }

                break;
            }

            case 13: {
                int n;
                printf("Enter size of square matrix: ");

                if (scanf("%d", &n) != 1 || n < 1 || n > MAX) {
                    printf("Invalid dimensions.\n");
                    break;
                }

                int a[n][n];
                if (!matrixinput(n, n, a))
                    break;

                long long det = determinant(n, a);

                if (det == 0) {
                    printf("Inverse does not exist because determinant is 0.\n");
                    break;
                }

                long long adj[n][n];
                matrixadjugate(n, a, adj);

                double result[n][n];

                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < n; j++) {
                        result[i][j] = (double)adj[i][j] / det;
                    }
                }

                printf("Inverse of A:\n");
                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < n; j++)
                        printf("%.4f\t", result[i][j]);
                    printf("\n");
                }

                printf("Inverse displayed. Ans stores integers only, so this result was not saved to Ans.\n");
                break;
            }

            case 0:
                printf("Exiting Matrix Calculator. Goodbye!\n");
                break;

            default:
                printf("Invalid choice. Please select 0-13.\n");
        }

    } while (choice != 0);

    return 0;
}
