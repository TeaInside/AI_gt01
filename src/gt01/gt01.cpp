
#include <gt01/gt01.hpp>

Php::Value tea_gt01(Php::Parameters &p) {
	gt01 *t = new gt01;

	t->set_name(p[1], p[2]);
	t->set_text(p[0]);

	std::string response;
	bool got_response = t->exec();

	if (got_response) {
		response = t->get_response();
	}

	delete t;
	t = nullptr;

	return got_response ? response : "";
}

void gt01::set_name(std::string name, std::string nickname) {
	this->name = name;
	this->nickname = nickname;
}

void gt01::set_text(std::string text) {
	this->text = text;
}

bool gt01::exec() {
	return false;
}

std::string gt01::get_response() {
	return this->response;
}

void gt01::set_response(std::string response) {
	this->response = response;
}
