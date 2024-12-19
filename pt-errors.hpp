#ifndef __PT_ERRORS__
#define __PT_ERRORS__

#include <string>
#include "cpp-httplib/httplib.h"
#include "nlohmann/json.hpp"

struct PtException : public std::exception {
private:
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
};

struct PtJsonException : public PtException {
private:
    std::string m_msg;

public:
    std::vector<PtError> errors;

    PtJsonException(int statusCode, const std::string& body) :
        PtException(statusCode, body), m_msg("") {
        nlohmann::json json = nlohmann::json::parse(body);
        for (auto& error : json["errors"]) {
            std::string codeStr = error["code"]; // TODO why is it string?
            PtError ptError{std::stoi(codeStr), error["title"]};
            this->errors.push_back(ptError);
            m_msg += std::to_string(ptError.code) + " " + ptError.title + "\n";
        }
        m_msg.pop_back();
    }

    const char* what() const noexcept override { return this->m_msg.c_str(); }
};

#endif
