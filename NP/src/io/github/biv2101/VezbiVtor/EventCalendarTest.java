package io.github.biv2101.VezbiVtor;

import java.text.DateFormat;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.*;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

class WrongDateException extends Exception {

    public WrongDateException(String message) {
        super(message);
    }
}

class Eventt {
    private String name;
    private String location;
    private Date time;

    public Eventt(String name, String location, Date time) {
        this.name = name;
        this.location = location;
        this.time = time;

    }


    public String getName() {
        return name;
    }

    public Date getTime() {
        return time;
    }

    public int getMonth() {
        Calendar c = Calendar.getInstance();
        c.setTime(time);
        return c.get(Calendar.MONTH);
    }

    public static Comparator<Eventt> comparator = Comparator.comparing(Eventt::getTime).thenComparing(Eventt::getName);

    @Override
    public String toString() {
        DateFormat dateFormat = new SimpleDateFormat("dd MMM, yyyy HH:mm");

        return String.format("%s at %s, %s", dateFormat.format(time), location, name);
    }
}

class EventCalendar {

    private int year;
    private Map<Date, SortedSet<Eventt>> events;

    public EventCalendar(int year) {
        this.year = year;
        events = new HashMap<>();
    }

    public void addEvent(String name, String location, Date date) throws WrongDateException {
        Calendar c = Calendar.getInstance();
        c.setTime(date);
        Calendar cal = Calendar.getInstance();
        cal.setTime(date);
        cal.set(Calendar.HOUR_OF_DAY, 0);
        cal.set(Calendar.MINUTE, 0);
        cal.set(Calendar.SECOND, 0);
        cal.set(Calendar.MILLISECOND, 0);
        Date datewt = cal.getTime();
        if (year == c.get(Calendar.YEAR))
            events.computeIfAbsent(datewt, x -> new TreeSet<>(Eventt.comparator)).add(new Eventt(name, location, date));
        else throw new WrongDateException("Wrong date: " + date);
    }

    public void listEvents(Date date) {
        Calendar cal = Calendar.getInstance();
        cal.setTime(date);
        cal.set(Calendar.HOUR_OF_DAY, 0);
        cal.set(Calendar.MINUTE, 0);
        cal.set(Calendar.SECOND, 0);
        cal.set(Calendar.MILLISECOND, 0);
        Date datewt = cal.getTime();
        if (events.get(datewt) == null) {
            System.out.println("No events on this day!");
        } else {
            events.get(datewt).stream().forEach(System.out::println);
        }
    }

    public void listByMonth() {
        List<SortedSet<Eventt>> setList = events.values().stream().collect(Collectors.toList());
        List<Eventt> eventts = new ArrayList<>();
        setList.forEach(eventts::addAll);
        IntStream.range(0, 12).forEach(i -> System.out.printf("%d : %d\n", i + 1, eventts.stream().filter(x -> x.getMonth() == i).count()));
    }


}

public class EventCalendarTest {
    public static void main(String[] args) throws ParseException {
        Scanner scanner = new Scanner(System.in);
        int n = scanner.nextInt();
        scanner.nextLine();
        int year = scanner.nextInt();
        scanner.nextLine();
        EventCalendar eventCalendar = new EventCalendar(year);
        DateFormat df = new SimpleDateFormat("dd.MM.yyyy HH:mm");
        for (int i = 0; i < n; ++i) {
            String line = scanner.nextLine();
            String[] parts = line.split(";");
            String name = parts[0];
            String location = parts[1];
            Date date = df.parse(parts[2]);
            try {
                eventCalendar.addEvent(name, location, date);
            } catch (WrongDateException e) {
                System.out.println(e.getMessage());
            }
        }
        Date date = df.parse(scanner.nextLine());
        eventCalendar.listEvents(date);
        eventCalendar.listByMonth();
    }
}

// vashiot kod ovde