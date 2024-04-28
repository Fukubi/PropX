#pragma once

#include <map>
#include <string>

/// @brief Namespace for properties related entities
namespace property {
/// @brief A collection used for coordinates with keys 'x' and 'y'
using Coordinates = std::map<char, float>;

/// @brief The representation of a generic property
class Property {
public:
  /// @brief Default constructor with everything blank
  Property();

  /// @brief Set a ID but use the others value as default (as in the default
  /// constructor)
  /// @param id The ID of the Property
  Property(long id);

  /// @brief Get the number of the property
  /// @return The number of the property
  int getNumber();
  /// @brief Get the price of the property
  /// @return The price of the property
  float getPrice();
  /// @brief Get the quantity of rooms in the property
  /// @return The quantity of rooms in the property
  int getQtdFloors();
  /// @brief Get the size of the property in square meters
  /// @return The size of the property in square meters
  float getSize();
  /// @brief Get the name of the State the property is located
  /// @return The name of the State the property is located
  std::string getState();
  /// @brief Get the name of the street the property is located
  /// @return The name of the street the property is located
  std::string getStreet();
  /// @brief Get the name of the city the property is located
  /// @return The name of the city the property is located
  std::string getCity();
  /// @brief Get the name of the district the property is located
  /// @return The name of the city the property is located
  std::string getDistrict();
  /// @brief Get if the property is mobiliated
  /// @return True if is mobiliated, false otherwise
  bool getIsMobiliated();
  /// @brief Get the coordinate in specific axis
  /// @param axis The axis of the coordinate
  /// @return The coordinate value
  double getCoordinates(char axis);
  /// @brief Get the ID of the Property
  /// @return The ID of the Property
  long getId();

  /// @brief Set the number to the property
  /// @param number The number
  void setNumber(int number);
  /// @brief Set the price to the property
  /// @param price The price
  void setPrice(float price);
  /// @brief Set the quantity of floors of the property
  /// @param qtdFloors The quantity of floors
  void setQtdFloors(int qtdFloors);
  /// @brief Set the size of the property (in square meters)
  /// @param size The size (in square meters)
  void setSize(int size);
  /// @brief Set the name of the state of the property
  /// @param state The name of the state
  void setState(std::string state);
  /// @brief Set the name of the street of the property
  /// @param street The name of the street
  void setStreet(std::string street);
  /// @brief Set the name of the city of the property
  /// @param city The name of the city
  void setCity(std::string city);
  /// @brief Set the name of the district of the property
  /// @param district The name of the district
  void setDistrict(std::string district);
  /// @brief Set if the property is mobiliated
  /// @param isMobiliated If the property is mobiliated
  void setIsMobiliated(bool isMobiliated);
  /// @brief Set the coordinate of specific axis
  /// @param axis The axis to set the coordinate
  /// @param value The coordinate value
  void setCoordinates(char axis, double value);

private:
  /// @brief The ID of the property in the database
  long id;
  /// @brief The number of the property
  int number;
  /// @brief The price of the property
  float price;
  /// @brief The quantity of floors in the property
  int qtdFloors;
  /// @brief The size of the property (in square meters)
  float size;
  /// @brief The name of the state
  std::string state;
  /// @brief The name of the street
  std::string street;
  /// @brief The name of the city
  std::string city;
  /// @brief The name of the district
  std::string district;
  /// @brief If the property is mobiliated
  bool isMobiliated;
  /// @brief The coordinates of the property
  std::map<char, double> coordinate;
};
} // namespace property
