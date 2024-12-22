#ifndef __PT_ERRORS__
#define __PT_ERRORS__

#include <string>
#include <optional>
#include "cpp-httplib/httplib.h"
#include "nlohmann/json.hpp"

struct PtException : public std::exception {
protected:
    std::string m_msg;

public:
    int statusCode;
    std::string body;

    PtException(int statusCode, const std::string& body) :
        statusCode(statusCode),
        body(body),
        m_msg(std::to_string(statusCode) + " " + httplib::status_message(statusCode)+": "+body)
        {}
    const char* what() const noexcept override { return this->m_msg.c_str(); }
};

struct PtError {
    int code;
    std::string title;
    std::optional<std::string> detail;
};

struct PtJsonException : public PtException {
    std::vector<PtError> errors; // PT server sends array of errors

    PtJsonException(int statusCode, const std::string& body) : PtException(statusCode, body) {
        this->m_msg = "";
        nlohmann::json json = nlohmann::json::parse(body);
        for (auto& error : json["errors"]) {
            std::optional<std::string> detail;
            if (error.contains("detail"))
                detail = error["detail"];
            std::string codeStr = error["code"]; // TODO why is it string?
            PtError ptError{std::stoi(codeStr), error["title"], detail};
            this->errors.push_back(ptError);
            this->m_msg += error.dump() + '\n';
        }
        this->m_msg.pop_back();
    }
};

#endif
