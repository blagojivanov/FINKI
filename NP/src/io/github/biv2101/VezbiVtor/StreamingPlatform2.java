package io.github.biv2101.VezbiVtor;

import java.util.*;
import java.util.stream.Collectors;

class CosineSimilarityCalculator {

    public static double cosineSimilarity(Map<String, Integer> c1, Map<String, Integer> c2) {
        return cosineSimilarity(c1.values(), c2.values());
    }

    public static double cosineSimilarity(Collection<Integer> c1, Collection<Integer> c2) {
        int[] array1;
        int[] array2;
        array1 = c1.stream().mapToInt(i -> i).toArray();
        array2 = c2.stream().mapToInt(i -> i).toArray();
        double up = 0.0;
        double down1 = 0, down2 = 0;

        for (int i = 0; i < c1.size(); i++) {
            up += (array1[i] * array2[i]);
        }

        for (int i = 0; i < c1.size(); i++) {
            down1 += (array1[i] * array1[i]);
        }

        for (int i = 0; i < c1.size(); i++) {
            down2 += (array2[i] * array2[i]);
        }

        return up / (Math.sqrt(down1) * Math.sqrt(down2));
    }
}

class SPUser {
    String id;
    String username;
    Map<String, Integer> movieRatings;

    public SPUser(String id, String username) {
        this.id = id;
        this.username = username;
        movieRatings = new TreeMap<>();
    }

    public void fillMap(Map<String, SPMovie> movies) {
        movies.keySet().forEach(x -> movieRatings.putIfAbsent(x, 0));
    }

    List<String> favMovie(Map<String, SPMovie> map) {
        Comparator<Map.Entry<String, Integer>> c = Comparator.comparing(Map.Entry::getValue);
        Comparator<Map.Entry<String, Integer>> comparator = new Comparator<Map.Entry<String, Integer>>() {
            @Override
            public int compare(Map.Entry<String, Integer> o1, Map.Entry<String, Integer> o2) {
                return Double.compare(map.get(o1.getKey()).getAvg(), map.get(o2.getKey()).getAvg());
            }
        };
        int max = movieRatings.values().stream().mapToInt(y -> y).max().orElse(0);
        return movieRatings.entrySet().stream().filter(x -> x.getValue() == max).sorted(c.thenComparing(comparator).reversed()).map(Map.Entry::getKey).collect(Collectors.toList());
    }

    public double cosCalc(SPUser other)
    {
        return CosineSimilarityCalculator.cosineSimilarity(movieRatings, other.movieRatings);
    }

    @Override
    public String toString() {
        return String.format("User ID: %s Name: %s", id, username);
    }
}

class SPMovie {
    String id;
    String name;
    List<Integer> ratings;

    public SPMovie(String id, String name) {
        this.id = id;
        this.name = name;
        ratings = new ArrayList<>();
    }

    public double getAvg() {
        return ratings.stream().mapToInt(x -> x).average().orElse(0.0);
    }

    @Override
    public String toString() {
        return String.format("Movie ID: %s Title: %s Rating: %.2f", id, name, getAvg());
    }
}

class StreamingPlatform {
    Map<String, SPMovie> movies;
    Map<String, SPUser> users;

    public StreamingPlatform() {
        movies = new TreeMap<>();
        users = new HashMap<>();
    }

    void addMovie(String id, String name) {
        movies.put(id, new SPMovie(id, name));
    }

    void addUser(String id, String username) {
        users.put(id, new SPUser(id, username));
    }

    void addRating(String userId, String movieId, int rating) {
        movies.get(movieId).ratings.add(rating);
        users.get(userId).movieRatings.put(movieId, rating);
    }

    void topNMovies(int n) {

        movies.values().stream().sorted(Comparator.comparing(SPMovie::getAvg).reversed()).limit(n).forEach(System.out::println);
    }

    void favouriteMoviesForUsers(List<String> userIds) {
        users.entrySet().stream().filter(x -> userIds.contains(x.getKey())).map(Map.Entry::getValue)
                .forEach(x ->
                {
                    System.out.println(x);
                    x.favMovie(movies).forEach(y -> System.out.println(movies.get(y)));
                    System.out.println();
                });
    }

    void similarUsers(String userId) {
        users.values().stream().forEach(x -> x.fillMap(movies));

        Comparator<SPUser> comparator = new Comparator<SPUser>() {
            @Override
            public int compare(SPUser o1, SPUser o2) {
                return Double.compare(users.get(userId).cosCalc(o1), users.get(userId).cosCalc(o2));
            }
        };
        users.values().stream().sorted(comparator.reversed()).skip(1).forEach(x-> System.out.println(x + " " + users.get(userId).cosCalc(x)));

    }
}

public class StreamingPlatform2 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        StreamingPlatform sp = new StreamingPlatform();

        while (sc.hasNextLine()) {
            String line = sc.nextLine();
            String[] parts = line.split("\\s+");

            if (parts[0].equals("addMovie")) {
                String id = parts[1];
                String name = Arrays.stream(parts).skip(2).collect(Collectors.joining(" "));
                sp.addMovie(id, name);
            } else if (parts[0].equals("addUser")) {
                String id = parts[1];
                String name = parts[2];
                sp.addUser(id, name);
            } else if (parts[0].equals("addRating")) {
                //String userId, String movieId, int rating
                String userId = parts[1];
                String movieId = parts[2];
                int rating = Integer.parseInt(parts[3]);
                sp.addRating(userId, movieId, rating);
            } else if (parts[0].equals("topNMovies")) {
                int n = Integer.parseInt(parts[1]);
                System.out.println("TOP " + n + " MOVIES:");
                sp.topNMovies(n);
            } else if (parts[0].equals("favouriteMoviesForUsers")) {
                List<String> users = Arrays.stream(parts).skip(1).collect(Collectors.toList());
                System.out.println("FAVOURITE MOVIES FOR USERS WITH IDS: " + users.stream().collect(Collectors.joining(", ")));
                sp.favouriteMoviesForUsers(users);
            } else if (parts[0].equals("similarUsers")) {
                String userId = parts[1];
                System.out.println("SIMILAR USERS TO USER WITH ID: " + userId);
                sp.similarUsers(userId);
            }
        }
    }
}
