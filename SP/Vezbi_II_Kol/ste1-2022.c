#include <stdio.h>
#include <stdlib.h>

void wf()
{
    FILE *f = fopen("input.txt", "w");
    char c;
    while ((c=getchar())!= '~')
    {
        fputc(c,f);
    }
    fclose(f);
}

float find(int mat[100][100], int n, int m, int i, int j)
{
    float sum = 0;
    int k, l, ct=0;
    for (k = i-1, l = j-1; k>=0; k--,l--) // gore levo
    {
        sum+=(float) mat[k][l];
        ct++;

    }
    for (k = i-1, l = j+1; k>=0&&l<m; k--,l++) // gore desno
    {
        sum+=(float) mat[k][l];
        ct++;

    }
    for (k = i+1, l = j-1; k<n && l >=0; k++, l--) // dole levo
    {
        sum+=(float) mat[k][l];
        ct++;
    }
    for (k = i+1, l = j+1; k<n && l <m; k++, l++) // dole desno
    {
        sum+= (float) mat[k][l];
        ct++;
    }
    return sum/(float)ct;
}

int main() {
    wf();
    FILE *f = fopen("input.txt", "r");
    int m, n, a[100][100];
    float k[100][100];
    fscanf(f, "%d %d\n", &n, &m);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            fscanf(f, "%d ", &a[i][j]);
        }
    }

    for (int i = 0; i<n; i++)
    {
        for (int j = 0; j<m; j++)
        {
            k[i][j] = find(a,n,m,i,j);
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%.2f ", k[i][j]);
        }
        printf("\n");
    }
    //printf("%.2f", find(a,n,m,1,2));
    fclose(f);
    return 0;

}


