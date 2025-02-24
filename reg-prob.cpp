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

string trim(const string &str);

// Exceptions
struct bad_problem_format_exception : exception
{
};
struct readme_file_not_found_exception : exception
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
        try
        {
            // Format: ID - Name in Title Case
            const auto splitter = raw_prob.find('-');
            const auto id = stoi(raw_prob.substr(0, splitter));
            const auto name = trim(raw_prob.substr(splitter + 1));
            auto file_name = name;
            replace(file_name.begin(), file_name.end(), ' ', '_');
            for (auto &c : file_name)
                c = tolower(c);
            return Problem{id, name, dir + to_string(id) + '_' + file_name + ".cpp"};
        }
        catch (const invalid_argument)
        {
            throw bad_problem_format_exception();
        }
    }
};

void reg_problem(const Problem &prob)
{
    auto readme_file = fstream("README.md");
    if (!readme_file)
        throw readme_file_not_found_exception();

    stringstream buffer;
    buffer << readme_file.rdbuf();

    ostringstream updated_content;
    string _line;
    while (getline(buffer, _line))
    {
        static const regex pattern(R"(\|\s*\[(\d+)\]\(.+\)\s*\|\s*([^|]+)\s*\|)");
        smatch match;
        if ((regex_search(_line, match, pattern) && stoi(match[1]) > prob.id) || buffer.eof())
        {
            updated_content << "| " << '[' << prob.id << ']' << '(' << prob.file_path << ')' << " | " << prob.name << " |\n";
            updated_content << _line << '\n';
            break;
        }
        updated_content << _line << '\n';
    }
    updated_content << buffer.rdbuf();

    // Overwrite the file
    readme_file.seekp(0);
    readme_file << updated_content.str();
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

        reg_problem(prob);

        return 0;
    }
    catch (const bad_problem_format_exception)
    {
        cout << "Bad problem format.\n";
        return -1;
    }
    catch (const dir_not_found_exception)
    {
        cout << "Please enter a valid path.\n";
        return -1;
    }
    catch (const readme_file_not_found_exception)
    {
        cout << "README.md file not found.\n";
        return -1;
    }
}

string trim(const string &str)
{
    auto start = find_if(str.begin(), str.end(), [](unsigned char ch)
                         { return !isspace(ch); });

    auto end = find_if(str.rbegin(), str.rend(), [](unsigned char ch)
                       { return !isspace(ch); })
                   .base();

    return (start < end) ? string(start, end) : "";
}