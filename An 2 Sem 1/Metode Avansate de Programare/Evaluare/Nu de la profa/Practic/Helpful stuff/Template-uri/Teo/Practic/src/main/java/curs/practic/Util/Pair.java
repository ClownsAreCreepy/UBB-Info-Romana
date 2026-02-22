package curs.practic.Util;

import java.util.Objects;

public final class Pair<K, V> {
    private final K first;
    private final V second;

    public Pair(K first, V second) {
        this.first = first;
        this.second = second;
    }

    public K getFirst() {
        return first;
    }

    public V getSecond() {
        return second;
    }

    @Override
    public boolean equals(Object obj) {
        if(obj == this)
            return true;

        if (obj instanceof Pair o) {
            return first.equals(o.getFirst()) && second.equals(o.getSecond());
        }
        return false;
    }

    @Override
    public int hashCode() {
        return Objects.hash(first, second);
    }
}