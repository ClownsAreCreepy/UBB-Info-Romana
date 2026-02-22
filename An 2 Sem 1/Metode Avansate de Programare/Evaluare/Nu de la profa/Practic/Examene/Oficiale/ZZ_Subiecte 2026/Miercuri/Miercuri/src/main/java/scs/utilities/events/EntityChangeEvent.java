package scs.utilities.events;

public record EntityChangeEvent<T>(ChangeEventType type, T data, T oldData) {
    // Already have built-in ctor from the record class
    // We use one without oldData for convenience because we don't use oldData that much
    public EntityChangeEvent(ChangeEventType type, T data) {
        this(type, data, null);
    }
}
