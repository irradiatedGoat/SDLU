#include "ssLoader.h"
#include "Styles.h"

void buildLvl(double time, ssLoader* ssLdr, Loader* ld, Registry* r)
{
	ssLdr->appendQueue(makeEnemy(700, 39, ld, r), time+5, true, ENEMYLIST);
	ssLdr->appendQueue(makeEnemy(700, 65, ld, r), time+8, true, ENEMYLIST);
	ssLdr->appendQueue(makePowerup(700, 255, ld), time+2, true, ENEMYLIST);
	ssLdr->appendQueue(makeEnemy(700, 378, ld, r), time+10, true, ENEMYLIST);
	ssLdr->appendQueue(makeEnemy(700, 39, ld, r), time+11, true, ENEMYLIST);
	ssLdr->appendQueue(makeEnemy(700, 300, ld, r), time+15, true, ENEMYLIST);
	ssLdr->appendQueue(makeEnemy(700, 20, ld, r), time+18, true, ENEMYLIST);
	ssLdr->appendQueue(makeEnemy(700, 200, ld, r), time+19, true, ENEMYLIST);
	ssLdr->appendQueue(makeEnemy(700, 40, ld, r), time+20, true, ENEMYLIST);
	ssLdr->appendQueue(makeEnemy(700, 420, ld, r), time+20, true, ENEMYLIST);
	ssLdr->appendQueue(makeEnemy(700, 20, ld, r), time+21, true, ENEMYLIST);
	ssLdr->appendQueue(makeEnemy(700, 200, ld, r), time+21, true, ENEMYLIST);
	ssLdr->appendQueue(makeEnemy(700, 200, ld, r), time+24, true, ENEMYLIST);
	ssLdr->appendQueue(makeEnemy(700, 39, ld, r), time+25, true, ENEMYLIST);
	ssLdr->appendQueue(makeEnemy(700, 20, ld, r), time+26, true, ENEMYLIST);
	ssLdr->appendQueue(makeEnemy(700, 39, ld, r), time+27, true, ENEMYLIST);
	ssLdr->appendQueue(makeEnemy(700, 0, ld, r), time+30, true, ENEMYLIST);
	ssLdr->appendQueue(makeEnemy(700, 39, ld, r), time+30, true, ENEMYLIST);
	ssLdr->appendQueue(makeEnemy(700, 420, ld, r), time+37, true, ENEMYLIST);
	ssLdr->appendQueue(makeEnemy(700, 20, ld, r), time+41, true, ENEMYLIST);
	ssLdr->appendQueue(makeEnemy(700, 200, ld, r), time+41, true, ENEMYLIST);

}