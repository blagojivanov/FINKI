package io.github.biv2101.VezbiVtor;

import java.io.*;
import java.util.*;
import java.util.function.Function;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

/**
 * January 2016 Exam problem 1
 */
// Slack integrations
class StudentRec {
    List<Integer> grades;
    String id;

    public StudentRec(String line) {
        grades = new ArrayList<>();
        List<String> lp = Arrays.stream(line.split("\\s+")).collect(Collectors.toList());
        id = lp.get(0);
        lp.stream().skip(2).forEach(x -> grades.add(Integer.parseInt(x)));

    }

    public double getAverage() {
        return grades.stream().mapToInt(x -> x).average().orElse(0);
    }

    public Map<Integer, Long> getGradeDist() {
        Map<Integer, Long> returnMap = new TreeMap<>();
        IntStream.range(6, 11).forEach(i ->
        {
            returnMap.computeIfAbsent(i, x -> grades.stream().filter(y -> y == i).count());
        });
        return returnMap;
    }

    public String getId() {
        return id;
    }

    @Override
    public String toString() {
        return String.format("%s %.2f", id, getAverage());
    }
}

class StudentRecords {

    Map<String, List<StudentRec>> records;

    public StudentRecords() {
        records = new TreeMap<>();
    }

    public int readRecords(InputStream is) {
        BufferedReader br = new BufferedReader(new InputStreamReader(is));
        br.lines().forEach(l ->
        {
            String[] lp = l.split("\\s+");
            records.computeIfAbsent(lp[1], x -> new ArrayList<>()).add(new StudentRec(l));
        });
        return (int) records.values().stream().flatMap(Collection::stream).count();
    }

    public void writeTable(OutputStream os) {
        PrintStream ps = new PrintStream(os);
        records.forEach((key, value) -> {
            ps.printf("%s\n", key);
            value.stream().sorted(Comparator.comparing(StudentRec::getAverage).reversed().thenComparing(StudentRec::getId)).forEach(ps::println);
        });
    }

    public void writeDistribution(OutputStream os) {
        PrintStream ps = new PrintStream(os);

        Map<String, Map<Integer, Long>> distr = new TreeMap<>();
        records.forEach((key, value) ->
        {
            Map<Integer, Long> gradedist = new TreeMap<>();
            value.stream().map(StudentRec::getGradeDist).forEach(m ->
            {
                IntStream.range(6, 11).forEach(i -> gradedist.compute(i, (k, v) -> (v == null) ? m.get(i) : v + m.get(i)));
            });
            distr.put(key, gradedist);
        });

        Comparator<Map.Entry<String, Map<Integer, Long>>> entryComparator = Comparator.comparingInt(o -> Math.toIntExact(o.getValue().get(10)));
        distr.entrySet().stream().sorted(entryComparator.reversed()).forEach(x ->
        {
            ps.println(x.getKey());
            x.getValue().entrySet().stream().forEach(z -> ps.printf("%2d | %s(%d)\n", z.getKey(), "*".repeat((int) Math.ceil((double) z.getValue() / 10)), z.getValue()));
        });

    }
}

public class StudentRecordsTest {
    public static void main(String[] args) {
        System.out.println("=== READING RECORDS ===");
        StudentRecords studentRecords = new StudentRecords();
        int total = studentRecords.readRecords(System.in);
        System.out.printf("Total records: %d\n", total);
        System.out.println("=== WRITING TABLE ===");
        studentRecords.writeTable(System.out);
        System.out.println("=== WRITING DISTRIBUTION ===");
        studentRecords.writeDistribution(System.out);
    }
}

// your code here