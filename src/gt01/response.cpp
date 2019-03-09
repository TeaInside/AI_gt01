
#include <stdint.h>
#include <stdlib.h>
#include <phpcpp.h>
#include <gt01/gt01.hpp>

#define ST(A,B) \
	if (h >= A && h <= B)

#define RET() \
	int arrsize = sizeof(a)/sizeof(a[0]) - 1; \
	int offsetResult = Php::call("rand", 0, arrsize); \
	this->set_response(std::string(a[offsetResult])); \
	return true;

#define RS(SIZE) \
	const char a[][SIZE] = \

#define SET_PAT(PAT) \
	if (Php::call("preg_match", PAT, this->text)) 

bool gt01::check() {

	uint8_t h = atoi(Php::call("date", "H"));
	uint16_t i = 0;
	uint32_t unixtime = (int)Php::call("time");	

	SET_PAT("/^.{0,5}(go?od)?mo?rni?ni?g?.{0,10}$/Usi") {

		ST(0, 10) {
			
			RS(44){
				"Good morning {cname}!",
				"Hi, good morning {cname}!\nHave a nice day!",
				"Ohayou ~^o^~"
			};
			RET();

		} else 

		ST(11, 14) {

			RS(44){
				"Good afternoon {cname}!",
				"It is now afternoon {cname}!"
			};
			RET();

		}
	}

	return false;
}
