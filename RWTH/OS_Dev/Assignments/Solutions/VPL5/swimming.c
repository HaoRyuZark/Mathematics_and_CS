#include "macros.h"
#include "swimming_lib.h"
#include <semaphore.h>

extern sem_t *changing_room; // initialized to 5
extern sem_t *locker;        // initialized to 20
extern sem_t *shower_room;   // initialized to 12

void swimming_routine() {
	sem_wait(changing_room);
	get_changed();
	sem_post(changing_room);

	sem_wait(locker);

	sem_wait(shower_room);
	shower();
	sem_post(shower_room);

	swim();

	sem_wait(shower_room);
	shower();
	sem_post(shower_room);

	sem_post(locker);

	sem_wait(changing_room);
	get_changed();
	sem_post(changing_room);

	leave();
}
