#include "single.hpp"

void single::sql::perform_update(const std::string &stmt) {
    global_sql_mutex.lock();
    update << stmt << cppdb::exec;
    global_sql_mutex.unlock();
}

void single::sql::perform_update(std::istream &stream) {
    global_sql_mutex.lock();
    std::string stmt;

    int ci = -1;
    bool instring = false;

    while ((ci=stream.get()) != -1) {
        char ch = (char)ci;
        stmt.push_back(ch);
        switch(ch) {
            case '\'':
                if (!instring) {
                    instring = true;
                } else if ('\'' != (char)stream.peek()) {
                    instring = false;
                }
                break;
            case ';':
                if (!instring) {
                    update << stmt << cppdb::exec;
                    stmt.clear();
                }
                break;
        }
    }
    global_sql_mutex.unlock();
}
