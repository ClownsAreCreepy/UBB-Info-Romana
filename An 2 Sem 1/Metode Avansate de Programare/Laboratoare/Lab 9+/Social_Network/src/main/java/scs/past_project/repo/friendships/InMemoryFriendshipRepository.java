//package scs.repo.friend.friendships;
//
//import java.util.*;
//
//public class InMemoryFriendshipRepository implements FriendshipRepository {
//    // lista de adiacenta: userId -> set of friends' ids
//    private final Map<Long, Set<Long>> adj = new HashMap<>();
//
//    @Override
//    public void addUser(long id) {
//        adj.putIfAbsent(id, new HashSet<>());
//    }
//
//    @Override
//    public void removeUser(long id) {
//        adj.remove(id);
//        for (var friends : adj.values())
//            friends.remove(id);
//    }
//
//
//    @Override
//    public void addFriendship(long id1, long id2) {
//        if (id1 == id2)
//            throw new IllegalArgumentException("you can't be friends with yourself.");
//
//        adj.putIfAbsent(id1, new HashSet<>());
//        adj.putIfAbsent(id2, new HashSet<>());
//
//        adj.get(id1).add(id2);
//        adj.get(id2).add(id1);
//    }
//
//    @Override
//    public void removeFriendship(long id1, long id2) {
//        Optional.ofNullable(adj.get(id1)).ifPresent(s -> s.remove(id2));
//        Optional.ofNullable(adj.get(id2)).ifPresent(s -> s.remove(id1));
//    }
//
//
//    @Override
//    public Set<Long> getFriends(long id) {
//        return Collections.unmodifiableSet(adj.getOrDefault(id, Collections.emptySet()));
//    }
//
//    @Override
//    public Set<Long> getAllUsers() {
//        return Collections.unmodifiableSet(adj.keySet());
//    }
//
//    @Override
//    public boolean areFriends(long id1, long id2) {
//        return adj.getOrDefault(id1, Set.of()).contains(id2);
//    }
//
//    @Override
//    public int nrFriends(long id) {
//        return adj.getOrDefault(id, Set.of()).size();
//    }
//
//
//    @Override
//    public List<long[]> findAllEdges() {
//        var res = new ArrayList<long[]>();
//        var seen = new HashSet<Long>();
//
//        for (var e : adj.entrySet()) {
//            long a = e.getKey();
//            for (long b : e.getValue())
//                if (!seen.contains(b))
//                    res.add(new long[]{a, b});
//            seen.add(a);
//        }
//
//        return res;
//    }
//
//
//    public Set<Long> mutualFriends(long a, long b) {
//        var fa = adj.getOrDefault(a, Set.of());
//        var fb = adj.getOrDefault(b, Set.of());
//        var res = new HashSet<>(fa);
//        res.retainAll(fb);
//        return res;
//    }
//
//    public Map<Long, Set<Long>> snapshot() {
//        Map<Long, Set<Long>> copy = new HashMap<>();
//        adj.forEach((k, v) -> copy.put(k, Collections.unmodifiableSet(new HashSet<>(v))));
//        return Collections.unmodifiableMap(copy);
//    }
//}