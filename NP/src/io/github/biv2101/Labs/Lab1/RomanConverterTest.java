package io.github.biv2101.Labs.Lab1;

import java.util.*;
import java.util.stream.IntStream;

public class RomanConverterTest {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int n = scanner.nextInt();
        IntStream.range(0, n)
                .forEach(x -> System.out.println(RomanConverter.toRoman(scanner.nextInt())));
        scanner.close();
    }
}


class RomanConverter {
    /**
     * Roman to decimal converter
     *
     * @param n number in decimal format
     * @return string representation of the number in Roman numeral
     */
    public static String toRoman(int n) {

        StringBuilder sb = new StringBuilder();

        int [] arr = {1000,900,500,400,100,90,50,40,10,9,5,4,1};
        String [] arrs = {"M","CM","D","CD","C","XC","L","XL","X","IX","V","IV","I"};

        for (int i = 0; i < arr.length; i++)
        {
            while (n >= arr[i]){
                sb.append(arrs[i]);
                n-=arr[i];
            }
        }

        return sb.toString();
    }

}
