/* conservated
 * 2012-04-09
 *
 *
 *
 *
#include "superclass.hpp"

template <class T>
booster::shared_ptr<T> controller::app_manager::acquire(std::string const& key, cppcms::service & srv) {
    booster::shared_ptr<T> ptr(new T(srv));
    m_app[key] = ptr;
    return ptr;
}

template <class T>
booster::shared_ptr<T> controller::app_manager::operator [](std::string const& key) {
    std::map<std::string,booster::shared_ptr<cppcms::application> >::iterator it,end;
    end = m_app.end();
    it = std::find(m_app.begin(),end,key);
    if (it != end) {
        return m_app[key];
    } else {
        return booster::shared_ptr<T>(0);
    }
}
*/
