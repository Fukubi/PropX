#include "property.h"

namespace property {
Property::Property() {
  this->size = 0;
  this->qtdBathroom = 0;
  this->qtdRoom = 0;
  this->price = 0;
  this->mobiliated = false;
  this->livingRoom = false;
  this->kitchen = false;
}

Coordinates Property::getCoordinates() { return coordinates; }

float Property::getSize() { return this->size; }

float Property::getQtdBathroom() { return this->qtdBathroom; }

float Property::getQtdRoom() { return this->qtdRoom; }

float Property::getPrice() { return this->price; }

bool Property::isMobiliated() { return this->mobiliated; }

bool Property::hasLivingRoom() { return this->livingRoom; }

bool Property::hasKitchen() { return this->kitchen; }

void Property::setCoordinates(float x, float y) {
  coordinates['x'] = x;
  coordinates['y'] = y;
}

void Property::setSize(float size) {
  if (size < 0) {
    size = 0;
  }

  this->size = size;
}

void Property::setQtdBathroom(int qtdBathroom) {
  if (qtdBathroom < 0) {
    qtdBathroom = 0;
  }

  this->qtdBathroom = qtdBathroom;
}

void Property::setQtdRoom(int qtdRoom) {
  if (qtdRoom < 0) {
    qtdRoom = 0;
  }

  this->qtdRoom = qtdRoom;
}

void Property::setPrice(float price) {
  if (price < 0) {
    price = 0;
  }

  this->price = price;
}
void Property::setIsMobiliated(bool isMobiliated) {
  this->mobiliated = isMobiliated;
}
void Property::setHasLivingRoom(bool hasLivingRoom) {
  this->livingRoom = hasLivingRoom;
}
void Property::setHasKitchen(bool hasKitchen) { this->kitchen = hasKitchen; }
House::House() : Property() {}
} // namespace property
