package io.github.biv2101.VezbiPrv;

import io.github.biv2101.Standard.DLL;
import io.github.biv2101.Standard.DLLNode;

import java.util.Scanner;

public class ListaOdListi {
    public static long findMagicNumber(DLL<DLL<Integer>> list) {
        long mult = 1;
        for (DLLNode<DLL<Integer>> curr = list.getFirst(); curr != null; curr = curr.succ)
        {
            long sum = 0;
            for (DLLNode<Integer> subcurr = curr.element.getFirst(); subcurr!=null; subcurr = subcurr.succ)
            {
                sum += subcurr.element;
            }
            mult*=sum;
        }
        return mult;
    }

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        int m = in.nextInt();
        DLL<DLL<Integer>> list = new DLL<DLL<Integer>>();
        for (int i = 0; i < n; i++) {
            DLL<Integer> tmp = new DLL<Integer>();
            for (int j = 0; j < m; j++) {
                tmp.insertLast(in.nextInt());
            }
            list.insertLast(tmp);
        }
        in.close();
        System.out.println(findMagicNumber(list));
    }

}
