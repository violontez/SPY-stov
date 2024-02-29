#include <iostream>
#include <vector>

using namespace std;

// ��������� ��� ������������� ����� �����
struct Edge {
    int source, destination, weight;
};

// ������� ��� ���������� ����� �� ������� ��������� � ������� ������������� �����
vector<Edge> buildGraph(vector<vector<int>>& adjacencyMatrix, vector<int>& durations) {
    vector<Edge> graph;
    int n = adjacencyMatrix.size();

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (adjacencyMatrix[i][j] != 0) {
                Edge edge;
                edge.source = i;
                edge.destination = j;
                edge.weight = durations[j];
                graph.push_back(edge);
            }
        }
    }

    return graph;
}

// ������� ��� ���������� ������������ ���� � �����
void findCriticalPath(vector<vector<int>>& adjacencyMatrix, vector<int>& durations) {
    int n = adjacencyMatrix.size();
    vector<Edge> graph = buildGraph(adjacencyMatrix, durations);

    // ���������� ������ � ������� �������
    vector<int> earlyStart(n, 0);
    vector<int> earlyFinish(n, 0);
    vector<int> lateStart(n, INT_MAX);
    vector<int> lateFinish(n, INT_MAX);

    // ������ ������ �������
    for (int i = 0; i < n; i++) {
        for (Edge edge : graph) {
            if (edge.destination == i) {
                earlyStart[i] = max(earlyStart[i], earlyFinish[edge.source]);
                earlyFinish[i] = earlyStart[i] + edge.weight;
            }
        }
    }

    // ������ ������� �������
    lateFinish[n - 1] = earlyFinish[n - 1];
    lateStart[n - 1] = lateFinish[n - 1] - durations[n - 1];

    for (int i = n - 2; i >= 0; i--) {
        for (Edge edge : graph) {
            if (edge.source == i) {
                lateFinish[i] = min(lateFinish[i], lateStart[edge.destination]);
                lateStart[i] = lateFinish[i] - durations[i];
            }
        }
    }
    // ���������� ������������ ���� � ��� �����
    cout << "����������� ����: ";
    int criticalPathLength = 0;
    for (int i = 0; i < n; i++) {
        if (earlyStart[i] == lateStart[i]) {
            cout << i << " ";
            criticalPathLength += durations[i];
        }
    }
    cout << endl;

    // ����� ����� ������������ ����
    cout << "����� ������������ ����: " << criticalPathLength << endl;

   
    cout << endl;

    // ����� �������
    cout << "�������:\n";
    cout << "������\t������������\t������ �����\t������ �����\t������� �����\t������� �����\n";
    for (int i = 0; i < n; i++) {
        cout << i << "\t" << durations[i] << "\t\t" << earlyStart[i] << "\t\t" << earlyFinish[i]
            << "\t\t" << lateStart[i] << "\t\t" << lateFinish[i] << endl;
    }
}

int main() {
    setlocale(LC_ALL, "RUS");
    vector<vector<int>> adjacencyMatrix = {
        {0, 1, 1, 0, 0, 0},
        {1, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 1, 0},
        {0, 0, 0, 0, 0, 1},
        {0, 1, 0, 1, 0, 1},
        {0, 0, 0, 0, 0, 0}
    };

    vector<int> durations = { 15, 18, 6, 8, 5, 4 };

    findCriticalPath(adjacencyMatrix, durations);

    return 0;
}