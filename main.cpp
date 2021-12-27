#include <bits/stdc++.h>
using namespace std;
#define MAXN 100
const int INF = 1e7;
int dis[MAXN][MAXN];
int Next[MAXN][MAXN];
int V = 11;
vector<string> categories = {"Entry", "Hot Bar", "Wine", "Health", "Beauty", "Grocery-1", "Grocery-2", "Seasonal", "Floral", "Frozen", "Diary"};

void initialise(int V,
                vector<vector<int>> &graph)
{
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            dis[i][j] = graph[i][j];
            if (graph[i][j] == INF)
                Next[i][j] = -1;
            else
                Next[i][j] = j;
        }
    }
}
vector<int> constructPath(int u, int v)
{
    if (Next[u][v] == -1)
        return {};
    vector<int> path = {u};
    while (u != v)
    {
        u = Next[u][v];
        path.push_back(u);
    }
    return path;
}

void floydWarshall(int V)
{
    for (int k = 0; k < V; k++)
    {
        for (int i = 0; i < V; i++)
        {
            for (int j = 0; j < V; j++)
            {
                if (dis[i][k] == INF || dis[k][j] == INF)
                    continue;
                if (dis[i][j] > dis[i][k] + dis[k][j])
                {
                    dis[i][j] = dis[i][k] + dis[k][j];
                    Next[i][j] = Next[i][k];
                }
            }
        }
    }
}
void printPath(vector<int> &path)
{
    int n = path.size();
    for (int i = 1; i < n - 1; i++)
        cout << " -> " << categories[path[i]];
    cout << " -> " << categories[path[n - 1]];
}
int indexofSmallestElement(int array[], int size)
{
    int index = 0;
    for (int i = 1; i < size; i++)
    {
        if (array[i] < array[index])
            index = i;
    }
    return index;
}
int main()
{
    fstream item_list;
    item_list.open("item_list.txt", ios::in);
    int n;
    if (item_list.is_open())
    {
        string line;
        while (getline(item_list, line))
            n++;
    }
    item_list.close();
    item_list.open("item_list.txt", ios::in);
    string items[n];
    if (item_list.is_open())
    {
        string item;
        int i = 0;
        while (getline(item_list, item))
        {
            items[i] = item;
            i++;
        }
        item_list.close();
    }
    vector<vector<string>> available = {
        {"soup", "italian", "continental"},
        {"desert wine", "red wine", "sparkling wine"},
        {"probiotics", "medicines", "anticeptics"},
        {"cosmetics", "hair care", "skin care"},
        {"flour", "fulses", "rice"},
        {"namkeens", "biscuits", "cold drinks"},
        {"fruits", "vegetables", "juice"},
        {"vasks", "baskets", "bouquetes"},
        {"peas", "mccain", "chicken"},
        {"paneer", "milk", "ice cream"}};
    vector<vector<int>> graph = {
        {0, 30, 20, 25, 30, 50, 50, 100, INF, INF, INF},     //Entry
        {30, 0, 10, INF, INF, INF, INF, INF, INF, 5, 10},    //Hot Bar
        {20, 10, 0, 10, INF, INF, INF, INF, INF, 2, 9},      //Wine
        {25, INF, 10, 0, 5, INF, INF, INF, INF, 2, 7},       //Health
        {30, INF, INF, 5, 0, 10, INF, INF, INF, 2, 3},       //Beauty
        {50, INF, INF, INF, 10, 0, 5, 10, INF, 7, 4},        //Grocery 1
        {50, INF, INF, INF, INF, 5, 0, INF, INF, 8, 4},      //Grocery 2
        {100, INF, INF, INF, INF, 10, INF, 0, 7, INF, INF},  //Seasonal
        {INF, INF, INF, INF, INF, INF, INF, 7, 0, INF, INF}, //Floral
        {INF, 5, 2, 2, 2, 7, 8, INF, INF, 0, 2},             //Frozen
        {INF, 10, 9, 7, 3, 4, 4, INF, INF, 2, 0}             //Diary
    };
    vector<int> subs;
    vector<string>::iterator it;
    subs.push_back(0);
    for (int j = 0; j < n; j++)
    {
        for (int i = 0; i < available.size(); i++)
        {
            it = find(available[i].begin(), available[i].end(), items[j]);
            if (it != available[i].end())
            {
                subs.push_back(i + 1);
            }
        }
    }
    initialise(V, graph);
    floydWarshall(V);
    int temp[subs.size()];
    vector<int> gal;
    gal.push_back(0);
    subs[0] = -1;
    for (int j = 0; j < subs.size(); j++)
    {
        for (int i = 0; i < subs.size(); i++)
        {
            if (subs[i] == -1)
            {
                temp[i] = INF;
            }
            else
            {
                temp[i] = dis[gal[gal.size() - 1]][subs[i]];
            }
        }
        int index = indexofSmallestElement(temp, subs.size());
        gal.push_back(subs[index]);
        subs[index] = -1;
    }
    gal[gal.size() - 1] = 0;
    vector<int> path;
    cout<<"Shortest path for the customer: "<<endl;
    cout << categories[0];
    for (int i = 0; i < gal.size() - 1; i++)
    {
        path = constructPath(gal[i], gal[i + 1]);
        printPath(path);
    }
    int distance = 0;
    for (int i = 0; i < gal.size() - 1; i++)
    {
        distance += dis[gal[i]][gal[i + 1]];
    }
    cout << endl
         << "Total distance travelled: " << distance;
}