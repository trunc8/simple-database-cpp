#include <iostream>
#include <list>
#include <vector>
#include <fstream>
using namespace std;

int main() {
    cout << "---------Start of program----------\n\n\n";
    
    int elem, insert_index, erase_index, list_index;
    list<int>::iterator it;
    ofstream out_file;
    ifstream in_file;
    string filename = "list_contents.bin";

    list<int> numbers;
    numbers.push_back(1);
    numbers.push_back(2);
    numbers.push_back(3);

    cout << "Initial list:" << endl;
    for (it=numbers.begin(); it!=numbers.end(); it++) {
        cout << *it << " ";
    }
    cout << endl;

    int choice=-1;
    while (choice!=0) {
        cout << "\n--------New turn---------\n"
            "CHOICES\n"
            "0: Exit\n"
            "1: Push back to list\n"
            "2: Push front to list\n"
            "3: Insert to list\n"
            "4: Erase from list\n"
            "5: Save list\n"
            "6: Load list\n"
            "Any other integer views the list\n\n";
        cout << "Please enter an integer choice: ";
        cin >> choice;
        cout << "\n--------Output---------\n";

        

        switch (choice) {
        case 1:
            cout << "Please enter element to push back: ";
            cin >> elem;
            numbers.push_back(elem);
            break;

        case 2:
            cout << "Please enter element to push front: ";
            cin >> elem;
            numbers.push_front(elem);
            break;

        case 3:
            cout << "Please enter index to insert: ";
            cin >> insert_index;
            
            cout << "Please enter element to insert: ";
            cin >> elem;
            
            it=numbers.begin();
            list_index = 0;
            while (it!=numbers.end()) {
                if (list_index==insert_index) {
                    numbers.insert(it, elem);
                    break;
                }
                list_index++;
                it++;
            }
            break;

        case 4:
            cout << "Please enter index to erase: ";
            cin >> erase_index;
            
            it=numbers.begin();
            list_index=0;
            while (it!=numbers.end()) {
                if (list_index==erase_index) {
                    numbers.erase(it);
                    break;
                }
                list_index++;
                it++;
            }
            break;

        case 5:
            cout << "Saving list to " + filename << endl;
            out_file.open(filename, ios::binary);
            if (!out_file.is_open()) {
                cout << "Could not open " + filename << endl;
                continue;
            }
            else {
                int list_size = numbers.size();
                int list_content[list_size];
                
                it=numbers.begin();
                list_index=0;
                while (it!=numbers.end()) {
                    list_content[list_index] = *it;
                    list_index++;
                    it++;
                }

                out_file.write(reinterpret_cast<char *>(&list_size), sizeof(int));
                out_file.write(reinterpret_cast<char *>(&list_content), sizeof(list_content));
                
                out_file.close();
                
                cout << "Saved!\n\n";
            }
            break;
        
        case 6:
            cout << "Loading list from " + filename << endl;
            in_file.open(filename, ios::binary);
            if (!in_file.is_open()) {
                cout << "Could not open " + filename << endl;
                continue;
            }
            else {
                int list_size;
                in_file.read(reinterpret_cast<char *>(&list_size), sizeof(int));

                int list_content[list_size];
                in_file.read(reinterpret_cast<char *>(&list_content), sizeof(list_content));

                in_file.close();

                // Updating list with read list
                numbers.clear();
                for (int i=0; i<list_size; i++) {
                    numbers.push_back(list_content[i]);
                }

                cout << "Loaded!\n\n";
            }
            break;

        default:
            break;

        }
        
        cout << "Current list:" << endl;
        for (it=numbers.begin(); it!=numbers.end(); it++) {
            cout << *it << " ";
        }
        cout << endl;

        
    }

    cout << "\n\n---------End of program----------\n";

    return 0;
}
