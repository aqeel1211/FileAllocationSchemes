#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;
const int T_S = 5;
const int NameSize = 25;
const int ExtSize = 5;
int random = 0;
char Disk[64];
class node {
public:
	node *next;
	string fileName;
	node() {
		fileName = "";
		next = NULL;
	}
	node(string k) {
		fileName = k;
		next = NULL;
	}
};
struct block
{
	short blockId;
	block *nextB;
};
struct fNode {
	char File[NameSize];
	char Extn[ExtSize];
	int start;
	node *end;
	short fSize; // no. of block;
	short *indexBlock;
	node *next;
	block *startl;
	block *End;
};
class HashTable {
public:
	node *ht[T_S];
	fNode fileNode[100];
	HashTable() {

		for (int i = 0; i < T_S; i++) {
			ht[i] = NULL;
		}
	}
	int HashFunc(string k) {
		int i = 0;
		int sum = 0;
		while (k[i] != NULL) {
			sum = sum + int(k[i]);
			i++;
		}
		return sum % T_S;
	}
	void insertWithContiguousAllocation(string fN, string extension, short size, int fileNumber) {
		fileNode[fileNumber].fSize = size;
		int n = fN.length();
		strcpy(fileNode[fileNumber].File, fN.c_str());
		n = extension.length();
		strcpy(fileNode[fileNumber].Extn, extension.c_str());

		int index = HashFunc(fN);
		node *temp = new node;
		temp->fileName = fN;
		temp->next = NULL;
		node *last = NULL;
		if (ht[index] == NULL) {
			ht[index] = temp;
			last = temp;
		}
		else {
			node *temp2 = ht[index];
			//node *last = ht[index];
			while (temp2->next != NULL) {
				temp2 = temp2->next;

			}
			temp2->next = temp;
		}
		fileNode[fileNumber].next = temp;
		//	placing in DISK
		
		int count = 0;
		fileNode[fileNumber].start = random;
		cout << "fileNode.start " << fileNode[fileNumber].start << endl;
		int j;
		for (int i = fileNode[fileNumber].start, j = 1; j <= fileNode[fileNumber].fSize; i++, j++) {
			if (Disk[i] == NULL) {
				count++;
			}
		}
		if (count >= fileNode[fileNumber].fSize) {


			while (size != 0) {
				contiguousAllocation(random);
				size--;
			}
		}
	}
	void displayHashTable() {
		for (int i = 0; i < T_S; i++) {
			if (ht[i] != NULL) {
				//	cout << ht[i]->fileName << endl;
				while (ht[i] != NULL) {

					cout << ht[i]->fileName << endl;
					ht[i] = ht[i]->next;
				}
			}
		}
	}
	void contiguousAllocation(int &index) {
		if (Disk[index] == NULL &&index <= 63) {
			Disk[index] = 'O';
			cout << index << endl;
		}
		else
		{
			if (index > 63) {
				index = 0;
			}
			while (Disk[index] != NULL) {
				index++;

			}
			Disk[index] = 'O';
			cout << index << endl;
		}
		index++;
	}
	void insertWithLinkedListAllocation(string fN, string extension, short size, int fileNumber) {
		fileNode[fileNumber].fSize = size;
		int n = fN.length();
		strcpy_s(fileNode[fileNumber].File, fN.c_str());
		n = extension.length();
		strcpy(fileNode[fileNumber].Extn, extension.c_str());

		int index = HashFunc(fN);
		node *temp = new node;
		temp->fileName = fN;
		temp->next = NULL;
		node *last = NULL;
		if (ht[index] == NULL) {
			ht[index] = temp;
			last = temp;
		}
		else {
			node *temp2 = ht[index];
			//node *last = ht[index];
			while (temp2->next != NULL) {
				temp2 = temp2->next;

			}
			temp2->next = temp;
		}
		fileNode[fileNumber].next = temp;
		
		block *temp01 = new block;
		
		temp01->nextB = NULL;
		fileNode[fileNumber].startl = temp01;
		//cout << "fileNode.start " << fileNode[fileNumber].startl->blockId << endl;
		//cout <<"Block ID = "<< fileNode[fileNumber].startl->blockId<<'\n';
		//fileNode[fileNumber].startl->nextB = NULL;
		//cout<<fileNode[fileNumber].startl->blockId << Endl;
		while (size != 0)
		{
			int i = (rand() % 63) + 0;
			temp01->blockId = i;
			linkedListAllocation(i);
			//cout << "i = " << i << '\n';
			block *last = new block;
			last->blockId = i;
			last->nextB = NULL;
			block *temp02 = new block;
			temp02 = fileNode[fileNumber].startl;
			if (fileNode[fileNumber].startl == NULL)
			{
				fileNode[fileNumber].startl = last;
				fileNode[fileNumber].End = last;
			}
			else
			{
				while (temp02->nextB != NULL)
				{
					temp02 = temp02->nextB;
				}
				temp02->nextB = last;
				fileNode[fileNumber].End = temp02;
				fileNode[fileNumber].End->blockId = temp02->blockId;
			}
			size--;
		}
		//output linklist
		block *temp03 = new block;
		temp03 = fileNode[fileNumber].startl;
		while (temp03 <= fileNode[fileNumber].End)
		{
			cout << temp03->blockId << "\n";
			temp03 = temp03->nextB;
		}
		//cout << "End = " << fileNode[fileNumber].End->blockId << "\n";
	}
	void linkedListAllocation(int &index)
	{
		if (Disk[index] == NULL && index <= 63)
		{
			//chk = true;
			Disk[index] = 'O';

		}
		else
		{
			//chk = false;
			if (index > 63) {
				index = 0;
			}
			while (Disk[index] != NULL) {
				index++;
			}
			Disk[index] = 'O';
		}
		index++;
	}
	void deleteFromLinkedList(char arr[])
	{
		bool compare = true;
		int i = 0;
		int fileNumber = 0;
		int fileNumberFound = 0;
		while (fileNumber < 10) {
			while (arr[i] != '\0' || fileNode[fileNumber].File[i] != '\0') {
				if (arr[i] != fileNode[fileNumber].File[i]) {
					compare = false;
					break;
				}
				compare = true;
				i++;
			}
			if (compare) {
				fileNumberFound = fileNumber;
				break;
			}
			i = 0;
			fileNumber++;
		}
		if (compare)
		{
			cout << "FileNumber = " << fileNumber << "\n";

			block *temp03 = new block;
			temp03 = fileNode[fileNumber].startl;
			cout << "Start = " << temp03->blockId << "\n";
			block *swap = new block;
			cout << "End of File = " << fileNode[fileNumber].End->blockId;
			while (temp03 <= fileNode[fileNumber].End)
			{
				int i = temp03->blockId;
				Disk[i] = 'E';
				temp03 = temp03->nextB;
			}
			int del = 0;
			while (del != NameSize)
			{
				fileNode[fileNumber].File[del] = '\0';
				del++;
			}
			cout << endl;
			cout << "File deleted " << endl;
		}
		else
		{
			cout << "File Does not exist " << endl;
		}
	}
	void displayDisk() {
		for (int i = 0; i < 64; i++) {
			cout << Disk[i] << " ";
		}
		cout << endl;
	}
	void deleteFromDisk(char arr[]) {
		bool compare = true;
		int i = 0;
		int fileNumber = 0;
		int fileNumberFound = 0;
		while (fileNumber < 10) {
			while (arr[i] != '\0' || fileNode[fileNumber].File[i] != '\0') {
				if (arr[i] != fileNode[fileNumber].File[i]) {
					compare = false;
					break;
				}
				compare = true;
				i++;
			}
			if (compare) {
				fileNumberFound = fileNumber;
				break;
			}
			i = 0;
			fileNumber++;
		}
		fileNumber = fileNode[fileNumberFound].fSize;
		if (compare) {
			while (fileNumber != 0) {
				if (Disk[fileNode[fileNumberFound].start] != NULL &&fileNode[fileNumberFound].start <= 63) {
					Disk[fileNode[fileNumberFound].start] = 'E';
					int del = 0;
					while (del != NameSize) {
						fileNode[fileNumberFound].File[del] = '\0';
						del++;
					}
					cout << fileNode[fileNumberFound].start << endl;
				}
				else
				{
					if (fileNode[fileNumberFound].start > 63) {
						fileNode[fileNumberFound].start = 0;
						Disk[fileNode[fileNumberFound].start] = 'E';
						int del = 0;
						while (del != NameSize) {
							fileNode[fileNumberFound].File[del] = '\0';
							del++;
						}
					}
					cout << fileNode[fileNumberFound].start << endl;
				}
				fileNode[fileNumberFound].start++;
				fileNumber--;
			}
			cout << "file deleted" << endl;
		}
		else {
			cout << " file doesnt exist " << endl;
		}
	}
	void searchFromDisk(char arr[]) {
		bool compare = true;
		int i = 0;
		int fileNumber = 0;

		while (fileNumber < 10) {
			while (arr[i] != '\0' || fileNode[fileNumber].File[i] != '\0') {
				if (arr[i] != fileNode[fileNumber].File[i]) {
					compare = false;
					break;
				}
				compare = true;
				i++;
			}
			if (compare) {

				break;
			}
			i = 0;
			fileNumber++;
		}
		if (compare) {
			cout << "found " << endl;
		}
		else {
			cout << "not found " << endl;
		}
	}
	void insertWithindexedAllocation(string fN, string extension, short size, int fileNumber) {
		fileNode[fileNumber].indexBlock = new short[size];
		fileNode[fileNumber].fSize = size;
		int n = fN.length();
		strcpy(fileNode[fileNumber].File, fN.c_str());
		n = extension.length();
		strcpy(fileNode[fileNumber].Extn, extension.c_str());
		int index = HashFunc(fN);
		node *temp = new node;
		temp->fileName = fN;
		temp->next = NULL;
		node *last = NULL;
		if (ht[index] == NULL) {
			ht[index] = temp;
			last = temp;
		}
		else {
			node *temp2 = ht[index];
			//node *last = ht[index];
			while (temp2->next != NULL) {
				temp2 = temp2->next;

			}
			temp2->next = temp;
		}
		int ind = 0;
		while (size != 0) {
			short random = (rand() % 63) + 0;
			cout << "random " << random << endl;

			if (Disk[random] == NULL &&random <= 63) {
				Disk[random] = 'O';
				fileNode[fileNumber].indexBlock[ind] = random;
			}
			else {
				while (Disk[random] != NULL &&random <= 63) {
					random = (rand() % 63) + 0;
				}

				Disk[random] = 'O';
				fileNode[fileNumber].indexBlock[ind] = random;
			}
			cout << "!" << fileNode[fileNumber].indexBlock[ind] << endl;
			ind++;

			size--;
		}

	}
	void deleteFromDisk_indexedAllocation(char arr[]) {
		bool compare = true;
		int i = 0;
		int fileNumber = 0;
		int fileNumberFound = 0;
		while (fileNumber < 10) {
			while (arr[i] != '\0' || fileNode[fileNumber].File[i] != '\0') {
				if (arr[i] != fileNode[fileNumber].File[i]) {
					compare = false;
					break;
				}
				compare = true;
				i++;
			}
			if (compare) {
				fileNumberFound = fileNumber;
				break;
			}
			i = 0;
			fileNumber++;
		}
		fileNumber = fileNode[fileNumberFound].fSize;
		short start = 0;
		if (compare) {
			while (fileNumber != 0) {
				if (fileNode[fileNumberFound].indexBlock[start] != NULL &&fileNode[fileNumberFound].indexBlock[start] <= 63) {
					Disk[fileNode[fileNumberFound].indexBlock[start]] = 'E';
					int del = 0;
					while (del != NameSize) {
						fileNode[fileNumberFound].File[del] = '\0';
						del++;
					}
					cout << fileNode[fileNumberFound].indexBlock[start] << endl;
				}

				start++;
				fileNumber--;
			}
			cout << "file deleted" << endl;
		}
		else {
			cout << " file doesnt exist " << endl;
		}
	}

};
void menu() {
	cout << "1.Insertion with contiguous allocation " << endl;
	cout << "2.Insertion with linked list allocation " << endl;
	cout << "3.Insertion with Indexed allocation " << endl;
	cout << "4.Search File " << endl;
	cout << "5.Delete File " << endl;
	cout << "6.Display Disk " << endl;
	cout << "7.Display HashTable " << endl;
}
int main() {
	HashTable hash;
	srand(time(0));
	int blocks;
	string str, extn;
	int fileNumber = 0;
	int fileNumber1 = 0;
	char choice = 'y';
	int choice2;
	while (choice == 'y') {
		menu();
		cout << "enter choice " << endl;
		cin >> choice2;
		if (choice2 == 1) {
			cout << "enter filename to insert " << endl;
			cin >> str;
			cout << "enter extension of filename " << endl;
			cin >> extn;
			cout << "enter number of blocks occupied by this file " << endl;
			cin >> blocks;
			hash.insertWithContiguousAllocation(str, extn, blocks, fileNumber);
			fileNumber++;
		}
		else if (choice2 == 2) {
			cout << "enter filename to insert " << endl;
			cin >> str;
			cout << "enter extension of filename " << endl;
			cin >> extn;
			cout << "enter number of blocks occupied by this file " << endl;
			cin >> blocks;
			hash.insertWithLinkedListAllocation(str, extn, blocks, fileNumber);
			fileNumber++;
		}
		else if (choice2 == 3) {
			cout << "enter filename to insert " << endl;
			cin >> str;
			cout << "enter extension of filename " << endl;
			cin >> extn;
			cout << "enter number of blocks occupied by this file " << endl;
			cin >> blocks;
			hash.insertWithindexedAllocation(str, extn, blocks, fileNumber);
			fileNumber++;
		}
		else if (choice2 == 4) {
			cout << "enter file name to search " << endl;
			char arr[NameSize];
			cin >> arr;
			hash.searchFromDisk(arr);
		}
		else if (choice2 == 5) {
			cout << "enter file name to delete " << endl;
			char arr[NameSize];
			int x;
			cin >> arr;
			cout << "1.Delete from Contiguous Allocation " << endl;
			cout << "2.Delete from Linked List Allocation " << endl;
			cout << "3.Delete from Indexed Allocation " << endl;
			cout << "enter choice " << endl;
			cin >> x;
			if (x == 1) {
				hash.deleteFromDisk(arr);
			}
			else if (x == 2) {
				hash.deleteFromLinkedList(arr);

			}
			else if (x == 3) {
				hash.deleteFromDisk_indexedAllocation(arr);
			}
		}
		else if (choice2 == 6) {
			hash.displayDisk();
		}
		else if (choice2 == 7) {
			hash.displayHashTable();
		}
		cout << "want to go again " << endl;
		cin >> choice;

	}
	system("pause");
	return 0;
}