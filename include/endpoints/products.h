#ifndef LIGHTSPEED_PRODUCTS_H
#define LIGHTSPEED_PRODUCTS_H

#include "dtos/Product.h"
#include <string>
#include <vector>

class LightspeedApi; // Forward declaration

class ProductsEndpoint {
public:
  ProductsEndpoint(LightspeedApi &api);

  // Corresponds to GET /products.json?page={page}&limit=250
  std::vector<Lightspeed::dto::Product> getPage(int page);

  // Corresponds to GET /products/count.json
  int getCount();

  // Corresponds to GET /products/{id}.json
  Lightspeed::dto::Product get(int id);

  // Corresponds to POST /products.json
  Lightspeed::dto::Product create(Lightspeed::dto::Product product);

private:
  LightspeedApi &api_;
};

#endif // LIGHTSPEED_PRODUCTS_H
