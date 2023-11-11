package io.github.biv2101.VezbiPrv;

import java.util.Arrays;
import java.util.Scanner;


public class LDS {
    // TODO: resi so dinamicko programiranje
    private static int najdolgaOpagackaSekvenca(int[] a) {
        int[] lengths = new int[a.length];
        Arrays.fill(lengths,1);
        for (int i = a.length - 1; i >= 0; i--) {
            for (int j = i + 1; j < a.length; j++) {
                if (lengths[i] <= lengths[j] && a[j] < a[i]) {
                    lengths[i] = lengths[j] + 1;
                }
            }
        }

        return Arrays.stream(lengths).max().getAsInt();
    }

    public static void main(String[] args) {
        Scanner stdin = new Scanner(System.in);

        int n = stdin.nextInt();
        int a[] = new int[n];
        for (int i = 0; i < a.length; i++) {
            a[i] = stdin.nextInt();
        }
        System.out.println(najdolgaOpagackaSekvenca(a));
    }


}
