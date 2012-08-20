#include "Angle.h"

Angle::Angle() {
  set(0, ANGLE_TYPE_RAD);
}

Angle::Angle(float angle, angletype type) {
  set(angle, type);
}

Angle::~Angle() {

}

void Angle::preserveInvalid() {
  if(angle_rad > (M_PI * 2) || fabs(angle_rad - (M_PI * 2)) < 0.001) {
    angle_rad -= ((int)(angle_rad / (M_PI * 2))) * (M_PI * 2);
  } else if(angle_rad < 0) {
    angle_rad += ((int)(-angle_rad / (M_PI * 2)) + 1) * (M_PI * 2);
  }
}

void Angle::set(float angle, angletype type) {
  if(type == ANGLE_TYPE_RAD) {
    angle_rad = angle;
  } else if(type == ANGLE_TYPE_DEG) {
    angle_rad = (angle / 360.0f) * M_PI * 2;
  }
  preserveInvalid();
}

float Angle::getDEG() {
  return (angle_rad * 360.0f) / M_2_PI;
}

float Angle::getRAD() {
  return angle_rad;
}

Angle Angle::operator+=(const Angle &angle) {
  this->operator+=(angle.angle_rad);
  return *this;
}

Angle Angle::operator+=(const float angle) {
  this->set(this->getRAD() + angle);
  preserveInvalid();
  return *this;
}

Angle Angle::operator-=(const Angle &angle) {
  this->operator-=(angle.angle_rad);
  return *this;
}

Angle Angle::operator-=(const float angle) {
  this->set(this->getRAD() - angle);
  return *this;
}

Angle operator+(Angle angle1, Angle angle2) {
  Angle res(angle1.angle_rad + angle2.angle_rad);
  return res;
}

Angle operator+(float angle1, Angle angle2) {
  Angle res(angle1 + angle2.angle_rad);
  return res;
}

Angle operator+(Angle angle1, float angle2) {
  Angle res(angle1.angle_rad + angle2);
  return res;
}

Angle operator-(Angle angle1, Angle angle2) {
  Angle res(angle1.angle_rad - angle2.angle_rad);
  return res;
}

Angle operator-(float angle1, Angle angle2) {
  Angle res(angle1 - angle2.angle_rad);
  return res;
}

Angle operator-(Angle angle1, float angle2) {
  Angle res(angle1.angle_rad - angle2);
  return res;
}

bool Angle::operator==(Angle angle) {
  return fabs(angle.angle_rad - this->angle_rad) < 0.001;
}

bool Angle::operator>(Angle angle1) {
  return this->angle_rad > angle1.getRAD();
}

bool Angle::operator<(Angle angle1) {
  return this->angle_rad < angle1.getRAD();
}

Angle Angle::operator-() const {
  return Angle(this->angle_rad - M_PI);
}

Angle &Angle::operator=(const Angle& angle) {
  if(this == &angle) {
    return *this;
  }

  this->set(angle.angle_rad);
  return *this;
}

