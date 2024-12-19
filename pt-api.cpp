#include "pt-api.hpp"
#include "pt-errors.hpp"

PtAPI::PtAPI(
    const std::string& hostname,
    uint16_t port,
    const std::string& username,
    const std::string& password
) :
    hostname(hostname),
    port(port),
    username(username),
    password(password) {
}

nlohmann::json PtAPI::get(const std::string& path) {
    httplib::Client client(this->hostname, this->port);
    auto result = client.Get(path);
    if (result->status != httplib::StatusCode::OK_200)
        throw PtJsonException(result->status, result->body);
    nlohmann::json json = nlohmann::json::parse(result->body);
    if (json.contains("errors"))
        throw PtJsonException(result->status, result->body);
    return json;
}

nlohmann::json PtAPI::put(const std::string& path, const nlohmann::json& content) {
    httplib::Client client(this->hostname, this->port);
    std::string contentStr = content.dump();

    this->username + ":" + this->password;
    httplib::Headers headers {
        {"Authorization", "Basic bHJrdjp5MlF0Qms5cmp1UWhmN2VG"}
    };

    auto result = client.Put(
        path,
        headers,
        contentStr.c_str(),
        contentStr.size(),
        "application/json"
    );

    if (result->status != httplib::StatusCode::OK_200)
        throw PtJsonException(result->status, result->body);
    nlohmann::json json = nlohmann::json::parse(result->body);
    if (json.contains("errors"))
        throw PtJsonException(result->status, result->body);
    return json;
}
