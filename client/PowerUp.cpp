#include "PowerUp.hpp"

// Implementation headers
#include "Ghost.hpp"
#include "client.hpp"

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

		GhostRevertTaskData *grtd = new GhostRevertTaskData;
		grtd->pkoka = pkoka;
		pkoka->sch->_register(
		 new GhostRevertTask(getCurrentTime() + 5000),
		 grtd);
	}
} // powerup_coca

static void setScared(Ghost *ghost,
 std::map<GameSprite*, ActorMovement*> &akmovs,
 AnimationFilm *film)
{
	if(ghost->GetState() == NORMAL) {
		ghost->SetState(SCARED);
		ghost->setFilm(film);
		akmovs[ghost]->setDelay(25);
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
	db("Task Data");
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
} // GhostRevertTask::()

Task &GhostRevertTask::operator++(void) { return *this; }

void Ghost_collision_callback(Sprite *ghost, Sprite *pacman, void *c) {
	Ghost* gs = dynamic_cast<Ghost*>(ghost);
	if(gs->GetState() == SCARED) { if (c) {
		// It gets called : D
		_gcoca *gkoka = CAST(_gcoca*, c);
		AnimationFilm *retreat_film = gkoka->filmhold->
		 GetFilm("snailyate");
		std::map<GameSprite*, ActorMovement*> &akmovs =
		 *gkoka->akmovs;

		gs->SetState(RETREAT);
		gs->setFilm(retreat_film);
		akmovs[gs]->setDelay(17);
		CollisionChecker::Singleton()->Cancel(gkoka->left_right, gs);	
		CollisionChecker::Singleton()->Register(gkoka->down, gs);
		
	} else
		db("Warning: Useless pacman-ghost callback");
	}
} // collision_callback

void ghost_uneating_callback(Sprite *waypoint, Sprite *_ghost, void *c) {
	Ghost* gs = dynamic_cast<Ghost*>(_ghost);
	if(gs->GetState() == RETREAT) if(c){
		AnimationFilm *film;
		_gcoca *gkoka = CAST(_gcoca*, c);
		if(gs == gkoka->ghost->stalker)
			film = gkoka->filmhold->GetFilm("snaily");
		else if(gs == gkoka->ghost->random)
			film = gkoka->filmhold->GetFilm("snailyl");
		else if(gs == gkoka->ghost->retard)
			film = gkoka->filmhold->GetFilm("snailyd");
		else film = gkoka->filmhold->GetFilm("snailyb");
		gs->SetState(NORMAL);
		gs->setFilm(film);
		(*gkoka->akmovs)[gs]->pressed(ActorMovement::UP, getCurrentTime());
		CollisionChecker::Singleton()->Cancel(gkoka->down, gs);	
		CollisionChecker::Singleton()->Register(gkoka->left_right, gs);
	}
	
} // ghost_uneating_callback
