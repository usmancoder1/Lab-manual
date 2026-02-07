#include <iostream>
#include <string>
using namespace std;

class Song {
public:
    int id;
    string title;
    string artist;
    int duration;

    Song* next;
    Song* prev;

    Song(int i, string t, string a, int d) {
        id = i;
        title = t;
        artist = a;
        duration = d;
        next = NULL;
        prev = NULL;
    }
};

class Playlist {
private:
    Song* head;
    Song* tail;
    Song* current;
    int totalSongs;

public:
    Playlist() {
        head = tail = current = NULL;
        totalSongs = 0;
    }

    void insertSong(int id, string title, string artist, int duration) {
        Song* newSong = new Song(id, title, artist, duration);

        if (head == NULL) {
            head = tail = current = newSong;
        } else {
            tail->next = newSong;
            newSong->prev = tail;
            tail = newSong;
        }

        totalSongs++;
        cout << "Song added.\n";
    }

    Song* searchSong(string key) {
        Song* temp = head;

        while (temp != NULL) {
            if (temp->title == key || temp->artist == key) {
                return temp;
            }
            temp = temp->next;
        }
        return NULL;
    }

    void modifySong(string key) {
        Song* found = searchSong(key);

        if (found == NULL) {
            cout << "Song not found.\n";
            return;
        }

        cout << "Enter new title: ";
        cin.ignore();
        getline(cin, found->title);

        cout << "Enter new artist: ";
        getline(cin, found->artist);

        cout << "Enter new duration (seconds): ";
        cin >> found->duration;

        cout << "Song updated.\n";
    }

    void displaySongs() {
        Song* temp = head;
        int totalDuration = 0;

        if (temp == NULL) {
            cout << "Playlist empty.\n";
            return;
        }

        cout << "\nPlaylist:\n";
        while (temp != NULL) {
            cout << "ID: " << temp->id << endl;
            cout << "Title: " << temp->title << endl;
            cout << "Artist: " << temp->artist << endl;
            cout << "Duration: " << temp->duration << " sec\n";
            cout << "------------------\n";
            totalDuration += temp->duration;
            temp = temp->next;
        }

        cout << "Total songs: " << totalSongs << endl;
        cout << "Total duration: " << totalDuration << " sec\n";
    }

    void playNext() {
        if (current == NULL) {
            cout << "No songs.\n";
            return;
        }

        if (current->next != NULL) {
            current = current->next;
            cout << "Now playing: " << current->title << endl;
        } else {
            cout << "Already at last song.\n";
        }
    }

    void playPrevious() {
        if (current == NULL) {
            cout << "No songs.\n";
            return;
        }

        if (current->prev != NULL) {
            current = current->prev;
            cout << "Now playing: " << current->title << endl;
        } else {
            cout << "Already at first song.\n";
        }
    }
};

int main() {
    Playlist p;
    int choice, id, duration;
    string title, artist, key;

    do {
        cout << "\n1.Insert Song";
        cout << "\n2.Search Song";
        cout << "\n3.Modify Song";
        cout << "\n4.Display Playlist";
        cout << "\n5.Play Next";
        cout << "\n6.Play Previous";
        cout << "\n0.Exit";
        cout << "\nEnter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter ID: ";
            cin >> id;
            cin.ignore();
            cout << "Enter title: ";
            getline(cin, title);
            cout << "Enter artist: ";
            getline(cin, artist);
            cout << "Enter duration (sec): ";
            cin >> duration;
            p.insertSong(id, title, artist, duration);
            break;

        case 2:
            cout << "Enter title or artist: ";
            cin.ignore();
            getline(cin, key);
            {
                Song* s = p.searchSong(key);
                if (s)
                    cout << "Found: " << s->title << " by " << s->artist << endl;
                else
                    cout << "Not found.\n";
            }
            break;

        case 3:
            cout << "Enter title or artist to modify: ";
            cin.ignore();
            getline(cin, key);
            p.modifySong(key);
            break;

        case 4:
            p.displaySongs();
            break;

        case 5:
            p.playNext();
            break;

        case 6:
            p.playPrevious();
            break;
        }

    } while (choice != 0);

    return 0;
}
