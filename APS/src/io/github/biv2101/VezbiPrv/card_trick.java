package io.github.biv2101.VezbiPrv;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Stack;


public class card_trick {

    public static int count(int N) {

        Queue<Integer> queue = new LinkedList<>();
        for (int i = 1; i <= 51; i++) {
            queue.add(i);
        }

        int ct = 0;
        while (true) {
            if (queue.peek() == N)
            {
                return ct;
            }
            Stack<Integer> meshani = new Stack<>();
            for (int i = 0; i < 7; i++) {
                meshani.push(queue.poll());
            }
            for (int i = 0; i < 7; i++) {
                queue.add(meshani.pop());
                queue.add(queue.poll());
            }
            ct++;
        }

    }

    public static void main(String[] args) throws NumberFormatException, IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        System.out.println(count(Integer.parseInt(br.readLine())));
    }

}
