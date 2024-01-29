package io.github.biv2101.VezbiVtor;

import java.io.BufferedReader;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.*;
import java.util.stream.Collectors;

class QuizProcessor {
    public static Map<String, Double> processAnswers(InputStream is) {
        BufferedReader br = new BufferedReader(new InputStreamReader(is));
        List<String> lines = br.lines().collect(Collectors.toList());
        Map<String, Double> resultMap = new TreeMap<>();
        for (String line : lines)
        {
            String[] lp = line.split(";");
            String key = lp[0];
            String[] answers = lp[1].split("\\s+");
            String[] correct = lp[2].split("\\s+");

            if (answers.length != correct.length)
            {
                System.out.println("A quiz must have same number of correct and selected answers");
                continue;
            }

            double sum = 0;
            for (int i = 0; i<answers.length; i++)
            {
                if (answers[i].equals(correct[i]))
                {
                    sum+=1;
                } else {
                    sum-=0.25;
                }
            }
            resultMap.put(key, sum);
        }
        return resultMap;
    }
}

public class QuizProcessorTest {
    public static void main(String[] args) {
        QuizProcessor.processAnswers(System.in).forEach((k, v) -> System.out.printf("%s -> %.2f%n", k, v));
    }
}