 package io.github.biv2101.Labs.Lab3;

import java.util.Arrays;
import java.util.Scanner;

public class MiceHoles {

    //TODO: implement function
    public static int minTime(int mice[], int holes[]) {
        int maxDist = 0;
        Arrays.sort(mice);
        Arrays.sort(holes);
        for (int i = 0; i<mice.length; i++)
        {
            maxDist = Math.abs(holes[i]-mice[i]);
        }
        return maxDist;

    }

    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);

        String line = input.nextLine();
        String parts[] = line.split(" ");
        int mice[] = new int[parts.length];
        for(int i=0;i<parts.length;i++) {
            mice[i] = Integer.parseInt(parts[i]);
        }

        line = input.nextLine();
        parts = line.split(" ");
        int holes[] = new int[parts.length];
        for(int i=0;i<parts.length;i++) {
            holes[i] = Integer.parseInt(parts[i]);
        }

        System.out.println(minTime(mice, holes));
    }
}
