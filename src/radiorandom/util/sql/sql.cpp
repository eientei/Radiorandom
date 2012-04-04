#include "sql.hpp"

std::string util::sql::salt_password(const std::string &salt, const std::string &raw_password) {
    char * raw_result = NULL;
    asprintf(&raw_result,salt.c_str(),raw_password.c_str());
    std::string result(raw_result);
    free(raw_result);
    return result;
}

std::string util::sql::hash_password(const std::string &password) {
    unsigned char md[20];
    char raw_result[41];
    SHA1((const unsigned char*)password.c_str(),password.length(),md);
    char * p = raw_result;
    for (int i = 0; i < 20; i++, p+=2) {
        snprintf(p,3,"%02x",md[i]);
    }
    std::string result(raw_result);
    return result;
}


std::string util::sql::make_password_hash(const std::string &salt, const std::string &raw_password) {
    return hash_password(salt_password(salt,raw_password));
}









bool util::sql::add_user(const std::string &name, const std::string &salt, const std::string &password, const std::string &email) {
    //std::string password_hash = make_password_hash(salt,password);
    return false;
}
