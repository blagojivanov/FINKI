package io.github.biv2101.VezbiPrv;

//15 i 16 kolokviumska, tuka se dodava delot so statistika i formatiranje na pecatenje

//ID item_price1 item_tax_type1 item_price2 item_tax_type2 … item_price-n item_tax_type-n

import java.io.InputStream;
import java.io.OutputStream;
import java.io.PrintStream;
import java.util.*;
import java.util.stream.Collectors;

class AmountNotAllowedException extends Exception {
    public AmountNotAllowedException(String message) {
        super(message);
    }
}

class DDVItem {
    private int price;
    private char type;

    public DDVItem(int price, char type) {
        this.price = price;
        this.type = type;
    }

    public double tax() {
        if (type == 'A') {
            return price * 0.18;
        } else if (type == 'B') {
            return price * 0.05;
        } else {
            return 0;
        }
    }

    public int getPrice() {
        return price;
    }

    public double getTaxReturn() {
        return tax() * 0.15;
    }

}

class DDVRecord {
    private int id;
    List<DDVItem> items;

    public DDVRecord(int id, List<DDVItem> items) {
        this.items = items;
        this.id = id;
    }

    public int getValue() {
        return items.stream().mapToInt(DDVItem::getPrice).sum();
    }

    public double getTax() {
        return items.stream().mapToDouble(DDVItem::getTaxReturn).sum();
    }

    public int getId() {
        return id;
    }
}

class MojDDV {
    List<DDVRecord> records;

    public MojDDV() {
        this.records = new ArrayList<>();
    }

    public void readRecords(InputStream is) {
        Scanner sc = new Scanner(is);
        while (sc.hasNextLine()) {
            String[] recordStr = sc.nextLine().split("\\s+");
            int id = Integer.parseInt(recordStr[0]);
            List<DDVItem> items = new ArrayList<>();
            for (int i = 1; i < recordStr.length - 1; i += 2) {
                int price = Integer.parseInt(recordStr[i]);
                char type = recordStr[i + 1].charAt(0);
                items.add(new DDVItem(price, type));
            }
            try {
                addRecord(new DDVRecord(id, items));
            } catch (AmountNotAllowedException e) {
                System.out.println(e.getMessage());
            }

        }
    }

    public void printTaxReturns(OutputStream os) {
        PrintStream ps = new PrintStream(os);
        records.stream().forEach(r -> ps.println(String.format("%10d\t%10d\t%10.5f", r.getId(), r.getValue(), r.getTax())));
        ps.flush();
    }

    public void addRecord(DDVRecord record) throws AmountNotAllowedException {
        if (record.getValue() > 30000) {
            throw new AmountNotAllowedException("Receipt with amount " + record.getValue() + " is not allowed to be scanned");
        } else {
            records.add(record);
        }
    }

    public void printStatistics(OutputStream os)
    {
        PrintStream ps = new PrintStream(os);
        DoubleSummaryStatistics dss = records.stream().collect(Collectors.summarizingDouble(DDVRecord::getTax));
        ps.printf("min:\t%-5.3f\n", dss.getMin());
        ps.printf("max:\t%-5.3f\n", dss.getMax());
        ps.printf("sum:\t%-5.3f\n", dss.getSum());
        ps.printf("count:\t%-5d\n", dss.getCount());
        ps.printf("avg:\t%-5.3f\n", dss.getAverage());
        ps.flush();
    }
}

public class MojDDVTest {

    public static void main(String[] args) {

        MojDDV mojDDV = new MojDDV();

        System.out.println("===READING RECORDS FROM INPUT STREAM===");
        mojDDV.readRecords(System.in);

        System.out.println("===PRINTING TAX RETURNS RECORDS TO OUTPUT STREAM ===");
        mojDDV.printTaxReturns(System.out);

        System.out.println("===PRINTING SUMMARY STATISTICS FOR TAX RETURNS TO OUTPUT STREAM===");
        mojDDV.printStatistics(System.out);


    }
}