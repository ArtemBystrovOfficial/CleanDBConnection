#pragma once
#include <string>
#include <vector>
#include "../util/tagged_uuid.h"
#include <optional>

namespace domain {

namespace detail {
struct AuthorTag {};
}  // namespace detail

using AuthorId = util::TaggedUUID<detail::AuthorTag>;

class Author {
public:
    Author(AuthorId id, std::string name)
        : id_(std::move(id))
        , name_(std::move(name)) {
    }

    const AuthorId& GetId() const noexcept {
        return id_;
    }

    const std::string& GetName() const noexcept {
        return name_;
    }

private:
    AuthorId id_;
    std::string name_;
};

class AuthorRepository {
public:
    using list_authors_t = std::vector<Author>;

    virtual void DeleteAuthorAndDependencies(const Author& author) = 0;
    virtual void Save(const Author& author) = 0;
    virtual list_authors_t GetList() = 0;
    virtual std::optional <domain::Author> FindAuthorByName(const std::string &) = 0;

protected:
    ~AuthorRepository() = default;
};

}  // namespace domain
