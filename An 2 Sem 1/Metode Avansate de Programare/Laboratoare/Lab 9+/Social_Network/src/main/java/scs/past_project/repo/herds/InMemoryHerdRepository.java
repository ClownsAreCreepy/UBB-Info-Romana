//package scs.repo.herds;
//
//import scs.domain.group.Card;
//import scs.domain.user.Duck;
//import scs.utilities.errors.DuplicateException;
//import scs.utilities.errors.NotFoundException;
//
//import java.util.HashMap;
//import java.util.List;
//import java.util.Map;
//import java.util.Objects;
//
//public class InMemoryCardRepository<T extends Duck> implements CardRepository<T> {
//    private final Map<Long, Card<T>> byId = new HashMap<>();
//    private final Map<String, Long> byName = new HashMap<>();
//
//    @Override
//    public void add(Card<T> card) {
//        var name = card.getNumeCard();
//
//        if (byName.containsKey(name))
//            throw new DuplicateException("herd name", "herd name already in use");
//
//        byId.put(card.getId(), card);
//        byName.put(name, card.getId());
//    }
//
//    @Override
//    public void update(Card<T> card) {
//        var existing = byId.get(card.getId());
//        if (existing == null)
//            throw new NotFoundException("herd", "card does not exist.");
//
//        var oldName = existing.getNumeCard();
//        var newName = card.getNumeCard();
//
//        if (!Objects.equals(oldName, newName)){
//            if (byName.containsKey(newName))
//                throw new DuplicateException("herd name", "herd name already in use.");
//
//            byName.remove(oldName);
//            byName.put(newName, card.getId());
//        }
//
//        byId.put(card.getId(), card);
//    }
//
//    @Override
//    public Card<T> findById(long id) {
//        var c = byId.get(id);
//
//        if (c == null)
//            throw new NotFoundException("no id match", " herd not found");
//
//        return c;
//    }
//
//    @Override
//    public Card<T> findByName(String name){
//        var id = byName.get(name);
//
//        if (id == null)
//            throw new NotFoundException("no name match", " herd not found");
//
//        return byId.get(id);
//    }
//
//    @Override
//    public List<Card<T>> getAll() {
//        return List.copyOf(byId.values());
//    }
//
//    @Override
//    public void deleteById(long id) {
//        var removed = byId.remove(id);
//        if (removed == null)
//            throw new NotFoundException("herd", "herd not found.");
//
//        byName.remove(removed.getNumeCard());
//    }
//
//    @Override
//    public boolean existsById(long id) {
//        return byId.containsKey(id);
//    }
//
//    @Override
//    public boolean existsByName(String name) {
//        return byName.containsKey(name);
//    }
//
//}
