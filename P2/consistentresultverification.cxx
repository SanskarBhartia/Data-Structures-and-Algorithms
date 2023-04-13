#include<iostream>
#include<fstream>
#include"json.hpp"

int main(int argc, char* argv[]) {
	std::ifstream file1, file2;
	nlohmann::json file1_json_object;
	nlohmann::json file2_json_object;
	nlohmann::json result_json_object;


	file1.open(argv[1]);
	if (file1.is_open()) {
		file1 >> file1_json_object;
	}
	file1.close();

	file2.open(argv[2]);
	if (file2.is_open()) {
		file2 >> file2_json_object;
	}
	file2.close();

	const auto MAX_ARRAY_SIZE = file1_json_object["metadata"]["arraySize"];
	const auto MAX_ARRAY_AMOUNT = file1_json_object["metadata"]["numSamples"];

	auto conflicting_counter = 0;
	for (auto file1itr = file1_json_object.begin(), file2itr = file2_json_object.begin();
	     file1itr != std::prev(file1_json_object.end()), file2itr != std::prev(file2_json_object.end()); ++file1itr, ++file2itr) {
		if (file1itr.value() != file2itr.value()) {
			conflicting_counter++;
			for (int i = 0; i < MAX_ARRAY_SIZE; ++i) {
				if (file1itr.value()[i] != file2itr.value()[i]) {
					result_json_object[file2itr.key()][argv[2]] = file2itr.value();
					result_json_object[file2itr.key()]["Mismatches"][std::to_string(i)] = {file1itr.value()[i], file2itr.value()[i]};
					result_json_object[file2itr.key()][argv[1]] = file1itr.value();

				}
			}
			result_json_object["metadata"]["File1"]["arraySize"] = file1_json_object["metadata"]["arraySize"];
			result_json_object["metadata"]["File1"]["name"] = argv[1];
			result_json_object["metadata"]["File1"]["numSamples"] = file1_json_object["metadata"]["numSamples"];

			result_json_object["metadata"]["File2"]["arraySize"] = file2_json_object["metadata"]["arraySize"];
			result_json_object["metadata"]["File2"]["name"] = argv[2];
			result_json_object["metadata"]["File2"]["numSamples"] = file2_json_object["metadata"]["numSamples"];

			result_json_object["metadata"]["samplesWithConflictingResults"] = conflicting_counter;
		}

	}
	std::cout << result_json_object.dump(2) << std::endl;
	return 0;
}
