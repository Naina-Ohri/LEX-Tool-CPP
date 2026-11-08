#include <cctype>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;

struct Token {
    string type, value;
    int line;
};

const set<string> keywords = {
    "int", "float", "double", "char", "bool", "void",
    "if", "else", "while", "for", "return", "true", "false"
};

vector<Token> scan(const string& source) {
    vector<Token> tokens;
    size_t i = 0;
    int line = 1;

    auto add = [&](string type, string value) {
        tokens.push_back({type, value, line});
    };

    while (i < source.size()) {
        char c = source[i];

        if (c == '\n') { ++line; ++i; continue; }
        if (isspace(static_cast<unsigned char>(c))) { ++i; continue; }

        if (c == '/' && i + 1 < source.size() && source[i + 1] == '/') {
            while (i < source.size() && source[i] != '\n') ++i;
            continue;
        }

        if (c == '/' && i + 1 < source.size() && source[i + 1] == '*') {
            int startLine = line;
            i += 2;
            bool closed = false;
            while (i < source.size()) {
                if (source[i] == '\n') ++line;
                if (source[i] == '*' && i + 1 < source.size()
                    && source[i + 1] == '/') {
                    i += 2;
                    closed = true;
                    break;
                }
                ++i;
            }
            if (!closed)
                tokens.push_back({"ERROR", "Unclosed comment", startLine});
            continue;
        }

        if (isalpha(static_cast<unsigned char>(c)) || c == '_') {
            size_t start = i++;
            while (i < source.size() &&
                   (isalnum(static_cast<unsigned char>(source[i])) ||
                    source[i] == '_')) ++i;
            string word = source.substr(start, i - start);
            add(keywords.count(word) ? "KEYWORD" : "IDENTIFIER", word);
            continue;
        }

        if (isdigit(static_cast<unsigned char>(c))) {
            size_t start = i++;
            while (i < source.size() &&
                   (isdigit(static_cast<unsigned char>(source[i])) ||
                    (source[i] == '.' && i + 1 < source.size() &&
                     isdigit(static_cast<unsigned char>(source[i + 1])))))
                ++i;
            add("NUMBER", source.substr(start, i - start));
            continue;
        }

        if (c == '"' || c == '\'') {
            char quote = c;
            size_t start = i++;
            bool closed = false;
            while (i < source.size()) {
                if (source[i] == '\n') break;
                if (source[i] == '\\' && i + 1 < source.size()) {
                    i += 2;
                    continue;
                }
                if (source[i] == quote) {
                    ++i;
                    closed = true;
                    break;
                }
                ++i;
            }
            if (closed) add(quote == '"' ? "STRING" : "CHARACTER",
                            source.substr(start, i - start));
            else {
                add("ERROR", "Unclosed string/character literal");
                if (i < source.size() && source[i] == '\n') ++line;
            }
            continue;
        }

        string two = i + 1 < source.size() ? source.substr(i, 2) : "";
        const set<string> doubleOps = {
            "==", "!=", "<=", ">=", "++", "--", "+=", "-=",
            "*=", "/=", "&&", "||", "->"
        };
        if (doubleOps.count(two)) {
            add("OPERATOR", two);
            i += 2;
            continue;
        }

        if (string("+-*/%=<>!&|^~").find(c) != string::npos) {
            add("OPERATOR", string(1, c));
            ++i;
            continue;
        }

        if (string("(){}[];,.:").find(c) != string::npos) {
            add("PUNCTUATION", string(1, c));
            ++i;
            continue;
        }

        add("ERROR", string("Invalid character: ") + c);
        ++i;
    }

    tokens.push_back({"EOF", "EOF", line});
    return tokens;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: CD_LEX_Project <source-file>\n";
        return 1;
    }

    ifstream file(argv[1]);
    if (!file) {
        cerr << "Error: Cannot open file " << argv[1] << '\n';
        return 1;
    }

    string source((istreambuf_iterator<char>(file)),
                   istreambuf_iterator<char>());
    vector<Token> tokens = scan(source);
    bool errors = false;

    cout << "LEXICAL ANALYSIS\n";
    cout << "------------------------------\n";
    cout << "LINE\tTOKEN TYPE\tVALUE\n";
    cout << "------------------------------\n";

    for (const auto& token : tokens) {
        cout << token.line << '\t' << token.type << '\t'
             << token.value << '\n';
        if (token.type == "ERROR") errors = true;
    }

    cout << "------------------------------\n";
    cout << (errors ? "Lexical errors found.\n" :
                      "Lexical analysis completed successfully.\n");
    return errors ? 2 : 0;
}
