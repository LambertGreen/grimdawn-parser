#include "tutorial_pages.hpp"

json tutorial_pages::get_json() const {
  json j;

  ADD_TO_JSON(j, pages);
  return j;
};
