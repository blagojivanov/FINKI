package io.github.biv2101.VezbiVtor;

import java.util.*;
import java.util.stream.Collectors;

class DuplicateNumberException extends Exception {
    public DuplicateNumberException(String message) {
        super(message);
    }
}

class PhoneBook {
    Map<String, Set<String>> contacts;

    public PhoneBook() {
        contacts = new TreeMap<>();
    }

    void addContact(String name, String number) throws DuplicateNumberException {
        contacts.computeIfAbsent(name, x -> new TreeSet<>());
        if (contacts.get(name).contains(number)) {
            throw new DuplicateNumberException("Duplicate number: " + number);
        }
        contacts.get(name).add(number);
    }

    void contactsByNumber(String number) {
        Map<String, String> numbers = new HashMap<>();
        for (String name : contacts.keySet()) {
            for (String num : contacts.get(name)) {
                numbers.put(num, name);
            }
        }

        numbers = numbers.entrySet().stream().
                filter(x -> x.getKey().contains(number)).
                collect(Collectors.toMap(Map.Entry::getKey, Map.Entry::getValue, (key, value) -> value, HashMap::new));
        if (numbers.isEmpty()) {
            System.out.println("NOT FOUND");
        } else {
            numbers.entrySet().stream()
                    .sorted(Map.Entry.<String, String>comparingByValue()
                            .thenComparing(Map.Entry.comparingByKey()))
                    .forEach(x ->
                            {
                                System.out.println(x.getValue() + " " + x.getKey());
                            }
                    );
        }
    }

    void contactsByName(String name) {
        if (contacts.containsKey(name) == false)
        {
            System.out.println("NOT FOUND");
            return;
        }
        contacts.get(name).stream().forEach(
                x -> System.out.println(name + " " + x)
        );
    }
}

public class PhoneBookTest {

    public static void main(String[] args) {
        PhoneBook phoneBook = new PhoneBook();
        Scanner scanner = new Scanner(System.in);
        int n = scanner.nextInt();
        scanner.nextLine();
        for (int i = 0; i < n; ++i) {
            String line = scanner.nextLine();
            String[] parts = line.split(":");
            try {
                phoneBook.addContact(parts[0], parts[1]);
            } catch (DuplicateNumberException e) {
                System.out.println(e.getMessage());
            }
        }
        while (scanner.hasNextLine()) {
            String line = scanner.nextLine();
            System.out.println(line);
            String[] parts = line.split(":");
            if (parts[0].equals("NUM")) {
                phoneBook.contactsByNumber(parts[1]);
            } else {
                phoneBook.contactsByName(parts[1]);
            }
        }
    }

}

// Вашиот код овде

