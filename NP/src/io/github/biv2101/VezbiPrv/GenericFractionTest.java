package io.github.biv2101.VezbiPrv;

import java.util.Scanner;

class ZeroDenominatorException extends Exception {

    @Override
    public String getMessage() {
        return "Denominator cannot be zero";
    }
}

class GenericFraction<T extends Number, U extends Number> {
    T numerator;
    U denominator;

    public GenericFraction(T numerator, U denominator) throws ZeroDenominatorException {
        this.numerator = numerator;
        if (denominator.doubleValue() != 0) {
            this.denominator = denominator;
        } else {
            throw new ZeroDenominatorException();
        }
    }

    GenericFraction<Double, Double> add(GenericFraction<? extends Number, ? extends Number> gf) {
        Double b = denominator.doubleValue() * gf.denominator.doubleValue();
        Double a = numerator.doubleValue() * gf.denominator.doubleValue() + gf.numerator.doubleValue() * denominator.doubleValue();
        try {
            return new GenericFraction<Double, Double>(a, b);
        } catch (ZeroDenominatorException e) {
            throw new RuntimeException(e);
        }
    }

    public double toDouble() {
        return numerator.doubleValue() / denominator.doubleValue();
    }

    public int nzs(int a, int b) {
        return b == 0 ? a : nzs(b, a % b);
    }

    @Override
    public String toString() {
        int nzss = nzs(numerator.intValue(), denominator.intValue());
        return String.format("%.2f / %.2f", numerator.doubleValue() / nzss, denominator.doubleValue() / nzss);
    }
}

public class GenericFractionTest {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        double n1 = scanner.nextDouble();
        double d1 = scanner.nextDouble();
        float n2 = scanner.nextFloat();
        float d2 = scanner.nextFloat();
        int n3 = scanner.nextInt();
        int d3 = scanner.nextInt();
        try {
            GenericFraction<Double, Double> gfDouble = new GenericFraction<Double, Double>(n1, d1);
            GenericFraction<Float, Float> gfFloat = new GenericFraction<Float, Float>(n2, d2);
            GenericFraction<Integer, Integer> gfInt = new GenericFraction<Integer, Integer>(n3, d3);
            System.out.printf("%.2f\n", gfDouble.toDouble());
            System.out.println(gfDouble.add(gfFloat));
            System.out.println(gfInt.add(gfFloat));
            System.out.println(gfDouble.add(gfInt));
            gfInt = new GenericFraction<Integer, Integer>(n3, 0);
        } catch (ZeroDenominatorException e) {
            System.out.println(e.getMessage());
        }

        scanner.close();
    }

}

// вашиот код овде
