// (Soon-to-be) working version of the chapter 10 code.
// The code is finalised in listing 10-55 but includes snippets throughout the chapter,
// so this is provided for reference.
// Uses header libraries catch and hippomocks.
#define CATCH_CONFIG_MAIN
#include "hippomocks.h"
#include "catch.hpp"
#include <functional>
#include <exception>

struct SpeedUpdate {
    double velocity_mps;
};
struct CarDetected {
    double distance_m;
    double velocity_mps;
};
struct BrakeCommand {
    double time_to_collision_s;
};

using SpeedUpdateCallback = std::function<void(const SpeedUpdate&)>;
using CarDetectedCallback = std::function<void(const CarDetected&)>;

struct IServiceBus {
    virtual ~IServiceBus() = default;
    virtual void publish(const BrakeCommand&) = 0;
    virtual void subscribe_to_speed(SpeedUpdateCallback) = 0;
    virtual void subscribe_to_car_detected(CarDetectedCallback) = 0;
};

template <typename T>
struct AutoBrake {
    AutoBrake(const T& publish) : publish{ publish } { }
    void observe(const SpeedUpdate& x) { 
        speed_mps = x.velocity_mps;
    }
    void observe(const CarDetected& x) { }

    void set_collision_threshold_s(double x) {
        if (x < 1) throw std::exception();
        collision_threshold_s = x;
    }
    double get_collision_threshold_s() const {
        return collision_threshold_s;
    }
    double get_speed_mps() const {
        return speed_mps;
    }

    private:
        double collision_threshold_s{5.0};
        double speed_mps{0.0};
        const T& publish;
};

TEST_CASE("AutoBrake") {
    MockRepository mocks;
    mocks.autoExpect = false;
    CarDetectedCallback car_detected_callback;
    SpeedUpdateCallback speed_update_callback;
    auto* bus = mocks.Mock<IServiceBus>();
    mocks.ExpectCall(bus, IServiceBus::subscribe_to_speed)
        .Do([&](const auto& x) {
            speed_update_callback = x;
    });
    mocks.ExpectCall(bus, IServiceBus::subscribe_to_car_detected)
        .Do([&](const auto& x) {
            car_detected_callback = x;
    });
    AutoBrake auto_brake{ *bus };

    SECTION("initializes speed to zero") {
        REQUIRE(auto_brake.get_speed_mps() == Approx(0));
    }

    SECTION("initializes sensitivity to five") {
        REQUIRE(auto_brake.get_collision_threshold_s() == Approx(5));
    }

    SECTION("throws when sensitivity less than one") {
        REQUIRE_THROWS(auto_brake.set_collision_threshold_s(0.5L));
    }

    SECTION("saves speed after update") {
        speed_update_callback(SpeedUpdate{ 100L });
        REQUIRE(100L == auto_brake.get_speed_mps());
        speed_update_callback(SpeedUpdate{ 50L });
        REQUIRE(50L == auto_brake.get_speed_mps());
        speed_update_callback(SpeedUpdate{ 0L });
        REQUIRE(0L == auto_brake.get_speed_mps());
    }

    SECTION("no alert when not imminent") {
        auto_brake.set_collision_threshold_s(2L);
        speed_update_callback(SpeedUpdate{ 100L });
        car_detected_callback(CarDetected{ 1000L, 50L });
    }

    SECTION("alert when imminent") {
        mocks.ExpectCall(bus, IServiceBus::publish)
            .Match([](const auto& cmd) {
                return cmd.time_to_collision_s == Approx(1);
        });
    }
    
    auto_brake.set_collision_threshold_s(10L);
    speed_update_callback(SpeedUpdate{ 100L }); // BAD: That won't work because is an uninitalised function
    car_detected_callback(CarDetected{ 100L, 0L }); // BAD: That won't work because is an uninitalised function
    //However, lines like 'bus->subscribe_to_speed(speed_update_callback);' would satisfy the expected call.
    //BUT we need a way to pass in updates.
}