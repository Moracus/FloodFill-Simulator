#include <SDL.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <queue>
#include <SDL_timer.h>
using namespace std;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

const int CELL_SIZE = 25;

vector<vector<int>> matrix = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1},
    {1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1},
    {1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

void bfs(int sr, int sc, vector<vector<int>> &image, vector<vector<int>> &ans, int newColor, int iniColor, int delrow[], int delcol[], queue<pair<int, int>> &bfsQ, queue<vector<vector<int>>> &q)
{

    bfsQ.push({sr, sc});
    int n = image.size();
    int m = image[0].size();
    while (!bfsQ.empty())
    {
        int row = bfsQ.front().first;
        int col = bfsQ.front().second;
        ans[row][col] = newColor;
        q.push(ans);
        bfsQ.pop();

        for (int i = 0; i < 4; i++)
        {
            int nrow = row + delrow[i];
            int ncol = col + delcol[i];
            if (nrow >= 0 && nrow < n && ncol >= 0 && ncol < m && image[nrow][ncol] == iniColor && ans[nrow][ncol] != newColor)
            {
                bfsQ.push({nrow, ncol});
            }
        }
    }
}

void dfs(int row, int col, vector<vector<int>> &image, vector<vector<int>> &ans, int newColor, int iniColor, int n, int m, int delrow[], int delcol[],
         queue<vector<vector<int>>> &q)
{

    // Marking it as the newColor
    ans[row][col] = newColor;
    q.push(ans);

    for (int i = 0; i < 4; i++)
    {
        int nrow = row + delrow[i];
        int ncol = col + delcol[i];
        // Checking Out Of Bound Condition
        if (nrow >= 0 && ncol >= 0 && nrow < n && ncol < m && image[nrow][ncol] == iniColor && ans[nrow][ncol] != newColor)
        {
            dfs(nrow, ncol, image, ans, newColor, iniColor, n, m, delrow, delcol, q);
        }
    }
}

vector<vector<int>> floodFill(vector<vector<int>> &image, int sr, int sc, int newColor, queue<vector<vector<int>>> &q)
{
    // Code here
    vector<vector<int>> ans = image;
    queue<pair<int, int>> bfsQ;
    int n = image.size();
    int m = image[0].size();
    // Initial Color
    int iniColor = image[sr][sc];
    // vectors for changing of rows and column direction
    // UP LEFT DOWN RIGHT
    int delrow[] = {-1, 0, +1, 0};
    int delcol[] = {0, +1, 0, -1};
    // Calling dfs function
    // dfs(sr, sc, image, ans, newColor, iniColor, n, m, delrow, delcol, q);
    bfs(sr, sc, image, ans, newColor, iniColor, delrow, delcol, bfsQ, q);
    return ans;
}

bool init(SDL_Window *&window, SDL_Renderer *&renderer)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    window = SDL_CreateWindow("Flood fill simulation", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
    {
        printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    return true;
}

void close(SDL_Window *window, SDL_Renderer *renderer)
{

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
}

void drawBox(SDL_Renderer *renderer)
{
    SDL_Rect box = {SCREEN_WIDTH / 6, SCREEN_HEIGHT / 6, SCREEN_WIDTH * 2 / 3, SCREEN_HEIGHT * 2 / 3};
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);

    SDL_RenderDrawRect(renderer, &box);
}

void drawMatrix(SDL_Renderer *renderer, vector<vector<int>> &matrix)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    drawBox(renderer);

    for (int i = 0; i < matrix.size(); ++i)
    {
        for (int j = 0; j < matrix[0].size(); ++j)
        {
            SDL_Rect rect = {(SCREEN_WIDTH / 6 + (j * CELL_SIZE)), (SCREEN_HEIGHT / 6 + (i * CELL_SIZE)), CELL_SIZE, CELL_SIZE};
            switch (matrix[i][j])
            {
            case 1:
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 150);
                SDL_RenderFillRect(renderer, &rect);
                break;
            case 2:
                SDL_SetRenderDrawColor(renderer, 0, 255, 0, 150);
                SDL_RenderFillRect(renderer, &rect);
                break;
            case 0:
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 150);
                SDL_RenderFillRect(renderer, &rect);
                break;
            case 3:
                SDL_SetRenderDrawColor(renderer, 0, 0, 255, 150);
                SDL_RenderFillRect(renderer, &rect);
                break;

            default:
                break;
            }
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderDrawRect(renderer, &rect);
        }
    }

    try
    {
        SDL_RenderPresent(renderer);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}

struct TimerCallbackParams
{
    SDL_Renderer *renderer;
    queue<vector<vector<int>>> &q;
};

Uint32 visualizer(Uint32 interval, void *params)
{
    TimerCallbackParams *timerParams = static_cast<TimerCallbackParams *>(params);
    SDL_Renderer *renderer = timerParams->renderer;
    queue<vector<vector<int>>> &q = timerParams->q;

    if (!q.empty())
    {

        try
        {
            q.pop();
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }
    }

    return interval;
}

int main(int argc, char *args[])
{
    queue<vector<vector<int>>> q;
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    q.push(matrix);
    vector<vector<int>> ans = floodFill(matrix, 0, 1, 3, q);
    TimerCallbackParams timerParams = {renderer, q};
    if (!init(window, renderer))
    {
        printf("Failed to initialize!\n");
        return -1;
    }

    bool quit = false;
    SDL_Event e;
    int timer = 0;
    const int ticksUntilNextFrame = 100;
    while (!quit)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
        }

        if (!q.empty())
        {
            drawMatrix(renderer, q.front());
            timer++;
            if (timer >= ticksUntilNextFrame)
            {
                q.pop();
                timer = 0;
            }
        }
        else
        {
            drawMatrix(renderer, ans);
        }
    }

    close(window, renderer);

    return 0;
}