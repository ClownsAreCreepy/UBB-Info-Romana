package scs.domain.interactions;

public record Friendship(Long user1, Long user2) {
    public boolean involves(Long userId) {
        return user1.equals(userId) || user2.equals(userId);
    }
}
