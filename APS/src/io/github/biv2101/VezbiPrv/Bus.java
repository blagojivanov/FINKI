package io.github.biv2101.VezbiPrv;

import java.io.BufferedReader;
import java.io.InputStreamReader;

public class Bus {

    public static void main(String[] args) throws Exception {
        int i, j, k;

        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        int N = Integer.parseInt(br.readLine());
        int M = Integer.parseInt(br.readLine());

        br.close();
        int sumMin = (M > N) ? (M - N) * 100 + N * 100 : (N - M) * 100 + M * 100;
        int sumMax = (M>0) ? (M + N - 1) * 100 : (M+N)*100;

        System.out.println(sumMin);
        System.out.println(sumMax);
    }

}
