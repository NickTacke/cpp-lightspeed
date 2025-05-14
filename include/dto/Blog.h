#ifndef LIGHTSPEED_DTOS_BLOG_H
#define LIGHTSPEED_DTOS_BLOG_H

#include <nlohmann/json.hpp>
#include <string>

namespace Lightspeed {
namespace dto {

enum Commentable {
    no,
    after_approval,
    without_approval
};

struct Blog {
    int id;
    std::string createdAt;
    std::string updatedAt;
    int sortOrder;
    Commentable commentable;
    std::string url;
    std::string title;
    // TODO: Add resources
};

inline void from_json(const nlohmann::json &j, Blog &b) {
    j.at("id").get_to(b.id);
    j.at("createdAt").get_to(b.createdAt);
    j.at("updatedAt").get_to(b.updatedAt);
    j.at("sortOrder").get_to(b.sortOrder);
    j.at("commentable").get_to(b.commentable);
    j.at("url").get_to(b.url);
    j.at("title").get_to(b.title);
}

inline void to_json(nlohmann::json &j, const Blog &b) {
    j = nlohmann::json{
        {"id", b.id},
        {"createdAt", b.createdAt},
        {"updatedAt", b.updatedAt},
        {"sortOrder", b.sortOrder},
        {"commentable", b.commentable},
        {"url", b.url},
        {"title", b.title}
    };
}

} // namespace dto
} // namespace Lightspeed

#endif