#include "PowerUp.hpp"

// Implementation headers
#include "Ghost.hpp"
#include "client.hpp"
#include "SoundManager.hpp"

static void setScared(Ghost*, std::map<GameSprite*, ActorMovement*> &,
 AnimationFilm*);
static void ScaredToNormal(Ghost *ghost,
 std::map<GameSprite*, ActorMovement*> &akmovs,
 AnimationFilm *film);

struct GhostRevertTaskData : public TaskData {
	_pcoca *pkoka;
}; // struct GhostRevertTaskData
struct GhostRevertTask : public Task {
	void operator()(TaskData *);
	Task &operator++(void);
	Task &operator+=(timestamp_t);
	GhostRevertTask(timestamp_t time); ~GhostRevertTask(void);
}; // struct GhostRevertTask

void powerup_coca(Sprite *p, Sprite *stoocker, void *c) {
	static Task *ghost_revert_task = CAST(Task*, 0);
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

		if (ghost_revert_task)
			pkoka->sch->cancel(ghost_revert_task);
		GhostRevertTaskData *grtd = new GhostRevertTaskData;
		grtd->pkoka = pkoka;
		pkoka->sch->_register(ghost_revert_task = 
		 new GhostRevertTask(getCurrentTime() + EATABLE_DURATION),
		 grtd);

		SoundManager::Singleton()->PlayEffect(5, POWERUP);
		SoundManager::Singleton()->MuteChannel(0);
		SoundManager::Singleton()->lolChannel(1, 128);
	}
} // powerup_coca

static void setScared(Ghost *ghost,
 std::map<GameSprite*, ActorMovement*> &akmovs,
 AnimationFilm *film)
{
	if(ghost->GetState() == NORMAL) {
		ghost->SetState(SCARED);
		ghost->setFilm(film);
		akmovs[ghost]->setDelay(30);
	}
} // setScared

static void ScaredToNormal(Ghost *ghost,
 std::map<GameSprite*, ActorMovement*> &akmovs,
 AnimationFilm *film)
{
	if(ghost->GetState() == SCARED) {
		ghost->SetState(NORMAL);
		ghost->setFilm(film);
		akmovs[ghost]->setDelay(15);
	}
}


GhostRevertTask::GhostRevertTask(timestamp_t time) :
	Task(time, false) { }
GhostRevertTask::~GhostRevertTask(void) { }

void GhostRevertTask::operator()(TaskData *d) {
	_pcoca *pkoka = dynamic_cast<GhostRevertTaskData*>(d)->pkoka;

	// Change ghosts' status, animation film and anim delay
	AnimationFilm *_film = pkoka->filmhold->
	GetFilm("snaily");
	AnimationFilm *l_film = pkoka->filmhold->
	GetFilm("snailyl");
	AnimationFilm *d_film = pkoka->filmhold->
	GetFilm("snailyd");
	AnimationFilm *b_film = pkoka->filmhold->
	GetFilm("snailyb");
	
	std::map<GameSprite*, ActorMovement*> &akmovs =
		*pkoka->akmovs;
	ScaredToNormal(pkoka->ghost->stalker, akmovs, _film);
	ScaredToNormal(pkoka->ghost->random, akmovs, d_film);
	ScaredToNormal(pkoka->ghost->retard, akmovs, b_film);
	ScaredToNormal(pkoka->ghost->kieken, akmovs, l_film);
	SoundManager::Singleton()->MuteChannel(1);
      	SoundManager::Singleton()->lolChannel(0, 36);
} // GhostRevertTask::()

Task &GhostRevertTask::operator++(void) { return *this; }
Task &GhostRevertTask::operator+=(timestamp_t _time) {
	time += _time;
	return *this;
} // GhostRevertTask +=

