#include <vector>
#include <list>
#include <set>
#include <string>
#include <iostream>
#include <iomanip>
#include "imdb.h"
#include "path.h"
using namespace std;

/**
 * Using the specified prompt, requests that the user supply
 * the name of an actor or actress.  The code returns
 * once the user has supplied a name for which some record within
 * the referenced imdb existsif (or if the user just hits return,
 * which is a signal that the empty string should just be returned.)
 *
 * @param prompt the text that should be used for the meaningful
 *               part of the user prompt.
 * @param db a reference to the imdb which can be used to confirm
 *           that a user's response is a legitimate one.
 * @return the name of the user-supplied actor or actress, or the
 *         empty string.
 */

static string promptForActor(const string& prompt, const imdb& db)
{
  string response;
  while (true) {
    cout << prompt << " [or <enter> to quit]: ";
    getline(cin, response);
    if (response == "") return "";
    vector<film> credits;
    if (db.getCredits(response, credits)) return response;
    cout << "We couldn't find \"" << response << "\" in the movie database. "
	 << "Please try again." << endl;
  }
}

/**
 * Function generateShortestPath
 * -----------------------------
 * @param src name of an actor where connection should start
 * @param db loaded imdb class
 * @param dest name of an actor where connection should end
 * @return pointer to shortest path between src and dest
 */
bool generateShortestPath(const imdb& db, const string& src, const string& target) {
	list<path> partial_paths;
	set<string> seen_actors;
	set<film> seen_movies;
	vector<film> credits;
	vector<string> cast;
	
	partial_paths.push_back(path(src));
	while (partial_paths.size() > 0) {
		//cout << partial_paths.size() << endl;
		if (partial_paths.front().getLength() > 2) return NULL;
		db.getCredits(partial_paths.front().getLastPlayer(), credits);
		// go through credits
		for (unsigned int i = 0; i < credits.size(); i++) {
			if (seen_movies.count(credits[i]) == 0) {
				seen_movies.insert(credits[i]);
				// getcast for movie
				db.getCast(credits[i], cast);
				/* go through cast of an movie */
				for (unsigned int j = 0; j < cast.size(); j++) {
					/* check seen_actors */
					if (seen_actors.count(cast[j]) == 0) {
						seen_actors.insert(cast[j]);
						/* add to partial path */
						partial_paths.front().addConnection(credits[i], cast[j]); // temporary insert connection to front
						partial_paths.push_back(partial_paths.front());           // add path to queue
						partial_paths.front().undoConnection();                   // take back temporary last one
						/* check target */
						if (cast[j] == target) {
							cout << partial_paths.back() << endl;
							return true;
						}
					}
				}
				cast.clear();
			}
		}
		credits.clear();                    // erase processed credits
		partial_paths.pop_front();
	}

	cout << "path" << path(src) << endl;
	return false;
}


/**
 * Serves as the main entry point for the six-degrees executable.
 * There are no parameters to speak of.
 *
 * @param argc the number of tokens passed to the command line to
 *             invoke this executable.  It's completely ignored
 *             here, because we don't expect any arguments.
 * @param argv the C strings making up the full command line.
 *             We expect argv[0] to be logically equivalent to
 *             "six-degrees" (or whatever absolute path was used to
 *             invoke the program), but otherwise these are ignored
 *             as well.
 * @return 0 if the program ends normally, and undefined otherwise.
 */

int main(int argc, const char *argv[])
{
  imdb db(determinePathToData(argv[1])); // inlined in imdb-utils.h
  if (!db.good()) {
    cout << "Failed to properly initialize the imdb database." << endl;
    cout << "Please check to make sure the source files exist and that you have permission to read them." << endl;
    exit(1);
  }
  
  while (true) {
    string source = promptForActor("Actor or actress", db);
    if (source == "") break;
    string target = promptForActor("Another actor or actress", db);
    if (target == "") break;
    if (source == target) {
      cout << "Good one.  This is only interesting if you specify two different people." << endl;
    } else {
      // replace the following line by a call to your generateShortestPath routine... 
	  if (!generateShortestPath(db, source, target))
      	cout << endl << "No path between those two people could be found." << endl << endl;
    }
  }
  
  cout << "Thanks for playing!" << endl;
  return 0;
}

