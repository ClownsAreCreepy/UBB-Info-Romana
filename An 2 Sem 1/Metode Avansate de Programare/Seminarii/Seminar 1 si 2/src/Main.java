import App.*;
import Factory.*;
import TaskRunner.*;

import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

public class Main {
    public static void main(String[] args) {
        // Test 1
        {
            DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm");

            MessageTask[] tasks = new MessageTask[5];

            tasks[0] = new MessageTask(1, "Feedback lab1", "Ai obtinut 9.60", "Gigi", "Ana",
                    LocalDateTime.of(2018, 9, 27, 9, 29));
            tasks[1] = new MessageTask(2, "Tema 2", "Ai obtinut 10.00", "Profesor", "Mihai",
                    LocalDateTime.of(2018, 10, 1, 12, 45));
            tasks[2] = new MessageTask(3, "Lab 3", "Ai lipsit azi", "Profesor", "Ioana",
                    LocalDateTime.of(2018, 10, 8, 8, 0));
            tasks[3] = new MessageTask(4, "Lab 4", "Bravo, progres bun!", "Andreea", "Alex",
                    LocalDateTime.of(2018, 10, 15, 10, 30));
            tasks[4] = new MessageTask(5, "Lab 5", "Te rog sa refaci exercitiul 2", "Profesor", "Vlad",
                    LocalDateTime.of(2018, 10, 22, 9, 15));

            // print them all in requested format
            for (MessageTask t : tasks) {
                System.out.println("id=" + t.getID()
                        + "|descriere=" + t.getDescriere()
                        + "|message=" + t.getMesaj()
                        + "|from=" + t.getFrom()
                        + "|to=" + t.getTo()
                        + "|date=" + t.getDate().format(formatter));
            }
        }

        // Base for test 2, 3 and 4

        // Verificam daca avem argumente
        if (args.length == 0) {
            System.out.println("Please specify a strategy: FIFO or LIFO");
            return;
        }

        // Convertam primul argument intr-un enum din Strategy
        Strategy strategy;
        try {
            strategy = Strategy.valueOf(args[0].toUpperCase());
        } catch (IllegalArgumentException e) {
            System.out.println("Invalid strategy. Use FIFO or LIFO.");
            return;
        }

        System.out.println("Running with strategy: " + strategy);

        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyy-MM-dd HH:mm");
        MessageTask[] tasks = {
                new MessageTask(1, "Feedback lab1", "Ai obtinut 9.60", "Gigi", "Ana",
                        LocalDateTime.of(2018, 9, 27, 9, 29)),
                new MessageTask(2, "Tema 2", "Ai obtinut 10.00", "Profesor", "Mihai",
                        LocalDateTime.of(2018, 10, 1, 12, 45)),
                new MessageTask(3, "Lab 3", "Ai lipsit azi", "Profesor", "Ioana",
                        LocalDateTime.of(2018, 10, 8, 8, 0))

        };

        // Test 2
        {
            // Creem runner
            StrategyTaskRunner runner = new StrategyTaskRunner(strategy);

            // Creem mesaje pentru task-uri

            // add them all
            for (MessageTask t : tasks) {
                runner.addTask(t);
            }

            // execute all tasks
            runner.executeAll();
        }

        // Test 3
        {
            // base runner
            TaskRunner baseRunner = new StrategyTaskRunner(strategy);

            // decorate it with Printer
            TaskRunner decoratedRunner = new PrinterTaskRunner(baseRunner);

            for (MessageTask t: tasks) {
                decoratedRunner.addTask(t);
            }

            decoratedRunner.executeAll();
        }

        // Test 4
        {
            // base runner
            TaskRunner base = new StrategyTaskRunner(strategy);

            // delayed runner
            TaskRunner delayed = new DelayTaskRunner(base, 3000);

            // wrap with print runner
            TaskRunner print_and_delayed = new PrinterTaskRunner(delayed);

            for (MessageTask t: tasks) {
                print_and_delayed.addTask(t);
            }

            print_and_delayed.executeAll();
        }
    }
}