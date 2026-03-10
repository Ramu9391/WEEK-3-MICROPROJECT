#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct song {
    char name[50];
    char artist[50];
    struct song *next;
} Song;

Song *last = NULL;
Song *current = NULL;

/* create new song node */
Song* createSong(char name[], char artist[]) {
    Song *n = (Song*)malloc(sizeof(Song));
    strcpy(n->name, name);
    strcpy(n->artist, artist);
    n->next = NULL;
    return n;
}

/* add song */
void addSong() {
    char name[50], artist[50];

    printf("Enter Song Name (no spaces): ");
    scanf("%s", name);
    printf("Enter Artist Name (no spaces): ");
    scanf("%s", artist);

    Song *n = createSong(name, artist);

    if (last == NULL) {
        last = n;
        last->next = last;
        current = last;
    } else {
        n->next = last->next;
        last->next = n;
        last = n;
    }

    printf("Song added successfully!\n");
}

/* display playlist */
void displayPlaylist() {
    if (last == NULL) {
        printf("Playlist empty\n");
        return;
    }

    Song *temp = last->next;
    int i = 1;

    printf("\n--- Music Playlist ---\n");
    do {
        printf("%d. %s - %s\n", i++, temp->name, temp->artist);
        temp = temp->next;
    } while (temp != last->next);
}

/* search song */
void searchSong() {
    if (last == NULL) {
        printf("Playlist empty\n");
        return;
    }

    char key[50];
    printf("Enter song name: ");
    scanf("%s", key);

    Song *temp = last->next;

    do {
        if (strcmp(temp->name, key) == 0) {
            printf("Song found: %s - %s\n",
                   temp->name, temp->artist);
            return;
        }
        temp = temp->next;
    } while (temp != last->next);

    printf("Song not found\n");
}

/* delete song */
void deleteSong() {
    if (last == NULL) {
        printf("Playlist empty\n");
        return;
    }

    char key[50];
    printf("Enter song name to delete: ");
    scanf("%s", key);

    Song *curr = last->next;
    Song *prev = last;

    do {
        if (strcmp(curr->name, key) == 0) {

            if (curr == prev) {
                free(curr);
                last = current = NULL;
            } else {
                prev->next = curr->next;

                if (curr == last)
                    last = prev;

                if (current == curr)
                    current = curr->next;

                free(curr);
            }

            printf("Song deleted\n");
            return;
        }

        prev = curr;
        curr = curr->next;

    } while (curr != last->next);

    printf("Song not found\n");
}

/* play next song */
void playNext() {
    if (current == NULL) {
        printf("Playlist empty\n");
        return;
    }

    current = current->next;
    printf("Now playing: %s - %s\n",
           current->name, current->artist);
}

/* main menu */
int main() {
    int choice;

    while (1) {
        printf("\n1.Add Song\n2.Delete Song\n3.Search Song\n");
        printf("4.Display Playlist\n5.Play Next Song\n6.Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addSong(); break;
            case 2: deleteSong(); break;
            case 3: searchSong(); break;
            case 4: displayPlaylist(); break;
            case 5: playNext(); break;
            case 6: exit(0);
            default: printf("Invalid choice\n");
        }
    }
}



