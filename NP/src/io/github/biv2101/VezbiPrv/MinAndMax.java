package io.github.biv2101.VezbiPrv;

import java.util.Comparator;
import java.util.Scanner;

class MinMax<T extends Comparable<T>> {
    private T minimum;
    private T maximum;

    int diff, ctMax, ctMin;

    void update(T t) {
        if (diff == 0) maximum = minimum = t;
        if (maximum.compareTo(t) == 0) ctMax++;
        if (minimum.compareTo(t) == 0) ctMin++;

        if (minimum.compareTo(t) > 0) {
            minimum = t;
            ctMin = 1;
        }
        if (maximum.compareTo(t) < 0) {
            maximum = t;
            ctMax = 1;
        }
        diff++;
    }


    public T min() {
        return minimum;
    }

    public T max() {
        return maximum;
    }

    @Override
    public String toString() {
        return minimum + " " + maximum + " " + (diff - ctMax - ctMin) + "\n";
    }
}

public class MinAndMax {
    public static void main(String[] args) throws ClassNotFoundException {
        Scanner scanner = new Scanner(System.in);
        int n = scanner.nextInt();
        MinMax<String> strings = new MinMax<String>();
        for (int i = 0; i < n; ++i) {
            String s = scanner.next();
            strings.update(s);
        }
        System.out.println(strings);
        MinMax<Integer> ints = new MinMax<Integer>();
        for (int i = 0; i < n; ++i) {
            int x = scanner.nextInt();
            ints.update(x);
        }
        System.out.println(ints);
    }
}