package io.github.biv2101.VezbiVtor;

import java.time.LocalDateTime;
import java.util.*;
import java.util.stream.Collectors;

/**
 * Partial exam II 2016/2017
 */

class File implements Comparable<File>
{
    private String name;
    private int size;
    private LocalDateTime date;

    public File(String name, int size, LocalDateTime date) {
        this.name = name;
        this.size = size;
        this.date = date;
    }

    public String getName() {
        return name;
    }

    public int getSize() {
        return size;
    }

    public LocalDateTime getDate() {
        return date;
    }

    @Override
    public String toString() {
        return String.format("%-10s %5dB %s", name, size, date);
    }

    @Override
    public int compareTo(File o) {
        if (date.compareTo(o.date) != 0)
        {
            return date.compareTo(o.date);
        }
        if (name.compareTo(o.name) != 0)
        {
            return name.compareTo(o.name);
        }
        return Integer.compare(size, o.size);
    }
}
class FileSystem
{
    private Map<Character, SortedSet<File>> files;

    public FileSystem() {
        this.files = new HashMap<>();
    }

    public void addFile(char folder, String name, int size, LocalDateTime createdAt)
    {
        if (files.containsKey(folder))
        {
            files.get(folder).add(new File(name, size, createdAt));
            return;
        }
        SortedSet<File> set = new TreeSet<>();
        set.add(new File(name, size, createdAt));
        files.put(folder,set);
    }

    public List<File> findAllHiddenFilesWithSizeLessThen(int size)
    {
        List<File> result = new ArrayList<>();
        for (Map.Entry<Character, SortedSet<File>> file : files.entrySet())
        {
            if (file.getKey() == '.')
            {
                result.addAll(file.getValue().stream().filter(f->f.getSize()<size).collect(Collectors.toList()));
                continue;
            }
            file.getValue().stream().filter(f -> f.getName().startsWith(".") && f.getSize()<size).forEach(result::add);
        }
        return result;
    }

    public int totalSizeOfFilesFromFolders(List<Character> folders)
    {
        return folders.stream().filter(x->files.containsKey(x)).mapToInt(f -> files.get(f).stream().mapToInt(File::getSize).sum()).sum();
    }

    public Map<Integer, Set<File>> byYear()
    {
        Map<Integer, Set<File>> retmap = new HashMap<>();
        for (Map.Entry<Character, SortedSet<File>> file : files.entrySet())
        {
            for (File f : file.getValue())
            {
                if (!retmap.containsKey(f.getDate().getYear()))
                {
                    Set<File> sett = new HashSet<>();
                    sett.add(f);
                    retmap.put(f.getDate().getYear(), sett);
                } else
                {
                    retmap.get(f.getDate().getYear()).add(f);
                }
            }
        }

        return retmap;
    }

    public Map<String, Long> sizeByMonthAndDay()
    {
        Map<String, Long> retmap = new HashMap<>();
        for (Map.Entry<Character, SortedSet<File>> file : files.entrySet())
        {
            for (File f : file.getValue())
            {
                if (!retmap.containsKey(f.getDate().getMonth() + "-" + f.getDate().getDayOfMonth()))
                {
                    retmap.put(f.getDate().getMonth() + "-" + f.getDate().getDayOfMonth(), (long) f.getSize());
                } else
                {
                    retmap.put(f.getDate().getMonth() + "-" + f.getDate().getDayOfMonth(), retmap.get(f.getDate().getMonth() + "-" + f.getDate().getDayOfMonth()) + f.getSize());
                }
            }
        }
        return retmap;
    }

}
public class FileSystemTest {
    public static void main(String[] args) {
        FileSystem fileSystem = new FileSystem();
        Scanner scanner = new Scanner(System.in);
        int n = scanner.nextInt();
        scanner.nextLine();
        for (int i = 0; i < n; i++) {
            String line = scanner.nextLine();
            String[] parts = line.split(":");
            fileSystem.addFile(parts[0].charAt(0), parts[1],
                    Integer.parseInt(parts[2]),
                    LocalDateTime.of(2016, 12, 29, 0, 0, 0).minusDays(Integer.parseInt(parts[3]))
            );
        }
        int action = scanner.nextInt();
        if (action == 0) {
            scanner.nextLine();
            int size = scanner.nextInt();
            System.out.println("== Find all hidden files with size less then " + size);
            List<File> files = fileSystem.findAllHiddenFilesWithSizeLessThen(size);
            files.forEach(System.out::println);
        } else if (action == 1) {
            scanner.nextLine();
            String[] parts = scanner.nextLine().split(":");
            System.out.println("== Total size of files from folders: " + Arrays.toString(parts));
            int totalSize = fileSystem.totalSizeOfFilesFromFolders(Arrays.stream(parts)
                    .map(s -> s.charAt(0))
                    .collect(Collectors.toList()));
            System.out.println(totalSize);
        } else if (action == 2) {
            System.out.println("== Files by year");
            Map<Integer, Set<File>> byYear = fileSystem.byYear();
            byYear.keySet().stream().sorted()
                    .forEach(key -> {
                        System.out.printf("Year: %d\n", key);
                        Set<File> files = byYear.get(key);
                        files.stream()
                                .sorted()
                                .forEach(System.out::println);
                    });
        } else if (action == 3) {
            System.out.println("== Size by month and day");
            Map<String, Long> byMonthAndDay = fileSystem.sizeByMonthAndDay();
            byMonthAndDay.keySet().stream().sorted()
                    .forEach(key -> System.out.printf("%s -> %d\n", key, byMonthAndDay.get(key)));
        }
        scanner.close();
    }
}

// Your code here

