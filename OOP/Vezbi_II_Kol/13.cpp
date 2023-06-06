#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

class Image {
protected:
    char *name;
    char user[50];
    int x, y;
public:
    Image(const char *name = "untitled", const char *user = "unknown", int x = 800, int y = 800) {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
        strcpy(this->user, user);
        this->x = x;
        this->y = y;
    }

    Image(const Image &i) {
        this->name = new char[strlen(i.name) + 1];
        strcpy(this->name, i.name);
        strcpy(this->user, i.user);
        this->x = i.x;
        this->y = i.y;
    }

    Image &operator=(const Image &i) {
        if (this == &i) return *this;
        delete[] name;
        this->name = new char[strlen(i.name) + 1];
        strcpy(this->name, i.name);
        strcpy(this->user, i.user);
        this->x = i.x;
        this->y = i.y;
        return *this;
    }

    virtual int fileSize() {
        return x * y * 3;
    }

    ~Image() {
        delete[] name;
    }

    friend ostream &operator<<(ostream &os, Image &i) {
        os << i.name << " " << i.user << " " << i.fileSize() << endl;
    }

    bool operator>(Image &i) {
        return (fileSize() < i.fileSize());
    }
};

class TransparentImage : public Image {
private:
    bool transparency;
public:
    TransparentImage(const char *name = "untitled", const char *user = "unknown", int x = 800, int y = 800,
                     bool transparency = true)
            : Image(name, user, x, y) {
        this->transparency = transparency;
    }

    TransparentImage(const TransparentImage &ti)
            : Image(ti) {
        this->transparency = ti.transparency;
    }

    TransparentImage &operator=(const TransparentImage &ti) {
        if (this == &ti) return *this;
        delete[] name;
        this->name = new char[strlen(ti.name) + 1];
        strcpy(this->name, ti.name);
        strcpy(this->user, ti.user);
        this->x = ti.x;
        this->y = ti.y;
        this->transparency = ti.transparency;
        return *this;
    }

    int fileSize() override {
        if (transparency) {
            return x * y * 4;
        } else {
            return (x * y + (x * y) / 8);
        }
    }

    friend ostream &operator<<(ostream &os, TransparentImage &i) {
        os << i.name << " " << i.user << " " << i.fileSize() << endl;
    }

};

class Folder {
private:
    char fname[255];
    char fuser[50];
    Image **sliki;
    int n;
public:
    Folder(const char *fname = "", const char *fuser = "unknown", Image **sliki = 0, int n = 0) {
        strcpy(this->fname, fname);
        strcpy(this->fuser, fuser);
        this->n = n;
        this->sliki = new Image *[n];
        for (int i = 0; i < n; i++) {
            this->sliki[i] = sliki[i];
        }
    }

    Folder(const Folder &f) {
        strcpy(this->fname, f.fname);
        strcpy(this->fuser, f.fuser);
        this->n = f.n;
        this->sliki = new Image *[f.n];
        for (int i = 0; i < f.n; i++) {
            this->sliki[i] = f.sliki[i];
        }
    }

    Folder &operator=(const Folder &f) {
        if (this == &f) return *this;
        strcpy(this->fname, f.fname);
        strcpy(this->fuser, f.fuser);
        this->n = f.n;
        delete[] sliki;
        this->sliki = new Image *[f.n];
        for (int i = 0; i < f.n; i++) {
            this->sliki[i] = f.sliki[i];
        }
    }

    ~Folder() {
        delete[] sliki;
    }

    Folder &operator+=(Image &i) {
        Image **temp = new Image *[n + 1];
        for (int i = 0; i < n; i++) {
            temp[i] = sliki[i];
        }
        temp[n++] = &i;
        delete[] sliki;
        sliki = temp;
        return *this;
    }

    int folderSize() {
        int retval = 0;
        for (int i = 0; i < n; i++) {
            retval += sliki[i]->fileSize();
        }
        return retval;
    }

    Image *getMaxFile() {
        Image *max = sliki[0]; // proverka
        for (int i = 1; i < n; i++) {
            if (sliki[i]->fileSize() >  max->fileSize()) {
                max = sliki[i];
            }
        }
        return max;
    }

    Image *operator[](int i){
        if (i >=n) return NULL;
        return sliki[i];
    }

    friend ostream &operator<<(ostream &os, Folder &f)
    {
        os << (f.fname) << " "<< (f.fuser)<<endl;
        os << "--" << endl;
        for (int i = 0; i<f.n; i++)
        {
            os << *f.sliki[i];
        }
        os << "--" << endl;
        os << "Folder size: "<< f.folderSize() <<endl;
        return os;
    }
};

Folder max_folder_size(Folder *niza, int n)
{
    Folder max = niza[0];
    for (int i = 1; i<n; i++)
    {
        if (max.folderSize() < niza[i].folderSize())
        {
            max = niza[i];
        }
    }
    return max;
}

int main() {

    int tc; // Test Case

    char name[255];
    char user_name[51];
    int w, h;
    bool tl;

    cin >> tc;

    if (tc == 1) {
        // Testing constructor(s) & operator << for class File

        cin >> name;
        cin >> user_name;
        cin >> w;
        cin >> h;


        Image f1;

        cout << f1;

        Image f2(name);
        cout << f2;

        Image f3(name, user_name);
        cout << f3;

        Image f4(name, user_name, w, h);
        cout << f4;
    } else if (tc == 2) {
        // Testing constructor(s) & operator << for class TextFile
        cin >> name;
        cin >> user_name;
        cin >> w >> h;
        cin >> tl;

        TransparentImage tf1;
        cout << tf1;

        TransparentImage tf4(name, user_name, w, h, tl);
        cout << tf4;
    } else if (tc == 3) {
        // Testing constructor(s) & operator << for class Folder
        cin >> name;
        cin >> user_name;

        Folder f3(name, user_name);
        cout << f3;
    } else if (tc == 4) {
        // Adding files to folder
        cin >> name;
        cin >> user_name;

        Folder dir(name, user_name);

        Image *f;
        TransparentImage *tf;

        int sub, fileType;

        while (1) {
            cin >> sub; // Should we add subfiles to this folder
            if (!sub) break;

            cin >> fileType;
            if (fileType == 1) { // Reading File
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                f = new Image(name, user_name, w, h);
                dir += *f;
            } else if (fileType == 2) {
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                cin >> tl;
                tf = new TransparentImage(name, user_name, w, h, tl);
                dir += *tf;
            }
        }
        cout << dir;
    } else if (tc == 5) {
        // Testing getMaxFile for folder

        cin >> name;
        cin >> user_name;

        Folder dir(name, user_name);

        Image *f;
        TransparentImage *tf;

        int sub, fileType;

        while (1) {
            cin >> sub; // Should we add subfiles to this folder
            if (!sub) break;

            cin >> fileType;
            if (fileType == 1) { // Reading File
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                f = new Image(name, user_name, w, h);
                dir += *f;
            } else if (fileType == 2) {
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                cin >> tl;
                tf = new TransparentImage(name, user_name, w, h, tl);
                dir += *tf;
            }
        }
        cout << *(dir.getMaxFile());
    } else if (tc == 6) {
        // Testing operator [] for folder

        cin >> name;
        cin >> user_name;

        Folder dir(name, user_name);

        Image *f;
        TransparentImage *tf;

        int sub, fileType;

        while (1) {
            cin >> sub; // Should we add subfiles to this folder
            if (!sub) break;

            cin >> fileType;
            if (fileType == 1) { // Reading File
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                f = new Image(name, user_name, w, h);
                dir += *f;
            } else if (fileType == 2) {
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                cin >> tl;
                tf = new TransparentImage(name, user_name, w, h, tl);
                dir += *tf;
            }
        }

        cin >> sub; // Reading index of specific file
        cout << *dir[sub];
    } else if (tc == 7) {
        // Testing function max_folder_size
        int folders_num;

        Folder dir_list[3];

        Folder dir;
        cin >> folders_num;

        for (int i = 0; i < folders_num; ++i) {
            cin >> name;
            cin >> user_name;
            dir = Folder(name, user_name);


            Image *f;
            TransparentImage *tf;

            int sub, fileType;

            while (1) {
                cin >> sub; // Should we add subfiles to this folder
                if (!sub) break;

                cin >> fileType;
                if (fileType == 1) { // Reading File
                    cin >> name;
                    cin >> user_name;
                    cin >> w >> h;
                    f = new Image(name, user_name, w, h);
                    dir += *f;
                } else if (fileType == 2) {
                    cin >> name;
                    cin >> user_name;
                    cin >> w >> h;
                    cin >> tl;
                    tf = new TransparentImage(name, user_name, w, h, tl);
                    dir += *tf;
                }
            }
            dir_list[i] = dir;
        }

        Folder maxi = max_folder_size(dir_list, folders_num);
        cout << maxi;
    }
    return 0;
};
