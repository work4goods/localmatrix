#include "Params.h"

double func0(int i, int j, int n)
{
    return i+j == n-1 ?1 :0;
}

double func1(int i, int j, int n)
{
    if(i == j && 0 < i && i < n-1)
    {
        return -2;
    }
    if(i == j-1 || i== j+1)
    {
        return 1;
    }
    if(i == 0 && j == 0)
    {
        return -1;
    }
    if (i == n-1 && j == n-1)
    {
        return -1 + 1.0/n;
    }
    else
    {
        return 0;
    }
}

int enterData(double* matrix, double *vector, int n, FILE* fin, int functionNumber)
{
    int i, j;

    if (fin)
    {
        printf("\n Check 1\n");
        for (i = 0; i < n; ++i)
        {
            for (j = 0; j < n; ++j)
            {
                if (fscanf(fin, "%lf", &matrix[i*n+j]) != 1)
                {
                    printf("\n Check 2\n");
                    return -1;
                }
            }

            if (fscanf(fin, "%lf", &vector[i]) != 1)
                return -1;
        }
    }
    else
    {
        for (i = 0; i < n; ++i)
        {
            for (j = 0; j < n; ++j)
            {
                switch(functionNumber)
                {
                    case 0:
                    {
                        matrix[i*n+j] = func0(i, j, n);
                        break;
                    }
                    case 1:
                    {
                        matrix[i*n+j] = func1(i, j, n);
                        break;
                    }
                    case 2:
                    {
                        printf("\n Enter [%d][%d] = ", i, j);
                        scanf("%lf", &matrix[i*n+j]);
                        break;
                    }

                }

            }

            printf("\n Enter right[%d] = ", i);
            scanf("%lf", &vector[i]);
        }
    }

    return 0;
}

void printResult(double* result, int n, int m)
{
    int i;
    int min_ = fmin(n,m);

    for (i = 0; i < min_; ++i)
        printf("%f ", result[i]);
    if (min_ < n-1)
        printf("... ");
    if (min_ != n)
        printf("%f ", result[n-1]);
}

void printMatrix(double *matrix, int n, int m)
{
    int i, j;
    int min_ = fmin(n,m);

    for(i = 0; i < min_; ++i)
    {
        for(j = 0; j < min_; ++j)
        {
            printf("%f ", matrix[i*n+j]);
        }
        if (min_ < n-1)
            printf("... ");
        if (min_ != n)
            printf("%f ", matrix[i*n+n-1]);

        printf("\n");
    }

    if (min_ < n-1)
    {
        printf("... ");
        printf("\n");
    }

    if (min_ != n)
    {
        for(j = 0; j < min_; j++)
        {
            printf("%f ", matrix[(n-1)*n+j]);
        }
    }

    if (min_ < n-1)
        printf("... ");

    if (min_ != n)
        printf("%f\n",matrix[(n-1)*n+n-1]);
}

float residualNorm(double* matrix, double* vector, double* result, int n)
{
    int i, j;
    float res = 0;
    double a;

    for (i = 0; i < n; ++i)
    {
        a = 0.0;

        for (j = 0; j < n; ++j)
            a += matrix[i*n+j] * result[j];

        a -= vector[i];

        res += a*a;
    }

    return sqrt(res);
}
