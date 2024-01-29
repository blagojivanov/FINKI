package io.github.biv2101.VezbiVtor;

import java.util.*;
import java.util.stream.IntStream;

class SeatNotAllowedException extends Exception {
    public SeatNotAllowedException() {
    }
}

class SeatTakenException extends Exception {
    public SeatTakenException() {
    }
}

class Sector {

    public static Comparator<Sector> comparator = Comparator.comparing(Sector::freeSeats).thenComparing(Sector::getCode);
    private String code;
    private int seats;
    private Map<Integer, Integer> info;

    public Sector(String code, int seats) {
        this.code = code;
        this.seats = seats;
        info = new HashMap<>();
    }

    @Override
    public boolean equals(Object o) {
        Sector sector = (Sector) o;
        return Objects.equals(code, sector.code);
    }

    public Map<Integer, Integer> getInfo() {
        return info;
    }

    public String getCode() {
        return code;
    }

    public int freeSeats() {
        return seats - info.size();
    }

    @Override
    public String toString() {
        return String.format("%s\t%d/%d\t%.1f%%", code, freeSeats(), seats, info.size() / (float) seats * 100.0);
    }

    @Override
    public int hashCode() {
        return Objects.hash(code, seats, info);
    }
}

class Stadium {
    private String name;
    private Map<String, Sector> sectors;

    public Stadium(String name) {
        this.name = name;
        sectors = new HashMap<>();
    }

    public void createSectors(String[] sectorNames, int[] sizes) {
        IntStream.range(0, sectorNames.length).forEach(i -> sectors.put(sectorNames[i], new Sector(sectorNames[i], sizes[i])));
    }

    public void buyTicket(String sectorName, int seat, int type) throws SeatNotAllowedException, SeatTakenException {
        if (sectors.containsKey(sectorName)) {
            int toContain = (type >= 1 && type != 2) ? 2 : 1;
            if (type == 0) {
                if (sectors.get(sectorName).getInfo().get(seat) != null)
                    throw new SeatTakenException();
                sectors.get(sectorName).getInfo().put(seat, type);
                return;
            }

            if (sectors.get(sectorName).getInfo().get(seat) != null) {
                throw new SeatTakenException();
            }

            if (sectors.get(sectorName).getInfo().containsValue(toContain))
                throw new SeatNotAllowedException();


            sectors.get(sectorName).getInfo().put(seat, type);

        }
    }

    public void showSectors() {
        sectors.values().stream().sorted(Comparator.comparing(Sector::freeSeats)
                .reversed().thenComparing(Sector::getCode)).forEach(System.out::println);
    }
}

public class StaduimTest {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int n = scanner.nextInt();
        scanner.nextLine();
        String[] sectorNames = new String[n];
        int[] sectorSizes = new int[n];
        String name = scanner.nextLine();
        for (int i = 0; i < n; ++i) {
            String line = scanner.nextLine();
            String[] parts = line.split(";");
            sectorNames[i] = parts[0];
            sectorSizes[i] = Integer.parseInt(parts[1]);
        }
        Stadium stadium = new Stadium(name);
        stadium.createSectors(sectorNames, sectorSizes);
        n = scanner.nextInt();
        scanner.nextLine();
        for (int i = 0; i < n; ++i) {
            String line = scanner.nextLine();
            String[] parts = line.split(";");
            try {
                stadium.buyTicket(parts[0], Integer.parseInt(parts[1]),
                        Integer.parseInt(parts[2]));
            } catch (SeatNotAllowedException e) {
                System.out.println("SeatNotAllowedException");
            } catch (SeatTakenException e) {
                System.out.println("SeatTakenException");
            }
        }
        stadium.showSectors();
    }
}
