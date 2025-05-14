#ifndef LIGHTSPEED_DTOS_BLOGCOMMENT_H
#define LIGHTSPEED_DTOS_BLOGCOMMENT_H

#include <nlohmann/json.hpp>
#include <string>

#include "Blog.h"
#include "BlogArticle.h"
#include "Language.h"
#include "Resource.h"

namespace Lightspeed {
namespace dto {

struct BlogComment {
    int id;
    std::string createdAt;
    std::string updatedAt;
    bool isPublished;
    std::string from;
    std::string name;
    std::string email;
    std::string content;
    Language language;
    Resource<Blog> blog;
    Resource<BlogArticle> blogArticle;
};

} // namespace dto
} // namespace Lightspeed

#endif