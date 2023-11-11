package io.github.biv2101.Labs.Lab1;

import java.io.ByteArrayInputStream;
import java.io.InputStream;
import java.util.*;
import java.util.stream.IntStream;

final class IntegerArray {
    private final int[] arr;
    private final int leng;

    public IntegerArray(int a[]) {
        this.arr = Arrays.copyOf(a, a.length);
        this.leng = a.length;
    }

    public int length() {
        return this.leng;
    }

    public int getElementAt(int i) {
        if (i < 0 || i > leng - 1) {
            throw new IndexOutOfBoundsException();
        }
        return arr[i];
    }

    public int sum() {
        return IntStream.of(arr).sum();
    }


    public double average() {
        return (double) sum() /leng;
    }

    public IntegerArray getSorted() {
        int[] sarr = Arrays.copyOf(arr, leng);
        Arrays.sort(sarr);
        return new IntegerArray(sarr);
    }

    //lambda ??
    public IntegerArray concat(IntegerArray ia) {
        int[] narr = new int[leng + ia.length()];
        for (int i = 0; i < leng; i++) {
            narr[i] = arr[i];
        }

        for (int i = 0; i < ia.length(); i++) {
            narr[leng+i] = ia.getElementAt(i);
        }

        return new IntegerArray(narr);
    }

    @Override
    public String toString() {
        return Arrays.toString(arr);
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        IntegerArray that = (IntegerArray) o;
        return leng == that.leng && Arrays.equals(arr, that.arr);
    }

    @Override
    public int hashCode() {
        return 0;
    }
}

class ArrayReader {
    public static IntegerArray readIntegerArray(InputStream input) {
        Scanner sc = new Scanner(input);
        int l = sc.nextInt();
        int[] narr = new int[l];
        for (int i = 0; i < l; i++) {
            narr[i] = sc.nextInt();
        }
        return new IntegerArray(narr);
    }
}

public class IntegerArrayTester {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        String s = scanner.nextLine();
        IntegerArray ia = null;
        switch (s) {
            case "testSimpleMethods":
                ia = new IntegerArray(generateRandomArray(scanner.nextInt()));
                testSimpleMethods(ia);
                break;
            case "testConcat":
                testConcat(scanner);
                break;
            case "testEquals":
                testEquals(scanner);
                break;
            case "testSorting":
                testSorting(scanner);
                break;
            case "testReading":
                testReading(new ByteArrayInputStream(scanner.nextLine().getBytes()));
                break;
            case "testImmutability":
                int a[] = generateRandomArray(scanner.nextInt());
                ia = new IntegerArray(a);
                testSimpleMethods(ia);
                testSimpleMethods(ia);
                IntegerArray sorted_ia = ia.getSorted();
                testSimpleMethods(ia);
                testSimpleMethods(sorted_ia);
                sorted_ia.getSorted();
                testSimpleMethods(sorted_ia);
                testSimpleMethods(ia);
                a[0] += 2;
                testSimpleMethods(ia);
                ia = ArrayReader.readIntegerArray(new ByteArrayInputStream(integerArrayToString(ia).getBytes()));
                testSimpleMethods(ia);
                break;
        }
        scanner.close();
    }

    static void testReading(InputStream in) {
        IntegerArray read = ArrayReader.readIntegerArray(in);
        System.out.println(read);
    }

    static void testSorting(Scanner scanner) {
        int[] a = readArray(scanner);
        IntegerArray ia = new IntegerArray(a);
        System.out.println(ia.getSorted());
    }

    static void testEquals(Scanner scanner) {
        int[] a = readArray(scanner);
        int[] b = readArray(scanner);
        int[] c = readArray(scanner);
        IntegerArray ia = new IntegerArray(a);
        IntegerArray ib = new IntegerArray(b);
        IntegerArray ic = new IntegerArray(c);
        System.out.println(ia.equals(ib));
        System.out.println(ia.equals(ic));
        System.out.println(ib.equals(ic));
    }

    static void testConcat(Scanner scanner) {
        int[] a = readArray(scanner);
        int[] b = readArray(scanner);
        IntegerArray array1 = new IntegerArray(a);
        IntegerArray array2 = new IntegerArray(b);
        IntegerArray concatenated = array1.concat(array2);
        System.out.println(concatenated);
    }

    static void testSimpleMethods(IntegerArray ia) {
        System.out.print(integerArrayToString(ia));
        System.out.println(ia);
        System.out.println(ia.sum());
        System.out.printf("%.2f\n", ia.average());
    }


    static String integerArrayToString(IntegerArray ia) {
        StringBuilder sb = new StringBuilder();
        sb.append(ia.length()).append('\n');
        for (int i = 0; i < ia.length(); ++i)
            sb.append(ia.getElementAt(i)).append(' ');
        sb.append('\n');
        return sb.toString();
    }

    static int[] readArray(Scanner scanner) {
        int n = scanner.nextInt();
        int[] a = new int[n];
        for (int i = 0; i < n; ++i) {
            a[i] = scanner.nextInt();
        }
        return a;
    }


    static int[] generateRandomArray(int k) {
        Random rnd = new Random(k);
        int n = rnd.nextInt(8) + 2;
        int a[] = new int[n];
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.nextInt(20) - 5;
        }
        return a;
    }

}
