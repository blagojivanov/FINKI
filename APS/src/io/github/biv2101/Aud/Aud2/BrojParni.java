package io.github.biv2101.Aud.Aud2;

import io.github.biv2101.Standard.SLL;
import io.github.biv2101.Standard.SLLNode;

import java.util.Scanner;

public class BrojParni {
    public static int checkEven(SLL<Integer> list) {
        SLLNode<Integer> temp = list.getFirst();
        int res = 0;

        while (temp != null) {
            if (temp.element % 2 == 0) {
                res++;
            }
            temp = temp.succ;
        }
        return res;
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        int n = sc.nextInt();

        SLL<Integer> list = new SLL<>();
        for (int i = 0; i<n; i++){
            list.insertLast(sc.nextInt());
        }

        System.out.println(checkEven(list));
    }
}
