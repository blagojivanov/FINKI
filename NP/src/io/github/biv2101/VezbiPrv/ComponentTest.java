package io.github.biv2101.VezbiPrv;

import java.util.ArrayList;
import java.util.List;
import java.util.PriorityQueue;
import java.util.Scanner;

class InvalidPositionException extends Exception {

    private int pos;
    public InvalidPositionException(int pos) {
        this.pos = pos;
    }

    @Override
    public String getMessage() {
        return "Invalid position " + pos + ", alredy taken!";
    }
}

class Component {
    private String color;
    private int weight;
    private List<Component> components;

    private int lev;
    public Component(String color, int weight) {
        this.color = color;
        this.weight = weight;
        this.components = new ArrayList<>();
        this.lev = 1;
    }

    public void setLev(int lev) {
        this.lev = lev;
    }


    public void changeColor(int weight, String color)
    {
        if (this.weight<weight)
        {
            this.color = color;
        }
        components.forEach(c->c.changeColor(weight, color));
    }
    public void addComponent(Component component) {
        component.setLev(lev + 1);
        for (int i = 0; i<components.size(); i++)
        {
            if (component.weight == components.get(i).weight) {
                if (component.color.compareTo(components.get(i).color) < 0)
                {
                    components.add(i, component);
                    return;
                }
            } else {
                if (component.weight < components.get(i).weight)
                {
                    components.add(i, component);
                    return;
                }
            }
        }
        components.add(component);
    }

//    @Override
//    public int compareTo(Component o) {
//        if (weight == o.weight) {
//            return color.compareTo(o.color);
//        } else {
//            return Integer.compare(weight, o.weight);
//        }
//    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder(weight + ":" + color);
        components.forEach(c -> sb.append("\n").append("---".repeat(lev)).append(c));
        return sb.toString();
    }
}

class Window {
    private String name;
    private List<Component> list;

    public Window(String name) {
        this.name = name;
        this.list = new ArrayList<>();
    }

    public void addComponent(int position, Component component) throws InvalidPositionException {
        if (position - 1 >= list.size()) {
            for (int i = list.size(); i < position - 2; i++) {
                list.add(null);
            }
            list.add(component);
        } else if (list.get(position - 1) != null) {
            throw new InvalidPositionException(position);
        } else {
            list.set(position - 1, component);
        }
    }

    public void changeColor(int weight, String color) {
        list.stream().forEach(f->f.changeColor(weight, color));
    }

    public void swichComponents(int pos1, int pos2) {
        Component temp = list.get(pos1 - 1);
        list.set(pos1 - 1, list.get(pos2 - 1));
        list.set(pos2 - 1, temp);
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < list.size(); i++) {
            if (list.get(i) != null) {
                sb.append(i + 1).append(":").append(list.get(i)).append("\n");
            }
        }
        return "WINDOW " + name + "\n" + sb.toString();
    }
}

public class ComponentTest {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        String name = scanner.nextLine();
        Window window = new Window(name);
        Component prev = null;
        while (true) {
            try {
                int what = scanner.nextInt();
                scanner.nextLine();
                if (what == 0) {
                    int position = scanner.nextInt();
                    window.addComponent(position, prev);
                } else if (what == 1) {
                    String color = scanner.nextLine();
                    int weight = scanner.nextInt();
                    Component component = new Component(color, weight);
                    prev = component;
                } else if (what == 2) {
                    String color = scanner.nextLine();
                    int weight = scanner.nextInt();
                    Component component = new Component(color, weight);
                    prev.addComponent(component);
                    prev = component;
                } else if (what == 3) {
                    String color = scanner.nextLine();
                    int weight = scanner.nextInt();
                    Component component = new Component(color, weight);
                    prev.addComponent(component);
                } else if (what == 4) {
                    break;
                }

            } catch (InvalidPositionException e) {
                System.out.println(e.getMessage());
            }
            scanner.nextLine();
        }

        System.out.println("=== ORIGINAL WINDOW ===");
        System.out.println(window);
        int weight = scanner.nextInt();
        scanner.nextLine();
        String color = scanner.nextLine();
        window.changeColor(weight, color);
        System.out.println(String.format("=== CHANGED COLOR (%d, %s) ===", weight, color));
        System.out.println(window);
        int pos1 = scanner.nextInt();
        int pos2 = scanner.nextInt();
        System.out.println(String.format("=== SWITCHED COMPONENTS %d <-> %d ===", pos1, pos2));
        window.swichComponents(pos1, pos2);
        System.out.println(window);
    }
}

// вашиот код овде