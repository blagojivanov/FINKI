package io.github.biv2101.VezbiVtor;

import java.text.CollationElementIterator;
import java.util.*;
import java.util.stream.Collectors;
import java.util.stream.IntStream;
import java.util.stream.Stream;

class Flight {

    private String from;
    private String to;

    private int time;
    private int duration;

    public Flight(String from, String to, int time, int duration) {
        this.from = from;
        this.to = to;
        this.time = time;
        this.duration = duration;
    }

    public String getFrom() {
        return from;
    }

    public String getTo() {
        return to;
    }

    public int getTime() {
        return time;
    }

    public String takeoff() {
        return String.format("%02d:%02d", time / 60, time % 60);
    }

    public String landing() {
        if ((time + duration) / 60 >= 24) {
            return String.format("%02d:%02d", ((time + duration) / 60) - 24, (time + duration) % 60);
        }
        return String.format("%02d:%02d", (time + duration) / 60, (time + duration) % 60);
    }

    public String flightTime() {
        if ((time + duration) / 60 >= 24) {
            return String.format("+1d %dh%02dm", duration / 60, duration % 60);
        }
        return String.format("%dh%02dm", duration / 60, duration % 60);
    }

    public int getDuration() {
        return duration;
    }

    @Override
    public String toString() {
        return String.format("%s-%s %s-%s %s", from, to, takeoff(), landing(), flightTime());
    }


    public static Comparator<Flight> COMPARATOR = Comparator.comparing(Flight::getTo)
            .thenComparing(Flight::getTime).thenComparing(Flight::getDuration);

}

class Airport {

    private SortedSet<Flight> flights;
    private String name;
    private String country;
    private String code;
    private int passengers;

    public Airport(String name, String country, String code, int passengers) {
        this.name = name;
        this.country = country;
        this.code = code;
        this.passengers = passengers;
        flights = new TreeSet<>(Flight.COMPARATOR);
    }

    public SortedSet<Flight> getFlights() {
        return flights;
    }

    public String getName() {
        return name;
    }

    public String getCountry() {
        return country;
    }

    public String getCode() {
        return code;
    }

    public int getPassengers() {
        return passengers;
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        String retstr = String.format("%s (%s)\n%s\n%d", name, code, country, passengers);

        Iterator<Flight> iterator = flights.iterator();
        for (int i = 1; i <= flights.size(); i++) {

            sb.append("\n").append(i).append(". ").append(iterator.next());
        }

        return retstr + sb;
    }
}

class Airports {
    private List<Airport> airports;

    public Airports() {
        airports = new ArrayList<>();
    }

    public void addAirport(String name, String country, String code, int passengers) {
        airports.add(new Airport(name, country, code, passengers));
    }

    public void addFlights(String from, String to, int time, int duration) {

        airports.stream().filter(x -> x.getCode().equals(from)).findFirst().get().getFlights().add(new Flight(from, to, time, duration));
    }

    public void showFlightsFromAirport(String code) {
        System.out.println(airports.stream().filter(x -> x.getCode().equals(code)).findFirst().get());
    }

    public void showDirectFlightsFromTo(String from, String to) {
        Stream<Flight> flightStream = airports.stream().filter(x -> x.getCode().equals(from)).findFirst().get().getFlights().stream().filter(x -> x.getTo().equals(to));
        if (flightStream.findAny().isEmpty()) {
            System.out.println("No flights from " + from + " to " + to);
            return;
        }
        airports.stream().filter(x -> x.getCode().equals(from)).findFirst().get().getFlights().stream().filter(x -> x.getTo().equals(to)).forEach(System.out::println);

    }

    public void showDirectFlightsTo(String to) {
        Comparator<Flight> comparator = Comparator.comparing(Flight::getTime).thenComparing(Flight::getFrom);
        SortedSet<Flight> flightss = new TreeSet<>(comparator);
        for (Airport airport : airports) {
            airport.getFlights().stream().filter(y -> y.getTo().equals(to)).forEach(flightss::add);
        }

        flightss.forEach(System.out::println);
    }

}

public class AirportsTest {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        Airports airports = new Airports();
        int n = scanner.nextInt();
        scanner.nextLine();
        String[] codes = new String[n];
        for (int i = 0; i < n; ++i) {
            String al = scanner.nextLine();
            String[] parts = al.split(";");
            airports.addAirport(parts[0], parts[1], parts[2], Integer.parseInt(parts[3]));
            codes[i] = parts[2];
        }
        int nn = scanner.nextInt();
        scanner.nextLine();
        for (int i = 0; i < nn; ++i) {
            String fl = scanner.nextLine();
            String[] parts = fl.split(";");
            airports.addFlights(parts[0], parts[1], Integer.parseInt(parts[2]), Integer.parseInt(parts[3]));
        }
        int f = scanner.nextInt();
        int t = scanner.nextInt();
        String from = codes[f];
        String to = codes[t];
        System.out.printf("===== FLIGHTS FROM %S =====\n", from);
        airports.showFlightsFromAirport(from);
        System.out.printf("===== DIRECT FLIGHTS FROM %S TO %S =====\n", from, to);
        airports.showDirectFlightsFromTo(from, to);
        t += 5;
        t = t % n;
        to = codes[t];
        System.out.printf("===== DIRECT FLIGHTS TO %S =====\n", to);
        airports.showDirectFlightsTo(to);
    }
}

// vashiot kod ovde


