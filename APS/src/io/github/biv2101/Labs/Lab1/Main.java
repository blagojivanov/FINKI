package io.github.biv2101.Labs.Lab1;

import java.util.List;
import java.util.Scanner;
import java.util.Vector;

class QuarterlySales {

    private int numOfSales;
    private int[] revenues;
    private int quarterNo;

    public QuarterlySales(int numOfSales, int[] revenues, int quarterNo) {
        this.numOfSales = numOfSales;
        this.revenues = revenues;
        this.quarterNo = quarterNo;
    }

    public void readQuarter(int quarterN) {
        quarterNo = quarterN;
        Scanner s = new Scanner(System.in);
        for (int i = 0; i < numOfSales; i++) {
            revenues[i] = s.nextInt();
        }
    }

    public void setRevenues(int[] revenues) {
        this.revenues = revenues;
    }

    public int calculate() {
        int retsum = 0;
        for (int s : revenues) retsum += s;
        return retsum;
    }

    @Override
    public String toString() {

        int calculated = calculate();
        return calculated + "   ";
    }

}

class SalesPerson {

    private String name;
    private QuarterlySales[] quarters;

    public SalesPerson(String name, QuarterlySales[] quarters) {
        this.name = name;
        this.quarters = quarters;
    }

    public void readPerson() {
        Scanner sc = new Scanner(System.in);
        name = sc.next();
        for (int i = 1; i <= 4; i++) {
            quarters[i - 1].readQuarter(i);
        }
    }

    public QuarterlySales[] getQuarters() {
        return quarters;
    }

    public String getName()
    {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append(name).append("   ");
        for (QuarterlySales q : quarters) {
            sb.append(q.toString());
        }
        return sb.toString();
    }

}


public class Main {


    public static int sumSales(SalesPerson sp) {
        int sum = 0;
        for (QuarterlySales q : sp.getQuarters()) {
            sum += q.calculate();
        }
        return sum;
    }

    public static SalesPerson salesChampion(SalesPerson[] arr) {
        SalesPerson max = arr[0];
        for (SalesPerson sp : arr) {
            if (sumSales(sp) > sumSales(max)) {
                max = sp;
            }
        }
        return max;
    }

    public static void table(SalesPerson[] arr) {
        System.out.println("SP   1   2   3   4   Total");
        for (SalesPerson sp : arr)
        {
            System.out.println(sp.toString() + sumSales(sp));
        }
    }

    public static void main(String[] args) {

        int n;
        Scanner input = new Scanner(System.in);
        n = input.nextInt();
        SalesPerson[] arr = new SalesPerson[n];
        for (int i = 0; i < n; i++) {

            String name = input.next();
            QuarterlySales[] qs = new QuarterlySales[4];
            for (int j = 0; j < 4; j++){
                int sn = input.nextInt();
                int[] rev = new int[sn];
                for (int k = 0; k < sn; k++)
                {
                    rev[k] = input.nextInt();
                }
                qs[j] = new QuarterlySales(sn, rev, j+1); 
            }
            arr[i] = new SalesPerson(name, qs);
        }

        table(arr);
        System.out.println("\nSALES CHAMPION: " + salesChampion(arr).getName());

    }

}