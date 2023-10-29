package io.github.biv2101.Labs.Lab1;

import java.util.Scanner;

public class ReverseWord {

    public static void printReversed(String word) {
        StringBuilder sb = new StringBuilder();
        for (int i = word.length()-1; i>=0; i--)
        {
            sb.append(word.charAt(i));
        }
        System.out.println();
    }

    public static void main(String[] args) {
        Scanner s = new Scanner(System.in);
        int n = s.nextInt();

        for (int i = 0; i < n; i++) {
            printReversed(s.next());
        }
    }
}

