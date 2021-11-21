#include <MainSystem.h>

MainSystem::MainSystem() {
  internal_state = 0;
}

void MainSystem::start() {
  switch (internal_state) {
    case IDLE: //TODO
    case STOPPED:
      log->I(TAG,
             "Changed internal_state " + String(internal_state) + " to " + String(RUNNING));
      internal_state = RUNNING;
      run();
      break;
    case RUNNING:
      log->E(TAG,
             "Start called when system was already running");
      break;
    case PAUSED:
      log->E(TAG, "System is paused, can't restart system.");
      break;
  }
}

void MainSystem::run() {
  unsigned long int time;
  while (internal_state == RUNNING) {
    time = millis();
    smm->nextState();
    command->readCommand();
    while(millis() - time < TIMESTEP);
  }
}

void MainSystem::stop() {
  // TODO
}

void MainSystem::resume() {
  // TODO
}

MainSystem *MainSystem::instance = 0;

MainSystem *MainSystem::getInstance() {
  if (!instance) instance = new MainSystem();
  return instance;
}