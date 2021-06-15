/* The application determines the winner in the vote. In case of a tie, the next round will be held. Each voter ranks all candidates. Uses electoral system developed by Nicolaus Tideman. */
/* Build: gcc ../../vendor/cs50.c tideman.c -o tideman  */
/* Usage example:
    tideman James Mia
    Number of voters: 3
    Rank 1: James
    Rank 2: Mia
    ...
    James
*/


#include "../../vendor/cs50.h"
#include <stdio.h>
#include <strings.h>
// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
} pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (!strcasecmp(candidates[i], name))
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pair p;
                p.winner = i;
                p.loser = j;
                pairs[pair_count] = p;
                pair_count++;
            }
        }
    }
    return;
}

int get_pref_difference(int i)
{
    return preferences[pairs[i].winner][pairs[i].loser] - preferences[pairs[i].loser][pairs[i].winner];
}
// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    int max, max_dif, cur_dif;
    for (int i = 0; i < pair_count; i++)
    {
        max = i;
        max_dif = get_pref_difference(i);
        //find index with max preferences difference in not sorted part array
        for (int j = i; j < pair_count; j++)
        {
            cur_dif = get_pref_difference(j);
            if (cur_dif > max_dif)
            {
                max = j;
                max_dif = get_pref_difference(max);
            }
        }
        cur_dif = get_pref_difference(i);
        if (max_dif > cur_dif)
        {
            pair tmp;
            tmp = pairs[i];
            pairs[i] = pairs[max];
            pairs[max] = tmp;
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    int winner, loser, current;
    bool is_next_finded;
    for (int i = 0; i < pair_count; i++)
    {
        winner = pairs[i].winner;
        loser = pairs[i].loser;
        current = loser;
        while (1)
        {
            is_next_finded = false;
            //find next locked pair in chain
            for (int j = 0; j < pair_count; j++)
            {
                if (locked[current][j])
                {
                    is_next_finded = true;
                    current = j;
                }
            }
            //if end of chain finded lock pair
            if (!is_next_finded)
            {
                locked[winner][loser] = true;
                break;
            }
            //if loop finded exit
            if (current == loser || current == winner)
            {
                break;
            }
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    bool is_locked_as_winner, is_locked_as_loser;
    for (int i = 0; i < pair_count; i++)
    {
        is_locked_as_winner = false;
        is_locked_as_loser = false;
        for (int j = 0; j < pair_count; j++)
        {
            if (locked[i][j])
            {
                is_locked_as_winner = true;
            }
            if (locked[j][i])
            {
                is_locked_as_loser = true;
            }
        }
        if (is_locked_as_winner && !is_locked_as_loser)
        {
            printf("%s\n", candidates[i]);
            return;
        }
    }
    return;
}
