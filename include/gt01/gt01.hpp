
#ifndef GT01_HPP
#define GT01_HPP

#include <string>
#include <phpcpp.h>

Php::Value tea_gt01(Php::Parameters &p);

class gt01
{
public:
	void set_name(std::string name, std::string nickname);
	void set_text(std::string text);
	bool exec();
	std::string get_response();
private:
	bool check();
	void set_response(std::string response);
	std::string text;
	std::string name;
	std::string nickname;
	std::string response;
};

#endif
