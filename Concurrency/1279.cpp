#include <iostream>
// unordered_multiset here
#include <unordered_set>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <vector>
using namespace std;

/* 1279. Traffic Light Controlled Intersection */
class TrafficLight {
private:
    mutex mtx;
    bool isLighGreenOnA = true;
    
public:
    TrafficLight() {}

    void carArrived(
        int carId,                   // ID of the car
        int roadId,                  // ID of the road the car travels on. Can be 1 (road A) or 2 (road B)
        int direction,               // Direction of the car
        function<void()> turnGreen,  // Use turnGreen() to turn light to green on current road
        function<void()> crossCar    // Use crossCar() to make car cross the intersection
    ) {
        mtx.lock();
        if ((isLighGreenOnA && (roadId == 1)) || (!isLighGreenOnA && (roadId == 2))) {
            crossCar();
            mtx.unlock();
            return;
        }
        isLighGreenOnA = !isLighGreenOnA;
        turnGreen();
        crossCar();
        mtx.unlock();
    }
};
