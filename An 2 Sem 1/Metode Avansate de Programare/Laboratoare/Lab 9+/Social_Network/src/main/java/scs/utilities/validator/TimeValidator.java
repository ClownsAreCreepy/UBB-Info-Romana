package scs.utilities.validator;

import scs.utilities.errors.ValidationException;

import java.time.LocalDate;

public class TimeValidator implements Validator<LocalDate> {
    private final String field;
    private final LocalDate minInclusive;
    private final LocalDate maxInclusive;

    public TimeValidator(String field, LocalDate minInclusive, LocalDate maxInclusive) {
        this.field = field;
        this.minInclusive = minInclusive;
        this.maxInclusive = maxInclusive;
    }

    @Override
    public void validate(LocalDate time) {
        if (time == null || time.isBefore(minInclusive) || time.isAfter(maxInclusive))
            throw new ValidationException(field, field + " must be between " + minInclusive + " and " + maxInclusive);
    }
}
