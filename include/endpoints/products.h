#ifndef LIGHTSPEED_PRODUCTS_H
#define LIGHTSPEED_PRODUCTS_H

#include <string>
#include <vector>

class LightspeedApi; // Forward declaration

class ProductsEndpoint {
public:
  ProductsEndpoint(LightspeedApi &api);

  // Corresponds to GET /products.json?page={page}&limit=250
  std::string getPage(int page);

private:
  LightspeedApi &api_;
};
#endif
