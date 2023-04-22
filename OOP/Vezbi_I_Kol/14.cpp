#include <iostream>
#include <cstring>

using namespace std;

enum Extension {
    txt, pdf, exe
};

class File {
private:
    char *name;
    char *owner;
    Extension ext;
    int size;

public:
//    File file(fileName, fileOwner, fileSize, (Extension) ext);


    File(char *name = "", char *owner = "", int size = 0, Extension ext = txt) {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
        this->owner = new char[strlen(owner) + 1];
        strcpy(this->owner, owner);
        this->ext = ext;
        this->size = size;
    }

    File(const File &f) {
        this->name = new char[strlen(f.name) + 1];
        strcpy(this->name, f.name);
        this->owner = new char[strlen(f.owner) + 1];
        strcpy(this->owner, f.owner);
        this->ext = f.ext;
        this->size = f.size;
    }

    File &operator=(const File &f) {
        if (this == &f) return *this;

        delete[] name;
        delete[] owner;

        this->name = new char[strlen(f.name) + 1];
        strcpy(this->name, f.name);
        this->owner = new char[strlen(f.owner) + 1];
        strcpy(this->owner, f.owner);
        this->ext = f.ext;
        this->size = f.size;
        return *this;
    }

    void print() {
        cout << "File name: " << name << ".";
        if (ext == 0) {
            cout << "pdf" << endl;
        } else if (ext == 1) {
            cout << "txt" << endl;
        } else if (ext == 2) {
            cout << "exe" << endl;
        }
        cout<<"File owner: "<<owner<<endl;
        cout<<"File size: "<<size<<endl;
    }

    bool equals(const File &that) const {
        if (strcmp(name, that.name) == 0 && strcmp(owner, that.owner) == 0 && ext == that.ext)
            return true;
        return false;
    }

    bool equalsType(const File &that) const {
        if (strcmp(name, that.name) == 0 && ext == that.ext)
            return true;
        return false;
    }

    ~File() {
        delete[]name;
        delete[]owner;
    }
};

class Folder {
private:
    char *name;
    File *files;
    int n;

public:

    Folder(const char *name = "") {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
        this->files = nullptr;
        this->n = 0;
    }

    Folder(const Folder &f) {
        this->name = new char[strlen(f.name) + 1];
        strcpy(this->name, f.name);
        this->n = f.n;
        this->files = new File[f.n];
        for (int i = 0; i < f.n; i++) {
            files[i] = f.files[i];
        }
    }


    Folder &operator=(const Folder &f) {
        if (this == &f) return *this;

        delete[] name;
        delete[] files;

        this->name = new char[strlen(f.name) + 1];
        strcpy(this->name, f.name);
        this->n = f.n;
        this->files = new File[f.n];
        for (int i = 0; i < f.n; i++) {
            files[i] = f.files[i];
        }
        return *this;
    }

    ~Folder() {
        delete[] name;
        delete[] files;
    }

    void print() {
        cout << "Folder name: " <<name << endl;
        for (int i = 0; i < n; i++) {
            files[i].print();
        }
    }

    void remove(const File &file) {
        for (int i = 0; i < n; i++) {
            if (file.equals(files[i])) {
                File *temp = new File[n - 1];
                int nc = 0;
                for (int j = 0; j < n; j++) {
                    if (!file.equals(files[j])) {
                        temp[nc++] = files[j];
                    }
                }
                n = nc;
                delete [] files;
                files = temp;
            }
        }
    }

    void add(const File &file) {
        File *temp = new File[n + 1];
        for (int i = 0; i < n; i++) {
            temp[i] = files[i];
        }

        temp[n++] = file;
        delete[] files;
        files = temp;
    }

};


int main() {
    char fileName[20];
    char fileOwner[20];
    int ext;
    int fileSize;

    int testCase;
    cin >> testCase;
    if (testCase == 1) {
        cout << "======= FILE CONSTRUCTORS AND = OPERATOR =======" << endl;
        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File created = File(fileName, fileOwner, fileSize, (Extension) ext);
        File copied = File(created);
        File assigned = created;

        cout << "======= CREATED =======" << endl;
        created.print();
        cout << endl;
        cout << "======= COPIED =======" << endl;
        copied.print();
        cout << endl;
        cout << "======= ASSIGNED =======" << endl;
        assigned.print();
    } else if (testCase == 2) {
        cout << "======= FILE EQUALS & EQUALS TYPE =======" << endl;
        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File first(fileName, fileOwner, fileSize, (Extension) ext);
        first.print();

        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File second(fileName, fileOwner, fileSize, (Extension) ext);
        second.print();

        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File third(fileName, fileOwner, fileSize, (Extension) ext);
        third.print();

        bool equals = first.equals(second);
        cout << "FIRST EQUALS SECOND: ";
        if (equals)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;

        equals = first.equals(third);
        cout << "FIRST EQUALS THIRD: ";
        if (equals)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;

        bool equalsType = first.equalsType(second);
        cout << "FIRST EQUALS TYPE SECOND: ";
        if (equalsType)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;

        equalsType = second.equals(third);
        cout << "SECOND EQUALS TYPE THIRD: ";
        if (equalsType)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;

    } else if (testCase == 3) {
        cout << "======= FOLDER CONSTRUCTOR =======" << endl;
        cin >> fileName;
        Folder folder(fileName);
        folder.print();

    } else if (testCase == 4) {
        cout << "======= ADD FILE IN FOLDER =======" << endl;
        char name[20];
        cin >> name;
        Folder folder(name);

        int iter;
        cin >> iter;

        while (iter > 0) {
            cin >> fileName;
            cin >> fileOwner;
            cin >> fileSize;
            cin >> ext;

            File file(fileName, fileOwner, fileSize, (Extension) ext);
            folder.add(file);
            iter--;
        }
        folder.print();
    } else {
        cout << "======= REMOVE FILE FROM FOLDER =======" << endl;
        char name[20];
        cin >> name;
        Folder folder(name);

        int iter;
        cin >> iter;

        while (iter > 0) {
            cin >> fileName;
            cin >> fileOwner;
            cin >> fileSize;
            cin >> ext;

            File file(fileName, fileOwner, fileSize, (Extension) ext);
            folder.add(file);
            iter--;
        }
        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File file(fileName, fileOwner, fileSize, (Extension) ext);
        folder.remove(file);
        folder.print();
    }
    return 0;
}