package service;

import domain.group.Card;
import domain.group.Performance;
import domain.user.Duck;
import repo.herds.CardRepository;
import utilities.IdGenerator;
import utilities.validator.NotBlankValidator;
import utilities.validator.V;

import java.util.List;

public class CardService {
    private final CardRepository<Duck> repo;

    public CardService(CardRepository<Duck> repo) {
        this.repo = repo;
    }

    public Card<Duck> createCard(String nume) {
        new NotBlankValidator("name").validate(nume);
        V.maxLengthString("name", 30).validate(nume);

        Card<Duck> c = new Card<>(nume);
        repo.add(c);
        return c;
    }

    public void deleteCard(long id) {
        repo.deleteById(id);
    }

    public List<Card<Duck>> getAll() {
        return repo.getAll();
    }

    public Card<Duck> findById(long id) {
        return repo.findById(id);
    }

    public void addDuck(long cardId, Duck duck){
        repo.addDuck(cardId, duck.getId());
    }

    public void deleteDuck(long cardId, long duckId) {
        Card<Duck> c = findById(cardId);
        repo.removeDuck(cardId, duckId);
    }

    public Performance performance(long cardId) {
        Card<Duck> c =  findById(cardId);
        return c.getAvgPerformance();
    }

    public List<Duck> members(long cardId) {
        var c = repo.findById(cardId);
        return c.getMembers();
    }
}
