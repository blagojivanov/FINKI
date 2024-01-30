package io.github.biv2101.VezbiVtor;

import java.io.*;
import java.util.*;
import java.util.stream.Collectors;

class InvalidIDException extends Exception {
    public InvalidIDException(String message) {
        super(message);
    }
}

class InvalidDimensionException extends Exception {
    public InvalidDimensionException() {
        super("Dimension 0 is not allowed!");
    }

}

interface Shape {
    double area();

    double perimeter();

    void scale(double coef);
}

class Circle implements Shape {
    private double radius;

    public Circle(String line) throws InvalidDimensionException {
        radius = Double.parseDouble(line.split("\\s+")[2]);
        if (radius == 0)
            throw new InvalidDimensionException();
    }

    @Override
    public double area() {
        return radius * radius * Math.PI;
    }

    @Override
    public double perimeter() {
        return 2 * radius * Math.PI;
    }

    @Override
    public void scale(double coef) {
        radius = radius * coef;
    }

    @Override
    public String toString() {
        return String.format("Circle -> Radius: %.2f Area: %.2f Perimeter: %.2f", radius, area(), perimeter());
    }
}

class Square implements Shape {

    private double side;

    public Square(String line) throws InvalidDimensionException {
        side = Double.parseDouble(line.split("\\s+")[2]);
        if (side == 0) {
            throw new InvalidDimensionException();
        }
    }

    @Override
    public double area() {
        return side * side;
    }

    @Override
    public double perimeter() {
        return 4 * side;
    }

    @Override
    public void scale(double coef) {
        side = side * coef;
    }

    @Override
    public String toString() {
        return String.format("Square: -> Side: %.2f Area: %.2f Perimeter: %.2f", side, area(), perimeter());
    }
}

class Rectangle implements Shape {

    private double a;
    private double b;

    public Rectangle(String line) throws InvalidDimensionException {
        a = Double.parseDouble(line.split("\\s+")[2]);
        b = Double.parseDouble(line.split("\\s+")[3]);
        if (a == 0 || b == 0) {
            throw new InvalidDimensionException();
        }
    }

    @Override
    public double area() {
        return a * b;
    }

    @Override
    public double perimeter() {
        return 2 * a + 2 * b;
    }

    @Override
    public void scale(double coef) {
        a = a * coef;
        b = b * coef;
    }

    @Override
    public String toString() {
        return String.format("Rectangle: -> Sides: %.2f, %.2f Area: %.2f Perimeter: %.2f", a, b, area(), perimeter());
    }
}


class Canvas {

    private Map<String, List<Shape>> shapes;
    private Set<Shape> shapeSet;

    public Canvas() {
        shapes = new HashMap<>();
        shapeSet = new TreeSet<>(Comparator.comparing(Shape::area));
    }

    private boolean test(String id) {
        if (id.length() != 6) return false;
        for (int i = 0; i < id.length(); i++) {
            if (!Character.isLetterOrDigit(id.charAt(i))) {
                return false;
            }
        }
        return true;
    }

    public Shape createShape(String line) throws InvalidDimensionException {
        if (line.startsWith("1"))
            return new Circle(line);
        else if (line.startsWith("2"))
            return new Square(line);
        else
            return new Rectangle(line);
    }

    public void readShapes(InputStream is) throws InvalidDimensionException {
        BufferedReader br = new BufferedReader(new InputStreamReader(is));
        List<String> lines = br.lines().collect(Collectors.toList());

        for (String k : lines) {
            if (!test(k.split("\\s+")[1])) {
                try {
                    throw new InvalidIDException("ID " + k.split("\\s+")[1] + " is not valid");
                } catch (InvalidIDException e) {
                    System.out.println(e.getMessage());
                }
            } else {
                Shape s = createShape(k);
                shapes.computeIfAbsent(k.split("\\s+")[1], l -> new ArrayList<>()).add(s);
                shapeSet.add(s);
            }
        }
    }

    public void scaleShapes(String userID, double coef) {
        shapes.getOrDefault(userID, new ArrayList<>()).forEach(x -> x.scale(coef));
    }

    public void printAllShapes(OutputStream os) {
        PrintStream ps = new PrintStream(os);
        shapeSet.forEach(ps::println);
    }

    public void printByUserId(OutputStream os) {
        PrintStream ps = new PrintStream(os);
        Comparator<Map.Entry<String, List<Shape>>> comparator = Comparator.comparing(entry -> entry.getValue().size());

        shapes.entrySet().stream().sorted(comparator.reversed()
                        .thenComparing(k -> k.getValue().stream().mapToDouble(Shape::area).sum()))
                .forEach(k -> {
                    ps.println("Shapes of user: " + k.getKey());
                    k.getValue().stream().sorted(Comparator.comparing(Shape::perimeter)).forEach(ps::println);
                });
    }

    public void statistics(OutputStream os)
    {
        PrintStream ps = new PrintStream(os);
        DoubleSummaryStatistics statistics = shapeSet.stream().mapToDouble(x -> x.area()).summaryStatistics();
        ps.printf("count: %d\nsum: %.2f\nmin: %.2f\naverage: %.2f\nmax: %.2f",
                statistics.getCount(), statistics.getSum(), statistics.getMin(),
                statistics.getAverage(), statistics.getMax());
        ps.flush();
    }

}

public class CanvasTest {

    public static void main(String[] args) {
        Canvas canvas = new Canvas();

        System.out.println("READ SHAPES AND EXCEPTIONS TESTING");
        try {
            canvas.readShapes(System.in);
        } catch (InvalidDimensionException e) {
            System.out.println(e.getMessage());
        }

        System.out.println("BEFORE SCALING");
        canvas.printAllShapes(System.out);
        canvas.scaleShapes("123456", 1.5);
        System.out.println("AFTER SCALING");
        canvas.printAllShapes(System.out);

        System.out.println("PRINT BY USER ID TESTING");
        canvas.printByUserId(System.out);

        System.out.println("PRINT STATISTICS");
        canvas.statistics(System.out);
    }
}