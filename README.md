# Spam-Checker
Spam emails are one of the most irritating things, and it eats up a lot of space, so to deal with that, we have a spam checker. Spam checker checks for some specific words in a file, which is considered spam when exceeding a certain number of repetitions in a file

The project checks for spam mails. There is a file where you can add the words/sentences which are
or can be categorized as spam, the code basically searches for these spam words in the content sent
for checking, if the content contains those words, it is considered to be a spam, else given a clean
chit

The above task is achieved using trie., it searches Trie is an efficient information retrieval data
structure. Using Trie, search complexities can be brought to optimal limit (key length). If we store
keys in binary search tree, a well-balanced BST will need time proportional to M * log N, where M
is maximum string length and N is number of keys in tree. Using Trie, we can search the key in
O(M) time.
