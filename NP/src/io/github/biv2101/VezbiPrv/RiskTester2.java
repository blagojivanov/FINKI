package io.github.biv2101.VezbiPrv;

import java.io.InputStream;
import java.util.Arrays;
import java.util.Scanner;

class Risk2 {
    public void processAttacksData(InputStream is) {
        Scanner sc = new Scanner(is);
        int add=0;
        while (sc.hasNextLine()) {
            String line = sc.nextLine();
            String[] lp = line.split(";");
            String[] attacks = lp[0].split("\\s+");
            String[] defense = lp[1].split("\\s+");

            int ctatc = 3;
            int ctdef = 3;

            int[] atcs = Arrays.stream(attacks).mapToInt(f -> Integer.parseInt(f)).sorted().toArray();
            int[] defs = Arrays.stream(defense).mapToInt(f -> Integer.parseInt(f)).sorted().toArray();

            for (int i = 0; i < atcs.length; i++) {
                if (atcs[i] > defs[i]) {
                    ctdef--;
                } else if (atcs[i] <= defs[i]) {
                    ctatc--;
                }
            }
            if (ctatc == 3)
            {
                add++;
            }
        }
        System.out.println(add);
    }
}

public class RiskTester2 {
    public static void main(String[] args) {
        Risk2 risk = new Risk2();
        risk.processAttacksData(System.in);
    }
}
