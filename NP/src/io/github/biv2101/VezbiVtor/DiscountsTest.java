package io.github.biv2101.VezbiVtor;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.*;
import java.util.stream.Collectors;

/**
 * Discounts
 */

class Product {
    private int discounted, original;

    public Product(String part) {
        String[] p = part.split(":");
        this.discounted = Integer.parseInt(p[0]);
        this.original = Integer.parseInt(p[1]);
    }

    public int getDiscount() {
        return (int) (((double) 1 - ((double) discounted / original)) * 100);
    }

    public int absoluteDiscount() {
        return original - discounted;
    }

    @Override
    public String toString() {
        return String.format("\n%2d%% %d/%d", getDiscount(), discounted, original);
    }
}

class Store {
    private List<Product> products;
    private String name;

    public Store(String line) {
        String[] parts = line.split("\\s+");
        name = parts[0];
        products = Arrays.stream(parts).skip(1).map(Product::new).collect(Collectors.toList());
    }

    public double averageDiscount() {
        return products.stream().mapToDouble(Product::getDiscount).average().orElse(0);
    }

    public int sumAbsolutes() {
        return products.stream().mapToInt(Product::absoluteDiscount).sum();
    }

    public String getName() {
        return name;
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        products.stream().sorted(Comparator.comparing(Product::getDiscount).thenComparing(Product::absoluteDiscount).reversed()).forEach(sb::append);
        return String.format("%s\nAverage discount: %.1f%%\nTotal discount: %d", name, averageDiscount(), sumAbsolutes()) + sb;
    }
}

class Discounts {
    private List<Store> stores;

    public Discounts() {
        stores = new ArrayList<>();
    }

    public int readStores(InputStream is) {
        BufferedReader br = new BufferedReader(new InputStreamReader(is));
        stores = br.lines().map(Store::new).collect(Collectors.toList());
        try {
            br.close();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        return stores.size();
    }

    @Override
    public String toString() {
        return "Discounts{" +
                "stores=" + stores +
                '}';
    }

    public List<Store> byAverageDiscount() {
        return stores.stream().sorted(Comparator.comparing(Store::averageDiscount).thenComparing(Store::getName).reversed()).limit(3).collect(Collectors.toList());
    }

    public List<Store> byTotalDiscount() {
        return stores.stream().sorted(Comparator.comparing(Store::sumAbsolutes).thenComparing(Store::getName)).limit(3).collect(Collectors.toList());
    }
}

public class DiscountsTest {
    public static void main(String[] args) {
        Discounts discounts = new Discounts();
        int stores = discounts.readStores(System.in);
        System.out.println("Stores read: " + stores);
        System.out.println("=== By average discount ===");
        discounts.byAverageDiscount().forEach(System.out::println);
        System.out.println("=== By total discount ===");
        discounts.byTotalDiscount().forEach(System.out::println);
    }
}

// Vashiot kod ovde