/* Error definition of PtAPI library.
 */

#ifndef __PT_ERRORS__
#define __PT_ERRORS__

#include <string>
#include <optional>
#include "httplib.h"
#include "json.hpp"

/* Raw PtException is generated, when PTserver returns http code != 200 OK.
 * The PtException contains raw body as a std::string, no json parsing is
 * performed.
 */
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


/* PtJsonException is a standard PTserver's return error - server responds with
 * 200 OK but returns json with "errors" list. Each error is represented as a
 * PtError struct instance.
 */
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
