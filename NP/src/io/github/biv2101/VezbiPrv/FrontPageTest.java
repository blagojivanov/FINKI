package io.github.biv2101.VezbiPrv;

import java.time.Duration;
import java.time.LocalDateTime;
import java.util.*;
import java.util.concurrent.TimeUnit;
import java.util.stream.Collectors;

class CategoryNotFoundException extends Exception {
    private String name;

    public CategoryNotFoundException(String name) {
        this.name = name;
    }

    @Override
    public String getMessage() {
        return "Category " + name + " was not found";
    }
}

class Category {
    private String name;

    public Category(String name) {
        this.name = name;
    }

    public String getName() {
        return name;
    }
}

abstract class NewsItem {
    public NewsItem(String title, Date date, Category category) {
        this.title = title;
        this.date = date;
        this.category = category;
    }

    protected String title;
    protected Date date;
    protected Category category;

    public Category getCategory() {
        return category;
    }

    abstract public String getTeaser();
}


class TextNewsItem extends NewsItem {
    private String text;

    public TextNewsItem(String title, Date date, Category category, String text) {
        super(title, date, category);
        this.text = text;
    }

    @Override
    public String getTeaser() {
        Duration d = Duration.between(date.toInstant(),Calendar.getInstance().getTime().toInstant());
        return String.format("%s\n%d\n%s\n", title, d.toMinutes(), text.substring(0, Math.min(80, text.length())));
    }

    @Override
    public String toString() {
        return getTeaser();
    }
}

class MediaNewsItem extends NewsItem {
    private String url;
    private int views;

    public MediaNewsItem(String title, Date date, Category category, String url, int views) {
        super(title, date, category);
        this.url = url;
        this.views = views;
    }


    @Override
    public String getTeaser() {
        Duration d = Duration.between(date.toInstant(),Calendar.getInstance().getTime().toInstant());
        return String.format("%s\n%d\n%s\n%d\n", title, d.toMinutes(), url, views);
    }

    @Override
    public String toString() {
        return getTeaser();
    }
}

class FrontPage {
    private List<NewsItem> newsItemList;
    private Category[] categories;

    public FrontPage(Category[] categories) {
        this.categories = Arrays.copyOf(categories, categories.length);
        this.newsItemList = new ArrayList<>();
    }

    public void addNewsItem(NewsItem news) {
        newsItemList.add(news);
    }

    public List<NewsItem> listByCategory(Category c) {

        return newsItemList.stream().filter(ni -> ni.getCategory() == c).collect(Collectors.toList());

    }

    public List<NewsItem> listByCategoryName(String catname) throws CategoryNotFoundException {
        if (Arrays.stream(categories).filter(c -> c.getName().equals(catname)).count() == 0)
            throw new CategoryNotFoundException(catname);
        return newsItemList.stream().filter(ni -> ni.getCategory().getName().equals(catname)).collect(Collectors.toList());
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        newsItemList.forEach(sb::append);
        return sb.toString();
    }
}

public class FrontPageTest {
    public static void main(String[] args) {
        // Reading
        Scanner scanner = new Scanner(System.in);
        String line = scanner.nextLine();
        String[] parts = line.split(" ");
        Category[] categories = new Category[parts.length];
        for (int i = 0; i < categories.length; ++i) {
            categories[i] = new Category(parts[i]);
        }
        int n = scanner.nextInt();
        scanner.nextLine();
        FrontPage frontPage = new FrontPage(categories);
        Calendar cal = Calendar.getInstance();
        for (int i = 0; i < n; ++i) {
            String title = scanner.nextLine();
            cal = Calendar.getInstance();
            int min = scanner.nextInt();
            cal.add(Calendar.MINUTE, -min);
            Date date = cal.getTime();
            scanner.nextLine();
            String text = scanner.nextLine();
            int categoryIndex = scanner.nextInt();
            scanner.nextLine();
            TextNewsItem tni = new TextNewsItem(title, date, categories[categoryIndex], text);
            frontPage.addNewsItem(tni);
        }

        n = scanner.nextInt();
        scanner.nextLine();
        for (int i = 0; i < n; ++i) {
            String title = scanner.nextLine();
            int min = scanner.nextInt();
            cal = Calendar.getInstance();
            cal.add(Calendar.MINUTE, -min);
            scanner.nextLine();
            Date date = cal.getTime();
            String url = scanner.nextLine();
            int views = scanner.nextInt();
            scanner.nextLine();
            int categoryIndex = scanner.nextInt();
            scanner.nextLine();
            MediaNewsItem mni = new MediaNewsItem(title, date, categories[categoryIndex], url, views);
            frontPage.addNewsItem(mni);
        }
        // Execution
        String category = scanner.nextLine();
        System.out.println(frontPage);
        for (Category c : categories) {
            System.out.println(frontPage.listByCategory(c).size());
        }
        try {
            System.out.println(frontPage.listByCategoryName(category).size());
        } catch (CategoryNotFoundException e) {
            System.out.println(e.getMessage());
        }
    }
}


// Vasiot kod ovde