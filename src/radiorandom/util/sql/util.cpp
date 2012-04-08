#include "util.hpp"

std::vector<std::string> util::sql::parse_sql_schema(std::istream &stream) {
    std::vector<std::string> result;
    std::string stmt;

    int c = -1;
    bool instring = false;

    while ((c=stream.get()) != -1) {
        char ch = (char)c;
        stmt.push_back(ch);
        switch (ch) {
            case '\'':
                if (!instring) {
                    instring = true;
                } else {
                    if ('\'' == (char)stream.peek()) {
                        stream.get();
                    } else {
                        instring = false;
                    }
                }
                break;
            case ';':
                if (!instring) {
                    result.push_back(stmt);
                    stmt.clear();
                }
                break;
        }
    }
    return result;
}
