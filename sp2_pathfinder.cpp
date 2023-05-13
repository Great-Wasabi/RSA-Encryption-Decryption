#include <iomanip>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string>
#include <math.h>

using namespace std;

struct Node
{
   public:
    int x, y;

    Node()
    {
        x = -1;
        y = -1;
    }
    
    Node(int X, int Y)
    {
        x = X;
        y = Y;
    }
};

struct Queue
{
private:
    Node* arr;
    int front;
    int back;

public:
    void push(int x, int y) { arr[back++] = Node(x, y); }
    Node pop() { return arr[front++]; };
    bool empty() { return (front == back); };

    Queue(int N)
    {
        arr = (Node*)malloc((N + 1) * sizeof(Node));
        front = back = 0;
    }
};

char** create2DCharArray(int** matrix, int height, int width, int goalX, int goalY, int startX, int startY) 
{
    char** charArray = new char*[height];
    for (int i = 0; i < height; i++)
        charArray[i] = new char[width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if(matrix[i][j] == -1)
                charArray[i][j] = '#';
            else if(matrix[i][j] == 1)
                charArray[i][j] = '$';
            else
                charArray[i][j] = ' ';
        }
    }

    charArray[startY][startX] = '@';

    return charArray;
}

int** reformMatrix(int** matrix, int height, int width, int impass, int value) 
{
    srand (time(NULL));

    matrix = new int*[height];
    for (int i = 0; i < height; i++) 
        matrix[i] = new int[width];

    if(impass == 100)
    {
        for (int i = 0; i < height; i++) 
            for (int j = 0; j < width; j++) 
                matrix[i][j] = value;
    }
    else
    {
        int log = (impass * height * width)/100;
        for (int i = 0; i < log;) 
        {
            int randHeight = rand() % height, randWidth = rand() % width;
            if (matrix[randHeight][randWidth] != value) 
            {
                matrix[randHeight][randWidth] = value;
                i++;
            }
        }
    }
    return matrix;
}


void printMatrix(int** matrix, int height, int width) 
{
    for (int i = 0; i < height; i++) 
    {
        for (int j = 0; j < width; j++) 
        {
            if(matrix[i][j]==-1 || matrix[i][j]==10)
                cout << matrix[i][j] << setw(4) << "  ";
            else
                cout << " " <<matrix[i][j] << setw(4) << " ";
        }
            
        cout << endl;
    }
}

void printMatrix(char** matrix, int height, int width) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            char ch = matrix[i][j];
            if (ch == '#') {
                std::cout << "\033[31m" << ch << "\033[0m ";
            } else if (ch == '$' || ch == '@') {
                std::cout << "\033[32m" << ch << "\033[0m ";
            } else if (ch == '*') {
                std::cout << "\033[33m" << ch << "\033[0m ";
            } else {
                std::cout << ch << " ";
            }
        }
        std::cout << std::endl;
    }
}

void Moore(int** matrix, int W, int H, int goalX, int goalY) 
{
    matrix[goalY][goalX] = 1;
    Queue q(W * H);
    q.push(goalY, goalX);

    while (!q.empty()) 
    {
        Node curr = q.pop();
        int i = curr.x, j = curr.y;
        bool north = (i > 0), south = (i < H - 1), east = (j < W - 1), west = (j > 0);

        if (north && east && !matrix[i - 1][j + 1])
        {
            matrix[i - 1][j + 1] = matrix[i][j] + 1;
            q.push(i - 1, j + 1);
        }
        if (north && west && !matrix[i - 1][j - 1])
        {
            matrix[i - 1][j - 1] = matrix[i][j] + 1;
            q.push(i - 1, j - 1);
        }
        if (south && east && !matrix[i + 1][j + 1])
        {
            matrix[i + 1][j + 1] = matrix[i][j] + 1;
            q.push(i + 1, j + 1);
        }
        if (south && west && !matrix[i + 1][j - 1])
        {
            matrix[i + 1][j - 1] = matrix[i][j] + 1;
            q.push(i + 1, j - 1);
        }
        if (north && !matrix[i - 1][j])
        {
            matrix[i - 1][j] = matrix[i][j] + 1;
            q.push(i - 1, j);
        }
        if (south && !matrix[i + 1][j])
        {
            matrix[i + 1][j] = matrix[i][j] + 1;
            q.push(i + 1, j);
        }
        if (east && !matrix[i][j + 1])
        {
            matrix[i][j + 1] = matrix[i][j] + 1;
            q.push(i, j + 1);
        }
        if (west && !matrix[i][j - 1])
        {
            matrix[i][j - 1] = matrix[i][j] + 1;
            q.push(i, j - 1);
        }
    }
}

void greed(int** arr, int W, int H,int X,int Y,char** charr)
{
    int newX, newY;
    int mini = arr[Y][X];
    if(mini == 1)
        return;
    else if(arr[Y-1][X-1] < mini && arr[Y-1][X-1] > 1)
    {
        charr[Y-1][X-1] = '*';
        newX = X-1;newY = Y-1;
        greed(arr, W, H, newX, newY, charr);
    }
    else if(arr[Y][X-1] < mini && arr[Y][X-1] > 1)
    {
        charr[Y][X-1] = '*';
        newX = X-1;newY = Y;
        greed(arr, W, H, newX, newY, charr);
    }
    else if(arr[Y+1][X-1] < mini && arr[Y+1][X-1] > 1)
    {
        charr[Y+1][X-1] = '*';
        newX = X-1;newY = Y+1;
        greed(arr, W, H, newX, newY, charr);
    }
    else if(arr[Y-1][X] < mini && arr[Y-1][X] > 1)
    {
        charr[Y-1][X] = '*';
        newX = X;newY = Y-1;
        greed(arr, W, H, newX, newY, charr);
    }
    else if(arr[Y][X] < mini && arr[Y][X] > 1)
    {
        charr[Y][X] = '*';
        newX = X;newY = Y;
        greed(arr, W, H, newX, newY, charr);
    }
    else if(arr[Y+1][X] < mini && arr[Y+1][X] > 1)
    {
        charr[Y+1][X] = '*';
        newX = X;newY = Y+1;
        greed(arr, W, H, newX, newY, charr);
    }
    else if(arr[Y-1][X+1] < mini && arr[Y-1][X+1] > 1)
    {
        charr[Y-1][X+1] = '*';
        newX = X+1;newY = Y-1;
        greed(arr, W, H, newX, newY, charr);
    }
    else if(arr[Y][X+1] < mini && arr[Y][X+1] > 1)
    {
        charr[Y][X+1] = '*';
        newX = X+1;newY = Y;
        greed(arr, W, H, newX, newY, charr);
    }
    else if(arr[Y+1][X+1] < mini && arr[Y+1][X+1] > 1)
    {
        charr[Y+1][X+1] = '*';
        newX = X+1;newY = Y+1;
        greed(arr, W, H, newX, newY, charr);
    }
}

int main()
{
    int height, width;
    int impass;
    int goalX, goalY, startX, startY;
    int rgoalX, rgoalY, rstartX, rstartY; 
    char choice;
    char** graphArrayChar;
    
    cout << "Welcome to the WaveFront Pather" <<endl <<endl;
    cout << "Please tell me about the grid you want to generate." << endl;
    cout << "Enter the height (at least 10): ";
    cin >> height;
    cout << "Enter the width (at least 10): ";
    cin >> width;

    int** graphArray = reformMatrix(graphArray, height, width, 100, 0);

    while(true)
    {
        cout << "Enter the percent of impassible terrain (0 - 100): ";
        cin >> impass;
        if(impass > 40)
        {
            cout << "Having a value greater than 40% might create poor results, do you with to continue? (y/n):";
            cin >> choice;
            if(choice == 'y')
                break;
        }
        else break;
    }

    graphArray = reformMatrix(graphArray, height, width, impass, -1);

    //graphArray[height-3-1][4] = 99;
    //printMatrix(graphArray, height, width);

    while(true)
    {
        cout << "Please enter the Goal Position X: ";
        cin >> goalX;
        cout << "Please enter the Goal Position Y: ";
        cin >> goalY;

        if(graphArray[height-goalY-1][goalX]==-1 || goalY >= height || goalX >= width)
            cout << "Sorry, that position is inside an obstacle or Out of Bounds" << endl;
        else
        {
            rgoalY = height-goalY-1;
            rgoalX = goalX-1;
            break;
        }     
    }

    Moore(graphArray, width, height, rgoalX, rgoalY);
    printMatrix(graphArray, height, width);

    while(true)
    {
        cout << "Please enter the Start Position X: ";
        cin >> startX;
        cout << "Please enter the Start Position Y: ";
        cin >> startY;

        if(graphArray[height-startY-1][startX]==-1 || startY >= height || startX >= width)
            cout << "Sorry, that position is inside an obstacle or Out of Bounds" << endl;
        else
        {
            rstartY = height-startY-1;
            rstartX = startX;
            break;
        }     
    }
    
    
    graphArrayChar = create2DCharArray(graphArray, height, width, rgoalX, rgoalY, rstartX, rstartY);
    greed(graphArray, width, height, rstartX, rstartY, graphArrayChar);
    printMatrix(graphArrayChar, height, width);


    return 0;
}
