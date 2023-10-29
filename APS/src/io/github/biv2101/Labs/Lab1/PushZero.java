package io.github.biv2101.Labs.Lab1;

import java.util.Scanner;

import static java.util.Collections.swap;

public class PushZero {

    static void pushZerosToBeginning(int arr[], int n) {
        int k = n-1;
        for (int i = n-2; i>=0; i--)
        {
            if (arr[k] == 0 && arr[i] != 0)
            {
                arr[k] = arr[i];
                arr[i] = 0;
                k--;
            } else if (arr[k] != 0)
            {
                k--;
            }
        }
        for (int a : arr) {
            System.out.print(a + " ");
        }
    }

    public static void main(String[] args) {

        Scanner s = new Scanner(System.in);
        int n = s.nextInt();
        int[] array = new int[n];
        for (int i = 0; i < n; i++) {
            array[i] = s.nextInt();
        }

        System.out.println("Transformiranata niza e:");
        pushZerosToBeginning(array, n);
    }
}