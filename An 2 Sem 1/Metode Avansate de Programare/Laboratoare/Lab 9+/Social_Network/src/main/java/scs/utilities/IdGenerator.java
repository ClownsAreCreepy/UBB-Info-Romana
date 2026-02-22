package scs.utilities;

import java.util.concurrent.atomic.AtomicLong;

public final class IdGenerator {
    private final AtomicLong seq;

    public IdGenerator() {
        this(1L);
    }

    public IdGenerator(long startAt) {
        this.seq = new AtomicLong(startAt);
    }

    public long next() {
        return seq.getAndIncrement();
    }

    public void bumpToAtLeast(long value) {
        long current;
        do {
            current = seq.get();
            if (current > value)
                return;
        } while (!seq.compareAndSet(current, value));
    }

    public long getNumber() {
        return seq.get();
    }
}
