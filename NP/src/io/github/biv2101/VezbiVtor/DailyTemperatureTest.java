package io.github.biv2101.VezbiVtor;

import java.io.*;
import java.util.*;
import java.util.stream.Collectors;

class Temperature
{
    double value;
    public Temperature(String line)
    {
        value = Integer.parseInt(line.substring(0, line.length()-1));
        if (line.endsWith("F"))
        {
            value =  ((value-32) * 5)/9;
        }
    }

    public double val(char scale)
    {
        if (scale == 'C')
        {
            return value;
        } else {
            return ((value * 9)/5) + 32;
        }
    }
    public void print(char scale)
    {

    }


}
class DailyTemperatures
{
    Map<Integer, List<Temperature>> temps;

    DailyTemperatures()
    {
        temps = new TreeMap<>();
    }
    void readTemperatures(InputStream is)
    {
        BufferedReader br = new BufferedReader(new InputStreamReader(is));

        br.lines().forEach(l->
        {
            String[] lp = l.split("\\s+");
            temps.computeIfAbsent(Integer.parseInt(lp[0]), x->new ArrayList<>()).addAll(Arrays.stream(lp).skip(1).map(Temperature::new).collect(Collectors.toList()));
        });
    }
    void writeDailyStats(OutputStream os, char scale)
    {
        PrintStream ps = new PrintStream(os);
        temps.entrySet().stream().sorted(Comparator.comparing(Map.Entry::getKey)).
                forEach(x-> ps.printf("%3d: Count: %3d Min: %6.2f%s Max: %6.2f%s Avg: %6.2f%s\n",
                        x.getKey(),
                        x.getValue().size(),
                        x.getValue().stream().mapToDouble(y->y.val(scale)).min().orElse(0), scale,
                        x.getValue().stream().mapToDouble(y->y.val(scale)).max().orElse(0), scale,
                        x.getValue().stream().mapToDouble(y->y.val(scale)).average().orElse(0), scale));
    }
}
public class DailyTemperatureTest {
    public static void main(String[] args) {
        DailyTemperatures dailyTemperatures = new DailyTemperatures();
        dailyTemperatures.readTemperatures(System.in);
        System.out.println("=== Daily temperatures in Celsius (C) ===");
        dailyTemperatures.writeDailyStats(System.out, 'C');
        System.out.println("=== Daily temperatures in Fahrenheit (F) ===");
        dailyTemperatures.writeDailyStats(System.out, 'F');
    }
}
