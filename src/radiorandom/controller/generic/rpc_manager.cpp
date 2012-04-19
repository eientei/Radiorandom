/* conservated
 * 2012-04-09
 *
 *
 *
 *
#include "superclass.hpp"

template <class T>
booster::shared_ptr<T> controller::rpc_manager::acquire(std::string const& key, cppcms::service & srv) {
    booster::shared_ptr<T> ptr(new T(srv));
    m_rpc[key] = ptr;
    return ptr;
}
template <class T>
booster::shared_ptr<T> controller::rpc_manager::operator [](std::string const& key) {
    std::map<std::string,booster::shared_ptr<cppcms::rpc::json_rpc_server> >::iterator it,end;
    end = m_rpc.end();
    it = std::find(m_rpc.begin(),end,key);
    if (it != end) {
        return m_rpc[key];
    } else {
        return booster::shared_ptr<T>(0);
    }
}
*/
