package io.github.biv2101.VezbiVtor;

import java.util.*;

/*
YOUR CODE HERE
DO NOT MODIFY THE interfaces and classes below!!!
*/

interface Location {
    int getX();

    int getY();

    default int distance(Location other) {
        int xDiff = Math.abs(getX() - other.getX());
        int yDiff = Math.abs(getY() - other.getY());
        return xDiff + yDiff;
    }
}

class LocationCreator {
    public static Location create(int x, int y) {

        return new Location() {
            @Override
            public int getX() {
                return x;
            }

            @Override
            public int getY() {
                return y;
            }
        };
    }
}

//TODO: cleanup and refactor
class DeliveryPerson {
    private String id;
    private String name;
    private Location location;

    public int numorders;
    public double sum;

    public int getNumorders() {
        return numorders;
    }

    public double getSum() {
        return sum;
    }

    public Location getLocation() {
        return location;
    }

    public DeliveryPerson(String id, String name, Location location) {
        this.id = id;
        this.name = name;
        this.location = location;
        numorders = 0;
        sum = 0;
    }

    public String getName() {
        return name;
    }
    public void setLocation(Location location) {
        this.location = location;
    }

    @Override
    public String toString() {
        double last = 0;
        if (numorders != 0) {
            last = sum / numorders;
        }
        return String.format("ID: %s Name: %s Total deliveries: %d Total delivery fee: %.2f Average delivery fee: %.2f", id, name, numorders, sum, last);
    }
}

class AppUser {
    private String id;
    private String name;
    private List<Double> orders;
    private Map<String, Location> addresses;

    public AppUser(String id, String name) {
        this.id = id;
        this.name = name;
        addresses = new HashMap<>();
        orders = new ArrayList<>();
    }

    public Map<String, Location> getAddresses() {
        return addresses;
    }

    public String getName() {
        return name;
    }

    public void addOrder(double cost) {
        orders.add(cost);
    }

    public double spent() {
        return orders.stream().mapToDouble(x -> x).sum();
    }

    public double avg() {
        return orders.stream().mapToDouble(x -> x).average().orElse(0);
    }

    //ID: 1 Name: stefan Total orders: 1 Total amount spent: 450.00 Average amount spent: 450.00


    @Override
    public String toString() {
        return String.format("ID: %s Name: %s Total orders: %d Total amount spent: %.2f Average amount spent: %.2f", id, name, orders.size(), spent(), avg());
    }
}

class Restaurant {
    private String id;
    private String name;
    private Location location;

    private List<Double> orders;

    public Location getLocation() {
        return location;
    }

    public Restaurant(String id, String name, Location location) {
        this.id = id;
        this.name = name;
        this.location = location;
        orders = new ArrayList<>();
    }

    public String getName() {
        return name;
    }

    public void addOrder(double cost) {
        orders.add(cost);
    }

    public double earned() {
        return orders.stream().mapToDouble(x -> x).sum();
    }

    public double avg() {
        return orders.stream().mapToDouble(x -> x).average().orElse(0);
    }

    @Override
    public String toString() {
        return String.format("ID: %s Name: %s Total orders: %d Total amount earned: %.2f Average amount earned: %.2f", id, name, orders.size(), earned(), avg());
    }

}

class DeliveryApp {
    private String name;
    private Map<String, DeliveryPerson> couriers;
    private Map<String, AppUser> users;
    private Map<String, Restaurant> restaurants;

    public DeliveryApp(String name) {
        this.name = name;
        couriers = new TreeMap<>();
        users = new TreeMap<>();
        restaurants = new TreeMap<>();
    }

    public void registerDeliveryPerson(String id, String name, Location currentLocation) {
        couriers.put(id, new DeliveryPerson(id, name, currentLocation));
    }

    public void addRestaurant(String id, String name, Location location) {
        restaurants.put(id, new Restaurant(id, name, location));

    }

    public void addUser(String id, String name) {
        users.put(id, new AppUser(id, name));
    }

    public void addAddress(String id, String addressName, Location location) {
        users.get(id).getAddresses().put(addressName, location);
    }

    public void orderFood(String userId, String userAddressName, String restaurantId, float cost) {

        Location resLoc = restaurants.get(restaurantId).getLocation();
        Location userLoc = users.get(userId).getAddresses().get(userAddressName);

        DeliveryPerson deliveryPerson = couriers.values().stream().sorted(Comparator.comparing((DeliveryPerson p) -> p.getLocation().distance(resLoc))
                .thenComparing(DeliveryPerson::getNumorders)).findFirst().get();
        deliveryPerson.numorders++;
        deliveryPerson.sum += 90 + ((int)(resLoc.distance(deliveryPerson.getLocation()) / 10.0) * 10);
        deliveryPerson.setLocation(userLoc);

        restaurants.get(restaurantId).addOrder(cost);

        users.get(userId).addOrder(cost);
    }

    public void printUsers() {
        users.values().stream().sorted(Comparator.comparing(AppUser::spent).thenComparing(AppUser::getName).reversed()).forEach(System.out::println);
    }

    public void printDeliveryPeople() {
        couriers.values().stream().sorted(Comparator.comparing(DeliveryPerson::getSum).thenComparing(DeliveryPerson::getNumorders).thenComparing(DeliveryPerson::getName).reversed()).forEach(System.out::println);
    }

    public void printRestaurants() {
        restaurants.values().stream().sorted(Comparator.comparing(Restaurant::avg).thenComparing(Restaurant::getName).reversed()).forEach(System.out::println);
    }

}

public class DeliveryAppTester {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String appName = sc.nextLine();
        DeliveryApp app = new DeliveryApp(appName);
        while (sc.hasNextLine()) {
            String line = sc.nextLine();
            String[] parts = line.split(" ");

            if (parts[0].equals("addUser")) {
                String id = parts[1];
                String name = parts[2];
                app.addUser(id, name);
            } else if (parts[0].equals("registerDeliveryPerson")) {
                String id = parts[1];
                String name = parts[2];
                int x = Integer.parseInt(parts[3]);
                int y = Integer.parseInt(parts[4]);
                app.registerDeliveryPerson(id, name, LocationCreator.create(x, y));
            } else if (parts[0].equals("addRestaurant")) {
                String id = parts[1];
                String name = parts[2];
                int x = Integer.parseInt(parts[3]);
                int y = Integer.parseInt(parts[4]);
                app.addRestaurant(id, name, LocationCreator.create(x, y));
            } else if (parts[0].equals("addAddress")) {
                String id = parts[1];
                String name = parts[2];
                int x = Integer.parseInt(parts[3]);
                int y = Integer.parseInt(parts[4]);
                app.addAddress(id, name, LocationCreator.create(x, y));
            } else if (parts[0].equals("orderFood")) {
                String userId = parts[1];
                String userAddressName = parts[2];
                String restaurantId = parts[3];
                float cost = Float.parseFloat(parts[4]);
                app.orderFood(userId, userAddressName, restaurantId, cost);
            } else if (parts[0].equals("printUsers")) {
                app.printUsers();
            } else if (parts[0].equals("printRestaurants")) {
                app.printRestaurants();
            } else {
                app.printDeliveryPeople();
            }

        }
    }
}
