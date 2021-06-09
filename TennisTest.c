#include "CppUTest/TestHarness.h"
#include <CppUTest/CommandLineTestRunner.h>
#include <CppUTestExt/MockSupport.h>

#include "TennisGame.h"

TEST_GROUP(MyCode)
{
    void setup()
    {
    }
    void teardown()
    {
    }
};


struct Parameter
{
    int player1Score;
    int player2Score;
    const char* expectedScore;
};

static int maxScore(int a, int b)
{
    return a > b ? a : b;
}

TEST(MyCode, allscorestest)
{
    struct Parameter param[] =
    {
    { 0, 0, "Love-All" },
    { 1, 1, "Fifteen-All" },
    { 2, 2, "Thirty-All" },
    { 3, 3, "Deuce" },
    { 4, 4, "Deuce" },
    { 1, 0, "Fifteen-Love" },
    { 0, 1, "Love-Fifteen" },
    { 2, 0, "Thirty-Love" },
    { 0, 2, "Love-Thirty" },
    { 3, 0, "Forty-Love" },
    { 0, 3, "Love-Forty" },
    { 4, 0, "Win for player1" },
    { 0, 4, "Win for player2" },
    { 2, 1, "Thirty-Fifteen" },
    { 1, 2, "Fifteen-Thirty" },
    { 3, 1, "Forty-Fifteen" },
    { 1, 3, "Fifteen-Forty" },
    { 4, 1, "Win for player1" },
    { 1, 4, "Win for player2" },
    { 3, 2, "Forty-Thirty" },
    { 2, 3, "Thirty-Forty" },
    { 4, 2, "Win for player1" },
    { 2, 4, "Win for player2" },
    { 4, 3, "Advantage player1" },
    { 3, 4, "Advantage player2" },
    { 5, 4, "Advantage player1" },
    { 4, 5, "Advantage player2" },
    { 15, 14, "Advantage player1" },
    { 14, 15, "Advantage player2" },
    { 6, 4, "Win for player1" },
    { 4, 6, "Win for player2" },
    { 16, 14, "Win for player1" },
    { 14, 16, "Win for player2" }, };

    for (unsigned int caseNum = 0; caseNum < (sizeof param / sizeof param[0]); caseNum++)
    {
        const char *name = param[caseNum].expectedScore;
        int player1Score = param[caseNum].player1Score;
        int player2Score = param[caseNum].player2Score;
        
        struct TennisGame* game = TennisGame_Create("player1", "player2");

        for (int i = 0; i < maxScore(player1Score, player2Score); i++)
        {
            if (i < player1Score)
                TennisGame_WonPoint(game, "player1");
            if (i < player2Score)
                TennisGame_WonPoint(game, "player2");
        }
        STRCMP_EQUAL(name, TennisGame_GetScore(game));
        free(game);
    }
}

TEST(MyCode, realisticGame)
{
    const char* points[] = { "player1", "player1", "player2",
                             "player2", "player1", "player1" };
    const char* expectedScores[] = { "Fifteen-Love", "Thirty-Love", "Thirty-Fifteen",
                                     "Thirty-All", "Forty-Thirty", "Win for player1" };
    struct TennisGame* game = TennisGame_Create("player1", "player2");

    for (int i = 0; i < 6; i++)
    {
        TennisGame_WonPoint(game, points[i]);
        STRCMP_EQUAL(expectedScores[i], TennisGame_GetScore(game));
    }

    free(game);

}
int
main(int ac, char** av)
{
  return CommandLineTestRunner::RunAllTests(ac, av);
}
