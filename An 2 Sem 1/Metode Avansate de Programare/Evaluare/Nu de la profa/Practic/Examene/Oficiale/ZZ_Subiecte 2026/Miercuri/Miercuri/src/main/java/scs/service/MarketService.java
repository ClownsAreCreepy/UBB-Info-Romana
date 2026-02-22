package scs.service;

import javafx.application.Platform;
import scs.domain.Coin;
import scs.domain.Transaction;
import scs.domain.User;
import scs.repo.CoinRepository;
import scs.repo.TransactionRepository;
import scs.repo.UserRepository;
import scs.utilities.events.ChangeEventType;
import scs.utilities.events.EntityChangeEvent;
import scs.utilities.observer.Observable;

import java.time.LocalDateTime;
import java.util.List;
import java.util.concurrent.CompletableFuture;
import java.util.concurrent.TimeUnit;

public class MarketService extends Observable<EntityChangeEvent<Object>> {
    private final UserRepository userRepo;
    private final CoinRepository coinRepo;
    private final TransactionRepository transRepo;

    public MarketService(UserRepository userRepo, CoinRepository coinRepo, TransactionRepository transRepo) {
        this.userRepo = userRepo;
        this.coinRepo = coinRepo;
        this.transRepo = transRepo;
    }

    public List<User> getAllUsers() {
        return userRepo.findAll();
    }

    public List<Coin> getAllCoins() {
        return coinRepo.findAll();
    }

    public List<Transaction> getAllTransactions() {
        return transRepo.findAll();
    }

    // how many of a specific coin does a user own
    public int getHoldings(Long userId, String symbol) {
        List<Transaction> history = transRepo.findAll().stream()
                .filter(t -> t.getUserid().equals(userId) && t.getCoinsymbol().equals(symbol))
                .toList();

        int owned = 0;
        for (Transaction t : history) {
            if (t.getType().equals("BUY"))
                owned++;
            else
                owned--;
        }

        return owned;
    }

    public void processTransactionAsync(Long userId, String coinSymbol, String type) {
        CompletableFuture.delayedExecutor(3, TimeUnit.SECONDS).execute(() -> {
            try {
                if (type.equals("BUY"))
                    buyCoin(userId, coinSymbol);
                else
                    sellCoin(userId, coinSymbol);

                Platform.runLater(() -> {
                    // force refresh or specific update
                    notifyObservers(new EntityChangeEvent<>(ChangeEventType.UPDATE, null));
                });
            } catch (Exception e) {
                e.printStackTrace();
            }
        });
    }

    private synchronized void buyCoin(Long userId, String coinSymbol) {
        User user = userRepo.findOne(userId).orElseThrow();
        Coin coin = getAllCoins().stream().filter(c -> c.getSymbol().equals(coinSymbol)).findFirst().orElseThrow();

        if (user.getBudget() < coin.getPrice())
            throw new RuntimeException("Insufficient funds! Cost: " + coin.getPrice() + ", You have:" + user.getBudget());

        user.setBudget(user.getBudget() - coin.getPrice());
        userRepo.update(user);

        Transaction t = new Transaction(0L, userId, coinSymbol, "BUY", coin.getPrice(), LocalDateTime.now());
        transRepo.save(t);
    }

    private synchronized void sellCoin(Long userId, String coinSymbol) {
        User user = userRepo.findOne(userId).orElseThrow();
        Coin coin = getAllCoins().stream().filter(c -> c.getSymbol().equals(coinSymbol)).findFirst().orElseThrow();

        if (getHoldings(userId, coinSymbol) <= 0)
            throw new RuntimeException("You dont own any" + coinSymbol + " to sell!");

        user.setBudget(user.getBudget() + coin.getPrice());
        userRepo.update(user);

        Transaction t = new Transaction(0L, userId, coinSymbol, "SELL", coin.getPrice(), LocalDateTime.now());
        transRepo.save(t);
    }

    public void updateCoinPrice(Coin coin) {
        coinRepo.update(coin);
        notifyObservers(new EntityChangeEvent<>(ChangeEventType.UPDATE, coin));
    }
}
