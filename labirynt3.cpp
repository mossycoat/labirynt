#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <climits>
using namespace std;

const int rows = 20;
const int cols = 20;
int eX = 1;
int eY = 0;

int shortestLength = INT_MAX;
pair<int, int> shortestPath[400];

void findShortestPath(int tab[20][20], int posX, int posY, int length, pair<int, int> currentPath[400])
{
    if (posX == eX && posY == eY)
    {
        if (length < shortestLength)
        {
            shortestLength = length;
            for (int i = 0; i < length; i++)
            {
                shortestPath[i] = currentPath[i];
            }
        }
        return;
    }

    if (posX < 0 || posX >= rows || posY < 0 || posY >= cols || tab[posX][posY] == 1)
    {
        return;
    }

    tab[posX][posY] = 1; // Zastaw obecną pozycję
    currentPath[length] = {posX, posY}; // Zapisz pozycję

    findShortestPath(tab, posX - 1, posY, length + 1, currentPath); // W górę
    findShortestPath(tab, posX + 1, posY, length + 1, currentPath); // W dół
    findShortestPath(tab, posX, posY - 1, length + 1, currentPath); // W lewo
    findShortestPath(tab, posX, posY + 1, length + 1, currentPath); // W prawo

    tab[posX][posY] = 0; // Zdejmij ścianę z obecnej pozycji
}

pair<int, int> getRandomStartingPoint(int tab[20][20])
{
    srand(time(0));
    int x, y;
    do
    {
        x = rand() % rows;
        y = rand() % cols;
    }
    while (tab[x][y] == 1);
    return {x, y};
}

int main()
{
    int tab[20][20] = {0};

    string line;
    ifstream file("labirynttxt.txt");

    for (int i = 0; getline(file, line) && i < rows; i++)
    {
        for (int j = 0; j < cols && j < line.length(); j++)
        {
            if (line[j] == 'X')
            {
                tab[i][j] = 1;
            }
        }
    }

    pair<int, int> startingPoint = getRandomStartingPoint(tab);
    pair<int, int> currentPath[400];
    findShortestPath(tab, startingPoint.first, startingPoint.second, 0, currentPath);

    if (shortestLength == INT_MAX)
    {
        cout << "Nie ma sciezki." << endl;
    }
    else
    {
        cout << "Najkrotsza sciezka z punktu {X:" << startingPoint.first << " Y:" << startingPoint.second << "} ma dlugosc: " << shortestLength << endl;

        // Zaznacz ściężkę
        for (int i = 0; i < shortestLength; i++)
        {
            tab[shortestPath[i].first][shortestPath[i].second] = 2;
        }

        // Wypisz
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                if (tab[i][j] == 1)
                {
                    cout << "X";
                }
                else if (tab[i][j] == 2)
                {
                    cout << "#";
                }
                else
                {
                    cout << " ";
                }
            }
            cout << endl;
        }
    }

    return 0;
}

