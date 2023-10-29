package io.github.biv2101.Aud.Aud2;

import java.util.ArrayList;

public class DveNizi<E> {

    public void changeArrays(ArrayList<E> array1, ArrayList<E> array2) {
        if (array1.size() == array2.size()) {
            int size = array1.size();
            int i = 0;
            while (i < size) {
                System.out.println("Comparing: " + array1.get(i) + array2.get(i));
                if (array1.get(i) == array2.get(i)) {
                    System.out.println("Deleted " + array1.get(i));
                    array1.remove(i);
                    array2.remove(i);
                    size--;
                } else {
                    i++;
                }
            }
        } else {
            System.out.println("Nizite ne se so ista golemina");
            return;
        }
    }

    public static void main(String[] args) {
        ArrayList<String> niza1 = new ArrayList<String>(4);
        niza1.add("a");
        niza1.add("b");
        niza1.add("c");
        niza1.add("d");

        ArrayList<String> niza2 = new ArrayList<String>(4);
        niza2.add("a");
        niza2.add("b");
        niza2.add("d");
        niza2.add("e");

        System.out.println(niza1.toString());
        System.out.println(niza2.toString());

        DveNizi<String> changer = new DveNizi<String>();

        changer.changeArrays(niza1, niza2);

        System.out.println(niza1.toString());
        System.out.println(niza2.toString());


    }

}
