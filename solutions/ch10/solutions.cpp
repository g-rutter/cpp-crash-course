// 10-1. Your car company has completed work on a service that detects speed limits based on signage it
//       observes on the side of the road. The speed-limit-detection team will publish objects of the
//       following type to the event bus periodically: (see struct SpeedLimitDetected).
//       The service bus has been extended to incorporate this new type: (see struct IServiceBus)
//       Update the service with the new interface and make sure the tests still pass.
// 10-2. Add a private field for the last known speed limit. Implement a getter method for this field.
// 10-3. The product owner wants you to initialize the last known speed limit to 39 meters per second.
//       Implement a unit test that checks a newly constructed AutoBrake that has a last known speed limit of 39.
// 10-4. Make unit tests pass.
// 10-5. Implement a unit test where you publish three different SpeedLimitDetected objects using the same
//       callback technique you used for SpeedUpdate and CarDetected. After invoking each of the callbacks,
//       check the last known speed limit on the AutoBrake object to ensure it matches.
// 10-6. Make all unit tests pass.
// 10-7. Implement a unit test where the last known speed limit is 35 meters per second, and you’re traveling
//       at 34 meters per second. Ensure that no BrakeCommand is published by AutoBrake.
// 10-8. Make all unit tests pass.

// 10-9. Implement a unit test where the last known speed limit is 35 meters per second and then publish a
//       SpeedUpdate at 40 meters per second. Ensure that exactly one BrakeCommand is issued. The
//       time_to_collision_s field should equal 0.
// 10-10. Make all unit tests pass.

// 10-11. Implement a new unit test where the last known speed limit is 35 meters per second and then publish
//        a SpeedUpdate at 30 meters per second. Then issue a SpeedLimitDetected with a speed_mps of 25 meters per
//        second. Ensure that exactly one BrakeCommand is issued. The time_to_collision_s field should equal 0.
// 10-12. Make all unit tests pass
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <functional>
#include <stdexcept>

using namespace std;

struct SpeedLimitDetected {
  unsigned short speed_limit;
};

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

typedef function<void(const SpeedUpdate&)> SpeedUpdateCallback;
typedef function<void(const CarDetected&)> CarDetectedCallback;
typedef function<void(const SpeedLimitDetected&)> SpeedLimitCallback;

struct IServiceBus {
    virtual ~IServiceBus() = default;
    virtual void publish(const BrakeCommand&) = 0;
    virtual void subscribe(SpeedUpdateCallback) = 0;
    virtual void subscribe(CarDetectedCallback) = 0;
    virtual void subscribe(SpeedLimitCallback) = 0;
};

struct MockServiceBus : IServiceBus {
    void publish(const BrakeCommand& cmd) override {
        commands_published++;
        last_command = cmd;
    };
    void subscribe(SpeedUpdateCallback callback) override {
        speed_update_callback = callback;
    };
    void subscribe(CarDetectedCallback callback) override {
        car_detected_callback = callback;
    };
    void subscribe(SpeedLimitCallback callback) override {
        speed_limit_callback = callback;
    };
    BrakeCommand last_command{};
    int commands_published{};
    SpeedUpdateCallback speed_update_callback{};
    CarDetectedCallback car_detected_callback{};
    SpeedLimitCallback speed_limit_callback{};
};

struct AutoBrake {
    AutoBrake(IServiceBus& bus): collision_threshold_s{ 5 }, speed_mps{}, speed_limit{ 39 } {
        bus.subscribe([this, &bus](const SpeedUpdate& update) {
          speed_mps = update.velocity_mps;
          if(speed_mps > speed_limit) bus.publish(BrakeCommand{ 0. });
        });
        bus.subscribe([this, &bus](const SpeedLimitDetected& update) {
          speed_limit = update.speed_limit;
          if(speed_mps > speed_limit) bus.publish(BrakeCommand{ 0. });
        });
        bus.subscribe([this, &bus](const CarDetected& cd) {
            auto relative_velocity_mps = speed_mps - cd.velocity_mps;
            auto time_to_collision_s = cd.distance_m / relative_velocity_mps;
            if(time_to_collision_s > 0 && time_to_collision_s <= collision_threshold_s) {
                bus.publish(BrakeCommand{ time_to_collision_s });
            }
        });
    }
    void set_collision_threshold_s(double x) {
        if(x < 1) throw runtime_error{ "Collision less than 1." };
        collision_threshold_s = x;
    }
    double get_collision_threshold_s() const {
        return collision_threshold_s;
    }
    double get_speed_mps() const {
        return speed_mps;
    }
    double get_speed_limit() const {
        return speed_limit;
    }

    private:
        double collision_threshold_s;
        double speed_mps;
        unsigned short speed_limit;
};

TEST_CASE("AutoBrake") {
    MockServiceBus bus{};
    AutoBrake auto_break{ bus };

    SECTION("initializes speed to zero") {
        REQUIRE(auto_break.get_speed_mps() == Approx(0));
    }

    SECTION("initializes last known speed to 39") {
        REQUIRE(auto_break.get_speed_limit() == Approx(39));
    }

    SECTION("initializes sensitivity to five") {
        REQUIRE(auto_break.get_collision_threshold_s() == Approx(5));
    }

    SECTION("throws when sensitivity less than one") {
        REQUIRE_THROWS(auto_break.set_collision_threshold_s(0.5L));
    }

    SECTION("saves speed limit after update") {
        bus.speed_limit_callback(SpeedLimitDetected{ 100 });
        REQUIRE(100L == auto_break.get_speed_limit());
        bus.speed_limit_callback(SpeedLimitDetected{ 50 });
        REQUIRE(50L == auto_break.get_speed_limit());
        bus.speed_limit_callback(SpeedLimitDetected{ 0 });
        REQUIRE(0L == auto_break.get_speed_limit());
    }

    SECTION("saves speed after update") {
        bus.speed_update_callback(SpeedUpdate{ 100L });
        REQUIRE(100L == auto_break.get_speed_mps());
        bus.speed_update_callback(SpeedUpdate{ 50L });
        REQUIRE(50L == auto_break.get_speed_mps());
        bus.speed_update_callback(SpeedUpdate{ 0L });
        REQUIRE(0L == auto_break.get_speed_mps());
    }

    SECTION("no alert when not imminent") {
        auto_break.set_collision_threshold_s(2L);
        bus.speed_update_callback(SpeedUpdate{ 100L });
        bus.car_detected_callback(CarDetected{ 1000L, 50L });
        REQUIRE(bus.commands_published == 1);
    }

    SECTION("alert when imminent") {
        auto_break.set_collision_threshold_s(10L);
        bus.speed_update_callback(SpeedUpdate{ 100L });
        bus.car_detected_callback(CarDetected{ 100L, 0L });
        REQUIRE(bus.commands_published == 2);
        REQUIRE(bus.last_command.time_to_collision_s == Approx(1));
    }

    SECTION("no break command when travelling under speed limit") {
        bus.speed_limit_callback(SpeedLimitDetected{ 35 });
        bus.speed_update_callback(SpeedUpdate{ 34 });
        REQUIRE(bus.commands_published == 0);
    }

    SECTION("break command when travelling above speed limit") {
        bus.speed_limit_callback(SpeedLimitDetected{ 35 });
        bus.speed_update_callback(SpeedUpdate{ 40 });
        REQUIRE(bus.commands_published == 1);
        REQUIRE(bus.last_command.time_to_collision_s == Approx(0));
    }

    SECTION("break command when travelling above speed limit, then speed limit is lowered") {
        bus.speed_limit_callback(SpeedLimitDetected{ 35 });
        bus.speed_update_callback(SpeedUpdate{ 30 });
        bus.speed_limit_callback(SpeedLimitDetected{ 25 });
        REQUIRE(bus.commands_published == 1);
        REQUIRE(bus.last_command.time_to_collision_s == Approx(0));
    }
}