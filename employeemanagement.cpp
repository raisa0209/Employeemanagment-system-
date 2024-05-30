#include <bits/stdc++.h>
#include <fstream>
#include <conio.h>
#include <windows.h>
#include <algorithm>
#include <stdexcept>
#include <queue>
#include <unordered_map>
#include <stack>

using namespace std;

class BSTNode {
public:
    string EmployeeID, Name, Position, Department, JoiningDate , PhoneNumber, newPosition;
    float salary;
    BSTNode* left;
    BSTNode* right;

    BSTNode(string id, string name, string pos, string dept, string joiningDate, float sal)
        : EmployeeID(id), Name(name), Position(pos), Department(dept), JoiningDate(joiningDate), salary(sal), left(nullptr), right(nullptr) {}
};

class Employee {
private:
    BSTNode* root;
    string username;
    string password;
    unordered_map<string, unordered_map<string, int>> graph;
    vector<string> positions;
    vector<string> departments;
    unordered_map<string, float> positionSalaries;
    unordered_map<string, string> employeePositions;


public:
    Employee();
    ~Employee();
    void showWelcomeScreen();
    void authenticateUser();
    void displayMenu();
    void addEmployee();
    void searchEmployeeByID();
    void editEmployee();
    void deleteEmployee();
    void displayEmployees();
    void generateSalarySlip();
    void searchByDepartment();
    void loadEmployeesFromFile();
    void saveChangesToFile(BSTNode* employee);
    void saveEmployeesToFile();
    void saveEmployeesInOrder(BSTNode* node, ofstream& outFile);
    void freeMemory(BSTNode* node);
    void askToContinueOrExit();
    void transferEmployee(string id);
    pair<vector<string>, int> shortestPath(const string& source, const string& destination);
    BSTNode* insert(BSTNode* node, string id, string name, string pos, string dept, string joiningDate, float sal);
    BSTNode* search(BSTNode* node, string id);
    BSTNode* deleteNode(BSTNode* root, string id);
    BSTNode* minValueNode(BSTNode* node);
    void inorder(BSTNode* node);
    void searchDepartment(BSTNode* node, string dept);
    void visitBranch();
    pair<vector<string>, int> dijkstra(const string& source, const string& destination);


};

Employee::Employee() : root(nullptr), username(""), password(""), positionSalaries({
    {"Manager", 100000.00},
    {"Assistant Manager", 80000.00},
    {"Team Lead", 70000.00},
    {"Senior Developer", 60000.00},
    {"Junior Developer", 40000.00},
    {"Intern", 20000.00},
    {"HR", 50000.00},
    {"Finance Officer", 55000.00},
    {"Sales Executive", 45000.00},
    {"Marketing Specialist", 48000.00}
}) {
    graph["cantonment"]["mirpur"] = 2;
    graph["cantonment"]["uttara"] = 3;
    graph["mirpur"]["cantonment"] = 2;
    graph["mirpur"]["savar"] = 10;
    graph["mirpur"]["uttara"] = 1;
    graph["mirpur"]["rampura"] = 5;
    graph["uttara"]["cantonment"] = 3;
    graph["uttara"]["mirpur"] = 1;
    graph["uttara"]["rampura"] = 6;
    graph["rampura"]["uttara"] = 6;
    graph["rampura"]["gazipur"] = 11;
    graph["rampura"]["mirpur"] = 5;
    graph["gazipur"]["rampura"] = 11;
    graph["gazipur"]["savar"] = 4;
    graph["savar"]["mirpur"] = 10;


    positions = {"Manager", "Assistant Manager", "Team Lead", "Senior Developer", "Junior Developer", "Intern", "HR", "Finance Officer", "Sales Executive", "Marketing Specialist"};
    departments = {"HR", "Finance", "IT", "Sales", "Marketing"};
}




Employee::~Employee() {
    freeMemory(root);
}

void Employee::freeMemory(BSTNode* node) {
    if (node != nullptr) {
        freeMemory(node->left);
        freeMemory(node->right);
        delete node;
    }
}

void Employee::showWelcomeScreen() {
    system("cls");
    cout << "\n\n\n\n\n\n\n";
    cout << "\t\t\t==================================================";
    cout << "\n\t\t\t   ============================================";
    cout << "\n\n\n\t\t\t     WELCOME TO EMPLOYEE MANAGEMENT SYSTEM ";
    cout << "\n\n\t\t\t   ============================================";
    cout << "\n\t\t\t==================================================";
    getch();
}

void Employee::authenticateUser() {
    const string validUsernames[] = {"raisa", "saima", "mim"};
    const string validPasswords[] = {"123456", "123456", "123456"};
    const int numUsers = sizeof(validUsernames) / sizeof(validUsernames[0]);

    while (true) {
        try {
            system("cls");

            cout << "\n\n";
            cout << "\t\t\t===============================";
            cout << "\n\n\t\t\t\tLOGIN PANEL";
            cout << "\n\n\t\t\t===============================";
            cout << "\n\n\n ENTER USER NAME: ";
            cin >> username;
            cout << "\n\n ENTER PASSWORD: ";
            password = "";
            for (int i = 1; i <= 6; i++) {
                password += getch();
                cout << "*";
            }

            bool authenticated = false;
            for (int i = 0; i < numUsers; i++) {
                if (username == validUsernames[i] && password == validPasswords[i]) {
                    authenticated = true;
                    break;
                }
            }

            if (authenticated) {
                cout << "\n\n\n\t\t\tCONGRATULATIONS! LOGIN SUCCESS";
                cout << "\n\n\n\t\t\t\tLOADING";
                for (int i = 1; i <= 6; i++) {
                    Sleep(500);
                    cout << ".";
                }
                loadEmployeesFromFile();
                displayMenu();
            } else {
                throw invalid_argument("Invalid login credentials");
            }
        } catch (const invalid_argument& e) {
            cout << "\n\n\n\t\t\t" << e.what();
        } catch (const exception& e) {
            cout << "\n\n\n\t\t\tAn error occurred: " << e.what();
        }
        getch();
    }
}

void Employee::displayMenu() {
    string id;
    string employeeID;
    string newPosition;
    while (true) {
        try {
            system("cls");

            int choice;
            cout << "\n\n\t\t\t=========================";
            cout << "\n\n\t\t\t   EMPLOYEE MANAGEMENT";
            cout << "\n\n\t\t\t=========================";
            cout << "\n\n\n 1. Add Employee Record";
            cout << "\n 2. Search Employee Record";
            cout << "\n 3. Edit Employee Record";
            cout << "\n 4. Delete Employee Record";
            cout << "\n 5. Display All Employees";
            cout << "\n 6. Generate Salary Slip";
            cout << "\n 7. Search by Department";
            cout << "\n 8. Visit Branch";
            cout << "\n 9. Transfer Employee";
            cout << "\n 10. EXIT";
            cout << "\n\n YOUR CHOICE: ";
            cin >> choice;

            switch (choice) {
            case 1:
                addEmployee();
                break;
            case 2:
                searchEmployeeByID();
                break;
            case 3:
                editEmployee();
                break;
            case 4:
                deleteEmployee();
                break;
            case 5:
                displayEmployees();
                break;
            case 6:
                generateSalarySlip();
                break;
            case 7:
                searchByDepartment();
                break;
            case 8:
                visitBranch();
                break;
            case 9:
                cout << "\nEnter Employee ID to transfer: ";
                cin >> id;
                transferEmployee(id);
                break;
           case 10:
                saveEmployeesToFile();
                askToContinueOrExit();
                return;
            default:
                throw invalid_argument("Invalid choice, please try again");
            }
        } catch (const invalid_argument& e) {
            cout << "\n\n " << e.what() << "";
        } catch (const exception& e) {
            cout << "\n\n An error occurred: " << e.what();
        }
        getch();
    }
}

void Employee::askToContinueOrExit() {
    while (true) {
        try {
            system("cls");

            int choice;
            cout << "\n\n\t\t\t=======================================";
            cout << "\n\n\t\t\t   Are you sure you want to exit";
            cout << "\n\n\t\t\t=======================================";
            cout << "\n\n\n 1. Continue display menu";
            cout << "\n 2. Exit ";
            cout << "\n\n YOUR CHOICE: ";
            cin >> choice;

            switch (choice) {
            case 1:
                displayMenu();
                return;
            case 2:
                cout << "\n\n Exited.";
                exit(0);
            default:
                throw invalid_argument("Invalid choice, please try again");
            }
        } catch (const invalid_argument& e) {
            cout << "\n\n " << e.what() << "";
        } catch (const exception& e) {
            cout << "\n\n An error occurred: " << e.what();
        }
        getch();
    }
}

BSTNode* Employee::insert(BSTNode* node, string id, string name, string pos, string dept, string joiningDate, float sal) {
    if (node == nullptr) {
        return new BSTNode(id, name, pos, dept, joiningDate, sal);
    }
    if (id < node->EmployeeID) {
        node->left = insert(node->left, id, name, pos, dept, joiningDate, sal);
    } else if (id > node->EmployeeID) {
        node->right = insert(node->right, id, name, pos, dept, joiningDate, sal);
    }
    return node;
}

void Employee::addEmployee() {
    try {
        system("cls");
        string id, name, pos, dept, joiningDate, phoneNumber;
        float sal;
        int age;

        cout << "\n\n\t\t\t===============================";
        cout << "\n\n\t\t\t    ADD NEW EMPLOYEE";
        cout << "\n\n\t\t\t===============================";
        cout << "\n\n\n ENTER EMPLOYEE ID: ";
        cin >> id;
        cout << "\n\n ENTER EMPLOYEE NAME: ";
        cin.ignore();
        getline(cin, name);

        cout << "\n\n SELECT POSITION (choose a number): ";
        for (int i = 0; i < positions.size(); ++i) {
            cout << "\n " << (i + 1) << ". " << positions[i];
        }
        int posChoice;
        cout << "\n\n YOUR CHOICE: ";
        cin >> posChoice;
        if (posChoice < 1 || posChoice > positions.size()) {
            throw invalid_argument("Invalid choice for position");
        }
        pos = positions[posChoice - 1];

        sal = positionSalaries[pos];

        cout << "\n\n SELECT DEPARTMENT (choose a number): ";
        for (int i = 0; i < departments.size(); ++i) {
            cout << "\n " << (i + 1) << ". " << departments[i];
        }
        int deptChoice;
        cout << "\n\n YOUR CHOICE: ";
        cin >> deptChoice;
        if (deptChoice < 1 || deptChoice > departments.size()) {
            throw invalid_argument("Invalid choice for department");
        }
        dept = departments[deptChoice - 1];

        cout << "\n\n ENTER JOINING DATE (YYYY-MM-DD): ";
        cin >> joiningDate;


        cout << "\n\n ENTER PHONE NUMBER (11 digits starting with '01'): ";
        cin >> phoneNumber;
        if (phoneNumber.length() != 11 || phoneNumber.substr(0, 2) != "01") {
            throw invalid_argument("Invalid phone number");
        }


        while (true) {
            cout << "\n\n ENTER AGE (20 to 65): ";
            cin >> age;
            if (age < 20 || age > 65) {
                cout << "\n\n Invalid age. Please enter age between 20 and 65.";
            } else {
                break;
            }
        }

        root = insert(root, id, name, pos, dept, joiningDate, sal);
        cout << "\n\n Employee added successfully!";
        saveEmployeesToFile();
    } catch (const invalid_argument& e) {
        cout << "\n\n " << e.what();
    } catch (const exception& e) {
        cout << "\n\n An error occurred: " << e.what();
    }
}


BSTNode* Employee::search(BSTNode* node, string id) {
    if (node == nullptr || node->EmployeeID == id) {
        return node;
    }
    if (id < node->EmployeeID) {
        return search(node->left, id);
    } else {
        return search(node->right, id);
    }
}

void Employee::searchEmployeeByID() {
    try {
        system("cls");
        string id;

        cout << "\n\n\t\t\t===============================";
        cout << "\n\n\t\t\t    SEARCH EMPLOYEE RECORD";
        cout << "\n\n\t\t\t===============================";
        cout << "\n\n\n ENTER EMPLOYEE ID TO SEARCH: ";
        cin >> id;

        BSTNode* employee = search(root, id);
        if (employee != nullptr) {
            cout << "\n\n EMPLOYEE ID: " << employee->EmployeeID;
            cout << "\n EMPLOYEE NAME: " << employee->Name;
            cout << "\n POSITION: " << employee->Position;
            cout << "\n DEPARTMENT: " << employee->Department;
            cout << "\n JOINING DATE: " << employee->JoiningDate;
            cout << "\n SALARY: " << employee->salary;
        } else {
            cout << "\n\n Employee not found!";
        }
    } catch (const exception& e) {
        cout << "\n\n An error occurred: " << e.what();
    }
}



BSTNode* Employee::minValueNode(BSTNode* node) {
    BSTNode* current = node;
    while (current && current->left != nullptr) {
        current = current->left;
    }
    return current;
}

void Employee::editEmployee() {
    try {
        system("cls");
        string id;

        cout << "\n\n\t\t\t===============================";
        cout << "\n\n\t\t\t    EDIT EMPLOYEE RECORD";
        cout << "\n\n\t\t\t===============================";
        cout << "\n\n\n ENTER EMPLOYEE ID TO EDIT: ";
        cin >> id;

        BSTNode* employee = search(root, id);
        if (employee != nullptr) {
            cout << "\n\n EMPLOYEE ID: " << employee->EmployeeID;
            cout << "\n EMPLOYEE NAME: " << employee->Name;
            cout << "\n POSITION: " << employee->Position;
            cout << "\n DEPARTMENT: " << employee->Department;
            cout << "\n JOINING DATE: " << employee->JoiningDate;
            cout << "\n PHONE NUMBER: " << employee->PhoneNumber;
            cout << "\n SALARY: " << employee->salary;

            string name, pos, dept, joiningDate, phone;
            float sal;


            cout << "\n\n ENTER NEW NAME (leave empty to keep current): ";
            cin.ignore();
            getline(cin, name);
            if (!name.empty()) {
                employee->Name = name;
            }


            cout << "\n\n SELECT NEW POSITION (choose a number, leave empty to keep current): ";
            for (int i = 0; i < positions.size(); ++i) {
                cout << "\n " << (i + 1) << ". " << positions[i];
            }
            string posChoiceStr;
            cout << "\n\n YOUR CHOICE: ";
            getline(cin, posChoiceStr);
            if (!posChoiceStr.empty()) {
                int posChoice = stoi(posChoiceStr);
                if (posChoice < 1 || posChoice > positions.size()) {
                    throw invalid_argument("Invalid choice for position");
                }
                employee->Position = positions[posChoice - 1];
                employee->salary = positionSalaries[employee->Position];


            cout << "\n\n SELECT NEW DEPARTMENT (choose a number, leave empty to keep current): ";
            for (int i = 0; i < departments.size(); ++i) {
                cout << "\n " << (i + 1) << ". " << departments[i];
            }
            string deptChoiceStr;
            cout << "\n\n YOUR CHOICE: ";
            getline(cin, deptChoiceStr);
            if (!deptChoiceStr.empty()) {
                int deptChoice = stoi(deptChoiceStr);
                if (deptChoice < 1 || deptChoice > departments.size()) {
                    throw invalid_argument("Invalid choice for department");
                }
                employee->Department = departments[deptChoice - 1];
            }

            cout << "\n\n ENTER NEW PHONE NUMBER (leave empty to keep current): ";
            getline(cin, phone);
            if (!phone.empty()) {
                if (phone.length() != 11 || phone.substr(0, 2) != "01") {
                    throw invalid_argument("Invalid phone number");
                }
                employee->PhoneNumber = phone;
            }

            saveEmployeesToFile();
            saveChangesToFile(employee);

            cout << "\n\n Employee record updated successfully!";
        } else {
            cout << "\n\n Employee not found!";
        }
    } catch (const invalid_argument& e) {
        cout << "\n\n " << e.what();
    } catch (const exception& e) {
        cout << "\n\n An error occurred: " << e.what();
    }
}



BSTNode* Employee::deleteNode(BSTNode* root, string id) {
    if (root == nullptr) {
        return root;
    }
    if (id < root->EmployeeID) {
        root->left = deleteNode(root->left, id);
    } else if (id > root->EmployeeID) {
        root->right = deleteNode(root->right, id);
    } else {
        if (root->left == nullptr) {
            BSTNode* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == nullptr) {
            BSTNode* temp = root->left;
            delete root;
            return temp;
        }
        BSTNode* temp = minValueNode(root->right);
        root->EmployeeID = temp->EmployeeID;
        root->right = deleteNode(root->right, temp->EmployeeID);
    }
    return root;
}

void Employee::deleteEmployee() {
    try {
        system("cls");
        string id;

        cout << "\n\n\t\t\t===============================";
        cout << "\n\n\t\t\t    DELETE EMPLOYEE RECORD";
        cout << "\n\n\t\t\t===============================";
        cout << "\n\n\n ENTER EMPLOYEE ID TO DELETE: ";
        cin >> id;

        root = deleteNode(root, id);
        cout << "\n\n Employee record deleted successfully!";
        saveEmployeesToFile();
    } catch (const exception& e) {
        cout << "\n\n An error occurred: " << e.what();
    }
}

void Employee::inorder(BSTNode* node) {
    if (node != nullptr) {
        inorder(node->left);
        cout << "\n\n Employee ID: " << node->EmployeeID;
        cout << "\n Employee Name: " << node->Name;
        cout << "\n Employee Position: " << node->Position;
        cout << "\n Employee Department: " << node->Department;
        cout << "\n Employee Joining Date: " << node->JoiningDate;
        cout << "\n Employee Salary: " << node->salary << " TK";
        inorder(node->right);
    }
}

void Employee::displayEmployees() {
    system("cls");

    cout << "\n\n\t\t\t===========================";
    cout << "\n\n\t\t\t INFORMATION OF EMPLOYEES";
    cout << "\n\n\t\t\t===========================";
    inorder(root);
    cout << "\n\n Press any key to continue...";
    getch();
    return;
}

void Employee::generateSalarySlip() {
    while (true) {
        try {
            system("cls");

            string id;
            cout << "\n\n\t\t\t===========================";
            cout << "\n\n\t\t\t     SALARY SLIP";
            cout << "\n\n\t\t\t===========================";
            cout << "\n\n\n Enter Employee ID: ";
            cin >> id;

            BSTNode* employee = search(root, id);
            if (employee != nullptr) {
                cout << "\n\n Employee ID: " << employee->EmployeeID;
                cout << "\n Employee Name: " << employee->Name;
                cout << "\n Employee Position: " << employee->Position;
                cout << "\n Employee Department: " << employee->Department;
                cout << "\n Employee Salary: " << employee->salary <<"TK";
            } else {
                throw invalid_argument("Employee not found");
            }
        } catch (const invalid_argument& e) {
            cout << "\n\n " << e.what() << "";
        } catch (const exception& e) {
            cout << "\n\n An error occurred: " << e.what();
        }
        cout << "\n\n Press any key to continue...";
        getch();
        return;
    }
}
void Employee::searchByDepartment() {
    while (true) {
        try {
            system("cls");

            string dept;
            cout << "\n\n\t\t\t===========================";
            cout << "\n\n\t\t\t   SEARCH BY DEPARTMENT";
            cout << "\n\n\t\t\t===========================";
            cout << "\n\n\n Enter Department: ";
            cin >> dept;

            cout << "\n\n Employees in Department " << dept << ":\n";

            queue<BSTNode*> q;

            q.push(root);
            bool found = false;

            while (!q.empty()) {
                BSTNode* current = q.front();
                q.pop();

                if (current != nullptr && current->Department == dept) {
                    found = true;
                    cout << "\n\n Employee ID: " << current->EmployeeID;
                    cout << "\n Employee Name: " << current->Name;
                    cout << "\n Employee Position: " << current->Position;
                    cout << "\n Employee Salary: " << current->salary;
                }
                if (current != nullptr && current->left != nullptr) {
                    q.push(current->left);
                }
                if (current != nullptr && current->right != nullptr) {
                    q.push(current->right);
                }
            }

            if (!found) {
                cout << "\n\n No employees found in department " << dept << ".";
            }
        } catch (const exception& e) {
            cout << "\n\n An error occurred: " << e.what();
        }
        cout << "\n\n Press any key to continue...";
        getch();
        return;
    }
}


void Employee::visitBranch() {
    while (true) {
        try {
            system("cls");

            cout << "\n\n\t\t\t===========================";
            cout << "\n\n\t\t\t      VISIT BRANCH";
            cout << "\n\n\t\t\t===========================";
            cout << "\n\n\n Select Source Branch:";
            cout << "\n 1. cantonment";
            cout << "\n 2. uttara";
            cout << "\n 3. gazipur";
            cout << "\n 4. rampura";
            cout << "\n 5. mirpur";
            cout << "\n 6. savar";
            cout << "\n\n YOUR CHOICE: ";
            int sourceChoice;
            cin >> sourceChoice;

            cout << "\n\n\n Select Destination Branch:";
            cout << "\n 1. cantonment";
            cout << "\n 2. uttara";
            cout << "\n 3. gazipur";
            cout << "\n 4. rampura";
            cout << "\n 5. mirpur";
            cout << "\n 6. savar";
            cout << "\n\n YOUR CHOICE: ";
            int destinationChoice;
            cin >> destinationChoice;

            string branches[] = {"cantonment", "uttara", "gazipur", "rampura", "mirpur", "savar"};

            if (sourceChoice < 1 || sourceChoice > 6 || destinationChoice < 1 || destinationChoice > 6) {
                throw invalid_argument("Invalid branch selection. Please try again.");
            }

            string sourceBranch = branches[sourceChoice - 1];
            string destinationBranch = branches[destinationChoice - 1];

            auto result = dijkstra(sourceBranch, destinationBranch);
            vector<string> path = result.first;
            int distance = result.second;

            if (path.empty()) {
                cout << "\n\n No path found between " << sourceBranch << " and " << destinationBranch << ".";
            } else {
                cout << "\n\n Shortest path from " << sourceBranch << " to " << destinationBranch << ":\n";
                for (const string& branch : path) {
                    cout << branch << " -> ";
                } cout<<"Destination reached";
                cout << "\n\n Distance: " << distance << " km";
            }
        } catch (const invalid_argument& e) {
            cout << "\n\n " << e.what() << "";
        } catch (const exception& e) {
            cout << "\n\n An error occurred: " << e.what() << "";
        }
        cout << "\n\n Press any key to continue...";
        getch();
        return;
    }
}

pair<vector<string>, int> Employee::dijkstra(const string& source, const string& destination) {
    unordered_map<string, int> dist;
    unordered_map<string, string> prev;
    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> pq;

    // Initialize distances
    for (const auto& entry : graph) {
        dist[entry.first] = INT_MAX;
    }
    dist[source] = 0;
    pq.push({0, source});

    while (!pq.empty()) {
        auto top = pq.top();
        pq.pop();
        int u_dist = top.first;
        string u = top.second;

        if (u_dist > dist[u]) continue;

        for (const auto& neighbor : graph[u]) {
            string v = neighbor.first;
            int weight = neighbor.second;

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                prev[v] = u;
                pq.push({dist[v], v});
            }
        }
    }
    vector<string> path;
    int distance = dist[destination];
    string current = destination;
    while (prev.find(current) != prev.end()) {
        path.push_back(current);
        current = prev[current];
    }
    path.push_back(source);
    reverse(path.begin(), path.end());

    return {path, distance};
}

void Employee::loadEmployeesFromFile() {
    ifstream inFile("employees.txt");
    if (!inFile) {
        cout << "\n\n File not found or unable to open!";
        return;
    }

    string id, name, pos, dept, joiningDate;
    float sal;
    while (inFile >> id >> name >> pos >> dept >> joiningDate >> sal) {
        root = insert(root, id, name, pos, dept, joiningDate, sal);
    }

    inFile.close();
}

void Employee::transferEmployee(string id) {
    try {
        system("cls");
        string employeeID = id;

        cout << "\n\n\t\t\t===============================";
        cout << "\n\n\t\t\t    TRANSFER EMPLOYEE";
        cout << "\n\n\t\t\t===============================";
        cout << "\n\n\n ENTER EMPLOYEE ID TO TRANSFER: " << employeeID;

        cout << "\n\n SELECT DEPARTMENT TO TRANSFER (choose a number): ";
        for (int i = 0; i < departments.size(); ++i) {
            cout << "\n " << (i + 1) << ". " << departments[i];
        }

        int deptChoice;
        cout << "\n\n YOUR CHOICE: ";
        cin >> deptChoice;

        if (deptChoice < 1 || deptChoice > departments.size()) {
            throw invalid_argument("Invalid choice for department");
        }

        string sourceDepartment;
        string destinationDepartment = departments[deptChoice - 1];

        auto result = shortestPath(sourceDepartment, destinationDepartment);
        vector<string> path = result.first;



        cout << "\n\n Confirm transfer (Y/N): ";
        char confirm;
        cin >> confirm;
        if (confirm == 'Y' || confirm == 'y') {

            cout << "\n\n Employee transferred successfully!";
            saveEmployeesToFile();

        } else {
            cout << "\n\n Transfer canceled.";
        }
    } catch (const invalid_argument& e) {
        cout << "\n\n " << e.what();
    } catch (const exception& e) {
        cout << "\n\n An error occurred: " << e.what();
    }
}

pair<vector<string>, int> Employee::shortestPath(const string& source, const string& destination) {
    int V = departments.size();
    unordered_map<string, int> nodeIndex;
    vector<vector<int>> dist(V, vector<int>(V, INT_MAX));
    vector<vector<int>> next(V, vector<int>(V, -1));

    // Initialize node index
    for (int i = 0; i < V; ++i) {
        nodeIndex[departments[i]] = i;
        dist[i][i] = 0;
        next[i][i] = i;
    }

    for (const auto& entry : graph) {
        int u = nodeIndex[entry.first];
        for (const auto& neighbor : entry.second) {
            int v = nodeIndex[neighbor.first];
            dist[u][v] = neighbor.second;
            next[u][v] = v;
        }
    }

    for (int k = 0; k < V; ++k) {
        for (int i = 0; i < V; ++i) {
            for (int j = 0; j < V; ++j) {
                if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX && dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    next[i][j] = next[i][k];
                }
            }
        }
    }
    vector<string> path;
    int u = nodeIndex[source];
    int v = nodeIndex[destination];

    if (next[u][v] == -1) {
        return {path, INT_MAX}; // No path found
    }

    for (; u != v; u = next[u][v]) {
        path.push_back(departments[u]);
    }
    path.push_back(departments[v]);

    return {path, dist[nodeIndex[source]][nodeIndex[destination]]};
}


void Employee::saveEmployeesToFile() {
    ofstream outFile("employees.txt",ios::app);
    if (!outFile) {
        cout << "\n\n Unable to create file!";
        return;
    }

    saveEmployeesInOrder(root, outFile);

    outFile.close();
}
void Employee::saveChangesToFile(BSTNode* employee) {

    ofstream outFile("employee_changes.txt", ios::app);
    if (outFile.is_open()) {
        // Write employee information to file
        outFile << "Employee ID: " << employee->EmployeeID << "\n";
        outFile << "Name: " << employee->Name << "\n";
        outFile << "Position: " << employee->Position << "\n";
        outFile << "Department: " << employee->Department << "\n";
        outFile << "Phone Number: " << employee->PhoneNumber << "\n";
        outFile << "--------------------------\n";
        outFile.close();
    } else {
        cout << "\n\n Error: Unable to open file for writing.";
    }
}

void Employee::saveEmployeesInOrder(BSTNode* node, ofstream& outFile) {
    if (node != nullptr) {
        saveEmployeesInOrder(node->left, outFile);
        outFile << node->EmployeeID << " " << node->Name << " " << node->Position << " " << node->Department << " " << node->JoiningDate << " " << node->salary << endl;
        saveEmployeesInOrder(node->right, outFile);
    }
}

int main() {
    Employee emp;
    emp.showWelcomeScreen();
    emp.authenticateUser();
    emp.saveEmployeesToFile();
    return 0;
}

