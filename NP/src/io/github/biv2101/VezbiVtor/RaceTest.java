package io.github.biv2101.VezbiVtor;

import java.io.*;
import java.sql.Time;
import java.time.Duration;
import java.time.LocalDateTime;
import java.time.LocalTime;
import java.util.ArrayList;
import java.util.List;
import java.util.stream.Collectors;

class Runner implements Comparable<Runner> {
    Duration duration;
    int id;

    public Runner(String line) {
        String[] split = line.split("\\s+");
        id = Integer.parseInt(split[0]);
        LocalTime parse1 = LocalTime.parse(split[1]);
        LocalTime parse2 = LocalTime.parse(split[2]);
        duration = Duration.between(parse1, parse2);
    }

    @Override
    public String toString() {

        return String.format("%d %02d:%02d:%02d", id, duration.toHoursPart(), duration.toMinutes(), duration.toSecondsPart());
    }

    @Override
    public int compareTo(Runner o) {
        return duration.compareTo(o.duration);
    }
}

class TeamRace {

    static void findBestTeam(InputStream is, OutputStream os) throws IOException {
        PrintStream ps = new PrintStream(os);
        BufferedReader br = new BufferedReader(new InputStreamReader(is));
        List<Runner> runnerList = br.lines().map(Runner::new).collect(Collectors.toList());

        runnerList.stream().sorted().limit(4).forEach(ps::println);
        Duration duration = Duration.ofSeconds(runnerList.stream().sorted().limit(4).mapToInt(x -> Math.toIntExact(x.duration.toSeconds())).sum());
        System.out.printf("%02d:%02d:%02d", duration.toHoursPart(), duration.toMinutesPart(), duration.toSecondsPart());

        br.close();
    }
}

public class RaceTest {
    public static void main(String[] args) {
        try {
            TeamRace.findBestTeam(System.in, System.out);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }
}