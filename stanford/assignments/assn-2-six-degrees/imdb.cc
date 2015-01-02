using namespace std;
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "imdb.h"

const char *const imdb::kActorFileName = "actordata";
const char *const imdb::kMovieFileName = "moviedata";

static int act_cmp(const void *a, const void *b) {
	struct akeyItem *act_key = (struct akeyItem *)a; // v a jsem predal klic, kde je ulozena baze
	int b_offset = *(int *)b;                        // offset b
	char *b_name = (char *)act_key->base + b_offset; // tady by mel byt zaznam herce
	return strcmp(act_key->name, b_name);
}

static int mov_cmp(const void *a, const void *b) {
	struct fkeyItem *mov_key = (struct fkeyItem *)a; // v a je klic i z bazi
	int b_offset = *(int *)b;                        // offset b
	char *movie_title = (char *)mov_key->base + b_offset; // nazev filmu
	film tfilm;

	tfilm.title = movie_title;                       // movie title
	tfilm.year  = 1900 + *((char*)mov_key->base + b_offset + strlen(movie_title) + 1);
	if (*(mov_key->movie) < tfilm) return -1;
	if (*(mov_key->movie) == tfilm) return 0;
	return 1;
}

imdb::imdb(const string& directory)
{
  const string actorFileName = directory + "/" + kActorFileName;
  const string movieFileName = directory + "/" + kMovieFileName;
  
  actorFile = acquireFileMap(actorFileName, actorInfo);
  movieFile = acquireFileMap(movieFileName, movieInfo);
}

bool imdb::good() const
{
  return !( (actorInfo.fd == -1) || 
	    (movieInfo.fd == -1) ); 
}

// you should be implementing these two methods right here... 
bool imdb::getCredits(const string& player, vector<film>& films) const { 
	char *actor_item, *movie_item;
	struct akeyItem actorKeyItem;
	int actors_count = *(int *)actorFile;
	struct film tfilm;

	actorKeyItem.name = player.c_str();
	actorKeyItem.base = actorFile;
	actor_item = (char *)bsearch(&actorKeyItem, (char *)actorFile + 4, actors_count, sizeof(int), act_cmp);
	if (actor_item == NULL) return false;
	actor_item = (char *)actorFile + *(int *)actor_item;    // porition from offset to real entry 

	// vyparsovat veci z playera a ulozit je do films
	int act_mov_count_off = ((strlen(actor_item) + 2) >> 1) << 1;  // zaokrouhli nahoru na binarni 10
	int act_mov_list_off  = ((strlen(actor_item) + sizeof(short) + 4) >> 2) << 2; // zakrouhli nahoru na binarni 100
	short actor_movies = *(short *)(actor_item + act_mov_count_off);

	for (int i = 0; i < actor_movies; i++) {
		movie_item = (char *)movieFile + *(int *)(actor_item + act_mov_list_off + i*sizeof(int));
		tfilm.title = movie_item;
		tfilm.year = 1900 + *(char *)(movie_item + strlen(movie_item) + 1);
		films.push_back(tfilm);
	}
	return true; 
}

bool imdb::getCast(const film& movie, vector<string>& players) const { 
	char *actor_item, *movie_item;
	struct fkeyItem filmKeyItem;
	int movies_count = *(int *)movieFile;
	
	filmKeyItem.movie = &movie;
	filmKeyItem.base = movieFile;
	movie_item = (char *)bsearch(&filmKeyItem, (char *)movieFile + 4, movies_count, sizeof(int), mov_cmp);
	if (movie_item == NULL) { cout << "NULL" << endl; return false; }
	movie_item = (char *)movieFile + *(int *)movie_item;

	// vyparsovat playery z filmu
	int mov_act_count_off = ((strlen(movie_item) + 3) >> 1) << 1; // zaokrouhli nahoru na binarni 10
	int mov_act_list_off  = ((strlen(movie_item) + sizeof(short) + 5) >> 2) << 2; // zaokrouhli nahoru na binarni 100
	short movies_actors = *(short *)(movie_item + mov_act_count_off);

	for (int i = 0; i < movies_actors; i++) {
		actor_item = (char *)actorFile + *(int *)(movie_item + mov_act_list_off + i*sizeof(int));
		players.push_back(actor_item);
	}
	return true; 
}

imdb::~imdb()
{
  releaseFileMap(actorInfo);
  releaseFileMap(movieInfo);
}

// ignore everything below... it's all UNIXy stuff in place to make a file look like
// an array of bytes in RAM.. 
const void *imdb::acquireFileMap(const string& fileName, struct fileInfo& info)
{
  struct stat stats;
  stat(fileName.c_str(), &stats);
  info.fileSize = stats.st_size;
  info.fd = open(fileName.c_str(), O_RDONLY);
  return info.fileMap = mmap(0, info.fileSize, PROT_READ, MAP_SHARED, info.fd, 0);
}

void imdb::releaseFileMap(struct fileInfo& info)
{
  if (info.fileMap != NULL) munmap((char *) info.fileMap, info.fileSize);
  if (info.fd != -1) close(info.fd);
}
