package io.github.biv2101.VezbiVtor;

//package mk.ukim.finki.midterm;


import java.util.*;

class DurationConverter {
    public static String convert(long duration) {
        long minutes = duration / 60;
        duration %= 60;
        return String.format("%02d:%02d", minutes, duration);
    }
}

enum Action {
    ANSWER, HOLD, END, RESUME
}

interface IState {
    void hold(long timestamp);

    void answer(long timestamp);

    void resume(long timestamp);

    void end(long timestamp);
}

abstract class State implements IState {
    Call call;

    public State(Call call) {
        this.call = call;
    }
}

class RingingState extends State {

    public RingingState(Call call) {
        super(call);
    }

    @Override
    public void hold(long timestamp) {
        throw new RuntimeException();

    }

    @Override
    public void answer(long timestamp) {
        call.startTimestamp = timestamp;
        call.state = new InProgressState(call);
    }

    @Override
    public void resume(long timestamp) {
        throw new RuntimeException();

    }

    @Override
    public void end(long timestamp) {
        call.startTimestamp = timestamp;
        call.endTimestamp = timestamp;
        call.duration = 0;
    }
}

class InProgressState extends State {

    public InProgressState(Call call) {
        super(call);
    }

    @Override
    public void hold(long timestamp) {
        call.holdTimestamp = timestamp;
        call.state = new PausedState(call);
    }

    @Override
    public void answer(long timestamp) {
        throw new RuntimeException();

    }

    @Override
    public void resume(long timestamp) {
        throw new RuntimeException();

    }

    @Override
    public void end(long timestamp) {
        call.endTimestamp = timestamp;
        if (call.holdTimestamp != -1)
        {
            call.totalHoldtime += timestamp - call.holdTimestamp;
        }
        call.duration = call.endTimestamp - call.totalHoldtime - call.startTimestamp;

        call.state = new IdleState(call);
    }
}

class PausedState extends State {

    public PausedState(Call call) {
        super(call);
    }

    @Override
    public void hold(long timestamp) {
        throw new RuntimeException();
    }

    @Override
    public void answer(long timestamp) {
        throw new RuntimeException();

    }

    @Override
    public void resume(long timestamp) {
        call.totalHoldtime += timestamp - call.holdTimestamp;
        call.holdTimestamp = -1;
        call.state = new InProgressState(call);
    }

    @Override
    public void end(long timestamp) {
        call.endTimestamp = timestamp;
        if (call.holdTimestamp != -1)
        {
            call.totalHoldtime += timestamp - call.holdTimestamp;
        }
        call.duration = call.endTimestamp - call.totalHoldtime - call.startTimestamp;

        call.state = new IdleState(call);
    }
}

class IdleState extends State {

    public IdleState(Call call) {
        super(call);
    }

    @Override
    public void hold(long timestamp) {
        throw new RuntimeException();
    }

    @Override
    public void answer(long timestamp) {
        throw new RuntimeException();

    }

    @Override
    public void resume(long timestamp) {
        throw new RuntimeException();

    }

    @Override
    public void end(long timestamp) {
        throw new RuntimeException();

    }
}

class Call {
    private String uuid;
    private String dialer;
    private String reciever;
    private long timestamp;

    //timetracking
    long startTimestamp;
    long totalHoldtime = 0;
    long holdTimestamp = -1;
    long endTimestamp;

    long duration = 0;
    State state = new RingingState(this);

    public Call(String uuid, String dialer, String reciever, long timestamp) {
        this.uuid = uuid;
        this.dialer = dialer;
        this.reciever = reciever;
        this.timestamp = timestamp;
        this.startTimestamp = timestamp;
    }

    public void update(String action, long timestamp) {
        Action enumerated = Action.valueOf(action);
        if (enumerated == Action.ANSWER) {
            state.answer(timestamp);
        } else if (enumerated == Action.END) {
            state.end(timestamp);
        } else if (enumerated == Action.HOLD) {
            state.hold(timestamp);
        } else if (enumerated == Action.RESUME) {
            state.resume(timestamp);
        }
    }

    public String getDialer() {
        return dialer;
    }

    public String getReciever() {
        return reciever;
    }

    public long getTimestamp() {
        return timestamp;
    }

    public long getDuration() {
        return duration;
    }
}

class TelcoApp {
    private Map<String, Call> calls;

    public TelcoApp() {
        calls = new TreeMap<>();
    }

    void addCall(String uuid, String dialer, String receiver, long timestamp) {
        calls.put(uuid, new Call(uuid, dialer, receiver, timestamp));
    }

    void updateCall(String uuid, long timestamp, String action) {
        calls.get(uuid).update(action, timestamp);
    }

    void printChronologicalReport(String phoneNumber) {
        calls.values().stream().filter(x -> x.getDialer().equals(phoneNumber) || x.getReciever().equals(phoneNumber))
                .sorted(Comparator.comparing(Call::getTimestamp)).forEach(x -> System.out.printf("%s %s %d %s %s\n", x.getReciever().equals(phoneNumber) ? "R" : "D",
                        x.getReciever().equals(phoneNumber) ? x.getDialer() : x.getReciever(), x.startTimestamp, x.endTimestamp != x.startTimestamp ? x.endTimestamp : "MISSED CALL", DurationConverter.convert(x.duration)));
    }

    void printReportByDuration(String phoneNumber) {
        calls.values().stream().filter(x -> x.getDialer().equals(phoneNumber) || x.getReciever().equals(phoneNumber))
                .sorted(Comparator.comparing(Call::getDuration).thenComparing(Call::getTimestamp).reversed()).forEach(x -> System.out.printf("%s %s %d %s %s\n", x.getReciever().equals(phoneNumber) ? "R" : "D",
                        x.getReciever().equals(phoneNumber) ? x.getDialer() : x.getReciever(), x.startTimestamp, x.endTimestamp != x.startTimestamp ? x.endTimestamp : "MISSED CALL", DurationConverter.convert(x.duration)));
    }

    void printCallsDuration() {
        Map<String, Long> callMap = new TreeMap<>();

        for (Call call : calls.values()) {
            callMap.put(call.getDialer() + " <-> " + call.getReciever(), calls.values().stream().filter(x -> x.getDialer().equals(call.getDialer()) && x.getReciever().equals(call.getReciever())).mapToLong(Call::getDuration).sum());
        }
        Comparator<Map.Entry<String, Long>> c = Comparator.comparing(Map.Entry::getValue);
        callMap.entrySet().stream().sorted(c.reversed()).forEach(x -> System.out.printf("%s : %s\n", x.getKey(), DurationConverter.convert(x.getValue())));
    }
}

public class TelcoTest2 {
    public static void main(String[] args) {
        TelcoApp app = new TelcoApp();

        Scanner sc = new Scanner(System.in);

        while (sc.hasNextLine()) {
            String line = sc.nextLine();
            String[] parts = line.split("\\s+");
            String command = parts[0];

            if (command.equals("addCall")) {
                String uuid = parts[1];
                String dialer = parts[2];
                String receiver = parts[3];
                long timestamp = Long.parseLong(parts[4]);
                app.addCall(uuid, dialer, receiver, timestamp);
            } else if (command.equals("updateCall")) {
                String uuid = parts[1];
                long timestamp = Long.parseLong(parts[2]);
                String action = parts[3];
                app.updateCall(uuid, timestamp, action);
            } else if (command.equals("printChronologicalReport")) {
                String phoneNumber = parts[1];
                app.printChronologicalReport(phoneNumber);
            } else if (command.equals("printReportByDuration")) {
                String phoneNumber = parts[1];
                app.printReportByDuration(phoneNumber);
            } else {
                app.printCallsDuration();
            }
        }

    }
}
