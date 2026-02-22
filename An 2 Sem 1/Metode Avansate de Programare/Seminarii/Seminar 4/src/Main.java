
import Aria.*;
import Forme.*;

import java.util.Arrays;
import java.util.Comparator;
import java.util.List;
import java.util.function.Function;
import java.util.function.Predicate;
import java.util.function.Supplier;
import java.util.stream.Collectors;

public class Main {
    // the required signature from the sheet
    public static <E> void printArie(List<E> l, Arie<E> f) {
        for (E e : l) {
            double a = f.calc(e);
            System.out.println(e + " -> area=" + a);
        }
    }


    // II. Built-in functional interfaces
    // 2) generic method that prints items matching a Predicate<E>
    public static <E> void printIF(List<E> l, Predicate<E> p) {
        for (E e : l)
            if (p.test(e)) System.out.println(e);
    }

    // 3) Functions - declarations matching the prompt
    static Function<String, Integer> converterLambda = x -> Integer.valueOf(x);
    static Function<String, Integer> converterMethodReference = Integer::valueOf;

    // 4) Suppliers - same as 3
    // they don't take args; they just .get()
    static Supplier<Integer> fortyTwo = () -> Integer.valueOf(42);
    static Supplier<Double> randomDouble = Math::random;

    // 5) Comparators - a few short examples
    static Comparator<Rect> byArea = Comparator.comparingDouble(r -> r.getW() * r.getH());

    static Comparator<Rect> byAreaDesc = Comparator.comparingDouble((Rect r) -> r.getW() * r.getH()).reversed();

    static Comparator<Rect> byWThenH = Comparator.comparingDouble((Rect r) -> r.getW()).thenComparingDouble(Rect::getH);

    static Comparator<String> nullsFirstAlpha = Comparator.nullsFirst(String::compareToIgnoreCase);


    // III. Stream tasks
    // 6) filterGeneric(list, predicate)
    public static <E> List<E> filterGeneric(List<E> lista, Predicate<E> p) {
        return lista.stream().filter(p).collect(Collectors.toList());
    }

    // 7) filterGeneric(list, predicate, comparator) - filter + sort
    public static <E> List<E> filterGeneric(List<E> lista, Predicate<E> p, Comparator<E> c) {
        return lista.stream().filter(p).sorted(c).collect(Collectors.toList());
    }

    public static void main(String[] args) {
        // I. Custom functional interface in action
        List<Circle> circles = Arrays.asList(new Circle(1), new Circle(2.5), new Circle(3));
        Arie<Circle> circleArea = c -> Math.PI * c.getR() * c.getR();
        System.out.println("areas from circles");
        printArie(circles, circleArea);

        List<Rect> rects = Arrays.asList(new Rect(3, 4), new Rect(2, 2), new Rect(5, 1.5));
        Arie<Rect> rectArea = r -> r.getW() * r.getH();
        System.out.println("\nareas from rects");
        printArie(rects, rectArea);

        // II. Predicates
        System.out.println("\nrects with area >= 6: ");
        printIF(rects, r -> r.getW() * r.getH() >= 6);

        // III. Functions
        System.out.println("\nFunction.apply demo: ");
        System.out.println(converterLambda.apply("123"));
        System.out.println(converterMethodReference.apply("456"));

        // suppliers
        System.out.println("\nSupplier.get demo: ");
        System.out.println("fortyTwo -> " + fortyTwo.get());
        System.out.println("randomDouble -> " + randomDouble.get());

        // comparators
        System.out.println("\nsort rects by area asc: ");
        rects.stream().sorted(byArea).forEach(System.out::println);

        System.out.println("\nsort rects by area desc: ");
        rects.stream().sorted(byAreaDesc).forEach(System.out::println);

        System.out.println("\nsort rects by width then height: ");
        rects.stream().sorted(byWThenH).forEach(System.out::println);

        // stream - the two methods
        System.out.println("\nfilterGeneric: circles with r > 2");
        List<Circle> bigC = filterGeneric(circles, c -> c.getR() > 2);
        bigC.forEach(System.out::println);

        System.out.println("\nfilterGeneric + sort: rects area >= 3 by area asc");
        List<Rect> nice = filterGeneric(rects, r -> r.getW() * r.getH() >= 3, byArea);
        nice.forEach(System.out::println);

        // lil extra: string w/ nulls _ comparator example
        System.out.println("\nnullsFirstAlpha: ");
        List<String> names = Arrays.asList("Zed", "army", null, "Bob");
        names.stream().sorted(nullsFirstAlpha).forEach(System.out::println);
    }
}