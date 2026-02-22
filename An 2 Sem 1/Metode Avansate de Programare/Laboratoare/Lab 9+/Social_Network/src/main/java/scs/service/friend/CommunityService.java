package scs.service.friend;

import scs.domain.user.User;
import scs.repo.friend.friendships.FriendshipRepository;
import scs.repo.users.UserRepository;
import scs.utilities.errors.NotFoundException;
import scs.utilities.paging.Page;
import scs.utilities.paging.Pageable;

import java.util.*;


public class CommunityService {
    private final UserRepository users;
    private final FriendshipRepository graph;

    public CommunityService(UserRepository users, FriendshipRepository graph) {
        this.users = users;
        this.graph = graph;
    }

    // DTO
    public record CommunitySummary(Set<User> members, int diameter) {
    }

    // --- helpers ---
    private void bfsRecursive(Long start, Map<Long, Set<Long>> adj, Set<Long> visited, Set<Long> component) {
        Queue<Long> q = new ArrayDeque<>();
        q.add(start);
        visited.add(start);
        component.add(start);

        while (!q.isEmpty()) {
            Long u = q.poll();
            for (Long v : adj.getOrDefault(u, Set.of()))
                if (!visited.contains(v)) {
                    visited.add(v);
                    component.add(v);
                    q.add(v);
                }
        }
    }


    // BFS shortest distances inside 'allowed' subgraph
    private int bfsMaxDist(Long start, Set<Long> allowed, Map<Long, Set<Long>> adj) {
        Map<Long, Integer> dist = new HashMap<>();
        Queue<Long> q = new ArrayDeque<>();

        dist.put(start, 0);
        q.add(start);
        int localMax = 0;

        while (!q.isEmpty()) {
            Long u = q.poll();
            int du = dist.get(u);

            for (Long v : adj.getOrDefault(u, Set.of())) {
                if (allowed.contains(v) && !dist.containsKey(v)) {
                    dist.put(v, du + 1);
                    q.add(v);

                    if (du > localMax)
                        localMax = du;
                }
            }
        }

        return localMax;
    }

    private Map<Long, Set<Long>> buildAdjacencyList(List<Long[]> edges) {
        Map<Long, Set<Long>> adj = new HashMap<>();

        for (Long[] edge : edges) {
            Long u = edge[0];
            Long v = edge[1];
            adj.computeIfAbsent(u, k -> new HashSet<>()).add(v);
            adj.computeIfAbsent(v, k -> new HashSet<>()).add(u);
        }

        return adj;
    }

    // returns all communities as sets of userIds
    public List<Set<Long>> findConnectedComponents(Map<Long, Set<Long>> adj) {
        List<Set<Long>> comps = new ArrayList<>();
        Set<Long> visited = new HashSet<>();

        for (Long node : adj.keySet())
            if (!visited.contains(node)) {
                Set<Long> comp = new HashSet<>();
                bfsRecursive(node, adj, visited, comp);
                comps.add(comp);
            }
        return comps;
    }

    // compute diameter (max shortest path) inside a component
    public int calculateDiameter(Set<Long> component, Map<Long, Set<Long>> adj) {
        if (component.size() <= 1) return 0;

        int maxDist = 0;
        for (Long startNode : component)
            maxDist = Math.max(maxDist, bfsMaxDist(startNode, component, adj));

        return maxDist;
    }

    public int countCommunities() {
        List<Long[]> edges = graph.findAllEdges();

        Map<Long, Set<Long>> adj = buildAdjacencyList(edges);

        List<Set<Long>> components = findConnectedComponents(adj);

//        Long totalUsers = users.getAll().size();
//        Long usersInFriendships = adj.size();
//        Long isolatedUsers = totalUsers - usersInFriendships;

        return components.size();
    }

    // pick the most sociable community + report members and diameter
    public CommunitySummary mostSociableCommunity() {
        // 1. LOAD DATA: Fetch all edges in ONE query
        // Returns List<Long[]> where index 0 is id1, index 1 is id2
        List<Long[]> edges = graph.findAllEdges();

        // 2. BUILD GRAPH: Convert to Adjacency List in Memory
        Map<Long, Set<Long>> adj = buildAdjacencyList(edges);

        // 3. LOGIC: Run algorithm on RAM
        List<Set<Long>> components = findConnectedComponents(adj);

        if (components.isEmpty())
            return new CommunitySummary(Set.of(), 0);

        // 4. FIND BEST: Sort by logic
        // Pre-calculate diameters to avoid recalculating during sort
        record CompStats(Set<Long> ids, int dia) {
        }

        List<CompStats> stats = components.stream()
                .map(ids -> new CompStats(ids, calculateDiameter(ids, adj)))
                .sorted((a, b) -> {
                    if (b.dia != a.dia) return Integer.compare(b.dia, a.dia); // desc diameter
                    return Integer.compare(b.ids.size(), a.ids.size());       // desc size
                })
                .toList();

        if (stats.isEmpty()) return new CommunitySummary(Set.of(), 0);

        CompStats best = stats.getFirst();

        List<Long> idsToFetch = new ArrayList<>(best.ids);

        Page<User> page = users.search(
                new Pageable(0, Integer.MAX_VALUE),
                "ALL", "ALL",
                idsToFetch,
                null
        );

        Set<User> members = new LinkedHashSet<>(page.getElementsOnPage());

        return new CommunitySummary(members, best.dia);
    }

}
