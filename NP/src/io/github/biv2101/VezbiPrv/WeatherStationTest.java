package io.github.biv2101.VezbiPrv;

import java.text.DateFormat;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.*;
import java.util.stream.Collectors;

class Measurement implements Comparable<Measurement> {
    private final float temperature;
    private final float wind;
    private final float humidity;
    private final float visibility;
    private final Date date;

    public Measurement(float temperature, float wind, float humidity, float visibility, Date date) {
        this.temperature = temperature;
        this.wind = wind;
        this.humidity = humidity;
        this.visibility = visibility;
        this.date = date;
    }

    public Date getDate() {
        return date;
    }

    public float getTemperature() {
        return temperature;
    }

    @Override
    public String toString() {
        //temp winds     hum   vis      date
        //22.1 18.9 km/h 1.3% 24.6 km Tue Dec 17 23:30:15 GMT 2013
        return temperature + " " + wind + " km/h " + humidity + "% " + visibility + " km " + date.toString().replace("UTC", "GMT");
    }

    @Override
    public int compareTo(Measurement o) {
        return date.compareTo(o.date);
    }
}

class WeatherStation {

    private final List<Measurement> measurements;
    private final int x;

    public WeatherStation(int x) {
        this.x = x;
        this.measurements = new ArrayList<>();
    }

    public void addMeasurment(float temp, float wind, float hum, float vis, Date date) {
        if (measurements.isEmpty()) {
            measurements.add(new Measurement(temp, wind, hum, vis, date));
            return;
        }
        for (int i = 0; i < measurements.size(); i++) {
            if (Math.abs(measurements.get(i).getDate().getTime() - date.getTime()) < 150 * 1000) {
                return;
            }
        }
        measurements.add(new Measurement(temp, wind, hum, vis, date));
        measurements.stream().sorted();
        for (int i = 0; i<measurements.size(); i++) {
            if (date.getTime() - measurements.get(i).getDate().getTime() >= (int) x * 86400 * 1000)
            {
                measurements.remove(i);
            }
        }
    }

    public void status(Date from, Date to) {
        List<Measurement> collect = measurements.stream().filter(m -> m.getDate().compareTo(from) >= 0 && m.getDate().compareTo(to) <=0).sorted().collect(Collectors.toList());
        if (collect.isEmpty()) throw new RuntimeException();
        collect.forEach(System.out::println);
        System.out.printf("Average temperature: %.2f", collect.stream().mapToDouble(Measurement::getTemperature).average().getAsDouble());
    }

    public int total() {
        return measurements.size();
    }
}


public class WeatherStationTest {
    public static void main(String[] args) throws ParseException {
        Scanner scanner = new Scanner(System.in);
        DateFormat df = new SimpleDateFormat("dd.MM.yyyy HH:mm:ss");
        int n = scanner.nextInt();
        scanner.nextLine();
        WeatherStation ws = new WeatherStation(n);
        while (true) {
            String line = scanner.nextLine();
            if (line.equals("=====")) {
                break;
            }
            String[] parts = line.split(" ");
            float temp = Float.parseFloat(parts[0]);
            float wind = Float.parseFloat(parts[1]);
            float hum = Float.parseFloat(parts[2]);
            float vis = Float.parseFloat(parts[3]);
            line = scanner.nextLine();
            Date date = df.parse(line);
            ws.addMeasurment(temp, wind, hum, vis, date);
        }
        String line = scanner.nextLine();
        Date from = df.parse(line);
        line = scanner.nextLine();
        Date to = df.parse(line);
        scanner.close();
        System.out.println(ws.total());
        try {
            ws.status(from, to);
        } catch (RuntimeException e) {
            System.out.println(e);
        }
    }
}

// vashiot kod ovde