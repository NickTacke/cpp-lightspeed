#ifndef LIGHTSPEED_DTOS_VARIANT_H
#define LIGHTSPEED_DTOS_VARIANT_H

#include <nlohmann/json.hpp>
#include <string>

#include "Resource.h"

namespace Lightspeed {
namespace dto {

struct Product; // Forward declaration

enum Tracking {
    DISABLED,
    ENABLED,
    INDICATED
};

NLOHMANN_JSON_SERIALIZE_ENUM(Tracking, {
    {Tracking::DISABLED, "disabled"},
    {Tracking::ENABLED, "enabled"},
    {Tracking::INDICATED, "indicated"}
})

enum WeightUnit {
    G,
    KG,
    OZ,
    LB
};

NLOHMANN_JSON_SERIALIZE_ENUM(WeightUnit, {
    {WeightUnit::G, "g"},
    {WeightUnit::KG, "kg"},
    {WeightUnit::OZ, "oz"},
    {WeightUnit::LB, "lb"}
})

struct Variant {
    int id;
    std::string createdAt;
    std::string updatedAt;
    bool isDefault;
    int sortOrder;
    std::string articleCode;
    std::string ean; // EAB (bar) code
    std::string sku; // Stock Keeping Unit
    std::string hs; // Harmonized System code
    float priceExcl;
    float priceIncl;
    float priceCost;
    float oldPriceExcl;
    float oldPriceIncl;
    Tracking stockTracking;
    int stockLevel;
    int stockAlert;
    int stockMinimum;
    int stockSold;
    int stockBuyMinimum;
    int stockBuyMaximum;
    int weight;
    std::string weightValue;
    WeightUnit weightUnit;
    int volume;
    float volumeValue;
    std::string volumeUnit;
    int colli;
    int sizeX;
    int sizeY;
    int sizeZ;
    std::string sizeXValue;
    std::string sizeYValue;
    std::string sizeZValue;
    std::string sizeUnit;
    std::string matrix;
    std::string title;
    std::string taxType;
    float unitPrice;
    std::string unitUnit;
    // TODO: Add options, tax, movements, metafields, additionalcost & image
    Resource<Product> product;
};

inline void to_json(nlohmann::json& j, const Variant& v) {
    j = nlohmann::json{
        {"id", v.id},
        {"createdAt", v.createdAt},
        {"updatedAt", v.updatedAt},
        {"isDefault", v.isDefault},
        {"sortOrder", v.sortOrder},
        {"articleCode", v.articleCode},
        {"ean", v.ean},
        {"sku", v.sku},
        {"hs", v.hs},
        {"priceExcl", v.priceExcl},
        {"priceIncl", v.priceIncl},
        {"priceCost", v.priceCost},
        {"oldPriceExcl", v.oldPriceExcl},
        {"oldPriceIncl", v.oldPriceIncl},
        {"stockTracking", v.stockTracking},
        {"stockLevel", v.stockLevel},
        {"stockAlert", v.stockAlert},
        {"stockMinimum", v.stockMinimum},
        {"stockSold", v.stockSold},
        {"stockBuyMinimum", v.stockBuyMinimum},
        {"stockBuyMaximum", v.stockBuyMaximum},
        {"weight", v.weight},
        {"weightValue", v.weightValue},
        {"weightUnit", v.weightUnit},
        {"volume", v.volume},
        {"volumeValue", v.volumeValue},
        {"volumeUnit", v.volumeUnit},
        {"colli", v.colli},
        {"sizeX", v.sizeX},
        {"sizeY", v.sizeY},
        {"sizeZ", v.sizeZ},
        {"sizeXValue", v.sizeXValue},
        {"sizeYValue", v.sizeYValue},
        {"sizeZValue", v.sizeZValue},
        {"sizeUnit", v.sizeUnit},
        {"matrix", v.matrix},
        {"title", v.title},
        {"taxType", v.taxType},
        {"unitPrice", v.unitPrice},
        {"unitUnit", v.unitUnit},
        {"product", v.product}
    };
}

inline void from_json(const nlohmann::json& j, Variant& v) {
    j.at("id").get_to(v.id);
    j.at("createdAt").get_to(v.createdAt);
    j.at("updatedAt").get_to(v.updatedAt);
    j.at("isDefault").get_to(v.isDefault);
    j.at("sortOrder").get_to(v.sortOrder);
    j.at("articleCode").get_to(v.articleCode);
    j.at("ean").get_to(v.ean);
    j.at("sku").get_to(v.sku);
    j.at("hs").is_null() ? v.hs = "" : j.at("hs").get_to(v.hs);
    j.at("priceExcl").get_to(v.priceExcl);
    j.at("priceIncl").get_to(v.priceIncl);
    j.at("priceCost").get_to(v.priceCost);
    j.at("oldPriceExcl").get_to(v.oldPriceExcl);
    j.at("oldPriceIncl").get_to(v.oldPriceIncl);
    j.at("stockTracking").get_to(v.stockTracking);
    j.at("stockLevel").get_to(v.stockLevel);
    j.at("stockAlert").get_to(v.stockAlert);
    j.at("stockMinimum").get_to(v.stockMinimum);
    j.at("stockSold").get_to(v.stockSold);
    j.at("stockBuyMinimum").get_to(v.stockBuyMinimum);
    j.at("stockBuyMaximum").get_to(v.stockBuyMaximum);
    j.at("weight").get_to(v.weight);
    j.at("weightValue").get_to(v.weightValue);
    j.at("weightUnit").get_to(v.weightUnit);
    j.at("volume").get_to(v.volume);
    j.at("volumeValue").get_to(v.volumeValue);
    j.at("volumeUnit").get_to(v.volumeUnit);
    j.at("colli").get_to(v.colli);
    j.at("sizeX").get_to(v.sizeX);
    j.at("sizeY").get_to(v.sizeY);
    j.at("sizeZ").get_to(v.sizeZ);
    j.at("sizeXValue").get_to(v.sizeXValue);
    j.at("sizeYValue").get_to(v.sizeYValue);
    j.at("sizeZValue").get_to(v.sizeZValue);
    j.at("sizeUnit").get_to(v.sizeUnit);
    j.at("matrix").is_boolean() ? v.matrix = "false" : j.at("matrix").get_to(v.matrix);
    j.at("title").get_to(v.title);
    j.at("taxType").get_to(v.taxType);
    j.at("unitPrice").get_to(v.unitPrice);
    j.at("unitUnit").get_to(v.unitUnit);
    j.at("product").get_to(v.product);
}

} // namespace dto
} // namespace Lightspeed

#endif // LIGHTSPEED_DTOS_VARIANT_H