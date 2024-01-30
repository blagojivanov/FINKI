package io.github.biv2101.VezbiVtor;

import java.util.*;

class BlockContainer<T extends Comparable<T>> {
    Map<Integer, SortedSet<T>> map;
    int numblocks;
    int blockcap;

    public Comparator<T> comparator = new Comparator<T>() {
        @Override
        public int compare(T o1, T o2) {
            return compare(o1, o2);
        }
    };

    public BlockContainer(int n) {
        map = new HashMap<>();
        numblocks = 0;
        blockcap = n;
    }

    public void add(T a) {
        if (map.get(numblocks) != null) {
            if (map.get(numblocks).size() < blockcap) {
                map.get(numblocks).add(a);
            } else {
                map.computeIfAbsent(++numblocks, x -> new TreeSet<>()).add(a);
            }
            return;
        }
        map.computeIfAbsent(numblocks, x -> new TreeSet<>()).add(a);
    }

    public void remove(T a) {
        map.get(numblocks).remove(a);
        if (map.get(numblocks).isEmpty()) {
            map.remove(numblocks);
            numblocks--;
        }
    }

    public void sort() {
        List<T> list = new ArrayList<>();
        map.values().forEach(list::addAll);
        list.sort(Comparator.naturalOrder());
        map.clear();
        numblocks = 0;
        list.stream().forEach(this::add);
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        map.values().forEach(x -> sb.append(x).append(","));

        return sb.substring(0, sb.length() - 1);
    }
}

public class BlockContainerTest {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int n = scanner.nextInt();
        int size = scanner.nextInt();
        BlockContainer<Integer> integerBC = new BlockContainer<Integer>(size);
        scanner.nextLine();
        Integer lastInteger = null;
        for (int i = 0; i < n; ++i) {
            int element = scanner.nextInt();
            lastInteger = element;
            integerBC.add(element);
        }
        System.out.println("+++++ Integer Block Container +++++");
        System.out.println(integerBC);
        System.out.println("+++++ Removing element +++++");
        integerBC.remove(lastInteger);
        System.out.println("+++++ Sorting container +++++");
        integerBC.sort();
        System.out.println(integerBC);
        BlockContainer<String> stringBC = new BlockContainer<String>(size);
        String lastString = null;
        for (int i = 0; i < n; ++i) {
            String element = scanner.next();
            lastString = element;
            stringBC.add(element);
        }
        System.out.println("+++++ String Block Container +++++");
        System.out.println(stringBC);
        System.out.println("+++++ Removing element +++++");
        stringBC.remove(lastString);
        System.out.println("+++++ Sorting container +++++");
        stringBC.sort();
        System.out.println(stringBC);
    }
}

// Вашиот код овде



