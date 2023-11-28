package io.github.biv2101.VezbiPrv;

import java.util.*;
import java.util.stream.Collectors;
import java.util.stream.IntStream;


interface IFile {
    String getFileName();

    long getFileSize();

    String getFileInfo(int offset);

    void sortBySize();

    long findLargestFile();

    int compareTo(IFile o);
}

class FileNameExistsException extends Exception {

    String name;
    String folder;
    public FileNameExistsException(String name, String folder) {

        this.name = name;
        this.folder = folder;
    }

    @Override
    public String getMessage() {
        return "There is already a file named " + name + " in the folder " + folder;
    }
}

class File implements IFile  {

    private String name, info;
    private long size;
    private int printOffset;

    public File(String name, long size) {
        this.name = name;
        this.size = size;
    }

    @Override
    public String getFileName() {
        return name;
    }

    @Override
    public long getFileSize() {
        return size;
    }

    @Override
    public String getFileInfo(int offset) {
        printOffset = offset;
        return toString();
    }

    @Override
    public void sortBySize() {

    }

    @Override
    public long findLargestFile() {
        return size;
    }

    @Override
    public String toString() {
        return String.format(" ".repeat(printOffset) + "File name: %10s File size: %10d\n", name, size);
    }

    @Override
    public int compareTo(IFile o) {
        return Long.compare(getFileSize(), o.getFileSize());
    }
}

class Folder implements IFile {


    List<IFile> files = new ArrayList<>();
    private String name, info;
    private int printOffset;

    public Folder(String s) {
        name = s;
    }

    //dodavanje + exception sredeno
    public void addFile(IFile i) throws FileNameExistsException {
        if (files.stream().anyMatch(f -> i.getFileName().equals(f.getFileName())))
        {
            throw new FileNameExistsException(i.getFileName(), name);
        }
        files.add(i);

    }

    @Override
    public String getFileName() {
        return name;
    }

    @Override
    public long getFileSize() {
        return files.stream().mapToLong(IFile::getFileSize).sum();
    }

    @Override
    public String getFileInfo(int offset) {
        printOffset = offset;
        return toString();
    }

    @Override
    public void sortBySize() {
        files.sort(IFile::compareTo);
        files.stream().forEach(f->f.sortBySize());
    }

    @Override
    public long findLargestFile() {
        return files.stream().mapToLong(IFile::findLargestFile).max().orElse(0);
    }

    @Override
    public int compareTo(IFile o) {
        return Long.compare(getFileSize(), o.getFileSize());
    }

    @Override
    public String toString() {
        return String.format(" ".repeat(printOffset) + "Folder name: %10s Folder size: %10d\n", name, getFileSize()) + String.format(files.stream().map(f-> f.getFileInfo(printOffset+4)).collect(Collectors.joining()));
    }
}

class FileSystem
{
    Folder root;
    private String name;

    public FileSystem()
    {
        root = new Folder("root");
        name = "root";
    }

    //dodavanje + exception sredeno
    public void addFile(IFile file) throws FileNameExistsException
    {
        root.addFile(file);
    }

    //sortiranje sredeno
    public void sortBySize()
    {
        root.files.stream().forEach(IFile::sortBySize);
    }
    //sredeno
    public long findLargestFile() {
        return root.findLargestFile();
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append(root.getFileInfo(0));
        return sb.toString();
    }
}

public class FileSystemTest {

    public static Folder readFolder(Scanner sc) {

        Folder folder = new Folder(sc.nextLine());
        int totalFiles = Integer.parseInt(sc.nextLine());

        for (int i = 0; i < totalFiles; i++) {
            String line = sc.nextLine();

            if (line.startsWith("0")) {
                String fileInfo = sc.nextLine();
                String[] parts = fileInfo.split("\\s+");
                try {
                    folder.addFile(new File(parts[0], Long.parseLong(parts[1])));
                } catch (FileNameExistsException e) {
                    System.out.println(e.getMessage());
                }
            } else {
                try {
                    folder.addFile(readFolder(sc));
                } catch (FileNameExistsException e) {
                    System.out.println(e.getMessage());
                }
            }
        }

        return folder;
    }

    public static void main(String[] args) {

        //file reading from input

        Scanner sc = new Scanner(System.in);

        System.out.println("===READING FILES FROM INPUT===");
        FileSystem fileSystem = new FileSystem();
        try {
            fileSystem.addFile(readFolder(sc));
        } catch (FileNameExistsException e) {
            System.out.println(e.getMessage());
        }

        System.out.println("===PRINTING FILE SYSTEM INFO===");
        System.out.println(fileSystem.toString());

        System.out.println("===PRINTING FILE SYSTEM INFO AFTER SORTING===");
        fileSystem.sortBySize();
        System.out.println(fileSystem.toString());

        System.out.println("===PRINTING THE SIZE OF THE LARGEST FILE IN THE FILE SYSTEM===");
        System.out.println(fileSystem.findLargestFile());


    }
}
