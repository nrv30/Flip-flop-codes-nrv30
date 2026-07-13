#include <array>
#include <assert.h>
#include <fstream>
#include <iostream>
#include <print>
#include <sstream>
#include <tuple>
#include <vector>

struct Node {
    Node* next;
    Node* prev;
    int data;
};

void print_patterns(std::array<std::vector<int>, 26>& patterns) {
    std::println("----------------------");
    
    for (auto& pat : patterns) {
        if (pat.size() > 0) {
            for (auto& num : pat) {
                std::print("{},", num);
            }
            std::println();
        }
    }
}

void printList(Node* head, int gen) {
    Node* temp = head;     
    std::print("Generation {}: ", gen);
    while (temp != NULL) {
        std::print("{}", (char)(temp->data + 65));
        temp = temp->next;
    }
}

size_t countList(Node* head) {
    size_t count = 0;
    Node* temp = head;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    return count;
}

Node* allocNode() {
    Node* temp = (Node*) malloc(sizeof(Node));
    assert(temp != NULL);
    return temp;
}

// returns the head and tail of a sub-list of children
std::tuple<Node*, Node*> getChildren(int letter, std::array<std::vector<int>, 26>& patterns) {
    Node* head = NULL;
    Node* temp = NULL;
    Node* tail = NULL;
    for (int i = 0; i < patterns[letter].size(); ++i){
        Node* child = allocNode();
        child->data = patterns[letter][i];
        
        // replace the parrent with the children
        if (head == NULL) {
            temp = child;
            child->prev = NULL;
            head = child;
            continue;
        }
        temp->next = child;
        child->prev = temp;
        temp = child;
        if (i == patterns[letter].size() - 1) {
            child->next = NULL;
            tail = child;
        }
    }
    
    return {head, tail};
}

Node* evolve(Node* head, std::array<std::vector<int>, 26>& patterns) {
    Node* temp = head;
    while (temp != NULL) {
        Node* next = temp->next;
        auto children = getChildren(temp->data, patterns);
        if (temp->prev == NULL) {
            head = std::get<0>(children);
        } else {
            std::get<0>(children)->prev = temp->prev;
            temp->prev->next = std::get<0>(children);
        }
        
        if (!temp->next == NULL) {
            std::get<1>(children)->next = temp->next;
            temp->next->prev = std::get<1>(children);
        }
        
        temp = next;
    }
    return head;
}

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::println("must pass input file as args\n");
        return EXIT_FAILURE;
    }
    
    std::ifstream input;
    input.open(argv[1]);
    if (!input)
    {
        std::println("Invalid file\n");
        return EXIT_FAILURE;
    }
    
    std::array<std::vector<int>, 26> patterns;
    
    std::string line;
    while (getline(input, line)) {
        int letter = -1;
        bool started = false;
        std::vector<int> pattern;
        for (size_t i = 0; i < line.size(); ++i) {
            if (!std::isspace(line[i])) {
                if (letter == -1) {
                    letter = line[i];
                    if (patterns[letter - 65].size() > 0) {
                        goto skip;
                    }
                } else {
                    pattern.push_back((int)line[i] - 65);
                }
            }
        }
        patterns[letter - 65] = pattern;
        skip:
    }
    
    Node* head = NULL;
    Node* first = allocNode();
    head = first;
    first->data = 0;
    first->prev = NULL;
    Node* second = allocNode();
    second->data = 1;
    second->next = NULL;
    first->next = second;
    second->prev = first;
    
    int gens = 3;
    printList(head, 0);
    std::println();
    for (int i = 1; i <= gens; ++i) {
        head = evolve(head, patterns);
        printList(head, i);
        std::println();
    }
    
    std::println("{}",countList(head));
   
    input.close();
    return EXIT_SUCCESS;
}