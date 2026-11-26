#include <stdio.h>

#define MAX 10

void readMatrix(int m[MAX][MAX], int rows, int cols)
{
    int i, j;
    for (i = 0; i < rows; i++)
        for (j = 0; j < cols; j++)
            scanf("%d", &m[i][j]);
}

int main()
{
    int a[MAX][MAX], b[MAX][MAX], c[MAX][MAX];
    int r1, c1, r2, c2, i, j, k;

    printf("Enter rows and columns of first matrix (max 10): ");
    scanf("%d %d", &r1, &c1);
    printf("Enter rows and columns of second matrix (max 10): ");
    scanf("%d %d", &r2, &c2);

    if (r1 < 1 || r1 > MAX || c1 < 1 || c1 > MAX ||
        r2 < 1 || r2 > MAX || c2 < 1 || c2 > MAX)
    {
        printf("Invalid matrix size.\n");
        return 1;
    }

    if (c1 != r2)
    {
        printf("Multiplication not possible: columns of first must equal rows of second.\n");
        return 1;
    }

    printf("Enter elements of first matrix:\n");
    readMatrix(a, r1, c1);
    printf("Enter elements of second matrix:\n");
    readMatrix(b, r2, c2);

    for (i = 0; i < r1; i++)
    {
        for (j = 0; j < c2; j++)
        {
            c[i][j] = 0;
            for (k = 0; k < c1; k++)
                c[i][j] += a[i][k] * b[k][j];
        }
    }

    printf("Product matrix:\n");
    for (i = 0; i < r1; i++)
    {
        for (j = 0; j < c2; j++)
            printf("%d\t", c[i][j]);
        printf("\n");
    }

    return 0;
}
