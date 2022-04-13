// The area of a circle is defined as πr^2. Estimate π to 3 decimal places using a Monte Carlo method.

// Hint: The basic equation of a circle is x2 + y2 = r2.

#include <random>
#include <cstdio>
#include <cmath>
#include <iostream>

//Higher numbers will on average result on a better approximation
#define LOOP_NUM 100000

struct Point2D{
public:
    Point2D(double x = 0, double y = 0): x_(x), y_(y){}

    inline double x() {return x_;}
    inline double y() {return y_;}

    static Point2D GeneratePoint();
    double  DistanceFromOrigin();

    friend std::ostream & operator << (std::ostream &out, const Point2D &point);
private:
    double x_;
    double y_;
};


Point2D Point2D::GeneratePoint(){
    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_real_distribution<float> distr(0, 1);
    float x = distr(eng);
    float y = distr(eng);

    return Point2D(x, y);
}

std::ostream & operator<<(std::ostream &out, const Point2D &point){
     out << "(" << point.x_ << ", " << point.y_ << ")";
     return out;
}

double Point2D::DistanceFromOrigin(){
    double radicand = std::abs(x_*x_ + y_*y_);

    return std::sqrt(radicand);
}

int main(int argc, char **argv){
    double count_in_circle = 0.0;
    double total = 0.0;

    for(int i = 0; i < LOOP_NUM; i++){
         Point2D point = Point2D::GeneratePoint();
         total+=1;
         if(point.DistanceFromOrigin() <= 1) count_in_circle+=1;
    }

    double pi_estimate = (4*count_in_circle)/total;

    printf("Using the Monte Carlo method, the estimate for PI is %.2f\n", pi_estimate);

    return 0;
}