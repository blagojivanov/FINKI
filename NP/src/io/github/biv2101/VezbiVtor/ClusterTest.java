package io.github.biv2101.VezbiVtor;

import java.util.*;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

interface Clusterable {
    long getId();

    double distance(Clusterable clusterable);
}

class Point2D implements Clusterable {
    private long id;
    private float x;
    private float y;

    public Point2D(long id, float x, float y) {
        this.id = id;
        this.x = x;
        this.y = y;
    }

    public float getX() {
        return x;
    }

    public float getY() {
        return y;
    }

    @Override
    public long getId() {
        return id;
    }

    @Override
    public double distance(Clusterable clusterable) {
        Point2D point2D = (Point2D) clusterable;
        return Math.sqrt((x - point2D.x) * (x - point2D.x) + (y - point2D.y) * (y - point2D.y));
    }

}

class Cluster<T extends Clusterable> {
    private List<T> list;

    public Cluster() {
        list = new ArrayList<>();
    }

    public void addItem(T element) {
        list.add(element);
    }

    public void near(long id, int top) {

        T c = list.stream().filter(x -> x.getId() == id).findFirst().get();
        List<T> collect = list.stream().sorted(Comparator.comparing(p -> p.distance(c))).collect(Collectors.toList());

        IntStream.range(1, Math.min(top + 1, collect.size())).forEach(i -> System.out.printf("%d. %d -> %.3f\n", i, collect.get(i).getId(), c.distance(collect.get(i))));
    }
}

/**
 * January 2016 Exam problem 2
 */
public class ClusterTest {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        Cluster<Point2D> cluster = new Cluster<>();
        int n = scanner.nextInt();
        scanner.nextLine();
        for (int i = 0; i < n; ++i) {
            String line = scanner.nextLine();
            String[] parts = line.split(" ");
            long id = Long.parseLong(parts[0]);
            float x = Float.parseFloat(parts[1]);
            float y = Float.parseFloat(parts[2]);
            cluster.addItem(new Point2D(id, x, y));
        }
        int id = scanner.nextInt();
        int top = scanner.nextInt();
        cluster.near(id, top);
        scanner.close();
    }
}

// your code here