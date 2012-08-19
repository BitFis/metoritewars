#ifndef _ANGLE_H
#define _ANGLE_H

#include <cmath>

typedef enum {ANGLE_TYPE_DEG, ANGLE_TYPE_RAD} angletype;

class Angle {
  private:
    float angle_rad;
    void preserveInvalid();

  public:
    Angle(float angle, angletype type = ANGLE_TYPE_RAD);
    virtual ~Angle();

    float getDEG();
    float getRAD();

    void set(float angle, angletype type = ANGLE_TYPE_RAD);

    Angle operator+=(const Angle &angle);
    Angle operator+=(float angle);
    Angle operator-=(const Angle &angle);
    Angle operator-=(float angle);
    friend Angle operator+(Angle angle1, Angle angle2);
    friend Angle operator+(Angle angle1, float angle2);
    friend Angle operator+(float angle1, Angle angle2);
    friend Angle operator-(Angle angle1, Angle angle2);
    friend Angle operator-(float angle1, Angle angle2);
    friend Angle operator-(Angle angle1, float angle2);
    bool operator<(Angle angle1);
    bool operator>(Angle angle1);
    bool operator==(Angle angle);
    Angle operator-() const;
    Angle &operator=(const Angle& angle);
    Angle &operator=(const float angle);

};

#endif/* _ANGLE_H */
