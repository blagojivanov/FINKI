package io.github.biv2101.VezbiVtor;
import java.io.*;
import java.util.*;
import java.util.function.Supplier;
import java.util.stream.Collectors;
class Employee implements Comparable<Employee> {
    protected String type;
    protected String level;
    protected String id;

    public String getLevel() {
        return level;
    }

    public static Employee createNewEmployee(String line) {
        String[] parts = line.split(";");
        if (parts[0].equals("F")) {
            return new FreelanceEmployee(line);
        }
        return new HourlyEmployee(line);
    }

    public double salary() {
        return 0;
    }

    @Override
    public int compareTo(Employee o) {
        return Comparator.comparing(Employee::salary).thenComparing(Employee::getLevel).reversed().compare(this, o);
    }
}

class HourlyEmployee extends Employee {
    private double hours;

    public HourlyEmployee(String line) {
        String[] parts = line.split(";");
        this.type = parts[0];
        this.id = parts[1];
        this.level = parts[2];
        this.hours = Double.parseDouble(parts[3]);
    }

    @Override
    public double salary() {
        return PayrollSystem.getHourlyRateByLevel().get(level) * Math.min(hours, 40) + PayrollSystem.getHourlyRateByLevel().get(level) * (Math.max(hours, 40) - 40)*1.5;
    }

    @Override
    public String toString() {
        return String.format("Employee ID: %s Level: %s Salary: %.2f Regular hours: %.2f Overtime hours: %.2f", id, level, salary(), Math.min(hours, 40), Math.max(hours, 40) - 40);
    }
}

class FreelanceEmployee extends Employee {
    private List<Integer> ticketP;

    public FreelanceEmployee(String line) {

        String[] parts = line.split(";");
        ticketP = new ArrayList<>();
        this.type = parts[0];
        this.id = parts[1];
        this.level = parts[2];
        Arrays.stream(parts).skip(3).forEach(x -> ticketP.add(Integer.parseInt(x)));
    }

    public double salary() {
        return PayrollSystem.getTicketRateByLevel().get(level) * ticketP.stream().mapToInt(x -> x).sum();
    }

    @Override
    public String toString() {
        return String.format("Employee ID: %s Level: %s Salary: %.2f Tickets count: %d Tickets points: %d", id, level, salary(), ticketP.size(), ticketP.stream().mapToInt(x -> x).sum());

    }
}

class PayrollSystem {
    private static Map<String, Double> hourlyRateByLevel;
    private static Map<String, Double> ticketRateByLevel;

    private List<Employee> employees;

    public PayrollSystem(Map<String, Double> hourlyRateByLevel, Map<String, Double> ticketRateByLevel) {
        PayrollSystem.hourlyRateByLevel = hourlyRateByLevel;
        PayrollSystem.ticketRateByLevel = ticketRateByLevel;
    }

    void readEmployees(InputStream is) {
        BufferedReader br = new BufferedReader(new InputStreamReader(is));

        employees = br.lines().map(Employee::createNewEmployee).collect(Collectors.toList());
    }

    Map<String, Set<Employee>> printEmployeesByLevels(OutputStream os, Set<String> levels) {
        PrintStream ps = new PrintStream(os);
        Map<String, Set<Employee>> map = employees.stream().collect(Collectors.groupingBy(Employee::getLevel,
                (Supplier<Map<String, Set<Employee>>>) TreeMap::new,
                Collectors.toCollection(TreeSet::new)));

        List<String> presentLevels = map.keySet().stream().collect(Collectors.toList());

        presentLevels.stream().filter(lvl -> !levels.contains(lvl)).forEach(lvl -> map.remove(lvl));

        return map;

    }

    public static Map<String, Double> getHourlyRateByLevel() {
        return hourlyRateByLevel;
    }

    public static Map<String, Double> getTicketRateByLevel() {
        return ticketRateByLevel;
    }

}


public class PayrollSystemTest {

    public static void main(String[] args) {

        Map<String, Double> hourlyRateByLevel = new LinkedHashMap<>();
        Map<String, Double> ticketRateByLevel = new LinkedHashMap<>();
        for (int i = 1; i <= 10; i++) {
            hourlyRateByLevel.put("level" + i, 10 + i * 2.2);
            ticketRateByLevel.put("level" + i, 5 + i * 2.5);
        }

        PayrollSystem payrollSystem = new PayrollSystem(hourlyRateByLevel, ticketRateByLevel);

        System.out.println("READING OF THE EMPLOYEES DATA");
        payrollSystem.readEmployees(System.in);

        System.out.println("PRINTING EMPLOYEES BY LEVEL");
        Set<String> levels = new LinkedHashSet<>();
        for (int i = 5; i <= 10; i++) {
            levels.add("level" + i);
        }
        Map<String, Set<Employee>> result = payrollSystem.printEmployeesByLevels(System.out, levels);
        result.forEach((level, employees) -> {
            System.out.println("LEVEL: " + level);
            System.out.println("Employees: ");
            employees.forEach(System.out::println);
            System.out.println("------------");
        });


    }
}
