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

    std::string _path = path;
    if (_path[0] != '/')
        _path = "/" + _path;
    auto result = client.Get(_path);

    if (result->status != httplib::StatusCode::OK_200)
        throw PtJsonException(result->status, result->body);
    nlohmann::json json = nlohmann::json::parse(result->body);
    if (json.contains("errors"))
        throw PtJsonException(result->status, result->body);
    return json;
}

void PtAPI::put(const std::string& path, const nlohmann::json& content) {

}
