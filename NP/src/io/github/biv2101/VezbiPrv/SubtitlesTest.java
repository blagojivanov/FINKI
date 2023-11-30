package io.github.biv2101.VezbiPrv;

import java.io.InputStream;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class SubtitlesTest {
    public static void main(String[] args) {
        Subtitles subtitles = new Subtitles();
        int n = subtitles.loadSubtitles(System.in);
        System.out.println("+++++ ORIGINIAL SUBTITLES +++++");
        subtitles.print();
        int shift = n * 37;
        shift = (shift % 2 == 1) ? -shift : shift;
        System.out.println(String.format("SHIFT FOR %d ms", shift));
        subtitles.shift(shift);
        System.out.println("+++++ SHIFTED SUBTITLES +++++");
        subtitles.print();
    }
}

class SubTime {

    private int hh;
    private int mm;
    private int ss;
    private int ms;

    public SubTime(String segment) {
        String[] parts = segment.split(":");
        String[] p2 = parts[2].split(",");
        hh = Integer.parseInt(parts[0]);
        mm = Integer.parseInt(parts[1]);
        ss = Integer.parseInt(p2[0]);
        ms = Integer.parseInt(p2[1]);
    }

    public void shiftMss(int mss) {
        int totalms = hh * 3600 * 1000 + mm * 60 * 1000 + ss * 1000 + ms + mss;
        hh = totalms / (3600 * 1000);
        totalms %= (3600 * 1000);
        mm = totalms / (60 * 1000);
        totalms %= (60 * 1000);
        ss = totalms / 1000;
        ms = totalms % 1000;

    }

    @Override
    public String toString() {
        return String.format("%02d:%02d:%02d,%03d", hh, mm, ss, ms);
    }
}

class Sub {
    private int nr;
    private SubTime start;
    private SubTime end;

    private String text;

    public Sub(List<String> segment) {
        this.nr = Integer.parseInt(segment.get(0));
        String[] parts = segment.get(1).split(" --> ");
        this.start = new SubTime(parts[0]);
        this.end = new SubTime(parts[1]);
        this.text = segment.get(2);
    }

    public void shiftTimes(int mss) {
        start.shiftMss(mss);
        end.shiftMss(mss);
    }

    @Override
    public String toString() {
        return String.format("%d\n%s --> %s\n%s\n", nr, start, end, text);
    }
}

class Subtitles {
    private List<Sub> subs;

    public Subtitles() {
        this.subs = new ArrayList<>();
    }

    public int loadSubtitles(InputStream is) {
        Scanner sc = new Scanner(is);
        while (sc.hasNextLine()) {
            String s1 = sc.nextLine();
            String s2 = sc.nextLine();
            String s3 = sc.nextLine();
            if (sc.hasNextLine()) {
                String next = sc.nextLine();
                if (!next.isEmpty()) {
                    s3 = s3.concat("\n" + next);
                    if (sc.hasNextLine()) {
                        sc.nextLine();
                    }
                }
            }
            List<String> strings = new ArrayList<>();
            strings.add(s1);
            strings.add(s2);
            strings.add(s3);

            subs.add(new Sub(strings));
        }
        return subs.size();
    }

    public void print() {
        subs.forEach(System.out::println);
    }

    public void shift(int mss) {
        subs.stream().forEach(sub -> sub.shiftTimes(mss));
    }
}