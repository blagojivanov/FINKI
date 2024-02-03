package io.github.biv2101.VezbiVtor;

import java.io.*;
import java.time.Duration;
import java.time.LocalDateTime;
import java.time.Month;
import java.time.format.DateTimeFormatter;
import java.util.*;

class DeadlineNotValidException extends Exception {
    public DeadlineNotValidException(String message) {
        super(message);
    }
}

interface Task {
    int getPriority();

    LocalDateTime getDeadline();
}

class TaskBase implements Task {
    protected String name;
    protected String description;

    public TaskBase(String name, String description) {
        this.name = name;
        this.description = description;
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append("Task{");
        sb.append("name='").append(name).append("', description='").append(description).append("'");
        sb.append("}");
        return sb.toString();

    }

    public String getName() {
        return name;
    }
    @Override
    public int getPriority() {
        return Integer.MAX_VALUE;
    }

    @Override
    public LocalDateTime getDeadline() {
        return LocalDateTime.MAX;
    }
}

abstract class TaskDecorator implements Task {
    protected Task task;

    public TaskDecorator(Task task) {
        this.task = task;
    }
}

class PriorityTaskDecorator extends TaskDecorator {

    int priority;

    public PriorityTaskDecorator(Task task, int priority) {
        super(task);
        this.priority = priority;
    }

    @Override
    public int getPriority() {
        return priority;
    }

    @Override
    public LocalDateTime getDeadline() {
        return task.getDeadline();
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder(task.toString().substring(0, task.toString().length() - 1));
        sb.append(", priority=").append(priority);
        sb.append("}");
        return sb.toString();
    }
}

class TimeTaskDecorator extends TaskDecorator {
    LocalDateTime deadline;

    public TimeTaskDecorator(Task task, LocalDateTime deadline) {
        super(task);
        this.deadline = deadline;
    }

    @Override
    public int getPriority() {
        return task.getPriority();
    }

    @Override
    public LocalDateTime getDeadline() {
        return deadline;
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder(task.toString().substring(0, task.toString().length() - 1));
        sb.append(", deadline=").append(deadline);
        sb.append("}");
        return sb.toString();
    }
}

class TaskFactory {
    public static DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd'T'HH:mm:ss.SSS");

    public static Task createTask(String line) throws DeadlineNotValidException {
        Task t;

        String[] lp = line.split(",");
        String name = lp[1];
        String description = lp[2];
        t = new TaskBase(name, description);
        LocalDateTime deadline;
        if (lp.length == 4) {
            if (lp[3].length() > 2) {
                deadline = LocalDateTime.parse(lp[3], formatter);
                if (deadline.isBefore(LocalDateTime.of(2020, Month.JUNE, 2, 0, 0))) {
                    throw new DeadlineNotValidException("The deadline " + LocalDateTime.parse(lp[3], formatter) + " has already passed");
                } else {
                    t = new TimeTaskDecorator(t, deadline);
                }
            } else {
                t = new PriorityTaskDecorator(t, Integer.parseInt(lp[3]));
            }

        }
        if (lp.length == 5) {

            deadline = LocalDateTime.parse(lp[3], formatter);
            if (deadline.isBefore(LocalDateTime.of(2020, Month.JUNE, 2, 0, 0))) {
                throw new DeadlineNotValidException("The deadline " + LocalDateTime.parse(lp[3], formatter) + " has already passed");
            } else {
                t = new PriorityTaskDecorator(new TimeTaskDecorator(t, deadline), Integer.parseInt(lp[4]));
            }

        }
        return t;
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
                Task t = TaskFactory.createTask(l);
                tasks.computeIfAbsent(lp[0], x -> new ArrayList<>()).add(t);
                tasksList.add(t);
            } catch (DeadlineNotValidException e) {
                System.out.println(e.getMessage());
            }
        });
    }

    void printTasks(OutputStream os, boolean includePriority, boolean includeCategory) {
        PrintStream ps = new PrintStream(os);

        Comparator<Task> c = (includePriority) ? Comparator.comparing(Task::getPriority).thenComparing(task -> Duration.between(LocalDateTime.now(), task.getDeadline())) : Comparator.comparing(task -> Duration.between(LocalDateTime.now(), task.getDeadline()));

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
