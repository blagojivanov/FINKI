package io.github.biv2101.VezbiPrv;

import java.io.OutputStream;
import java.io.PrintStream;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;
import java.util.stream.Collectors;
import java.util.stream.Stream;

class InvalidOperationException extends Exception {
    public InvalidOperationException(String message) {
        super(message);
    }
}

abstract class Item implements Comparable<Item> {

    protected int id;
    protected String name;
    protected double productPrice;

    public Item(int id, String name, double productPrice) {
        this.id = id;
        this.name = name;
        this.productPrice = productPrice;
    }

    public void setProductPrice(double productPrice) {
        this.productPrice = productPrice;
    }

    public abstract double price();

    @Override
    public int compareTo(Item o) {
        return Double.compare(o.price(), price());
    }

    @Override
    public String toString() {
        return String.format("%d - %.2f", id, price());
    }
}

class WSItem extends Item {
    private int quantity;

    public WSItem(int id, String name, int productPrice, int quantity) {
        super(id, name, productPrice);
        this.quantity = quantity;
    }

    @Override
    public double price() {
        return quantity * productPrice;
    }
}

class PSItem extends Item {
    private double quantity;

    public PSItem(int id, String name, int productPrice, double quantity) {
        super(id, name, productPrice);
        this.quantity = quantity;
    }

    @Override
    public double price() {
        return (quantity / 1000) * productPrice;
    }
}

class ShoppingCart {
    private List<Item> items;

    public ShoppingCart() {
        this.items = new ArrayList<>();
    }

    //      0   1           2           3           4
//    PSWS;productID;productName;productPrice;quantity
    public void addItem(String line) throws InvalidOperationException {
        String[] lp = line.split(";");
        if (Double.parseDouble(lp[4]) == 0)
            throw new InvalidOperationException("The quantity of the product with id " + lp[1] + " can not be 0.");
        if (lp[0].equals("WS")) {
            items.add(new WSItem(Integer.parseInt(lp[1]), lp[2], Integer.parseInt(lp[3]), Integer.parseInt(lp[4])));
        } else {
            items.add(new PSItem(Integer.parseInt(lp[1]), lp[2], Integer.parseInt(lp[3]), Double.parseDouble(lp[4])));
        }
    }

    public void printShoppingCart(OutputStream os) {
        PrintStream ps = new PrintStream(os);
        items.stream().sorted().forEach(ps::println);
    }

    public void blackFridayOffer(List<Integer> discountItems, OutputStream os) throws InvalidOperationException {
        PrintStream ps = new PrintStream(os);
        if (discountItems.isEmpty()) {
            throw new InvalidOperationException("There are no products with discount.");
        }
        List<Item> collect = items.stream().filter(item -> discountItems.contains(item.id)).collect(Collectors.toList());

        collect.forEach(i -> i.setProductPrice((i.productPrice - i.productPrice * 0.9)));
        collect.forEach(ps::println);

    }
}

public class ShoppingTest {

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        ShoppingCart cart = new ShoppingCart();

        int items = Integer.parseInt(sc.nextLine());
        for (int i = 0; i < items; i++) {
            try {
                cart.addItem(sc.nextLine());
            } catch (InvalidOperationException e) {
                System.out.println(e.getMessage());
            }
        }

        List<Integer> discountItems = new ArrayList<>();
        int discountItemsCount = Integer.parseInt(sc.nextLine());
        for (int i = 0; i < discountItemsCount; i++) {
            discountItems.add(Integer.parseInt(sc.nextLine()));
        }

        int testCase = Integer.parseInt(sc.nextLine());
        if (testCase == 1) {
            cart.printShoppingCart(System.out);
        } else if (testCase == 2) {
            try {
                cart.blackFridayOffer(discountItems, System.out);
            } catch (InvalidOperationException e) {
                System.out.println(e.getMessage());
            }
        } else {
            System.out.println("Invalid test case");
        }
    }
}