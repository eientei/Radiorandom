#include "sql.hpp"

std::vector<std::string> util::sql::read_file_to_stmts(const std::string &filename) {
    std::ifstream schema_file(filename.c_str());
    std::vector<std::string> sql_stmts;
    std::string stmt;

    int ci = -1;
    bool instring = false;

    while ((ci=schema_file.get()) != -1) {
        char ch = (char)ci;
        stmt.push_back(ch);
        switch(ch) {
            case '\'':
                if (!instring) {
                    instring = true;
                } else if ('\'' != (char)schema_file.peek()) {
                    instring = false;
                }
                break;
            case ';':
                if (!instring) {
                    sql_stmts.push_back(stmt);
                    stmt.clear();
                }
                break;
        }
    }
    return sql_stmts;
}
