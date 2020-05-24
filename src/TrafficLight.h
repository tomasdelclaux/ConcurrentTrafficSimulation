#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H

#include <mutex>
#include <queue>
#include <condition_variable>
#include "TrafficObject.h"

enum TrafficLightPhase
{
    red,
    green
};

// forward declarations to avoid include cycle
class Vehicle;

template <class T>
class MessageQueue
{
public:
    T receive();

    void send(T &&msg);

private:
    std::mutex _mutex;
    std::condition_variable _cond;
    std::deque<T> _queue;
};

class TrafficLight : public TrafficObject
{
public:
    // constructor/destructor
    TrafficLight();

    // getters / setters
    TrafficLightPhase getCurrentPhase();

    // typical behaviour methods
    void simulate();

    void waitForGreen();

private:
    std::mutex _mutex;
    TrafficLightPhase _currentPhase;
    MessageQueue<TrafficLightPhase> _messages;
    void cycleThroughPhases();
};

#endif