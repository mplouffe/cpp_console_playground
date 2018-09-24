// Example of multiple inheritence with a common base class
// Listing 14.5 from Learn C++ in 21 Days

#include <iostream>
using namespace std;

typedef int HANDS;
enum COLOR { Red, Green, Blue, Yellow, White, Black, Brown };

class Animal {
    public:
        Animal(int);
        virtual ~Animal() { cout << "Animal destructor...\n"; }
        virtual int GetAge() const { return itsAge; }
        virtual void SetAge(int age) { itsAge = age; }
    private:
        int itsAge;
};

Animal::Animal(int age):
    itsAge(age)
    {
        cout << "Animal constructor...\n";
    }

class Horse : public Animal {
    public:
        Horse(COLOR color, HANDS height, int age);
        virtual ~Horse() { cout << "Horse destructor...\n"; }
        virtual void Whinny() const { cout << "Whinny!...\n"; }
        virtual HANDS GetHeight() const { return itsHeight; }
        virtual COLOR GetColor() const { return itsColor; }
    protected:
        HANDS itsHeight;
        COLOR itsColor;
};

Horse::Horse(COLOR color, HANDS height, int age):
    Animal(age),
    itsColor(color),
    itsHeight(height)
    {
        cout << "Horse constructor...\n";
    }

class Bird : public Animal {
    public:
        Bird(COLOR color, bool migration, int age);
        virtual ~Bird() { cout << "Bird constructor...\n"; }
        virtual void Chirp() const { cout << "Chirp...\n"; }
        virtual void Fly() const { cout << "I can fly! I can fly!\n"; }
        virtual COLOR GetColor() const { return itsColor; }
        virtual bool GetMigration() const { return itsMigration; }
    protected:
        COLOR itsColor;
        bool itsMigration;
};

Bird::Bird(COLOR color, bool migrate, int age):
    Animal(age + 2),
    itsColor(color),
    itsMigration(migrate)
    {
        cout << "Bird constructor...\n";
    }

class Pegasus : public Horse, public Bird {
    public:
        Pegasus(COLOR color, HANDS height, bool migration, long believers, int age);
        virtual ~Pegasus() { cout << "Pegasus destructor...\n"; }
        void Chirp() const { Whinny(); }
        virtual long GetNumberBelivers() const { return itsNumberBelievers; }
        virtual COLOR GetColor() const { return Horse::itsColor; }
        virtual int GetAge() const { return Horse::GetAge(); }
    private:
        long itsNumberBelievers;
};

Pegasus::Pegasus(
    COLOR color,
    HANDS height,
    bool migration,
    long believers,
    int age):
    Horse(color, height, age),
    Bird(color, migration, age),
    itsNumberBelievers(believers)
    {
        cout << "Pegasus constructor...\n";
    }

int main() {
    Pegasus *pPeg = new Pegasus(Red, 5, true, 10, 2);
    int age = pPeg->GetAge();
    cout << "This pegasus is " << age << " years old!" << endl;
    int birdYears = pPeg->Bird::GetAge();           // manually calling the Bird inherited version of GetAge();
    cout << "This pegasus is " << birdYears << " years old in Bird Years!" << endl;
    delete pPeg;
    char response;
    std::cin >> response;
    return 0;
}
