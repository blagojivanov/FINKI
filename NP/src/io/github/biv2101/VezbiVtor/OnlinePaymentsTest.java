package io.github.biv2101.VezbiVtor;

import java.io.*;
import java.util.*;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

class Payment {

    public String index;
    public String title;
    public int cost;

    public Payment(String line) {
        String[] lp = line.split(";");
        index = lp[0];
        title = lp[1];
        cost = Integer.parseInt(lp[2]);
    }

    public int getCost() {
        return cost;
    }
}

class OnlinePayments {
    Map<String, List<Payment>> students;

    public OnlinePayments()
    {
        students = new HashMap<>();
    }

    public void readItems(InputStream is) {
        BufferedReader br = new BufferedReader(new InputStreamReader(is));
        br.lines().map(Payment::new).forEach(x -> students.computeIfAbsent(x.index, z -> new ArrayList<>()).add(x));
        try {
            br.close();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    public void printStudentReport(String id, OutputStream os) {
        PrintStream ps = new PrintStream(os);
        if (students.containsKey(id)) {
            List<Payment> list = students.get(id);
            int sum = list.stream().mapToInt(x -> x.cost).sum();
            int fee = (int) Math.round(Math.max(3, Math.min(300, sum * 0.0114)));
            list.sort(Comparator.comparing(Payment::getCost).reversed());
            ps.printf("Student: %s Net: %d Fee: %d Total: %d\nItems:\n", id, sum, fee, sum + fee);
            IntStream.range(0, list.size()).forEach(i -> {
                System.out.printf("%d. %s %s\n", i+1, list.get(i).title, list.get(i).cost);
            });
        } else {
            System.out.println("Student " + id + " not found!");
        }
    }

}

public class OnlinePaymentsTest {
    public static void main(String[] args) {
        OnlinePayments onlinePayments = new OnlinePayments();

        onlinePayments.readItems(System.in);

        IntStream.range(151020, 151025).mapToObj(String::valueOf).forEach(id -> onlinePayments.printStudentReport(id, System.out));
    }
}