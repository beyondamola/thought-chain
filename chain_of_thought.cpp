#include <iostream>
#include <fstream>
#include <ctime>
#include <string>

using namespace std;

class Node{
private:
    string text = "";
    Node* next = nullptr;
public:
    Node(string text, Node* next = nullptr){this -> text = text; this -> next = next;}
    Node(){};
    Node* getNext(){return next;}
    void setNext(Node* newNode){this -> next = newNode;}
    string getData(){return text;}
    void setData(string text){this -> text = text;}
};

class JournalManager{
private:
int entry_count = 0;
Node* head = nullptr;
Node* tail = nullptr;
Node* trash_head = nullptr;
Node* trash_tail = nullptr;
string save_file = "chain_of_thought.txt"; // haha.. get it?
string trash_file = "broken_links.txt";

protected:
    pair<Node*, Node*> load(string file_name){ // prints out all entries from a file by default into a lined_list
        ifstream file(file_name);
        string line;
        Node* target_head = nullptr;
        Node* target_tail = nullptr;
        if (!file.is_open()){cerr << "Failed to open file...\n"; return {nullptr, nullptr};}
        
        while(getline(file,line)){
            ///     {------ ENTRY ------}   <---- Our delimitar [or our searlizer string]
            if (line.find("------ ENTRY ------") != string::npos || line.empty()){continue;}

            Node* newNode = new Node(line);
            if(!target_head){target_head = newNode; target_tail = target_head;} // if head doesn't point to a node yet, set our FIRST node as head
            else {target_tail->setNext(newNode); target_tail = newNode;} // for all other nodes, let our current tail point to the new node and set itself as the new tail...
        }

        file.close();
        return {target_head, target_tail};
    }

    string entry_UI(){
        cout << "\nHow are we feeling today?: \n";
        string entrytext = "";
        getline(cin, entrytext);
        time_t now = time(0);
        char* live_time = ctime(&now); // get and log the current time the new entry was made
        entrytext += ("\t\t\t" + string(live_time)); // add that to the tailend of our entry...
        return entrytext;
    }
public:
    JournalManager(){file_load(false); file_load();}
    bool all_entries(){ // prints out all entries 
        Node* current = head;
        // error check
        if(current == nullptr || current->getData().empty()) {cerr << "No entries to post... {NO HEAD ENTRY}\n"; return false;}
        while (current != nullptr){
            Node* next = current->getNext();
            cout << "\n" << current->getData() << "\n";
            if (next != nullptr){
            current = next;
            }else {break;}
        }
    return true;
    }

    bool save_entries(bool type = true){ // prints out all entries {wipes the file clean before saving all entries...}
        ofstream file;
        Node* current = head;
        if(type) {file.open(save_file);} else {file.open(trash_file); current = trash_head;}
        int count = 0;

        // error check..
        if(!file.is_open()){ // error check..
            std::cerr << "\nFailed to open file...\n" << save_file << endl;
            return false;
        }

        // traverse through the linked list and save the text data while leaving a searalizer above every entry
        if(file.is_open()){ 
            while (current != nullptr){
                count++;
                file << "------ ENTRY ------\t\t(" << count << ")\n";
                file <<  current->getData() << "\n\n";
                current = current->getNext();
            }
            file.close();
        }
    return true;
    }


    Node* file_load(bool type = true){if(type){auto [head, tail] = load(save_file); this -> head = head; this-> tail = tail; return head;}else{auto [trash_head, trash_tail] = load(trash_file); this-> trash_head = trash_head; this -> trash_tail = trash_tail; return trash_head;}}

    bool new_entry(){ // adds a new entry/node into the linked_list in memory.... {DOES NOT SAVE}
        Node* current = head;
        if(head == nullptr) {head = new Node(entry_UI());} // if head does no exist, make a node and call it head...
        else if (head->getData().empty()) {head->setData(entry_UI());} // if head is made but unused, fill head..
        else {
            while(current->getNext() != nullptr){current = current->getNext();} // traverse to the tail node 
            current->setNext(new Node(entry_UI())); // add a node at the tail and input our entry...
        }
    entry_count++;
    return true;
    }

    void add_trash(string text){
        if (trash_head == nullptr){trash_head = new Node(text); trash_tail = trash_head;}
        else if (trash_tail->getNext() == nullptr){trash_tail->setNext(new Node(text));}
        else{while (trash_tail->getNext() != nullptr){trash_tail = trash_tail->getNext();}
        trash_tail->setNext(new Node(text));}
    }

    
    // BIG ERROR; WE NEED TO PARSE IN THE HEAD AND TAIL NODES AS ADDRESSES FOR US TO HAVE A DYNAMIC HANDELER --- MUST FIX
    bool delete_entry(int entry_num){
        entry_count = get_count(head); // update the entry num for the real nodes...
        Node* current = head;
        Node* next = nullptr;
        int count = 1;
        if (entry_num > entry_count || entry_num <= 0){
            cerr << "\nInvalid Entry {entry num is out of bounds}\n";
            return false;
        }
        
        if(current == nullptr){cerr << "\nEMPTY JOURNAL\n"; return false;} // check if our head node is null.. {ERROR CHECK}
        else if (entry_num == 1 && current != nullptr){
            next = head;
            add_trash(head->getData());
            head = head->getNext();
            delete next;
            return true;
            }
        else{
            while(current != nullptr){
            next = current->getNext(); 
            count++;
                if(count == entry_num){
                    add_trash(next->getData());
                    current->setNext(next->getNext());
                    delete next;
                    return true;
                }else{current = next;}
            }
        }
    }


    int get_count(Node*& target_head){
        Node* head = target_head;
        int count = 0;
        if(head == nullptr){cerr << "\nRECIEVED EMPTY HEAD NODE... {GET COUNT FAILED}\n"; return 0;}
        else{
            while(head != nullptr){
                count++;
                head = head->getNext();
            }
        }
        return count;
    }

    void cleanup(){ // GOTTA REMEMEMBER TO CALL AT THE END OF THE PROGRAM TO WIPE THE NODES
        Node* current = head;
        Node* next = nullptr;
        while(current != nullptr){
            next = current->getNext();
            delete current;
            current = next;
        }
        current = trash_head;
        while(current != nullptr){
            next = current->getNext();
            delete current;
            current = next;
        }
    }
};

int main(){
    // now we just gotta build the damn UI components...
    JournalManager test; // autoloads both SAVE and TRASH Linked_lists
    test.new_entry();
    test.all_entries();
    test.save_entries();
    test.cleanup();
}