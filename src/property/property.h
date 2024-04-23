#pragma once

#include <map>
#include <string>

namespace property {
typedef std::map<char, float> Coordinates;

class Property {
public:
  Property();

  Coordinates getCoordinates();
  float getSize();
  float getQtdBathroom();
  float getQtdRoom();
  float getPrice();
  bool isMobiliated();
  bool hasLivingRoom();
  bool hasKitchen();

  void setCoordinates(float x, float y);
  void setSize(float size);
  void setQtdBathroom(int qtdBathroom);
  void setQtdRoom(int qtdRoom);
  void setPrice(float price);
  void setIsMobiliated(bool isMobiliated);
  void setHasLivingRoom(bool hasLivingRoom);
  void setHasKitchen(bool hasKitchen);

private:
  Coordinates coordinates;
  float size;
  int qtdBathroom;
  int qtdRoom;
  float price;
  bool mobiliated;
  bool livingRoom;
  bool kitchen;
};

class House : public Property {
public:
  House();

private:
  std::string city;
  std::string state;
  std::string street;
  std::string district;
  std::string cep;
  int number;
};

class Apartment : public Property {};

class Address {};
} // namespace property
