package io.github.biv2101.VezbiVtor;

import java.io.*;
import java.text.DateFormat;
import java.time.Duration;
import java.time.LocalDate;
import java.time.LocalDateTime;
import java.time.Month;
import java.time.format.DateTimeFormatter;
import java.util.*;
import java.util.stream.Collectors;

class DeadlineNotValidException extends Exception {
    public DeadlineNotValidException(String message) {
        super(message);
    }
}

class Task {
    String name;
    String description;
    int priority;
    LocalDateTime deadline;

    boolean hasPriority;

    boolean hasDeadline;

    public static DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd'T'HH:mm:ss.SSS");

    public Task(String line) throws DeadlineNotValidException {
//        School,NP,lab 1 po NP,2020-06-23T23:59:59.000,1
        String[] lp = line.split(",");
        name = lp[1];
        description = lp[2];
        deadline = LocalDateTime.now();
        hasDeadline = false;
        hasPriority = false;
        if (lp.length > 3) {
            if (lp[3].length() > 2) {
                deadline = LocalDateTime.parse(lp[3], formatter);
                hasDeadline = true;
                if (deadline.isBefore(LocalDateTime.of(2020, Month.JUNE, 2, 0, 0))) {
                    throw new DeadlineNotValidException("The deadline " + LocalDateTime.parse(lp[3], formatter) + " has already passed");
                }
            } else {
                priority = Integer.parseInt(lp[3]);
                hasPriority = true;
            }

        }
        if (lp.length > 4) {
            priority = Integer.parseInt(lp[4]);
            hasPriority = true;

        }

    }

    public int getPriority() {
        return priority;
    }

    public LocalDateTime getDeadline() {
        return deadline;
    }

    public boolean isPriority()
    {
        return !hasPriority;
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append("Task{");
        sb.append("name='").append(name).append("', description='").append(description).append("'");
        if (hasDeadline) sb.append(", deadline=").append(deadline);
        if (hasPriority) sb.append(", priority=").append(priority);
        sb.append("}");
        return sb.toString();

    }
}

class TaskManager {
    Map<String, List<Task>> tasks;
    List<Task> tasksList;

    public TaskManager() {
        tasks = new TreeMap<>();
        tasksList = new ArrayList<>();
    }

    void readTasks(InputStream is) {
        BufferedReader br = new BufferedReader(new InputStreamReader(is));

        br.lines().forEach(l ->
        {
            String[] lp = l.split(",");

            try {
                Task t = new Task(l);
                tasks.computeIfAbsent(lp[0], x -> new ArrayList<>()).add(t);
                tasksList.add(t);
            } catch (DeadlineNotValidException e) {
                System.out.println(e.getMessage());
            }
        });
    }

    void printTasks(OutputStream os, boolean includePriority, boolean includeCategory) {
        PrintStream ps = new PrintStream(os);

        Comparator<Task> c = (includePriority) ? Comparator.comparing(Task::isPriority).thenComparing(Task::getPriority).thenComparing(task -> Duration.between(LocalDateTime.now(), task.getDeadline())) : Comparator.comparing(task -> Duration.between(LocalDateTime.now(), task.getDeadline()));

        if (includeCategory) {
            tasks.keySet().stream().forEach(key -> ps.printf("%s\n%s", key.toUpperCase(), printList(key, c)));
        } else {
            tasksList.stream().sorted(c).forEach(ps::println);
        }
    }

    String printList(String key, Comparator<Task> c) {
        StringBuilder sb = new StringBuilder();
        tasks.get(key).stream().sorted(c).forEach(x -> sb.append(x).append("\n"));
        return sb.toString();
    }

}

public class TasksManagerTest {

    public static void main(String[] args) {

        TaskManager manager = new TaskManager();

        System.out.println("Tasks reading");
        manager.readTasks(System.in);
        System.out.println("By categories with priority");
        manager.printTasks(System.out, true, true);
        System.out.println("-------------------------");
        System.out.println("By categories without priority");
        manager.printTasks(System.out, false, true);
        System.out.println("-------------------------");
        System.out.println("All tasks without priority");
        manager.printTasks(System.out, false, false);
        System.out.println("-------------------------");
        System.out.println("All tasks with priority");
        manager.printTasks(System.out, true, false);
        System.out.println("-------------------------");

    }
}
