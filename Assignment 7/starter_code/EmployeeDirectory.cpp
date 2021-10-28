#include "EmployeeDirectory.hpp"

// [HELPER FUNCTIONS]
char EmployeeDirectory::getLastInitial(string name) {
    int found_ix = name.find(' ');

    if (found_ix != string::npos)
        return name[found_ix + 1];

    return '\0';
}

void EmployeeDirectory::printEmployee(LLNode* n) {
    if (n == NULL) {
        cout << "LLNode is NULL." << endl;
    }
    else {
        cout << "Employee Information" << endl;
        cout << "====================" << endl;
        cout << "ID     : " << n->empId << endl;
        cout << "Name   : " << n->empName << endl;
        cout << "Level  : " << n->empLevel << endl;
        cout << "Phone  : " << n->empPhone << endl;
        cout << "Joined : " << n->empJoiningYear << endl;
    }
}


// [TO BE IMPLEMENTED]
// ----------------------------------------------------------------------------

EmployeeDirectory::EmployeeDirectory() {
    root = NULL;
}

// ----------------------------------------------------------------------------

void deleteTreeNode(TreeNode *node){
    if(node == NULL){
        return;
    }else{
        if(node->right != NULL){
            deleteTreeNode(node->right);
        }
        if(node->left != NULL){
            deleteTreeNode(node->left);
        }
        LLNode *temp = node->head;
        LLNode *next;
        if(temp == NULL){
            delete node;
            return;
        }else{
            if(temp->next == NULL){
                delete temp;
                delete node; 
                return;
            }
            while(temp->next != NULL){
                next = temp->next;
                delete temp;
                temp = next;
            }
            delete temp;
        }
        delete node;
    }
    return;
}

EmployeeDirectory::~EmployeeDirectory() {
    deleteTreeNode(root);
}

// ----------------------------------------------------------------------------

TreeNode* searchCharNodeHelper(TreeNode *node, char key) {
    if(node == NULL){
        return node;
    }else if(node->lastInitial == key){
        return node;
    }else if(node->lastInitial < key && node->right != NULL){
        searchCharNodeHelper(node->right, key);
    }else if(node->lastInitial > key && node->left != NULL){
        searchCharNodeHelper(node->left, key);
    }else{
        return NULL;
    }
}

TreeNode* EmployeeDirectory::searchCharNode(char key) {
    return searchCharNodeHelper(root, key);
}

// ----------------------------------------------------------------------------

void showEmployeeDirectoryHelper(TreeNode *node){
    if(node != NULL){
        showEmployeeDirectoryHelper(node->left);
        if(node->parent == NULL){
            cout << "[Employees with lastInitial=" << node-> lastInitial << ", parent=" << ' ' << "]" << endl;
        }else{
            cout << "[Employees with lastInitial=" << node-> lastInitial << ", parent=" << node->parent->lastInitial << "]" << endl;
        }
        LLNode *temp = node->head;
        if(temp == NULL){
            cout << "No employees found." << endl;
            cout << "---------------------------------------" << endl;
        }else{
            while(temp != NULL){
                cout << "> " << temp->empName << ", " << temp->empPhone << ", " << temp->empId<< endl;
                temp = temp->next;
            }
            cout << "---------------------------------------" << endl;
        }
        showEmployeeDirectoryHelper(node->right);
    }
}

void EmployeeDirectory::showEmployeeDirectory() {
    showEmployeeDirectoryHelper(root);
}

// ----------------------------------------------------------------------------

LLNode* EmployeeDirectory::searchEmployee(int empId, string empName) {
    
    if(searchCharNode(getLastInitial(empName)) == NULL){
        return NULL;
    }else if(searchCharNode(getLastInitial(empName))->head == NULL){
        return NULL;
    }else{
        LLNode *temp = searchCharNode(getLastInitial(empName))->head;
        while(temp->next != NULL){
            if(temp->empId == empId){
                return temp;
            }
            temp = temp->next;
        }
        if(temp->empId == empId){
            return temp;
        }else{
            return NULL;
        }
    }
}

// ----------------------------------------------------------------------------

void insertEmployeeHelper(TreeNode *&node, TreeNode *&parent, char lastInitial, int empId, string empName, int empLevel, string empPhone, int empJoiningYear){
    if (node == NULL){
        node = new TreeNode(lastInitial);
        node->head = new LLNode(empId, empName, empLevel, empPhone, empJoiningYear);
        if(parent != NULL){
            node->parent = parent;
        }
    }else if(node->lastInitial < lastInitial){
        insertEmployeeHelper(node->right, node, lastInitial, empId, empName, empLevel, empPhone, empJoiningYear);
    }else if(node->lastInitial > lastInitial){
        insertEmployeeHelper(node->left, node, lastInitial, empId, empName, empLevel, empPhone, empJoiningYear);
    }
}

void EmployeeDirectory::insertEmployee(int empId, string empName, int empLevel, string empPhone, int empJoiningYear) {
    char lastInitial = getLastInitial(empName);

    if(searchCharNode(lastInitial) != NULL){
        TreeNode *node = searchCharNode(lastInitial);
        
        if(node->head == NULL){
            node->head = new LLNode(empId, empName, empLevel, empPhone, empJoiningYear);
        }else if(node->head->empId > empId){
            LLNode *newNode = new LLNode(empId, empName, empLevel, empPhone, empJoiningYear);
            LLNode *temp = node->head;
            node->head = newNode;
            node->head->next = temp;
        }else if(node->head->empId < empId){
            LLNode *newNode = new LLNode(empId, empName, empLevel, empPhone, empJoiningYear);
            LLNode *temp = node->head;
            LLNode *next;
            if(temp->next == NULL){
                next = temp->next;
                temp->next = newNode;
                temp->next->next = next;
            }else{
                while(temp->next->next != NULL && (temp->empId < empId && temp->next->empId < empId)){
                    temp = temp->next;
                }
                if(temp->next->empId < empId){
                    temp = temp->next;
                }
                next = temp->next;
                temp->next = newNode;
                temp->next->next = next;
            }
        }
    }else{
        if(root == NULL){
            root = new TreeNode(lastInitial);
            root->head = new LLNode(empId, empName, empLevel, empPhone, empJoiningYear);
        }else{
            insertEmployeeHelper(root, root->parent, lastInitial, empId, empName, empLevel, empPhone, empJoiningYear);
        }
        
    }
}

// ----------------------------------------------------------------------------

void EmployeeDirectory::removeEmployee(int empId, string empName) {
    if(searchCharNode(getLastInitial(empName)) == NULL){
        cout << "Employee not found." << endl;
    }else{
        LLNode *temp = searchCharNode(getLastInitial(empName))->head;
        LLNode *prev;
        LLNode *next;

        if(temp->empId == empId){
            next = temp->next;
            delete temp;
            searchCharNode(getLastInitial(empName))->head = next;
            return;
        }
        
        prev = temp;
        temp = temp->next;
        next = temp->next;
        
        if(temp->empId == empId){
            delete temp;
            prev->next = next;
            return;
        }
        
        while(next != NULL){
            if(temp->empId == empId){
                delete temp;
                prev->next = next;
                return;
            }
            prev = prev->next;
            temp = temp->next;
            next = next->next;
        }

        if(temp->next->empId == empId){
            delete temp;
            prev->next = next;
        }
        return;
    }
}

// ----------------------------------------------------------------------------

void EmployeeDirectory::leftRotate(TreeNode* curr) {

    if(curr->right == NULL){
        return;
    }

    TreeNode *right = curr->right;
    TreeNode *rightLeftChild = right->left;
    if(root == curr){
        right->parent = NULL;
        root = right;
        curr->parent = root;
        curr->right = rightLeftChild;
        if(rightLeftChild != NULL){
            rightLeftChild->parent = curr;
        }
        root->left = curr;
    }else{
        TreeNode *parent = curr->parent;
        if(curr->lastInitial < parent->lastInitial){
            parent->left = right;
        }else{
            parent->right = right;
        }
        right->parent = curr->parent;
        curr->parent = right;
        curr->right = rightLeftChild;
        if(rightLeftChild != NULL){
            rightLeftChild->parent = curr;
        }
        right->left = curr;
        
    }
}

// ----------------------------------------------------------------------------
