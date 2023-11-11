package io.github.biv2101.Labs.Lab3;

import javax.swing.border.EmptyBorder;
import java.rmi.server.ExportException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Scanner;
import java.util.stream.IntStream;

interface Item {
    int getPrice();

    String getType();
}

class InvalidExtraTypeException extends Exception {
}

class InvalidPizzaTypeException extends Exception {
}

class ItemOutOfStockException extends Exception {
    public ItemOutOfStockException(Item item) {

    }
}

class ArrayIndexOutOfBoundsException extends Exception {
    public ArrayIndexOutOfBoundsException(int idx) {

    }
}

class OrderLockedException extends Exception {

}

class EmptyOrder extends Exception {

}

class PizzaItem implements Item {

    private String type;

    public PizzaItem(String type) throws InvalidPizzaTypeException {
        if (type.equals("Standard") || type.equals("Pepperoni") || type.equals("Vegetarian")) {
            this.type = type;
        } else {
            throw new InvalidPizzaTypeException();
        }
    }

    @Override
    public String getType() {
        return type;
    }

    @Override
    public int getPrice() {
        return type.equals("Standard") ? 10 : type.equals("Pepperoni") ? 12 : 8;
    }
}

class ExtraItem implements Item {

    private String type;

    public ExtraItem(String type) throws InvalidExtraTypeException {
        if (type.equals("Coke") || type.equals("Ketchup")) {
            this.type = type;
        } else {
            throw new InvalidExtraTypeException();
        }
    }
    @Override
    public String getType() {
        return type;
    }

    @Override
    public int getPrice() {
        return type.equals("Ketchup") ? 3 : 5;
    }

}

class Order {

    private class OrderItem {
        private final Item item;
        private int c;

        public OrderItem(Item item, int c) {
            this.item = item;
            this.c = c;
        }

        public Item getItem() {
            return item;
        }

        public int getC() {
            return c;
        }

        public void setC(int c) {
            this.c = c;
        }

        public int getPrice() {
            return c * item.getPrice();
        }
    }

    // dinamicka alokacija na memorija?
    private List<OrderItem> items = new ArrayList<>();
    private boolean locked;

    public Order() {
        locked = false;
    }

    public void addItem(Item item, int count) throws ItemOutOfStockException, OrderLockedException {
        boolean found = false;
        if (locked) throw new OrderLockedException();
        if (count > 10) throw new ItemOutOfStockException(item);
        else {
            for (int i = 0; i < items.size(); i++) {
                if (items.get(i).getItem().getType().equals(item.getType())) {
                    items.get(i).setC(count);
                    found = true;
                }
            }
            if (!found) {
                items.add(new OrderItem(item, count));
            }
        }
    }

    public void removeItem(int idx) throws ArrayIndexOutOfBoundsException, OrderLockedException {
        if (locked) throw new OrderLockedException();
        if (idx >= items.size()) throw new ArrayIndexOutOfBoundsException(idx);
        else {
            items.remove(idx);
        }
    }

    public void lock() throws EmptyOrder {
        if (items.isEmpty()) throw new EmptyOrder();
        locked = true;
    }

    public int getPrice() {
        // ok?
        return items.stream().mapToInt(OrderItem::getPrice).sum();
    }

    public void displayOrder() {
        IntStream.range(0, items.size()).forEach(i -> {
            OrderItem orderItem = items.get(i);
            System.out.printf("%3d.%-15sx%2d%5d$\n", i + 1, orderItem.getItem().getType(), orderItem.getC(), orderItem.getPrice());
        });
        System.out.printf("%-22s%5d$\n", "Total:", getPrice());
    }

}

public class PizzaOrderTest {

    public static void main(String[] args) {
        Scanner jin = new Scanner(System.in);
        int k = jin.nextInt();
        if (k == 0) { //test Item
            try {
                String type = jin.next();
                String name = jin.next();
                Item item = null;
                if (type.equals("Pizza")) item = new PizzaItem(name);
                else item = new ExtraItem(name);
                System.out.println(item.getPrice());
            } catch (Exception e) {
                System.out.println(e.getClass().getSimpleName());
            }
        }
        if (k == 1) { // test simple order
            Order order = new Order();
            while (true) {
                try {
                    String type = jin.next();
                    String name = jin.next();
                    Item item = null;
                    if (type.equals("Pizza")) item = new PizzaItem(name);
                    else item = new ExtraItem(name);
                    if (!jin.hasNextInt()) break;
                    order.addItem(item, jin.nextInt());
                } catch (Exception e) {
                    System.out.println(e.getClass().getSimpleName());
                }
            }
            jin.next();
            System.out.println(order.getPrice());
            order.displayOrder();
            while (true) {
                try {
                    String type = jin.next();
                    String name = jin.next();
                    Item item = null;
                    if (type.equals("Pizza")) item = new PizzaItem(name);
                    else item = new ExtraItem(name);
                    if (!jin.hasNextInt()) break;
                    order.addItem(item, jin.nextInt());
                } catch (Exception e) {
                    System.out.println(e.getClass().getSimpleName());
                }
            }
            System.out.println(order.getPrice());
            order.displayOrder();
        }
        if (k == 2) { // test order with removing
            Order order = new Order();
            while (true) {
                try {
                    String type = jin.next();
                    String name = jin.next();
                    Item item = null;
                    if (type.equals("Pizza")) item = new PizzaItem(name);
                    else item = new ExtraItem(name);
                    if (!jin.hasNextInt()) break;
                    order.addItem(item, jin.nextInt());
                } catch (Exception e) {
                    System.out.println(e.getClass().getSimpleName());
                }
            }
            jin.next();
            System.out.println(order.getPrice());
            order.displayOrder();
            while (jin.hasNextInt()) {
                try {
                    int idx = jin.nextInt();
                    order.removeItem(idx);
                } catch (Exception e) {
                    System.out.println(e.getClass().getSimpleName());
                }
            }
            System.out.println(order.getPrice());
            order.displayOrder();
        }
        if (k == 3) { //test locking & exceptions
            Order order = new Order();
            try {
                order.lock();
            } catch (Exception e) {
                System.out.println(e.getClass().getSimpleName());
            }
            try {
                order.addItem(new ExtraItem("Coke"), 1);
            } catch (Exception e) {
                System.out.println(e.getClass().getSimpleName());
            }
            try {
                order.lock();
            } catch (Exception e) {
                System.out.println(e.getClass().getSimpleName());
            }
            try {
                order.removeItem(0);
            } catch (Exception e) {
                System.out.println(e.getClass().getSimpleName());
            }
        }
    }

}