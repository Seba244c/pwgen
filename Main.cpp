#include <iostream>
#include <cstdlib>
#include <string>
#include <chrono>
#include "getopt.h"

std::string charsAlphabetic = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
std::string charsSemiSpecial = charsAlphabetic + "~`! @#$%^&*()_-+={[}]|:;'<,>.?/"; // Same as charsSpecial without " and \

std::string charsSpecial = charsAlphabetic + "~`! @#$%^&*()_-+={[}]|\\:;\"'<,>.?/";

struct Cli {
	int length = 18;
	int amount = 1;
	std::string seperator = "\n";
	std::string chars = charsSpecial;
};

std::string genPassword(Cli& cli) {
	std::string out;

	for (int i = 0; i < cli.length; i++) {
		int n = rand() % cli.chars.length();
		out.push_back(cli.chars.at(n));
	}

	return out;
}

int main(int argc, char *argv[]) {
	Cli cli;
	srand((unsigned)std::chrono::high_resolution_clock::now().time_since_epoch().count());

	// Parse args
	for (;;) {
		switch (getopt(argc, argv, "i:l:asfh")) {
		case 'l':
			cli.length = std::stoi(optarg);
			continue;
		case 'i':
			cli.amount = std::stoi(optarg);
			continue;
		case 'a':
			cli.chars = charsAlphabetic;
			continue;
		case 's':
			cli.chars = charsSemiSpecial;
			continue;
		case 'f':
			cli.chars = charsSpecial;
			continue;
		case '?':
		case 'h':
		default:
			std::cout << "usage: pwgen [switches]" << std::endl;
			std::cout << " -h/-? for this help text" << std::endl;
			std::cout << " -l [length] sets the length of generated passwords" << std::endl;
			std::cout << " -i [amount] sets the amount of passwords to generate" << std::endl;
			std::cout << " Chareter options " << std::endl;
			std::cout << "    -a Makes it so the password only contains [a-z][A-Z]0-9" << std::endl;
			std::cout << "    -f Uses the full set of charaters" << std::endl;
			std::cout << "    -s Uses the full set of charaters except for \"\\" << std::endl;
			return 0;
		case -1:
			break;
		}

		break;
	}
	
	// Generate passwords and print
	for (int i = 0; i < cli.amount; i++) {
		std::cout << genPassword(cli) << cli.seperator;
	}
}