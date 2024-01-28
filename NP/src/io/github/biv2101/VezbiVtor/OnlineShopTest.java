package io.github.biv2101.VezbiVtor;

import java.time.LocalDateTime;
import java.time.chrono.ChronoLocalDateTime;
import java.util.*;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

enum COMPARATOR_TYPE {
    NEWEST_FIRST,
    OLDEST_FIRST,
    LOWEST_PRICE_FIRST,
    HIGHEST_PRICE_FIRST,
    MOST_SOLD_FIRST,
    LEAST_SOLD_FIRST
}

class ProductNotFoundException extends Exception {
    ProductNotFoundException(String message) {
        super(message);
    }
}


class Product {

    private String id;
    private String name;
    private LocalDateTime createdAt;
    private double price;
    public int quantitySold;
    private String category;

    public Product(String id, String name, LocalDateTime createdAt, double price, int quantitySold, String category) {
        this.id = id;
        this.name = name;
        this.createdAt = createdAt;
        this.price = price;
        this.quantitySold = quantitySold;
        this.category = category;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Product product = (Product) o;
        return Objects.equals(id, product.id);
    }

    @Override
    public int hashCode() {
        return Objects.hash(id);
    }

    public double getPrice() {
        return price;
    }

    public LocalDateTime getCreatedAt() {
        return createdAt;
    }

    public String getCategory() {
        return category;
    }
    @Override
    public String toString() {
        return "Product{" +
                "id='" + id + '\'' +
                ", name='" + name + '\'' +
                ", createdAt=" + createdAt +
                ", price=" + price +
                ", quantitySold=" + quantitySold +
                '}';
    }
}


class OnlineShop {

    private Map<String, Product> products;

    public OnlineShop() {
        products = new HashMap<>();
    }

    void addProduct(String category, String id, String name, LocalDateTime createdAt, double price) {
        products.put(id, new Product(id, name, createdAt, price, 0, category));
    }

    double buyProduct(String id, int quantity) throws ProductNotFoundException {

        if (!products.containsKey(id)) {
            throw new ProductNotFoundException("Product with id " + id + " does not exist in the online shop!");
        } else {
            products.get(id).quantitySold += quantity;
        }
        return quantity * products.get(id).getPrice();
    }

    List<List<Product>> listProducts(String category, COMPARATOR_TYPE comparatorType, int pageSize) {
        List<List<Product>> result = new ArrayList<>();
        Comparator<Product> comparator = new Comparator<Product>() {
            @Override
            public int compare(Product o1, Product o2) {
                if (comparatorType == COMPARATOR_TYPE.HIGHEST_PRICE_FIRST) {
                    return Double.compare(o2.getPrice(), o1.getPrice());
                } else if (comparatorType == COMPARATOR_TYPE.LOWEST_PRICE_FIRST) {
                    return Double.compare(o1.getPrice(), o2.getPrice());
                } else if (comparatorType == COMPARATOR_TYPE.MOST_SOLD_FIRST) {
                    return Integer.compare(o2.quantitySold, o1.quantitySold);
                } else if (comparatorType == COMPARATOR_TYPE.LEAST_SOLD_FIRST) {
                    return Integer.compare(o1.quantitySold, o2.quantitySold);
                } else if (comparatorType == COMPARATOR_TYPE.NEWEST_FIRST) {
                    return o2.getCreatedAt().compareTo(o1.getCreatedAt());
                } else if (comparatorType == COMPARATOR_TYPE.OLDEST_FIRST) {
                    return o1.getCreatedAt().compareTo(o2.getCreatedAt());
                }
                return 0;
            }
        };
        if (category != null) {
            for (int i = 0; i < products.size(); i += pageSize) {
                List<Product> prod = products.values().stream().filter(x -> x.getCategory().equals(category)).sorted(comparator).skip(i).limit(pageSize).collect(Collectors.toList());
                if (prod.isEmpty()) {
                    break;
                }
                result.add(prod);
            }
        } else {
            for (int i = 0; i < products.size(); i += pageSize) {
                result.add(products.values().stream().sorted(comparator).skip(i).limit(pageSize).collect(Collectors.toList()));
            }
        }
        return result;
    }

}

public class OnlineShopTest {

    public static void main(String[] args) {
        OnlineShop onlineShop = new OnlineShop();
        double totalAmount = 0.0;
        Scanner sc = new Scanner(System.in);
        String line;
        while (sc.hasNextLine()) {
            line = sc.nextLine();
            String[] parts = line.split("\\s+");
            if (parts[0].equalsIgnoreCase("addproduct")) {
                String category = parts[1];
                String id = parts[2];
                String name = parts[3];
                LocalDateTime createdAt = LocalDateTime.parse(parts[4]);
                double price = Double.parseDouble(parts[5]);
                onlineShop.addProduct(category, id, name, createdAt, price);
            } else if (parts[0].equalsIgnoreCase("buyproduct")) {
                String id = parts[1];
                int quantity = Integer.parseInt(parts[2]);
                try {
                    totalAmount += onlineShop.buyProduct(id, quantity);
                } catch (ProductNotFoundException e) {
                    System.out.println(e.getMessage());
                }
            } else {
                String category = parts[1];
                if (category.equalsIgnoreCase("null"))
                    category = null;
                String comparatorString = parts[2];
                int pageSize = Integer.parseInt(parts[3]);
                COMPARATOR_TYPE comparatorType = COMPARATOR_TYPE.valueOf(comparatorString);
                printPages(onlineShop.listProducts(category, comparatorType, pageSize));
            }
        }
        System.out.println("Total revenue of the online shop is: " + totalAmount);

    }

    private static void printPages(List<List<Product>> listProducts) {
        for (int i = 0; i < listProducts.size(); i++) {
            System.out.println("PAGE " + (i + 1));
            listProducts.get(i).forEach(System.out::println);
        }
    }
}

