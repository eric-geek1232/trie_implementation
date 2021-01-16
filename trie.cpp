/*By Eric 13/01/2021  -Trie implementation- */
#include <iostream>

using namespace std; 

#define ALPHABET_SIZE (26) 
#define CONVERT_CHAR_TO_INDEX(caracter) (caracter - 'a') 

struct TrieNode 
{ 
	TrieNode *children[ALPHABET_SIZE];
	char caracter; 
	bool isWordEnd; 
}; 

class Trie{
	private:
		TrieNode *root;
		
		TrieNode *createNode(char caracter); 
		bool isLastNode(TrieNode* root); 
		void findSuggestions(TrieNode* root, string currentPrefix);
		
	public:
		Trie();
		void insert(string word);
		bool searchWord(string word);
		bool deleteWord(string word);
		void printAutoSuggestions(string keyWord);
			
};

Trie::Trie()
{ 
	root = createNode(' '); 	
}

TrieNode *Trie::createNode(char caracter) 
{ 
	TrieNode *newNode = new TrieNode(); 
	newNode->isWordEnd = false;
	newNode->caracter = caracter; 

	// Create dictionary a-z
	for (int i = 0; i < ALPHABET_SIZE; i++) {
		newNode->children[i] = NULL; 	
	}

	return newNode; 
} 

void Trie::insert(string word) 
{ 
	TrieNode *trie_aux = root; 

	for (int level = 0; level < word.length(); level++) {
		int index = CONVERT_CHAR_TO_INDEX(word[level]);  
		
		//If not present, inserts key into trie
		if (trie_aux->children[index] == NULL) {
			trie_aux->children[index] = createNode(word[level]); 	
		} 

		trie_aux = trie_aux->children[index]; 
	} 

	// mark last node as leaf 
	trie_aux->isWordEnd = true;
	
	cout<< "\n [info]-contact "<< word<<" saved\n"<< endl; 
} 

bool Trie::searchWord(string word) 
{
	TrieNode *trie_aux = root; 
	
	for (int level = 0; level < word.length(); level++) { 
		int index = CONVERT_CHAR_TO_INDEX(word[level]); 

		if (trie_aux->children[index] == NULL) return false;

		trie_aux = trie_aux->children[index]; 
	} 

	return (trie_aux != NULL && trie_aux->isWordEnd); 
} 

bool Trie::deleteWord(string word){
	TrieNode *trie_aux = root;
	
	for (int level = 0; level < word.length(); level++) { 
		int index = CONVERT_CHAR_TO_INDEX(word[level]); 

		if (trie_aux->children[index] == NULL) return false;
		
		trie_aux = trie_aux->children[index];
	} 
	
	if (trie_aux != NULL && trie_aux->isWordEnd) {
		// break word
		trie_aux->isWordEnd = false;
		
		return true;
	} 
	
	return false;
}

bool Trie::isLastNode(TrieNode	*node) 
{ 
	for (int i = 0; i < ALPHABET_SIZE; i++) {
		// node has a child 
		if (node->children[i] != NULL) return false;	
	} 
	
	// node has no children
	return true; 
} 
 
void Trie::findSuggestions(TrieNode	*node, string currentPrefix) 
{ 
	// suggestion found 
	if (node->isWordEnd) { 
		cout<< "\n "<< currentPrefix<< endl;
		return; 
	} 
	
	// end of tree 
	if (isLastNode(node)) {
		return; 	
	}
	
	 
	string prefix_aux = currentPrefix;
	
	for (int i = 0; i < ALPHABET_SIZE; i++) { 
		if (node->children[i] != NULL) { 
			// append current character to currentPrefix string
			currentPrefix += node->children[i]->caracter;
			
			// recursive over the rest to append more characters
			findSuggestions(node->children[i], currentPrefix);
			
			// Avoid impurities if there are more children in the current node
			currentPrefix = prefix_aux;
		} 
	} 
} 


void Trie::printAutoSuggestions(string keyWord) 
{ 
	TrieNode *trie_aux = root; 
	
	// find the node (of last level) with last character of given string. 
	for (int level = 0; level < keyWord.length(); level++) { 
		int index = CONVERT_CHAR_TO_INDEX(keyWord[level]); 

		if (trie_aux->children[index] == NULL) {
			cout<< "\n\n [Warning]-No word found with this prefix\n"<< endl;
			return;
		}
		
		trie_aux = trie_aux->children[index]; 
	} 
	
	// If prefix is present as a word 
	if (trie_aux->isWordEnd && isLastNode(trie_aux)) { 
		cout<< "\n "<< keyWord<< endl; 
		return; 
	} 
 
	if (!isLastNode(trie_aux)) {  
		findSuggestions(trie_aux, keyWord);
	} 
} 

int main() 
{ 
	Trie *trie = new Trie(); 
	int option;
	string word; 
	
	do {
		cout<< "\t Trie\n"<< endl;
		cout<< "\t.::MENU::.\n"<< endl;
		cout<< " [1] Insert word"<< endl;
		cout<< " [2] Suggestions"<< endl;
		cout<< " [3] Search Word"<< endl;
		cout<< " [4] Delete Word"<< endl;
		cout<< " [5] Exit"<< endl;
		cout<< "\n Choose: ";
		cin>>option;
		
		switch(option) {
			case 1:
				cout<< "\n\n Type a word: ";
				cin>> word;
				
				trie->insert(word);
				break;
				
			case 2:
				cout<< "\n\n Type something: ";
				cin>> word;
				
				trie->printAutoSuggestions(word);
				cout<< "\n"<< endl; 	
				break;
				
			case 3:
				cout<< "\n\n Type contact name: ";
				cin>> word;
				
				if (trie->searchWord(word)) {
					cout<< "\n\n [Info]-Result: " << word<< "\n"<< endl;
				} else {
					cout<< "\n\n [Warning]-No results \n"<< endl;
				}
				break;
				
			case 4:
				cout<< "\n\n Type contact name: ";
				cin>> word;
				
				if (trie->deleteWord(word)) {
					cout<< "\n\n [Info]-Result: " << word<< " removed\n"<< endl;
				} else {
					cout<< "\n\n [Warning]-No results \n"<< endl;
				}
				break;
				
			case 5:
				cout<< "\n\n\t**Big thanks for using this program**\n"<< endl;
				break;
				
			default:
				cout<< "\n\n\tWrong option... try again!\n"<< endl;
		}
		
		system("pause");
		system("cls");
	} while (option != 5);

	return 0; 
} 
