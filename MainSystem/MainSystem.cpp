#include <MainSystem.h>

MainSystem::MainSystem() {
  internal_state = 0;
  wait_time = 5000;
}

void MainSystem::start() {
  switch (internal_state) {
    case IDLE:
    case STOPPED:
      LOG->I(TAG, "Changed internal_state " + String(internal_state) + " to 1.");
      internal_state = RUNNING;
      run();
      break;
    case RUNNING:
      break;
    case PAUSED:
      break;
  }
}

void MainSystem::run() {
  while (internal_state == RUNNING) {
    smm->nextState();
    command->readCommand();
    delay(wait_time);
  }
}

void MainSystem::stop() {
  // Don't need implementation yet
}

void MainSystem::resume() {
  // Don't need implementation yet
}

MainSystem *MainSystem::instance = 0;

MainSystem *MainSystem::getInstance() {
  if (!instance) instance = new MainSystem();
  return instance;
}