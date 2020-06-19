// EXERCISES
// 16-1. Implement an output operator that prints information about the AutoBrake from
//       “An Extended Example: Taking a Brake” on page 283. Include the vehicle’s 
//       current collision threshold and speed.
#include <iostream>

struct AutoBrake {
    AutoBrake(double collision_threshold_s, double speed_mps)
        : collision_threshold_s{collision_threshold_s},
          speed_mps{speed_mps} {}

    private:
        double collision_threshold_s;
        double speed_mps;

    friend std::ostream& operator<<(std::ostream& s, AutoBrake& auto_brake);
};

std::ostream& operator<<(std::ostream& s, AutoBrake& auto_brake){
    return s << "AutoBrake(speed=" << auto_brake.speed_mps <<
           ", collision_threshold=" << auto_brake.collision_threshold_s << ")";
}

int main() {
    AutoBrake auto_break{10.0, 10.};
    std::cout << auto_break << std::endl;
}