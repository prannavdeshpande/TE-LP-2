#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;

// Struct for topic-keywords and book recommendation
struct BookRecommendation {
    vector<string> keywords;
    string book;
};

// Convert to lowercase
string toLower(string str) {
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}

// Tokenize input
vector<string> tokenize(string input) {
    vector<string> tokens;
    stringstream ss(input);
    string word;
    while (ss >> word) {
        tokens.push_back(toLower(word));
    }
    return tokens;
}

// Knowledge base of project topics and book recommendations
vector<BookRecommendation> knowledgeBase = {
    {{"machine", "learning", "ai", "ml"}, "Recommended Book: 'Hands-On Machine Learning with Scikit-Learn, Keras, and TensorFlow' by Aurélien Géron"},
    {{"web", "development", "html", "css", "javascript"}, "Recommended Book: 'Eloquent JavaScript' by Marijn Haverbeke"},
    {{"data", "science", "analysis"}, "Recommended Book: 'Python for Data Analysis' by Wes McKinney"},
    {{"android", "mobile", "app", "kotlin"}, "Recommended Book: 'Android Programming: The Big Nerd Ranch Guide'"},
    {{"cyber", "security", "hacking"}, "Recommended Book: 'The Web Application Hacker's Handbook'"},
    {{"iot", "internet", "things"}, "Recommended Book: 'Designing the Internet of Things' by Adrian McEwen"},
    {{"cloud", "aws", "azure"}, "Recommended Book: 'Cloud Computing: Concepts, Technology & Architecture' by Erl Thomas"}
};

// Inference engine to find best match
string recommendBook(string userQuery) {
    vector<string> queryWords = tokenize(userQuery);

    int maxScore = 0;
    string bestMatch = "Sorry, we couldn't find a suitable book recommendation for your topic.";

    for (const auto& item : knowledgeBase) {
        int score = 0;
        for (const auto& kw : item.keywords) {
            for (const auto& word : queryWords) {
                if (kw == word) {
                    score++;
                }
            }
        }
        if (score > maxScore) {
            maxScore = score;
            bestMatch = item.book;
        }
    }

    return bestMatch;
}

// Main driver
int main() {
    string query;
    cout << "--- Library Expert System for Project Book Recommendations ---\n";
    cout << "Enter your project topic or keywords:\n> ";

    cin.ignore();
    getline(cin, query);

    string result = recommendBook(query);
    cout << "\n" << result << endl;

    return 0;
}
