package service;

import domain.user.User;
import repo.FriendshipRepository;
import repo.users.UserRepository;
import error.NotFoundException;

import java.util.*;

/**
 * community logic:
 * - connected components via BFS
 * - diameter per component ( max shortest-path distance)
 * - most sociable = max diameter; tie -> larger size; tie -> lowest id
 */
public class CommunityService {
    private final UserRepository users;
    private final FriendshipRepository graph;

    public CommunityService(UserRepository users, FriendshipRepository graph) {
        this.users = users;
        this.graph = graph;
    }


    // --- helpers ---
    private Set<Long> bfsComponent(long start) {
        var q = new ArrayDeque<Long>();
        var comp = new LinkedHashSet<Long>();
        q.add(start);
        comp.add(start);

        while (!q.isEmpty()) {
            long u = q.poll();
            for (long v : graph.getFriends(u))
                if (comp.add(v))
                    q.add(v);
        }

        return comp;
    }


    // BFS shortest distances inside 'allowed' subgraph
    private Map<Long, Integer> bfsDistances(long start, Set<Long> allowed) {
        var dist = new HashMap<Long, Integer>();
        var q = new ArrayDeque<Long>();
        dist.put(start, 0);
        q.add(start);

        while (!q.isEmpty()) {
            long u = q.poll();
            int du = dist.get(u);
            for (long v : graph.getFriends(u)) {
                if (!allowed.contains(v))
                    continue;
                if (!dist.containsKey(v)) {
                    dist.put(v, du + 1);
                    q.add(v);
                }
            }
        }

        return dist;
    }


    // simple DTO for reporting
    public static final class CommunitySummary {
        private final Set<User> members;
        private final int diameter;

        public CommunitySummary(Set<User> members, int diameter) {
            this.members = members;
            this.diameter = diameter;
        }

        public Set<User> getMembers() {
            return members;
        }

        public int getDiameter() {
            return diameter;
        }
    }


    // --- big ones ---
    // how many connected components exist right now
    public int countCommunities() {
        return connectedComponents().size();
    }

    // returns all communities as sets of userIds
    public List<Set<Long>> connectedComponents() {
        var comps = new ArrayList<Set<Long>>();
        var visited = new HashSet<Long>();

        for (long u : graph.getAllUsers()) {
            if (visited.contains(u))
                continue;
            Set<Long> comp = bfsComponent(u);
            visited.addAll(comp);
            comps.add(comp);
        }
        return comps;
    }

    // compute diameter (max shortest path) inside a component
    public int diameter(Set<Long> component) {
        if (component.isEmpty() || component.size() == 1) return 0;

        int dia = 0;
        for (long start : component) {
            Map<Long, Integer> dist = bfsDistances(start, component);
            for (long v : component) {
                Integer d = dist.get(v);
                if (d != null && d > dia)
                    dia = d;
            }
        }

        return dia;
    }

    // pick the most sociable community + report members and diameter
    public CommunitySummary mostSociableCommunity() {
        var comps = connectedComponents();
        if (comps.isEmpty())
            return new CommunitySummary(Set.of(), 0);

        comps.sort((a, b) -> {
            int da = diameter(a), db = diameter(b);
            if (db != da)
                return Integer.compare(db, da); // desc by diamete

            if (b.size() != a.size())
                return Integer.compare(b.size(), a.size()); // desc by size

            // asc by min id for stability
            long mina = a.stream().min(Long::compareTo).orElse(Long.MAX_VALUE);
            long minb = b.stream().min(Long::compareTo).orElse(Long.MAX_VALUE);
            return Long.compare(mina, minb);
        });

        var best = comps.get(0);
        int bestDia = diameter(best);

        // map ids -> users (skip ghosts if any)
        Set<User> members = new LinkedHashSet<>();

        for (long id : best.stream().sorted().toList())
            try{
                members.add(users.findById(id));
            } catch (NotFoundException ignored) {}

        return new CommunitySummary(members, bestDia);
    }

}
