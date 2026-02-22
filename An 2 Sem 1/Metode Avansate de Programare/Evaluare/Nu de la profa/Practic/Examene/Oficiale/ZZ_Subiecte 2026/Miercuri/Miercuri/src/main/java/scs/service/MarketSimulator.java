package scs.service;

import scs.domain.Coin;

import java.util.Random;

public class MarketSimulator implements Runnable {
    private final MarketService service;
    private final Random random = new Random();
    private volatile boolean running = true;


    public MarketSimulator(MarketService service) {
        this.service = service;
    }

    public void stop() {
        this.running = false;
    }

    @Override
    public void run() {
        while(running) {
            try {
                Thread.sleep(3000);

                for (Coin coin : service.getAllCoins()) {
                    // price fluctuates by +/- 5%
                    double changePercent = (random.nextDouble() * 0.10) - 0.5;
                    double newPrice = coin.getPrice() * (1 + changePercent);

                    if (newPrice < 0.01)
                        newPrice = 0.01;
                    coin.setPrice(Math.round(newPrice * 100.0) / 100.0);

                    service.updateCoinPrice(coin);
                }
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
                break;
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }
}
