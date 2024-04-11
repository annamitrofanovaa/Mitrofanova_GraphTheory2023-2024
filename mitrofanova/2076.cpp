
#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

class dsu {
    int* height, * parent, n;

public:
    dsu() : height(nullptr), parent(nullptr), n(0) {}
    ~dsu() {
        delete[] height;
        delete[] parent;
    }
    dsu(int n)
    {
        parent = new int[n];
        height = new int[n];
        this->n = n;
        makeSet();
    }
    void makeSet()
    {
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    int par(int x)
    {
        if (parent[x] != x) {
            parent[x] = par(parent[x]);
        }
        return parent[x];
    }
    void unions(int x, int y)
    {
        int first = par(x);
        int second = par(y);
        if (first == second)
            return;
        if (height[first] < height[second]) {
            parent[first] = second;
        }
        else if (height[first] > height[second]) {
            parent[second] = first;
        }
        else {
            parent[second] = first;
            height[first] = height[first] + 1;
        }
    }
};

class Solution {
public:
    Solution() {}
    ~Solution() {}
    vector<bool> friendRequests(int n, vector<vector<int>>& restrictions, vector<vector<int>>& requests) {
        dsu friends(n);
        friends.makeSet();
        vector<bool> ans;
        for (int i = 0; i < requests.size(); i++) {
            int a = friends.par(requests[i][0]);
            int b = friends.par(requests[i][1]);
            bool tf = true;
            for (int j = 0; j < restrictions.size(); j++) {
                int a1 = friends.par(restrictions[j][0]);
                int b1 = friends.par(restrictions[j][1]);
                if ((a == a1 && b == b1) || (a == b1 && b == a1)) {
                    tf = false;
                    break;
                }
            }
            if (tf) {
                ans.push_back(true);
                friends.unions(requests[i][0], requests[i][1]);
            }
            else {
                ans.push_back(false);
            }
        }
        return ans;
    }
};
int main()
{
    Solution solution;
    int n = 5;
    vector<vector<int>> restrictions = { {0,1},{1,2},{2,3} };
    vector<vector<int>> requests = { {0,4},{1,2},{3,1},{3,4} };
    vector<bool> output = solution.friendRequests(n, restrictions, requests);
    for (bool success : output) {
        cout << (success ? "true" : "false") << " ";
    }
    cout << endl;
    return 0;
    //std::cout << "Hello World!\n";
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
