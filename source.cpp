#include <iostream>  //M.Moeed Asif B 21i-0483
#include <fstream>
#include<queue>
#include <string>
#include<sstream>
using namespace std;

struct URL   //link lists for urls 
{
    string url;
    URL* next;
    URL(string u)
    {
        url = u;
        next = NULL;
    }
};
struct Node //node of the bst tree
{
    int keyword;
    Node* left;
    Node* right;
    URL* urlptr;
    Node()
    {
        keyword = 0;
        left = NULL;
        right = NULL;
        urlptr = NULL;
    }
    Node(int val)
    {
        keyword = val;
        left = NULL;
        right = NULL;
		urlptr = NULL;
    }

};


class BST
{
public:
    Node* root;
    BST()
    {
        root = NULL;
    }
    Node* insert(Node* subroot, int keyword, string url)
    {
        if (subroot == NULL)
        {
            Node* newNode = new Node(keyword);
            newNode->urlptr = new URL(url);
            subroot = newNode;
        }
        else if (keyword == subroot->keyword)
        {
            URL* urlNode = new URL(url);
            if (subroot->urlptr == NULL) {
                subroot->urlptr = urlNode;
            }
            else {
                URL* ptr = subroot->urlptr;
                while (ptr->next != NULL)
                {
                    ptr = ptr->next;
                }
                ptr->next = urlNode;
            }
        }
        else if (keyword < subroot->keyword)
        {
            subroot->left = insert(subroot->left, keyword, url);
        }
        else  if (keyword > root->keyword)
        {
            subroot->right = insert(subroot->right, keyword, url);
        }
        return subroot;
    }
    void display(Node* subroot)
    {
        if (subroot == NULL) {
            return;
        }
        display(subroot->left);
        cout << "Keyword: " << subroot->keyword << endl;
        cout << "URLs: ";
        URL* ptr = subroot->urlptr;
        while (ptr != NULL) {
            cout << ptr->url << " " << endl;
            ptr = ptr->next;
        }
        cout << endl;
        display(subroot->right);
    }
    void insert(int keyword, string url)
    {
        root = insert(root, keyword, url);
    }
    Node* getRoot()
    {
        return root;
    }
    void searchKeyword(const int& keyword)
    {
        Node* node = root;
        while (node != nullptr)
        {
            if (keyword == node->keyword)
            {
                // cout << "URLs for the keyword '" << keyword << endl;
                URL* ptr = node->urlptr;
                while (ptr != nullptr)
                {
                    cout << ptr->url << endl;
                    ptr = ptr->next;
                }
                cout << endl;
                return; // Exit the function once found
            }
            else if (keyword < node->keyword)
            {
                node = node->left;
            }
            else {
                node = node->right;
            }
        }
        cout << "Keyword  not found in the BST." << endl;
    }
    void display()
    {
        cout << "Contents in the BST:" << endl;
        display(root);
    }
    int calculatehashvalue(const string& word)
    {
        int sum = 0,i=1;
        for (char c : word)
        {
            sum += static_cast<int>(c)*i;
            i *= 10;
        }
        return sum;
    }
    void readdata(string& filename)
    {
        int i = 1, j = 2, k = 0;
        string line, url, keyword;
        ifstream obj(filename + ".txt");
        if (obj.is_open())
        {
            cout << "File Loaded successfully" << endl;
            while (getline(obj, line))
            {
                if (line.empty() || line[0] == ' ')
                {
                    continue;
                }
                if (i % 3 == 0)
                {
                    url = line;
                    i++;
                    //cout << url << endl;
                }
                if (i == 1)
                {
                    url = line;
                }
                else
                {
                    keyword = line;
                    istringstream iss(line);
                    string word;
                    while (iss >> word)
                    {
                        int asciisum = calculatehashvalue(word);
                        insert(asciisum, url);
                    }
                }
                i++; // Increment 'i' to switch between URL and Keyword

            }

        }
        else
            cout << "Error! opening file" << endl;
    }
    Node* findMin(Node* node)
    {
        while (node->left != nullptr)
        {
            node = node->left;
        }
        return node;
    }

    Node* deleteNode(Node* subroot, int keyword)
    {
        if (subroot == nullptr)
        {
            return subroot;
        }
        else if (keyword < subroot->keyword)
        {
            subroot->left = deleteNode(subroot->left, keyword);
        }
        else if (keyword > subroot->keyword)
        {
            subroot->right = deleteNode(subroot->right, keyword);
        }
        else
        {
            // Case 1: No child or only one child
            if (subroot->left == nullptr)
            {
                Node* temp = subroot->right;
                delete subroot;
                return temp;
            }
            else if (subroot->right == nullptr)
            {
                Node* temp = subroot->left;
                delete subroot;
                return temp;
            }
            Node* temp = findMin(subroot->right);
            subroot->keyword = temp->keyword;
            subroot->urlptr = temp->urlptr;

            subroot->right = deleteNode(subroot->right, temp->keyword);
        }
        return subroot;
    }
    void deleteKeyword(int keyword)
    {
        root = deleteNode(root, keyword);
    }
};

int main()
{
    BST bst;
    Node* root = bst.getRoot();
    string filename;
    cout << "Enter the filename: ";
    cin >> filename;
    bst.readdata(filename);
   // bst.display();
    string keywordserach;
    cout << "Enter keyword to search: ";
    cin >> keywordserach;
    int asciisum = bst.calculatehashvalue(keywordserach);
    bst.searchKeyword(asciisum);
    string dltkeyword;
    cout << "Enter keyword to delete from the tree:";
    cin >> dltkeyword;
    int val=bst.calculatehashvalue(dltkeyword);
    bst.deleteKeyword(val);
    cout << "Delete sucessfully" << endl;
    cout << "Enter keyword to search: ";
    cin >> keywordserach;
    int deletedvalue = bst.calculatehashvalue(keywordserach);
    bst.searchKeyword(deletedvalue);

    return 0;
}

