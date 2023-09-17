#include "essay.h"

using namespace std;

string readFileContent(char* addr) {
	ifstream infile;
	infile.open(addr);
	if (!infile.is_open()) {
		cout << "Failed to open file for reading." << endl;
		exit(0);
	}

	string content, temp;
	while (infile >> temp) {
		content += temp;
	}

	infile.close();
	return content;
}

void writeFileContent(char* addr, const double& val) {
	ofstream outfile;
	outfile.open(addr);
	if (!outfile.is_open()) {
		cout << "Failed to open file for writing." << endl;
		exit(0);
	}

	outfile << fixed << setprecision(2) << val << endl;
	outfile.close();
}

map<string, int> calculateWordFrequency(const string& text) {
	map<string, int> wordFreq;
	for (int i = 0; size_t(i) + 5 < text.size(); i++) {
		string word = text.substr(i, 7); // n-gram segmentation
		wordFreq[word]++;
	}
	return wordFreq;
}

double calculateSimilarity(const vector<int>& vec1, const vector<int>& vec2) {
	const size_t n = vec1.size();
	double dotProduct = 0, norm1 = 0, norm2 = 0;
	for (int i = 0; i < n; i++) {
		dotProduct += 1LL * vec1[i] * vec2[i];
		norm1 += 1LL * vec1[i] * vec1[i];
		norm2 += 1LL * vec2[i] * vec2[i];
	}

	if (norm1 == 0 || norm2 == 0) return 0;

	double similarity = dotProduct / (sqrt(norm1) * sqrt(norm2));
	return similarity;
}

int main(int argc, char* argv[]) {

	string text1 = readFileContent(argv[1]);
	string text2 = readFileContent(argv[2]);

	map<string, int> wordFreq1 = calculateWordFrequency(text1);
	map<string, int> wordFreq2 = calculateWordFrequency(text2);

	set<string> uniqueWords;
	for (auto word : wordFreq1) {
		uniqueWords.insert(word.first);
	}
	for (auto word : wordFreq2) {
		uniqueWords.insert(word.first);
	}

	vector<int> vec1, vec2;
	for (auto word : uniqueWords) {
		vec1.push_back(wordFreq1[word]);
		vec2.push_back(wordFreq2[word]);
	}

	double similarity = calculateSimilarity(vec1, vec2);
	writeFileContent(argv[3], similarity);
	cout << "Result has been written to the file." << endl;

	return 0;
}
