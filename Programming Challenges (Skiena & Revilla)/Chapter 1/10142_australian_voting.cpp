#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

vector<vector<int>> readVotes(const int n)
{
    vector<vector<int>> ballotVotes;
    string line;
    while (getline(cin, line) && !line.empty()) // for each vote
    {
        auto lineStream = stringstream(line);
        vector<int> vote(n);
        for (int i = 0; i < n; ++i)
        {
            int t;
            lineStream >> t;
            vote[i] = t - 1;
        }
        ballotVotes.push_back(vote);
    }
    return ballotVotes;
}

vector<string> countBallot(const vector<string> &candidates, const vector<vector<int>> &ballotVotes)
{
    const int n = candidates.size();
    const int voters = ballotVotes.size();

    vector<bool> isEleminated(n, false);
    static constexpr int eleminatedCode = -1;

    vector<int> votesPerCan(n);

    while (true)
    {
        for (int i = 0; i < n; ++i)
            votesPerCan[i] = isEleminated[i] ? eleminatedCode : 0;

        for (const auto &vote : ballotVotes)
        {
            int votedCanIndex = 0;
            while (isEleminated[vote[votedCanIndex]])
                ++votedCanIndex;

            const int votedCan = vote[votedCanIndex];
            if (++votesPerCan[votedCan] > voters / 2)
                return {candidates[votedCan]};
        }

        int lowest = voters, highest = 0;
        for (const auto canVote : votesPerCan)
        {
            if (canVote == eleminatedCode)
                continue;

            if (canVote > highest)
                highest = canVote;
            if (canVote < lowest)
                lowest = canVote;
        }

        if (lowest == highest) // tie
        {
            vector<string> winners;
            for (int i = 0; i < n; i++)
            {
                if (votesPerCan[i] == highest)
                    winners.push_back(candidates[i]);
            }
            return winners;
        }

        for (int i = 0; i < n; ++i) // eleminate losers
        {
            if (votesPerCan[i] == lowest)
                isEleminated[i] = true;
        }
    }
}

int main()
{
    int caseN;
    cin >> caseN;
    while (caseN--)
    {
        int n;
        cin >> n;
        vector<string> candidates(n);
        string nameLine;
        cin >> ws;
        for (int i = 0; i < n; i++)
        {
            getline(cin, nameLine);
            candidates[i] = nameLine;
        }

        auto ballotVotes = readVotes(n);
        auto winners = countBallot(candidates, ballotVotes);

        for (const string &winner : winners)
            cout << winner << '\n';

        if (caseN)
            cout << '\n';
    }
}
