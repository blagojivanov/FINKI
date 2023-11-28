package io.github.biv2101.VezbiPrv;

import java.io.InputStream;
import java.io.OutputStream;
import java.io.PrintStream;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;
import java.util.Scanner;

class UnsupportedFormatException extends Exception {

    private String time;
    public UnsupportedFormatException(String time)
    {
        this.time = time;
    }

    @Override
    public String getMessage() {
        return time;
    }
}

class InvalidTimeException extends Exception {

    private String time;
    public InvalidTimeException(String time)
    {
        this.time = time;
    }

    @Override
    public String getMessage() {
        return time;
    }
}

class Time implements Comparable<Time> {
    int hours;
    int minutes;

    public Time(int hours, int minutes) {
        this.hours = hours;
        this.minutes = minutes;
    }

    public int value() {
        return hours * 60 + minutes;
    }

    public String timeString(TimeFormat tf) {
        if (tf == TimeFormat.FORMAT_24) {
            return String.format("%2d:%02d", hours, minutes);
        } else {
            String pref = "AM";
            int hrs;
            if (hours == 0) {
                hrs = 12;
            } else if (hours == 12) {
                hrs = 12;
                pref = "PM";
            } else if (hours > 12) {
                pref = "PM";
                hrs = hours - 12;
            } else
            {
                hrs = hours;
            }
            return String.format("%2d:%02d %s", hrs, minutes, pref);
        }
    }

    @Override
    public int compareTo(Time o) {
        return Integer.compare(value(), o.value());
    }
}

class TimeTable {
    List<Time> times;

    public TimeTable() {
        this.times = new ArrayList<>();
    }


    public void readTimes(InputStream in) throws UnsupportedFormatException, InvalidTimeException {
        Scanner sc = new Scanner(in);
        while (sc.hasNext()) {
            String line = sc.next();
            if (line.contains(".") || line.contains(":")) {
                String[] lp;
                if (line.contains(".")) {
                    lp = line.split("\\.");
                } else {
                    lp = line.split(":");
                }

                int hrs = Integer.parseInt(lp[0]);
                int min = Integer.parseInt(lp[1]);
                if ((hrs >= 24 || hrs <0) || (min < 0 || min>=60)) throw new InvalidTimeException(line);

                Time t = new Time(hrs, min);
                times.add(t);

            } else throw new UnsupportedFormatException(line);
        }
    }

    public void writeTimes(OutputStream out, TimeFormat timeFormat) {
        times.sort(Comparator.naturalOrder());
        PrintStream pw = new PrintStream(out);

        times.stream().map(t-> t.timeString(timeFormat)).forEach(pw::println);
    }
}

public class TimesTest {

    public static void main(String[] args) {
        TimeTable timeTable = new TimeTable();
        try {
            timeTable.readTimes(System.in);
        } catch (UnsupportedFormatException e) {
            System.out.println("UnsupportedFormatException: " + e.getMessage());
        } catch (InvalidTimeException e) {
            System.out.println("InvalidTimeException: " + e.getMessage());
        }
        System.out.println("24 HOUR FORMAT");
        timeTable.writeTimes(System.out, TimeFormat.FORMAT_24);
        System.out.println("AM/PM FORMAT");
        timeTable.writeTimes(System.out, TimeFormat.FORMAT_AMPM);
    }


}

enum TimeFormat {
    FORMAT_24, FORMAT_AMPM
}