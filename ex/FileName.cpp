#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Participant {
protected:
    string name;
    int runLimit;
    int jumpLimit;
public:
    string Getname() {
        return name;
    }

    Participant(string name, int runLimit, int jumpLimit)
        : name(name), runLimit(runLimit), jumpLimit(jumpLimit) {}

    virtual void run(int distance) {
        if (distance <= runLimit) {
            cout << "Участник " << name << " пробежал " << distance << " метров\n";
        } 
        else {
            cout << "Участник " << name << " не смог пробежать " << distance << " метров Пройдено " << runLimit << " метров\n";
            throw runtime_error("Участник выбыл из участия");
        }
    }

    virtual void jump(int height) {
        if (height <= jumpLimit) {
            cout << "Участник " << name << " перепрыгнул " << height << " метров\n";
        } 
        else {
            cout << "Участник " << name << " не смог перепрыгнуть " << height << " метров Пройдено " << jumpLimit << " метров\n";
            throw runtime_error("Участник выбыл из участия");
        }
    }

    virtual ~Participant() = default;
};

class Human : public Participant {
public:
    Human(string name) : Participant(name, 5000, 2) {}
};

class Cat : public Participant {
public:
    Cat(string name) : Participant(name, 1000, 3) {}
};

class Robot : public Participant {
public:
    Robot(string name) : Participant(name, 10000, 1) {}
};

class Obstacle {
public:
    virtual void overcome(Participant* participant) = 0;
    virtual ~Obstacle() = default;
};

class RunningTrack : public Obstacle {
    int distance;
public:
    RunningTrack(int distance) : distance(distance) {}

    void overcome(Participant* participant) override {
        try {
            participant->run(distance);
        } catch (runtime_error&) {
            throw;
        }
    }
};

class Wall : public Obstacle {
    int height;
public:
    Wall(int height) : height(height) {}

    void overcome(Participant* participant) override {
        try {
            participant->jump(height);
        } catch (runtime_error&) {
            throw;
        }
    }
};

int main() {
    setlocale(0, "ru");

    vector<Participant*> participants = {
        new Human("Александр"),
        new Cat("Мурзик"),
        new Robot("Бот")
    };

    vector<Obstacle*> obstacles = {
        new RunningTrack(3000),
        new Wall(2),
        new RunningTrack(7000),
        new Wall(1)
    };

    for (Participant* participant : participants) {
        cout << "=== Участник: " << participant->Getname() << " ===\n";
        try {
            for (Obstacle* obstacle : obstacles) {
                obstacle->overcome(participant);
            }
        } catch (runtime_error&) {
            cout << participant->Getname() << " выбыл из соревнования\n";
        }
    }

    for (Participant* participant : participants) {
        delete participant;
    }

    for (Obstacle* obstacle : obstacles) {
        delete obstacle;
    }
}