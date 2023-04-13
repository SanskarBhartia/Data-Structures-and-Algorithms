#include<iostream>
#include<fstream>
#include "json.hpp"

int main(int argc, char* argv[]) {
	std::ifstream file;
	file.open(argv[1]);
	nlohmann::json json_object;
	nlohmann::json new_json_object;
	if (file.is_open()) {
		file >> json_object;
	}
	file.close();
	auto inversion_count = 0;
	const int MAX_ARRAY_SIZE = json_object["metadata"]["arraySize"];
	for (auto itr = json_object.begin(); itr != std::prev(json_object.end()); ++itr) {
		auto inversion_found = false;
		for (auto i = 0; i < MAX_ARRAY_SIZE - 1; i++) {
			if (itr.value()[i] > itr.value()[i + 1]) {
				auto sample_number = itr.key();
				int inversion[2] = {itr.value()[i], itr.value()[i + 1]};
				new_json_object[sample_number]["ConsecutiveInversions"][std::to_string(i)] = inversion;
				inversion_found = true;
			}
		}
		if (inversion_found == true) {
			inversion_count++;
			new_json_object[itr.key()]["sample"] = itr.value();
		}
	}
	new_json_object["metadata"]["arraySize"] = json_object["metadata"]["arraySize"];
	new_json_object["metadata"]["file"] = argv[1];
	new_json_object["metadata"]["numSamples"] = json_object["metadata"]["numSamples"];
	new_json_object["metadata"]["samplesWithInversions"] = inversion_count;

	std::cout << new_json_object.dump(2) << std::endl;

	return 0;
}
