package io.github.biv2101.Labs.Lab3;

import java.util.Scanner;

public class CountWordPairs {

    //TODO: implement function
    public static int countWordPairs(String[] words) {
        int pairs[] = new int[26];
        int rett = 0;
        for (String w : words) {
            pairs[w.charAt(0) - 97]++;
        }
        for (int p : pairs) {
            if (p >= 2) {
                rett += p * (p - 1) / 2;
            }
        }
        return rett;
    }

    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        int N = input.nextInt();

        String words[] = new String[N];

        for (int i = 0; i < N; i++) {
            words[i] = input.next();
        }

        System.out.println(countWordPairs(words));

    }
}