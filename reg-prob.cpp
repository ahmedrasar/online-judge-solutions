#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <regex>
using namespace std;

/*
    Author: Ahmed R. Asar
    Date: 2025-2-22
*/

#if defined(_WIN64) || defined(_WIN32)
#define DIRSPLITER '\\'
#else
#define DIRSPLITER '/'
#endif

// Exceptions
struct invalid_problem_format : exception
{
};
struct invalid_file : exception
{
};
struct dir_not_found_exception : exception
{
};

struct Problem
{
    const int id;
    const string name, file_path;

    static Problem from_raw(const string &raw_prob, const string &dir)
    {

        // Format: ID - Name in Title Case
        static const regex format(R"(\s*(\d+)\s*-?\s*(.+))");
        smatch match;
        regex_search(raw_prob, match, format);
        if (match.empty())
            throw invalid_problem_format();
        const auto id = stoi(match[1]);
        const string name = match[2];
        auto file_name = name;
        replace(file_name.begin(), file_name.end(), ' ', '_');
        for (auto &c : file_name)
            c = tolower(c);
        return Problem{id, name, dir + to_string(id) + '_' + file_name + ".cpp"};
    }
};

void reg_problem(const Problem &prob, fstream &file)
{
    stringstream buffer;
    buffer << file.rdbuf();

    ostringstream updated_content;
    string _line;
    while (getline(buffer, _line))
    {
        // Format: [ID]
        static const regex format(R"(\[(\d+)\])");
        smatch match;
        if ((regex_search(_line, match, format) && stoi(match[1]) > prob.id))
            break;

        updated_content << _line << '\n';
    }
    // Format: | [ID](file) | Name |
    updated_content << "| " << '[' << prob.id << ']' << '(' << prob.file_path << ')' << " | " << prob.name << " |\n";

    if (buffer)
        updated_content << _line << '\n';
    updated_content << buffer.rdbuf();

    // Overwrite the file
    file.seekp(0);
    file << updated_content.str();
}

int main(int argc, char const *argv[])
{
    if (argc < 2)
    {
        cout << "Please insert the problem.\n";
        return -1;
    }

    const string raw_prob = argv[1];
    try
    {
        string dir;
        if (argc != 2)
        {
            dir = argv[2];
            if (dir.back() != DIRSPLITER)
                dir += DIRSPLITER;
        }

        const Problem prob = Problem::from_raw(raw_prob, dir);

        auto file = ofstream(prob.file_path);
        if (!file)
            throw dir_not_found_exception();

        fstream readme_file("README.md");
        if (!readme_file)
            throw invalid_file();
        reg_problem(prob, readme_file);

        return 0;
    }
    catch (const invalid_problem_format)
    {
        cout << "Bad problem format.\n";
        return -1;
    }
    catch (const dir_not_found_exception)
    {
        cout << "Please enter a valid path.\n";
        return -1;
    }
    catch (const invalid_file)
    {
        cout << "README.md file not found.\n";
        return -1;
    }
}