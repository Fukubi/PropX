#include "property.h"

namespace property {
Property::Property() : number(0), price(0.0f), qtdFloors(0), size(0), id(0) {}

Property::Property(long id)
    : number(0), price(0.0f), qtdFloors(0), size(0), id(id) {}

int Property::getNumber() { return number; }

float Property::getPrice() { return price; }

int Property::getQtdFloors() { return qtdFloors; }

float Property::getSize() { return size; }

std::string Property::getState() { return state; }

std::string Property::getStreet() { return street; }

std::string Property::getCity() { return city; }

std::string Property::getDistrict() { return district; }

bool Property::getIsMobiliated() { return isMobiliated; }

double Property::getCoordinates(char axis) { return coordinate[axis]; }

long Property::getId() { return this->id; }

void Property::setNumber(int number) {
  if (number < 0) {
    number = 0;
  }

  this->number = number;
}

void Property::setPrice(float price) {
  if (price < 0) {
    price = 0;
  }

  this->price = price;
}

void Property::setQtdFloors(int qtdFloors) {
  if (qtdFloors < 0) {
    qtdFloors = 0;
  }

  this->qtdFloors = qtdFloors;
}

void Property::setSize(int size) {
  if (size < 0) {
    size = 0;
  }

  this->size = size;
}

void Property::setState(std::string state) { this->state = state; }

void Property::setStreet(std::string street) { this->street = street; }

void Property::setCity(std::string city) { this->city = city; }

void Property::setDistrict(std::string district) { this->district = district; }

void Property::setIsMobiliated(bool isMobiliated) {
  this->isMobiliated = isMobiliated;
}

void Property::setCoordinates(char axis, double value) {
  coordinate[axis] = value;
}
} // namespace property
