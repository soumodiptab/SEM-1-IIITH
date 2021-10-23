#include <iostream>
#include <limits>
#include <vector>
#include <queue>
using namespace std;
class point
{
public:
    int row;
    int col;
    point()
    {
    }
    point(int row, int col)
    {
        this->row = row;
        this->col = col;
    }
    point displace(int row, int col)
    {
        point q = point(this->row + row, this->col + col);
        return q;
    }
};
class grid
{
    int rows, cols;
    char c_node = '.';
    char c_block = '#';
    char c_rider = 'R';
    char c_start = 'A';
    int movement[2][4] = {{-1, 0, 1, 0}, {0, -1, 0, 1}};
    vector<vector<char>> grid_store;
    vector<vector<int>> distance;
    vector<vector<bool>> visited;
    bool index_check(point &p)
    {
        if (p.row < 0 || p.row >= rows)
            return false;
        if (p.col < 0 || p.col >= cols)
            return false;
        if (grid_store[p.row][p.col] == c_block)
            return false;
        return true;
    }

public:
    grid() {}
    void grid_solver()
    {
        char ch;
        cin >> rows >> cols;
        vector<point> riders;
        point start_position;
        point destination_point(1, 0); //hard coded for now <change later>
        distance = vector<vector<int>>(rows, vector<int>(cols, -1));
        visited = vector<vector<bool>>(rows, vector<bool>(cols, false));
        for (int i = 0; i < rows; i++)
        {
            vector<char> row;
            for (int j = 0; j < cols; j++)
            {
                char ch;
                cin >> ch;
                if (ch == c_rider)
                {
                    riders.push_back(point(i, j));
                    ch = c_node;
                }
                else if (ch == c_start)
                {
                    start_position = point(i, j);
                    ch = c_node;
                }
                row.push_back(ch);
            }
            grid_store.push_back(row);
        }
        queue<point> que;
        distance[destination_point.row][destination_point.col] = 0;
        que.push(destination_point);
        while (!que.empty())
        {
            int row, col;
            point grid_point = que.front();
            que.pop();
            if (visited[grid_point.row][grid_point.col])
                continue;
            visited[grid_point.row][grid_point.col] = true;
            for (int i = 0; i < 4; i++)
            {
                point new_point = grid_point.displace(movement[0][i], movement[1][i]);
                if (index_check(new_point) && !visited[new_point.row][new_point.col])
                {
                    distance[new_point.row][new_point.col] = distance[grid_point.row][grid_point.col] + 1;
                    que.push(new_point);
                }
            }
        }
        if (!riders.empty())
        {
            point min = riders[0];
            for (auto r : riders)
            {
                if (visited[r.row][r.col] && distance[r.row][r.col] < distance[min.row][min.col])
                {
                    min = r;
                }
            }
            if (visited[min.row][min.col] &&
                (distance[start_position.row][start_position.col] == -1 ||
                 distance[min.row][min.col] < distance[start_position.row][start_position.col]))
            {
                cout << "No" << endl;
            }
            else if (visited[start_position.row][start_position.col])
            {
                cout << "Yes" << endl
                     << distance[start_position.row][start_position.col] << endl;
            }
            else
            {
                cout << "No" << endl;
            }
        }
        else if (visited[start_position.row][start_position.col])
        {
            cout << "Yes" << endl
                 << distance[start_position.row][start_position.col] << endl;
        }
        else
        {
            cout << "No" << endl;
        }
    }
};
void driver()
{
    grid new_grid = grid();
    new_grid.grid_solver();
}
int main()
{
    //freopen("grid.txt","r",stdin);
    driver();
}