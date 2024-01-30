package io.github.biv2101.VezbiVtor;

//package mk.ukim.finki.midterm;


import java.time.Duration;
import java.time.LocalDateTime;
import java.util.*;
import java.util.stream.Collectors;

enum Action {
    ANSWER, HOLD, RESUME, END
}

enum State {
    IDLE, RINGING, PROGRESS, PAUSED
}

class DurationConverter {
    public static String convert(long duration) {
        long minutes = duration / 60;
        duration %= 60;
        return String.format("%02d:%02d", minutes, duration);
    }
}

class StateP {
    private State state;
    private long timestamp;

    public long getTimestamp() {
        return timestamp;
    }

    public StateP(State state, long timestamp) {
        this.state = state;
        this.timestamp = timestamp;
    }

    public State getState() {
        return state;
    }
}

class Call {
    private String uuid;
    private String dialer;
    private String reciever;
    private long timestamp;

    private List<StateP> states;


    public Call(String uuid, String dialer, String reciever, long timestamp) {
        this.uuid = uuid;
        this.dialer = dialer;
        this.reciever = reciever;
        this.timestamp = timestamp;
        states = new ArrayList<>();
        states.add(new StateP(State.RINGING, timestamp));
    }

    public void update(String action, long timestamp) {
        Action enumerated = Action.valueOf(action);
        if (states.get(states.size() - 1).getState() == State.IDLE) {
            if (enumerated == Action.ANSWER) {
                states.add(new StateP(State.RINGING, timestamp));
            }
        } else if (states.get(states.size() - 1).getState() == State.RINGING) {
            if (enumerated == Action.ANSWER) {
                states.add(new StateP(State.PROGRESS, timestamp));
            } else if (enumerated == Action.END) {
                states.add(new StateP(State.IDLE, timestamp));
            }
        } else if (states.get(states.size() - 1).getState() == State.PROGRESS) {
            if (enumerated == Action.HOLD) {
                states.add(new StateP(State.PAUSED, timestamp));
            } else if (enumerated == Action.END) {
                states.add(new StateP(State.IDLE, timestamp));
            }
        } else if (states.get(states.size() - 1).getState() == State.PAUSED) {
            if (enumerated == Action.RESUME) {
                states.add(new StateP(State.PROGRESS, timestamp));
            } else if (enumerated == Action.END) {
                states.add(new StateP(State.IDLE, timestamp));
            }
        }
    }

    public StateP callStart() {

        if (callDuration() == 0) {
            return states.stream().filter(x -> x.getState() == State.IDLE).findFirst().orElse(null);
        }
        return states.stream().filter(x -> x.getState() == State.PROGRESS).findFirst().orElse(null);
    }

    public StateP callEnd() {
        if (callDuration() == 0) {
            return new StateP(State.IDLE, 0);
        }
        return states.stream().filter(x -> x.getState() == State.IDLE).findFirst().orElse(null);
    }

    public long callDuration() {
        Queue<StateP> stateq = new LinkedList<>(states);

        long totalDuration = 0;
        while (!stateq.isEmpty()) {
            StateP curr = stateq.poll();
            if (curr.getState() == State.PROGRESS) {
                StateP next = stateq.poll();
                totalDuration += next.getTimestamp() - curr.getTimestamp();
            } else if (curr.getState() == State.RINGING) {
                if (stateq.peek().getState() == State.IDLE) {
                    return 0;
                }
            }
        }
        return totalDuration;
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
                        x.getReciever().equals(phoneNumber) ? x.getDialer() : x.getReciever(), x.callStart().getTimestamp(), x.callEnd().getTimestamp() != 0 ? x.callEnd().getTimestamp() : "MISSED CALL", DurationConverter.convert(x.callDuration())));
    }

    void printReportByDuration(String phoneNumber) {
        calls.values().stream().filter(x -> x.getDialer().equals(phoneNumber) || x.getReciever().equals(phoneNumber))
                .sorted(Comparator.comparing(Call::callDuration).thenComparing(Call::getTimestamp).reversed()).forEach(x -> System.out.printf("%s %s %d %s %s\n", x.getReciever().equals(phoneNumber) ? "R" : "D",
                        x.getReciever().equals(phoneNumber) ? x.getDialer() : x.getReciever(), x.callStart().getTimestamp(), x.callEnd().getTimestamp() != 0 ? x.callEnd().getTimestamp() : "MISSED CALL", DurationConverter.convert(x.callDuration())));
    }

    void printCallsDuration() {
        Map<String, Long> callMap = new TreeMap<>();

        for (Call call : calls.values()) {
            callMap.put(call.getDialer() + " <-> " + call.getReciever(), calls.values().stream().filter(x -> x.getDialer().equals(call.getDialer()) && x.getReciever().equals(call.getReciever())).mapToLong(Call::callDuration).sum());
        }
        Comparator<Map.Entry<String, Long>> c = Comparator.comparing(Map.Entry::getValue);
        callMap.entrySet().stream().sorted(c.reversed()).forEach(x->System.out.printf("%s : %s\n", x.getKey(), DurationConverter.convert(x.getValue())));
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
