package io.github.biv2101.VezbiVtor;

import java.util.*;
import java.util.stream.Collectors;

class Person implements Comparable<Person>
{
    private String name;
    private String code;
    private String city;
    private int age;

    public Person(String city, String code, String name, int age) {
        this.name = name;
        this.code = code;
        this.city = city;
        this.age = age;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Person person = (Person) o;
        return Objects.equals(code, person.code);
    }

    @Override
    public String toString() {
        return code + " " + name + " " + age;
    }

    @Override
    public int hashCode() {
        return code.hashCode();
    }

    @Override
    public int compareTo(Person o) {
        return (name.compareTo(o.name) != 0) ? name.compareTo(o.name) : Integer.compare(age, o.age);
    }
}

class Audition
{
    private HashMap<String, HashSet<Person>> participants;

    public Audition() {
        participants = new HashMap<>();
    }

    public void addParticpant(String city, String code, String name, int age)
    {
        Person person = new Person(city, code, name, age);
        if (!participants.containsKey(city))
        {
            participants.put(city, new HashSet<>());
        }
        participants.get(city).add(person);
    }

    public void listByCity(String city)
    {
        participants.get(city).stream().collect(Collectors.toList()).stream().sorted().forEach(System.out::println);
    }
}

public class AuditionTest {
    public static void main(String[] args) {
        Audition audition = new Audition();
        List<String> cities = new ArrayList<String>();
        Scanner scanner = new Scanner(System.in);
        while (scanner.hasNextLine()) {
            String line = scanner.nextLine();
            String[] parts = line.split(";");
            if (parts.length > 1) {
                audition.addParticpant(parts[0], parts[1], parts[2],
                        Integer.parseInt(parts[3]));
            } else {
                cities.add(line);
            }
        }
        for (String city : cities) {
            System.out.printf("+++++ %s +++++\n", city);
            audition.listByCity(city);
        }
        scanner.close();
    }
}