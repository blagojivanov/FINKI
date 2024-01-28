package io.github.biv2101.VezbiVtor;


import java.util.*;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

class Student {

    public static Comparator<Student> comp = Comparator.comparing(Student::summary).thenComparing(Student::getIndex);
    private String index;
    private List<Integer> points;


    public String failed() {
        if (points.size() < 8) {
            return "NO";
        }
        return "YES";
    }

    public String getIndex() {
        return index;
    }

    public Student(String index, List<Integer> points) {
        this.index = index;
        this.points = points;
    }

    public double summary() {
        return points.stream().mapToDouble(x -> x).sum()/10;
    }

    public int getYear()
    {
        return 20 - Integer.parseInt(getIndex().substring(0,2));
    }

    @Override
    public String toString() {
        return String.format("%s %s %.2f", index, failed(), summary());
    }
}

class LabExercises {

    Set<Student> students;

    public LabExercises() {
        students = new HashSet<>();
    }

    public void addStudent(Student student) {
        students.add(student);
    }

    public void printByAveragePoints(boolean ascending, int n) {
        SortedSet<Student> sorted;
        if (!ascending) {
            sorted = new TreeSet<>(Student.comp.reversed());
        } else {
            sorted = new TreeSet<>(Student.comp);
        }
        sorted.addAll(students);
        sorted.stream().limit(n).forEach(System.out::println);
    }

    public List<Student> failedStudents() {

        return students.stream().filter(x->x.failed().equals("NO")).sorted(Comparator.comparing(Student::getIndex).thenComparing(Student::summary)).collect(Collectors.toList());
    }
    public Map<Integer,Double> getStatisticsByYear()
    {

        return students.stream().filter(x->x.failed().equals("YES")).collect(Collectors.groupingBy(Student::getYear, Collectors.averagingDouble(Student::summary)));
    }
}
public class LabExercisesTest {

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        LabExercises labExercises = new LabExercises();
        while (sc.hasNextLine()) {
            String input = sc.nextLine();
            String[] parts = input.split("\\s+");
            String index = parts[0];
            List<Integer> points = Arrays.stream(parts).skip(1)
                    .mapToInt(Integer::parseInt)
                    .boxed()
                    .collect(Collectors.toList());

            labExercises.addStudent(new Student(index, points));
        }

        System.out.println("===printByAveragePoints (ascending)===");
        labExercises.printByAveragePoints(true, 100);
        System.out.println("===printByAveragePoints (descending)===");
        labExercises.printByAveragePoints(false, 100);
        System.out.println("===failed students===");
        labExercises.failedStudents().forEach(System.out::println);
        System.out.println("===statistics by year");
        labExercises.getStatisticsByYear().entrySet().stream()
                .map(entry -> String.format("%d : %.2f", entry.getKey(), entry.getValue()))
                .forEach(System.out::println);

    }
}