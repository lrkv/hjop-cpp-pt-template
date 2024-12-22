#ifndef __PT_API__
#define __PT_API__

#include <string>
#include "httplib.h"
#include "json.hpp"

class PtAPI {
public:
    inline static const std::string DEFAULT_HOSTNAME = "localhost";
    inline static constexpr uint16_t DEFAULT_PORT = 5823;

    std::string hostname;
    uint16_t port;
    std::string username;
    std::string password;

    PtAPI(
        const std::string& hostname = DEFAULT_HOSTNAME,
        uint16_t port = DEFAULT_PORT,
        const std::string& username = "",
        const std::string& password = ""
    );
    virtual ~PtAPI() = default;

    nlohmann::json get(const std::string& path);
    nlohmann::json put(const std::string& path, const nlohmann::json& content);
};

#endif
