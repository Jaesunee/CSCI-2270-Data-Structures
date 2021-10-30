#include "EmployeeTree.hpp"

EmployeeTree::EmployeeTree() {
    root = NULL;
}

void deleteEmployee(EmployeeNode *node){
    if(node == NULL){
        delete node;
    }else{
        deleteEmployee(node->right);
        deleteEmployee(node->left);
        delete node;
        node = NULL;
    }
}

EmployeeTree::~EmployeeTree() {
   deleteEmployee(root);
}

void printEmployee(EmployeeNode *node){
    if(node != NULL){
        printEmployee(node->left);
        cout << node->empId << ", " << node->empName << endl;
        printEmployee(node->right);
    }
}

void EmployeeTree::printEmployeeDirectory() {
    if (root == NULL){
        cout << "Tree is Empty. Cannot print." << endl;
    }else{
        printEmployee(root);
    }
}

EmployeeNode* createEmployee(int empId, string empName, int empLevel, string empPhone, int empJoiningYear){
    EmployeeNode *newEmployee = new EmployeeNode;
    newEmployee->empId = empId;
    newEmployee->empName = empName;
    newEmployee->empLevel = empLevel;
    newEmployee->empPhone = empPhone;
    newEmployee->empJoiningYear = empJoiningYear;
    newEmployee->right = NULL;
    newEmployee->left = NULL;
    return newEmployee;
}

EmployeeNode* addEmployeeHelper(EmployeeNode *node, int empId, string empName, int empLevel, string empPhone, int empJoiningYear){
    if (node == NULL){
        return createEmployee(empId, empName, empLevel, empPhone, empJoiningYear);
    }else if(node->empId < empId){
        node->right = addEmployeeHelper(node->right, empId, empName, empLevel, empPhone, empJoiningYear);
    }else if(node->empId > empId){
        node->left = addEmployeeHelper(node->left, empId, empName, empLevel, empPhone, empJoiningYear);
    }
    return node;
}

void EmployeeTree::addEmployee(int empId, string empName, int empLevel, string empPhone, int empJoiningYear) {
    root = addEmployeeHelper(root, empId, empName, empLevel, empPhone, empJoiningYear);
}

void findEmployeeId(int &id,string &empName, int &empLevel, string &empPhone, int &empJoiningYear, EmployeeNode *node, int empId){
    if (node == NULL){
        id = 0;
    }else if (node->empId == empId){
        id = node->empId;
        empName = node->empName;
        empLevel = node->empLevel;
        empPhone = node->empPhone;
        empJoiningYear = node->empJoiningYear;
    }else if(node->empId < empId && node->right != NULL){
        findEmployeeId(id, empName, empLevel, empPhone, empJoiningYear, node->right, empId);
    }else if(node->empId > empId && node->left != NULL){
        findEmployeeId(id, empName, empLevel, empPhone, empJoiningYear, node->left, empId);
    }else{
        id = node->empId;
    }

}

void EmployeeTree::findEmployee(int empId) {
    int id;
    string name;
    int level;
    string phone;
    int year;
    findEmployeeId(id, name, level, phone, year, root, empId);
   if(id != empId ||id == 0){
       cout << "Employee not found." << endl;
   }else{
        cout << "Employee Information" << endl;
        cout << "====================" << endl;
        cout << "ID     : " << id << endl;
        cout << "Name   : " << name << endl;
        cout << "Level  : " << level << endl;
        cout << "Phone  : " << phone << endl;
        cout << "Joined : " << year << endl;
   }
}

void printEmployee(EmployeeNode *node, int level, int year){
    if(node->empLevel >= level && node->empJoiningYear > year){
        cout << "====================" << endl;
        cout << "ID     : " << node->empId << endl;
        cout << "Level  : " << node->empLevel << endl;
        cout << "Joined : " << node->empJoiningYear << endl;
    }

    if(node->left != NULL){
        printEmployee(node->left, level, year);
    }

    if(node->right != NULL){
        printEmployee(node->right, level, year);
    }
}

void EmployeeTree::queryEmployees(int level, int year)
{
    if(root == NULL){
        cout << "Tree is Empty. Cannot query employees directory" << endl;
    }else{
        cout << "Employees who joined after " << year << " and are at least at level " << level << ":" << endl;
        printEmployee(root, level, year);
    }
}

void printLevelNodesHelper(EmployeeNode *node, int level, int node_level){
    
    if(node){
        if(level == node_level){
            cout << node->empId << ", " << node->empName << endl;
        }else if(level < node_level){
            level++;
            printLevelNodesHelper(node->left, level, node_level);
            printLevelNodesHelper(node->right, level, node_level);
        }
    }
}

void EmployeeTree::printLevelNodes(int node_level) {
    int level = 0;
    printLevelNodesHelper(root, level, node_level);
}

void getKthLowestEmployeeIDHelper(EmployeeNode *node, int k, int &count, int &id){

    if(node != NULL){
        getKthLowestEmployeeIDHelper(node->left, k, count, id);
        count++;
        
        if(k == count){
            id = node->empId;
        }
        getKthLowestEmployeeIDHelper(node->right, k, count, id);
    }
}

int EmployeeTree::getKthLowestEmployeeID(int k) {
    int count = 0;
    int id = 0;
    getKthLowestEmployeeIDHelper(root, k, count, id);
    return id;
}



