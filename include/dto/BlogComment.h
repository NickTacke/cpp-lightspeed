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

inline void from_json(const nlohmann::json &j, BlogComment &b) {
    j.at("id").get_to(b.id);
    j.at("createdAt").get_to(b.createdAt);
    j.at("updatedAt").get_to(b.updatedAt);
    j.at("isPublished").get_to(b.isPublished);
    j.at("from").get_to(b.from);
    j.at("name").get_to(b.name);
    j.at("email").get_to(b.email);
    j.at("content").get_to(b.content);
    j.at("language").get_to(b.language);
    j.at("blog").get_to(b.blog);
    j.at("blogArticle").get_to(b.blogArticle);
}

inline void to_json(nlohmann::json &j, const BlogComment &b) {
    j = nlohmann::json{
        {"id", b.id},
        {"createdAt", b.createdAt},
        {"updatedAt", b.updatedAt},
        {"isPublished", b.isPublished},
        {"from", b.from},
        {"name", b.name},
        {"email", b.email},
        {"content", b.content},
        {"language", b.language},
        {"blog", b.blog},
        {"blogArticle", b.blogArticle}
    };
}

} // namespace dto
} // namespace Lightspeed

#endif