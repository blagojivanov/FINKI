package io.github.biv2101.VezbiPrv;

import java.io.InputStream;
import java.io.OutputStream;
import java.io.PrintStream;
import java.util.*;
import java.util.stream.Collectors;

class IrregularCanvasException extends Exception {
    public IrregularCanvasException(String message) {
        System.out.println(message);
    }
}

interface Shape {
    double getArea();
}

class Circle implements Shape {
    int radius;

    public Circle(int radius) {
        this.radius = radius;
    }

    @Override
    public double getArea() {
        return radius * radius * Math.PI;
    }
}

class Square implements Shape, Comparable<Shape> {

    int side;

    public Square(int side) {
        this.side = side;
    }

    @Override
    public double getArea() {
        return side * side;
    }

    @Override
    public int compareTo(Shape o) {
        return Double.compare(getArea(), o.getArea());
    }
}

class Canvas implements Comparable<Canvas> {

    private ArrayList<Shape> shapes;
    private String id;

    public Canvas(String id) {
        this.id = id;
        this.shapes = new ArrayList<>();
    }

    public ArrayList<Shape> getShapes() {
        return shapes;
    }

    private int getNumCirc() {
        return (int) shapes.stream().filter(Circle.class::isInstance).count();
    }

    private int getNumSq() {
        return (int) shapes.stream().filter(Square.class::isInstance).count();
    }

    private double minimumArea() {
        return shapes.stream().min(Comparator.comparing(Shape::getArea)).get().getArea();
    }

    public double maximumArea() {
        return shapes.stream().max(Comparator.comparing(Shape::getArea)).get().getArea();

    }

    private double averageArea() {
        return shapes.stream().mapToDouble(Shape::getArea).average().getAsDouble();
    }

    public double getSumAreas() {
        return shapes.stream().mapToDouble(Shape::getArea).sum();
    }

    public void addShape(Shape s) {
        shapes.add(s);
    }

    @Override
    public String toString() {
        return id + " " + shapes.size() + " " + getNumCirc() + " " + getNumSq() + " " + String.format("%.2f", minimumArea()) + " " + String.format("%.2f", maximumArea()) + " " + String.format("%.2f", averageArea());
    }

    @Override
    public int compareTo(Canvas o) {
        return Double.compare(getSumAreas(), o.getSumAreas());
    }

    public String getId() {
        return id;
    }
}

class ShapesApplication {

    private double maxArea;
    private List<Canvas> canvases;

    public ShapesApplication(double maxArea) {
        this.maxArea = maxArea;
        this.canvases = new ArrayList<>();
    }

    public void addCanvas(Canvas c) throws IrregularCanvasException {
        if (c.maximumArea() > maxArea) {
            throw new IrregularCanvasException("Canvas " + c.getId() + " has a shape with area larger than " + String.format("%.2f",maxArea));
        } else {
            canvases.add(c);
        }
    }

    public void readCanvases(InputStream inputStream){
        Scanner sc = new Scanner(inputStream);

        while (sc.hasNextLine()) {
            String line = sc.nextLine();
            String[] parts = line.split("\\s+");
            Canvas canvas = new Canvas(parts[0]);
            for (int i = 1; i < parts.length - 1; i += 2) {
                Shape shape;
                if (parts[i].toString().toLowerCase().equals("c")) {
                    shape = new Circle(Integer.parseInt(parts[i + 1]));
                } else {
                    shape = new Square(Integer.parseInt(parts[i + 1]));
                }
                canvas.addShape(shape);
            }
            try {
                addCanvas(canvas);
            } catch (IrregularCanvasException e)
            {
                continue;
            }
        }
    }

    public void printCanvases(OutputStream outputStream) {
        PrintStream ps = new PrintStream(outputStream);
        Comparator<Canvas> comp = (Canvas::compareTo);

        canvases.stream().sorted(comp.reversed()).forEach(ps::println);
    }
}

public class Shapes2Test {

    public static void main(String[] args) {

        ShapesApplication shapesApplication = new ShapesApplication(10000);

        System.out.println("===READING CANVASES AND SHAPES FROM INPUT STREAM===");
        shapesApplication.readCanvases(System.in);

        System.out.println("===PRINTING SORTED CANVASES TO OUTPUT STREAM===");
        shapesApplication.printCanvases(System.out);


    }
}