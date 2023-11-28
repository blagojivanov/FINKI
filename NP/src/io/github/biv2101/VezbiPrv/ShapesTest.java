package io.github.biv2101.VezbiPrv;


import java.util.*;

enum Color {
    RED, GREEN, BLUE
}

interface Scalable {
    void scale(float scaleFactor);
}

interface Stackable {
    float weight();
}

class Shape implements Stackable, Scalable, Comparable<Shape>, Cloneable {

    protected String id;
    protected Color color;

    public Shape(String id, Color color) {
        this.id = id;
        this.color = color;
    }

    public String getId() {
        return id;
    }

    public String getColor() {
        return (color == Color.RED) ? "RED" : (color == Color.GREEN) ? "GREEN" : "BLUE";
    }

    @Override
    public void scale(float scaleFactor) {
    }

    @Override
    public float weight() {
        return 0;
    }

    @Override
    public int compareTo(Shape o) {
        return Float.compare(weight(), o.weight());
    }

    @Override
    public Shape clone() {
        return this.clone();
    }
}

class Rectangle extends Shape {
    private float width, height;

    public Rectangle(String id, Color color, float width, float height) {
        super(id, color);
        this.width = width;
        this.height = height;
    }

    @Override
    public void scale(float scaleFactor) {
        width *= scaleFactor;
        height *= scaleFactor;
    }

    @Override
    public float weight() {
        return width * height;
    }

    @Override
    public String toString() {
        return String.format("R: %-5s%-10s%10.2f", id, getColor(), weight());
    }

    @Override
    public Shape clone() {
        return new Rectangle(id, color, width, height);
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Rectangle rectangle = (Rectangle) o;
        return Float.compare(width, rectangle.width) == 0 && Float.compare(height, rectangle.height) == 0;
    }

    @Override
    public int hashCode() {
        return Objects.hash(id);
    }
}

class Circle extends Shape {
    private float radius;

    public Circle(String id, Color color, float radius) {
        super(id, color);
        this.radius = radius;
    }

    @Override
    public void scale(float scaleFactor) {
        radius *= scaleFactor;
    }

    @Override
    public float weight() {
        return (float) (radius * radius * Math.PI);
    }

    @Override
    public String toString() {
        return String.format("C: %-5s%-10s%10.2f", id, getColor(), weight());
    }

    @Override
    public Shape clone() {
        return new Circle(id, color, radius);
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Circle circle = (Circle) o;
        return Float.compare(radius, circle.radius) == 0;
    }

    @Override
    public int hashCode() {
        return Objects.hash(id);
    }
}

class Canvas {
    private List<Shape> shapes;

    public Canvas() {
        shapes = new ArrayList<>();
    }

    public void add(String id, Color color, float radius) {
        Shape toAdd = new Circle(id, color, radius);
        addS(toAdd);
    }

    public void add(String id, Color color, float width, float height) {
        Shape toAdd = new Rectangle(id, color, width, height);
        addS(toAdd);
    }

    private void addS(Shape s) {
        if (shapes.isEmpty())
        {
            shapes.add(s);
            return;
        }
        for (int i = 0; i < shapes.size(); i++)
            if (shapes.get(i).weight() < s.weight()) {
                shapes.add(i, s);
                return;
            }
        shapes.add(s);

    }

    public void scale(String id, float scaleFactor) {
        Shape toChange = null;
        Iterator<Shape> itr = shapes.iterator();
        while (itr.hasNext()) {
            Shape shape = itr.next();
            if (shape.getId().equals(id)) {
                shape.scale(scaleFactor);
                toChange = shape;
                itr.remove();
                break;
            }
        }

        if (toChange != null) {
            addS(toChange);
        }
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();

        shapes.stream().forEach(s -> sb.append(s).append("\n"));
//        shapes.forEach(s -> sb.append(s).append("\n"));
        return sb.toString();
    }
}

public class ShapesTest {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        Canvas canvas = new Canvas();
        while (scanner.hasNextLine()) {
            String line = scanner.nextLine();
            String[] parts = line.split(" ");
            int type = Integer.parseInt(parts[0]);
            String id = parts[1];
            if (type == 1) {
                Color color = Color.valueOf(parts[2]);
                float radius = Float.parseFloat(parts[3]);
                canvas.add(id, color, radius);
            } else if (type == 2) {
                Color color = Color.valueOf(parts[2]);
                float width = Float.parseFloat(parts[3]);
                float height = Float.parseFloat(parts[4]);
                canvas.add(id, color, width, height);
            } else if (type == 3) {
                float scaleFactor = Float.parseFloat(parts[2]);
                System.out.println("ORIGNAL:");
                System.out.print(canvas);
                canvas.scale(id, scaleFactor);
                System.out.printf("AFTER SCALING: %s %.2f\n", id, scaleFactor);
                System.out.print(canvas);
            }

        }
    }
}
