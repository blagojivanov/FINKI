package io.github.biv2101.Aud;

import java.util.Arrays;
import java.util.DoubleSummaryStatistics;
import java.util.List;
import java.util.stream.DoubleStream;

public class MathClass {

    public static void printStat(List<? extends Number> numbers) {
        DoubleSummaryStatistics doubleSummaryStatistics = numbers.stream().mapToDouble(Number::doubleValue).summaryStatistics();
        System.out.println(doubleSummaryStatistics.toString());
    }

    public static void main(String[] args) {

    }
}
