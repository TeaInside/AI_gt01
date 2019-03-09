
#include <gt01/gt01.hpp>

extern "C" {
    PHPCPP_EXPORT void *get_module() {
        static Php::Extension extension("tea_gt01", "1.0");
        extension.add<tea_gt01>("tea_gt01", {
        	Php::ByVal("text", Php::Type::String),
        	Php::ByVal("full_name", Php::Type::String),
        	Php::ByVal("nick_name", Php::Type::String)
        });
        return extension;
    }
}
