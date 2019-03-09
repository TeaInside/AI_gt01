
#include <stdint.h>
#include <stdlib.h>
#include <phpcpp.h>
#include <gt01/gt01.hpp>

#define time_range(A,B) \
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
	uint32_t unixtime = (uint32_t)((int)Php::call("time"));	

	SET_PAT(
		"/(^|(.{0,3}[\\s]+))" \
		"(go?od)?mo?rni?ni?g?" \
		"(([\\s]+.{0,10})|$)/Usi"
	) {

		// 00 AM to 11 AM
		time_range(0, 11) {

			RS(44){
				"Good morning {cname}!",
				"Hi, good morning {cname}!\nHave a nice day!",
				"Ohayou ~^o^~"
			};
			RET();

		} else 

		// Saying good morning in afternoon (12 AM to 11 PM).
		time_range(12, 23) {

			RS(28){
				"Good afternoon {cname}!",
				"It is now afternoon {cname}!"
			};
			RET();

		}
	}

	SET_PAT(
		"/(^|(.{0,3}[\\s]+))" \
		"(go?od)afte?rnoo?n" \
		"(([\\s]+.{0,10})|$)/"
	) {

		// Saying good afternoon in morning (00 AM to 10 AM).
		// Some people assume that 11 AM is afternoon, so we don't catch it.
		time_range(0, 10) {

			RS(33){
				"Good morning {cname}!",
				"Hi {cname}, it's still morning :3"
			};
			RET();

		} else 

		// 12 AM to 11 PM
		time_range(11, 23) {

			RS(){
				"Good afternoon {cname}!",
				"Hi, good afternoon {cname}, how was your day?",
				"Konnichiwa^^"
			};
			RET();

		}

	}

	return false;
}
