package io.github.biv2101.VezbiVtor;

import java.util.*;
import java.util.stream.IntStream;

class OperationNotAllowedException extends Exception {
    public OperationNotAllowedException(String message) {
        super(message);
    }
}

class Course {
    private String name;
    private List<Integer> grades;

    public Course(String name) {
        this.name = name;
        grades = new ArrayList<>();
    }

    public List<Integer> getGrades() {
        return grades;
    }

    public int listeners() {
        return grades.size();
    }

    public double getAverage() {
        return grades.stream().mapToInt(x -> x).average().orElse(5.0);
    }

    @Override
    public String toString() {
        return String.format("%s %d %.2f", name, listeners(), getAverage());
    }
}

abstract class FacultyStudent {
    protected String id;
    protected int yearsOfStudies;

    protected Map<Integer, List<Integer>> grades;
    protected Set<String> courses;
    protected boolean graduated;

    protected int coursesPassed() {
        return courses.size();
    }

    public FacultyStudent(String id, int yearsOfStudies) {
        grades = new TreeMap<>();
        courses = new TreeSet<>();
        this.id = id;
        this.yearsOfStudies = yearsOfStudies;
        graduated = false;
        IntStream.range(1, yearsOfStudies * 2 + 1).forEach(i -> grades.put(i, new ArrayList<>()));
    }

    public String getId() {
        return id;
    }

    public int getYearsOfStudies() {
        return yearsOfStudies;
    }

    public Map<Integer, List<Integer>> getGrades() {
        return grades;
    }

    public Set<String> getCourses() {
        return courses;
    }

    public double getAverage() {
        return grades.values().stream().flatMap(Collection::stream).mapToInt(x -> x).average().orElse(5.0);
    }

    public abstract boolean addGrade(int term, String courseName, int grade) throws OperationNotAllowedException;

    @Override
    public String toString() {
        return String.format("Student: %s Courses passed: %d Average grade: %.2f", id, coursesPassed(), getAverage());
    }
}

class ThreeYearStudent extends FacultyStudent {

    public ThreeYearStudent(String id, int yearsOfStudies) {
        super(id, yearsOfStudies);
    }

    @Override
    public boolean addGrade(int term, String courseName, int grade) throws OperationNotAllowedException {
        if (term <= 6) {
            List<Integer> grades = getGrades().get(term);
            if (grades.size() < 3) {
                grades.add(grade);
                getCourses().add(courseName);
            } else {
                throw new OperationNotAllowedException("Student " + id + " already has 3 grades in term " + term);
            }
        } else {
            throw new OperationNotAllowedException("Term " + term + " is not possible for student with ID " + id);
        }

        graduated = getCourses().size() == 18;
        return graduated;

    }
}

class FourYearStudent extends FacultyStudent {

    public FourYearStudent(String id, int yearsOfStudies) {
        super(id, yearsOfStudies);
    }

    @Override
    public boolean addGrade(int term, String courseName, int grade) throws OperationNotAllowedException {
        if (term <= 8) {
            List<Integer> grades = getGrades().get(term);
            if (grades.size() < 3) {
                grades.add(grade);
                getCourses().add(courseName);
            } else {
                throw new OperationNotAllowedException("Student " + id + " already has 3 grades in term " + term);
            }
        } else {
            throw new OperationNotAllowedException("Term " + term + " is not possible for student with ID " + id);
        }

        graduated = getCourses().size() == 24;
        return graduated;

    }
}


class Faculty {

    private Map<String, FacultyStudent> students;
    private Map<String, Course> courses;
    private List<String> logs;

    public Faculty() {
        students = new TreeMap<>();
        courses = new TreeMap<>();
        logs = new ArrayList<>();
    }

    void addStudent(String id, int yearsOfStudies) {
        students.put(id, (yearsOfStudies == 3) ? new ThreeYearStudent(id, yearsOfStudies) : new FourYearStudent(id, yearsOfStudies));
    }

    void addGradeToStudent(String studentId, int term, String courseName, int grade) throws OperationNotAllowedException {
        FacultyStudent facultyStudent = students.get(studentId);
        if (facultyStudent != null) {
            courses.computeIfAbsent(courseName, x -> new Course(courseName)).getGrades().add(grade);
            facultyStudent.addGrade(term, courseName, grade);
            if (facultyStudent.graduated) {
                logs.add(String.format("Student with ID %s graduated with average grade %.2f in %d years.", studentId, facultyStudent.getAverage(), facultyStudent.getYearsOfStudies()));
                students.remove(studentId);
            }
        }
    }

    String getFacultyLogs() {
        StringBuilder sb = new StringBuilder();
        logs.forEach(x -> sb.append(x).append("\n"));
        return sb.substring(0, sb.length()-1);
    }
    String getDetailedReportForStudent(String id) {
        StringBuilder sb = new StringBuilder();
        sb.append("Student: ").append(id).append("\n");
        students.get(id).getGrades().forEach((key, value) ->
        {
            sb.append("Term ").append(key).append("\n");
            sb.append("Courses: ").append(value.size()).append("\n");
            sb.append(String.format("Average grade for term: %.2f", value.stream().mapToInt(x -> x).average().orElse(5.0))).append("\n");
        });
        sb.append(String.format("Average grade: %.2f\n", students.get(id).getAverage()));
        sb.append("Courses attended: ");
        students.get(id).getCourses().forEach(x -> sb.append(x).append(","));
        return sb.substring(0, sb.length() - 1);
    }

    void printFirstNStudents(int n) {
        students.values().stream().sorted(Comparator.comparing(FacultyStudent::coursesPassed).thenComparing(FacultyStudent::getAverage).thenComparing(FacultyStudent::getId).reversed())
                .limit(n).forEach(System.out::println);
    }

    void printCourses() {
        courses.values().stream().sorted(Comparator.comparing(Course::listeners).thenComparing(Course::getAverage)).forEach(System.out::println);
    }
}

public class FacultyTest {

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int testCase = sc.nextInt();

        if (testCase == 1) {
            System.out.println("TESTING addStudent AND printFirstNStudents");
            Faculty faculty = new Faculty();
            for (int i = 0; i < 10; i++) {
                faculty.addStudent("student" + i, (i % 2 == 0) ? 3 : 4);
            }
            faculty.printFirstNStudents(10);

        } else if (testCase == 2) {
            System.out.println("TESTING addGrade and exception");
            Faculty faculty = new Faculty();
            faculty.addStudent("123", 3);
            faculty.addStudent("1234", 4);
            try {
                faculty.addGradeToStudent("123", 7, "NP", 10);
            } catch (OperationNotAllowedException e) {
                System.out.println(e.getMessage());
            }
            try {
                faculty.addGradeToStudent("1234", 9, "NP", 8);
            } catch (OperationNotAllowedException e) {
                System.out.println(e.getMessage());
            }
        } else if (testCase == 3) {
            System.out.println("TESTING addGrade and exception");
            Faculty faculty = new Faculty();
            faculty.addStudent("123", 3);
            faculty.addStudent("1234", 4);
            for (int i = 0; i < 4; i++) {
                try {
                    faculty.addGradeToStudent("123", 1, "course" + i, 10);
                } catch (OperationNotAllowedException e) {
                    System.out.println(e.getMessage());
                }
            }
            for (int i = 0; i < 4; i++) {
                try {
                    faculty.addGradeToStudent("1234", 1, "course" + i, 10);
                } catch (OperationNotAllowedException e) {
                    System.out.println(e.getMessage());
                }
            }
        } else if (testCase == 4) {
            System.out.println("Testing addGrade for graduation");
            Faculty faculty = new Faculty();
            faculty.addStudent("123", 3);
            faculty.addStudent("1234", 4);
            int counter = 1;
            for (int i = 1; i <= 6; i++) {
                for (int j = 1; j <= 3; j++) {
                    try {
                        faculty.addGradeToStudent("123", i, "course" + counter, (i % 2 == 0) ? 7 : 8);
                    } catch (OperationNotAllowedException e) {
                        System.out.println(e.getMessage());
                    }
                    ++counter;
                }
            }
            counter = 1;
            for (int i = 1; i <= 8; i++) {
                for (int j = 1; j <= 3; j++) {
                    try {
                        faculty.addGradeToStudent("1234", i, "course" + counter, (j % 2 == 0) ? 7 : 10);
                    } catch (OperationNotAllowedException e) {
                        System.out.println(e.getMessage());
                    }
                    ++counter;
                }
            }
            System.out.println("LOGS");
            System.out.println(faculty.getFacultyLogs());
            System.out.println("PRINT STUDENTS (there shouldn't be anything after this line!");
            faculty.printFirstNStudents(2);
        } else if (testCase == 5 || testCase == 6 || testCase == 7) {
            System.out.println("Testing addGrade and printFirstNStudents (not graduated student)");
            Faculty faculty = new Faculty();
            for (int i = 1; i <= 10; i++) {
                faculty.addStudent("student" + i, ((i % 2) == 1 ? 3 : 4));
                int courseCounter = 1;
                for (int j = 1; j < ((i % 2 == 1) ? 6 : 8); j++) {
                    for (int k = 1; k <= ((j % 2 == 1) ? 3 : 2); k++) {
                        try {
                            faculty.addGradeToStudent("student" + i, j, ("course" + courseCounter), i % 5 + 6);
                        } catch (OperationNotAllowedException e) {
                            System.out.println(e.getMessage());
                        }
                        ++courseCounter;
                    }
                }
            }
            if (testCase == 5)
                faculty.printFirstNStudents(10);
            else if (testCase == 6)
                faculty.printFirstNStudents(3);
            else
                faculty.printFirstNStudents(20);
        } else if (testCase == 8 || testCase == 9) {
            System.out.println("TESTING DETAILED REPORT");
            Faculty faculty = new Faculty();
            faculty.addStudent("student1", ((testCase == 8) ? 3 : 4));
            int grade = 6;
            int counterCounter = 1;
            for (int i = 1; i < ((testCase == 8) ? 6 : 8); i++) {
                for (int j = 1; j < 3; j++) {
                    try {
                        faculty.addGradeToStudent("student1", i, "course" + counterCounter, grade);
                    } catch (OperationNotAllowedException e) {
                        e.printStackTrace();
                    }
                    grade++;
                    if (grade == 10)
                        grade = 5;
                    ++counterCounter;
                }
            }
            System.out.println(faculty.getDetailedReportForStudent("student1"));
        } else if (testCase == 10) {
            System.out.println("TESTING PRINT COURSES");
            Faculty faculty = new Faculty();
            for (int i = 1; i <= 10; i++) {
                faculty.addStudent("student" + i, ((i % 2) == 1 ? 3 : 4));
                int courseCounter = 1;
                for (int j = 1; j < ((i % 2 == 1) ? 6 : 8); j++) {
                    for (int k = 1; k <= ((j % 2 == 1) ? 3 : 2); k++) {
                        int grade = sc.nextInt();
                        try {
                            faculty.addGradeToStudent("student" + i, j, ("course" + courseCounter), grade);
                        } catch (OperationNotAllowedException e) {
                            System.out.println(e.getMessage());
                        }
                        ++courseCounter;
                    }
                }
            }
            faculty.printCourses();
        } else if (testCase == 11) {
            System.out.println("INTEGRATION TEST");
            Faculty faculty = new Faculty();
            for (int i = 1; i <= 10; i++) {
                faculty.addStudent("student" + i, ((i % 2) == 1 ? 3 : 4));
                int courseCounter = 1;
                for (int j = 1; j <= ((i % 2 == 1) ? 6 : 8); j++) {
                    for (int k = 1; k <= ((j % 2 == 1) ? 2 : 3); k++) {
                        int grade = sc.nextInt();
                        try {
                            faculty.addGradeToStudent("student" + i, j, ("course" + courseCounter), grade);
                        } catch (OperationNotAllowedException e) {
                            System.out.println(e.getMessage());
                        }
                        ++courseCounter;
                    }
                }

            }

            for (int i = 11; i < 15; i++) {
                faculty.addStudent("student" + i, ((i % 2) == 1 ? 3 : 4));
                int courseCounter = 1;
                for (int j = 1; j <= ((i % 2 == 1) ? 6 : 8); j++) {
                    for (int k = 1; k <= 3; k++) {
                        int grade = sc.nextInt();
                        try {
                            faculty.addGradeToStudent("student" + i, j, ("course" + courseCounter), grade);
                        } catch (OperationNotAllowedException e) {
                            System.out.println(e.getMessage());
                        }
                        ++courseCounter;
                    }
                }
            }
            System.out.println("LOGS");
            System.out.println(faculty.getFacultyLogs());
            System.out.println("DETAILED REPORT FOR STUDENT");
            System.out.println(faculty.getDetailedReportForStudent("student2"));
            try {
                System.out.println(faculty.getDetailedReportForStudent("student11"));
                System.out.println("The graduated students should be deleted!!!");
            } catch (NullPointerException e) {
                System.out.println("The graduated students are really deleted");
            }
            System.out.println("FIRST N STUDENTS");
            faculty.printFirstNStudents(10);
            System.out.println("COURSES");
            faculty.printCourses();
        }
    }
}
