package io.github.biv2101.Labs.Lab4;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class SumOfAbsoluteDifferences {

    static int solve(int numbers[], int n, int k) {
        int [][] dp = new int[n][k]; // prv so vtor, so tret so n-ti - vtor so vtor vtor so tret, son ti
        int max = 0;

        for (int i = 0; i<n; i++) {
            for (int j = 1; j < k; j++) {
                for (int z = 0; z < i; z++) {
                    dp[i][j] = Math.max(dp[i][j], dp[z][j - 1] + Math.abs(numbers[i] - numbers[z]));
                }
                max = Math.max(dp[i][j], max);
            }
        }
        // vasiot kod ovde
        // mozete da napisete i drugi funkcii dokolku vi se potrebni
        return max;
    }

    public static void main(String[] args) throws Exception {
        int i, j, k;

        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());
        int N = Integer.parseInt(st.nextToken());
        int K = Integer.parseInt(st.nextToken());

        int numbers[] = new int[N];

        st = new StringTokenizer(br.readLine());
        for (i = 0; i < N; i++) {
            numbers[i] = Integer.parseInt(st.nextToken());
        }

        int res = solve(numbers, N, K);
        System.out.println(res);

        br.close();

    }

}