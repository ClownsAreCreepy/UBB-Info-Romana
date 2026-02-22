package UI;

import Domain.Duck;
import Domain.ProblemData;
import Domain.Result;

import java.io.*;
import java.util.*;

public class UI {
    // citeste din natatie.in (as in statement) and builds ProblemData
    public ProblemData read() throws Exception{
        try(Scanner sc = new Scanner(new File("D:\\Facultate\\Eu\\An 2 Sem 1\\Metode Avansate de Programare\\Laboratoare\\Lab 1-4\\Ratuste\\src\\natatie.in"))){
            ProblemData data = new ProblemData();

            int N = sc.nextInt();
            int M = sc.nextInt();
            data.setN(N);
            data.setM(M);

            double[] speed =  new double[N];
            for(int i = 0; i < N; i++)
                speed[i] = sc.nextDouble();

            int [] res = new int[N];
            for (int i = 0; i < N; i++)
                res[i] = sc.nextInt();

            int [] d = new int [M];
            for(int i = 0; i < M; i++)
                d[i] = sc.nextInt();

            Duck[] ducks = new Duck[N];
            for(int i = 0; i < N; i++)
                ducks[i] = new Duck(i + 1, speed[i], res[i]);

            data.setBalize(d);
            data.setDucks(ducks);
            data.setResult(new Result(M));
            return data;
        }
    }

    // prints best time + lane assignment very cooly
    public void print(ProblemData data){
        Result res = data.getResult();
        double bestTime = res.getBestTime();

        System.out.printf(Locale.US, "%.3f%n", bestTime);

        int[] laneDuck = res.getLaneDuck();
        double[] dist = data.getBalizeAsDouble();
        Duck[] ducks = data.getDucks();

        for(int lane = 0; lane < dist.length; ++lane){
            Duck dk = ducks[laneDuck[lane] - 1];
            double tLane = 2.0 * dist[lane] / dk.getSpeed();
            System.out.println("Rata:" + dk.getId() + " pe linia " + (lane + 1) + " cu timpul " + tLane);
        }
    }
}
