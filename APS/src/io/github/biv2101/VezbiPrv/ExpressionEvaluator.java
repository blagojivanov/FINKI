package io.github.biv2101.VezbiPrv;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Stack;

public class ExpressionEvaluator {

    public static int evaluateExpression(String expression) {

        Stack<Integer> numStack = new Stack<>();

        String[] minusPlus = expression.split("\\+");

        for (String p : minusPlus) {
            if (p.contains("*")) {
                String[] minusAst = p.split("\\*");
                for (int i = 0; i < minusAst.length; i++) {
                    numStack.push(Integer.parseInt(minusAst[i]));
                    if (i >= 1) {
                        numStack.push(numStack.pop() * numStack.pop());
                    }
                }
            } else {
                numStack.push(Integer.parseInt(p));
            }
        }
        while (numStack.size() > 1) {
            numStack.push(numStack.pop() + numStack.pop());
        }
        return numStack.peek();
    }

    public static void main(String[] args) throws IOException {
        BufferedReader input = new BufferedReader(new InputStreamReader(System.in));
        System.out.println(evaluateExpression(input.readLine()));
    }

}