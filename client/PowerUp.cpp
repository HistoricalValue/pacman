#include "PowerUp.hpp"

// Implementation headers
#include "Ghost.hpp"
#include "client.hpp"

static void setScared(Ghost*, std::map<GameSprite*, ActorMovement*> &,
 AnimationFilm*);
struct GhostRevertTaskData : public TaskData {
	
}; // struct GhostRevertTaskData
struct GhostRevertTask : public Task {
	void operator()(TaskData *);
	Task &operator++(void);
	GhostRevertTask(timestamp_t time); ~GhostRevertTask(void);
}; // struct GhostRevertTask

void powerup_coca(Sprite *p, Sprite *stoocker, void *c) {
	if (p->IsVisible()) if (c) {
		_pcoca *pkoka = CAST(_pcoca*, c);
		p->SetVisibility(false); // powerup

		// Change ghosts' status, animation film and anim delay
		AnimationFilm *scared_film = pkoka->filmhold->
		 GetFilm("snailyeat");
		std::map<GameSprite*, ActorMovement*> &akmovs =
		 *pkoka->akmovs;
		setScared(pkoka->ghost->stalker, akmovs, scared_film);
		setScared(pkoka->ghost->random, akmovs, scared_film);
		setScared(pkoka->ghost->retard, akmovs, scared_film);
		setScared(pkoka->ghost->kieken, akmovs, scared_film);

		pkoka->sch->_register(
		 new GhostRevertTask(getCurrentTime() + 5000),
		 new GhostRevertTaskData);
	}
} // powerup_coca

static void setScared(Ghost *ghost,
 std::map<GameSprite*, ActorMovement*> &akmovs,
 AnimationFilm *film)
{
	ghost->SetState(SCARED);
	ghost->setFilm(film);
	akmovs[ghost]->setDelay(25);
} // setScared

GhostRevertTask::GhostRevertTask(timestamp_t time) :
	Task(time, false) { }
GhostRevertTask::~GhostRevertTask(void) { }

void GhostRevertTask::operator()(TaskData *d) {
	db("Task Data");
} // GhostRevertTask::()

Task &GhostRevertTask::operator++(void) { return *this; }

