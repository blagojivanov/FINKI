package io.github.biv2101.VezbiVtor;

import java.util.*;
import java.util.concurrent.ConcurrentMap;
import java.util.stream.Collectors;

enum LogType {
    INFO, WARN, ERROR
}

class Microservice {
    private String msname;
    private String message;
    private int timestamp;
    private LogType type;

    public Microservice(String line) {
        String[] lp = line.split("\\s+");
        this.type = LogType.valueOf(lp[2]);
        this.message = "";
        msname = lp[1];
        for (int i = 3; i < lp.length; i++) {
            message = message.concat(lp[i]).concat(" ");
        }
        timestamp = Integer.parseInt(lp[lp.length - 1]);

    }

    public String getMsname() {
        return msname;
    }

    public int getTimestamp() {
        return timestamp;
    }

    public int getSeverity() {
        if (type == LogType.INFO)
            return 0;
        if (type == LogType.WARN) {
            if (message.toLowerCase().contains("might cause error")) {
                return 2;
            }
            return 1;
        }
        int toret = 3;
        if (message.toLowerCase().contains("exception")) {
            toret += 3;
        }
        if (message.toLowerCase().contains("fatal")) {
            toret += 2;
        }
        return toret;
    }

    public String getMessage() {
        return message;
    }

    public LogType getType() {
        return type;
    }

    @Override
    public String toString() {
        return "Microservice{" +
                "msname='" + msname + '\'' +
                ", message='" + message + '\'' +
                ", timestamp=" + timestamp +
                ", type=" + type +
                '}';
    }
}

class Log {
    private String service;
    private List<Microservice> microservices;

    public void addMicro(String line) {
        microservices.add(new Microservice(line));
    }

    public Log(String line) {
        String[] lp = line.split("\\s+");
        service = lp[0];
        microservices = new ArrayList<>();
    }

    public double avgSeverity() {
        return microservices.stream().mapToInt(x -> x.getSeverity()).average().orElse(0);
    }

    public int getBySeverity(int sev) {
        return (int) microservices.stream().filter(x -> x.getSeverity() == sev).count();
    }

    public String getService() {
        return service;
    }

    public List<Microservice> getMicroservices() {
        return microservices;
    }


    @Override
    public String toString() {
        int numMicro = microservices.stream().map(Microservice::getMsname).collect(Collectors.toSet()).size();
        return String.format("Service name: %s Count of microservices: %d Total logs in service: %d Average severity for all logs: %.2f Average number of logs per microservice: %.2f",
                service,
                numMicro,
                microservices.size(),
                avgSeverity(),
                microservices.size() / (double) numMicro);
    }
}

class LogCollector {

    private Map<String, Log> logs;

    public LogCollector() {
        logs = new HashMap<>();
    }

    public void addLog(String line) {
        String[] lp = line.split("\\s+");
        logs.putIfAbsent(lp[0], new Log(line));
        logs.get(lp[0]).addMicro(line);
    }

    void printServicesBySeverity() {
        logs.values().stream().sorted(Comparator.comparing(Log::avgSeverity).reversed()).forEach(System.out::println);
    }

    Map<Integer, Integer> getSeverityDistribution(String service, String microservice) {
        Map<Integer, Integer> result = new HashMap<>();
        if (microservice != null) {
            logs.get(service).getMicroservices().stream().filter(ms -> ms.getMsname().equals(microservice)).forEach(y -> result.compute(y.getSeverity(), (key, value) -> value == null ? 1 : value + 1));
            return result;
        }

        logs.get(service).getMicroservices().stream().forEach(y -> result.compute(y.getSeverity(), (key, value) -> value == null ? 1 : value + 1));
        return result;
    }

    public void displayLogs(String service, String microservice, String order) {
        List<Microservice> list = new ArrayList<>();
        logs.values().stream().filter(x -> x.getService().equals(service)).forEach(x -> list.addAll(x.getMicroservices()));
        Comparator<Microservice> c = new Comparator<Microservice>() {
            @Override
            public int compare(Microservice o1, Microservice o2) {
                if (order.equalsIgnoreCase("newest_first")) {
                    return Integer.compare(o2.getTimestamp(), o1.getTimestamp());
                } else if (order.equalsIgnoreCase("OLDEST_FIRST")) {
                    return Integer.compare(o1.getTimestamp(), o2.getTimestamp());
                } else if (order.equalsIgnoreCase("MOST_SEVERE_FIRST")) {
                    return Integer.compare(o2.getSeverity(), o1.getSeverity());
                } else if (order.equalsIgnoreCase("LEAST_SEVERE_FIRST")) {
                    return Integer.compare(o1.getSeverity(), o2.getSeverity());
                }
                return 0;
            }
        };

        Comparator<Microservice> cTSasc = Comparator.comparing(Microservice::getTimestamp); // oldest -> newest
        Comparator<Microservice> cSEasc = Comparator.comparing(Microservice::getSeverity).thenComparing(Microservice::getTimestamp).reversed(); // least -> most

        Comparator<Microservice> finalComp = Comparator.comparing(Microservice::getTimestamp);

        if (order.equalsIgnoreCase("newest_first")) {
            finalComp = cTSasc.reversed();
        } else if (order.equalsIgnoreCase("OLDEST_FIRST")) {
            finalComp = cTSasc;
        } else if (order.equalsIgnoreCase("MOST_SEVERE_FIRST")) {
            finalComp = cSEasc;
        } else if (order.equalsIgnoreCase("LEAST_SEVERE_FIRST")) {
            finalComp = cSEasc.reversed();
        }

        if (microservice != null) {
            list.stream().filter(x -> x.getMsname().equals(microservice)).sorted(c.thenComparing(finalComp)).forEach(x -> System.out.printf("%s|%s [%s] %sT:%d\n", service, microservice, x.getType().toString(), x.getMessage(), x.getTimestamp()));
        } else {
            list.stream().sorted(finalComp).forEach(x -> System.out.printf("%s|%s [%s] %sT:%d\n", service, x.getMsname(), x.getType().toString(), x.getMessage(), x.getTimestamp()));
        }
        //service2|microservice1 [ERROR] Log message 3. 355 T:355
    }

}

public class LogsTester {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        LogCollector collector = new LogCollector();
        while (sc.hasNextLine()) {
            String line = sc.nextLine();
            if (line.startsWith("addLog")) {
                collector.addLog(line.replace("addLog ", ""));
            } else if (line.startsWith("printServicesBySeverity")) {
                collector.printServicesBySeverity();
            } else if (line.startsWith("getSeverityDistribution")) {
                String[] parts = line.split("\\s+");
                String service = parts[1];
                String microservice = null;
                if (parts.length == 3) {
                    microservice = parts[2];
                }
                collector.getSeverityDistribution(service, microservice).forEach((k, v) -> System.out.printf("%d -> %d%n", k, v));
            } else if (line.startsWith("displayLogs")) {
                String[] parts = line.split("\\s+");
                String service = parts[1];
                String microservice = null;
                String order = null;
                if (parts.length == 4) {
                    microservice = parts[2];
                    order = parts[3];
                } else {
                    order = parts[2];
                }
                System.out.println(line);

                collector.displayLogs(service, microservice, order);
            }
        }
    }
}