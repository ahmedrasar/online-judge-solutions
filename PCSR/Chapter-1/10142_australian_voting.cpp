#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

/*
    Author: Ahmed R. Asar

    Time Complexity: O(n)
*/

vector<vector<int>> read_votes(const int n)
{
    vector<vector<int>> ballot_votes;
    string line;
    while (getline(cin, line) && !line.empty())
    {
        auto lineStream = stringstream(line);
        vector<int> vote(n);
        for (int i = 0; i < n; ++i)
        {
            int t;
            lineStream >> t;
            vote[i] = t - 1;
        }
        ballot_votes.push_back(vote);
    }
    return ballot_votes;
}

vector<string> count_ballot(const vector<string> &candidates, const vector<vector<int>> &ballot_votes)
{
    const int n = candidates.size();
    const int voters = ballot_votes.size();

    vector<bool> isEleminated(n, false);
    static constexpr int ELEMINATEDCODE = -1;

    vector<int> votes_per_can(n);

    while (true)
    {
        for (int i = 0; i < n; ++i)
            votes_per_can[i] = isEleminated[i] ? ELEMINATEDCODE : 0;

        for (const auto &vote : ballot_votes)
        {
            int votedCanIndex = 0;
            while (isEleminated[vote[votedCanIndex]])
                ++votedCanIndex;

            const int votedCan = vote[votedCanIndex];
            if (++votes_per_can[votedCan] > voters / 2)
                return {candidates[votedCan]};
        }

        int lowest = voters, highest = 0;
        for (const auto can_vote : votes_per_can)
        {
            if (can_vote == ELEMINATEDCODE)
                continue;

            if (can_vote > highest)
                highest = can_vote;
            if (can_vote < lowest)
                lowest = can_vote;
        }

        if (lowest == highest)
        {
            vector<string> winners;
            for (int i = 0; i < n; i++)
            {
                if (votes_per_can[i] == highest)
                    winners.push_back(candidates[i]);
            }
            return winners;
        }

        // Eleminate losers.
        for (int i = 0; i < n; ++i)
        {
            if (votes_per_can[i] == lowest)
                isEleminated[i] = true;
        }
    }
}

int main()
{
    int N;
    cin >> N;
    while (N--)
    {
        int n;
        cin >> n;
        vector<string> candidates(n);
        string line;
        cin >> ws;
        for (int i = 0; i < n; i++)
        {
            getline(cin, line);
            candidates[i] = line;
        }

        auto ballot_votes = read_votes(n);
        auto winners = count_ballot(candidates, ballot_votes);

        for (const string &winner : winners)
            cout << winner << '\n';

        if (N)
            cout << '\n';
    }
}
