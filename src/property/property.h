#pragma once

#include <map>
#include <string>

namespace property {
using Coordinates = std::map<char, float>;

class Property {
public:
  Property();

  int getNumber();
  float getPrice();
  int getQtdFloors();
  float getSize();
  std::string getState();
  std::string getStreet();
  std::string getCity();
  std::string getDistrict();
  bool getIsMobiliated();
  double getCoordinates(char axis);

  void setNumber(int number);
  void setPrice(float price);
  void setQtdFloors(int qtdFloors);
  void setSize(int size);
  void setState(std::string state);
  void setStreet(std::string street);
  void setCity(std::string city);
  void setDistrict(std::string district);
  void setIsMobiliated(bool isMobiliated);
  void setCoordinates(char axis, double value);

private:
  int number;
  float price;
  int qtdFloors;
  float size;
  std::string state;
  std::string street;
  std::string city;
  std::string district;
  bool isMobiliated;
  std::map<char, double> coordinate;
};
} // namespace property
