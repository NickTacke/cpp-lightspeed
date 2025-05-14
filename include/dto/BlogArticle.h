#ifndef LIGHTSPEED_DTOS_BLOGARTICLE_H
#define LIGHTSPEED_DTOS_BLOGARTICLE_H

#include <nlohmann/json.hpp>
#include <string>

#include "Blog.h"
#include "Language.h"
#include "Resource.h"

namespace Lightspeed {
namespace dto {

struct BlogArticle {
    int id;
    std::string createdAt;
    std::string updatedAt;
    std::string publishedAt;
    bool isPublished;
    std::string url;
    std::string title;
    std::string author;
    std::string summary;
    std::string content;
    Language language;
    Resource<Blog> blog;
};

inline void from_json(const nlohmann::json &j, BlogArticle &b) {
    j.at("id").get_to(b.id);
    j.at("createdAt").get_to(b.createdAt);
    j.at("updatedAt").get_to(b.updatedAt);
    j.at("publishedAt").get_to(b.publishedAt);
    j.at("isPublished").get_to(b.isPublished);
    j.at("url").get_to(b.url);
    j.at("title").get_to(b.title);
    j.at("author").get_to(b.author);
    j.at("summary").get_to(b.summary);
    j.at("content").get_to(b.content);
    j.at("language").get_to(b.language);
    j.at("blog").get_to(b.blog);
}

inline nlohmann::json to_json(const BlogArticle &b) {
    nlohmann::json j;
    j["id"] = b.id;
    j["createdAt"] = b.createdAt;
    j["updatedAt"] = b.updatedAt;
    j["publishedAt"] = b.publishedAt;
    j["isPublished"] = b.isPublished;
    j["url"] = b.url;
    j["title"] = b.title;
    j["author"] = b.author;
    j["summary"] = b.summary;
    j["content"] = b.content;
    j["language"] = to_json(b.language);
    j["blog"] = nlohmann::json::parse(b.blog.toJson());
    return j;
}

} // namespace dto
} // namespace Lightspeed

#endif