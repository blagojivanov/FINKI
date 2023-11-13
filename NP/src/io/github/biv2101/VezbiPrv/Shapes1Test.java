package io.github.biv2101.VezbiPrv;

import java.io.InputStream;
import java.io.OutputStream;
import java.io.PrintStream;
import java.util.*;
import java.util.stream.IntStream;

class Square implements Comparable<Square> {
    int size;

    public Square(int size) {
        this.size = size;
    }

    public int getSize() {
        return size;
    }

    @Override
    public int compareTo(Square o) {
        return Integer.compare(size, o.size);
    }
}

class Canvas implements Comparable<Canvas> {
    private String id;

    public String getId() {
        return id;
    }

    private ArrayList<Square> squares;

    public Canvas(String id, ArrayList<Square> squares) {
        this.id = id;
        this.squares = squares;
    }


    public int getSumSquares() {
        return 4 * squares.stream().mapToInt(Square::getSize).sum();
    }


    public int getNumber() {
        return squares.size();
    }

    @Override
    public int compareTo(Canvas o) {
        return Integer.compare(getSumSquares(), o.getSumSquares());
    }
}

class ShapesApplication {
    private ArrayList<Canvas> canvases;

    ShapesApplication() {
        this.canvases = new ArrayList<>();
    }

    int readCanvases(InputStream inputStream) {
        Scanner sc = new Scanner(inputStream);
        while (sc.hasNextLine()) {
            String line = sc.nextLine();

            String[] parts = line.split("\\s+");

            ArrayList<Square> squares = new ArrayList<>();
            IntStream.range(1, parts.length).forEach(i -> squares.add(new Square(Integer.parseInt(parts[i]))));
            Canvas c = new Canvas(parts[0], squares);
            canvases.add(c);
        }
        sc.close();
        return canvases.stream().mapToInt(Canvas::getNumber).sum();
    }

    void printLargestCanvasTo(OutputStream outputStream) {
        PrintStream ps = new PrintStream(outputStream);
        Optional<Canvas> largest = canvases.stream().max(Comparator.naturalOrder());

        ps.println(largest.get().getId() + " " + largest.get().getNumber() + " " + largest.get().getSumSquares());
    }
}

public class Shapes1Test {

    public static void main(String[] args) {
        ShapesApplication shapesApplication = new ShapesApplication();

        System.out.println("===READING SQUARES FROM INPUT STREAM===");
        System.out.println(shapesApplication.readCanvases(System.in));
        System.out.println("===PRINTING LARGEST CANVAS TO OUTPUT STREAM===");
        shapesApplication.printLargestCanvasTo(System.out);

    }
}