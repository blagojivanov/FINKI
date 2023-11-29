package io.github.biv2101.VezbiPrv;

import java.time.LocalDate;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;
import java.util.Scanner;
import java.util.stream.Collectors;
import java.util.stream.Stream;

class NonExistingItemException extends Exception {
    private int id;

    public NonExistingItemException(int id) {
        this.id = id;
    }

    @Override
    public String getMessage() {
        return "Item with id " + id + " doesn't exist";
    }
}

class Archive {
    protected int id;
    protected LocalDate dateArchived;

    public Archive(int id) {
        this.id = id;
    }

    public void setDateArchived(LocalDate dateArchived) {
        this.dateArchived = dateArchived;
    }

    public int getId() {
        return id;
    }
}

class LockedArchive extends Archive {
    private LocalDate dateToOpen;

    public LockedArchive(int id, LocalDate dateToOpen) {
        super(id);
        this.dateToOpen = dateToOpen;
    }

    public LocalDate getDateToOpen() {
        return dateToOpen;
    }
}

class SpecialArchive extends Archive {
    private int maxOpen;
    private int opened;

    public SpecialArchive(int id, int maxOpen) {
        super(id);
        this.maxOpen = maxOpen;
    }

    public int getMaxOpen() {
        return maxOpen;
    }

    public boolean openn() {
        if (opened < maxOpen) {
            this.opened++;
            return true;
        }
        return false;
    }

}

class ArchiveStore {
    List<Archive> archiveList;
    List<String> log;

    public ArchiveStore() {
        this.archiveList = new ArrayList<>();
        this.log = new ArrayList<>();
    }

    public void archiveItem(Archive archive, LocalDate dateArchived) {
        archive.setDateArchived(dateArchived);
        archiveList.add(archive);
        log.add(String.format("Item %d archived at %d-%02d-%02d", archive.getId(), dateArchived.getYear(), dateArchived.getMonthValue(), dateArchived.getDayOfMonth()));

    }

    public void openItem(int archive, LocalDate date) throws NonExistingItemException {
        if (archiveList.stream().anyMatch(t -> t.getId() == archive)) {
            List<Archive> collect = archiveList.stream().filter(t -> t.getId() == archive).collect(Collectors.toList());
            if (collect.get(0) instanceof LockedArchive) {
                LockedArchive la = (LockedArchive) collect.get(0);
                if (date.compareTo(la.getDateToOpen()) >= 0) {
                    log.add(String.format("Item %d opened at %d-%02d-%02d", la.getId(), date.getYear(), date.getMonthValue(), date.getDayOfMonth()));
                } else {
                    log.add(String.format("Item %d cannot be opened before %d-%02d-%02d", la.getId(), la.getDateToOpen().getYear(), la.getDateToOpen().getMonthValue(), la.getDateToOpen().getDayOfMonth()));
                }
            } else {
                SpecialArchive sa = (SpecialArchive) collect.get(0);
                if (sa.openn()) {
                    log.add(String.format("Item %d opened at %d-%02d-%02d", sa.getId(), date.getYear(), date.getMonthValue(), date.getDayOfMonth()));
                } else {
                    log.add("Item " + sa.getId() + " cannot be opened more than " + sa.getMaxOpen() + " times");

                }
            }
        } else {
            throw new NonExistingItemException(archive);
        }
    }

    public String getLog() {
        StringBuilder sb = new StringBuilder();
        log.forEach(t -> sb.append(t).append("\n"));
        return sb.toString();
    }
}

public class ArchiveStoreTest {
    public static void main(String[] args) {
        ArchiveStore store = new ArchiveStore();
        LocalDate date = LocalDate.of(2013, 10, 7);
        Scanner scanner = new Scanner(System.in);
        scanner.nextLine();
        int n = scanner.nextInt();
        scanner.nextLine();
        scanner.nextLine();
        int i;
        for (i = 0; i < n; ++i) {
            int id = scanner.nextInt();
            long days = scanner.nextLong();

            LocalDate dateToOpen = date.atStartOfDay().plusSeconds(days * 24 * 60 * 60).toLocalDate();
            LockedArchive lockedArchive = new LockedArchive(id, dateToOpen);
            store.archiveItem(lockedArchive, date);
        }
        scanner.nextLine();
        scanner.nextLine();
        n = scanner.nextInt();
        scanner.nextLine();
        scanner.nextLine();
        for (i = 0; i < n; ++i) {
            int id = scanner.nextInt();
            int maxOpen = scanner.nextInt();
            SpecialArchive specialArchive = new SpecialArchive(id, maxOpen);
            store.archiveItem(specialArchive, date);
        }
        scanner.nextLine();
        scanner.nextLine();
        while (scanner.hasNext()) {
            int open = scanner.nextInt();
            try {
                store.openItem(open, date);
            } catch (NonExistingItemException e) {
                System.out.println(e.getMessage());
            }
        }
        System.out.println(store.getLog());
    }
}
