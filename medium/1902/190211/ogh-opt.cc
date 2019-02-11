#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

// [nodNum][cost] 
bool cost[1010][2048];
// Complete the beautifulPath function below.
#define point pair<int,int>
#define mp make_pair

vector<int> graph[1010][1010];
bool cmp(const point& a, const point& b) {
    return a.second > b.second;
}
int beautifulPath(vector<vector<int>> edges, int A, int B) {
    for(int i = 0;i < edges.size();i++) {
        int a = edges[i][0];
        int b = edges[i][1];
        int c = edges[i][2];
        graph[a][b].push_back(c);
        graph[b][a].push_back(c);
    }
    memset(cost,0,sizeof(cost));
    priority_queue<point, vector<point>, function<bool(point, point)>> pq(cmp);
    for(int i = 0 ;i < 1010;i++) {
        if (!graph[A][i].empty()) {
            for(int j = 0;j < graph[A][i].size();j++) {
                cost[i][graph[A][i][j]] = true;
                pq.push(mp(i, graph[A][i][j]));
            }
        }
    }
    while(!pq.empty()) {
        point p = pq.top();
        pq.pop();
        int nodeNum = p.first;
        int penalty = p.second;
        if (nodeNum == B) break;
        for(int i = 0 ;i < 1010;i++) {
            if (!graph[nodeNum][i].empty()) {
                for(int j = 0 ;j < graph[nodeNum][i].size();j++) {
                    int eCost = graph[nodeNum][i][j];
                    int nPen = penalty | eCost;
                    if (cost[i][nPen] == false) {
                        cost[i][nPen] = true;
                        pq.push(mp(i, nPen));
                    }
                }
            }
        }
    }
    int ret = -1;
    for(int i = 0 ;i < 2048;i++) {
        if (cost[B][i]) {
            ret = i;
            break;
        }
    }
    return ret;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string nm_temp;
    getline(cin, nm_temp);

    vector<string> nm = split_string(nm_temp);

    int n = stoi(nm[0]);

    int m = stoi(nm[1]);

    vector<vector<int>> edges(m);
    for (int i = 0; i < m; i++) {
        edges[i].resize(3);

        for (int j = 0; j < 3; j++) {
            cin >> edges[i][j];
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    string AB_temp;
    getline(cin, AB_temp);

    vector<string> AB = split_string(AB_temp);

    int A = stoi(AB[0]);

    int B = stoi(AB[1]);

    int result = beautifulPath(edges, A, B);

    fout << result << "\n";

    fout.close();

    return 0;
}

vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
        return x == y and x == ' ';
    });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}
