#include "Observe.h"

void Observable::notify_all() {
    for (const auto &obs : observers)
        obs->update();
}

void Observable::addObserver(Observer *obs) {
    observers.push_back(obs);
}

void Observable::removeObserver(Observer *obs) {
    observers.erase(std::ranges::remove(observers, obs).begin(), observers.end());
}
