package io.github.biv2101.VezbiVtor;

import java.util.*;
import java.util.stream.Collectors;

class Student {
    private String index;
    private String name;
    private int points1;
    private int points2;
    private int labs;

    public Student(String index, String name) {
        this.index = index;
        this.name = name;
    }

    public String getIndex() {
        return index;
    }

    public String getName() {
        return name;
    }

    public int getPoints1() {
        return points1;
    }

    public int getPoints2() {
        return points2;
    }

    public int getLabs() {
        return labs;
    }

    public void setPoints1(int points1) throws Exception {
        if (points1 < 0 || points1 > 100) {
            throw new Exception();
        }
        this.points1 = points1;
    }

    public void setPoints2(int points2) throws Exception {
        if (points2 < 0 || points2 > 100) {
            throw new Exception();
        }
        this.points2 = points2;
    }

    public void setLabs(int labs) throws Exception {
        if (labs < 0 || labs > 10) {
            throw new Exception();
        }
        this.labs = labs;
    }

    public double summaryPoints() {
        return points1 * 0.45 + points2 * 0.45 + labs;
    }

    public int grade() {
        return Math.max(5, Math.min(10, (int) (summaryPoints() + 10) / 10));
    }

    @Override
    public String toString() {
        return String.format("ID: %s Name: %s First midterm: %d Second midterm %d Labs: %d Summary points: %.2f Grade: %d", index, name, points1, points2, labs, summaryPoints(), grade());
    }
}

class AdvancedProgrammingCourse {

    private Map<String, Student> students;

    public AdvancedProgrammingCourse() {
        students = new HashMap<>();
    }

    public void addStudent(Student s) {
        students.put(s.getIndex(), s);
    }

    public void updateStudent(String idNumber, String activity, int points) {
        Student stud = students.getOrDefault(idNumber, null);
        if (stud != null) {
            if (activity.equals("midterm1")) {
                try {
                    stud.setPoints1(points);
                } catch (Exception e) {
                }
            } else if (activity.equals("midterm2")) {
                try {
                    stud.setPoints2(points);
                } catch (Exception e) {
                }
            } else {
                try {
                    stud.setLabs(points);
                } catch (Exception e) {
                }
            }
        }
    }

    public List<Student> getFirstNStudents(int n) {
        return students.values().stream().sorted(Comparator.comparing(Student::summaryPoints).reversed()).limit(n).collect(Collectors.toList());
    }

    public Map<Integer, Integer> getGradeDistribution() {
        Map<Integer, Integer> returnmap = new HashMap<>();
        for (int i = 5; i<=10; i++)
        {
            returnmap.put(i, 0);
        }
        students.values().stream().forEach(x -> returnmap.compute(x.grade(), (key, val) -> val == null ? 1 : val + 1));
        return returnmap;
    }

    public void printStatistics()
    {
        DoubleSummaryStatistics dss = students.values().stream().filter(x->x.summaryPoints()>=50).mapToDouble(x->x.summaryPoints()).summaryStatistics();
        System.out.printf("Count: %d Min: %.2f Average: %.2f Max: %.2f", dss.getCount(), dss.getMin(), dss.getAverage(), dss.getMax());
    }

}

public class CourseTest {

    public static void printStudents(List<Student> students) {
        students.forEach(System.out::println);
    }

    public static void printMap(Map<Integer, Integer> map) {
        map.forEach((k, v) -> System.out.printf("%d -> %d%n", k, v));
    }

    public static void main(String[] args) {
        AdvancedProgrammingCourse advancedProgrammingCourse = new AdvancedProgrammingCourse();

        Scanner sc = new Scanner(System.in);

        while (sc.hasNextLine()) {
            String line = sc.nextLine();
            String[] parts = line.split("\\s+");

            String command = parts[0];

            if (command.equals("addStudent")) {
                String id = parts[1];
                String name = parts[2];
                advancedProgrammingCourse.addStudent(new Student(id, name));
            } else if (command.equals("updateStudent")) {
                String idNumber = parts[1];
                String activity = parts[2];
                int points = Integer.parseInt(parts[3]);
                advancedProgrammingCourse.updateStudent(idNumber, activity, points);
            } else if (command.equals("getFirstNStudents")) {
                int n = Integer.parseInt(parts[1]);
                printStudents(advancedProgrammingCourse.getFirstNStudents(n));
            } else if (command.equals("getGradeDistribution")) {
                printMap(advancedProgrammingCourse.getGradeDistribution());
            } else {
                advancedProgrammingCourse.printStatistics();
            }
        }
    }
}
