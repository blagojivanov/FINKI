package io.github.biv2101.VezbiVtor;

import java.time.Duration;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.*;
import java.util.stream.Collectors;

class DateUtil {
    public static long durationBetween(LocalDateTime start, LocalDateTime end) {
        return Duration.between(start, end).toMinutes();
    }
}

class ParkingSpot {
    String spotId;
    String registration;
    boolean isParked;
    LocalDateTime timeStamp;
    LocalDateTime endtimeStamp;

    public ParkingSpot(String spotId, String registration, LocalDateTime timeStamp, boolean isParked) {
        this.spotId = spotId;
        this.registration = registration;
        this.isParked = isParked;
        this.timeStamp = timeStamp;
    }

    public void setEndtimeStamp(LocalDateTime endtimeStamp) {
        this.endtimeStamp = endtimeStamp;
    }

    public int getMinutes() {
        return (int) DateUtil.durationBetween(timeStamp, endtimeStamp);
    }

    //Registration number: NE0002AA Spot: A4 Start timestamp: 2024-01-15T21:11:32
    @Override
    public String toString() {
        return String.format("Registration number: %s Spot: %s Start timestamp: %s", registration, spotId, timeStamp);
    }

    public String getRegistration() {
        return registration;
    }

    public String getSpotId() {
        return spotId;
    }

    public LocalDateTime getTimestamp() {
        return timeStamp;
    }
}


class Parking {

    int capacity;
    Map<String, ParkingSpot> spots;
    List<ParkingSpot> spotHistory;


    public Parking(int capacity) {
        this.capacity = capacity;
        spots = new TreeMap<>();
        spotHistory = new ArrayList<>();
    }

    void update(String registration, String spot, LocalDateTime timestamp, boolean entry) {
        if (entry) {
            ParkingSpot parkingSpot = new ParkingSpot(spot, registration, timestamp, true);
            spots.put(spot, parkingSpot);
            spotHistory.add(parkingSpot);
        } else {
            spots.get(spot).setEndtimeStamp(timestamp);
            spots.get(spot).isParked = false;
            spots.remove(spot);
        }
    }

    void currentState() {
        System.out.printf("Capacity filled: %.2f%%\n", ((double) spots.size() / capacity) * 100);
        spots.values().stream().sorted(Comparator.comparing(ParkingSpot::getTimestamp).thenComparing(ParkingSpot::getSpotId).reversed()).forEach(System.out::println);
    }

    void history() {
        spotHistory.stream().filter(x -> !x.isParked).sorted(Comparator.comparing(ParkingSpot::getMinutes).thenComparing(ParkingSpot::getSpotId).reversed())
                .forEach(x -> System.out.println(x + " End timestamp: " + x.endtimeStamp + " Duration in minutes: " + x.getMinutes()));
    }

    Map<String, Long> carStatistics() {
        return spotHistory.stream().collect(Collectors.groupingBy(x -> x.registration, TreeMap::new, Collectors.counting()));
    }

    Map<String, Double> spotOccupancy(LocalDateTime start, LocalDateTime end) {
        int intervalDuration = (int) DateUtil.durationBetween(start, end);
        Map<String, Double> returnMap = new TreeMap<>();
        // starttime e pred pochetoko -> x.getMinutes() - DateUtil.durationBetween(startTimeStamp, start)
        // endtime e posle krajo na intervalo -> DateUtil.durationBetween(end, endTimeStamp)
        spotHistory.stream().forEach(x -> returnMap.compute(x.spotId,
                (k, v) -> (v == null) ?
                        ((((double) x.getMinutes()) - Math.max(0, DateUtil.durationBetween(x.timeStamp, start)) - Math.max(0, DateUtil.durationBetween(end, x.endtimeStamp))) / intervalDuration) * 100
                        : v + ((((double) x.getMinutes()) - Math.max(0, DateUtil.durationBetween(x.timeStamp, start)) - Math.max(0, DateUtil.durationBetween(end, x.endtimeStamp))) / intervalDuration) * 100));
        return returnMap;
    }
}

public class ParkingTesting {

    public static <K, V extends Comparable<V>> void printMapSortedByValue(Map<K, V> map) {
        map.entrySet().stream()
                .sorted(Map.Entry.comparingByValue(Comparator.reverseOrder()))
                .forEach(entry -> System.out.println(String.format("%s -> %s", entry.getKey().toString(), entry.getValue().toString())));

    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int capacity = Integer.parseInt(sc.nextLine());

        Parking parking = new Parking(capacity);

        while (sc.hasNextLine()) {
            String line = sc.nextLine();
            String[] parts = line.split("\\s+");
            if (parts[0].equals("update")) {
                String registration = parts[1];
                String spot = parts[2];
                LocalDateTime timestamp = LocalDateTime.parse(parts[3]);
                boolean entrance = Boolean.parseBoolean(parts[4]);
                parking.update(registration, spot, timestamp, entrance);
            } else if (parts[0].equals("currentState")) {
                System.out.println("PARKING CURRENT STATE");
                parking.currentState();
            } else if (parts[0].equals("history")) {
                System.out.println("PARKING HISTORY");
                parking.history();
            } else if (parts[0].equals("carStatistics")) {
                System.out.println("CAR STATISTICS");
                printMapSortedByValue(parking.carStatistics());
            } else if (parts[0].equals("spotOccupancy")) {
                LocalDateTime start = LocalDateTime.parse(parts[1]);
                LocalDateTime end = LocalDateTime.parse(parts[2]);
                printMapSortedByValue(parking.spotOccupancy(start, end));
            }
        }
    }
}
