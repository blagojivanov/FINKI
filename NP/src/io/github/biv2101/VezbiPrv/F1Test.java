package io.github.biv2101.VezbiPrv;

import java.io.InputStream;
import java.io.OutputStream;
import java.io.PrintStream;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

public class F1Test {

    public static void main(String[] args) {
        F1Race f1Race = new F1Race();
        f1Race.readResults(System.in);
        f1Race.printSorted(System.out);
    }

}

class Lap implements Comparable<Lap> {
    private int mm;
    private int ss;
    private int nnn;

    public Lap(int mm, int ss, int nnn) {
        this.mm = mm;
        this.ss = ss;
        this.nnn = nnn;
    }

    public int getVal()
    {
        return mm*60*1000 + ss * 1000 + nnn;
    }
    @Override
    public int compareTo(Lap o) {
        return Integer.compare(getVal(), o.getVal());
    }

    @Override
    public String toString() {
        return String.format("%d:%02d:%03d", mm,ss,nnn);
    }
}

class Driver implements Comparable<Driver> {

    private String name;
    private List<Lap> laps;

    public Driver(String name, List<Lap> laps) {
        this.name = name;
        this.laps = laps;
    }

    public Lap getBest()
    {
        return laps.stream().sorted().collect(Collectors.toList()).get(0);
    }

    @Override
    public int compareTo(Driver o) {
        return Integer.compare(getBest().getVal(), o.getBest().getVal());
    }

    @Override
    public String toString() {
        return String.format("%-10s%10s", name, getBest());
    }
}

class F1Race {


    private List<Driver> drivers;

    public F1Race() {
        drivers = new ArrayList<>();
    }

    public void readResults(InputStream is) {
        Scanner sc = new Scanner(is);
        while (sc.hasNextLine()) {
            String[] lp = sc.nextLine().split("\\s+");
            String name = lp[0];
            String[] lap1 = lp[1].split(":");
            String[] lap2 = lp[2].split(":");
            String[] lap3 = lp[3].split(":");
            Lap l1 = new Lap(Integer.parseInt(lap1[0]), Integer.parseInt(lap1[1]), Integer.parseInt(lap1[2]));
            Lap l2 = new Lap(Integer.parseInt(lap2[0]), Integer.parseInt(lap2[1]), Integer.parseInt(lap2[2]));
            Lap l3 = new Lap(Integer.parseInt(lap3[0]), Integer.parseInt(lap3[1]), Integer.parseInt(lap3[2]));
            List<Lap> laps = new ArrayList<>();
            laps.add(l1);
            laps.add(l2);
            laps.add(l3);

            Driver d = new Driver(name, laps);
            drivers.add(d);
        }
    }

    public void printSorted(OutputStream os)
    {
        PrintStream ps = new PrintStream(os);

        List<Driver> collect = drivers.stream().sorted().collect(Collectors.toList());
        IntStream.range(0, collect.size()).forEach(i->ps.println(i+1 + ". " + collect.get(i)));
        ps.flush();
    }

}