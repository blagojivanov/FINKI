package io.github.biv2101.Labs.Lab2;

import java.text.DecimalFormat;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Scanner;
import java.util.stream.IntStream;

enum Operator {VIP, ONE, TMOBILE}

abstract class Contact {
    protected String date;
    protected String type;

    public Contact(String date) {
        this.date = date;
    }

    public String getDate() {
        return date;
    }

    public abstract String getType();

    public boolean isNewerThan(Contact c) {
        return date.compareTo(c.getDate()) > 0;
    }

}

class EmailContact extends Contact {

    private String email;

    public EmailContact(String date, String email) {
        super(date);
        this.type = "Email";
        this.email = email;
    }

    public String getEmail() {
        return email;
    }

    @Override
    public String getType() {
        return type;
    }

    @Override
    public String toString() {
        return "\"" + email + "\"";
    }
}

class PhoneContact extends Contact {

    private String phone;
    private Operator operator;

    public PhoneContact(String date, String phone) {
        super(date);
        this.type = "Phone";
        this.phone = phone;
        if (phone.startsWith("070") || phone.startsWith("071") || phone.startsWith("072")) {
            operator = Operator.TMOBILE;
        } else if (phone.startsWith("075") || phone.startsWith("076")) {
            operator = Operator.ONE;
        } else {
            operator = Operator.VIP;
        }
    }

    public String getPhone() {
        return phone;
    }

    public Operator getOperator() {
        return operator;
    }

    @Override
    public String getType() {
        return type;
    }

    @Override
    public String toString() {
        return "\"" + phone + "\"";
    }
}

class Student {

    private String firstName;
    private String lastName;
    private String city;
    private int age;
    private long index;

    // dali biva vaka da bide so lista a ne so niza
    private List<Contact> contacts;

    public Student(String firstName, String lastName, String city, int age, long index) {
        this.firstName = firstName;
        this.lastName = lastName;
        this.city = city;
        this.age = age;
        this.index = index;
        this.contacts = new ArrayList<>();
    }

    public void addEmailContact(String date, String email) {
        contacts.add(new EmailContact(date, email));
    }

    public void addPhoneContact(String date, String phone) {
        contacts.add(new PhoneContact(date, phone));
    }

    public String getCity() {
        return city;
    }

    public String getFullName() {
        return firstName + " " + lastName;
    }

    public long getIndex() {
        return index;
    }

    public Contact[] getEmailContacts() {
        List<Contact> emails = new ArrayList<>();
        for (Contact c : contacts) {
            if (c.getType() == "Email") {
                emails.add(c);
            }
        }
        // da vrne niza
        return emails.toArray(new Contact[emails.size()]);
    }


    public Contact[] getPhoneContacts() {
        List<Contact> phones = new ArrayList<>();
        for (Contact c : contacts) {
            if (c.getType() == "Phone") {
                phones.add(c);
            }
        }
        //da vrne niza
        return phones.toArray(new Contact[phones.size()]);
    }

    public Contact getLatestContact() {
        Contact lc = contacts.get(0);
        // da se reshe so lambda?
//        contacts.stream().forEach(contact -> {
//            if()
//        });
        for (Contact c : contacts) {
            if (c.isNewerThan(lc)) {
                lc = c;
            }
        }
        return lc;
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append("{\"ime\":\"").append(firstName)
                .append("\", \"prezime\":\"").append(lastName)
                .append("\", \"vozrast\":").append(age)
                .append(", \"grad\":\"").append(city)
                .append("\", \"indeks\":").append(index)
                .append(", \"telefonskiKontakti\":[");

        IntStream.range(0, getPhoneContacts().length - 1).forEach(i -> sb.append(getPhoneContacts()[i]).append(", "));
        if (getPhoneContacts().length > 0)
            sb.append(getPhoneContacts()[getPhoneContacts().length - 1]);

        sb.append("]").append(", \"emailKontakti\":[");
        IntStream.range(0, getEmailContacts().length - 1).forEach(i -> sb.append(getEmailContacts()[i]).append(", "));
        if (getEmailContacts().length > 0)
            sb.append(getEmailContacts()[getEmailContacts().length - 1]);

        sb.append("]}");
        return sb.toString();
    }
}

class Faculty {

    private String name;
    private Student[] students;

    public Faculty(String name, Student[] students) {
        this.name = name;
        this.students = students;
    }

    // okej?
    public int countStudentsFromCity(String city) {
        return (int) Arrays.stream(students).filter(s -> s.getCity().equals(city)).count();
//        for (Student s : students) {
//            if (s.getCity().equals(city)) ct++;
//        }
//        return ct;
    }

    //lambda ??
    public Student getStudent(long index) {
        Student s = null;
        for (Student st : students) {
            if (st.getIndex() == index) {
                s = st;
                break;
            }
        }
        return s;
    }

    public double getAverageNumberOfContacts() {
        return Arrays.stream(students).mapToDouble(s -> s.getEmailContacts().length + s.getPhoneContacts().length).average().getAsDouble();
    }

    //mislam deka nema da mozhe
    public Student getStudentWithMostContacts() {
        Student maxSt = students[0];
        for (Student s : students) {
            if (maxSt.getPhoneContacts().length + maxSt.getEmailContacts().length < s.getEmailContacts().length + s.getPhoneContacts().length) {
                maxSt = s;
            } else if (maxSt.getPhoneContacts().length + maxSt.getEmailContacts().length == s.getEmailContacts().length + s.getPhoneContacts().length) {
                if (maxSt.getIndex() < s.getIndex()) {
                    maxSt = s;
                }
            }
        }
        return maxSt;
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append("{\"fakultet\":\"").append(name).append("\", \"studenti\":[");
        for (int i = 0; i < students.length; i++) {
            sb.append(students[i]);
            if (i < students.length - 1) {
                sb.append(", ");
            }
        }
        sb.append("]}");
        return sb.toString();
    }
}

public class ContactsTester {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        int tests = scanner.nextInt();
        Faculty faculty = null;

        int rvalue = 0;
        long rindex = -1;

        DecimalFormat df = new DecimalFormat("0.00");

        for (int t = 0; t < tests; t++) {

            rvalue++;
            String operation = scanner.next();

            switch (operation) {
                case "CREATE_FACULTY": {
                    String name = scanner.nextLine().trim();
                    int N = scanner.nextInt();

                    Student[] students = new Student[N];

                    for (int i = 0; i < N; i++) {
                        rvalue++;

                        String firstName = scanner.next();
                        String lastName = scanner.next();
                        String city = scanner.next();
                        int age = scanner.nextInt();
                        long index = scanner.nextLong();

                        if ((rindex == -1) || (rvalue % 13 == 0))
                            rindex = index;

                        Student student = new Student(firstName, lastName, city,
                                age, index);
                        students[i] = student;
                    }

                    faculty = new Faculty(name, students);
                    break;
                }

                case "ADD_EMAIL_CONTACT": {
                    long index = scanner.nextInt();
                    String date = scanner.next();
                    String email = scanner.next();

                    rvalue++;

                    if ((rindex == -1) || (rvalue % 3 == 0))
                        rindex = index;

                    faculty.getStudent(index).addEmailContact(date, email);
                    break;
                }

                case "ADD_PHONE_CONTACT": {
                    long index = scanner.nextInt();
                    String date = scanner.next();
                    String phone = scanner.next();

                    rvalue++;

                    if ((rindex == -1) || (rvalue % 3 == 0))
                        rindex = index;

                    faculty.getStudent(index).addPhoneContact(date, phone);
                    break;
                }

                case "CHECK_SIMPLE": {
                    System.out.println("Average number of contacts: "
                            + df.format(faculty.getAverageNumberOfContacts()));

                    rvalue++;

                    String city = faculty.getStudent(rindex).getCity();
                    System.out.println("Number of students from " + city + ": "
                            + faculty.countStudentsFromCity(city));

                    break;
                }

                case "CHECK_DATES": {

                    rvalue++;

                    System.out.print("Latest contact: ");
                    Contact latestContact = faculty.getStudent(rindex)
                            .getLatestContact();
                    if (latestContact.getType().equals("Email"))
                        System.out.println(((EmailContact) latestContact)
                                .getEmail());
                    if (latestContact.getType().equals("Phone"))
                        System.out.println(((PhoneContact) latestContact)
                                .getPhone()
                                + " ("
                                + ((PhoneContact) latestContact).getOperator()
                                .toString() + ")");

                    if (faculty.getStudent(rindex).getEmailContacts().length > 0
                            && faculty.getStudent(rindex).getPhoneContacts().length > 0) {
                        System.out.print("Number of email and phone contacts: ");
                        System.out
                                .println(faculty.getStudent(rindex)
                                        .getEmailContacts().length
                                        + " "
                                        + faculty.getStudent(rindex)
                                        .getPhoneContacts().length);

                        System.out.print("Comparing dates: ");
                        int posEmail = rvalue
                                % faculty.getStudent(rindex).getEmailContacts().length;
                        int posPhone = rvalue
                                % faculty.getStudent(rindex).getPhoneContacts().length;

                        System.out.println(faculty.getStudent(rindex)
                                .getEmailContacts()[posEmail].isNewerThan(faculty
                                .getStudent(rindex).getPhoneContacts()[posPhone]));
                    }

                    break;
                }

                case "PRINT_FACULTY_METHODS": {
                    System.out.println("Faculty: " + faculty.toString());
                    System.out.println("Student with most contacts: "
                            + faculty.getStudentWithMostContacts().toString());
                    break;
                }

            }

        }

        scanner.close();
    }
}
