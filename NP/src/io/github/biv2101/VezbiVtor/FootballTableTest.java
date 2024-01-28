package io.github.biv2101.VezbiVtor;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.*;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

/**
 * Partial exam II 2016/2017
 */

class Game {

    private String homeTeam;
    private String awayTeam;
    private int homeGoals;
    private int awayGoals;

    public String getHomeTeam() {
        return homeTeam;
    }

    public String getAwayTeam() {
        return awayTeam;
    }

    public int getHomeGoals() {
        return homeGoals;
    }

    public int getAwayGoals() {
        return awayGoals;
    }

    public Game(String homeTeam, String awayTeam, int homeGoals, int awayGoals) {
        this.homeTeam = homeTeam;
        this.awayTeam = awayTeam;
        this.homeGoals = homeGoals;
        this.awayGoals = awayGoals;
    }
}

class Team {
    private String name;
    private List<Game> games;

    public Team(String name) {
        this.name = name;
        games = new ArrayList<>();
    }

    public List<Game> getGames() {
        return games;
    }

    public int getWins() {
        return (int) games.stream().filter(x -> (x.getHomeTeam().equals(name) && x.getHomeGoals() > x.getAwayGoals())
                || (x.getAwayTeam().equals(name) && x.getAwayGoals() > x.getHomeGoals())).count();
    }

    public int getDraws() {
        return (int) games.stream().filter(x -> (x.getHomeTeam().equals(name) && x.getHomeGoals() == x.getAwayGoals())
                || (x.getAwayTeam().equals(name) && x.getAwayGoals() == x.getHomeGoals())).count();
    }

    public int getLosses() {
        return (int) (games.stream().filter(x -> (x.getHomeTeam().equals(name) && x.getHomeGoals() < x.getAwayGoals())
                || (x.getAwayTeam().equals(name) && x.getAwayGoals() < x.getHomeGoals())).count());
    }

    public int getPoints() {
        return getWins() * 3 + getDraws();
    }

    public int goalDiff() {
        return games.stream().filter(x -> (x.getHomeTeam().equals(name))).mapToInt(Game::getHomeGoals).sum() +
                games.stream().filter(x -> (x.getAwayTeam().equals(name))).mapToInt(Game::getAwayGoals).sum() -
                games.stream().filter(x -> (!x.getHomeTeam().equals(name))).mapToInt(Game::getHomeGoals).sum() -
                games.stream().filter(x -> (!x.getAwayTeam().equals(name))).mapToInt(Game::getAwayGoals).sum();
    }

    public String getName() {
        return name;
    }

    @Override
    public String toString() {
        return String.format("%-15s%5d%5d%5d%5d%5d", name, games.size(), getWins(), getDraws(), getLosses(), getPoints());
    }
}

class FootballTable {

    private Map<String, Team> teams;

    public FootballTable()
    {
        teams = new HashMap<>();
    }

    public void addGame(String homeTeam, String awayTeam, int homeGoals, int awayGoals) {
        teams.computeIfAbsent(homeTeam, x -> new Team(homeTeam)).getGames().add(new Game(homeTeam, awayTeam, homeGoals, awayGoals));
        teams.computeIfAbsent(awayTeam, x -> new Team(awayTeam)).getGames().add(new Game(homeTeam, awayTeam, homeGoals, awayGoals));
    }

    public void printTable() {
        List<Team> teamslist = teams.values().stream().sorted(Comparator.comparing(Team::getPoints).thenComparing(Team::goalDiff).reversed().thenComparing(Team::getName)).collect(Collectors.toList());
        IntStream.range(0, teamslist.size()).forEach(i -> System.out.printf("%2d. %s\n", i + 1, teamslist.get(i)));
    }
}

public class FootballTableTest {
    public static void main(String[] args) throws IOException {
        FootballTable table = new FootballTable();
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        reader.lines()
                .map(line -> line.split(";"))
                .forEach(parts -> table.addGame(parts[0], parts[1],
                        Integer.parseInt(parts[2]),
                        Integer.parseInt(parts[3])));
        reader.close();
        System.out.println("=== TABLE ===");
        System.out.printf("%-19s%5s%5s%5s%5s%5s\n", "Team", "P", "W", "D", "L", "PTS");
        table.printTable();
    }
}

// Your code here

