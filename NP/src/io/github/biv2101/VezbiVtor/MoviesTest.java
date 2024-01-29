package io.github.biv2101.VezbiVtor;

import java.util.*;
import java.util.stream.Collectors;

class Movie {
    private String title;
    private List<Integer> ratings;

    public String getTitle() {
        return title;
    }

    public Movie(String title, int[] ratings) {
        this.title = title;
        this.ratings = Arrays.stream(ratings).boxed().collect(Collectors.toList());
    }

    public double avgRating() {
        return ratings.stream().mapToDouble(x -> x).average().orElse(0);
    }

    public double ratingCoef() {
        return avgRating() * ratings.size() / MoviesList.maxRatings;
    }

    @Override
    public String toString() {
        return String.format("%s (%.2f) of %d ratings", title, avgRating(), ratings.size());
    }
}

class MoviesList {
    private List<Movie> movies;
    public static int maxRatings;

    public MoviesList() {
        movies = new ArrayList<>();
    }

    public void addMovie(String title, int[] ratings) {
        movies.add(new Movie(title, ratings));
        maxRatings = Math.max(maxRatings, ratings.length);
    }

    public List<Movie> top10ByAvgRating() {
        return movies.stream().sorted(Comparator.comparing(Movie::avgRating).reversed().thenComparing(Movie::getTitle)).limit(10).collect(Collectors.toList());
    }

    public List<Movie> top10ByRatingCoef() {
        return movies.stream().sorted(Comparator.comparing(Movie::ratingCoef).reversed().thenComparing(Movie::getTitle)).limit(10).collect(Collectors.toList());
    }

}

public class MoviesTest {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        MoviesList moviesList = new MoviesList();
        int n = scanner.nextInt();
        scanner.nextLine();
        for (int i = 0; i < n; ++i) {
            String title = scanner.nextLine();
            int x = scanner.nextInt();
            int[] ratings = new int[x];
            for (int j = 0; j < x; ++j) {
                ratings[j] = scanner.nextInt();
            }
            scanner.nextLine();
            moviesList.addMovie(title, ratings);
        }
        scanner.close();
        List<Movie> movies = moviesList.top10ByAvgRating();
        System.out.println("=== TOP 10 BY AVERAGE RATING ===");
        for (Movie movie : movies) {
            System.out.println(movie);
        }
        movies = moviesList.top10ByRatingCoef();
        System.out.println("=== TOP 10 BY RATING COEFFICIENT ===");
        for (Movie movie : movies) {
            System.out.println(movie);
        }
    }
}

// vashiot kod ovde