package io.github.biv2101.Labs.Lab4;// package io.github.biv2101.Labs.Lab4;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.Stack;

public class ArithmeticExpression {

    // funkcija za presmetuvanje na izrazot pocnuvajki
    // od indeks l, zavrsuvajki vo indeks r
    static int presmetaj(char c[], int l, int r) {
        if (l == r) {
            return c[l] - 48;
        }
        int p = 0, idx = -1;

        for (int i = l; i < r; i++) {
            if (c[i] == '(') {
                p++;
            } else if (c[i] == ')') {
                p--;
            }
            if ((c[i] == '-' || c[i] == '+') && p == 0) {
                idx = i;
            }
        }
        if (idx == -1) return presmetaj(c, l + 1, r - 1);


        if (c[idx] == '-') {
            return presmetaj(c, l, idx - 1) - presmetaj(c, idx + 1, r);
        } else {
            return presmetaj(c, l, idx - 1) + presmetaj(c, idx + 1, r);
        }
    }

    public static void main(String[] args) throws Exception {
        int i, j, k;

        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        String expression = br.readLine();
        char exp[] = expression.toCharArray();

        int rez = presmetaj(exp, 0, exp.length - 1);
        System.out.println(rez);

        br.close();

    }

}
