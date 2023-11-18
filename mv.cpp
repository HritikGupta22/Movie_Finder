#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;
void clearScreen() {
    system("cls");
}
class Movie {
    private:
    string title;
    string releaseDate;
    string synopsis;
    string rating;
    vector<Movie> movies;
public:
    Movie(const string title, const string releaseDate, const string synopsis, const string rating) {
        this->title = title;
        this->releaseDate = releaseDate;
        this->synopsis = synopsis;
        this->rating = rating;
    }

    const string getTitle() const {
        return title;
    }

    const string getReleaseDate() const {
        return releaseDate;
    }

    const string getSynopsis() const {
        return synopsis;
    }

    string getRating() const {
        return rating;
    }


};

class MovieDatabase {
public:
    void loaddata(const string filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Error: Could not open the database file." << endl;
            return;
        }

        string line;
        while (getline(file, line)) {
            if (line.empty()) continue;

            istringstream ss(line);
            string title, releaseDate, synopsis;
            string rating;

            if (getline(ss, title, '|') &&
                getline(ss, releaseDate, '|') &&
                getline(ss, synopsis, '|') &&
                (ss >> rating)) {
                movies.push_back(Movie(title, releaseDate, synopsis, rating));
                
            } else {
                cout << "Error " << line << endl;
            }
        }

        file.close();
    }

    vector<Movie> searchMoviesByKeyword(const string& keyword) {
        vector<Movie> matchingMovies;
        for (const Movie& movie : movies) {
            if (movie.getTitle().find(keyword) != string::npos || movie.getReleaseDate().find(keyword) != string::npos) {
                matchingMovies.push_back(movie);
            }
        }
        return matchingMovies;
    }

    void searchMovie(const string movieTitle) {
        for (const Movie movie : movies) {
            if (movie.getTitle() == movieTitle) {
                cout<<endl;
                cout << "Movie Title: " << movie.getTitle() << endl;
                cout << "Release Date: " << movie.getReleaseDate() << endl;
                cout << "Synopsis: " << movie.getSynopsis() << endl;
                cout << "Rating: " << movie.getRating() << endl;
                return;
            }
        }
        cout<<endl;

        cout << "Movie not found in the database." << endl;
        cout<<endl;
        int subChoice;
        while (true) {
            cout << "1. Add Movie" << endl;
            cout << "2. Return to Main Menu" << endl;
            cout<<endl;
            cout << "Enter your choice: ";
            cin >> subChoice;
            cin.ignore();

            switch (subChoice) {
                case 1:
                    addMovie(movieTitle);
                    break;
                case 2:
                    return;
                default:
                    cout << "Invalid choice. Please try again." << endl;
                    break;
            }
        }
    }

    void addMovie(const string movieTitle) {
        string releaseDate, synopsis;
        string rating;
        cout << "Enter Release Date for " << movieTitle << ": ";
        cin >> releaseDate;
        cin.ignore();
        cout << "Enter Synopsis for " << movieTitle << ": ";
        getline(cin, synopsis);
        cout << "Enter Rating for " << movieTitle << ": ";
        cin >> rating;

        movies.push_back(Movie(movieTitle, releaseDate, synopsis, rating));

    
        ofstream file("moviedb.txt", ios::app);
        if (file.is_open()) {
            file << movieTitle << '|' << releaseDate << '|' << synopsis << '|' << rating << '\n';
            file.close();
            cout<<endl;
            cout << "Movie added to the database." << endl;
            cout<<endl;
        } else {
            cout << "Error" << endl;
        }
    }

     bool isMovieExists(const string& movieTitle) {
        for (const Movie& movie : movies) {
            if (movie.getTitle() == movieTitle) {
                return true;
            }
        }
        return false;
    }

    void deleteMovie(const string movieTitle) {
    if (isMovieExists(movieTitle)) {
        auto it = movies.begin();
        while (it != movies.end()) {
            if (it->getTitle() == movieTitle) {
                it = movies.erase(it);
            } else {
                ++it;
            }
        }
        

        
        ofstream file("moviedb.txt");
        if (file.is_open()) {
            for (const Movie movie : movies) {
                file << movie.getTitle() << '|' << movie.getReleaseDate() << '|'
                     << movie.getSynopsis() << '|' << movie.getRating() << '\n';
            }
            file.close();
            cout<<endl;
            cout << "Movie deleted from the database." << endl;
            cout<<endl;
        }
    } 
    else {
            cout << "Movie Not Found!" << endl;
        }
    }


vector<Movie> movies;
};

int main() {
    MovieDatabase movieDb;
    movieDb.loaddata("moviedb.txt");

    int choice;
    string movieTitle;
    string keyword;

        cout<<endl;
        cout <<"    "<< "===========================================" << endl;
        cout <<"    "<< "|| Welcome to the Movie Database Program ||" << endl;
        cout <<"    "<< "===========================================" << endl;
        cout<<endl;
        vector<Movie> matchingMovies;
    while (true) {
        cout<<endl;
        cout<<"\t> > > > > > > > > > > > > > > > v"<<endl;
        cout<<"\t^"<<"\t\t\t\tv"<<endl;
        cout <<"\t^  "<< "Main Menu:" <<"\t\t\tv"<< endl;
        cout <<"\t^  "<< "1. Search Movie"<<"\t\tv" << endl;
        cout <<"\t^  "<< "2. Movies Library"<<"\t\tv" << endl;
        cout <<"\t^  "<< "3. Search by Keyword/Year"<<"\tv" << endl;
        cout <<"\t^  "<< "4. Exit" <<"\t\t\tv"<< endl;
        cout<<"\t^"<<"\t\t\t\tv"<<endl;
        cout<<"\t^ < < < < < < < < < < < < < < < <"<<endl;
        cout<<endl;
        cout <<"\t"<< "Enter your choice: ";
        cin >> choice;
        cin.ignore();
        clearScreen();
        switch (choice) {
            case 1:
                cout << "Enter the movie title you want to search: ";
                getline(cin, movieTitle);
                movieDb.searchMovie(movieTitle);
                cout<<endl<<endl;
                break;
            case 2:
                int libraryChoice;
                while (true) {

                    cout<<"\t> > > > > > > > > > > > > > > > v"<<endl;
                    cout<<"\t^"<<"\t\t\t\tv"<<endl;
                    cout <<"\t^  "<< "Library Menu:" <<"\t\tv"<< endl;
                    cout <<"\t^  "<< "1. Add Movie"<<"\t\t\tv" << endl;
                    cout <<"\t^  "<< "2. Delete Movie"<<"\t\tv" << endl;
                    cout <<"\t^  "<< "3. Back to Main Menu"<<"\t\tv" << endl;
                    cout<<"\t^"<<"\t\t\t\tv"<<endl;
                    cout<<"\t^ < < < < < < < < < < < < < < < <"<<endl;
                    cout<<endl;
                    cout <<"\t"<< "Enter your choice: ";
                    cin >> libraryChoice;
                    cin.ignore();

                    switch (libraryChoice) {
                        case 1:
                            cout << "Enter the movie title you want to add: ";
                            getline(cin, movieTitle);
                            movieDb.addMovie(movieTitle);
                            break;
                        case 2:
                            cout << "Enter the movie title you want to delete: ";
                            getline(cin, movieTitle);
                            movieDb.deleteMovie(movieTitle);
                            break;
                        
                        case 3:
                            clearScreen();
                            break;
                        default:
                            cout << "Invalid choice in the library menu. Please try again." << endl;
                            break;
                    }

                    if (libraryChoice == 3) {

                        break;
                    }
                }
                break;
            case 3:
            cout << "Enter a keyword/Year to search for movies: ";
                cin >> keyword;
                matchingMovies = movieDb.searchMoviesByKeyword(keyword);

                if (matchingMovies.empty()) {
                    cout<<endl;
                    cout << "No movies found with the keyword: " << keyword << endl;
                } else {
                    cout<<endl;
                    cout << "Movies matching the keyword '" << keyword << "':" << endl;
                    cout<<endl;
                    for (const Movie& movie : matchingMovies) {
                        cout << "Movie Title: " << movie.getTitle() << endl;
                        cout << "Release Date: " << movie.getReleaseDate() << endl;
                        cout << "Synopsis: " << movie.getSynopsis() << endl;
                        cout << "Rating: " << movie.getRating() << endl;
                        cout << endl;
                    }
                }
                break;
            case 4:
                cout << "Exiting the program." << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    }

    return 0;
}