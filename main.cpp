#include <bits/stdc++.h>
#include <windows.h>

using namespace std;

void loading();

const int ALPHABET_SIZE = 26;
// trie node
class TrieNode
{
public:
    TrieNode *children[ALPHABET_SIZE];

    // isEndOfWord is true if the node represents
    // end of a word
    bool isEndOfWord;

    TrieNode()
    {
        this->isEndOfWord = false;

        for (int i = 0; i < ALPHABET_SIZE; i++)
            this->children[i] = NULL;
    }
};

class Trie
{
    TrieNode *root;

public:
    Trie()
    {
        root = new TrieNode;
    }

    // If not present, inserts key into trie
    // If the key is prefix of trie node, just
    // marks leaf node
    void insert(string key)
    {
        TrieNode *pCrawl = root;

        for (int i = 0; i < key.length(); i++)
        {
            int index = key[i] - 'a';
            cout << "TEST " << index << " " << key[i] << endl;
            if (!pCrawl->children[index])
                pCrawl->children[index] = new TrieNode;
            pCrawl = pCrawl->children[index];
        }

        // mark last node as leaf
        pCrawl->isEndOfWord = true;
    }

    // Builds Trie for helping out spam word search
    void build(vector<string> arr)
    {
        //print(arr);
        for (auto ele : arr)
        {
            this->insert(ele);
        }
    }

    // Returns true if key presents in trie, else
    // false
    bool search(string key)
    {
        TrieNode *pCrawl = root;

        for (int i = 0; i < key.length(); i++)
        {
            int index = key[i] - 'a';
            if (!pCrawl->children[index])
                return false;

            pCrawl = pCrawl->children[index];
        }

        return (pCrawl != NULL && pCrawl->isEndOfWord);
    }

} Spam;

// Retrive spam words from database
vector<string> retrieve(string FileName = "SpamWords")
{

    // stores distinct words;
    vector<string> words;

    // Reading words from stored file
    ifstream spam_words;
    spam_words.open("Sources/" + FileName + ".txt");

    string line;

    while (getline(spam_words, line))
    {
        words.push_back(line);
    }

    return words;
}

//Utility function for debugging
void print(vector<string> arr)
{
    for (auto ele : arr)
    {
        cout << ele << " ";
    }
    cout << endl;
}

// Adding user specified spam words to stored database
void addSpamWords(string FileName, string Content)
{
    // transforms the word to lowercase for easier search operation
    transform(Content.begin(), Content.end(), Content.begin(), ::tolower);

    // Writing word to database
    ofstream spam_words;
    spam_words.open("Sources/" + FileName + ".txt", ios::app);
    spam_words << endl
               << Content;
    spam_words.close();
}

// Utility function to remove unessesary characters from words
string removeExtras(string word)
{
    // useless characters to remove from words
    vector<char> arr = {'.', ',', '!', '#', '&', '(', ')', '\'', '"', ':', ';',
                        '<', '>', '?', '/', '{', '}', '[', ']', '\\'};

    // string to store filtered word
    string filterdWord = "";

    for (int i = 0; i < word.length(); i++)
    {
        // flag insures only genuine characters are considered in current word
        bool flag = false;

        for (int j = 0; j < arr.size(); j++)
        {
            if (word[i] == arr[j])
            {
                flag = true;
                break;
            }
        }
        if (!flag)
            filterdWord.push_back(word[i]);
    }
    return filterdWord;
}

// Extract disinct words from given line
// Also, returns count of spam words in given line
pair<int, int> countSpamWords(string str)
{
    // total variable to store count of total words in given line
    int total = 0;

    // count variable to store count of spam words in given line
    int cnt = 0;

    // word variable to store word
    string word;

    // making a string stream
    stringstream iss(str);

    // Read and print each word.
    while (iss >> word)
    {
        word = removeExtras(word);
        total++;
        transform(word.begin(), word.end(), word.begin(), ::tolower);
        if (Spam.search(word))
            cnt++;
    }
    return {cnt, total};
}

// initialize the trie data structure
void initSpam()
{
    Spam.build(retrieve());
}

// main function to check spam words in given file
void spamChecker(string fileName)
{
    //Initialising data structures for checker to work
    initSpam();

    pair<long long, long long> totalSpams;

    ifstream file;
    file.open(fileName + ".txt");

    string line;

    while (getline(file, line))
    {
        pair<int, int> temp = countSpamWords(line);
        totalSpams.first += temp.first;
        totalSpams.second += temp.second;
    }

    cout << totalSpams.first << " out of " << totalSpams.second << " words" << endl;
}

int SpamFilter()
{
    int n;
    string word;
    cout << "Enter count of words to be entered : ";
    cin >> n;
    while (n--)
    {
        cin >> word;
        addSpamWords("SpamWords", word);
    }
    string name;
    cout << "Enter FileName of file to be check for spam : ";
    cin >> name;
    spamChecker(name);

    return 0;
}

void aboutspam() // This function contains all the theory related to spamchecker
{
    cout << " Spam emails are one of the most irritating things, and it eats up a lot of space, so to deal with that, we have a spam checker.Spam checker checks for some specific words in a file, which is considered spam when exceeding a certain number of repetitions in a file. The project checks for spam mails. There is a file where you can add the words/sentences which are or can be categorized as spam, the code basically search for these spam words in the content sent for checking, if the content contains those words, it is considered to be a spam, else given a clean chit. The above task is achieved using trie., it searches Trie is an efficient information reTrieval data structure. Using Trie, search complexities can be brought to optimal limit (key length). If we store keys in binary search tree, a well balanced BST will need time proportional to M * log N, where M is maximum string length and N is number of keys in tree. Using Trie, we can search the key in O(M) time."<<endl;
}

int spam() //This function contains a menu for all functions which we will use in spamchecker
{
    int spam;
    cout << "1.Add Spam words to database\n";
    cout << "2.To Check Spam\n";
    cout << "3.About Spamchecker\n";
    cout << "Enter your choice:-\t";
    cin >> spam;
    switch (spam)
    {
    case 1: //Case to add spam words into database
    {
        int n;
        string word;
        cout << "Enter count of words to be entered : ";
        cin >> n;
        while (n--)
        {
            cout << "\nEnter the word : ";
            cin >> word;
            loading();
            addSpamWords("SpamWords", word);
        }
        break;
    }
    case 2: //Case to check spam
    {
        string name;
        cout << "Enter filename of file to be check for spam : ";
        cin >> name;
        loading();
        spamChecker(name);

        break;
    }
    case 3: //Case to get information about spamchecker

        cout << "What is spamchecker?";
        loading();
        aboutspam();
        break;
    default:
        cout << "Wrong choice";
    }
    return 0;
}

void loading()
{

    for (int i = 0; i < 5; i++)
    {
        cout << "****";
        Sleep(1000);
    }
}
int main()
{
    spam();
    return 0;
}
