package io.github.biv2101.VezbiVtor;

import java.util.*;
import java.util.stream.Collectors;

class Names {
    Map<String, Integer> names;
    static Comparator<Map.Entry<String, Integer>> comparator = Comparator.comparing(Map.Entry::getKey);


    public Names() {
        names = new HashMap<>();
    }

    public void addName(String name) {
        names.putIfAbsent(name, 0);
        names.put(name, names.get(name) + 1);
    }

    public void printN(int n) {
        names.entrySet().stream().filter(x -> x.getValue() >= n).sorted(comparator).forEach(x -> System.out.printf("%s (%d) %d\n", x.getKey(), x.getValue(),
                (long) x.getKey().toLowerCase().chars().mapToObj(String::valueOf).collect(Collectors.toSet()).size()));
    }

    public String findName(int len, int x) {
        List<String> sorted = names.keySet().stream().filter(str -> str.length() < len).sorted(String::compareToIgnoreCase).collect(Collectors.toList());
        if (sorted.size() > x) {
            return sorted.get(x);
        } else {
            return sorted.get(x % sorted.size());
        }
    }
}

public class NamesTest {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int n = scanner.nextInt();
        scanner.nextLine();
        Names names = new Names();
        for (int i = 0; i < n; ++i) {
            String name = scanner.nextLine();
            names.addName(name);
        }
        n = scanner.nextInt();
        System.out.printf("===== PRINT NAMES APPEARING AT LEAST %d TIMES =====\n", n);
        names.printN(n);
        System.out.println("===== FIND NAME =====");
        int len = scanner.nextInt();
        int index = scanner.nextInt();
        System.out.println(names.findName(len, index));
        scanner.close();

    }
}

// vashiot kod ovde