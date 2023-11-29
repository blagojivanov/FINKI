package io.github.biv2101.VezbiPrv;

import java.util.Scanner;

class Triple<T extends Number> {
    T one, two, three;

    public Triple(T one, T two, T three) {
        this.one = one;
        this.two = two;
        this.three = three;
    }

    public double max() {
        double oned = one.doubleValue();
        double twod = two.doubleValue();
        double threed = three.doubleValue();
        return Math.max(oned, Math.max(twod, threed));
    }

    public double avarage() {
        double oned = one.doubleValue();
        double twod = two.doubleValue();
        double threed = three.doubleValue();
        return (oned + twod + threed) / 3.0;
    }

    public void sort() {
        if (max() == one.doubleValue()) {
            T temp = one;
            one = three;
            three = temp;

            if (two.doubleValue() < one.doubleValue()) {
                T temp2 = one;
                one = two;
                two = temp2;
            }
        } else if (max() == two.doubleValue()) {
            T temp = two;
            two = three;
            three = temp;

            if (two.doubleValue() < one.doubleValue()) {
                T temp2 = one;
                one = two;
                two = temp2;
            }
        } else if (max() == three.doubleValue())
        {
            if (two.doubleValue() < one.doubleValue()) {
                T temp2 = one;
                one = two;
                two = temp2;
            }
        }
    }

    @Override
    public String toString() {
        return String.format("%.2f %.2f %.2f", one.doubleValue(), two.doubleValue(), three.doubleValue());
    }
}

public class TripleTest {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int a = scanner.nextInt();
        int b = scanner.nextInt();
        int c = scanner.nextInt();
        Triple<Integer> tInt = new Triple<Integer>(a, b, c);
        System.out.printf("%.2f\n", tInt.max());
        System.out.printf("%.2f\n", tInt.avarage());
        tInt.sort();
        System.out.println(tInt);
        float fa = scanner.nextFloat();
        float fb = scanner.nextFloat();
        float fc = scanner.nextFloat();
        Triple<Float> tFloat = new Triple<Float>(fa, fb, fc);
        System.out.printf("%.2f\n", tFloat.max());
        System.out.printf("%.2f\n", tFloat.avarage());
        tFloat.sort();
        System.out.println(tFloat);
        double da = scanner.nextDouble();
        double db = scanner.nextDouble();
        double dc = scanner.nextDouble();
        Triple<Double> tDouble = new Triple<Double>(da, db, dc);
        System.out.printf("%.2f\n", tDouble.max());
        System.out.printf("%.2f\n", tDouble.avarage());
        tDouble.sort();
        System.out.println(tDouble);
    }
}
// vasiot kod ovde
// class Triple


