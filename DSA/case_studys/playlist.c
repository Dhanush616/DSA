#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Macro for memory allocation and error handling
#define MALLOC(p, n, type) \
{ \
    p = (type *)malloc((n) * sizeof(type)); \
    if (p == NULL) { \
        printf("Insufficient memory\n"); \
        exit(0); \
    } \
}

// Structure for each song node
typedef struct SongNode {
    char title[50];
    char artist[50];
    char genre[30];
    struct SongNode *next; // Pointer to the next song
    struct SongNode *prev; // Pointer to the previous song
} SongNode;

// Alias for SongNode as Song for simplicity
typedef SongNode Song;

// Structure for the playlist, which manages the song nodes
typedef struct Playlist {
    Song *current; // Pointer to the currently playing song
    Song *head;    // Pointer to the first song in the playlist
    Song *tail;    // Pointer to the last song in the playlist
} SongPlaylist;

// Alias for Playlist as SongPlaylist
typedef SongPlaylist Playlist;

// Function to display the main menu options
void display_menu() {
    printf("\n--- Music Playlist Menu ---\n");
    printf("1. Add a song to the playlist\n");
    printf("2. Play the next song\n");
    printf("3. Play the previous song\n");
    printf("4. Switch to a specific song\n");
    printf("5. Display songs by genre\n");
    printf("6. Display all songs\n");
    printf("7. Delete a song\n");
    printf("8. Exit\n");
}

// Function to create a new song with title, artist, and genre
Song* create_song(const char *title, const char *artist, const char *genre) {
    Song *new_song;
    MALLOC(new_song, 1, Song); // Allocate memory for the new song
    strcpy(new_song->title, title);
    strcpy(new_song->artist, artist);
    strcpy(new_song->genre, genre);
    new_song->next = NULL;
    new_song->prev = NULL;
    return new_song;
}

// Function to initialize an empty playlist
void initialize_playlist(Playlist *playlist) {
    playlist->head = NULL;
    playlist->tail = NULL;
    playlist->current = NULL;
}

// Function to add a song to the end of the playlist
void add_song(Playlist *playlist, const char *title, const char *artist, const char *genre) {
    Song *new_song = create_song(title, artist, genre); // Create the new song
    if (playlist->head == NULL) { // If playlist is empty, set the new song as head and tail
        playlist->head = playlist->tail = playlist->current = new_song;
        new_song->next = new_song;
        new_song->prev = new_song;
    } else { // Otherwise, add to the end and update pointers
        new_song->prev = playlist->tail;
        new_song->next = playlist->head;
        playlist->tail->next = new_song;
        playlist->head->prev = new_song;
        playlist->tail = new_song;
    }
    printf("Song %s added to the playlist.\n", title);
}

// Function to play the next song in the playlist (circularly)
void play_next(Playlist *playlist) {
    if (playlist->current) { // If playlist is not empty
        playlist->current = playlist->current->next; // Move to the next song
        printf("Playing next song: %s by %s\n", playlist->current->title, playlist->current->artist);
    } else {
        printf("The playlist is empty.\n");
    }
}

// Function to play the previous song in the playlist (circularly)
void play_previous(Playlist *playlist) {
    if (playlist->current) { // If playlist is not empty
        playlist->current = playlist->current->prev; // Move to the previous song
        printf("Playing previous song: %s by %s\n", playlist->current->title, playlist->current->artist);
    } else {
        printf("The playlist is empty.\n");
    }
}

// Function to switch to a specific song by title
void switch_to_song(Playlist *playlist, const char *title) {
    if (playlist->head == NULL) {
        printf("The playlist is empty.\n");
        return;
    }
    
    Song *temp = playlist->head;
    do {
        if (strcmp(temp->title, title) == 0) { // Check if song title matches
            playlist->current = temp; // Update current song
            printf("Switched to song: %s by %s\n", temp->title, temp->artist);
            return;
        }
        temp = temp->next;
    } while (temp != playlist->head); // Loop until back at the start

    printf("Song %s not found in the playlist.\n", title);
}

// Function to display songs by a specific genre
void display_by_genre(Playlist *playlist, const char *genre) {
    if (playlist->head == NULL) {
        printf("The playlist is empty.\n");
        return;
    }

    Song *temp = playlist->head;
    int found = 0;
    printf("Songs in genre %s:\n", genre);
    
    do {
        if (strcmp(temp->genre, genre) == 0) { // Check if genre matches
            printf(" - %s by %s\n", temp->title, temp->artist);
            found = 1;
        }
        temp = temp->next;
    } while (temp != playlist->head); // Loop until back at the start
    
    if (!found) {
        printf("No songs found in this genre.\n");
    }
}

// Function to display all songs in the playlist
void display_all_songs(Playlist *playlist) {
    if (playlist->head == NULL) {
        printf("The playlist is empty.\n");
        return;
    }

    Song *temp = playlist->head;
    printf("All songs in the playlist:\n");

    do {
        printf(" - %s by %s (Genre: %s)\n", temp->title, temp->artist, temp->genre);
        temp = temp->next;
    } while (temp != playlist->head); // Loop until back at the start
}

// Function to delete a specific song by title
void delete_song(Playlist *playlist, const char *title) {
    if (playlist->head == NULL) {
        printf("The playlist is empty.\n");
        return;
    }

    Song *temp = playlist->head;
    do {
        if (strcmp(temp->title, title) == 0) { // Check if song title matches
            if (temp->next == temp) {  // Only one song in the playlist
                playlist->head = playlist->tail = playlist->current = NULL;
            } else {
                if (temp == playlist->head) {
                    playlist->head = temp->next;
                }
                if (temp == playlist->tail) {
                    playlist->tail = temp->prev;
                }
                if (temp == playlist->current) {
                    playlist->current = temp->next;
                }
                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;
            }
            free(temp); // Free memory for deleted song
            printf("Song %s deleted from the playlist.\n", title);
            return;
        }
        temp = temp->next;
    } while (temp != playlist->head);

    printf("Song %s not found in the playlist.\n", title);
}

// Function to free all songs in the playlist
void free_playlist(Playlist *playlist) {
    if (playlist->head == NULL) {
        return;
    }

    Song *temp = playlist->head;
    do {
        Song *next_song = temp->next;
        free(temp);
        temp = next_song;
    } while (temp != playlist->head);

    playlist->head = playlist->tail = playlist->current = NULL;
}

int main() {
    Playlist playlist;
    initialize_playlist(&playlist);
    
    int choice;
    char title[50], artist[50], genre[30];

    while (1) {
        display_menu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: // Add song to playlist
                printf("Enter song title: ");
                fgets(title, sizeof(title), stdin);
                title[strcspn(title, "\n")] = '\0';

                printf("Enter artist name: ");
                fgets(artist, sizeof(artist), stdin);
                artist[strcspn(artist, "\n")] = '\0';

                printf("Enter genre: ");
                fgets(genre, sizeof(genre), stdin);
                genre[strcspn(genre, "\n")] = '\0';

                add_song(&playlist, title, artist, genre);
                break;

            case 2: // Play next song
                play_next(&playlist);
                break;

            case 3: // Play previous song
                play_previous(&playlist);
                break;

            case 4: // Switch to specific song
                printf("Enter the song title to switch to: ");
                fgets(title, sizeof(title), stdin);
                title[strcspn(title, "\n")] = '\0';
                switch_to_song(&playlist, title);
                break;

            case 5: // Display songs by genre
                printf("Enter genre to display: ");
                fgets(genre, sizeof(genre), stdin);
                genre[strcspn(genre, "\n")] = '\0';
                display_by_genre(&playlist, genre);
                break;

            case 6: // Display all songs
                display_all_songs(&playlist);
                break;

            case 7: // Delete a song
                printf("Enter the song title to delete: ");
                fgets(title, sizeof(title), stdin);
                title[strcspn(title, "\n")] = '\0';
                delete_song(&playlist, title);
                break;

            case 8: // Exit program
                free_playlist(&playlist);
                printf("Exiting the program.\n");
                exit(0);

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}
