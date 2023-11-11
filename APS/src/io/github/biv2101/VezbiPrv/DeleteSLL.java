package io.github.biv2101.VezbiPrv;

import io.github.biv2101.Standard.SLL;
import io.github.biv2101.Standard.SLLNode;

import java.util.Scanner;

public class DeleteSLL {
    public static void change(SLL<Integer> list, int br) {
        SLLNode<Integer> first = null;
        SLLNode<Integer> curr = list.getFirst();
        int ct = 0;
        while (curr != null) {
            if (curr.element.equals(br) && first == null) {
                first = curr;
                ct++;
            } else if (curr.element.equals(br)) {
                ct++;
            }
            curr = curr.succ;
        }
        if (ct % 2 == 1) {
            list.insertAfter(br, first);
        }
    }

    public static void main(String[] args) {
        // TODO Auto-generated method stub
        Scanner scan = new Scanner(System.in);
        int n, broj;
        SLL<Integer> list1 = new SLL<Integer>();
        n = scan.nextInt();
        for (int i = 0; i < n; i++) {
            list1.insertLast(scan.nextInt());
        }
        int br = scan.nextInt();
        change(list1, br);
        System.out.println(list1);


    }
}
