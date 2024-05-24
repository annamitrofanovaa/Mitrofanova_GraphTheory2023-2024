#include <iostream>
#include <fstream>
#include <chrono>
#include <sstream>
#include <vector>
#include <random>

#include "Graph.h" 

using namespace std;
using namespace std::chrono;

pair<int, double> testAlgorithmEdmondsKarp(const string& filename) {
    ifstream infile(filename);
    if (!infile.is_open()) {
        cerr << "Unable to open file: " << filename << endl;
        return make_pair(-1, -1);
    }

    int numOfVertex, numOfEdge, sourceVertex, destinationVertex;
    infile >> numOfVertex >> numOfEdge;
    sourceVertex = 0;
    destinationVertex = numOfVertex - 1;
    Graph graph(numOfVertex);

    for (int i = 0; i < numOfEdge; ++i) {
        int u, v, cap;
        infile >> u >> v >> cap;
        graph.addEdge(u - 1, v - 1, cap);
    }
    infile.close();

    auto start = high_resolution_clock::now();

    int maxFlow = graph.edmondsKarp(sourceVertex, destinationVertex);

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    return make_pair(maxFlow, duration.count());
}

pair<int, double> testAlgorithmPreflowPush(const string& filename) {
    ifstream infile(filename);
    if (!infile.is_open()) {
        cerr << "Unable to open file: " << filename << endl;
        return make_pair(-1, -1);
    }

    int numOfVertex, numOfEdge, sourceVertex, destinationVertex;
    infile >> numOfVertex >> numOfEdge;
    sourceVertex = 0;
    destinationVertex = numOfVertex - 1;
    Graph graph(numOfVertex);

    for (int i = 0; i < numOfEdge; ++i) {
        int u, v, cap;
        infile >> u >> v >> cap;
        graph.addEdge(u - 1, v - 1, cap);
    }
    infile.close();

    auto start = high_resolution_clock::now();

    int maxFlow = graph.getMaxFlow(sourceVertex, destinationVertex);

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    return make_pair(maxFlow, duration.count());
}
int main() {
    string input_folder_path = "D:/graph/womens/womens/MaxFlowtests"; //путь к папке с тестами

    while (true) {
        int algorithmChoice, testPackage;

        cout << "\nWhich algorithm do you want to use?\n1. Edmonds-Karp\n2. Preflow\n3. Exit\n4. Tests both on random graphs\n";
        cin >> algorithmChoice;
        if (algorithmChoice == 3) {
            break;
        }
        else if (algorithmChoice != 1 && algorithmChoice != 2 && algorithmChoice != 4) {
            cout << "Invalid choice. Please try again." << endl;
            continue;
        }
        vector<string> filenames;
        if (algorithmChoice == 4) {
            input_folder_path = "D:/women/testgraph/graph_tests";
            for (int i = 1; i <= 50; ++i) {
                filenames.push_back(input_folder_path + "/test" + to_string(i) + ".txt");
            }

            cout << "\nThe Edmons-Karp algorithm\n";
            cout << "Test\tVertex\tEdges\tMax Flow\tTime (ms)" << endl;
            //cout << "Test\tMax Flow ed-carp\tTime (ms)" << endl;
            ofstream outfile("results.txt");
            ifstream infile(filenames[0]);
            if (!infile.is_open()) {
                cerr << "Unable to open file: " << filenames[0] << endl;
                return -1;
            }
            int ver, edges;
            infile >> ver >> edges;
            infile.close();
            outfile << ver << "\n" << edges << "\n";
            for (size_t i = 0; i < filenames.size(); ++i) {
                auto result = testAlgorithmEdmondsKarp(filenames[i]);
                //cout << (i + 1) << "\t" << result.first << "\t\t\t" << result.second << endl;
                cout << (i + 1) << "\t" << ver << "\t" << edges << "\t" << result.first << "\t\t\t" << result.second << endl;

                outfile << result.second << "\n";
            }
            //cout << "Test\tMax Flow predpotok\tTime (ms)" << endl;
            cout << "\nPre-flow push\n";
            cout << "Test\tVertex\tEdges\tMax Flow\tTime (ms)" << endl;
            for (size_t i = 0; i < filenames.size(); ++i) {
                ifstream infile(filenames[i]);
                if (!infile.is_open()) {
                    cerr << "Unable to open file: " << filenames[i] << endl;
                    return -1;
                }
                int ver, edges;
                infile >> ver >> edges;
                infile.close();
                auto result = testAlgorithmPreflowPush(filenames[i]);
                //cout << (i + 1) << "\t" << result.first << "\t\t\t" << result.second << endl;
                cout << (i + 1) << "\t" << ver << "\t" << edges << "\t" << result.first << "\t\t\t" << result.second << endl;
                outfile << result.second << "\n";
            }

            return 0;
        }
        // Выбор пакета тестов
        if (algorithmChoice == 1) {
            testPackage = 1;
        }
        else {
            cout << "\nChoose a test package (1, 2, 3, 4) or 5 to Exit: ";
            cin >> testPackage;
        }
        
        if (testPackage == 5) {
            break;
        }else if (testPackage < 1 || testPackage > 4) {
            cout << "Invalid choice. Please try again." << endl;
            continue;
        }
           
        if (testPackage == 1) {
            for (int i = 1; i <= 6; ++i) {
                filenames.push_back(input_folder_path + "/test_" + to_string(i) + ".txt");
            }
        }
        else if (testPackage == 2) {
            for (int i = 1; i <= 5; ++i) {
                filenames.push_back(input_folder_path + "/test_d" + to_string(i) + ".txt");
            }
        }
        else if (testPackage == 3) {
            for (int i = 1; i <= 7; ++i) {
                filenames.push_back(input_folder_path + "/test_rd0" + to_string(i) + ".txt");
            }
        }
        else if (testPackage == 4) {
            for (int i = 1; i <= 9; ++i) {
                filenames.push_back(input_folder_path + "/test_rl0" + to_string(i) + ".txt");
            }
        }

        // Запуск тестов
        if (algorithmChoice == 1) {
            cout << "\nThe Edmons-Karp algorithm\n";
            cout << "Test\tVertex\tEdges\tMax Flow\tTime (ms)" << endl;
            for (size_t i = 0; i < filenames.size(); ++i) {
                ifstream infile(filenames[i]);
                if (!infile.is_open()) {
                    cerr << "Unable to open file: " << filenames[i] << endl;
                    return -1;
                }
                int ver, edges;
                infile >> ver>>edges; 
                infile.close();
                auto result = testAlgorithmEdmondsKarp(filenames[i]);
                cout << (i + 1) << "\t" <<ver<<"\t" << edges<<"\t" << result.first << "\t\t\t" << result.second << endl;
            }
        }
        else if (algorithmChoice == 2) {
            cout << "\nPre-flow push\n";
            cout << "Test\tVertex\tEdges\tMax Flow\tTime (ms)" << endl;
            for (size_t i = 0; i < filenames.size(); ++i) {
                ifstream infile(filenames[i]);
                if (!infile.is_open()) {
                    cerr << "Unable to open file: " << filenames[i] << endl;
                    return -1;
                }
                int ver, edges;
                infile >> ver >> edges;
                infile.close();
                auto result = testAlgorithmPreflowPush(filenames[i]);
                cout << (i + 1) << "\t" << ver << "\t" << edges << "\t" << result.first << "\t\t\t" << result.second << endl;
            }
        }
    }

    return 0;
}

