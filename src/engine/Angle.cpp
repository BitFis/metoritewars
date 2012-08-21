#include "Angle.h"

Angle::Angle() {
  set(0, ANGLE_TYPE_DEG);
}

Angle::Angle(float angle, angletype type) {
  set(angle, type);
}

Angle::~Angle() {

}

void Angle::preserveInvalid() {
  if(angle_deg >= ANGLE_MAX) {
    angle_deg -= ((int)(angle_deg / ANGLE_MAX)) * ANGLE_MAX;
  } else if(angle_deg < 0) {
    angle_deg += ((int)((-angle_deg) / ANGLE_MAX) + 1) * ANGLE_MAX;
  }
}

void Angle::set(float angle, angletype type) {
  set((int)round(angle * 1000), type);
}

void Angle::set(int angle, angletype type) {
  if(type == ANGLE_TYPE_DEG) {
    angle_deg = angle;
  } else if(type == ANGLE_TYPE_RAD) {
    angle_deg = (angle / M_PI) * 180.0f;
  }
  preserveInvalid();
}

float Angle::getDEG() const {
  return angle_deg / 1000.0f;
}

float Angle::getRAD() const {
  return (angle_deg / 180.0f * M_PI) / 1000.0f;
}

Angle Angle::operator+=(const Angle &angle) {
  this->operator+=(angle.getRAD());
  return *this;
}

Angle Angle::operator+=(const float angle) {
  this->set(this->getRAD() + angle);
  preserveInvalid();
  return *this;
}

Angle Angle::operator-=(const Angle &angle) {
  this->operator-=(angle.getRAD());
  return *this;
}

Angle Angle::operator-=(const float angle) {
  this->set(this->getRAD() - angle);
  return *this;
}

Angle operator+(Angle angle1, Angle angle2) {
  Angle res(angle1.getRAD() + angle1.getRAD());
  return res;
}

Angle operator+(float angle1, Angle angle2) {
  Angle res(angle1 + angle2.getRAD());
  return res;
}

Angle operator+(Angle angle1, float angle2) {
  Angle res(angle1.getRAD() + angle2);
  return res;
}

Angle operator-(Angle angle1, Angle angle2) {
  Angle res(angle1.getRAD() - angle2.getRAD());
  return res;
}

Angle operator-(float angle1, Angle angle2) {
  Angle res(angle1 - angle2.getRAD());
  return res;
}

Angle operator-(Angle angle1, float angle2) {
  Angle res(angle1.getRAD()  - angle2);
  return res;
}

bool Angle::operator==(Angle angle) {
  return abs(angle.angle_deg - this->angle_deg) < 100 || abs(abs(angle.angle_deg - this->angle_deg) - ANGLE_MAX) < 100;
}

bool Angle::operator>(Angle angle1) {
  return this->getDEG() > angle1.getDEG();
}

bool Angle::operator<(Angle angle1) {
  return this->getDEG() < angle1.getDEG();
}

Angle Angle::operator-() const {
  return Angle((this->angle_deg - (ANGLE_MAX / 2)) / 1000.f, ANGLE_TYPE_DEG);
}

Angle &Angle::operator=(const Angle& angle) {
  if(this == &angle) {
    return *this;
  }

  this->set(angle.angle_deg, ANGLE_TYPE_DEG);
  return *this;
}

