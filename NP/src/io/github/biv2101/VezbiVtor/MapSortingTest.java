package io.github.biv2101.VezbiVtor;

import java.util.*;
import java.util.stream.Collectors;


import java.util.*;

public class MapSortingTest {

    static <K, V extends Comparable<V>> SortedSet<Map.Entry<K, V>> entriesSortedByValues(Map<K, V> map) {
        Comparator<Map.Entry<K, V>> comparator = (o1, o2) -> {
            int result = o2.getValue().compareTo(o1.getValue());
            if (result == 0) {
                result = 1;
            }
            return result;
        };
        SortedSet<Map.Entry<K, V>> resultSet = new TreeSet<>(comparator);
        System.out.println(map);
        resultSet.addAll(map.entrySet());
        return resultSet;
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int n = scanner.nextInt();
        scanner.nextLine();
        List<String> l = readMapPairs(scanner);
        if (n == 1) {
            Map<String, Integer> map = new HashMap<>();
            fillStringIntegerMap(l, map);
            SortedSet<Map.Entry<String, Integer>> s = entriesSortedByValues(map);
            System.out.println(s);
        } else {
            Map<Integer, String> map = new HashMap<>();
            fillIntegerStringMap(l, map);
            SortedSet<Map.Entry<Integer, String>> s = entriesSortedByValues(map);
            System.out.println(s);
        }

    }

    private static List<String> readMapPairs(Scanner scanner) {
        String line = scanner.nextLine();
        String[] entries = line.split("\\s+");
        return Arrays.asList(entries);
    }

    static void fillStringIntegerMap(List<String> l, Map<String, Integer> map) {
        l.stream()
                .forEach(s -> map.put(s.substring(0, s.indexOf(':')), Integer.parseInt(s.substring(s.indexOf(':') + 1))));
    }

    static void fillIntegerStringMap(List<String> l, Map<Integer, String> map) {
        l.stream()
                .forEach(s -> map.put(Integer.parseInt(s.substring(0, s.indexOf(':'))), s.substring(s.indexOf(':') + 1)));
    }

    //вашиот код овде
}