package io.github.biv2101.Aud.Aud2;

import io.github.biv2101.Standard.SLL;
import io.github.biv2101.Standard.SLLNode;

public class SpojListi<E extends Comparable<E>> {

    public SLL<E> mergeLists(SLL<E> list1, SLL<E> list2) {
        SLL<E> rezniza = new SLL<>();
        SLLNode<E> node1 = list1.getFirst();
        SLLNode<E> node2 = list2.getFirst();
        while (node1 != null && node2 != null) {
            if (node1.element.compareTo(node2.element) < 0) {
                rezniza.insertLast(node1.element);
                node1 = node1.succ;
            } else {
                rezniza.insertLast(node2.element);
                node2 = node2.succ;
            }
        }


        while (node1 != null)
        {
            rezniza.insertLast(node1.element);
            node1 = node1.succ;
        }

        while (node2 != null)
        {
            rezniza.insertLast(node2.element);
            node2 = node2.succ;
        }

        return rezniza;
    }

    public static void main(String[] args) {
        SLL<String> niza1 = new SLL<>();
        niza1.insertLast("Ana");
        niza1.insertLast("Bojana");
        niza1.insertLast("Dejan");
        niza1.insertLast("Martin");

        SLL<String> niza2 = new SLL<>();
        niza2.insertLast("Adrijana");
        niza2.insertLast("Biljana");
        niza2.insertLast("Stefan");
        niza2.insertLast("Xae2101");

        SpojListi<String> joiner = new SpojListi<>();

        System.out.println(joiner.mergeLists(niza1,niza2));


    }
}
