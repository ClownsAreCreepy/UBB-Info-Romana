#pragma once

#include <vector>
#include <algorithm>

using namespace std;

class Observer {
public:
    virtual void update() = 0;
    virtual ~Observer() = default;
};

class Observable {
private:
    vector<Observer*> observers;

protected:
    void notify_all();

    virtual ~Observable() = default;

public:
    void addObserver(Observer *obs);

    void removeObserver(Observer *obs);
};