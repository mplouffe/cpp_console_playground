// Copy of the Week 2 Summation project from Learn C++ in 21 Days

#include <iostream>
using namespace std;

// PART
class Part {
    public:
        Part():itsPartNumber(1) {}
        Part(int partNumber):itsPartNumber(partNumber) {}
        virtual ~Part() {};
        int GetPartNumber() const { return itsPartNumber; }
        virtual void Display() const = 0;
    private:
        int itsPartNumber;
};

void Part::Display() const {
    cout << "\nPart Number: " << itsPartNumber << endl;
}

// CAR PART
class CarPart : public Part {
    public:
        CarPart():itsModelYear(94) {}
        CarPart(int year, int partNumber);
        virtual void Display() const {
            Part::Display();
            cout << "Model Year: " << itsModelYear << endl;
        }
    private:
        int itsModelYear;
};

CarPart::CarPart(int year, int partNumber):
    itsModelYear(year),
    Part(partNumber)
    {}

// AIRPLANE PART
class AirPlanePart : public Part {
    public:
        AirPlanePart(): itsEngineNumber(1) {}
        AirPlanePart(int engineNumber, int partNumber);
        virtual void Display() const {
            Part::Display();
            cout << "Engine No.: " << itsEngineNumber << endl;
        }
    private:
        int itsEngineNumber;
};

AirPlanePart::AirPlanePart(int engineNumber, int partNumber):
    itsEngineNumber(engineNumber),
    Part(partNumber)
    {}

// PART NODE
class PartNode {
    public:
        PartNode (Part*);
        ~PartNode();
        void SetNext(PartNode * node) { itsNext = node; }
        PartNode * GetNext() const;
        Part * GetPart() const;
    private:
        Part *itsPart;
        PartNode * itsNext;
};

PartNode::PartNode(Part* pPart):
    itsPart(pPart),
    itsNext(0)
    {}

PartNode::~PartNode() {
    delete itsPart;
    itsPart = 0;
    delete itsNext;
    itsNext = 0;
}

PartNode * PartNode::GetNext() const {
    return itsNext;
}

Part * PartNode::GetPart() const {
    if (itsPart) {
        return itsPart;
    } else {
        return NULL;
    }
}

// PARTS LIST
class PartsList {
    public:
        PartsList();
        ~PartsList();
        // needs copy constructor and operator equals
        Part * Find(int & position, int partNumber) const;
        int GetCount() const { return itsCount; }
        Part * GetFirst() const;
        void Insert(Part *);
        void Iterate() const;
        Part * operator[](int) const;
    private:
        PartNode * pHead;
        int itsCount;
};

PartsList::PartsList():
    pHead(0),
    itsCount(0)
    {}

PartsList::~PartsList() {
    delete pHead;
}

Part * PartsList::GetFirst() const {
    if (pHead) {
        return pHead->GetPart();
    } else {
        return NULL;
    }
}

Part * PartsList::operator[](int offset) const {
    PartNode * pNode = pHead;

    if(!pHead) {
        return NULL;
    }

    if (offset > itsCount) {
        return NULL;
    }

    for (int i = 0; i<offset; i++){
        pNode = pNode->GetNext();
    }

    return pNode->GetPart();
}

Part * PartsList::Find(int & position, int partNumber) const {
    PartNode * pNode = 0;
    for (pNode = pHead, position = 0; pNode != NULL; pNode = pNode->GetNext(), position++) {
        if (pNode->GetPart()->GetPartNumber() == partNumber) {
            break;
        }
    }
    if (pNode == NULL) {
        return NULL;
    } else {
        return pNode->GetPart();
    }
}

void PartsList::Iterate() const {
    if (!pHead) {
        return;
    }
    PartNode * pNode = pHead;
    do {
        pNode->GetPart()->Display();
    } while (pNode = pNode->GetNext());
}

void PartsList::Insert(Part * pPart){
    PartNode * pNode = new PartNode(pPart);
    PartNode * pCurrent = pHead;
    PartNode * pNext = 0;

    int newPartNumber = pPart->GetPartNumber();
    int next = 0;
    itsCount++;

    if (!pHead) {
        pHead = pNode;
        return;
    }

    if (pHead->GetPart()->GetPartNumber() > newPartNumber) {
        pNode->SetNext(pHead);
        pHead = pNode;
        return;
    }

    while(true) {
        if (!pCurrent->GetNext()) {
            pCurrent->SetNext(pNode);
            return;
        }

        pNext = pCurrent->GetNext();
        next = pNext->GetPart()->GetPartNumber();
        if (next > newPartNumber) {
            pCurrent->SetNext(pNode);
            pNode->SetNext(pNext);
            return;
        }
        pCurrent = pNext;
    }
}

int main() {
    PartsList pl;

    Part * pPart = 0;
    int partNumber;
    int value;
    int choice = 99;

    while (choice != 0) {
        cout << "(0)Quit (1)Car (2)Plane: ";
        cin >> choice;

        if (choice != 0) {
            cout << "New Part Number: ";
            cin >> partNumber;

            if (choice == 1) {
                cout << "Model Year: ";
                cin >> value;
                pPart = new CarPart(value, partNumber);
            } else if (choice == 2) {
                cout << "Engine Number: ";
                cin >> value;
                pPart = new AirPlanePart(value, partNumber);
            }

            pl.Insert(pPart);
        }
    }
    pl.Iterate();
    char response;
    std::cin >> response;
    return 0;
}